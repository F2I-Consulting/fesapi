/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#pragma once

#include <regex>
#include <thread>
#include <stdexcept>
#include <vector>
#include <fstream>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#ifdef WITH_ETP_SSL
#include <boost/asio/ssl.hpp>
#endif
#include <boost/beast/http/file_body.hpp>

#include "avro/Compiler.hh"

#include "ServerInitializationParameters.h"

namespace beast = boost::beast;                 // from <boost/beast.hpp>
namespace http = beast::http;                   // from <boost/beast/http.hpp>
#ifdef WITH_ETP_SSL
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
#endif
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

namespace ETP_NS
{
	// Return a reasonable mime type based on the extension of a file.
	beast::string_view
		mime_type(beast::string_view path)
	{
		using beast::iequals;
		auto const ext = [&path]
		{
			auto const pos = path.rfind(".");
			if (pos == beast::string_view::npos)
				return beast::string_view{};
			return path.substr(pos);
		}();
		if (iequals(ext, ".htm"))  return "text/html";
		if (iequals(ext, ".html")) return "text/html";
		if (iequals(ext, ".php"))  return "text/html";
		if (iequals(ext, ".css"))  return "text/css";
		if (iequals(ext, ".txt"))  return "text/plain";
		if (iequals(ext, ".js"))   return "application/javascript";
		if (iequals(ext, ".json")) return "application/json";
		if (iequals(ext, ".xml"))  return "application/xml";
		if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
		if (iequals(ext, ".flv"))  return "video/x-flv";
		if (iequals(ext, ".png"))  return "image/png";
		if (iequals(ext, ".jpe"))  return "image/jpeg";
		if (iequals(ext, ".jpeg")) return "image/jpeg";
		if (iequals(ext, ".jpg"))  return "image/jpeg";
		if (iequals(ext, ".gif"))  return "image/gif";
		if (iequals(ext, ".bmp"))  return "image/bmp";
		if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
		if (iequals(ext, ".tiff")) return "image/tiff";
		if (iequals(ext, ".tif"))  return "image/tiff";
		if (iequals(ext, ".svg"))  return "image/svg+xml";
		if (iequals(ext, ".svgz")) return "image/svg+xml";
		return "application/text";
	}

	// Append an HTTP rel-path to a local filesystem path.
	// The returned path is normalized for the platform.
	std::string
		path_cat(
			beast::string_view base,
			beast::string_view path)
	{
		if (base.empty())
			return path.to_string();
		std::string result = base.to_string();
#ifdef BOOST_MSVC
		char constexpr path_separator = '\\';
		if (result.back() == path_separator)
			result.resize(result.size() - 1);
		result.append(path.data(), path.size());
		for (auto& c : result)
			if (c == '/')
				c = path_separator;
#else
		char constexpr path_separator = '/';
		if (result.back() == path_separator)
			result.resize(result.size() - 1);
		result.append(path.data(), path.size());
#endif
		return result;
	}

