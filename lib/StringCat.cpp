//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2019 Software and Services LLC, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO Software and Services LLC.
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
// THIS	DOCUMENT AND THE INFORMATION CONTAINED HEREIN IS
// PROVIDED ON AN "AS IS" BASIS AND Software and Services LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,	INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES
// OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// THIS SOURCE CODE IS UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//

#include <SaS/String/CopyRightNotice.h>
#include <SaS/String/StringCache.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {
			char	*
			String::strcat8(char * ToString,
			                const char * const FromString)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					Results = ::strcat(ToString, FromString);
				}

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const char16_t * const FromString)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char	*	OutStr = nullptr;

					if (String::Charset16To8(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						Results = ::strcat(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const char32_t * const FromString)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char	*	OutStr = nullptr;

					if (String::Charset32To8(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						Results = ::strcat(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const wchar_t * const FromString)
			{
				char	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				Results = strcat8(ToString, (char16_t *)FromString);
#elif __SIZEOF_WCHAR_T__ == 4
				Results = strcat8(ToString, (char32_t *)FromString);
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const std::string & FromString)
			{
				char	*	Results = strcat8(ToString, FromString.c_str());

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const std::u16string & FromString)
			{
				char	*	Results = strcat8(ToString, FromString.c_str());

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const std::u32string & FromString)
			{
				char	*	Results = strcat8(ToString, FromString.c_str());

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const std::wstring & FromString)
			{
				char	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				Results = strcat8(ToString, (char16_t *)FromString.c_str());
#elif __SIZEOF_WCHAR_T__ == 4
				Results = strcat8(ToString, (char32_t *)FromString.c_str());
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char	*
			String::strcat8(char * ToString,
			                const String & FromString)
			{
				char	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strcat8(ToString, FromString.Get8());

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strcat8(ToString, FromString.cbegin().str8());
							break;

						case Is16Bit_t:
							strcat8(ToString, FromString.cbegin().str16());
							break;

						case Is32Bit_t:
							strcat8(ToString, FromString.cbegin().str32());
							break;

						case IsWBit_t:
							strcat8(ToString, FromString.cbegin().strW());
							break;

					}
				}

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const char * const FromString)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::Charset8To16(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcat16(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const char16_t * const FromString)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(char16_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const char32_t * const FromString)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::Charset32To16(nullptr,
					                          FromString,
					                          nullptr,
					                          OutStr)) {
						strcat16(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const wchar_t * const FromString)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcat16(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const std::string & FromString)
			{
				char16_t *	Results = ToString;

				strcat16(ToString, FromString.c_str());

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const std::u16string & FromString)
			{
				char16_t *	Results = ToString;

				strcat16(ToString, FromString.c_str());

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const std::u32string & FromString)
			{
				char16_t *	Results = ToString;

				strcat16(ToString, FromString.c_str());

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const std::wstring & FromString)
			{
				char16_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strcat16(ToString, (char16_t *)FromString.c_str());
#elif __SIZEOF_WCHAR_T__ == 4
				strcat16(ToString, (char32_t *)FromString.c_str());
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char16_t	*
			String::strcat16(char16_t * ToString,
			                 const String & FromString)
			{
				char16_t *	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strcat16(ToString, FromString.Get16());

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strcat16(ToString, FromString.cbegin().str8());
							break;

						case Is16Bit_t:
							strcat16(ToString, FromString.cbegin().str16());
							break;

						case Is32Bit_t:
							strcat16(ToString, FromString.cbegin().str32());
							break;

						case IsWBit_t:
							strcat16(ToString, FromString.cbegin().strW());
							break;

					}
				}

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const char * const FromString)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::Charset8To32(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcat32(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const char16_t * const FromString)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::Charset16To32(nullptr,
					                          FromString,
					                          nullptr,
					                          OutStr)) {
						strcat32(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const char32_t * const FromString)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(char32_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const wchar_t * const FromString)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcat32(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const std::string & FromString)
			{
				char32_t	*	Results = ToString;

				strcat32(ToString, FromString.c_str());

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const std::u16string & FromString)
			{
				char32_t	*	Results = ToString;

				strcat32(ToString, FromString.c_str());

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const std::u32string & FromString)
			{
				char32_t	*	Results = ToString;

				strcat32(ToString, FromString.c_str());

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const std::wstring & FromString)
			{
				char32_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strcat32(ToString, (char16_t *)FromString.c_str());
#elif __SIZEOF_WCHAR_T__ == 4
				strcat32(ToString, (char32_t *)FromString.c_str());
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char32_t	*
			String::strcat32(char32_t * ToString,
			                 const String & FromString)
			{
				char32_t	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strcat32(ToString, FromString.Get32());

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strcat32(ToString, FromString.cbegin().str8());
							break;

						case Is16Bit_t:
							strcat32(ToString, FromString.cbegin().str16());
							break;

						case Is32Bit_t:
							strcat32(ToString, FromString.cbegin().str32());
							break;

						case IsWBit_t:
							strcat32(ToString, FromString.cbegin().strW());
							break;

					}
				}

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const char * const FromString)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset8ToW(nullptr,
					                        FromString,
					                        nullptr,
					                        OutStr)) {
						strcatW(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const char16_t * const FromString)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset16ToW(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcatW(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const char32_t * const FromString)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset32ToW(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strcatW(ToString, OutStr);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const wchar_t * const FromString)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(wchar_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const std::string & FromString)
			{
				wchar_t	*	Results = ToString;

				strcatW(ToString, FromString.c_str());

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const std::u16string & FromString)
			{
				wchar_t	*	Results = ToString;

				strcatW(ToString, FromString.c_str());

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const std::u32string & FromString)
			{
				wchar_t	*	Results = ToString;

				strcatW(ToString, FromString.c_str());

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const std::wstring & FromString)
			{
				wchar_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strcat16((char16_t *)ToString,
				         (char16_t *)FromString.c_str());
#elif __SIZEOF_WCHAR_T__ == 4
				strcat32((char32_t *)ToString,
				         (char32_t *)FromString.c_str());
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			wchar_t	*
			String::strcatW(wchar_t * ToString,
			                const String & FromString)
			{
				wchar_t	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strcatW(ToString, FromString.Get32());

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strcatW(ToString, FromString.cbegin().str8());
							break;

						case Is16Bit_t:
							strcatW(ToString, FromString.cbegin().str16());
							break;

						case Is32Bit_t:
							strcatW(ToString, FromString.cbegin().str32());
							break;

						case IsWBit_t:
							strcatW(ToString, FromString.cbegin().strW());
							break;

					}
				}

				return (Results);
			}

			//
			char	*
			String::strncat8(char * ToString,
			                 const char * const FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					::strncat(ToString, FromString, Len);
				}

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const char16_t * const FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char	*	OutStr = nullptr;

					if (String::Charset16To8(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const char32_t * const FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char	*	OutStr = nullptr;

					if (String::Charset32To8(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const wchar_t * const FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char	*	OutStr = nullptr;

					if (String::CharsetWTo8(nullptr,
					                        FromString,
					                        nullptr,
					                        OutStr)) {
						strncat(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const std::string & FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				strncat8(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const std::u16string & FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				strncat8(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const std::u32string & FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				strncat8(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const std::wstring & FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strncat8(ToString, (char16_t *)FromString.c_str(), Len);
#elif __SIZEOF_WCHAR_T__ == 4
				strncat8(ToString, (char32_t *)FromString.c_str(), Len);
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char	*
			String::strncat8(char * ToString,
			                 const String & FromString,
			                 size_t Len)
			{
				char	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strncat8(ToString, FromString.Get8(), Len);

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strncat8(ToString, FromString.cbegin().str8(), Len);
							break;

						case Is16Bit_t:
							strncat8(ToString, FromString.cbegin().str16(), Len);
							break;

						case Is32Bit_t:
							strncat8(ToString, FromString.cbegin().str32(), Len);
							break;

						case IsWBit_t:
							strncat8(ToString, FromString.cbegin().strW(), Len);
							break;

					}
				}

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const char * const FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::Charset8To16(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat16(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const char16_t * const FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					if (Len2 > Len) {
						Len2 = Len;
					}

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(char16_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const char32_t * const FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::Charset32To16(nullptr,
					                          FromString,
					                          nullptr,
					                          OutStr)) {
						strncat16(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const wchar_t * const FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char16_t	*	OutStr = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat16(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const std::string & FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				strncat16(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const std::u16string & FromString,
			                  size_t Len)
			{
				char16_t	* Results = ToString;

				strncat16(ToString, FromString.c_str(), Len);

				return (Results);
			}


			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const std::u32string & FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				strncat16(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const std::wstring & FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strncat16(ToString, (char16_t *)FromString.c_str(), Len);
#elif __SIZEOF_WCHAR_T__ == 4
				strncat16(ToString, (char32_t *)FromString.c_str(), Len);
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char16_t	*
			String::strncat16(char16_t * ToString,
			                  const String & FromString,
			                  size_t Len)
			{
				char16_t	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strncat16(ToString, FromString.Get16(), Len);


				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strncat16(ToString, FromString.cbegin().str8(), Len);
							break;

						case Is16Bit_t:
							strncat16(ToString, FromString.cbegin().str16(), Len);
							break;

						case Is32Bit_t:
							strncat16(ToString, FromString.cbegin().str32(), Len);
							break;

						case IsWBit_t:
							strncat16(ToString, FromString.cbegin().strW(), Len);
							break;

					}
				}

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const char * const FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::Charset8To32(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat32(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const char16_t * const FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::Charset16To32(nullptr,
					                          FromString,
					                          nullptr,
					                          OutStr)) {
						strncat32(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const char32_t * const FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					if (Len2 > Len) {
						Len2 = Len;
					}

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(char32_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const wchar_t * const FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					char32_t	*	OutStr = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncat32(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const std::string & FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				strncat32(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const std::u16string & FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				strncat32(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const std::u32string & FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				strncat32(ToString, FromString.c_str(), Len);

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const std::wstring & FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strncat32(ToString, (char16_t *)FromString.c_str(), Len);
#elif __SIZEOF_WCHAR_T__ == 4
				strncat32(ToString, (char32_t *)FromString.c_str(), Len);
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			char32_t	*
			String::strncat32(char32_t * ToString,
			                  const String & FromString,
			                  size_t Len)
			{
				char32_t	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strncat32(ToString, FromString.Get32(), Len);

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strncat32(ToString, FromString.cbegin().str8(), Len);
							break;

						case Is16Bit_t:
							strncat32(ToString, FromString.cbegin().str16(), Len);
							break;

						case Is32Bit_t:
							strncat32(ToString, FromString.cbegin().str32(), Len);
							break;

						case IsWBit_t:
							strncat32(ToString, FromString.cbegin().strW(), Len);
							break;

					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const char * const FromString,
			                 size_t Len)
			{
				wchar_t		*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset8ToW(nullptr,
					                        FromString,
					                        nullptr,
					                        OutStr)) {
						strncatW(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const char16_t * const FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset16ToW(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncatW(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const char32_t * const FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					wchar_t	*	OutStr = nullptr;

					if (String::Charset32ToW(nullptr,
					                         FromString,
					                         nullptr,
					                         OutStr)) {
						strncatW(ToString, OutStr, Len);
						delete OutStr;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const wchar_t * const FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				if (ToString != nullptr && FromString != nullptr) {
					size_t		Len1 = strlen(ToString);
					size_t		Len2 = strlen(FromString);

					if (Len2 > Len) {
						Len2 = Len;
					}

					memcpy(&ToString[Len1], FromString,
					       Len2 * (sizeof(wchar_t)));
					Results[Len2 + Len1] = 0;
				}

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const std::string & FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				strncatW(ToString, FromString.c_str(), Len);

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const std::u16string & FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				strncatW(ToString, FromString.c_str(), Len);

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const std::u32string & FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				strncatW(ToString, FromString.c_str(), Len);

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const std::wstring & FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

#if __SIZEOF_WCHAR_T__ == 2
				strncatW(ToString, (char16_t *)FromString.c_str(), Len);
#elif __SIZEOF_WCHAR_T__ == 4
				strncatW(ToString, (wchar_t *)FromString.c_str(), Len);
#else
				ERROR what is WCHAR_T size;
#endif

				return (Results);
			}

			wchar_t	*
			String::strncatW(wchar_t * ToString,
			                 const String & FromString,
			                 size_t Len)
			{
				wchar_t	*	Results = ToString;

				if (!FromString.IsReadOnly()) {
					strncatW(ToString, FromString.GetW(), Len);

				} else {
					switch (FromString.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							strncatW(ToString, FromString.cbegin().str8(), Len);
							break;

						case Is16Bit_t:
							strncatW(ToString, FromString.cbegin().str16(), Len);
							break;

						case Is32Bit_t:
							strncatW(ToString, FromString.cbegin().str32(), Len);
							break;

						case IsWBit_t:
							strncatW(ToString, FromString.cbegin().strW(), Len);
							break;

					}
				}

				return (Results);
			}


			String	&
			String::operator +(const String & other)
			{
				String	*	Results = new String(*this);

				Results->Append(other);

				return (*Results);
			}

			String	&
			String::operator +(const char * other)
			{
				String	*	Results = new String(*this);

				Results->Append(other);

				return (*Results);
			}

			String	&
			String::operator +(const wchar_t * other)
			{
				String	*	Results = new String(*this);

				Results->Append(other);

				return (*Results);
			}

			String &
			String::Append(const String & NewStrData, size_t CharCount)
			{
				if (!_ROString) {

					const StringSeg	*	Seg = nullptr;
					StringSeg		*	NewSeg = nullptr;
					std::vector<StringSeg *>::const_iterator	it;
					size_t			ToGo = CharCount;
					size_t			SegLen = 0;

					if (ToGo == 0) {
						ToGo = NewStrData.Length();
					}

					if (NewStrData._RO != nullptr) {
						NewSeg = new StringSeg(*NewStrData._RO);
						_Segments.push_back(NewSeg);

					} else {
						for (it = NewStrData._Segments.begin()
						          ; ToGo > 0 && it != NewStrData._Segments.end()
						     ; it++) {

							Seg = *it;

							if (Seg != nullptr) {
								switch (Seg->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t:
										SegLen = Seg->Str.Utf8->length();
										break;

									case Is16Bit_t:
										SegLen = Seg->Str.Utf16->length();
										break;

									case Is32Bit_t:
										SegLen = Seg->Str.Utf32->length();
										break;

									case IsWBit_t:
										SegLen = Seg->Str.W->length();
										break;
								}

								if (ToGo >= SegLen) {
									NewSeg = new StringSeg(*Seg);
									ToGo -= SegLen;

								} else {
									NewSeg = new StringSeg(*Seg, ToGo);
									ToGo = 0;
								}

								_Segments.push_back(NewSeg);
							}
						}

						_SetInputChanged();
					}
				}

				return (*this);
			}

			String	&
			String::Append(String::const_iterator & It, size_t Len)
			{
				switch (It._Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Append(It.str8(), Len);
						break;

					case Is16Bit_t:
						Append(It.str16(), Len);
						break;

					case Is32Bit_t:
						Append(It.str32(), Len);
						break;

					case IsWBit_t:
						Append(It.strW(), Len);
						break;

				}

				return (*this);
			}

			String	&
			String::Append(const ROString & Str, size_t Len)
			{
				if (Len > Str.Length()) {
					Len = Str.Length();
				}

				switch (Str._RO->Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t: {
							const_iterator	it;

							it = Str.cbegin();

							Append(it.str8(), Len);
						}
						break;

					case Is16Bit_t: {
							const_iterator	it = Str.cbegin();

							Append(it.str16(), Len);
						}
						break;

					case Is32Bit_t: {
							const_iterator	it = Str.cbegin();

							Append(it.str32(), Len);
						}
						break;

					case IsWBit_t: {
							const_iterator	it = Str.cbegin();

							Append(it.strW(), Len);
						}
						break;

				}

				return (*this);
			}

			String &
			String::Append(const wchar_t * NewStrData, size_t charCount)
			{
				if (NewStrData != nullptr && !_ROString) {

					StringSeg	*	NewSeg = new StringSeg(NewStrData,
					                                       charCount);
					_Segments.push_back(NewSeg);
					_SetInputChanged();
				}

				return (*this);
			}

			String &
			String::Append(const char16_t * NewStrData,
			               size_t charCount)
			{
				if (NewStrData != nullptr && !_ROString) {

					StringSeg	*	NewSeg = new StringSeg(NewStrData,
					                                       charCount);
					_Segments.push_back(NewSeg);
					_SetInputChanged();
				}

				return (*this);
			}

			String &
			String::Append(const char32_t * NewStrData,
			               size_t charCount)
			{
				if (NewStrData != nullptr && !_ROString) {

					StringSeg	*	NewSeg = new StringSeg(NewStrData,
					                                       charCount);
					_Segments.push_back(NewSeg);
					_SetInputChanged();
				}

				return (*this);
			}

			String &
			String::Append(const char * NewStrData, size_t charCount)
			{
				if (NewStrData != nullptr && !_ROString) {

					StringSeg	*	NewSeg = new StringSeg(NewStrData,
					                                       charCount);
					_Segments.push_back(NewSeg);
					_SetInputChanged();
				}

				return (*this);
			}

			String	&
			String::Append(const std::string & Str, size_t charCount)
			{
				return (Append(Str.c_str(), charCount));
			}

			String	&
			String::Append(const std::u16string & Str, size_t charCount)
			{
				return (Append(Str.c_str(), charCount));
			}

			String	&
			String::Append(const std::u32string & Str, size_t charCount)
			{
				return (Append(Str.c_str(), charCount));
			}

			String	&
			String::Append(const std::wstring & Str, size_t charCount)
			{
				return (Append(Str.c_str(), charCount));
			}

			String &
			String::Append(char newVal)
			{
				char			newData[2];

				newData[0] = newVal;
				newData[1] = '\0';

				return (Append(newData));
			}

			String &
			String::Append(wchar_t newVal)
			{
				return (Append((char32_t)newVal));
			}

			String  &
			String::Append(char16_t newVal)
			{
				char16_t			newData[2];

				newData[0] = newVal;
				newData[1] = '\0';

				return (Append(newData));
			}

			String  &
			String::Append(char32_t newVal)
			{
				char32_t			newData[2];

				newData[0] = newVal;
				newData[1] = '\0';

				return (Append(newData));
			}

			String	&
			String::AppendValue(int8_t newVal)
			{
				char			newData[4 + 1];

				::sprintf(newData, "%d", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(uint8_t newVal)
			{
				char			newData[4 + 1];

				::sprintf(newData, "%u", newVal);

				return (Append(newData));
			}

			String &
			String::AppendValue(int16_t newVal)
			{
				char			newData[6 + 1];

				::sprintf(newData, "%d", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(uint16_t newVal)
			{
				char			newData[6 + 1];

				::sprintf(newData, "%u", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(int32_t newVal)
			{
				char			newData[11 + 1];

				::sprintf(newData, "%d", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(uint32_t newVal)
			{
				char			newData[11 + 1];

				::sprintf(newData, "%u", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(int64_t newVal)
			{
				char			newData[11 + 1];

				::sprintf(newData, "%ld", newVal);

				return (Append(newData));
			}

			String	&
			String::AppendValue(uint64_t newVal)
			{
				char			newData[11 + 1];

				::sprintf(newData, "%lu", newVal);

				return (Append(newData));
			}

		}
	}
}
