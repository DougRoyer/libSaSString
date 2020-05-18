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
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			char	*
			String::strncpy8(char * ToString, const char * const From,
			                 size_t Count)
			{
				char	*	Results = ToString;

				if (From != nullptr) {
					::strncpy(ToString, From, Count);
				}

				return (Results);
			}

			char	*
			String::strncpy8(char * ToString,
			                 const char16_t * const From, size_t Count)
			{
				char	*	Results = ToString;

				if (From != nullptr && Count > 0) {
					char	*	Out = nullptr;

					if (String::Charset16To8(Current16BitCharset,
					                         From,
					                         Current8BitCharset,
					                         Out)) {
						Results = strncpy8(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char	*
			String::strncpy8(char * ToString,
			                 const char32_t * const From, size_t Count)
			{
				char	*	Results = ToString;

				if (From != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset32To8(Current32BitCharset,
					                         From,
					                         Current8BitCharset,
					                         Out)) {
						Results = strncpy8(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char	*
			String::strncpy8(char * ToString,
			                 const wchar_t * const From, size_t Count)
			{
				char	*	Results = ToString;

				if (From != nullptr) {
					char	*	Out = nullptr;

					if (String::CharsetWTo8(CurrentWBitCharset,
					                        From,
					                        Current8BitCharset,
					                        Out)) {
						Results = strncpy8(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char	*
			String::strncpy8(char * ToString, const std::string & From,
			                 size_t Count)
			{
				return (strncpy8(ToString, From.c_str(), Count));
			}

			char	*
			String::strncpy8(char * ToString,
			                 const std::u16string & From, size_t Count)
			{
				return (strncpy8(ToString, From.c_str(), Count));
			}

			char	*
			String::strncpy8(char * ToString,
			                 const std::u32string & From, size_t Count)
			{
				return (strncpy8(ToString, From.c_str(), Count));
			}

			char	*
			String::strncpy8(char * ToString, const std::wstring & From,
			                 size_t Count)
			{
				return (strncpy8(ToString, From.c_str(), Count));
			}

			char	*
			String::strncpy8(char * ToString, const String & From,
			                 size_t Count)
			{
				char		*	Results = nullptr;

				size_t			Len = 0;

				switch (From.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (From.IsReadOnly()) {
							ROString	*	RPtr = (ROString *)&From;
							const char	*	Val = RPtr->Get8(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy8(ToString, Val, Len);

						} else {
							Results = strncpy8(ToString, From.Get8(), Count);
						}

						break;

					case Is16Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char16_t	*	Val = RPtr->Get16(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy8(ToString, Val, Len);

						} else {
							Results = strncpy8(ToString, From.Get16(), Count);
						}

						break;

					case Is32Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char32_t	*	Val = RPtr->Get32(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy8(ToString, Val, Len);

						} else {
							Results = strncpy8(ToString, From.Get32(), Count);
						}

						break;

					case IsWBit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const wchar_t	*	Val = RPtr->GetW(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy8(ToString, Val, Len);

						} else {
							Results = strncpy8(ToString, From.GetW(), Count);
						}

						break;

				}

				return (Results);
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const char * const From, size_t Count)
			{
				char16_t	*	Results = ToString;

				if (From != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset8To16(Current8BitCharset,
					                         From,
					                         Current16BitCharset,
					                         Out)) {
						Results = strncpy16(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const char16_t * const From, size_t Count)
			{
				char16_t	*	Results = ToString;

				if (From != nullptr) {
					size_t		ToLen = strlen(ToString);
					size_t		FromLen = strlen(From);


					if (FromLen > Count) {
						FromLen = Count;
					}

					if (FromLen > 0) {
						memcpy(&ToString[ToLen], From, FromLen * sizeof(char16_t));
						ToString[ToLen + FromLen] = 0;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const char32_t * const From, size_t Count)
			{
				char16_t	*	Results = ToString;

				if (From != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset32To16(Current32BitCharset,
					                          From,
					                          Current16BitCharset,
					                          Out)) {
						Results = strncpy16(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const wchar_t * const From, size_t Count)
			{
				char16_t	*	Results = ToString;

				if (From != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(CurrentWBitCharset,
					                         From,
					                         Current16BitCharset,
					                         Out)) {
						Results = strncpy16(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const std::string & From, size_t Count)
			{
				return (strncpy16(ToString, From.c_str(), Count));
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const std::u16string & From, size_t Count)
			{
				return (strncpy16(ToString, From.c_str(), Count));
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const std::u32string & From, size_t Count)
			{
				return (strncpy16(ToString, From.c_str(), Count));
			}

			char16_t	*
			String::strncpy16(char16_t * ToString,
			                  const std::wstring & From, size_t Count)
			{
				return (strncpy16(ToString, From.c_str(), Count));
			}

			char16_t	*
			String::strncpy16(char16_t * ToString, const String & From,
			                  size_t Count)
			{
				char16_t	*	Results = nullptr;

				size_t			Len = 0;

				switch (From.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char		*	Val = RPtr->Get8(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy16(ToString, Val, Len);

						} else {
							Results = strncpy16(ToString, From.Get8(), Count);
						}

						break;

					case Is16Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char16_t	*	Val = RPtr->Get16(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy16(ToString, Val, Len);

						} else {
							Results = strncpy16(ToString, From.Get16(), Count);
						}

						break;

					case Is32Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char32_t	*	Val = RPtr->Get32(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy16(ToString, Val, Len);

						} else {
							Results = strncpy16(ToString, From.Get32(), Count);
						}

						break;

					case IsWBit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const wchar_t	*	Val = RPtr->GetW(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy16(ToString, Val, Len);

						} else {
							Results = strncpy16(ToString, From.GetW(), Count);
						}

						break;
				}

				return (Results);
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const char * const From, size_t Count)
			{
				char32_t	*	Results = ToString;

				if (From != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset8To32(Current8BitCharset,
					                         From,
					                         Current32BitCharset,
					                         Out)) {
						Results = strncpy32(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const char16_t * const From, size_t Count)
			{
				char32_t	*	Results = ToString;

				if (From != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset16To32(Current16BitCharset,
					                          From,
					                          Current32BitCharset,
					                          Out)) {
						Results = strncpy32(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const char32_t * const From, size_t Count)
			{
				char32_t	*	Results = ToString;

				if (From != nullptr) {
					size_t		ToLen = strlen(ToString);
					size_t		FromLen = strlen(From);

					if (FromLen > Count) {
						FromLen = Count;
					}

					if (FromLen > 0) {
						memcpy(&ToString[ToLen], From, FromLen * sizeof(char32_t));
						ToString[ToLen + FromLen] = 0;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const wchar_t * const From,
			                  size_t Count)
			{
				char32_t	*	Results = ToString;

				if (From != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::CharsetWTo32(CurrentWBitCharset,
					                         From,
					                         Current32BitCharset,
					                         Out)) {
						Results = strncpy32(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const std::string & From, size_t Count)
			{
				return (strncpy32(ToString, From.c_str(), Count));
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const std::u16string & From, size_t Count)
			{
				return (strncpy32(ToString, From.c_str(), Count));
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const std::u32string & From, size_t Count)
			{
				return (strncpy32(ToString, From.c_str(), Count));
			}

			char32_t	*
			String::strncpy32(char32_t * ToString,
			                  const std::wstring & From, size_t Count)
			{
				return (strncpy32(ToString, From.c_str(), Count));
			}

			char32_t	*
			String::strncpy32(char32_t * ToString, const String & From,
			                  size_t Count)
			{
				char32_t	*	Results = nullptr;

				size_t			Len = 0;

				switch (From.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char		*	Val = RPtr->Get8(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy32(ToString, Val, Len);

						} else {
							Results = strncpy32(ToString, From.Get8(), Count);
						}

						break;

					case Is16Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char16_t	*	Val = RPtr->Get16(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy32(ToString, Val, Len);

						} else {
							Results = strncpy32(ToString, From.Get16(), Count);
						}

						break;

					case Is32Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char32_t	*	Val = RPtr->Get32(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy32(ToString, Val, Len);

						} else {
							Results = strncpy32(ToString, From.Get32(), Count);
						}

						break;

					case IsWBit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const wchar_t	*	Val = RPtr->GetW(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpy32(ToString, Val, Len);

						} else {
							Results = strncpy32(ToString, From.GetW(), Count);
						}

						break;

				}

				return (Results);
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const char * const From, size_t Count)
			{
				wchar_t		*	Results = ToString;

				if (From != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset8ToW(Current8BitCharset,
					                        From,
					                        CurrentWBitCharset,
					                        Out)) {
						Results = strncpyW(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const char16_t * const From, size_t Count)
			{
				wchar_t		*	Results = ToString;

				if (From != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset16ToW(Current16BitCharset,
					                         From,
					                         CurrentWBitCharset,
					                         Out)) {
						Results = strncpyW(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const char32_t * const From, size_t Count)
			{
				wchar_t		*	Results = ToString;

				if (From != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset32ToW(Current32BitCharset,
					                         From,
					                         CurrentWBitCharset,
					                         Out)) {
						Results = strncpyW(ToString, Out, Count);
						delete Out;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const wchar_t * const From, size_t Count)
			{
				wchar_t		*	Results = ToString;

				if (From != nullptr) {
					size_t		ToLen = strlen(ToString);
					size_t		FromLen = strlen(From);

					if (FromLen > Count) {
						FromLen = Count;
					}

					if (FromLen > 0) {
						memcpy(&ToString[ToLen], From, FromLen * sizeof(wchar_t));
						ToString[ToLen + FromLen] = 0;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const std::string & From, size_t Count)
			{
				return (strncpyW(ToString, From.c_str(), Count));
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const std::u16string & From, size_t Count)
			{
				return (strncpyW(ToString, From.c_str(), Count));
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const std::u32string & From, size_t Count)
			{
				return (strncpyW(ToString, From.c_str(), Count));
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString,
			                 const std::wstring & From, size_t Count)
			{
				return (strncpyW(ToString, From.c_str(), Count));
			}

			wchar_t	*
			String::strncpyW(wchar_t * ToString, const String & From,
			                 size_t Count)
			{
				wchar_t		*	Results = nullptr;

				size_t			Len = 0;

				switch (From.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char		*	Val = RPtr->Get8(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpyW(ToString, Val, Len);

						} else {
							Results = strncpyW(ToString, From.Get8(), Count);
						}

						break;

					case Is16Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char16_t	*	Val = RPtr->Get16(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpyW(ToString, Val, Len);

						} else {
							Results = strncpyW(ToString, From.Get16(), Count);
						}

						break;

					case Is32Bit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const char32_t	*	Val = RPtr->Get32(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpyW(ToString, Val, Len);

						} else {
							Results = strncpyW(ToString, From.Get32(), Count);
						}

						break;

					case IsWBit_t:
						if (From.IsReadOnly()) {
							ROString		*	RPtr = (ROString *)&From;
							const wchar_t	*	Val = RPtr->GetW(Len);

							if (Count < Len) {
								Len = Count;
							}

							Results = strncpyW(ToString, Val, Len);

						} else {
							Results = strncpyW(ToString, From.GetW(), Count);
						}

						break;
				}

				return (Results);
			}

		}
	}
}
