//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2015,2019 Software and Services LLC, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO SOFTWARE AND SERVICES LLC.
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
// THIS DOCUMENT AND THE INFORMATION CONTAINED HEREIN IS
// PROVIDED ON AN "AS IS" BASIS AND SOFTWARE AND SERVICES LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//
/**
 * @file StringCompareOperator.hpp
 * @ingroup IO
 * Compares c-string (char*).
 * Used as a method/class for std searching. (_Object->find(...)).
 */

#ifndef _SOFTWARE_AND_SERVICES_LIBRARY_LIBSASSTRING_STRINGCMPOPERATOR_HPP_
#define _SOFTWARE_AND_SERVICES_LIBRARY_LIBSASSTRING_STRINGCMPOPERATOR_HPP_

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include <SaS/Common/osver.h>
#include <SaS/Common/instance.hpp>
#include <SaS/String/String.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			/**
			 * @class CStringCompareOperator
			 * Compares c-string (char*).
			 * Used as a method/class for std searching. (_Object->find(...)).
			 *
			 * Simple Example:
			 *
			 * @verbatim
			 * std::map<const char *, const char *, CStringCompareOperator> var;
			 *
			 * std::map<const char *, const char *, CStringCompareOperator>::iterator it;
			 * var.insert(std::make_pair("Key1", "Value1");
			 * var.insert(std::make_pair("Key2", "Value2");
			 *
			 * it = std::find(var.begin(), var.end(), "Key1");
			 * if (it != var.end()) {
			 *	// FOUND!
			 * }
			 *
			 * std::map<const String *, const String *, StringCompareOperator> var2;
			 *
			 * std::map<const String *, const String *, StringCompareOperator>::iterator it2;
			 *
			 * String		Key1 = "Key1";
			 * String		Key2 = "Key2":
			 *
			 * String		Value1 = "Value1";
			 * String		Value2 = "Value2";

			 * var.insert(std::make_pair(&Key1, &Value1);
			 * var.insert(std::make_pair(&Key2, &Value2);
			 *
			 * it2 = std::find(var2.begin(), var2.end(), &Key1);
			 * if (it2 != var2.end()) {
			 *	// FOUND!
			 * }
			 *
			 * @endverbatim
			 */
			class CStringCompareOperator {

				public:

					/**
					 * C-String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					* @return true if One < Two.
					*/
					bool		operator()(const char * const One,
					                       const char * const Two) const;

			};

			/**
			 * @class StringCompareOperator
			 * Compares String.
			 * Used as a method/class for std searching. (_Object->find(...)).
			 */
			class StringCompareOperator {

				public:

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const String * const One,
					                       const wchar_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const ROString * const One,
					                       const wchar_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char * const One,
					                       const wchar_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char16_t * const One,
					                       const wchar_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const char32_t * const One,
					                       const wchar_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const String * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const ROString * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const char * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const char16_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const char32_t * const Two) const;

					/**
					 * String compare operator.
					 *
					 * @param One The first string to compare.
					 *
					 * @param Two The second string to compare.
					 *
					 * @return true if One < Two.
					 */
					bool		operator()(const wchar_t * const One,
					                       const wchar_t * const Two) const;


			};
		}
	}
}
#endif // _SOFTWARE_AND_SERVICES_LIBRARY_LIBSASSTRING_STRINGCMPOPERATOR_HPP_