	// This function produces an HTTP response for the given
	// request. The type of the response object depends on the
	// contents of the request, so the interface requires the
	// caller to pass a generic lambda for receiving the response.
	template<
		class Body, class Allocator,
		class Send>
		void
		handle_request(
			beast::string_view doc_root,
			http::request<Body, http::basic_fields<Allocator>>&& req,
			Send&& send, ServerInitializationParameters* serverInitializationParams)
	{
		// Returns a bad request response
		auto const bad_request =
			[&req, serverInitializationParams](beast::string_view why)
		{
			http::response<http::string_body> res{ http::status::bad_request, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = std::string(why);
			res.prepare_payload();
			return res;
		};

		// Returns a not found response
		auto const not_found =
			[&req, serverInitializationParams](beast::string_view target)
		{
			http::response<http::string_body> res{ http::status::not_found, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = "The resource '" + std::string(target) + "' was not found.";
			res.prepare_payload();
			return res;
		};

		// Returns an unprocessable_entity response
		auto const unprocessable_entity =
			[&req, serverInitializationParams](beast::string_view target)
		{
			http::response<http::string_body> res{ http::status::unprocessable_entity, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = "This server does not support ETP1.1. Add a query string ?GetVersion=etp12.energistics.org if you want to discover these server capabilities.";
			res.prepare_payload();
			return res;
		};

		// Returns a server error response
		auto const server_error =
			[&req, serverInitializationParams](beast::string_view what)
		{
			http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = "An error occurred: '" + std::string(what) + "'";
			res.prepare_payload();
			return res;
		};

		// Make sure we can handle the method
		if (req.method() != http::verb::get &&
			req.method() != http::verb::head)
			return send(bad_request("Unknown HTTP-method"));

		// Request path must be absolute and not contain "..".
		if (req.target().empty() ||
			req.target()[0] != '/' ||
			req.target().find("..") != beast::string_view::npos)
			return send(bad_request("Illegal request-target"));

		// Build the path to the requested file
		std::string path = path_cat(doc_root, req.target());
		if (req.target().back() == '/')
			path.append("index.html");

		// Attempt to open the file
		beast::error_code ec;
		http::string_body::value_type body;
		/*
		body.open(path.c_str(), beast::file_mode::scan, ec);

		// Handle the case where the file doesn't exist
		if (ec == boost::system::errc::no_such_file_or_directory)
			return send(not_found(req.target()));
			*/

		while (path.find("//") != std::string::npos) {
			path = std::regex_replace(path, std::regex("//"), "/");
		}
		while (path.find("\\\\") != std::string::npos) {
			// See https://stackoverflow.com/questions/4025482/cant-escape-the-backslash-with-regex
			path = std::regex_replace(path, std::regex("\\\\\\\\"), "\\");
		}

		if (path == "./.well-known/etp-server-capabilities" ||
			path == ".\\.well-known\\etp-server-capabilities") {
			return send(unprocessable_entity(req.target()));
		}

		if (path != "./.well-known/etp-server-capabilities?GetVersion=etp12.energistics.org" &&
			path != ".\\.well-known\\etp-server-capabilities?GetVersion=etp12.energistics.org" &&
			path != "./.well-known/etp-server-capabilities?GetVersions=true" &&
			path != ".\\.well-known\\etp-server-capabilities?GetVersions=true") {
			return send(not_found(req.target()));
		}

		std::ostringstream oss;

		if (path == "./.well-known/etp-server-capabilities?GetVersion=etp12.energistics.org" ||
			path == ".\\.well-known\\etp-server-capabilities?GetVersion=etp12.energistics.org") {
			avro::ValidSchema vs = avro::compileJsonSchemaFromString(
				"{"
				"  \"type\": \"record\","
				"  \"name\": \"ServerCapabilities\","
				"  \"fields\": ["
				"	{"
				"	  \"name\": \"applicationName\","
				"	  \"type\": \"string\""
				"	},"
				"	{"
				"	  \"name\": \"applicationVersion\","
				"	  \"type\": \"string\""
				"	},"
				"	{"
				"	  \"name\": \"contactInformation\","
				"	  \"type\": {"
				"		\"type\": \"record\","
				"       \"name\": \"Contact\","
				"		\"fields\": ["
				"		  {"
				"		    \"name\": \"organizationName\","
				"		    \"type\": \"string\""
				"		  },"
				"		  {"
				"		    \"name\": \"contactName\","
				"		    \"type\": \"string\""
				"		  },"
				"		  {"
				"		    \"name\": \"contactPhone\","
				"		    \"type\": \"string\""
				"		  },"
				"		  {"
				"		    \"name\": \"contactEmail\","
				"		    \"type\": \"string\""
				"		  }"
				"		]"
				"	  }"
				"	},"
				"	{"
				"	  \"name\": \"supportedCompression\","
				"	  \"type\": {"
				"		\"type\": \"array\","
				"		\"items\": \"string\""
				"	  }"
				"	},"
				"	{"
				"	  \"name\": \"supportedEncodings\","
				"	  \"type\": {"
				"		\"type\": \"array\","
				"		\"items\": \"string\""
				"	  }"
				"	},"
				"	{"
				"	  \"name\": \"supportedFormats\","
				"	  \"type\": {"
				"		\"type\": \"array\","
				"		\"items\": \"string\""
				"	  }"
				"	},"
				"	{"
				"	  \"name\": \"supportedDataObjects\","
				"	  \"type\": {"
				"		\"type\": \"array\","
				"		\"items\": {"
				"		  \"type\": \"record\","
				"		  \"name\" : \"SupportedDataObject\","
				"		  \"fields\" : ["
				"		    {"
				"			  \"name\": \"qualifiedType\","
				"			  \"type\" : \"string\""
				"		    },"
				"		    {"
				"			  \"name\": \"dataObjectCapabilities\","
				"			  \"type\" : {"
				"			    \"type\": \"array\","
				"			    \"items\" : \"string\""
				"		      }"
				"		    }"
				"		  ]"
				"	    }"
				"     }"
				"	},"
				"	{"
				"	  \"name\": \"supportedProtocols\","
				"	  \"type\": {"
				"		\"type\": \"array\","
				"		\"items\": {"
				"		  \"type\": \"record\","
				"		  \"name\": \"SupportedProtocol\","
				"		  \"fields\": ["
				"			{"
				"			  \"name\": \"protocol\","
				"			  \"type\": \"int\""
				"			},"
				"			{"
				"			  \"name\": \"protocolVersion\","
				"			  \"type\": {"
				"				\"type\": \"record\","
				"			    \"name\": \"Version\","
				"			    \"fields\": ["
				"				  {"
				"				    \"name\": \"major\","
				"				    \"type\": \"int\""
				"				  },"
				"				  {"
				"  				    \"name\": \"minor\","
				"				    \"type\": \"int\""
				"				  },"
				"				  {"
				"				    \"name\": \"revision\","
				"				    \"type\": \"int\""
				"				  },"
				"				  {"
				" 				    \"name\": \"patch\","
				"				    \"type\": \"int\""
				"				  }"
				"			    ]"
				"			  }"
				"			},"
				"			{"
				"			  \"name\": \"role\","
				"			  \"type\": \"string\""
				"			},"
				"			{"
				"			  \"name\": \"protocolCapabilities\","
				"			  \"type\": {"
				"				\"type\": \"map\","
				"				\"values\": {"
				"				  \"type\": \"record\","
				"				  \"name\": \"DataValue\","
				"				  \"fields\": ["
				"					{"
				"					  \"name\": \"item\","
				"					  \"type\": ["
				"						\"null\","
				"						\"boolean\","
				"						\"int\","
				"						\"long\","
				"						\"float\","
				"						\"double\","
				"						\"string\""
				"					  ]"
				"					}"
				"				  ]"
				"				}"
				"			  }"
				"			}"
				"		  ]"
				"		}"
				"	  }"
				"	},"
				"	{"
				"	  \"name\": \"endpointCapabilities\","
				"	  \"type\": {"
				"		\"type\": \"map\","
				"		\"values\": {"
				"		  \"type\": \"record\","
				"		  \"name\": \"DataValue\","
				"		  \"fields\": ["
				"			{"
				"			  \"name\": \"item\","
				"			  \"type\": ["
				"				\"null\","
				"				\"boolean\","
				"				\"int\","
				"				\"long\","
				"				\"float\","
				"				\"double\","
				"				\"string\""
				"			  ]"
				"			}"
				"		  ]"
				"		}"
				"	  }"
				"	}"
				"  ]"
				"}"
			);

			Energistics::Etp::v12::Datatypes::ServerCapabilities serverCap;
			serverCap.applicationName = serverInitializationParams->getApplicationName();
			serverCap.applicationVersion = serverInitializationParams->getApplicationVersion();
			serverCap.contactInformation.contactEmail = serverInitializationParams->getContactEmail();
			serverCap.contactInformation.contactName = serverInitializationParams->getContactName();
			serverCap.contactInformation.contactPhone = serverInitializationParams->getContactPhone();
			serverCap.contactInformation.organizationName = serverInitializationParams->getOrganizationName();
			serverCap.endpointCapabilities = serverInitializationParams->makeEndpointCapabilities();
			serverCap.supportedEncodings = serverInitializationParams->makeSupportedEncodings();
			serverCap.supportedFormats.push_back("xml");
			serverCap.supportedDataObjects = serverInitializationParams->makeSupportedDataObjects();
			serverCap.supportedProtocols = serverInitializationParams->makeSupportedProtocols();

			avro::OutputStreamPtr out = avro::ostreamOutputStream(oss);
			avro::EncoderPtr e = avro::jsonPrettyEncoder(vs);
			e->init(*out);
			avro::encode(*e, serverCap);
			e->flush();
			body = oss.str();
		}
		else {
			body = "[ \"etp12.energistics.org\" ]";
		}

		// Handle an unknown error
		if (ec)
			return send(server_error(ec.message()));

		// Cache the size since we need it after the move
		auto const size = body.size();

		// Respond to HEAD request
		if (req.method() == http::verb::head)
		{
			http::response<http::empty_body> res{ http::status::ok, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, mime_type("*.json"));
			res.content_length(size);
			res.keep_alive(req.keep_alive());
			return send(std::move(res));
		}

		// Respond to GET request
		http::response<http::string_body> res{
			std::piecewise_construct,
			std::make_tuple(std::move(body)),
			std::make_tuple(http::status::ok, req.version()) };
		res.set(http::field::server, serverInitializationParams->getApplicationName());
		res.set(http::field::content_type, mime_type("*.json"));
		res.content_length(size);
		res.keep_alive(req.keep_alive());
		return send(std::move(res));
	}

	class Server
	{
	private:

		ServerInitializationParameters* serverInitializationParams_;
		std::vector< std::shared_ptr<AbstractSession> > sessions_;

		template<class Body, class Allocator>
		static void
			make_websocket_session(
				tcp::socket socket,
				http::request<Body, http::basic_fields<Allocator>> req,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams)
		{
			auto session = std::make_shared<PlainServerSession>(std::move(socket));
			serverInitializationParams->postSessionCreationOperation(session.get());
			session->run(std::move(req));
			std::cout << "Opening the plain websocket session " << sessions.size() << std::endl;
			sessions.push_back(session);
		}

#ifdef WITH_ETP_SSL
		template<class Body, class Allocator>
		static void
			make_websocket_session(
				boost::beast::ssl_stream<tcp::socket> stream,
				http::request<Body, http::basic_fields<Allocator>> req,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams)
		{
			auto session = std::make_shared<SslServerSession>(std::move(stream));
			serverInitializationParams->postSessionCreationOperation(session.get());
			session->run(std::move(req));
			std::cout << "Opening the secured websocket session " << sessions.size() << std::endl;
			sessions.push_back(session);
		}
#endif

		// Handles an HTTP server connection.
		// This uses the Curiously Recurring Template Pattern so that
		// the same code works with both SSL streams and regular sockets.
		template<class Derived>
		class http_session
		{
			// Access the derived class, this is part of
			// the Curiously Recurring Template Pattern idiom.
			Derived&
				derived()
			{
				return static_cast<Derived&>(*this);
			}


			// This queue is used for HTTP pipelining.
			class queue
			{
				enum
				{
					// Maximum number of responses we will queue
					limit = 8
				};

				// The type-erased, saved work item
				struct work
				{
					virtual ~work() = default;
					virtual void operator()() = 0;
				};

				http_session& self_;
				std::vector<std::unique_ptr<work>> items_;

			public:
				explicit
					queue(http_session& self)
					: self_(self)
				{
					static_assert(limit > 0, "queue limit must be positive");
					items_.reserve(limit);
				}

				// Returns `true` if we have reached the queue limit
				bool
					is_full() const
				{
					return items_.size() >= limit;
				}

				// Called when a message finishes sending
				// Returns `true` if the caller should initiate a read
				bool
					on_write()
				{
					BOOST_ASSERT(!items_.empty());
					auto const was_full = is_full();
					items_.erase(items_.begin());
					if (!items_.empty())
						(*items_.front())();
					return was_full;
				}

				// Called by the HTTP handler to send a response.
				template<bool isRequest, class Body, class Fields>
				void
					operator()(http::message<isRequest, Body, Fields>&& msg)
				{
					// This holds a work item
					struct work_impl : work
					{
						http_session& self_;
						http::message<isRequest, Body, Fields> msg_;

						work_impl(
							http_session& self,
							http::message<isRequest, Body, Fields>&& msg)
							: self_(self)
							, msg_(std::move(msg))
						{
						}

						void
							operator()()
						{
							http::async_write(
								self_.derived().stream(),
								msg_,
								boost::asio::bind_executor(
									self_.strand_,
									std::bind(
										&http_session::on_write,
										self_.derived().shared_from_this(),
										std::placeholders::_1,
										msg_.need_eof())));
						}
					};

					// Allocate and store the work
					items_.push_back(
						boost::make_unique<work_impl>(self_, std::move(msg)));

					// If there was no previous work, start this one
					if (items_.size() == 1)
						(*items_.front())();
				}
			};

			std::shared_ptr<std::string const> doc_root_;
			http::request<http::string_body> req_;
			queue queue_;
			std::vector< std::shared_ptr<AbstractSession> >& sessions_;
			ServerInitializationParameters* serverInitializationParams_;

		protected:
			boost::asio::steady_timer timer_;
			boost::asio::strand<
				boost::asio::io_context::executor_type> strand_;
			beast::flat_buffer buffer_;

		public:
			// Take ownership of the socket
			explicit
				http_session(
					boost::asio::io_context& ioc,
					std::shared_ptr<std::string const> const& doc_root,
					std::vector< std::shared_ptr<AbstractSession> >& sessions,
					ServerInitializationParameters* serverInitializationParams
				)
				: doc_root_(doc_root)
				, queue_(*this)
				, timer_(ioc,
					(std::chrono::steady_clock::time_point::max)())
				, strand_(ioc.get_executor())
				, sessions_(sessions)
				, serverInitializationParams_(serverInitializationParams)
			{
			}

			void
				do_read()
			{
				// Set the timer
				timer_.expires_after(std::chrono::seconds(15));

				// Make the request empty before reading,
				// otherwise the operation behavior is undefined.
				req_ = {};

				// Read a request
				http::async_read(
					derived().stream(),
					buffer_,
					req_,
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&http_session::on_read,
							derived().shared_from_this(),
							std::placeholders::_1)));
			}

			// Called when the timer expires.
			void
				on_timer(boost::system::error_code ec)
			{
				if (ec && ec != boost::asio::error::operation_aborted) {
					std::cerr << "timer : " << ec.message() << std::endl;
					return;
				}

				// Check if this has been upgraded to Websocket
				if (timer_.expires_at() == (std::chrono::steady_clock::time_point::min)())
					return;

				// Verify that the timer really expired since the deadline may have moved.
				if (timer_.expiry() <= std::chrono::steady_clock::now())
					return derived().do_timeout();

				// Wait on the timer
				timer_.async_wait(
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&http_session::on_timer,
							derived().shared_from_this(),
							std::placeholders::_1)));
			}

			void
				on_read(boost::system::error_code ec)
			{
				// Happens when the timer closes the socket
				if (ec == boost::asio::error::operation_aborted)
					return;

				// This means they closed the connection
				if (ec == http::error::end_of_stream)
					return derived().do_eof();

				if (ec) {
					std::cerr << "HTTP server read issue : " << ec.message() << std::endl;
					return;
				}

				// See if it is a WebSocket Upgrade
				if (websocket::is_upgrade(req_))
				{
					if (req_.count(boost::beast::http::field::sec_websocket_protocol) != 1 ||
						req_.at(boost::beast::http::field::sec_websocket_protocol).find("etp12.energistics.org") == std::string::npos) {
						auto const precondition_failed = [this]()
						{
							http::response<http::string_body> res{ http::status::precondition_failed, req_.version() };
							res.set(http::field::server, serverInitializationParams_->getApplicationName());
							res.set(http::field::content_type, "text/html");
							res.keep_alive(req_.keep_alive());
							res.body() = "The sec-websocket-protocol HTTP header field does not contain etp12.energistics.org.";
							res.prepare_payload();
							return res;
						};
						queue_(precondition_failed());
					}
					else {
						// Make timer expire immediately, by setting expiry to time_point::min we can detect
						// the upgrade to websocket in the timer handler
						timer_.expires_at((std::chrono::steady_clock::time_point::min)());

						// Transfer the stream to a new WebSocket session
						return make_websocket_session(
							derived().release_stream(),
							std::move(req_),
							sessions_,
							serverInitializationParams_);
					}
				}
				else {
					// Send the response
					handle_request(*doc_root_, std::move(req_), queue_, serverInitializationParams_);
				}

				// If we aren't at the queue limit, try to pipeline another request
				if (!queue_.is_full())
					do_read();
			}

			void
				on_write(boost::system::error_code ec, bool close)
			{
				// Happens when the timer closes the socket
				if (ec == boost::asio::error::operation_aborted)
					return;

				if (ec) {
					std::cerr << "write : " << ec.message() << std::endl;
					return;
				}

				if (close)
				{
					// This means we should close the connection, usually because
					// the response indicated the "Connection: close" semantic.
					return derived().do_eof();
				}

				// Inform the queue that a write completed
				if (queue_.on_write())
				{
					// Read another request
					do_read();
				}
			}
		};

