//
// BEGIN_DOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2017-2019 Douglas Mark Royer, All Rights Reserved.
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
#include <SaS/String/StringCache.hpp>
#include <sys/param.h>
#include <algorithm>
#include <ostream>

#include <unistr.h>
#include <unitypes.h>

#include <iconv.h>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			static
			String	*
			Replace8(const String & StrObject,
			         const char * Old,
			         const char * New,
			         size_t HowMany)
			{
				String		*	Results = nullptr;

				// Current8BitCharset, OldStr, and NewStr
				// are all in the same charset.
				//
				const char	*	Original = StrObject.Get8();
				const char	*	Found = String::strstr(Original, Old);

				String		*	Str = nullptr;
				size_t			OldStrLen = String::strlen(Old);
				size_t			Len;

				if (Found == nullptr) {
					Results = new String(Original);

				} else {
					while (Found != nullptr) {
						Len = Found - Original;

						Str = new String();

						if (Len > 0) {
							Str->Append(Original, Len);
						}

						Str->Append(New);
						Found += OldStrLen;
						Str->Append(Found);

						if (HowMany-- == 0) {
							Results = Str;
							break;

						} else {
							Original = String::strdup8(Str->Get8());
							OldStrLen = String::strlen(Old);
							delete Str;
							Str = nullptr;
							Found = String::strstr(Original, Old);
						}
					}
				}

				return (Results);
			}

			static
			String	*
			Replace16(const String & StrObject,
			          const char16_t * Old,
			          const char16_t * New,
			          size_t HowMany)
			{
				String		*	Results = nullptr;

				// Current8BitCharset, OldStr, and NewStr
				// are all in the same charset.
				//
				const char16_t	*	Original = StrObject.Get16();
				const char16_t	*	Found = String::strstr(Original, Old);

				String		*	Str = nullptr;
				size_t			OldStrLen = String::strlen(Old);
				size_t			Len;

				if (Found == nullptr) {
					Results = new String(Original);

				} else {
					while (Found != nullptr) {
						Len = Found - Original;

						Str = new String();

						if (Len > 0) {
							Str->Append(Original, Len);
						}

						Str->Append(New);
						Found += OldStrLen;
						Str->Append(Found);

						if (HowMany-- == 0) {
							Results = Str;
							break;

						} else {
							Original = String::strdup16(Str->Get32());
							OldStrLen = String::strlen(Old);
							delete Str;
							Str = nullptr;
							Found = String::strstr(Original, Old);
						}
					}
				}

				return (Results);
			}

			static
			String	*
			Replace32(const String & StrObject,
			          const char32_t * Old,
			          const char32_t * New,
			          size_t HowMany)
			{
				String		*	Results = nullptr;

				// Current8BitCharset, OldStr, and NewStr
				// are all in the same charset.
				//
				const char32_t	*	Original = StrObject.Get32();
				const char32_t	*	Found = String::strstr(Original, Old);

				String		*	Str = nullptr;
				size_t			OldStrLen = String::strlen(Old);
				size_t			Len;

				if (Found == nullptr) {
					Results = new String(Original);

				} else {
					while (Found != nullptr) {
						Len = Found - Original;

						Str = new String();

						if (Len > 0) {
							Str->Append(Original, Len);
						}

						Str->Append(New);
						Found += OldStrLen;
						Str->Append(Found);

						if (HowMany-- == 0) {
							Results = Str;
							break;

						} else {
							Original = String::strdup32(Str->Get32());
							OldStrLen = String::strlen(Old);
							delete Str;
							Str = nullptr;
							Found = String::strstr(Original, Old);
						}
					}
				}

				return (Results);
			}

			static
			String	*
			ReplaceW(const String & StrObject,
			         const wchar_t * Old,
			         const wchar_t * New,
			         size_t HowMany)
			{
				String		*	Results = nullptr;

				// Current8BitCharset, OldStr, and NewStr
				// are all in the same charset.
				//
				const wchar_t	*	Original = StrObject.GetW();
				const wchar_t	*	Found = String::strstr(Original, Old);

				String		*	Str = nullptr;
				size_t			OldStrLen = String::strlen(Old);
				size_t			Len;

				if (Found == nullptr) {
					Results = new String(Original);

				} else {
					while (Found != nullptr) {
						Len = Found - Original;

						Str = new String();

						if (Len > 0) {
							Str->Append(Original, Len);
						}

						Str->Append(New);
						Found += OldStrLen;
						Str->Append(Found);

						if (HowMany-- == 0) {
							Results = Str;
							break;

						} else {
							Original = String::strdupW(Str->GetW());
							OldStrLen = String::strlen(Old);
							delete Str;
							Str = nullptr;
							Found = String::strstr(Original, Old);
						}
					}
				}

				return (Results);
			}

			static
			String	*
			Convert(const String	&	TheString,
			        const void	*	OldString,
			        CharacterUnitWidth_e	OldStringWidth,
			        const void	*	NewString,
			        CharacterUnitWidth_e	NewStringWidth,
			        size_t			HowMany)

			{
				String		*	Results = nullptr;

				char		*	Old8 = nullptr;
				char16_t	*	Old16 = nullptr;
				char32_t	*	Old32 = nullptr;
				wchar_t		*	OldW = nullptr;
				char		*	New8 = nullptr;
				char16_t	*	New16 = nullptr;
				char32_t	*	New32 = nullptr;
				wchar_t		*	NewW = nullptr;

				switch (TheString.InputWidth()) {

					case Is8Bit_t:
						switch (OldStringWidth) {

							case Is8Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 8 8 8
										//
										{
											if (String::Charset8To8(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset8To8(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is16Bit_t:
										// 8 8 16
										//
										{
											if (String::Charset8To8(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset16To8(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is32Bit_t:
										// 8 8 32
										//
										{
											if (String::Charset8To8(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset32To8(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsWBit_t:
										// 8 8 W
										//
										{
											if (String::Charset8To8(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::CharsetWTo8(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is16Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 8 16 8
										//
										{
											if (String::Charset16To8(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset8To8(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is16Bit_t:
										// 8 16 16
										//
										{
											if (String::Charset16To8(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset16To8(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is32Bit_t:
										// 8 16 32
										//
										{
											if (String::Charset16To8(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset32To8(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsWBit_t:
										// 8 16 W
										//
										{
											if (String::Charset16To8(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::CharsetWTo8(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is32Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 8 32 8
										//
										{
											if (String::Charset32To8(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset8To8(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is16Bit_t:
										// 8 32 16
										//
										{
											if (String::Charset32To8(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset16To8(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is32Bit_t:
										// 8 32 32
										//
										{
											if (String::Charset32To8(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::Charset32To8(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsWBit_t:
										// 8 32 W
										//
										{
											if (String::Charset32To8(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         Old8)) {
												if (String::CharsetWTo8(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsWBit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 8 W 8
										//
										{
											if (String::CharsetWTo8(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset8To8(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is16Bit_t:
										// 8 W 16
										//
										{
											if (String::CharsetWTo8(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset16To8(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case Is32Bit_t:
										// 8 W 32
										//
										{
											if (String::CharsetWTo8(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::Charset32To8(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsWBit_t:
										// 8 W W
										//
										{
											if (String::CharsetWTo8(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        Old8)) {
												if (String::CharsetWTo8(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        New8)) {
													Results = Replace8(TheString, Old8, New8, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsUnknownBit_t:
										// 8 W ?
										/*EMPTY*/
										break;
								}

								break;

							case IsUnknownBit_t:
								// 8 ? (dont care now)
								/*EMPTY*/
								break;
						}

						break;

					case Is16Bit_t:
						switch (OldStringWidth) {

							case Is8Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 16 8 8
										//
										{
											if (String::Charset8To16(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old16)) {
												if (String::Charset8To16(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is16Bit_t:
										// 16 8 16
										//
										{
											if (String::Charset8To16(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old16)) {
												if (String::Charset16To16(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is32Bit_t:
										// 16 8 32
										//
										{
											if (String::Charset8To16(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old16)) {
												if (String::Charset32To16(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New8;
												}

												delete Old8;
											}
										}
										break;

									case IsWBit_t:
										// 16 8 W
										//
										{
											if (String::Charset8To16(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old16)) {
												if (String::CharsetWTo16(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is16Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 16 16 8
										//
										{
											if (String::Charset16To16(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset8To16(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is16Bit_t:
										// 16 16 16
										//
										{
											if (String::Charset16To16(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset16To16(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is32Bit_t:
										// 16 16 32
										//
										{
											if (String::Charset16To16(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset32To16(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case IsWBit_t:
										// 16 16 W
										//
										{
											if (String::Charset16To16(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::CharsetWTo16(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is32Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 16 32 8
										//
										{
											if (String::Charset32To16(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset8To16(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is16Bit_t:
										// 16 32 16
										//
										{
											if (String::Charset32To16(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset16To16(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case Is32Bit_t:
										// 16 32 32
										//
										{
											if (String::Charset32To16(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::Charset32To16(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case IsWBit_t:
										// 16 32 W
										//
										{
											if (String::Charset32To16(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old16)) {
												if (String::CharsetWTo16(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New16)) {
													Results = Replace16(TheString, Old16, New16, HowMany);
													delete New16;
												}

												delete Old16;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsWBit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// W 32 8
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset8ToW(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is16Bit_t:
										// W 32 16
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset16ToW(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is32Bit_t:
										// W 32 32
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset32ToW(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsWBit_t:
										// W 32 W
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::CharsetWToW(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsUnknownBit_t:
								/*EMPTY*/
								break;
						}

						break;

					case IsWBit_t:
						switch (OldStringWidth) {

							case Is8Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// W 8 8
										//
										{
											if (String::Charset8ToW(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset8ToW(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is16Bit_t:
										// W 8 16
										//
										{
											if (String::Charset8ToW(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset16ToW(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is32Bit_t:
										// W 8 32
										//
										{
											if (String::Charset8ToW(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset32ToW(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsWBit_t:
										// W 8 W
										//
										{
											if (String::Charset8ToW(Current8BitCharset,
											                        (char *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::CharsetWToW(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is16Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// W 16 8
										//
										{
											if (String::Charset16ToW(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset8ToW(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is16Bit_t:
										// W 16 16
										//
										{
											if (String::Charset16ToW(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset16ToW(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is32Bit_t:
										// W 16 32
										//
										{
											if (String::Charset16ToW(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset32ToW(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsWBit_t:
										// W 16 W
										//
										{
											if (String::Charset16ToW(Current16BitCharset,
											                         (char16_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::CharsetWToW(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is32Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// W 32 8
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset8ToW(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete Old16;
											}
										}
										break;

									case Is16Bit_t:
										// W 32 16
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset16ToW(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is32Bit_t:
										// W 32 32
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::Charset32ToW(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsWBit_t:
										// W 32 W
										//
										{
											if (String::Charset32ToW(Current32BitCharset,
											                         (char32_t *)OldString,
											                         TheString.InputCharset(),
											                         OldW)) {
												if (String::CharsetWToW(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsWBit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// W W 8
										//
										{
											if (String::CharsetWToW(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset8ToW(Current8BitCharset,
												                        (char *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete Old16;
											}
										}
										break;

									case Is16Bit_t:
										// W W 16
										//
										{
											if (String::CharsetWToW(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset16ToW(Current16BitCharset,
												                         (char16_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case Is32Bit_t:
										// W W 32
										//
										{
											if (String::CharsetWToW(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::Charset32ToW(Current32BitCharset,
												                         (char32_t *)NewString,
												                         TheString.InputCharset(),
												                         NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsWBit_t:
										// W W W
										//
										{
											if (String::CharsetWToW(CurrentWBitCharset,
											                        (wchar_t *)OldString,
											                        TheString.InputCharset(),
											                        OldW)) {
												if (String::CharsetWToW(CurrentWBitCharset,
												                        (wchar_t *)NewString,
												                        TheString.InputCharset(),
												                        NewW)) {
													Results = ReplaceW(TheString, OldW, NewW, HowMany);
													delete NewW;
												}

												delete OldW;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsUnknownBit_t:
								/*EMPTY*/
								break;
						}

						break;

					case Is32Bit_t:
						switch (OldStringWidth) {

							case Is8Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 32 8 8
										//
										{
											if (String::Charset8To32(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset8To32(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is16Bit_t:
										// 32 8 16
										//
										{
											if (String::Charset8To32(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset16To32(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is32Bit_t:
										// 32 8 32
										//
										{
											if (String::Charset8To32(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset32To32(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsWBit_t:
										// 32 8 W
										//
										{
											if (String::Charset8To32(Current8BitCharset,
											                         (char *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::CharsetWTo32(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is16Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 32 16 8
										//
										{
											if (String::Charset16To32(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset8To32(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is16Bit_t:
										// 32 16 16
										//
										{
											if (String::Charset16To32(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset16To32(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is32Bit_t:
										// 32 16 32
										//
										{
											if (String::Charset16To32(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset32To32(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsWBit_t:
										// 32 16 W
										//
										{
											if (String::Charset16To32(Current16BitCharset,
											                          (char16_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::CharsetWTo32(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case Is32Bit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 32 32 8
										//
										{
											if (String::Charset32To32(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset8To32(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is16Bit_t:
										// 32 32 16
										//
										{
											if (String::Charset32To32(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset16To32(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is32Bit_t:
										// 32 32 32
										//
										{
											if (String::Charset32To32(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::Charset32To32(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsWBit_t:
										// 32 32 W
										//
										{
											if (String::Charset32To32(Current32BitCharset,
											                          (char32_t *)OldString,
											                          TheString.InputCharset(),
											                          Old32)) {
												if (String::CharsetWTo32(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsWBit_t:
								switch (NewStringWidth) {

									case Is8Bit_t:
										// 32 W 8
										//
										{
											if (String::CharsetWTo32(CurrentWBitCharset,
											                         (wchar_t *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset8To32(Current8BitCharset,
												                         (char *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is16Bit_t:
										// 32 W 16
										//
										{
											if (String::CharsetWTo32(CurrentWBitCharset,
											                         (wchar_t *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset16To32(Current16BitCharset,
												                          (char16_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case Is32Bit_t:
										// 32 W 32
										//
										{
											if (String::CharsetWTo32(CurrentWBitCharset,
											                         (wchar_t *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::Charset32To32(Current32BitCharset,
												                          (char32_t *)NewString,
												                          TheString.InputCharset(),
												                          New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsWBit_t:
										// 32 W W
										//
										{
											if (String::CharsetWTo32(CurrentWBitCharset,
											                         (wchar_t *)OldString,
											                         TheString.InputCharset(),
											                         Old32)) {
												if (String::CharsetWTo32(CurrentWBitCharset,
												                         (wchar_t *)NewString,
												                         TheString.InputCharset(),
												                         New32)) {
													Results = Replace32(TheString, Old32, New32, HowMany);
													delete New32;
												}

												delete Old32;
											}
										}
										break;

									case IsUnknownBit_t:
										/*EMPTY*/
										break;
								}

								break;

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

						}

						break;

					case IsUnknownBit_t:
						/*EMPTY*/
						break;
				} // End InputWidth()

				return (Results);
			}

			String	*
			String::Replace(const char * OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is8Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char * OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is8Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char * OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is8Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char * OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is8Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char * OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				return (Replace(OldStr, NewStr.c_str(), HowMany));
			}

			String	*
			String::Replace(const char * OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				return (Replace(OldStr, NewStr.c_str(), HowMany));
			}

			String	*
			String::Replace(const char * OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				return (Replace(OldStr, NewStr.c_str(), HowMany));
			}

			String	*
			String::Replace(const char * OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				return (Replace(OldStr, NewStr.c_str(), HowMany));
			}

			String	*
			String::Replace(const char * OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				if (OldStr != nullptr) {
					switch (NewStr.InputWidth()) {

						case IsUnknownBit_t:

						/*FALLTHRU*/
						case Is8Bit_t:
							Results = Convert(*this,
							                  OldStr, Is8Bit_t,
							                  NewStr.Get8(), Is8Bit_t,
							                  HowMany);
							break;

						case Is16Bit_t:
							Results = Convert(*this,
							                  OldStr, Is8Bit_t,
							                  NewStr.Get16(), Is16Bit_t,
							                  HowMany);
							break;

						case Is32Bit_t:
							Results = Convert(*this,
							                  OldStr, Is8Bit_t,
							                  NewStr.Get32(), Is32Bit_t,
							                  HowMany);
							break;

						case IsWBit_t:
							Results = Convert(*this,
							                  OldStr, Is8Bit_t,
							                  NewStr.GetW(), IsWBit_t,
							                  HowMany);
							break;
					}
				}

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr.c_str(), Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr.c_str(), Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr.c_str(), Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is16Bit_t,
				                              NewStr.c_str(), IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char16_t * OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (NewStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr, Is16Bit_t,
						                  NewStr.Get8(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr, Is16Bit_t,
						                  NewStr.Get16(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr, Is16Bit_t,
						                  NewStr.Get32(), Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr, Is16Bit_t,
						                  NewStr.GetW(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr.c_str(), Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr.c_str(), Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr.c_str(), Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr, Is32Bit_t,
				                              NewStr.c_str(), IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const char32_t * OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (NewStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr, Is32Bit_t,
						                  NewStr.Get8(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr, Is32Bit_t,
						                  NewStr.Get16(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr, Is32Bit_t,
						                  NewStr.Get32(), Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr, Is32Bit_t,
						                  NewStr.GetW(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr.c_str(), Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr.c_str(), Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr.c_str(), Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is8Bit_t,
				                              NewStr.c_str(), IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::string & OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (NewStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is8Bit_t,
						                  NewStr.Get8(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is8Bit_t,
						                  NewStr.Get16(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is8Bit_t,
						                  NewStr.Get32(), Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is8Bit_t,
						                  NewStr.GetW(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr.c_str(), Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr.c_str(), Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr.c_str(), Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr.c_str(), IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (NewStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is16Bit_t,
						                  NewStr.Get8(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is16Bit_t,
						                  NewStr.Get16(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is16Bit_t,
						                  NewStr.Get32(), Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is16Bit_t,
						                  NewStr.GetW(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u16string & OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is16Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr, Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr, Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr, Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr, IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr.c_str(), Is8Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr.c_str(), Is16Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr.c_str(), Is32Bit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = Convert(*this,
				                              OldStr.c_str(), Is32Bit_t,
				                              NewStr.c_str(), IsWBit_t,
				                              HowMany);

				return (Results);
			}

			String	*
			String::Replace(const std::u32string & OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (NewStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is32Bit_t,
						                  NewStr.Get8(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is32Bit_t,
						                  NewStr.Get16(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is32Bit_t,
						                  NewStr.Get32(), Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.c_str(), Is32Bit_t,
						                  NewStr.GetW(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const char * NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr, Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr, Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr, Is8Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr, Is8Bit_t,
						                  HowMany);
						break;

				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const char16_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr, Is16Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr, Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr, Is16Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr, Is16Bit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const char32_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr, Is32Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr, Is32Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr, Is32Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr, Is32Bit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const wchar_t * NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr, IsWBit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr, IsWBit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr, IsWBit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr, IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const std::string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr.c_str(), Is8Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr.c_str(), Is8Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr.c_str(), Is8Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr.c_str(), Is8Bit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const std::u16string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;
				}


				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const std::u32string & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr.c_str(), Is32Bit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr.c_str(), Is16Bit_t,
						                  HowMany);
						break;

				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const std::wstring & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = Convert(*this,
						                  OldStr.Get8(), Is8Bit_t,
						                  NewStr.c_str(), IsWBit_t,
						                  HowMany);
						break;

					case Is16Bit_t:
						Results = Convert(*this,
						                  OldStr.Get16(), Is16Bit_t,
						                  NewStr.c_str(), IsWBit_t,
						                  HowMany);
						break;

					case Is32Bit_t:
						Results = Convert(*this,
						                  OldStr.Get32(), Is32Bit_t,
						                  NewStr.c_str(), IsWBit_t,
						                  HowMany);
						break;

					case IsWBit_t:
						Results = Convert(*this,
						                  OldStr.GetW(), IsWBit_t,
						                  NewStr.c_str(), IsWBit_t,
						                  HowMany);
						break;
				}

				return (Results);
			}

			String	*
			String::Replace(const String & OldStr,
			                const String & NewStr,
			                size_t HowMany)
			{
				String	*	Results = nullptr;

				switch (OldStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:

						switch (NewStr.InputWidth()) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = Convert(*this,
								                  OldStr.Get8(), Is8Bit_t,
								                  NewStr.Get8(), Is8Bit_t,
								                  HowMany);
								break;

							case Is16Bit_t:
								Results = Convert(*this,
								                  OldStr.Get8(), Is8Bit_t,
								                  NewStr.Get16(), Is16Bit_t,
								                  HowMany);
								break;

							case Is32Bit_t:
								Results = Convert(*this,
								                  OldStr.Get8(), Is8Bit_t,
								                  NewStr.Get32(), Is32Bit_t,
								                  HowMany);
								break;

							case IsWBit_t:
								Results = Convert(*this,
								                  OldStr.Get8(), Is8Bit_t,
								                  NewStr.GetW(), IsWBit_t,
								                  HowMany);
								break;
						}

						break;

					case Is16Bit_t:
						switch (NewStr.InputWidth()) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = Convert(*this,
								                  OldStr.Get16(), Is16Bit_t,
								                  NewStr.Get8(), Is8Bit_t,
								                  HowMany);
								break;

							case Is16Bit_t:
								Results = Convert(*this,
								                  OldStr.Get16(), Is16Bit_t,
								                  NewStr.Get16(), Is16Bit_t,
								                  HowMany);
								break;

							case Is32Bit_t:
								Results = Convert(*this,
								                  OldStr.Get16(), Is16Bit_t,
								                  NewStr.Get32(), Is32Bit_t,
								                  HowMany);
								break;

							case IsWBit_t:
								Results = Convert(*this,
								                  OldStr.Get16(), Is16Bit_t,
								                  NewStr.GetW(), IsWBit_t,
								                  HowMany);
								break;
						}

						break;

					case Is32Bit_t:
						switch (NewStr.InputWidth()) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = Convert(*this,
								                  OldStr.Get32(), Is32Bit_t,
								                  NewStr.Get8(), Is8Bit_t,
								                  HowMany);
								break;

							case Is16Bit_t:
								Results = Convert(*this,
								                  OldStr.Get32(), Is32Bit_t,
								                  NewStr.Get16(), Is16Bit_t,
								                  HowMany);
								break;

							case Is32Bit_t:
								Results = Convert(*this,
								                  OldStr.Get32(), Is32Bit_t,
								                  NewStr.Get32(), Is32Bit_t,
								                  HowMany);
								break;

							case IsWBit_t:
								Results = Convert(*this,
								                  OldStr.Get32(), Is32Bit_t,
								                  NewStr.GetW(), IsWBit_t,
								                  HowMany);
								break;
						}

						break;

					case IsWBit_t:
						switch (NewStr.InputWidth()) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = Convert(*this,
								                  OldStr.GetW(), IsWBit_t,
								                  NewStr.Get8(), Is8Bit_t,
								                  HowMany);
								break;

							case Is16Bit_t:
								Results = Convert(*this,
								                  OldStr.GetW(), IsWBit_t,
								                  NewStr.Get16(), Is16Bit_t,
								                  HowMany);
								break;

							case Is32Bit_t:
								Results = Convert(*this,
								                  OldStr.GetW(), IsWBit_t,
								                  NewStr.Get32(), Is32Bit_t,
								                  HowMany);
								break;

							case IsWBit_t:
								Results = Convert(*this,
								                  OldStr.GetW(), IsWBit_t,
								                  NewStr.GetW(), IsWBit_t,
								                  HowMany);
								break;
						}

						break;
				}

				return (Results);
			}

		}
	}
}
