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
%module fesapi

%{
#include <stdint.h>		// Use the C99 official header
%}

%include <swigarch.i>

/* Exact integral types.  */

/* Signed.  */

typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;
#if defined(SWIGWORDSIZE64)
typedef long int		int64_t;
#else
typedef long long int		int64_t;
#endif

/* Unsigned.  */
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
#ifndef SWIGJAVA	
#if defined(SWIGWORDSIZE64)
typedef unsigned long int	uint64_t;
#else
typedef unsigned long long int	uint64_t;
#endif
#endif

%include "std_string.i"

%include "../src/nsDefinitions.h"

//************************/
// JAVA
//************************/

#ifdef SWIGJAVA		
	// We don't want to use BigInteger in java.
	#if defined(SWIGWORDSIZE64)
	typedef long int		uint64_t;
	#else
	typedef long long int		uint64_t;
	#endif	
	
	/*
	 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
	 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
	 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
	 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
	 Two macros are available in java.swg to make this easier and using them is the preferred approach over simply copying the typemaps and modifying as this is forward compatible with any changes in the javabody typemap in future versions of SWIG.
	 The macros are for the proxy and typewrapper classes and can respectively be used to make the method and constructor public:
	  SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	  SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	*/
	SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	
	// http://www.swig.org/Doc4.0/SWIGDocumentation.html#Java_proper_enums
	%include "enums.swg"
	%javaconst(1);
	
	%include "swigJavaInclude.i"
#endif

//************************/
// CSHARP
//************************/

#ifdef SWIGCSHARP
	SWIG_CSBODY_PROXY(public, public, SWIGTYPE)
	SWIG_CSBODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	
	%include "swigCsInclude.i"
#endif

//************************/
// PYTHON
//************************/

#ifdef SWIGPYTHON

	%{
	#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping
	%}
	%include "swigPythonInclude.i"

#endif


//************************/
// POD C ARRAYS
//************************/

%include "carrays_indexing64bits.i"
#ifdef SWIGJAVA // Use functions instead of classes in java in order to avoid premature garbage collection
	%array_functions(unsigned long long, ULongArray);
	%array_functions(unsigned int, UIntArray);
	%array_functions(int, IntArray);
	%array_functions(long long, LongArray);
	%array_functions(float, FloatArray);
	%array_functions(double, DoubleArray);
	%array_functions(short, ShortArray);
	%array_functions(unsigned short, UShortArray);
	%array_functions(char, CharArray);
	%array_functions(unsigned char, UCharArray);
	%array_functions(bool, BoolArray);
#else // Use GC.KeepAlive on these arrays to ensure no premature garbage collection in C#
	%array_class(unsigned long long, ULongArray);
	%array_class(unsigned int, UIntArray);
	%array_class(int, IntArray);
	%array_class(long long, LongArray);
	%array_class(float, FloatArray);
	%array_class(double, DoubleArray);
	%array_class(short, ShortArray);
	%array_class(unsigned short, UShortArray);
	%array_class(char, CharArray);
	%array_class(unsigned char, UCharArray);
	%array_class(bool, BoolArray);
#endif

// Example below of premature garbage collection
// DoubleArray myDoubleArray = new DoubleArray(100);
// myOperations(myDoubleArray.cast());
// myDoubleArray can be GC after cast and before myOperations has finished.

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"

%template(StringVector) std::vector< std::string >;
%template(Int32Vector) std::vector< int >;
%template(Int64Vector) std::vector< long long >;
%template(FloatVector) std::vector< float >;
%template(DoubleVector) std::vector< double >;
%template(BoolVector) std::vector< bool >;

//************************/
// EXCEPTIONS
//************************/

%include "exception.i"
%exception {
    try {
        $action
    }
    catch (std::invalid_argument & e) {
        SWIG_exception(SWIG_TypeError,const_cast<char*>(e.what()));
    } 
    catch (std::out_of_range& e) {
        SWIG_exception(SWIG_IndexError,const_cast<char*>(e.what()));
    }
    catch (std::logic_error & e) {
        SWIG_exception(SWIG_SyntaxError,const_cast<char*>(e.what()));
    } 
    catch(...) {
        SWIG_exception(SWIG_RuntimeError,"Unknown exception at F2I C++ API level");
    }
}

typedef long long 				time_t;

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace COMMON_NS::AbstractObject;
	%nspace COMMON_NS::DataObjectReference;
	%nspace COMMON_NS::DataObjectRepository;
	%nspace COMMON_NS::EnumStringMapper;
	%nspace COMMON_NS::EpcDocument;
	%nspace COMMON_NS::HdfProxyFactory;
#endif

namespace EML2_NS
{
	class Activity;
}

%module(directors="1") fesapi
%feature("director") COMMON_NS::HdfProxyFactory;

