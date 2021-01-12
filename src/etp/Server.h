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

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/strand.hpp>
#ifdef WITH_ETP_SSL
#include <boost/asio/ssl.hpp>
#endif
#include <boost/beast/http/file_body.hpp>

#include <thread>
#include <stdexcept>
#include <vector>
#include <fstream>

#include "avro/Compiler.hh"

#include "ServerInitializationParameters.h"

namespace beast = boost::beast;                 // from <boost/beast.hpp>
namespace http = beast::http;                   // from <boost/beast/http.hpp>
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>

namespace ETP_NS
{
	// Return a reasonable mime type based on the extension of a file.
	boost::beast::string_view
		mime_type(boost::beast::string_view path)
	{
		using boost::beast::iequals;
		auto const ext = [&path]
		{
			auto const pos = path.rfind(".");
			if (pos == boost::beast::string_view::npos)
				return boost::beast::string_view{};
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
			boost::beast::string_view base,
			boost::beast::string_view path)
	{
		if (base.empty())
			return path.to_string();
		std::string result = base.to_string();
#if BOOST_MSVC
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
			boost::beast::string_view doc_root,
			http::request<Body, http::basic_fields<Allocator>>&& req,
			Send&& send, ServerInitializationParameters* serverInitializationParams)
	{
		// Returns a bad request response
		auto const bad_request =
			[&req, serverInitializationParams](boost::beast::string_view why)
		{
			http::response<http::string_body> res{ http::status::bad_request, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = why.to_string();
			res.prepare_payload();
			return res;
		};

		// Returns a not found response
		auto const not_found =
			[&req, serverInitializationParams](boost::beast::string_view target)
		{
			http::response<http::string_body> res{ http::status::not_found, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = "The resource '" + target.to_string() + "' was not found.";
			res.prepare_payload();
			return res;
		};

		// Returns an unprocessable_entity response
		auto const unprocessable_entity =
			[&req, serverInitializationParams](boost::beast::string_view target)
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
			[&req, serverInitializationParams](boost::beast::string_view what)
		{
			http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
			res.set(http::field::server, serverInitializationParams->getApplicationName());
			res.set(http::field::content_type, "text/html");
			res.keep_alive(req.keep_alive());
			res.body() = "An error occurred: '" + what.to_string() + "'";
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
			req.target().find("..") != boost::beast::string_view::npos)
			return send(bad_request("Illegal request-target"));

		// Build the path to the requested file
		std::string path = path_cat(doc_root, req.target());
		if (req.target().back() == '/')
			path.append("index.html");

		// Attempt to open the file
		boost::beast::error_code ec;
		http::string_body::value_type body;
		/*
		body.open(path.c_str(), boost::beast::file_mode::scan, ec);

		// Handle the case where the file doesn't exist
		if (ec == boost::system::errc::no_such_file_or_directory)
			return send(not_found(req.target()));
			*/

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

	template <class T>
	class Server
	{
	private:

		ServerInitializationParameters* serverInitializationParams_;
		std::vector< std::shared_ptr<T> > sessions_;

		// Handles an HTTP server connection
		class http_session : public std::enable_shared_from_this<http_session>
		{
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
								self_.socket_,
								msg_,
								boost::asio::bind_executor(
									self_.strand_,
									std::bind(
										&http_session::on_write,
										self_.shared_from_this(),
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

			tcp::socket socket_;
			boost::asio::strand<
				boost::asio::io_context::executor_type> strand_;
			boost::asio::steady_timer timer_;
			boost::beast::flat_buffer buffer_;
			std::shared_ptr<std::string const> doc_root_;
			http::request<http::string_body> req_;
			queue queue_;

			std::vector< std::shared_ptr<T> >& sessions_;
			ServerInitializationParameters* serverInitializationParams_;

		public:
			// Take ownership of the socket
			explicit
				http_session(
					tcp::socket socket,
					std::shared_ptr<std::string const> const& doc_root,
					std::vector< std::shared_ptr<T> >& sessions,
					ServerInitializationParameters* serverInitializationParams)
				: socket_(std::move(socket))
#if BOOST_VERSION < 107000
				, strand_(socket_.get_executor())
				, timer_(socket_.get_executor().context(),
			        (std::chrono::steady_clock::time_point::max)())
#else
				, strand_(static_cast<boost::asio::io_context&>(socket_.get_executor().context()).get_executor())
				, timer_(socket_.get_executor(),
					(std::chrono::steady_clock::time_point::max)())
#endif
				, doc_root_(doc_root)
				, queue_(*this)
				, sessions_(sessions)
				, serverInitializationParams_(serverInitializationParams)
			{
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
								&http_session::run,
								http_session::shared_from_this())));

				// Run the timer. The timer is operated
				// continuously, this simplifies the code.
				on_timer({});

				do_read();
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
				http::async_read(socket_, buffer_, req_,
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&http_session::on_read,
							http_session::shared_from_this(),
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
				{
					// Closing the socket cancels all outstanding operations. They
					// will complete with boost::asio::error::operation_aborted
					socket_.shutdown(tcp::socket::shutdown_both, ec);
					socket_.close(ec);
					return;
				}

				// Wait on the timer
				timer_.async_wait(
					boost::asio::bind_executor(
						strand_,
						std::bind(
							&http_session::on_timer,
							http_session::shared_from_this(),
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
					return do_close();

				if (ec) {
					std::cerr << "read : " << ec.message() << std::endl;
					return;
				}

				// See if it is a WebSocket Upgrade
				if (websocket::is_upgrade(req_))
				{
					// Create a websocket session, transferring ownership
					// of both the socket and the HTTP request.
					std::shared_ptr<T> session = std::make_shared<T>(std::move(socket_)
#ifdef WITH_ETP_SSL
						, ctx_
#endif
						);

					// Set Handlers of the session
					serverInitializationParams_->postSessionCreationOperation(session.get());

					// Run session
					session->run(std::move(req_));
					sessions_.push_back(session);
					std::cout << "Opening the websocket session " << sessions_.size() << std::endl;
					return;
				}

				// Send the response
				handle_request(*doc_root_, std::move(req_), queue_, serverInitializationParams_);

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
					return do_close();
				}

				// Inform the queue that a write completed
				if (queue_.on_write())
				{
					// Read another request
					do_read();
				}
			}

			void
				do_close()
			{
				// Send a TCP shutdown
				boost::system::error_code ec;
				socket_.shutdown(tcp::socket::shutdown_send, ec);

				// At this point the connection is closed gracefully
			}
		};

		// Accepts incoming connections and launches the sessions
		class listener : public std::enable_shared_from_this<listener>
		{
			tcp::acceptor acceptor_;
#ifdef WITH_ETP_SSL
			boost::asio::ssl::context& ctx_;
#endif
			tcp::socket socket_;
			std::vector< std::shared_ptr<T> >& sessions_;
			ServerInitializationParameters* serverInitializationParams_;

		public:
			listener(
				boost::asio::io_context& ioc,
#ifdef WITH_ETP_SSL
				boost::asio::ssl::context& ctx,
#endif
				tcp::endpoint endpoint,
				std::vector< std::shared_ptr<T> >& sessions,
				ServerInitializationParameters* serverInitializationParams)
				: acceptor_(ioc)
#ifdef WITH_ETP_SSL
				, ctx_(ctx)
#endif
				, socket_(ioc)
				, sessions_(sessions)
				, serverInitializationParams_(serverInitializationParams)
			{
				boost::beast::error_code ec;

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
					std::make_shared<http_session>(std::move(socket_), std::make_shared<std::string>("."), sessions_, serverInitializationParams_)->run();
				}

				// Accept another connection
				do_accept();
			}
		};

	public:
		Server(ServerInitializationParameters* serverInitializationParams) : serverInitializationParams_(serverInitializationParams) {}

		std::vector< std::shared_ptr<T> >& getSessions() { return sessions_; }

#ifdef WITH_ETP_SSL
		void listen(const std::string & host, unsigned short port, int threadCount, boost::asio::ssl::context & sslContext) {
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
			// Create and launch a listening port
			std::make_shared<Server::listener>(ioc, sslContext, tcp::endpoint{ address, port }, sessions_, serverInitializationParams_)->run();
#else
			// Create and launch a listening port
			std::make_shared<Server::listener>(ioc, tcp::endpoint{ address, port }, sessions_, serverInitializationParams_)->run();
#endif

			// Capture SIGINT and SIGTERM to perform a clean shutdown
			boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
			signals.async_wait(
				[&](boost::beast::error_code const&, int)
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

