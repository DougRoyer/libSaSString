//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2019 Douglas Mark Royer, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO DOUGLAS MARK ROYER
// THIS CODE IS PROPERTY OF THE COPYRIGHT HOLDER AND IS NOT TO
// BE DIVULGED OR USED BY PARTIES WHO HAVE NOT RECEIVED WRITTEN
// AUTHORIZATION FROM THE OWNER.
//
// THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES
// COPYRIGHT LAW (TITLE 17 UNITED STATES CODE). UNAUTHORIZED REPRODUCTION
// AND/OR SALE MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES
// OF UP TO $100,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO
// BE SUBJECT TO CIVIL LIABILITY.
//
// THIS NOTICE AND THE ABOVE COPYRIGHT NOTICE MUST REMAIN IN ALL
// COPIES AND ANY DERIVED WORK.
//
// ALL OF THIS CODE IS ORIGINAL WORK BY THE COPYRIGHT HOLDER.
//
// THIS  DOCUMENT  AND  THE  INFORMATION  CONTAINED  HEREIN  IS
// PROVIDED  ON  AN "AS IS" BASIS AND DOUGLAS MARK ROYER
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,  INCLUDING  BUT
// NOT  LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN  WILL  NOT  INFRINGE  ANY  RIGHTS  OR   ANY   IMPLIED
// WARRANTIES  OF  MERCHANTABILITY  OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//

/**
 * @file String.hpp "<SaS/String/ROString.hpp>"
 * @ingroup STRING
 * String manipulation routines for C++
 */