		// Handles a plain HTTP connection
		class plain_http_session
			: public http_session<plain_http_session>
			, public std::enable_shared_from_this<plain_http_session>
		{
			tcp::socket socket_;
			boost::asio::strand<
				boost::asio::io_context::executor_type> strand_;

		public:
			// Create the http_session
			plain_http_session(
				tcp::socket socket,
				std::shared_ptr<std::string const> const& doc_root,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams)
				: http_session<plain_http_session>(
#if BOOST_VERSION < 107000
					socket.get_executor().context(),
#else
					static_cast<boost::asio::io_context&>(socket.get_executor().context()),
#endif
					doc_root,
					sessions,
					serverInitializationParams)
				, socket_(std::move(socket))
#if BOOST_VERSION < 107000
				, strand_(socket_.get_executor())
#else
				, strand_(static_cast<boost::asio::io_context&>(socket_.get_executor().context()).get_executor())
#endif

			{
			}

			// Called by the base class
			tcp::socket&
				stream()
			{
				return socket_;
			}

			// Called by the base class
			tcp::socket
				release_stream()
			{
				return std::move(socket_);
			}

			// Start the asynchronous operation
			void
				run()
			{
				// Make sure we run on the strand
				if (!strand_.running_in_this_thread())
					return boost::asio::post(
						boost::asio::bind_executor(
							strand_,
							std::bind(
								&plain_http_session::run,
								shared_from_this())));

				// Run the timer. The timer is operated
				// continuously, this simplifies the code.
				on_timer({});

				do_read();
			}

			void
				do_eof()
			{
				// Send a TCP shutdown
				boost::system::error_code ec;
				socket_.shutdown(tcp::socket::shutdown_send, ec);

				// At this point the connection is closed gracefully
			}

			void
				do_timeout()
			{
				// Closing the socket cancels all outstanding operations. They
				// will complete with boost::asio::error::operation_aborted
				boost::system::error_code ec;
				socket_.shutdown(tcp::socket::shutdown_both, ec);
				socket_.close(ec);
			}
		};
#ifdef WITH_ETP_SSL
		// Handles an SSL HTTP connection
		class ssl_http_session
			: public http_session<ssl_http_session>
			, public std::enable_shared_from_this<ssl_http_session>
		{
			boost::beast::ssl_stream<tcp::socket> stream_;
			boost::asio::strand<
				boost::asio::io_context::executor_type> strand_;
			bool eof_ = false;

		public:
			// Create the http_session
			ssl_http_session(
				tcp::socket socket,
				ssl::context& ctx,
				std::shared_ptr<std::string const> const& doc_root,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams)
				: http_session<ssl_http_session>(
					socket.get_executor().context(),
					doc_root,
					sessions,
					serverInitializationParams)
				, stream_(std::move(socket), ctx)
				, strand_(stream_.get_executor())
			{
			}

			// Called by the base class
			boost::beast::ssl_stream<tcp::socket>&
				stream()
			{
				return stream_;
			}

			// Called by the base class
			boost::beast::ssl_stream<tcp::socket>
				release_stream()
			{
				return std::move(stream_);
			}

			// Start the asynchronous operation
			void
				run()
			{
				// Make sure we run on the strand
				if (!strand_.running_in_this_thread())
					return boost::asio::post(
						boost::asio::bind_executor(
							strand_,
							std::bind(
								&ssl_http_session::run,
								shared_from_this())));

				// Run the timer. The timer is operated
				// continuously, this simplifies the code.
				on_timer({});

				// Set the timer
				timer_.expires_after(std::chrono::seconds(15));

				// Perform the SSL handshake
				// Note, this is the buffered version of the handshake.
				stream_.async_handshake(
					ssl::stream_base::server,
					buffer_.data(),
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&ssl_http_session::on_handshake,
							shared_from_this(),
							std::placeholders::_1,
							std::placeholders::_2)));
			}

			void
				on_handshake(
					boost::system::error_code ec,
					std::size_t bytes_used)
			{
				// Happens when the handshake times out
				if (ec == boost::asio::error::operation_aborted)
					return;

				if (ec) {
					std::cerr << "handshake : " << ec.message() << std::endl;
					return;
				}

				// Consume the portion of the buffer used by the handshake
				buffer_.consume(bytes_used);

				do_read();
			}

			void
				do_eof()
			{
				eof_ = true;

				// Set the timer
				timer_.expires_after(std::chrono::seconds(15));

				// Perform the SSL shutdown
				stream_.async_shutdown(
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&ssl_http_session::on_shutdown,
							shared_from_this(),
							std::placeholders::_1)));
			}

			void
				on_shutdown(boost::system::error_code ec)
			{
				// Happens when the shutdown times out
				if (ec == boost::asio::error::operation_aborted)
					return;

				if (ec) {
					std::cerr << "shutdown : " << ec.message() << std::endl;
					return;
				}

				// At this point the connection is closed gracefully
			}

			void
				do_timeout()
			{
				// If this is true it means we timed out performing the shutdown
				if (eof_)
					return;

				// Start the timer again
				timer_.expires_at(
					(std::chrono::steady_clock::time_point::max)());
				on_timer({});
				do_eof();
			}
		};