/*
Following csbody and javabody typemap definitions force the target language to not 
manage the memory of the C++ part of wrapped COMMON_NS::HdfProxyFactory and 
COMMON_NS::AbstractObject. This C++ parts will be free at the destruction
of the COMMON_NS::DataObjectRepository thanks to the 
DataObjectRepository::clear() method (called by DataObjectRepository 
destructor).
*/
%typemap(csbody) COMMON_NS::HdfProxyFactory %{
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public HdfProxyFactory(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = false;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(HdfProxyFactory obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }
%}
%typemap(javabody) COMMON_NS::HdfProxyFactory %{
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  public HdfProxyFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = false;
    swigCPtr = cPtr;
  }

  public static long getCPtr(HdfProxyFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

/* 
AbstractHdfProxy may be inherited in target languages. In such case, overriding
AbstractObject::getXmlNamespace() is required. Thus, AbstractObject needs to be
a director base class. 
Note: to not export the virtual destructor in a director base class leads to a 
warning (205) during the Swig processing.
*/
%feature("director") COMMON_NS::AbstractObject;
%typemap(csbody) COMMON_NS::AbstractObject %{
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  public AbstractObject(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = false;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  public static global::System.Runtime.InteropServices.HandleRef getCPtr(AbstractObject obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }
%}
namespace COMMON_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	class DataObjectReference
	{
	public:
		/**
		 * Checks if this reference is empty (i.e. it points to nothing)
		 *
		 * @returns	True if this reference empty, false if it is not.
		 */
		bool isEmpty() const;
		
		/**
		 * Gets the referenced data object UUID
		 *
		 * @returns	The UUID of the referenced data object if it exists, otherwise empty string.
		 */
		std::string getUuid() const;
		
		/**
		 * Gets the referenced data object title (i.e. its name)
		 *
		 * @returns	The title of the referenced data object if it exists, otherwise empty string.
		 */
		std::string getTitle() const;
		
		/**
		 * Gets the referenced data object version
		 *
		 * @returns	The version of the referenced data object if it exists, otherwise empty string.
		 */
		std::string getVersion() const;
		
		/**
		 * Gets the referenced data object type
		 *
		 * @returns	The content type of the referenced data object if it exists, otherwise empty string.
		 */
		std::string getContentType() const;
	};
	
	class AbstractObject
	{
	public:
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG_64 = 3, ULONG_64 = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};
	
		virtual ~AbstractObject();
	
		/**
		 * Indicates if this data object is actually a partial object. A partial object just contains a mime
		 * type, an UUID and a title as a minimum amount of information. A partial object is never
		 * explicit in an EPC document: it is not a file
		 *
		 * @returns	True if is partial, false if is not.
		 */
		bool isPartial() const;
	
		/**
		 * Gets the UUID (https://tools.ietf.org/html/rfc4122#page-3) of this data object. The UUID
		 * intends to give an id to the \"thing\" (i.e. the business object), not to this instance
		 *
		 * @exception	std::invalid_argument	If no available gSOAP proxy instance is associated to
		 * 										this data object.
		 *
		 * @returns	The UUID of this data object.
		 */
		std::string getUuid() const;
		
		/**
		 * Gets the title (i.e. the name) of this data object. This is the equivalent of
		 * @c CI_Citation.title in ISO 19115
		 *
		 * @exception	std::invalid_argument	If no available gSOAP proxy instance is associated to
		 * 										this data object.
		 *
		 * @returns	The title of this data object.
		 */
		std::string getTitle() const;

		/**
		 * Gets the name (or other human-readable identifier) of the last person who updated the object.
		 * In ISO 19115, this is equivalent to the @c CI_Individual.name or the @c CI_Organization.name of
		 * the @c citedResponsibleParty whose role is @c editor
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The editor of this data object if it is defined, else empty string.
		 */
		std::string getEditor() const;
		
		/**
		 * Gets the date and time the data object was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c creation
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The creation date and time of the data object.
		 */
		time_t getCreation() const;

		/**
		 * Gets the name (or other human-readable identifier) of the person who initially originated
		 * this data object or document in the source application. If that information is not available,
		 * then this is the user of the session during the file creation. The originator remains the
		 * same as the object is subsequently edited. This is the equivalent in ISO 19115 to the @c
		 * CI_Individual.name or the @c CI_Organization.name of the @c citedResponsibleParty whose role
		 * is @c originator
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The originator name or identifier.
		 */
		std::string getOriginator() const;

		/**
		 * Gets the user descriptive comments about this data object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 @c abstract.CharacterString
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The description of this data object if it is defined, else empty string.
		 */
		std::string getDescription() const;

		/**
		 * Gets the date and time the data object was last modified in the source application or, if
		 * that information is not available, when it was last saved to the file. This is the equivalent
		 * of the ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c lastUpdate
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The last update date and time of the data object.
		 */
		time_t getLastUpdate() const;

		/**
		 * Gets the identifier of the software or service that was used to originate the data object and
		 * to create the file. Must be human and machine readable and unambiguously identify the
		 * software by including the company name, software name and software version. This is the
		 * equivalent in ISO 19115 to the @c istributionFormat.MD_Format. The ISO format for this is
		 * <tt> [vendor:applicationName]/fileExtension </tt> where the application name includes the
		 * version number of the application. In our case, @c fileExtension is not relevant and will be
		 * ignored if present. @c vendor and @c applicationName are mandatory
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The identifier of the software or service that was used to originate the data object
		 * 			and to create the file.
		 */
		std::string getFormat() const;

		/**
		 * Gets the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this data object. Intended to be used in a search function by
		 * software. This is the equivalent in ISO 19115 of @c descriptiveKeywords.MD_Keywords
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The key words to describe the activity relevant to this data object if they are
		 * 			defined, else empty string.
		 */
		std::string getDescriptiveKeywords() const;

		/**
		 * Gets the version of this data object. An empty version indicates that this is the latest (and
		 * ideally also the unique) version of this data object.
		 *
		 * @returns	The version of this object, empty string means latest version.
		 */
		std::string getVersion() const;

		/**
		 * Sets the title (i.e. the name) of this data object. This is the equivalent of
		 * @c CI_Citation.title in ISO 19115
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p title is more than 256 chars long.
		 *
		 * @param 	title	The title to set to this data object. If empty then \"unknown\" title will be
		 * 					set.
		 */
		void setTitle(const std::string & title);

		/**
		 * Sets the name (or other human-readable identifier) of the last person who updated the object.
		 * In ISO 19115, this is equivalent to the @c CI_Individual.name or the @c CI_Organization.name
		 * of the @c citedResponsibleParty whose role is @c editor
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p editor is more than 64 chars long.
		 *
		 * @param 	editor	The editor to set to this data object. 
		 */
		void setEditor(const std::string & editor);

		/**
		 * Sets the date and time the data object was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c creation
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @param 	creation	The creation date and time to set to this data object.
		 */
		void setCreation(time_t creation);

		/**
		 * Sets the name (or other human-readable identifier) of the person who initially originated
		 * this data object or document in the source application. If that information is not available,
		 * then this is the user of the session during the file creation. The originator remains the
		 * same as the object is subsequently edited. This is the equivalent in ISO 19115 to the @c
		 * CI_Individual.name or the @c CI_Organization.name of the @c citedResponsibleParty whose role
		 * is @c originator
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p originator is more than 64 chars long.
		 *
		 * @param 	originator	The originator name or identifier to set to this data object. If empty,
		 * 						the user id is set if available, \"unknown\" if it is not.
		 */
		void setOriginator(const std::string & originator);

		/**
		 * Sets a user descriptive comments about this data object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 @c abstract.CharacterString
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p description is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 *
		 * @param 	description	The description to set to this data object.
		 */
		void setDescription(const std::string & description);

		/**
		 * Sets the date and time the data object was last modified in the source application or, if
		 * that information is not available, when it was last saved to the file. This is the equivalent
		 * of the ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c lastUpdate
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @param 	lastUpdate	The last update date and time to set to this data object.
		 */
		void setLastUpdate(time_t lastUpdate);

		/**
		 * Sets the default citation format which is going to be written in each created object. A
		 * maximum of 256 chars is allowed.
		 *
		 * @exception	std::range_error	If the format is more than 256 chars long.
		 *
		 * @param 	vendor						The name of the vendor which is exporting the data
		 * 										objects.
		 * @param 	applicationName				The name of the application which is exporting the data
		 * 										objects.
		 * @param 	applicationVersionNumber	The version of the application which is exporting the
		 * 										data objects.
		 */
		static void setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber);
		
		/**
		 * Set the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this object. Intended to be used in a search function by software.
		 * This is the equivalent in ISO 19115 of descriptiveKeywords.MD_Keywords
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p descriptiveKeywords is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 *
		 * @param 	descriptiveKeywords	The key words to describe the activity relevant to this data
		 * 								object.
		 */
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);

		/**
		 * Set the version of this data object
		 *
		 * @exception	std::invalid_argument	If @p version is empty.
		 * @exception	std::range_error	 	If @p version is more than 64 chars long.
		 *
		 * @param 	version	The version to set to this data object.
		 */
		void setVersion(const std::string & version);

		/**
		 * Sets a title and other common metadata for this instance.
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p title is more than 256 chars long.
		 * @exception	std::range_error	 	If @p editor title is more than 64 chars long.
		 * @exception	std::range_error	 	If @p originator title is more than 64 chars long.
		 * @exception	std::range_error	 	If @p description is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 * @exception	std::range_error	 	If @p descriptiveKeywords is too long (more than 4000
		 * 										chars for RESQML2.0 or more than 2000 chars for EML2.1
		 * 										and EML2.2).
		 *
		 * @param 	title			   	The title to set to this instance. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	editor			   	The editor to set to this instance. Set to empty string or zero
		 * 								if you don't want to use.
		 * @param 	creation		   	The creation date and time to set to this instance.
		 * @param 	originator		   	The originator name or identifier to set to this instance. If
		 * 								empty, the user id is set if available, \"unknown\" if it is not.
		 * @param 	description		   	The description to set to this instance. Set to empty string or
		 * 								zero if you don't want to use.
		 * @param 	lastUpdate		   	The last update date and time to set to this data object.
		 * @param 	descriptiveKeywords	The key words to describe the activity relevant to this data
		 * 								object. Set to empty string or zero if you don't want to use.
		 */
		void setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/**
		 * Returns the data object repository which contains this instance
		 * 
		 * @returns A pointer to the data object repository.
		 */
		COMMON_NS::DataObjectRepository* getRepository() const;
		
		/**
		* Gets the XML namespace for the tags for the XML serialization of this instance
		*
		* @returns	The XML namespace of this instance.
		*/
		std::string getXmlNamespace() const;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		std::string getXmlTag() const;

		/**
		 * Gets the version of the XML namespace (i.e. WITSML, RESQML, PRODML) for the XML serialization
		 * of this instance
		 *
		 * @returns	The XML namespace version of this instance.
		 */
		std::string getXmlNamespaceVersion() const;

		/**
		 * Get the qualified type of the instance i.e. "namespace.datatype"
		 *
		 * @returns	The qualified type of the instance i.e. "namespace.datatype"
		 */
		std::string getQualifiedType() const;

		/**
		 * Serializes the gSOAP proxy of this instance into a string
		 *
		 * @returns	The string result of the serialization process.
		 */
		std::string serializeIntoString();

		/**
		 * Adds an alias for this data object
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p authority or @p title is more than 64 chars long.
		 *
		 * @param 	authority	The authority of the alias.
		 * @param 	title	 	The title of the alias.
		 */
		void addAlias(const std::string & authority, const std::string & title);

		/**
		 * Gets the count of aliases in this instance
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The alias count of this instance.
		 */
		uint64_t getAliasCount() const;

		/**
		 * Gets the alias authority at a particular index in the aliases set
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked alias authority.
		 *
		 * @returns	The alias authority at @p index.
		 */
		std::string getAliasAuthorityAtIndex(uint64_t index) const;

		/**
		 * Gets the alias title at a particular index in the aliases set
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked alias title.
		 *
		 * @returns	The alias title at @p index.
		 */
		std::string getAliasTitleAtIndex(uint64_t index) const;

		/**
		 * Gets the count of the activities where this instance is involved
		 *
		 * @returns	The count of all activities involving this instance.
		 */
		uint64_t getActivityCount() const;

		/**
		 * Gets an associated activity at a particular index
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked activity.
		 *
		 * @returns	The associated activity at @p index.
		 */
		EML2_NS::Activity* getActivity(uint64_t index) const;

		/**
		 * Pushes back an extra metadata (not a standard one) onto this instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0, EML2.1 or EML2.2 one.
		 *
		 * @param 	key  	The key of the metadata.
		 * @param 	value	The value of the metadata.
		 */
		void pushBackExtraMetadata(const std::string & key, const std::string & value);

		/**
		 * Get the count of extra metadata in this instance
		 *
		 * @returns	The extra metadata count of this instance.
		 */
		uint64_t getExtraMetadataCount() const;

		/**
		 * Get the key of a key value pair at a particular index in the extra metadata set of this
		 * instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 or EML2.2 one.
		 *
		 * @param 	index	Zero-based index of the asked key.
		 *
		 * @returns	The extra metadata key at @p index.
		 */
		std::string getExtraMetadataKeyAtIndex(uint64_t index) const;

		/**
		 * Get the value of a key value pair at a particular index in the extra metadata set of this
		 * instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 or EML2.2 one.
		 *
		 * @param 	index	Zero-based index of the asked value.
		 *
		 * @returns	The extra metadata value at @p index.
		 */
		std::string getExtraMetadataStringValueAtIndex(uint64_t index) const;
		
		/**
		* Build and return an ETP1.2 URI from an Energistics dataobject.
		* @return	The ETP1.2 URI built from the Energistics dataobject
		*/
		std::string buildEtp12Uri() const;
	};

%warnfilter(473) HdfProxyFactory::make;
	class HdfProxyFactory
	{
	public:
		HdfProxyFactory() {}
		virtual ~HdfProxyFactory();
		
		virtual EML2_NS::AbstractHdfProxy* make(const DataObjectReference& dor);
		
		/*
		The following method leads to a warning (473: Returning a pointer or reference
		in a director method is not recommended) when it is processed by SWIG since
		there is no guarantee as to the lifetime of the object returned 
		in its target language redefinition. We ensure that the C++ part of all
		COMMON_NS::AbstractObject created from the target language side is never garbage 
		collected thanks to upper %typemap(csbody) COMMON_NS::AbstractObject definition.
		Then it is always safe to make use of these objects in fesapi methods.
		*/
		virtual EML2_NS::AbstractHdfProxy* make(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			const std::string & packageDirAbsolutePath, const std::string & externalFilePath,
			COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess = COMMON_NS::DataObjectRepository::openingMode::READ_ONLY);
	};
}

#define CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName) bool has##vectorName##attributeName(uint64_t index) const;

#define GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName, attributeDatatype)\
	void set##vectorName##attributeName(uint64_t index, const attributeDatatype& value);\
	attributeDatatype get##vectorName##attributeName(uint64_t index) const;\
	CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName)
	
#define GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom);\
	double get##vectorName##attributeName##Value(uint64_t index) const;\
	uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const;\
	CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName)
	
%define SWIG_GETTER_DATAOBJECTS(returnedDataType, dataObjectName)
	uint64_t get ## dataObjectName ## Count() const;
	returnedDataType * get ## dataObjectName(uint64_t index) const;
%enddef

%include "swigEml2Include.i"
%include "swigResqml2Include.i"
%include "swigWitsml2Include.i"
%include "swigProdml2_1Include.i"
#ifdef WITH_ETP
%include "swigEtp1_2Include.i"
#endif

%{
#include "../src/common/EnumStringMapper.h"
#include "../src/common/EpcDocument.h"
#include "../src/common/HdfProxyFactory.h"
%}

namespace COMMON_NS
{
%typemap(javaimports) COMMON_NS::DataObjectRepository %{
import java.lang.AutoCloseable;
import com.f2i_consulting.fesapi.*;
%}
%typemap(javainterfaces) COMMON_NS::DataObjectRepository "AutoCloseable"
%typemap(javacode) COMMON_NS::DataObjectRepository %{
  @Override
  public void close() {
	clear();
    delete();
  }
%}
	class DataObjectRepository
	{
	public:

		/** Values that represent the HDF5 file permission access */
		enum class openingMode : std::int8_t {
			READ_ONLY = 0,
			READ_WRITE = 1,
			READ_WRITE_DO_NOT_CREATE = 2,
			OVERWRITE = 3
		};

		/** Enumeration for the various Energistics standards. */
		enum class EnergisticsStandard : std::int8_t {
			RESQML2_0_1 = 0,
			EML2_0 = 1,
			WITSML2_0 = 2,
			EML2_1 = 3,
			PRODML2_1 = 4,
			EML2_2 = 5,
			RESQML2_2 = 6,
			EML2_3 = 7
		};
		
		DataObjectRepository();

		/**
		 * Constructor
		 *
		 * @param 	propertyKindMappingFilesDirectory	Pathname of the property kind mapping files
		 * 												directory.
		 */
		DataObjectRepository(const std::string & propertyKindMappingFilesDirectory);

		/**
		* Set the used standard when creating a new dataobject
		*/
		void setDefaultStandard(EnergisticsStandard version);