#ifndef SOFTWARE_AND_SERVICES_LIBRARY_STRING_ROSTRING_HPP_
#define SOFTWARE_AND_SERVICES_LIBRARY_STRING_ROSTRING_HPP_

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include <string>
#include <SaS/String/String.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			class String;

			/**
			 * @class ROString ROString.hpp "<SaS/String/ROString.hpp>"
			 * Read-Only strings. This is an extension to String.
			 *
			 * A Rean-Only string can not be modified. One use is
			 * when the string is memory mapped from a disk file
			 * for a parser. And when the implememntation does not need to
			 * duplicate all of the strings in order to parse and
			 * use the input data.
			 */
			class ROString
				: public String,
				  public XdrSerialize<ROString> {

				public:

					/**
					 * Constructor - For 8-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const char * const Start, size_t Len = 0);

					/**
					 * Constructor - For 16-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const char16_t * const Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const char32_t * const Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const wchar_t * const Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const std::string & Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const std::u16string & Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const std::u32string & Start, size_t Len = 0);

					/**
					 * Constructor - For 32-bit strings.
					 *
					 * @param Start the pointer to the start of the string.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const std::wstring & Start, size_t Len = 0);

					/**
					 * Constructor - For String.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const String & Init, size_t Len = 0);

					/**
					 * Constructor - Copy Constructor.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const ROString & Init, size_t Len = 0);

					/**
					 * Constructor - Copy Constructor.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const_iterator & Init, size_t Len);

					/**
					 * Constructor - Copy Constructor.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(iterator & Init, size_t Len = 0);

					/**
					 * Constructor - Copy Constructor.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param It The position in the string to have as the start
					 * position.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const String & Init,
					         String::const_iterator & It,
					         size_t Len);


					/**
					 * Constructor - Copy Constructor.
					 *
					 * @param Init Wrap Init as ROString.
					 *
					 * @param It The position in the string to have as the start
					 * position.
					 *
					 * @param Len The number of character units to use.
					 */
					ROString(const ROString & Init,
					         String::const_iterator & It,
					         size_t Len);


					/**
					 * Create a ROString by mapping a file to memory.
					 *
					 * @param FileName The path to the file to be mapped.
					 *
					 * - The file will be opened with: open(FileName, O_RDONLY).
					 * - The file will be mmaped() with:
					 * mmap(...,MAP_PRIVATE, PROT_READ, ...)
					 *
					 * Use AtEOF(size_t Position), or AtEOF(const char * const Position)
					 * to find the end of the string.

					 *
					 * @param Last A reference to a pointer that will be
					 * updated to point to the last valid position in the
					 * string.
					 *
					 * @retun A new ROString object, or nullptr when FileName
					 * can not be mapped.
					 *
					 * On returning nullptr, errno from the system is preserved.
					 */
					ROString	*	NewFileMap(const char * const FileName,
					                           const char *& Last);

					/**
					 * ROString - Destructor
					 */
					virtual ~ROString();

					/**
					 * Read/Write the XDR object.
					 *
					 * @param xdrs An initialized XDR object.
					 *
					 * @return true if seralized. Returs false
					 * if xdrs is nullptr, or there is a serialization problem.
					 *
					 * @note
					 * You can not XDR_DECODE a ROString (because it is not
					 * writable).
					 */
					virtual bool_t          xdr(XDR * xdrs);

					/**
					 * Get the input character width of the input string.
					 */
					CharacterUnitWidth_e	Width() const;

					/**
					 * Get the ReadOnly 8-bit pointer. If not 8-bit data,
					 * gets nullptr.
					 *
					 * @param[out] Len The length of the string.
					 *
					 * @return The pointer to the 8-bit data, or nullptr
					 * when not 8-bit data.
					 * And Len is updated to indicated the length of the unterminated
					 * string result.
					 *
					 * @note
					 * ROString values are NOT terminated with a zero when
					 * they were initialized from NewFileMap(). So use
					 * the String::iterator<char> objects with them, or track length
					 * yourself.
					 *
					 * @note
					 * -The String::Get8() method returns an unterminated ROString.
					 * -The ROString::Get8(Len) method returns an unterminated ROString
					 * and provides the length.
					 */
					const char	*	Get8(size_t & Len) const;

					/**
					 * Get the ReadOnly 16-bit pointer. If not 16-bit data,
					 * gets nullptr.
					 *
					 * @param[out] Len The length of the string.
					 *
					 * @return The pointer to the 16-bit data, or nullptr
					 * when not 16-bit data.
					 * And Len is updated to indicated the length of the unterminated
					 * string result.
					 *
					 * @note
					 * ROString values are NOT terminated with a zero when
					 * they were initialized from NewFileMap(). So use
					 * the String::iterator<char16_t> objects with them, or track length
					 * yourself.
					 *
					 * @note
					 * -The String::Get16() method returns an unterminated ROString.
					 * -The ROString::Get16(Len) method returns an unterminated ROString
					 * and provides the length.
					 */
					const char16_t	*	Get16(size_t & Len) const;

					/**
					 * Get the ReadOnly 32-bit pointer. If not 32-bit data,
					 * gets nullptr.
					 *
					 * @param[out] Len The length of the string.
					 *
					 * @return The pointer to the 32-bit data, or nullptr
					 * when not 32-bit data.
					 * And Len is updated to indicated the length of the unterminated
					 * string result.
					 *
					 * @note
					 * ROString values are NOT terminated with a zero when
					 * they were initialized from NewFileMap(). So use
					 * the String::iterator<char32_t> objects with them, or track length
					 * yourself.
					 *
					 * @note
					 * -The String::Get32() method returns an unterminated ROString.
					 * -The ROString::Get32(Len) method returns an unterminated ROString
					 * and provides the length.
					 */
					const char32_t	*	Get32(size_t & Len) const;

					/**
					 * Get the ReadOnly wchar_t pointer. If not wchar_t data,
					 * gets nullptr.
					 *
					 * @param[out] Len The length of the string.
					 *
					 * @return The pointer to the wchar_t data, or nullptr
					 * when not wchar_t data.
					 * And Len is updated to indicated the length of the unterminated
					 * string result.
					 *
					 * @note
					 * ROString values are NOT terminated with a zero when
					 * they were initialized from NewFileMap(). So use
					 * the String::iterator<wchar_t> objects with them, or track length
					 * yourself.
					 *
					 * @note
					 * -The String::GetW() method returns an unterminated ROString.
					 * -The ROString::GetW(Len) method returns an unterminated ROString
					 * and provides the length.
					 */
					const wchar_t	*	GetW(size_t & Len) const;

				private:

					/**
					 * Returns an iterator to the first character.
					 *
					 * @return An iterator the the start of the string.
					 *
					 * @note Not possible with a ROString.
					 */
					iterator				&			begin();

					/**
					 * Returns an iterator to the first character.
					 *
					 * @return An iterator the the start of the string.
					 *
					 * @note Not possible with a ROString.
					 */
					iterator				&			rbegin();

					/**
					 * Returns an iterator to the end of the characters.
					 *
					 * @return An iterator the the end of the string.
					 *
					 * @note Not possible with a ROString.
					 */
					iterator				&			end();

					/**
					 * Returns an iterator to the end of the characters.
					 *
					 * @return An iterator the the end of the string.
					 *
					 * @note Not possible with a ROString.
					 */
					iterator				&			rend();

			};

		}
	}
}

extern "C" {
	using namespace SoftwareAndServices::Library::Common;

	/**
	 * Read/Write the String in XDR format.
	 *
	 * @param xdrs An initialized XDR object.
	 * @note You can NOT XDR_DECODE an ROString.
	 * You MUST decode it into a String with xdr_String().
	 *
	 * @param Pointer to the String object to be written.
	 *
	 * @return true when encoded. All attempts to XDR_DECODE a ROString
	 * will return false. Use xdr_String() to XDR decode
	 * a ROString.
	 */
	bool_t		xdr_ROString(XDR * xdrs,
	                         ROString * Pointer);
}

#endif // SOFTWARE_AND_SERVICES_LIBRARY_STRING_ROSTRING_HPP_
