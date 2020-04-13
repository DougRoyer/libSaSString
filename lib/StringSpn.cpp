//
// BEGIN_DOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2017-2018 Douglas Mark Royer, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO DOUGLAS MARK ROYER. THIS CODE IS CONSIDERED
// A TRADE SECRET AND IS NOT TO BE DIVULGED OR USED BY PARTIES WHO HAVE
// NOT RECEIVED WRITTEN AUTHORIZATION FROM THE OWNER.
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
// PROVIDED ON AN "AS IS" BASIS AND DOUGLAS MARK ROYER
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// END_DOUGLAS_MARK_ROYER_COPYRIGHT
//
#include <SaS/String/String.hpp>
#include <sys/param.h>
#include <algorithm>
#include <ostream>

#include <unistr.h>
#include <unitypes.h>

#include <iconv.h>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			size_t
			String::strspn(const String & InStr,
			               const String & Reject)
			{
				size_t		Results = 0;

				switch (InStr._InputWidth) {

					default:

					/*FALLTHRU*/
					case Is8Bit_t:
						Results = strspn(InStr.Get8(), Reject.Get8());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.Get16(), Reject.Get16());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.Get32(), Reject.Get32());
						break;
				}

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const char * const Reject)
			{
				size_t			Results = 0;

				if (Reject != nullptr) {
					if (strcmp(InStr._InputCharset, Current8BitCharset) == 0) {
						Results = strspn(InStr.Get8(), Reject);

					} else {
						String		RCopy(Reject);
						String	*	CS = RCopy.ToCharset(InStr._InputCharset,
						                                 InStr._InputWidth);

						Results = strspn(InStr, *CS);
						delete CS;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const char16_t * const Reject)
			{
				size_t			Results = 0;

				if (Reject != nullptr) {
					if (strcmp(InStr._InputCharset, Current16BitCharset) == 0) {
						Results = strspn(InStr.Get16(), Reject);

					} else {
						String		RCopy(Reject);
						String	*	CS = RCopy.ToCharset(InStr._InputCharset,
						                                 InStr._InputWidth);

						Results = strspn(InStr, *CS);
						delete CS;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const char32_t * const Reject)
			{
				size_t			Results = 0;

				if (Reject != nullptr) {
					if (strcmp(InStr._InputCharset, Current32BitCharset) == 0) {
						Results = strspn(InStr.Get32(), Reject);

					} else {
						String		RCopy(Reject);
						String	*	CS = RCopy.ToCharset(InStr._InputCharset,
						                                 InStr._InputWidth);

						Results = strspn(InStr, *CS);
						delete CS;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const wchar_t * const Reject)
			{
				size_t			Results = 0;

				if (Reject != nullptr) {
					if (strcmp(InStr._InputCharset, CurrentWBitCharset) == 0) {
						Results = strspn(InStr.GetW(), Reject);

					} else {
						String		RCopy(Reject);
						String	*	CS = RCopy.ToCharset(InStr._InputCharset,
						                                 InStr._InputWidth);

						Results = strspn(InStr, *CS);
						delete CS;

					}
				}

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const std::string & Reject)
			{
				size_t			Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const std::u16string & Reject)
			{
				size_t			Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const std::u32string & Reject)
			{
				size_t			Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const String & InStr,
			               const std::wstring & Reject)
			{
				size_t			Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const char * const Reject)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					const char  *	InPtr = InStr;
					const char  *	RPtr = Reject;
					size_t	InLen = 0;
					size_t	RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Reject;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) != 0) {
								Done = true;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset16To8(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const char32_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset32To8(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char	*	Out = nullptr;

					if (String::CharsetWTo8(nullptr,
					                        Reject,
					                        nullptr,
					                        Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const String & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.Get8());
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const std::string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const std::u16string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const std::u32string & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char * const InStr,
			               const std::wstring & Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const char * const Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset8To16(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const char16_t * const Reject)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					const char16_t  *	InPtr = InStr;
					const char16_t  *	RPtr = Reject;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Reject;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) != 0) {
								Done = true;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const char32_t * const Reject)
			{
				size_t			Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset32To16(nullptr,
					                          Reject,
					                          nullptr,
					                          Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const std::string & Reject)
			{
				return (strspn(InStr, Reject.c_str()));
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const std::u16string & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const std::u32string & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char16_t * const InStr,
			               const std::wstring & Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr) {
					Results = strspn(InStr, Reject.c_str());
				}

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const char * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset8To32(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset16To32(nullptr,
					                          Reject,
					                          nullptr,
					                          Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const char32_t * const Reject)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					const char32_t  *	InPtr = InStr;
					const char32_t  *	RPtr = Reject;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Reject;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) != 0) {
								Done = true;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const wchar_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const std::string & Reject)
			{
				size_t		Results = 0;

				Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const std::u16string & Reject)
			{
				size_t		Results = 0;

				Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const std::u32string & Reject)
			{
				size_t		Results = 0;

				Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const std::wstring & Reject)
			{
				size_t		Results = 0;

				Results = strspn(InStr, Reject.c_str());

				return (Results);
			}

			size_t
			String::strspn(const char32_t * const InStr,
			               const String & Reject)
			{
				size_t		Results = strspn(InStr, Reject.Get32());

				return (Results);
			}

			size_t
			String::strspn(const wchar_t * const InStr,
			               const char * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset8ToW(nullptr,
					                        Reject,
					                        nullptr,
					                        Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const wchar_t * const InStr,
			               const char16_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset16ToW(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const wchar_t * const InStr,
			               const char32_t * const Reject)
			{
				size_t		Results = 0;

				if (InStr != nullptr && Reject != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset32ToW(nullptr,
					                         Reject,
					                         nullptr,
					                         Out)) {
						Results = strspn(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			size_t
			String::strspn(const wchar_t * const InStr,
			               const wchar_t * const Reject)
			{
				size_t		Results = 0;

				bool		Done = false;

				if (InStr != nullptr && Reject != nullptr) {
					const wchar_t  *	InPtr = InStr;
					const wchar_t  *	RPtr = Reject;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Reject;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) != 0) {
								Done = true;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
							Results++;
						}
					}
				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const char * const Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject);
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject);
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject);
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject);
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const char16_t * const Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject);
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject);
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject);
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject);
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const char32_t * const Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject);
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject);
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject);
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject);
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const wchar_t * const Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject);
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject);
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject);
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject);
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const std::string & Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject.c_str());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject.c_str());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject.c_str());
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject.c_str());
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const std::u16string & Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject.c_str());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject.c_str());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject.c_str());
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject.c_str());
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const std::u32string & Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject.c_str());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject.c_str());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject.c_str());
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject.c_str());
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const std::wstring & Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject.c_str());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject.c_str());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject.c_str());
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject.c_str());
						break;

				}

				return (Results);
			}

			size_t
			String::strspn(String::const_iterator & InStr,
			               const String & Reject)
			{
				size_t		Results = 0;

				switch (InStr.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strspn(InStr.str8(), Reject.Get8());
						break;

					case Is16Bit_t:
						Results = strspn(InStr.str16(), Reject.Get16());
						break;

					case Is32Bit_t:
						Results = strspn(InStr.str32(), Reject.Get32());
						break;

					case IsWBit_t:
						Results = strspn(InStr.strW(), Reject.GetW());
						break;

				}

				return (Results);
			}


		}
	}
}