		/**
		* Gets the default EML version used when creating a EML data object.
		*
		* @returns The default EML version.
		*/
		EnergisticsStandard getDefaultEmlVersion() const;

		/**
		* Gets the default PRODML version used when creating a PRODML data object.
		* 
		* @returns The default PRODML version.
		*/
		EnergisticsStandard getDefaultProdmlVersion() const;

		/**
		* Gets the default RESQML version used when creating a RESQML data object.
		* 
		* @returns The default RESQML version.
		*/
		EnergisticsStandard getDefaultResqmlVersion() const;

		/**
		* Gets the default WITSML version used when creating a WITSML data object.
		* 
		* @returns The default WITSML version.
		*/
		EnergisticsStandard getDefaultWitsmlVersion() const;

		/** Removes and cleans all data objects from this repository */
		void clear();

		/**
		 * Gets the default CRS for writing. It is used in all writing methods if no explicit CRS is
		 * provided.
		 *
		 * @returns	A pointer to the default CRS if it is defined, else null.
		 */
		RESQML2_NS::AbstractLocal3dCrs* getDefaultCrs() const;

		/**
		 * Sets a default CRS for writing. It will be used in all writing methods if no explicit CRS is
		 * provided
		 *
		 * @param [in]	crs	If non-null, the default CRS.
		 */
		void setDefaultCrs(RESQML2_NS::AbstractLocal3dCrs* crs);

		/**
		 * Gets the default HDF5 file proxy for writing. It is used in all writing methods if no
		 * explicit HDF5 file proxy is provided.
		 *
		 * @returns	@c nullptr if no default HDF5 file proxy is defined, else a pointer to the default HDF5 file proxy.
		 */
		EML2_NS::AbstractHdfProxy* getDefaultHdfProxy() const;

		/**
		 * Sets a default HDF5 file proxy for writing. It will be used in all writing methods if no
		 * explicit HDF5 file proxy is provided.
		 *
		 * @param [in]	hdfProxy	If non-null, the HDF5 file proxy.
		 */
		void setDefaultHdfProxy(EML2_NS::AbstractHdfProxy* hdfProxy);

		/**
		* Set the factory used to create HDF proxy and takes ownership of this HDF Proxy factory (don't delete it!)
		* 
		* @param [in]	factory	If non-null, the factory.
		*/
		void setHdfProxyFactory(COMMON_NS::HdfProxyFactory * factory);
		
		/**
		 * Adds or replaces (based on Energistics XML definition) a data object in the repository. It
		 * does not update the relationships of the added or replaced data object
		 *
		 * @exception	std::invalid_argument	If, during a replacement, the content type of the data
		 * 										object has changed.
		 *
		 * @param 	xml					The XML which is the serialization of the Energistics data object to add
		 * 								or to replace.
		 * @param 	contentOrDataType	The content or qualified data type of the Energistics dataobject to add or to replace.
		 * @param	uriSource			The EPC document absolute path or the ETP dataspace URI where this dataobject comes from
		 *
		 * @returns	Null if the content type of the data object cannot be wrapped by fesapi, else a
		 * 			pointer the added or replaced data object.
		 */
		COMMON_NS::AbstractObject* addOrReplaceGsoapProxy(const std::string& xml, const std::string& contentType, const std::string& uriSource);
		