#endif
		// Accepts incoming connections and launches the sessions
		class listener : public std::enable_shared_from_this<listener>
		{
			tcp::acceptor acceptor_;
			tcp::socket socket_;
			std::vector< std::shared_ptr<AbstractSession> >& sessions_;
			ServerInitializationParameters* serverInitializationParams_;
#ifdef WITH_ETP_SSL
			ssl::context& ctx_;
			bool useSsl_;
#endif

		public:
#ifdef WITH_ETP_SSL
			listener(
				boost::asio::io_context& ioc,
				tcp::endpoint endpoint,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams,
				ssl::context& ctx,
				bool useSsl
			)
				: acceptor_(ioc)
				, socket_(ioc)
				, sessions_(sessions)
				, serverInitializationParams_(serverInitializationParams)
				, ctx_(ctx)
				, useSsl_(useSsl)
			{
				beast::error_code ec;

				// Open the acceptor
				acceptor_.open(endpoint.protocol(), ec);
				if (ec) {
					std::cerr << "listener open : " << ec.message() << std::endl;
					return;
				}

				// Allow address reuse
				acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
				if (ec) {
					std::cerr << "listener set_option : " << ec.message() << std::endl;
					return;
				}

				// Bind to the server address
				acceptor_.bind(endpoint, ec);
				if (ec) {
					std::cerr << "listener bind : " << ec.message() << std::endl;
					return;
				}

				// Start listening for connections
				acceptor_.listen(
					boost::asio::socket_base::max_listen_connections, ec);
				if (ec) {
					std::cerr << "listener listen : " << ec.message() << std::endl;
					return;
				}
			}
#else
			listener(
				boost::asio::io_context& ioc,
				tcp::endpoint endpoint,
				std::vector< std::shared_ptr<AbstractSession> >& sessions,
				ServerInitializationParameters* serverInitializationParams
			)
				: acceptor_(ioc)
				, socket_(ioc)
				, sessions_(sessions)
				, serverInitializationParams_(serverInitializationParams)
			{
				beast::error_code ec;

				// Open the acceptor
				acceptor_.open(endpoint.protocol(), ec);
				if (ec) {
					std::cerr << "listener open : " << ec.message() << std::endl;
					return;
				}

				// Allow address reuse
				acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
				if (ec) {
					std::cerr << "listener set_option : " << ec.message() << std::endl;
					return;
				}

				// Bind to the server address
				acceptor_.bind(endpoint, ec);
				if (ec) {
					std::cerr << "listener bind : " << ec.message() << std::endl;
					return;
				}

				// Start listening for connections
				acceptor_.listen(
					boost::asio::socket_base::max_listen_connections, ec);
				if (ec) {
					std::cerr << "listener listen : " << ec.message() << std::endl;
					return;
				}
			}
#endif

			// Start accepting incoming connections
			void run() {
				if (!acceptor_.is_open()) { return; }
				do_accept();
			}

			void do_accept() {
				acceptor_.async_accept(
					socket_,
					std::bind(
						&listener::on_accept,
						this->shared_from_this(),
						std::placeholders::_1));
			}

			void on_accept(boost::system::error_code ec) {
				if (ec) {
					std::cerr << "listener on_accept : " << ec.message() << std::endl;
				}
				else {
					// Create the http session and run it
#ifdef WITH_ETP_SSL
					if (useSsl_) {
						std::make_shared<ssl_http_session>(std::move(socket_), ctx_, std::make_shared<std::string>("."), sessions_, serverInitializationParams_)->run();
					}
					else 
#endif
						std::make_shared<plain_http_session>(std::move(socket_), std::make_shared<std::string>("."), sessions_, serverInitializationParams_)->run();
				}

				// Accept another connection
				do_accept();
			}
		};

	public:
		Server(ServerInitializationParameters* serverInitializationParams) : serverInitializationParams_(serverInitializationParams) {}

		std::vector< std::shared_ptr<AbstractSession> >& getSessions() { return sessions_; }

