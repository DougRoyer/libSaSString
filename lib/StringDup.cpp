//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2019 Software and Services LLC, All Rights Reserved.
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

			/**
			 * Copy up to Max UTF-8 CHARACTERS.
			 *
			 * @param Out Where to place the copied data.
			 * Must hold (Max+1) or when Max == 0, then hold
			 * (strlen(In) + 1) in octets.
			 *
			 * @param In Where to get the copied data from.
			 *
			 * @return The number of Octets copied (not characters).
			 */
			static size_t
			Copy8(char * Out, const char * const In, size_t Max)
			{
				size_t			Results = 0;

				if (strcmp(Current8BitCharset, Utf8_s) == 0) {
					size_t			ToGo = Max;
					const char		*	InPtr = In;
					char		*		OutPtr = Out;
					size_t			ToCopy;

					if (Max == 0) {
						ToGo = ::strlen(In);
					}

					while (*InPtr != 0 && ToGo != 0) {
						ToCopy = String::CharacterUnits(InPtr);
						memcpy(OutPtr, InPtr, ToCopy);
						OutPtr += ToCopy;
						InPtr += ToCopy;
						ToGo--;
						Results += ToCopy;
					}

					*OutPtr = 0;
				}

				return (Results);
			}

			/**
			 * Copy up to Max UTF-16 CHARACTERS.
			 *
			 * @param Out Where to place the copied data.
			 * Must hold (Max+1) or when Max == 0, then hold
			 * (strlen(In) + 1) in octets.
			 *
			 *
			 * @param In Where to get the copied data from.
			 *
			 * @return The number of Octets copied (not characters).
			 */
			static size_t
			Copy16(char16_t * Out, const char16_t * const In,
			       size_t Max)
			{
				size_t			Results = 0;

				if (strncmp(Current16BitCharset, Utf16_s, 6) == 0) {
					size_t			ToGo = Max;
					const char16_t	*	InPtr = In;
					char16_t		*	OutPtr = Out;
					size_t			ToCopy;

					if (Max == 0) {
						ToGo = String::strlen(In);
					}

					while (*InPtr != 0 && ToGo != 0) {
						ToCopy = String::CharacterUnits(InPtr);
						memcpy(OutPtr, InPtr, ToCopy * sizeof(char16_t));
						OutPtr += ToCopy;
						InPtr += ToCopy;
						ToGo--;
						Results += (ToCopy * sizeof(char16_t));
					}

					*OutPtr = 0;
				}

				return (Results);
			}

			/**
			 * Copy up to Max UTF-16 CHARACTERS.
			 *
			 * @param Out Where to place the copied data.
			 * Must hold (Max+1) or when Max == 0, then hold
			 * (strlen(In) + 1) in octets.
			 *
			 *
			 * @param In Where to get the copied data from.
			 *
			 * @return The number of Octets copied (not characters).
			 */
			static size_t
			CopyW(wchar_t * Out, const wchar_t * const In, size_t Max)
			{
				size_t			Results = 0;

#if __SIZEOF_WCHAR_T__ == 2
				const char		*	CSet = Utf16_s;
#endif
#if __SIZEOF_WCHAR_T__ == 4
				const char		*	CSet = Utf32_s;
#endif

				if (strncmp(CurrentWBitCharset, CSet, 6) == 0) {
					size_t			ToGo = Max;
					const wchar_t		*	InPtr = In;
					wchar_t		*	OutPtr = Out;
					size_t			ToCopy;

					if (Max == 0) {
						ToGo = String::strlen(In);
					}

					while (*InPtr != 0 && ToGo != 0) {
						ToCopy = String::CharacterUnits(InPtr);
						memcpy(OutPtr, InPtr, ToCopy * sizeof(wchar_t));
						OutPtr += ToCopy;
						InPtr += ToCopy;
						ToGo--;
						Results += (ToCopy * sizeof(wchar_t));
					}

					*OutPtr = 0;
				}

				return (Results);
			}

			/**
			 * Copy up to Max UTF-32 CHARACTERS.
			 *
			 * @param Out Where to place the copied data.
			 * Must hold (Max+1) or when Max == 0, then hold
			 * (strlen(In) + 1) in octets.
			 *
			 * @param In Where to get the copied data from.
			 *
			 * @return The number of Octets copied (not characters).
			 */
			static size_t
			Copy32(char32_t * Out, const char32_t * const In,
			       size_t Max)
			{
				if (Max == 0) {
					Max = String::strlen(In);
				}

				memcpy(Out, In, Max * 4);
				Out[Max] = 0;

				return (Max * 4);
			}

			char	*
			String::strdup8(const char * const In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						Results = ::strdup(In);

					} else {

						// Each UTF-8 character could be up to 4 octets long.
						//
						char	*	Dup = new char[(MaxLen * 4) + 1];
						size_t		DupOctets = Copy8(Dup, In, MaxLen);

						// Make it just fit.
						//
						if (DupOctets == (MaxLen * 4)) {
							Results = Dup;

						} else {
							Results = new char[DupOctets + 1];
							Results[DupOctets] = 0;
							memcpy(Results, Dup, DupOctets);
							delete Dup;
						}
					}
				}

				return (Results);
			}

			char	*
			String::strdup8(const char16_t * const In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char	*	Out = nullptr;

						if (Charset16To8(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-16 character could be up to 2 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char16_t	*	Dup = new char16_t[(MaxLen * 2) + 1];
						char	*	Out = nullptr;

						Copy16(Dup, In, MaxLen);

						if (Charset16To8(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char	*
			String::strdup8(const char32_t * const In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char	*	Out = nullptr;

						if (Charset32To8(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-32 character could be up to 1 unit long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char32_t	*	Dup = new char32_t[(MaxLen) + 1];
						char	*	Out = nullptr;

						Copy32(Dup, In, MaxLen);

						if (Charset32To8(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char	*
			String::strdup8(const wchar_t * const In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char	*	Out = nullptr;

						if (CharsetWTo8(nullptr,
						                In,
						                nullptr,
						                Out)) {
							Results = Out;
						}

					} else {
						// Each UTF-8 character could be up to 1 to 4 units long
						// depending on the size of wchar_t (16 or 32 bits).
						//
						wchar_t	*	Dup = new wchar_t[(MaxLen) + 1];
						char	*	Out = nullptr;

						CopyW(Dup, In, MaxLen);

						if (CharsetWTo8(nullptr,
						                Dup,
						                nullptr,
						                Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char	*
			String::strdup8(const std::string & In, size_t MaxLen)
			{
				char	*	Results = strdup8(In.c_str(), MaxLen);

				return (Results);
			}

			char	*
			String::strdup8(const std::u16string & In, size_t MaxLen)
			{
				char	*	Results = strdup8(In.c_str(), MaxLen);

				return (Results);
			}

			char	*
			String::strdup8(const std::u32string & In, size_t MaxLen)
			{
				char	*	Results = strdup8(In.c_str(), MaxLen);

				return (Results);
			}

			char	*
			String::strdup8(const std::wstring & In, size_t MaxLen)
			{
				char	*	Results = strdup8(In.c_str(), MaxLen);

				return (Results);
			}

			char	*
			String::strdup8(const String & In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				if (In._ROString) {
					if (In._RO->StrUnits < MaxLen) {
						MaxLen = In._RO->StrUnits;
					}

					switch (In._RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strdup8(In._RO->Str.RO8, MaxLen);
							break;

						case Is16Bit_t:
							Results = strdup8(In._RO->Str.RO16, MaxLen);
							break;

						case Is32Bit_t:
							Results = strdup8(In._RO->Str.RO32, MaxLen);
							break;

						case IsWBit_t:
							Results = strdup8(In._RO->Str.ROW, MaxLen);
							break;

					}

				} else {
					if (MaxLen == 0) {
						Results = ::strdup(In.Get8());

					} else {
						char	*	Dup = new char[(In.Length() * 4) + 1];

						Copy8(Dup, In.Get8(), MaxLen);
						Results = ::strdup(Dup);
						delete Dup;
					}
				}

				return (Results);
			}

			char	*
			String::strdup8(const ROString & In, size_t MaxLen)
			{
				char	*	Results = nullptr;

				size_t		Len = MaxLen;

				switch (In.Width()) {

					case Is8Bit_t: {
							const char	*	Tmp = In.Get8(Len);

							if (MaxLen < Len) {
								Len = MaxLen;
							}

							Results = strdup8(Tmp, Len);
						}
						break;

					case Is16Bit_t: {
							const char16_t	*	Tmp = In.Get16(Len);

							if (MaxLen < Len) {
								Len = MaxLen;
							}

							Results = strdup8(Tmp, Len);
						}
						break;

					case Is32Bit_t: {
							const char32_t	*	Tmp = In.Get32(Len);

							if (MaxLen < Len) {
								Len = MaxLen;
							}

							Results = strdup8(Tmp, Len);
						}
						break;

					case IsWBit_t: {
							const wchar_t	*	Tmp = In.GetW(Len);

							if (MaxLen < Len) {
								Len = MaxLen;
							}

							Results = strdup8(Tmp, Len);
						}
						break;

					default:
						/*EMPTY*/
						break;

				}

				return (Results);
			}

			char	*
			String::strdup8(const_iterator & It, size_t MaxLen)
			{
				char				*				Results = nullptr;

				if (It.Width() == Is8Bit_t) {
					const_iterator			Start = It;
					const_iterator			End = It;
					size_t							ToGo = MaxLen;

					while (ToGo < 0 && *End != 0) {
						End += CharacterUnits(*End);
						ToGo--;
					}

					Results = new char[(End - Start) + 1];
					memcpy(Results, It.str8(), End - Start);
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const_iterator & It, size_t MaxLen)
			{
				char16_t				*				Results = nullptr;

				if (It.Width() == Is16Bit_t) {
					const_iterator			Start = It;
					const_iterator			End = It;
					size_t							ToGo = MaxLen;

					while (ToGo < 0 && *End != 0) {
						End += CharacterUnits(*End);
						ToGo--;
					}

					Results = new char16_t[(End - Start) + 1];
					memcpy(Results, It.str16(),
					       (End - Start) * sizeof(char16_t));
				}

				return (Results);
			}

			char32_t	*
			String::strdup32(const_iterator & It, size_t MaxLen)
			{
				char32_t				*				Results = nullptr;

				if (It.Width() == Is32Bit_t) {
					const_iterator			Start = It;
					const_iterator			End = It;
					size_t							ToGo = MaxLen;

					while (ToGo < 0 && *End != 0) {
						End += CharacterUnits(*End);
						ToGo--;
					}

					Results = new char32_t[(End - Start) + 1];
					memcpy(Results, It.str32(),
					       (End - Start) * sizeof(char32_t));
				}

				return (Results);
			}

			wchar_t	*
			String::strdupW(const_iterator & It, size_t MaxLen)
			{
				wchar_t				*				Results = nullptr;

				if (It.Width() == IsWBit_t) {
					const_iterator			Start = It;
					const_iterator			End = It;
					size_t							ToGo = MaxLen;

					while (ToGo < 0 && *End != 0) {
						End += CharacterUnits(*End);
						ToGo--;
					}

					Results = new wchar_t[(End - Start) + 1];
					memcpy(Results, It.strW(), (End - Start) * sizeof(wchar_t));
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const char * const In, size_t MaxLen)
			{
				char16_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char16_t	*	Out = nullptr;

						if (Charset8To16(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-16 character could be up to 2 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char	*	Dup = new char[(MaxLen * 4) + 1];
						char16_t	*	Out = nullptr;

						Copy8(Dup, In, MaxLen);

						if (Charset8To16(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const char16_t * const In, size_t MaxLen)
			{
				char16_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						size_t		InLen = strlen(In);
						char16_t	*	Dup = new char16_t[InLen + 1];
						size_t		Octets = Copy16(Dup, In, 0);

						if (Octets == InLen) {
							Results = Dup;

						} else {
							Results = new char16_t[(Octets / 2) + 1];
							memcpy(Results, Dup, Octets);
							Results[Octets / 2] = 0;
						}

					} else {

						// Each UTF-16 character could be up to 4 octets long.
						//
						char16_t	*	Dup = new char16_t[(MaxLen * 2) + 1];
						size_t		Octets = Copy16(Dup, In, MaxLen);

						if (Octets == (MaxLen * 2)) {
							Results = Dup;

						} else {
							Results = new char16_t[(Octets / 2) + 1];
							memcpy(Results, Dup, Octets);
							Results[Octets / 2] = 0;
							delete Dup;
						}
					}
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const char32_t * const In, size_t MaxLen)
			{
				char16_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char16_t	*	Out = nullptr;

						if (Charset32To16(nullptr,
						                  In,
						                  nullptr,
						                  Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-32 character could be up to 1 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char32_t	*	Dup = new char32_t[(MaxLen) + 1];
						char16_t	*	Out = nullptr;

						Copy32(Dup, In, MaxLen);

						if (Charset32To16(nullptr,
						                  Dup,
						                  nullptr,
						                  Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const wchar_t * const In, size_t MaxLen)
			{
				char16_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char16_t	*	Out = nullptr;

						if (CharsetWTo16(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-32 character could be up to 1 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						wchar_t	*	Dup = new wchar_t[(MaxLen) + 1];
						char16_t	*	Out = nullptr;

						CopyW(Dup, In, MaxLen);

						if (CharsetWTo16(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char16_t	*
			String::strdup16(const std::string & In, size_t MaxLen)
			{
				char16_t	*	Results = strdup16(In.c_str(), MaxLen);

				return (Results);
			}

			char16_t	*
			String::strdup16(const std::u16string & In, size_t MaxLen)
			{
				char16_t	*	Results = strdup16(In.c_str(), MaxLen);

				return (Results);
			}

			char16_t	*
			String::strdup16(const std::u32string & In, size_t MaxLen)
			{
				char16_t	*	Results = strdup16(In.c_str(), MaxLen);

				return (Results);
			}

			char16_t	*
			String::strdup16(const std::wstring & In, size_t MaxLen)
			{
				char16_t	*	Results = strdup16(In.c_str(), MaxLen);

				return (Results);
			}

			char16_t	*
			String::strdup16(const String & In, size_t MaxLen)
			{
				char16_t	*	Results = strdup16(In.Get16(), MaxLen);

				return (Results);
			}

			char32_t	*
			String::strdup32(const char * const In, size_t MaxLen)
			{
				char32_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char32_t	*	Out = nullptr;

						if (Charset8To32(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-8 character could be up to 4 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char	*	Dup = new char[(MaxLen * 4) + 1];
						char32_t	*	Out = nullptr;

						Copy8(Dup, In, MaxLen);

						if (Charset8To32(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strdup32(const char16_t * const In, size_t MaxLen)
			{
				char32_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char32_t	*	Out = nullptr;

						if (Charset16To32(nullptr,
						                  In,
						                  nullptr,
						                  Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-16 character could be up to 2 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						char16_t	*	Dup = new char16_t[(MaxLen * 2) + 1];
						char32_t	*	Out = nullptr;

						Copy16(Dup, In, MaxLen);

						if (Charset16To32(nullptr,
						                  Dup,
						                  nullptr,
						                  Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strdup32(const char32_t * const In, size_t MaxLen)
			{
				char32_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						size_t		InLen = strlen(In);
						char32_t	*	Dup = new char32_t[InLen + 1];
						size_t		Octets = Copy32(Dup, In, 0);

						if (Octets == InLen) {
							Results = Dup;

						} else {
							Results = new char32_t[(Octets / 4) + 1];
							memcpy(Results, Dup, Octets);
							Results[Octets / 4] = 0;
						}

					} else {

						// Each UTF-32 character could be up to 1 octet long.
						//
						char32_t	*	Dup = new char32_t[(MaxLen) + 1];
						size_t		Octets = Copy32(Dup, In, MaxLen);

						if (Octets == (MaxLen)) {
							Results = Dup;

						} else {
							Results = new char32_t[(Octets / 4) + 1];
							memcpy(Results, Dup, Octets);
							Results[Octets / 4] = 0;
							delete Dup;
						}
					}
				}

				return (Results);
			}

			char32_t	*
			String::strdup32(const wchar_t * const In, size_t MaxLen)
			{
				char32_t	*	Results = nullptr;

				if (In != nullptr) {
					if (MaxLen == 0) {
						char32_t	*	Out = nullptr;

						if (CharsetWTo32(nullptr,
						                 In,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

					} else {

						// Each UTF-16 character could be up to 2 units long.
						//
						// The charset conversion methods covert entire strings.
						// So we have to make a string the correct length (number
						// of characters).
						//
						wchar_t	*	Dup = new wchar_t[(MaxLen * 2) + 1];
						char32_t	*	Out = nullptr;

						CopyW(Dup, In, MaxLen);

						if (CharsetWTo32(nullptr,
						                 Dup,
						                 nullptr,
						                 Out)) {
							Results = Out;
						}

						delete Dup;
					}
				}

				return (Results);
			}

			char32_t	*
			String::strdup32(const std::string & In, size_t MaxLen)
			{
				char32_t	*	Results = strdup32(In.c_str(), MaxLen);

				return (Results);
			}

			char32_t	*
			String::strdup32(const std::u16string & In, size_t MaxLen)
			{
				char32_t	*	Results = strdup32(In.c_str(), MaxLen);

				return (Results);
			}

			char32_t	*
			String::strdup32(const std::u32string & In, size_t MaxLen)
			{
				char32_t	*	Results = strdup32(In.c_str(), MaxLen);

				return (Results);
			}

			char32_t	*
			String::strdup32(const std::wstring & In, size_t MaxLen)
			{
				char32_t	*	Results = strdup32(In.c_str(), MaxLen);

				return (Results);
			}

			char32_t	*
			String::strdup32(const String & In, size_t MaxLen)
			{
				char32_t	*	Results = strdup32(In.Get32(), MaxLen);

				return (Results);
			}

			wchar_t	*
			String::strdupW(const char * const In, size_t MaxLen)
			{
				wchar_t		*	Results = nullptr;

				size_t			InLen = strlen(In);
				size_t			CpLen = InLen;

				if (MaxLen > 0) {
					if (CpLen > MaxLen) {
						CpLen = MaxLen;
					}
				}

				char	*	Dup = (char *)In;
				wchar_t	*	Out = nullptr;

				if (CpLen != InLen) {
					Dup = new char[InLen + 1];
					Copy8(Dup, In, CpLen);
				}

				if (Charset8ToW(nullptr,
				                Dup,
				                nullptr,
				                Out)) {
					Results = Out;

					if (CpLen != InLen) {
						delete Dup;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strdupW(const char16_t * const In, size_t MaxLen)
			{
				wchar_t		*	Results = nullptr;

				size_t			InLen = strlen(In);
				size_t			CpLen = InLen;

				if (MaxLen > 0) {
					if (CpLen > MaxLen) {
						CpLen = MaxLen;
					}
				}

				char16_t *	Dup = (char16_t *)In;
				wchar_t	*	Out = nullptr;

				if (CpLen != InLen) {
					Dup = new char16_t[InLen + 1];
					Copy16(Dup, In, CpLen);
				}

				if (Charset16ToW(nullptr,
				                 Dup,
				                 nullptr,
				                 Out)) {
					Results = Out;

					if (CpLen != InLen) {
						delete Dup;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strdupW(const char32_t * const In, size_t MaxLen)
			{
				wchar_t		*	Results = nullptr;

				size_t			InLen = strlen(In);
				size_t			CpLen = InLen;

				if (MaxLen > 0) {
					if (CpLen > MaxLen) {
						CpLen = MaxLen;
					}
				}

				char32_t *	Dup = (char32_t *)In;
				wchar_t	*	Out = nullptr;

				if (CpLen != InLen) {
					Dup = new char32_t[InLen + 1];
					Copy32(Dup, In, CpLen);
				}

				if (Charset32ToW(nullptr,
				                 Dup,
				                 nullptr,
				                 Out)) {
					Results = Out;

					if (CpLen != InLen) {
						delete Dup;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strdupW(const wchar_t * const In, size_t MaxLen)
			{
				wchar_t		*	Results = nullptr;

				size_t			InLen = strlen(In);
				size_t			CpLen = InLen;

				if (MaxLen > 0) {
					if (CpLen > MaxLen) {
						CpLen = MaxLen;
					}
				}

				wchar_t	*	Dup = (wchar_t *)In;
				wchar_t	*	Out = nullptr;

				if (CpLen != InLen) {
					Dup = new wchar_t[InLen + 1];
					CopyW(Dup, In, CpLen);
				}

				if (CharsetWToW(nullptr,
				                Dup,
				                nullptr,
				                Out)) {
					Results = Out;

					if (CpLen != InLen) {
						delete Dup;
					}
				}

				return (Results);
			}

			wchar_t	*
			String::strdupW(const std::string & In, size_t MaxLen)
			{
				wchar_t	*	Results = strdupW(In.c_str(), MaxLen);

				return (Results);
			}

			wchar_t	*
			String::strdupW(const std::u16string & In, size_t MaxLen)
			{
				wchar_t	*	Results = strdupW(In.c_str(), MaxLen);

				return (Results);
			}

			wchar_t	*
			String::strdupW(const std::u32string & In, size_t MaxLen)
			{
				wchar_t	*	Results = strdupW(In.c_str(), MaxLen);

				return (Results);
			}

			wchar_t	*
			String::strdupW(const std::wstring & In, size_t MaxLen)
			{
				wchar_t	*	Results = strdupW(In.c_str(), MaxLen);

				return (Results);
			}

			wchar_t	*
			String::strdupW(const String & In, size_t MaxLen)
			{
				wchar_t	*	Results = strdupW(In.Get32(), MaxLen);

				return (Results);
			}

		}
	}
}