		SWIG_GETTER_DATAOBJECTS(EML2_NS::AbstractHdfProxy, HdfProxy)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::AbstractLocal3dCrs, Local3dCrs)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::Activity, Activity)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::ActivityTemplate, ActivityTemplate)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::ColumnBasedTable, ColumnBasedTable)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::GraphicalInformationSet, GraphicalInformationSet)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::PropertyKind, PropertyKind)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::ReferencePointInALocalEngineeringCompoundCrs, ReferencePointInALocalEngineeringCompoundCrs)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::TimeSeries, TimeSeries)

		SWIG_GETTER_DATAOBJECTS(RESQML2_0_1_NS::DeviationSurveyRepresentation, DeviationSurveyRepresentation)

		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractSeismicLineFeature, SeismicLine)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractIjkGridRepresentation, IjkGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BlockedWellboreRepresentation, BlockedWellboreRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fault)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fracture)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, GeobodyBoundary)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Horizon)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::CmpLineFeature, CmpLine)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::CulturalFeature, Cultural)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, AllGrid2dRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, HorizonGrid2dRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridParametricRepresentation, IjkGridParametricRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridExplicitRepresentation, IjkGridExplicitRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridLatticeRepresentation, IjkSeismicCubeGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Model, Model)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PointSetRepresentation, PointSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, AllPolylineRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, HorizonPolylineRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, SeismicLinePolylineRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, AllPolylineSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, HorizonPolylineSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FaultPolylineSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FracturePolylineSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, CulturalPolylineSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RepresentationSetRepresentation, RepresentationSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RockVolumeFeature, RockVolume)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RockVolumeFeature, Geobody)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SeismicLatticeFeature, SeismicLattice)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SeismicLineSetFeature, SeismicLineSet)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::ShotPointLineFeature, ShotPointLine)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StreamlinesFeature, StreamlinesFeature)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StreamlinesRepresentation, StreamlinesRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, SubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, AllTriangulatedSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, UnclassifiedTriangulatedSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FaultTriangulatedSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FractureTriangulatedSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, HorizonTriangulatedSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::UnstructuredGridRepresentation, UnstructuredGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, Wellbore)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreTrajectoryRepresentation, WellboreTrajectoryRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreFrameRepresentation, WellboreFrameRepresentation)

		SWIG_GETTER_DATAOBJECTS(WITSML2_NS::Well, WitsmlWell)
		SWIG_GETTER_DATAOBJECTS(WITSML2_NS::Wellbore, WitsmlWellbore)
		SWIG_GETTER_DATAOBJECTS(WITSML2_NS::Trajectory, WitsmlTrajectory)

		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::WellCompletion, WellCompletion)
		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::WellboreCompletion, WellboreCompletion)
		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::WellboreGeometry, WellboreGeometry)
		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::Log, Log)
		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::ChannelSet, ChannelSet)
		SWIG_GETTER_DATAOBJECTS(WITSML2_0_NS::Channel, Channel)

		SWIG_GETTER_DATAOBJECTS(PRODML2_1_NS::FluidSystem, FluidSystem)
		SWIG_GETTER_DATAOBJECTS(PRODML2_1_NS::FluidCharacterization, FluidCharacterization)

		/**
		 * Gets a data object from the repository by means of its uuid. If several data object
		 * correspond to this uuid in the repository, the first one in memory will be arbitrarily
		 * returned.
		 *
		 * @param 	uuid	The uuid of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to the uuid, @c nullptr if there exists no
		 * 			such data object.
		 */
		AbstractObject* getDataObjectByUuid(const std::string & uuid) const;

		/**
		 * Gets a data object from the repository by means of both its uuid and version.
		 *
		 * @param 	uuid   	The uuid of the requested data object.
		 * @param 	version	The version of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to both uuid and version, @c nullptr if there
		 * 			exists no such data object.
		 */
		AbstractObject* getDataObjectByUuidAndVersion(const std::string & uuid, const std::string & version) const;

		/**
		 * Gets all the data object uuids which are part of this repository
		 *
		 * @returns	A vector of uuids.
		 */
		std::vector<std::string> getUuids() const;

		/**
		 * Creates a partial object in this repository based on a data object reference.
		 *
		 * @exception	std::invalid_argument	If no partial object can be created from @p dor.
		 *
		 * @param 	dor	A data object reference.
		 *
		 * @returns	A pointer to the created partial object.
		 */
		COMMON_NS::AbstractObject* createPartial(const DataObjectReference& dor);

		/**
		 * @brief	Creates a non parallel access to an HDF5 file for writing to it. Resulting HDF5 file
		 * 			proxy is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the HDF5 file proxy. If empty then a new
		 * 									guid will be generated.
		 * @param 	title				  	The title to set to the HDF5 file proxy. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	packageDirAbsolutePath	Path of the directory where the HDF5 file must be created.
		 * @param 	filePath	  			Path of the HDF5 file relative to packageDirAbsolutePath.
		 * @param 	hdfPermissionAccess   	The HDF5 file permission access. It is read
		 * 										only by default.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		EML2_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & filePath, DataObjectRepository::openingMode hdfPermissionAccess);

		//************ CRS *******************

		/**
		 * @brief	Creates a local depth 3d CRS which is fully identified by means of an EPSG code.
		 * 			Resulting local depth 3d CRS is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param 	guid			 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			 	The title to set to the local 3d CRS. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	originOrdinal1   	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2   	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3   	The offset in depth of the local CRS regarding the depth origin
		 * 								of the vertical CRS.
		 * @param 	arealRotation	 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	The EPSG code of the associated projected CRS.
		 * @param 	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode 	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented	 	If true, indicates that this depth CRS is actually an elevation
		 * 								CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is fully unknown. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason 	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		  	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is unknown for its vertical part. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param 	guid				 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				 	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		 	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		 	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		 	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	 	The EPSG code of the associated projected CRS.
		 * @param 	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		 	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is unknown for its projected part and which is
		 * 			identified by an EPSG code for its vertical part. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode	  	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented		  	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is fully identified by means of EPSG code.
		 * 			Resulting local time 3d CRS is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param 	guid			 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			 	The title to set to the local 3d CRS. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	originOrdinal1   	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2   	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3   	The offset in depth of the local CRS regarding the depth origin
		 * 								of the vertical CRS.
		 * @param 	arealRotation	 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	The EPSG code of the associated projected CRS.
		 * @param 	timeUom			 	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode 	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented	 	If true, indicates that the Z offset if an elevation when
		 * 								positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is fully unknown. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason 	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		  	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is unknown for its vertical part. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param 	guid				 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				 	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		 	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		 	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		 	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	 	The EPSG code of the associated projected CRS.
		 * @param 	timeUom				 	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		 	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which unknown for its projected part and which is
		 * 			identified by an EPSG code for its vertical part. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode	  	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented		  	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		EML2_NS::AbstractLocal3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a reference point (such as a MD datum) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	  	guid					 	The guid to set to the reference point. If empty then a new
		 * 											guid will be generated.
		 * @param 	  	title					 	The title to set to the reference point. If empty then
		 * 											\"unknown\" title will be set.
		 * @param [in]	locCrs					 	The local 3d CRS associated to this reference point if non-null,
		 * 											else the default local 3d CRS.
		 * @param 	  	originKind				 	The reference location of the reference point.
		 * @param 	  	referenceLocationOrdinal1	The first reference location ordinal relative to the
		 * 											local 3d CRS.
		 * @param 	  	referenceLocationOrdinal2	The second reference location ordinal relative to the
		 * 											local 3d CRS.
		 * @param 	  	referenceLocationOrdinal3	The third reference location ordinal relative to the
		 * 											local 3d CRS.
		 *
		 * @returns	A pointer to the new reference point.
		 */
		EML2_NS::ReferencePointInALocalEngineeringCompoundCrs* createReferencePointInALocalEngineeringCompoundCrs(const std::string & guid, const std::string & title,
			EML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		//************ FEATURE ***************

		/**
		 * @brief	Creates a boundary feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the boundary feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the boundary feature. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new boundary feature.
		 */
		RESQML2_NS::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a horizon into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the horizon. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the horizon. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new horizon.
		 */
		RESQML2_NS::BoundaryFeature* createHorizon(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a geobody boundary feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the geobody boundary feature. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the geobody boundary feature. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new geobody boundary feature.
		 */
		RESQML2_NS::BoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the geobody feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the geobody feature. If empty then \"unknown\" title will
		 * 					be set.
		 *
		 * @returns	A pointer to the new geobody feature.
		 */
		RESQML2_NS::RockVolumeFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a fault into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the fault. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the fault. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new fault.
		 */
		RESQML2_NS::BoundaryFeature* createFault(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a fracture into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the fracture. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the fracture. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new fracture.
		 */
		RESQML2_NS::BoundaryFeature* createFracture(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a wellbore feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the wellbore feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the wellbore feature. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new wellbore feature.
		 */
		RESQML2_NS::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a seismic lattice into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid			  	The guid to set to the seismic lattice. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			  	The title to set to the seismic lattice. If empty then
		 * 								\"unknown\" title will be set.
		 * @param 	inlineIncrement   	The constant index increment between two consecutive inlines of
		 * 								the seismic lattice.
		 * @param 	crosslineIncrement	The constant index increment between two consecutive crosslines
		 * 								of the seismic lattice.
		 * @param 	originInline	  	The index of the first inline of the seismic lattice.
		 * @param 	originCrossline   	The index of the first crossline of the seismic lattice.
		 * @param 	inlineCount		  	Number of inlines.
		 * @param 	crosslineCount	  	Number of crosslines.
		 *
		 * @returns	A pointer to the new seismic lattice.
		 */
		RESQML2_NS::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			int64_t inlineIncrement, int64_t crosslineIncrement,
			uint64_t originInline, uint64_t originCrossline,
			uint64_t inlineCount, uint64_t crosslineCount);

		/**
		 * Creates a seismic line into this repository
		 *
		 * @param 	guid			   	The guid to set to the seismic line. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			   	The title to set to the seismic line. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	traceIndexIncrement	The constant index increment between two consecutive traces.
		 * @param 	firstTraceIndex	   	The index of the first trace of the seismic line.
		 * @param 	traceCount		   	Number of traces.
		 *
		 * @returns	A pointer to the new seismic line.
		 */
		RESQML2_0_1_NS::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			int64_t traceIndexIncrement, uint64_t firstTraceIndex, uint64_t traceCount);

		/**
		 * @brief	Creates a CMP line into this repository
		 *
		 * @param 	guid								The guid to set to the CMP line. If empty then a
		 * 												new guid will be generated.
		 * @param 	title								The title to set to the CMP line. If empty then
		 * 												\"unknown\" title will be set.
		 * @param 	nearestShotPointIndicesIncrement	The constant index increment between two
		 * 												consecutive shot points indices.
		 * @param 	firstNearestShotPointIndex			The index of the first shot point of the CMP line.
		 * @param 	nearestShotPointCount				Number of shot point.
		 *
		 * @returns	A pointer to the new CMP line.
		 */
		RESQML2_NS::CmpLineFeature* createCmpLine(const std::string & guid, const std::string & title,
			int64_t nearestShotPointIndicesIncrement, int64_t firstNearestShotPointIndex, uint64_t nearestShotPointCount);

		/**
		 * Creates a shot point line into this repository
		 *
		 * @param 	guid			   	The guid to set to the shot point line. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			   	The title to set to the shot point line. If empty then \"unknown\"
		 * 								title will be set.
		 *
		 * @returns	A pointer to the new CMP line.
		 */
		RESQML2_NS::ShotPointLineFeature* createShotPointLine(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a seismic line set into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the seismic line set. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the seismic line set. If empty then \"unknown\".
		 *
		 * @returns	A pointer to the new seismic line set.
		 */
		RESQML2_NS::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a cultural into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the cultural. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the cultural. If empty then \"unknown\" title will be set.
		 * @param 	kind 	(Optional) The kind to set to the cultural. It is defaulted to
		 * 					gsoap_eml2_3::resqml22__CulturalFeatureKind::project_x0020boundaries for
		 * 					easing 2.0.1 compatibility.
		 *
		 * @returns	A pointer to the new cultural.
		 */
		RESQML2_NS::CulturalFeature* createCultural(const std::string & guid, const std::string & title,
			gsoap_eml2_3::resqml22__CulturalFeatureKind kind = gsoap_eml2_3::resqml22__CulturalFeatureKind::project_x0020boundaries);

		/**
		 * @brief	@deprecated Use {@link createRockVolumeFeature()} method for RESQML post v2.0.1
		 * 			Creates a stratigraphic unit into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic unit. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic unit. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic unit.
		 */
		RESQML2_NS::RockVolumeFeature* createStratigraphicUnitFeature(const std::string & guid, const std::string & title);

		/**
		 * @deprecated Use {@link createRockVolumeFeature()} method for RESQML post v2.0.1
		 * Creates a RockVolume feature into this repository
		 *
		 * @param 	guid 	The guid to set to the RockVolume feature. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the RockVolume feature. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new RockVolume feature.
		 */
		RESQML2_NS::RockVolumeFeature* createRockVolumeFeature(const std::string & guid, const std::string & title);

		/**
		 * Creates a model into this repository.
		 *
		 * @param 	guid 	The guid to set to the model. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the model. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new model.
		 */
		RESQML2_NS::Model* createModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a
		 * 			structural model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the structural model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the structural model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new structural model.
		 */
		RESQML2_NS::Model* createStructuralModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a
		 * 			stratigraphic model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic model.
		 */
		RESQML2_NS::Model* createStratigraphicModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a rock
		 * 			fluid model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the rock fluid model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the rock fluid model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new rock fluid model.
		 */
		RESQML2_NS::Model* createRockFluidModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates an earth
		 * 			model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the earth model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the earth model. If empty then \"unknown\" title will be
		 * 					set.
		 *
		 * @returns	A pointer to the new earth model.
		 */
		RESQML2_NS::Model* createEarthModel(const std::string & guid, const std::string & title);

		/**
		 * Creates a fluid boundary feature into this repository
		 *
		 * @param 	guid			The guid to set to the fluid boundary feature. If empty then a new
		 * 							guid will be generated.
		 * @param 	title			The title to set to the fluid boundary feature. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	fluidContact	The fluid contact.
		 *
		 * @returns	A pointer to the new fluid boundary feature.
		 */
		RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__FluidContact fluidContact);

		/**
		 * Creates rock fluid unit into this repository
		 *
		 * @param 		  	guid			   	The guid to set to the rock fluid unit. If empty then a
		 * 										new guid will be generated.
		 * @param 		  	title			   	The title to set to the rock fluid unit. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 		  	phase			   	The phase to set to the rock fluid unit.
		 * @param [in]		fluidBoundaryTop   	The rock fluid unit top boundary. It cannot be null.
		 * @param [in]		fluidBoundaryBottom	The rock fluid unit bottom boundary. It cannot be null.
		 *
		 * @returns	A pointer to the new rock fluid unit.
		 */
		RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);

		//************ INTERPRETATION ********

		/**
		 * @brief	Creates a generic feature interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param [in]	feature	The interpreted feature. It cannot be null.
		 * @param 	  	guid   	The guid to set to the generic feature interpretation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the generic feature interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new generic feature interpretation.
		 */
		RESQML2_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * Creates a boundary feature interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p feature is @c nullptr.
		 *
		 * @param [in]	feature	The interpreted boundary feature. It cannot be null.
		 * @param 	  	guid   	The guid to set to the boundary feature interpretation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the boundary feature interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new boundary feature interpretation.
		 */
		RESQML2_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a horizon interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>horizon == nullptr</tt>.
		 *
		 * @param [in]	horizon	The interpreted horizon. It cannot be null.
		 * @param 	  	guid   	The guid to set to the horizon interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title  	The title to set to the horizon interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new horizon interpretation.
		 */
		RESQML2_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_NS::BoundaryFeature * horizon, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody boundary interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>geobodyBoundary == nullptr</tt>.
		 *
		 * @param [in]	geobodyBoundary	The interpreted geobody boundary. It cannot be null.
		 * @param 	  	guid		   	The guid to set to the geobody boundary interpretation. If empty
		 * 								then a new guid will be generated.
		 * @param 	  	title		   	The title to set to the geobody boundary interpretation. If empty
		 * 								then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new geobody boundary interpretation.
		 */
		RESQML2_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_NS::BoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a fault interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>fault == nullptr</tt>.
		 *
		 * @param [in]	fault	The interpreted fault. It cannot be null.
		 * @param 	  	guid 	The guid to set to the fault interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title	The title to set to the fault interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new fault interpretation.
		 */
		RESQML2_NS::FaultInterpretation* createFaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a fluid Boundary interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>fault == nullptr</tt>.
		 *
		 * @param [in]	boundary		The interpreted boundary. It cannot be null.
		 * @param 	  	guid 			The guid to set to the interpretation. If empty then a new guid
		 * 								will be generated.
		 * @param 	  	title			The title to set to the interpretation. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	fluidContact	The fluid contact this boundary is.
		 *
		 * @returns	A pointer to the new interpretation.
		 */
		RESQML2_NS::FluidBoundaryInterpretation* createFluidBoundaryInterpretation(RESQML2_NS::BoundaryFeature * boundary, const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__FluidContact fluidContact);

		/**
		 * @brief	Creates a wellbore interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p wellbore is @c nullptr.
		 *
		 * @param [in]	wellbore 	The interpreted wellbore feature. It cannot be null.
		 * @param 	  	guid	 	The guid to set to the wellbore interpretation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title	 	The title to set to the wellbore interpretation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	isDrilled	Indicate if the wellbore is interpreted wether as drilled (true) or
		 * 									not (false).
		 *
		 * @returns	A pointer to the new wellbore interpretation.
		 */
		RESQML2_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);

		/**
		 * @brief	Creates an earth model interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt>.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the earth model interpretation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title  	The title to set to the earth model interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new earth model interpretation.
		 */
		RESQML2_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by age into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by apparent depth into this
		 * 			repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by measured depth into this
		 * 			repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a rock fluid organization interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a fluid organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the rock fluid organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the rock fluid organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new rock fluid organization interpretation.
		 */
		RESQML2_NS::RockFluidOrganizationInterpretation* createRockFluidOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a rock fluid unit interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param [in]	rockFluidUnitFeature	The interpreted rock fluid unit. It cannot be null.
		 * @param 	  	guid					The guid to set to the rock fluid unit interpretation. If
		 * 										empty then a new guid will be generated.
		 * @param 	  	title					The title to set to the rock fluid unit interpretation.
		 * 										If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new rock fluid unit interpretation.
		 */
		RESQML2_NS::RockFluidUnitInterpretation* createRockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>geobody == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p geobody is not an actual geobody feature.
		 *
		 * @param [in]	geobody	The interpreted geobody. It cannot be null.
		 * @param 	  	guid   	The guid to set to the geobody interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title  	The title to set to the geobody interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new geobody interpretation.
		 */
		RESQML2_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_NS::RockVolumeFeature* geobody, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic unit interpretation into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>stratiUnitFeature == nullptr</tt>.
		 *
		 * @param [in]	stratiUnitFeature	The interpreted stratigraphic unit. It cannot be null.
		 * @param 	  	guid			 	The guid to set to the stratigraphic unit interpretation. If
		 * 									empty then a new guid will be generated.
		 * @param 	  	title			 	The title to set to the stratigraphic unit interpretation. If
		 * 									empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic unit interpretation.
		 */
		RESQML2_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_NS::RockVolumeFeature * stratiUnitFeature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates stratigraphic column into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic column. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic column. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic column.
		 */
		RESQML2_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic column rank interpretation ordered by age into this
		 * 			repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic column rank interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic column rank interpretation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	rank   	The rank of the stratigraphic column rank interpretation.
		 *
		 * @returns	A pointer to the new stratigraphic column rank interpretation.
		 */
		RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);

		/**
		 * @brief	Creates a stratigraphic column rank interpretation ordered by apparent depth into
		 * 			this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic column rank interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic column rank interpretation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	rank   	The rank of the stratigraphic column rank interpretation.
		 *
		 * @returns	A pointer to the new stratigraphic column rank interpretation.
		 */
		RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);

		/**
		 * @brief	Creates a stratigraphic occurrence interpretation ordered by age into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic occurrence interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic occurrence interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic occurrence interpretation.
		 */
		RESQML2_NS::GeologicUnitOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic occurrence interpretation ordered by apparent depth into this
		 * 			repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic occurrence interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic occurrence interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic occurrence interpretation.
		 */
		RESQML2_NS::GeologicUnitOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		//************ REPRESENTATION ********

		/**
		 * @brief	Creates a triangulated set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the triangulated set representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title	The title to set to the triangulated set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new triangulated set representation.
		 */
		RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a triangulated set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createTriangulatedSetRepresentation} if no interpretation is
		 * 						associated to this representation.
		 * @param 	  	guid  	The guid to set to the triangulated set representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the triangulated set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new triangulated set representation.
		 */
		RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the polyline set representation. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the polyline set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createPolylineSetRepresentation} if no interpretation is
		 * 						associated to this representation.
		 * @param 	  	guid  	The guid to set to the polyline set representation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title 	The title to set to the polyline set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 * @exception	std::invalid_argument	If in a RESQML v2.0 context, @p roleKind is a break line
		 * 										role.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 							alternatively use {@link  createPolylineSetRepresentation} if no
		 * 							interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline set representation. If empty then a
		 * 							new guid will be generated.
		 * @param 	  	title   	The title to set to the polyline set representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	roleKind	The polyline set role kind.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind);

		/**
		 * @brief	Creates a point set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the point set representation. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the point set representation. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new point set representation.
		 */
		RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a point set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the point set representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the point set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new point set representation.
		 */
		RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a plane set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the plane set representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the plane set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new plane set representation.
		 */
		RESQML2_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid		The guid to set to the polyline representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	title   	The title to set to the polyline representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	isClosed	(Optional) True if the polyline is closed, false (default) if it is not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 							alternatively use {@link  createPolylineRepresentation} if no
		 * 							interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline representation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title   	The title to set to the polyline representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	isClosed	(Optional) True if the polyline is closed, false (default) if it is
		 * 							not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 									alternatively use {@link  createPolylineRepresentation} if no
		 * 									interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline representation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title   	The title to set to the polyline representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	roleKind	The polyline role kind.
		 * @param 	  	isClosed	(Optional) True if the polyline is closed, false (default) if it is
		 * 							not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind, bool isClosed = false);

		/**
		 * Creates a 2d grid representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the 2d grid representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the 2d grid representation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new 2d grid representation.
		 */
		RESQML2_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a wellbore trajectory representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p mdInfo is @c nullptr.
		 *
		 * @param [in]	interp		The represented wellbore interpretation. It cannot be null.
		 * @param 	  	guid  		The guid to set to the wellbore trajectory representation. If empty then
		 * 							a new guid will be generated.
		 * @param 	  	title 		The title to set to the wellbore trajectory representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param [in]	mdDatum		The MD datum of the trajectory, mainly the well reference point. It cannot be null.
		 *
		 * @returns	A pointer to the new wellbore trajectory representation.
		 */
		RESQML2_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, EML2_NS::ReferencePointInALocalEngineeringCompoundCrs* mdDatum);

		/**
		 * Creates a wellbore trajectory representation (with an existing deviation survey as its
		 * origin) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p deviationSurvey is @c nullptr.
		 *
		 * @param [in]	interp		   	The represented interpretation. It cannot be null.
		 * @param 	  	guid		   	The guid to set to the wellbore trajectory representation. If
		 * 								empty then a new guid will be generated.
		 * @param 	  	title		   	The title to set to the wellbore trajectory representation. If
		 * 								empty then \"unknown\" title will be set.
		 * @param [in]	deviationSurvey	The deviation survey on which this wellbore trajectory relies on.
		 * 								MD data will be retrieve from it. It cannot be null.
		 *
		 * @returns	A pointer to the new wellbore trajectory representation.
		 */
		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_0_1_NS::DeviationSurveyRepresentation* deviationSurvey);

		/**
		 * @brief	Creates a deviation survey representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>mdInfo ==
		 * 												nullptr</tt>.
		 *
		 * @param [in]	interp 		The represented interpretation. It cannot be null.
		 * @param 	  	guid   		The guid to set to the deviation survey representation. If empty then a
		 * 							new guid will be generated.
		 * @param 	  	title  		The title to set to the deviation survey representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	isFinal		Used to indicate that this is a final version of the deviation survey
		 * 							(true), as distinct from the interim interpretations (false).
		 * @param [in]	refPoint 	The reference point which acts as a datum for this deviation survey representation.
		 *							It canot be null.
		 *
		 * @returns	A pointer to the new deviation survey representation.
		 */
		RESQML2_0_1_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, bool isFinal, EML2_NS::ReferencePointInALocalEngineeringCompoundCrs* refPoint);

		/**
		 * @brief	Creates a wellbore frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore frame representation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore frame representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore frame. It cannot be
		 * 						null.
		 *
		 * @returns	A pointer to the new wellbore frame representation.
		 */
		RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a seismic wellbore frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If @p interp, @p traj or @p crs is @c nullptr.
		 *
		 * @param [in]	interp				 	The represented interpretation. It cannot be null.
		 * @param 	  	guid				 	The guid to set to the seismic wellbore frame
		 * 										representation. If empty then a new guid will be
		 * 										generated.
		 * @param 	  	title				 	The title to set to the seismic wellbore frame
		 * 										representation. If empty then \"unknown\" title will be
		 * 										set.
		 * @param [in]	traj				 	The wellbore trajectory that refers this seismic wellbore
		 * 										frame. It cannot be null.
		 * @param 	  	seismicReferenceDatum	The Z value where the seismic time is equal to zero for
		 * 										this survey wellbore frame.
		 * @param 	  	weatheringVelocity   	The weathering velocity. Sometimes also called seismic
		 * 										velocity replacement.
		 * @param [in]	crs					 	The local time 3d CRS that refers this seismic wellbore
		 * 										frame.
		 *
		 * @returns	A pointer to the new seismic wellbore frame representation.
		 */
		RESQML2_NS::SeismicWellboreFrameRepresentation* createSeismicWellboreFrameRepresentation(
			RESQML2_NS::WellboreInterpretation* interp,
			const std::string& guid, const std::string& title, 
			RESQML2_NS::WellboreTrajectoryRepresentation* traj,
			double seismicReferenceDatum,
			double weatheringVelocity,
			EML2_NS::AbstractLocal3dCrs* crs);

		/**
		 * Creates a wellbore marker frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp of @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore marker frame representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore marker frame representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore marker frame. It cannot
		 * 						be null.
		 *
		 * @returns	A pointer to the new wellbore marker frame representation.
		 */
		RESQML2_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a wellbore marker within a given wellbore marker frame representation.
		 *
		 * @exception	std::invalid_argument	If <tt>wellboreMarkerFrame == nullptr</tt>.
		 *
		 * @param [in]	wellboreMarkerFrame	The wellbore marker frame representation where to push back
		 * 									the wellbore marker.
		 * @param 	  	guid			   	The guid to set to the wellbore marker. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title			   	The title to set to the wellbore marker. If empty then
		 * 									\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new wellbore marker.
		 */
		RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title);

		/**
		 * @brief	Creates a wellbore marker within a given wellbore marker frame representation.
		 *
		 * @exception	std::invalid_argument	If <tt>wellboreMarkerFrame == nullptr</tt>.
		 *
		 * @param [in]	wellboreMarkerFrame 	The wellbore marker frame representation where to push
		 * 										back the wellbore marker.
		 * @param 	  	guid					The guid to set to the wellbore marker. If empty then a
		 * 										new guid will be generated.
		 * @param 	  	title					The title to set to the wellbore marker. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	geologicBoundaryKind	The geologic boundary kind.
		 *
		 * @returns	A pointer to the new wellbore marker.
		 */
		RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);

		/**
		 * @brief	Creates a blocked wellbore representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>traj == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the blocked wellbore representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the blocked wellbore representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this blocked wellbore representation.
		 * 						It cannot be null.
		 *
		 * @returns	A pointer to the new blocked wellbore representation.
		 */
		RESQML2_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_NS::WellboreInterpretation* interp,
			const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a representation set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createRepresentationSetRepresentation} if no interpretation
		 * 						is associated to this representation.
		 * @param 	  	guid  	The guid to set to the representation set representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the representation set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new representation set representation.
		 */
		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			RESQML2_NS::AbstractOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a representation set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the representation set representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title	The title to set to the representation set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new representation set representation.
		 */
		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a non sealed surface framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the non sealed surface framework representation. If
		 * 						empty then a new guid will be generated.
		 * @param 	  	title 	The title to set to the non sealed surface framework representation. If
		 * 						empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new non sealed surface framework representation.
		 */
		RESQML2_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a sealed surface framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the sealed surface framework representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the sealed surface framework representation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new sealed surface framework representation.
		 */
		RESQML2_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a sealed volume framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>ssf == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the sealed volume framework representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the sealed volume framework representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param [in]	ssf   	The sealed surface framework that refers this sealed volume framework. It
		 * 						cannot be null.
		 *
		 * @returns	A pointer to the new sealed volume framework representation.
		 */
		RESQML2_NS::SealedVolumeFrameworkRepresentation* createSealedVolumeFrameworkRepresentation(
			RESQML2_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf);

		/**
		 * Creates a partial ijk grid representation into this repository
		 *
		 * @param 	guid 	The guid to set to the sealed volume framework representation. If empty
		 * 					then a new guid will be generated.
		 * @param 	title	The title to set to the sealed volume framework representation.
		 *
		 * @returns	A pointer to the new partial ijk grid representation.
		 */
		RESQML2_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string& guid, const std::string& title);

		/**
		 * Creates a partial truncated ijk grid representation into this repository
		 *
		 * @param 	guid 	The guid to set to the sealed volume framework representation.
		 * @param 	title	The title to set to the sealed volume framework representation.
		 *
		 * @returns	A pointer to the new partial truncated ijk grid representation.
		 */
		RESQML2_NS::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string& guid, const std::string& title);

		/**
		 * @brief	Creates an ijk grid explicit representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param		guid  	The guid to set to the ijk grid explicit representation. If empty then a new
		 * 						guid will be generated.
		 * @param		title 	The title to set to the ijk grid explicit representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param		iCount	Count of cells in the I direction in the grid.
		 * @param 		jCount	Count of cells in the J direction in the grid.
		 * @param		kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid explicit representation.
		 */
		RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an ijk grid explicit representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid explicit representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid explicit representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid explicit representation.
		 */
		RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an ijk grid parametric representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param		guid  	The guid to set to the ijk grid parametric representation. If empty then a
		 * 						new guid will be generated.
		 * @param		title 	The title to set to the ijk grid parametric representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param		iCount	Count of cells in the I direction in the grid.
		 * @param		jCount	Count of cells in the J direction in the grid.
		 * @param		kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid parametric representation.
		 */
		RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an ijk grid parametric representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid parametric representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid parametric representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid parametric representation.
		 */
		RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an ijk grid lattice representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid  	The guid to set to the ijk grid lattice representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title 	The title to set to the ijk grid lattice representation. If empty then
		 * 					\"unknown\" title will be set.
		 * @param 	iCount	Count of cells in the I direction in the grid.
		 * @param 	jCount	Count of cells in the J direction in the grid.
		 * @param 	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid lattice representation.
		 */
		RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount);

		/**
		 * @brief	Creates an ijk grid lattice representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid lattice representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid lattice representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid lattice representation.
		 */
		RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount);

		/**
		 * @brief	Creates an ijk grid with no geometry representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param		guid  	The guid to set to the ijk grid with no geometry representation. If empty
		 * 						then a new guid will be generated.
		 * @param		title 	The title to set to the ijk grid with no geometry representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param		iCount	Count of cells in the I direction in the grid.
		 * @param		jCount	Count of cells in the J direction in the grid.
		 * @param		kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid with no geometry representation.
		 */
		RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an ijk grid with no geometry representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid with no geometry representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid with no geometry representation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 * @param		kGaps	(Optional) Boolean array of length KCellCount-1.
		 *						TRUE if there is a gap after the corresponding layer.
		 *						Won't be freed by FESAPI.
		 * @param [in]	proxy	(Optional) The HDF proxy for writing the @p enabledCells
		 * 						values. If @c nullptr (default), then the default HDF proxy will be
		 * 						used.
		 *
		 * @returns	A pointer to the new ijk grid with no geometry representation.
		 */
		RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			uint32_t iCount, uint32_t jCount, uint32_t kCount, bool* kGaps = nullptr, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * @brief	Creates an unstructured grid representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid	 	The guid to set to the unstructured grid representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	title	 	The title to set to the unstructured grid representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	cellCount	Number of cells in the grid.
		 *
		 * @returns	A pointer to the new unstructured grid representation.
		 */
		RESQML2_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(const std::string& guid, const std::string& title,
			uint64_t cellCount);

		/**
		 * @brief	Creates a sub-representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the sub-representation. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the sub-representation. If empty then \"unknown\" title
		 * 					will be set.
		 * @param 	defaultElementKind	The indexable element which will be by default used for selecting the subrepresentation of a supporting representation.
		 *
		 * @returns	A pointer to the new sub-representation.
		 */
		RESQML2_NS::SubRepresentation* createSubRepresentation(
			const std::string & guid, const std::string & title, gsoap_eml2_3::eml23__IndexableElement elementKind);

		/**
		 * @brief	Creates a sub-representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createSubRepresentation} if no interpretation is associated
		 * 						to this representation.
		 * @param 	  	guid  	The guid to set to the sub-representation. If empty then a new guid will
		 * 						be generated.
		 * @param 	  	title 	The title to set to the sub-representation. If empty then \"unknown\"
		 * 						title will be set.
		 * @param 		defaultElementKind	The indexable element which will be by default used for selecting the subrepresentation of a supporting representation.
		 *
		 * @returns	A pointer to the new sub-representation.
		 */
		RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::eml23__IndexableElement elementKind);

		/**
		 * @brief	Creates a grid connection set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the grid connection set representation. If empty then a
		 * 					new guid will be generated.
		 * @param 	title	The title to set to the grid connection set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new grid connection set representation.
		 */
		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a grid connection set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createGridConnectionSetRepresentation} if no interpretation
		 * 						is associated to this representation.
		 * @param 	  	guid  	The guid to set to the grid connection set representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the grid connection set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new grid connection set representation.
		 */
		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a streamlines feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 		The guid to set to the streamlines feature. If empty then a new guid will be
		 * 						generated.
		 * @param 	title		The title to set to the streamlines feature. If empty then \"unknown\" title
		 * 						will be set.
		 * @param 	timeIndex	The time index in the time series of the this streamlines feature.
		 * @param 	timeSeries	The time series where the time index of this streamlines feature is given.
		 *
		 * @returns	A pointer to the new wellbore feature.
		 */
		RESQML2_NS::StreamlinesFeature* createStreamlinesFeature(const std::string & guid, const std::string & title, uint64_t timeIndex, EML2_NS::TimeSeries* timeSeries);

		/**
		 * @brief	Creates a streamlines representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param [in]	interp		The represented interpretation. It cannot be null.
		 * @param [in]	guid 		The guid to set to the streamlines representation. If empty then a new guid will be
		 * 							generated.
		 * @param [in]	title		The title to set to the streamlines representation. If empty then \"unknown\" title
		 * 							will be set.
		 * @param [in]	lineCount	The count of line in this representation
		 *
		 * @returns	A pointer to the new wellbore feature.
		 */
		RESQML2_NS::StreamlinesRepresentation* createStreamlinesRepresentation(RESQML2_NS::GenericFeatureInterpretation* interp, const std::string & guid, const std::string & title, uint64_t lineCount);

		//************* PROPERTIES ***********

		/**
		 * @brief	Creates a time series into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the time series. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the time series. If empty then \"unknown\" title will be
		 * 					set.
		 *
		 * @returns	A pointer to the new time series.
		 */
		EML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a double table lookup into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the double table lookup. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the double table lookup. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new double table lookup.
		 */
		RESQML2_0_1_NS::DoubleTableLookup* createDoubleTableLookup(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a facies table into this repository
		 *			A facies table is a column based table which already has got two column headers :
		 *				column 0 is a key column (ordinal number prop kind) and must contain integer
		 *				column 1 is a normal column (facies prop kind) and must contain string
		 *			You need to set the values of the column after creation
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the facies table. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the facies table. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new facies table.
		 */
		EML2_NS::ColumnBasedTable* createFaciesTable(const std::string & guid, const std::string & title);

		/**
		 * Creates a RESQML2.0.1 only property kind into this repository
		 *
		 * @param 	guid						 	The guid to set to the property kind. If empty then a
		 * 											new guid will be generated.
		 * @param 	title						 	The title to set to the property kind. If empty then
		 * 											\"unknown\" title will be set.
		 * @param 	namingSystem				 	The name of the dictionary within which the property
		 * 											is unique. This also defines the name of the
		 * 											controlling authority. Use a URN of the form <tt>urn:x-
		 * 											resqml:domainOrEmail:dictionaryName</tt>.
		 * @param 	uom							 	The property kind unit of measure taken from the
		 * 											standard RESQML units of measure catalog.
		 * @param 	parentEnergisticsPropertyKind	The parent property kind taken from the standard set
		 * 											of RESQML property kinds.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * @brief	Creates a RESQML2.0.1 only property kind into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>parentPropType == nullptr</tt>.
		 *
		 * @param 	  	guid		  	The guid to set to the property kind. If empty then a new guid
		 * 								will be generated.
		 * @param 	  	title		  	The title to set to the property kind. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	namingSystem  	The name of the dictionary within which the property is unique.
		 * 								This also defines the name of the controlling authority. Use a
		 * 								URN of the form \"urn:x- resqml:domainOrEmail:dictionaryName\".
		 * @param 	  	uom			  	The property kind unit of measure taken from the standard RESQML
		 * 								units of measure catalog.
		 * @param [in]	parentPropType	The parent property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * Creates a RESQML2.0.1 only property kind into this repository.
		 *
		 * @param 	guid						 	The guid to set to the property kind. If empty then a
		 * 											new guid will be generated.
		 * @param 	title						 	The title to set to the property kind. If empty then
		 * 											\"unknown\" title will be set.
		 * @param 	namingSystem				 	The name of the dictionary within which the property
		 * 											is unique. This also defines the name of the
		 * 											controlling authority. Use a URN of the form \"urn:x-
		 * 											resqml:domainOrEmail:dictionaryName\".
		 * @param 	nonStandardUom				 	The property kind unit of measure.
		 * @param 	parentEnergisticsPropertyKind	The parent property kind taken from the standard set
		 * 											of RESQML property kinds.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * Creates a RESQML2.0.1 only property kind into this repository
		 *
		 * @param 	  	guid		  	The guid to set to the property kind. If empty then a new guid
		 * 								will be generated.
		 * @param 	  	title		  	The title to set to the property kind. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	namingSystem  	The name of the dictionary within which the property is unique.
		 * 								This also defines the name of the controlling authority. Use a
		 * 								URN of the form \"urn:x- resqml:domainOrEmail:dictionaryName\".
		 * @param 	  	nonStandardUom	The property kind unit of measure.
		 * @param [in]	parentPropType	The parent property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * @brief	Creates a property kind starting with EML2.1 version into this repository.
		 *			Don't use it at all if you want a full RESQML2.0.1 EPC!!! Use other same name methods instead please.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	  	guid			  	The guid to set to the property kind. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title			  	The title to set to the property kind. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	  	quantityClass	  	A reference to the name of a quantity class in the
		 * 									Energistics units of measure dictionary.
		 * @param 	  	isAbstract		  	(Optional) Indicates whether the property kind should be used
		 * 									as a real (default) property or not.
		 * @param [in]	parentPropertyKind	(Optional) If non-null, the parent property kind. If null, a
		 * 									default partial parent property kind will be created.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		EML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, EML2_NS::PropertyKind* parentPropertyKind = nullptr);

		/**
		 * @brief	Creates a property set into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If, in a RESQML v2.0 context, @p timeSetKind is single
		 * 										time series.
		 *
		 * @param 	guid				   	The guid to set to the property set. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				   	The title to set to the property set. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	hasMultipleRealizations	True if the set contains properties with defined realization
		 * 									indices, false if not.
		 * @param 	hasSinglePropertyKind  	True if the set contains only property values associated with
		 * 									a single property kind, false if not.
		 * @param 	timeSetKind			   	The time relationship that share the properties of this set,
		 * 									if any.
		 *
		 * @returns	A pointer to the new property set.
		 */
		RESQML2_0_1_NS::PropertySet* createPropertySet(const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind);

		/**
		 * Creates a comment property (which is of a well known Energistics property kind) into this
		 * repository.
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns	A pointer to the new comment property.
		 */
		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a comment property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new comment property.
		 */
		RESQML2_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a continuous property (which is of well known Energistics unit of measure and
		 * property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	uom					   	The property unit of measure taken from the standard
		 * 										Energistics units of measure catalog. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 * @param 	  	dimensions			   	The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a continuous property (which is of a well known unit of measure and a local property
		 * kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param 	  	uom			  	The property unit of measure taken from the standard Energistics
		 * 								units of measure catalog. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 * @param 	  	dimensions	   	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropType,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a continuous property (which is of a local unit of measure and a well known property
		 * kind) into this repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	nonStandardUom		   	The property unit of measure. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 * @param 	  	dimensions	   			The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, std::string nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a continuous property (which is of local unit of measure and property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param 	  	nonStandardUom	The property unit of measure. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 * @param 	  	dimensions	   			The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropType,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a discrete property (which is of a well known Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 * @param 	  	dimensions	   			The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new discrete property.
		 */
		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a discrete property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 * @param 	  	dimensions	   	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new discrete property.
		 */
		RESQML2_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a categorical property (which is of a standard Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param [in]	strLookup			   	The string lookup which defines the possible string
		 * 										values and their keys.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 * @param 	  	dimensions	   			The dimensions of each value of this property. If this parameter
		 *										is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns A pointer to new categorical property.
		 */
		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::ColumnBasedTable* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a categorical property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	strLookup	  	The string lookup which defines the possible string values and
		 * 								their keys. It cannot be null.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 * @param 	  	dimensions	  	The dimensions of each value of this property. If this parameter
		 *								is empty, then it is assumed this property is a scalar one.
		 *
		 * @returns	A pointer to the new categorical property.
		 */
		RESQML2_NS::DiscreteProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::ColumnBasedTable* strLookup, EML2_NS::PropertyKind * localPropType,
			std::vector<int> dimensions = std::vector<int>());

		/**
		 * Creates a 2.0.1 only points property (which is of a well known RESQML 2.0.1 property kind) into this
		 * repository. Only a single point per indexable element is supported.
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary. length is a good candidate
		 *
		 * @returns	A pointer to the new points property.
		 */
		RESQML2_0_1_NS::PointsProperty* createPointsProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::AbstractLocal3dCrs* localCrs,
			gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a points property (which is of a property kind) into this repository.
		 * Only a single point per indexable element is supported.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document. It cannot be null.
		 *
		 * @returns	A pointer to the new points property.
		 */
		RESQML2_NS::PointsProperty* createPointsProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::AbstractLocal3dCrs* localCrs,
			EML2_NS::PropertyKind * localPropType);

		//************* ACTIVITIES ***********

		/**
		 * @brief	Creates an activity template into this repository
		 *
		 * @exception	std::invalid_argument	If the default EML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the activity template. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the activity template. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new activity template.
		 */
		EML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an activity into this repository
		 *
		 * @exception	std::invalid_argument	If the default EML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>activityTemplate == nullptr</tt>.
		 *
		 * @param [in]	activityTemplate	The activity template on which this activity is based on.
		 * @param 	  	guid				The guid to set to the activity. If empty then a new guid
		 * 									will be generated.
		 * @param 	  	title				The title to set to the activity. If empty then \"unknown\"
		 * 									title will be set.
		 *
		 * @returns	A pointer to the new activity.
		 */
		EML2_NS::Activity* createActivity(EML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		//*************** WITSML *************
/*
		WITSML2_1_NS::ToolErrorModel* createToolErrorModel(
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__MisalignmentMode misalignmentMode);

		WITSML2_1_NS::ToolErrorModelDictionary* createToolErrorModelDictionary(
			const std::string & guid,
			const std::string & title);

		WITSML2_1_NS::ErrorTerm* createErrorTerm(
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__ErrorPropagationMode propagationMode,
			WITSML2_1_NS::WeightingFunction* weightingFunction);

		WITSML2_1_NS::ErrorTermDictionary* createErrorTermDictionary(
			const std::string & guid,
			const std::string & title);

		WITSML2_1_NS::WeightingFunction* createWeightingFunction(
			const std::string & guid,
			const std::string & title,
			const std::string & depthFormula,
			const std::string & inclinationFormula,
			const std::string & azimuthFormula);

		WITSML2_1_NS::WeightingFunctionDictionary* createWeightingFunctionDictionary(
			const std::string & guid,
			const std::string & title);
*/
		/**
		 * Creates a well into this repository
		 *
		 * @param 	guid 	The guid to set to the well. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the well. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new well.
		 */
		WITSML2_NS::Well* createWell(const std::string & guid,
			const std::string & title);

		/**
		 * Creates a well into this repository
		 *
		 * @param 	guid		 	The guid to set to the well. If empty then a new guid will be
		 * 							generated.
		 * @param 	title		 	The title to set to the well. If empty then \"unknown\" title will be
		 * 							set.
		 * @param 	operator_	 	The operator company name.
		 * @param 	statusWell   	POSC well status.
		 * @param 	directionWell	POSC well direction. The direction of the flow of the fluids in a
		 * 							well facility (generally, injected or produced, or some combination).
		 *
		 * @returns	A pointer to the new well.
		 */
		WITSML2_NS::Well* createWell(const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml20__WellDirection directionWell
		);

		/**
		 * @brief	Creates a wellbore into this repository.
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	The well associated to this wellbore. It cannot be null.
		 * @param 	  	guid	  	The guid to set to the wellbore. If empty then a new guid will be
		 * 							generated.
		 * @param 	  	title	  	The title to set to the wellbore. If empty then \"unknown\" title
		 * 							will be set.
		 *
		 * @returns	A pointer to the new wellbore.
		 */
		WITSML2_NS::Wellbore* createWellbore(WITSML2_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a wellbore into this repository.
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	  	The well associated to this wellbore. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the wellbore. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the wellbore. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	statusWellbore	POSC wellbore status.
		 * @param 	  	isActive	  	True if is active, false if not.
		 * @param 	  	achievedTD	  	True indicates that the wellbore has achieved total depth. That
		 * 								is, drilling has completed. False indicates otherwise.  
		 *
		 * @returns	A pointer to the new wellbore.
		 */
		WITSML2_NS::Wellbore* createWellbore(WITSML2_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		/**
		 * @brief	Creates a well completion into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	The well associated to this well completion. It cannot be null.
		 * @param 	  	guid	  	The guid to set to the well completion. If empty then a new guid will
		 * 							be generated.
		 * @param 	  	title	  	The title to set to the well completion. If empty then \"unknown\"
		 * 							title will be set.
		 *
		 * @returns	A pointer to the new well completion.
		 */
		WITSML2_0_NS::WellCompletion* createWellCompletion(WITSML2_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates a wellbore completion into this repository
		 *
		 * @param [in]	witsmlWellbore	  	The wellbore associated to this wellbore completion. It
		 * 									cannot be null.
		 * @param [in]	wellCompletion	  	The well completion associated to this wellbore completion.
		 * 									It cannot be null.
		 * @param 	  	guid			  	The guid to set to the wellbore completion. If empty then a new guid will be
		 * 									generated.
		 * @param 	  	title			  	The title to set to the wellbore completion. If empty then \"unknown\" title
		 * 									will be set.
		 * @param 	  	wellCompletionName	Human-recognizable context for the well completion that
		 * 									contains the completion.
		 *
		 * @returns	A pointer to the new wellbore completion.
		 */
		WITSML2_0_NS::WellboreCompletion* createWellboreCompletion(WITSML2_NS::Wellbore* witsmlWellbore,
			WITSML2_0_NS::WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);

		/**
		 * @brief	Creates a wellbore geometry into this repository. It is used to capture information
		 * 			about the configuration of the permanently installed components in a wellbore
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this wellbore geometry. It cannot be
		 * 								null.
		 * @param 	  	guid		  	The guid to set to the geometry. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the geometry. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	channelStatus 	Describes the growing status of the wellbore geometry, whether
		 * 								active, inactive or closed.
		 *
		 * @returns	A pointer to the new wellbore geometry.
		 */
		WITSML2_0_NS::WellboreGeometry* createWellboreGeometry(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		/**
		 * @brief	Creates a wellbore trajectory into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this wellbore trajectory. It cannot be
		 * 								null.
		 * @param 	  	guid		  	The guid to set to the trajectory. If empty then a new guid will
		 * 								be generated.
		 * @param 	  	title		  	The title to set to the trajectory. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	channelStatus 	Describes the growing status of the trajectory, whether active,
		 * 								inactive or closed.
		 *
		 * @returns	A pointer to the new trajectory.
		 */
		WITSML2_NS::Trajectory* createTrajectory(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		/**
		 * @brief	Creates a wellbore log into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this log. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the log. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the log. If empty then \"unknown\" title will
		 * 								be set.
		 *
		 * @returns	A pointer to the new log.
		 */
		WITSML2_0_NS::Log* createLog(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates a channel set into this repository
		 *
		 * @param 	guid 	The guid to set to the channel set. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the channel set. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new channel set.
		 */
		WITSML2_0_NS::ChannelSet* createChannelSet(
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a channel into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>propertyKind == nullptr</tt>.
		 *
		 * @param [in]	propertyKind	  	The property kind associated to this channel. It cannot be
		 * 									null.
		 * @param 	  	guid			  	The guid to set to the channel. If empty then a new guid will
		 * 									be generated.
		 * @param 	  	title			  	The title to set to the channel. If empty then \"unknown\"
		 * 									title will be set.
		 * @param 	  	mnemonic		  	The mnemonic name to set to this channel.
		 * @param 	  	uom				  	The underlying unit of measure of the value.
		 * @param 	  	dataType		  	The underlying ETP data type of the value.
		 * @param 	  	growingStatus	  	The status of a channel with respect to creating new
		 * 									measurements.
		 * @param 	  	timeDepth		  	Use to indicate if this is a time or depth log.
		 * @param 	  	loggingCompanyName	Name of the logging company.
		 *
		 * @returns	A pointer to the new channel.
		 */
		WITSML2_0_NS::Channel* createChannel(EML2_NS::PropertyKind * propertyKind,
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

		/**
		 * @brief	Creates a WITSML2.0 Wellbore Marker into this repository
		 *
		 * @param 	  	guid		  	The guid to set to the marker. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the marker. If empty then \"unknown\" title will
		 * 								be set.
		 * @param 	  	md		  		The Measured Depth to set to this marker.
		 * @param 	  	mdUom			The underlying unit of measure of the MD value.
		 * @param 	  	mdDatum		  	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 *
		 * @returns	A pointer to the new Wellbore Marker.
		 */
		WITSML2_0_NS::WellboreMarker* createWellboreMarker(
			const std::string & guid, const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		/**
		 * @brief	Creates a WITSML2.0 Wellbore Marker into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this marker. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the marker. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the marker. If empty then \"unknown\" title will
		 * 								be set.
		 * @param 	  	md		  		The Measured Depth to set to this marker.
		 * @param 	  	mdUom			The underlying unit of measure of the MD value.
		 * @param 	  	mdDatum		  	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 *
		 * @returns	A pointer to the new Wellbore Marker.
		 */
		WITSML2_0_NS::WellboreMarker* createWellboreMarker(WITSML2_NS::Wellbore* witsmlWellbore,
			const std::string & guid, const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		//*************** PRODML *************

		/**
		 * Creates a fluid system into this repository
		 *
		 * @param 	guid			  	The guid to set to the fluid system. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			  	The title to set to the fluid system. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	temperatureValue  	The temperature value.
		 * @param 	temperatureUom	  	The temperature unit of measure.
		 * @param 	pressureValue	  	The pressure value.
		 * @param 	pressureUom		  	The pressure unit of measure.
		 * @param 	reservoirFluidKind	The kind of the reservoir fluid.
		 * @param 	gasOilRatio		  	The gas oil ratio.
		 * @param 	gasOilRatioUom	  	The gas oil ratio unit of measure.
		 *
		 * @returns	A pointer to the new fluid system.
		 */
		PRODML2_1_NS::FluidSystem* createFluidSystem(const std::string & guid,
			const std::string & title,
			double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * Creates a fluid system into this repository
		 *
		 * @param 	guid			  	The guid to set to the fluid system. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			  	The title to set to the fluid system. If empty then \"unknown\"
		 * 								title will be set.
		 * @param   referenceCondition	A wellknown couple of temperature-pressure.
		 * @param 	reservoirFluidKind	The kind of the reservoir fluid.
		 * @param 	gasOilRatio		  	The gas oil ratio.
		 * @param 	gasOilRatioUom	  	The gas oil ratio unit of measure.
		 *
		 * @returns	A pointer to the new fluid system.
		 */
		PRODML2_1_NS::FluidSystem* createFluidSystem(const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::eml22__ReferenceCondition referenceCondition,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * Creates a fluid characterization into this repository
		 *
		 * @param 	guid 	The guid to set to the fluid characterization. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the fluid characterization. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new fluid characterization.
		 */
		PRODML2_1_NS::FluidCharacterization* createFluidCharacterization(const std::string & guid, const std::string & title);

		/**
		 * Creates a time series data into this repository
		 *
		 * @param 	guid 	The guid to set to the time series data. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the time series data. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new time series data.
		 */
		PRODML2_1_NS::TimeSeriesData* createTimeSeriesData(const std::string & guid, const std::string & title);

		//************** EML2.3 ****************

		/**
		 * Creates a graphical information set into this repository
		 *
		 * @param 	guid 	The guid to set to the graphical information set. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the graphical information set. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new graphical information set.
		 */
		EML2_NS::GraphicalInformationSet* createGraphicalInformationSet(const std::string & guid, const std::string & title);

		/**
		 * Creates a discrete color map into this repository
		 *
		 * @param 	guid 	The guid to set to the discrete color map. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the discrete color map. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new discrete color map.
		 */
		RESQML2_NS::DiscreteColorMap* createDiscreteColorMap(const std::string& guid, const std::string& title);

		/**
		 * Creates a continuous color map into this repository
		 *
		 * @param 	guid			   	The guid to set to the continuous color map. If empty then a new
		 * 								guid will be generated.
		 * @param 	title			   	The title to set to the continuous color map. If empty then
		 * 								\"unknown\" title will be set.
		 * @param 	interpolationDomain	The interpolation domain (the color space).
		 * @param 	interpolationMethod	The interpolation method.
		 *
		 * @returns	A pointer to the new continuous color map.
		 */
		RESQML2_NS::ContinuousColorMap* createContinuousColorMap(const std::string& guid, const std::string& title,
			gsoap_eml2_3::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_3::resqml22__InterpolationMethod interpolationMethod);

		//***** STANDARD PROP KIND ***********

		/**
		 * Gets the property kind mapper if it was given at repository construction time
		 *
		 * @returns	The property kind mapper, or @c nullptr if no property kind mapper was given at
		 * 			repository construction time.
		 */
		RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const { return propertyKindMapper.get(); }

		//************************************/
		//************* WARNINGS *************/
		//************************************/

		/** Clears the warnings from the repository */
		void clearWarnings();

		/**
		 * Gets the repository warnings
		 *
		 * @returns	A vector of all repository warnings.
		 */
		const std::vector<std::string> & getWarnings() const;
	};
	
%typemap(javaimports) COMMON_NS::EpcDocument %{
import java.lang.AutoCloseable;
%}
%typemap(javainterfaces) COMMON_NS::EpcDocument "AutoCloseable"
%typemap(javacode) COMMON_NS::EpcDocument %{
  @Override
  public void close() {
	closeNativeResource();
    delete();
  }
%}
	class EpcDocument
	{
	public:

		/**
		 * Constructor
		 *
		 * @param 	fileName	Full pathname of the EPC document.
		 */
		EpcDocument(const std::string & fileName);

		/**
		 * Sets the EPC document file path which will be used for future serialization and
		 * deserialization. This method will add the standard @c .epc extension if it is not already
		 * present.
		 *
		 * @exception	std::invalid_argument	if the HDF5 file error handling cannot be disabled.
		 *
		 * @param 	fp	Full pathname of the EPC document.
		 */
		void setFilePath(const std::string & fp);

		/**
		 * Serializes the content of a data object repository into this EPC document. It also allows to
		 * optionally zip this EPC document.
		 *
		 * @param 	repo		A data object repository.
		 * @param 	useZip64	(Optional) True to zip the EPC document, else false (default).
		 */
		virtual void serializeFrom(const DataObjectRepository & repo, bool useZip64 = false);

		/**
		 * Deserializes this package (data objects and relationships) into a data object repository
		 *
		 * @param [in,out]	repo			   	A data object repository.
		 * @param 		  	hdfPermissionAccess	(Optional) The HDF5 file permission access. It is read
		 * 										only by default.
		 *
		 * @returns	An empty string if success otherwise the warning string.
		 */
		virtual std::string deserializeInto(DataObjectRepository & repo, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::openingMode::READ_ONLY);

// JAVA uses autocloseable and consequently cannot use a second "close" method
#ifdef SWIGJAVA
		%javamethodmodifiers close() "private";
		%rename(closeNativeResource) close();
#endif
		void close();

		/**
		 * Gets the absolute path of the directory where the EPC document is stored.
		 *
		 * @returns	The EPC document storage directory.
		 */
		std::string getStorageDirectory() const;

		/**
		 * Gets the name of the EPC document
		 *
		 * @returns	The name of the EPC document without the @c .epc extension.
		 */
		std::string getName() const;
		
		/**
		 * Sets or adds an extended core property
		 *
		 * @param 	key  	The key of the property.
		 * @param 	value	The value of the property.
		 */
		void setExtendedCoreProperty(const std::string & key, const std::string & value);/**
		 * Gets extended core property count.
		 *
		 * @returns	The count of extended core properties in this EPC document
		 */
		uint64_t getExtendedCorePropertyCount() const;

		/**
		 * Gets an extended core property value according to its key.
		 *
		 * @param 	key	The key of the property.
		 *
		 * @returns	An empty string if the extended core property does not exist. Or the extended core
		 * 			property value if it exists.
		 */
		std::string getExtendedCoreProperty(const std::string & key);

	};
	
	class EnumStringMapper
	{
	public :
		EnumStringMapper();

		/**
		 * Get the name of a RESQML2.0 property kind as a string based on the property kind enumerated
		 * value
		 *
		 * @param 	energisticsPropertyKind	A RESQML2.0 property kind.
		 *
		 * @returns	A string corresponding to @p energisticsPropertyKind if successful. The empty string
		 * 			if no correspondence is found.
		 */
		std::string getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind) const;

		/**
		 * Get the RESQML2.0 property kind enumerated value from the name of a property kind
		 *
		 * @param 	energisticsPropertyKindName	The name of a RESQML2.0 property kind.
		 *
		 * @returns	The RESQML2.0 property kind enumerated value corresponding to @p
		 * 			energisticsPropertyKindName if successful. The most abstract RESQML2.0 property kind
		 * 			enumerated value if no correspondence is found.
		 */
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		/**
		 * Get the name of a RESQML2.0 unit of measure as a string based on the unit of measure
		 * enumerated value
		 *
		 * @param 	energisticsUom	A RESQML2.0 unit of measure.
		 *
		 * @returns	A string corresponding to @p energisticsUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		std::string getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml20__ResqmlUom energisticsUom) const;

		/**
		 * Get the RESQML2.0 unit of measure enumerated value from the name of a unit of measure
		 *
		 * @param 	energisticsUomName	The name of a RESQML2.0 unit of measure.
		 *
		 * @returns	The RESQML2.0 unit of measure enumerated value corresponding to @p energisticsUomName
		 * 			if successful. The Euclidian (no unit of measure) RESQML2.0 unit of measure if no
		 * 			correspondence is found.
		 */
		gsoap_resqml2_0_1::resqml20__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		/**
		 * Get the name of a RESQML2.0 facet as a string based on the enumerated facet enumerated value
		 *
		 * @param 	facet	A RESQML2.0 facet.
		 *
		 * @returns	A string corresponding to @p facet if successful. The empty string if no
		 * 			correspondence is found.
		 */
		std::string getFacet(gsoap_resqml2_0_1::resqml20__Facet facet) const;

		/**
		 * Get the RESQML2.0 facet enumerated value from the name of a facet.
		 *
		 * @param 	facet	The name of a RESQML2.0 facet.
		 *
		 * @returns	The RESQML2.0 facet enumerated value corresponding to @p facet if successful. The @c
		 * 			what facet enumerated value if no correspendance is found.
		 */
		gsoap_resqml2_0_1::resqml20__Facet getFacet(const std::string & facet) const;

		/**
		 * Get the name of an EML2.1 length unit of measure as a string based on the unit of measure
		 * enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 length unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		std::string lengthUomToString(gsoap_eml2_1::eml21__LengthUom witsmlUom) const;

		/**
		 * Get the name of an EML2.1 vertical coordinate unit of measure as a string based on the unit
		 * of measure enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 vertical coordinate unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		std::string verticalCoordinateUomToString(gsoap_eml2_1::eml21__VerticalCoordinateUom witsmlUom) const;

		/**
		 * Get the name of an EML2.1 plane angle unit of measure as a string based on the unit of
		 * measure enumerated value
		 *
		 * @param 	witsmlUom	An EML2.1 plane angle unit of measure.
		 *
		 * @returns	A string corresponding to @p witsmlUom if successful. The empty string if no
		 * 			correspondence is found.
		 */
		std::string planeAngleUomToString(gsoap_eml2_1::eml21__PlaneAngleUom witsmlUom) const;
	};
}