#ifdef WITH_ETP_SSL
		void listen(const std::string & host, unsigned short port, int threadCount,
			const std::string & cert = "", const std::string & key = "", const std::string & dh = "") {
#else
		void listen(const std::string & host, unsigned short port, int threadCount) {
#endif
			if (threadCount < 1) {
				throw std::invalid_argument("You need to run your server on at least one thread.");
			}
			auto const address = boost::asio::ip::make_address(host);

			// The io_context is required for all I/O
			boost::asio::io_context ioc{ threadCount };

#ifdef WITH_ETP_SSL
			// The context life scope must the server life scope. That's why it is not inside the below condition.
			ssl::context ctx{ ssl::context::tlsv12_server };

			// Create and launch a listening port
			if (!dh.empty()) {

				ctx.set_password_callback(
					[](std::size_t,
						boost::asio::ssl::context_base::password_purpose)
				{
					return "test";
				});

				ctx.set_options(
					boost::asio::ssl::context::default_workarounds |
					boost::asio::ssl::context::no_sslv2 |
					boost::asio::ssl::context::no_sslv3 |
					boost::asio::ssl::context::single_dh_use);

				ctx.use_certificate_chain(
					boost::asio::buffer(cert.data(), cert.size()));

				ctx.use_private_key(
					boost::asio::buffer(key.data(), key.size()),
					boost::asio::ssl::context::file_format::pem);

				ctx.use_tmp_dh(
					boost::asio::buffer(dh.data(), dh.size()));

				std::make_shared<Server::listener>(ioc, tcp::endpoint{ address, port }, sessions_, serverInitializationParams_, ctx, true)->run();
			}
			else {
				std::make_shared<Server::listener>(ioc, tcp::endpoint{ address, port }, sessions_, serverInitializationParams_, ctx, false)->run();
			}
#else
				// Create and launch a listening port
			std::make_shared<Server::listener>(ioc, tcp::endpoint{ address, port }, sessions_, serverInitializationParams_)->run();
#endif

			// Capture SIGINT and SIGTERM to perform a clean shutdown
			boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
			signals.async_wait(
				[&](beast::error_code const&, int)
			{
				// Stop the `io_context`. This will cause `run()`
				// to return immediately, eventually destroying the
				// `io_context` and all of the sockets in it.
				ioc.stop();
			});

			// Run the I/O service on the requested number of threads
			std::vector<std::thread> v;
			v.reserve(threadCount - 1);
			for (auto i = threadCount - 1; i > 0; --i)
				v.emplace_back(
					[&ioc]
			{
				auto handlersExecuted = ioc.run();
				std::cout << "The thread has executed " << handlersExecuted << " handlers." << std::endl;
			});
			auto handlersExecuted = ioc.run();
			std::cout << handlersExecuted << " handlers have been executed." << std::endl;
		}
	};
}
