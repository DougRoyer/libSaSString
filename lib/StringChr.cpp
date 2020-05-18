//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2015,2019 Douglas Mark Royer, All Rights Reserved.
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
#include <SaS/String/StringCache.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			String::const_iterator	&
			String::strchr(const char * const ToFind) const
			{
				const_iterator	&	Results = cend();

				if (_ROString) {
				} else {
					std::vector<StringSeg *>::const_iterator	sIt;

					const_iterator	it = cbegin();


					const char *	In8 = Get8();

					while (it != cend()) {
						if (*it == ToFind) {
							Results = it;
							break;
						}

						it++;
					}

					return (Results);
				}

				String::const_iterator	&
				String::strchr(const char16_t * const ToFind) const {
					const_iterator		&	Results = cend();

					const_iterator		it = cbegin();
					size_t		cWidth = 0;
					int		Cmp = 0;

					while (it != cend()) {

						switch (_InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	Out = nullptr;

									if (Charset16To8(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str8(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is16Bit_t: {
									char16_t	*	Out = nullptr;

									if (Charset16To16(nullptr,
									                  ToFind,
									                  _InputCharset,
									                  Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str16(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is32Bit_t: {
									char32_t	*	Out = nullptr;

									if (Charset16To32(nullptr,
									                  ToFind,
									                  _InputCharset,
									                  Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str32(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case IsWBit_t: {
									wchar_t	*	Out = nullptr;

									if (Charset16ToW(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.strW(), Out, cWidth);
									}

									delete Out;
								}
								break;
						}

						if (Cmp == 0) {
							Results = it;
							break;
						}

						it++;
					}

					return (Results);
				}

				String::const_iterator	&
				String::strchr(const char32_t * const ToFind) const {
					const_iterator		&	Results = cend();

					const_iterator		it = cbegin();
					size_t		cWidth = 0;
					int		Cmp = 0;

					while (it != cend()) {

						switch (_InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	Out = nullptr;

									if (Charset32To8(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str8(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is16Bit_t: {
									char16_t	*	Out = nullptr;

									if (Charset32To16(nullptr,
									                  ToFind,
									                  _InputCharset,
									                  Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str16(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is32Bit_t: {
									char32_t	*	Out = nullptr;

									if (Charset32To32(nullptr,
									                  ToFind,
									                  _InputCharset,
									                  Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str32(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case IsWBit_t: {
									wchar_t	*	Out = nullptr;

									if (Charset32ToW(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.strW(), Out, cWidth);
									}

									delete Out;
								}
								break;
						}

						if (Cmp == 0) {
							Results = it;
							break;
						}

						it++;
					}

					return (Results);
				}

				String::const_iterator	&
				String::strchr(const wchar_t * const ToFind) const {
					const_iterator		&	Results = cend();

					const_iterator		it = cbegin();
					size_t		cWidth = 0;
					int		Cmp = 0;

					while (it != cend()) {

						switch (_InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	Out = nullptr;

									if (CharsetWTo8(nullptr,
									                ToFind,
									                _InputCharset,
									                Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str8(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is16Bit_t: {
									char16_t	*	Out = nullptr;

									if (CharsetWTo16(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str16(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case Is32Bit_t: {
									char32_t	*	Out = nullptr;

									if (CharsetWTo32(nullptr,
									                 ToFind,
									                 _InputCharset,
									                 Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.str32(), Out, cWidth);
									}

									delete Out;
								}
								break;

							case IsWBit_t: {
									wchar_t	*	Out = nullptr;

									if (CharsetWToW(nullptr,
									                ToFind,
									                _InputCharset,
									                Out)) {
										cWidth = CharacterUnits(Out);
										Cmp = memcmp(it.strW(), Out, cWidth);
									}

									delete Out;
								}
								break;
						}

						if (Cmp == 0) {
							Results = it;
							break;
						}

						it++;
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr, char CharToFind) {
					char		*	Results = nullptr;

					if (InStr != nullptr) {
						const char	*	Ptr = InStr;

						while (*Ptr != 0) {
							if (*Ptr == CharToFind) {
								Results = (char *)Ptr;
								break;
							}

							Ptr++;
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               const char * const CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							size_t	Width = CharacterUnits(CharToFind);
							size_t	Offset;
							size_t	Len = strlen(CharToFind);

							for (Offset = 0; Offset < (Len - Width); Offset++) {
								if (memcmp(&InStr[Offset], CharToFind, Width) == 0) {
									Results = (char *)&InStr[Offset];
									break;
								}
							}
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               char16_t CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr) {
						char	*	Out = nullptr;
						char16_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset16To8(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               const char16_t * const CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char	*	Out = nullptr;

							if (Charset16To8(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               char32_t CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr) {
						char	*	Out = nullptr;
						char32_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset32To8(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               const char32_t * const CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char	*	Out = nullptr;

							if (Charset32To8(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               wchar_t CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr) {
						char	*	Out = nullptr;
						wchar_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (CharsetWTo8(nullptr,
						                Tmp,
						                nullptr,
						                Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char	*
				String::strchr(const char * const InStr,
				               const wchar_t * const CharToFind) {
					char	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char	*	Out = nullptr;

							if (CharsetWTo8(nullptr,
							                CharToFind,
							                nullptr,
							                Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               char CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char16_t	*	Out = nullptr;
						char		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset8To16(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               const char * const CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char16_t	*	Out = nullptr;

							if (Charset8To16(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char16_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               char16_t CharToFind) {
					char16_t		*	Results = nullptr;

					if (InStr != nullptr) {
						const char16_t	*	Ptr = InStr;

						while (*Ptr != 0) {
							if (*Ptr == CharToFind) {
								Results = (char16_t *)Ptr;
								break;
							}

							Ptr++;
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               const char16_t * const CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							size_t	Width = CharacterUnits(CharToFind);
							size_t	Offset;
							size_t	Len = strlen(CharToFind);

							for (Offset = 0; Offset < (Len - Width); Offset++) {
								if (memcmp(&InStr[Offset], CharToFind, Width) == 0) {
									Results = (char16_t *)&InStr[Offset];
									break;
								}
							}
						}
					}

					return (Results);
				}
				char16_t	*
				String::strchr(const char16_t * const InStr,
				               char32_t CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char16_t	*	Out = nullptr;
						char32_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset32To16(nullptr,
						                  Tmp,
						                  nullptr,
						                  Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               const char32_t * const CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char16_t	*	Out = nullptr;

							if (Charset32To16(nullptr,
							                  CharToFind,
							                  nullptr,
							                  Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char16_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               wchar_t CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char16_t	*	Out = nullptr;
						wchar_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (CharsetWTo16(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out);
							delete Out;
						}
					}

					return (Results);
				}

				char16_t	*
				String::strchr(const char16_t * const InStr,
				               const wchar_t * const CharToFind) {
					char16_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char16_t	*	Out = nullptr;

							if (CharsetWTo16(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char16_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               char CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char32_t	*	Out = nullptr;
						char		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset8To32(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               const char * const CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char32_t	*	Out = nullptr;

							if (Charset8To32(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char32_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               char16_t CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char32_t	*	Out = nullptr;
						char16_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset16To32(nullptr,
						                  Tmp,
						                  nullptr,
						                  Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               const char16_t * const CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char32_t	*	Out = nullptr;

							if (Charset16To32(nullptr,
							                  CharToFind,
							                  nullptr,
							                  Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char32_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               char32_t CharToFind) {
					char32_t		*	Results = nullptr;

					if (InStr != nullptr) {
						const char32_t	*	Ptr = InStr;

						while (*Ptr != 0) {
							if (*Ptr == CharToFind) {
								Results = (char32_t *)Ptr;
								break;
							}

							Ptr++;
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               const char32_t * const CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						Results = strchr(InStr, CharToFind[0]);
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               wchar_t CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr) {
						char32_t	*	Out = nullptr;
						wchar_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (CharsetWTo32(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				char32_t	*
				String::strchr(const char32_t * const InStr,
				               const wchar_t * const CharToFind) {
					char32_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							char32_t	*	Out = nullptr;

							if (CharsetWTo32(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (char32_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr, char CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr) {
						wchar_t	*	Out = nullptr;
						char		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset8ToW(nullptr,
						                Tmp,
						                nullptr,
						                Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               const char * const CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							wchar_t	*	Out = nullptr;

							if (Charset8ToW(nullptr,
							                CharToFind,
							                nullptr,
							                Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (wchar_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               char16_t CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr) {
						wchar_t	*	Out = nullptr;
						char16_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset16ToW(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               const char16_t * const CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							wchar_t	*	Out = nullptr;

							if (Charset16ToW(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (wchar_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               char32_t CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr) {
						wchar_t	*	Out = nullptr;
						char32_t		Tmp[2];

						Tmp[0] = CharToFind;
						Tmp[1] = 0;

						if (Charset32ToW(nullptr,
						                 Tmp,
						                 nullptr,
						                 Out)) {
							Results = strchr(InStr, Out[0]);
							delete Out;
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               const char32_t * const CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							wchar_t	*	Out = nullptr;

							if (Charset32ToW(nullptr,
							                 CharToFind,
							                 nullptr,
							                 Out)) {

								size_t	Width = CharacterUnits(Out);
								size_t	Offset;
								size_t	Len = strlen(Out);

								for (Offset = 0; Offset < (Len - Width); Offset++) {
									if (memcmp(&InStr[Offset], Out, Width) == 0) {
										Results = (wchar_t *)&InStr[Offset];
										break;
									}
								}

								delete Out;
							}
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               wchar_t CharToFind) {
					wchar_t		*	Results = nullptr;

					if (InStr != nullptr) {
						const wchar_t	*	Ptr = InStr;

						while (*Ptr != 0) {
							if (*Ptr == CharToFind) {
								Results = (wchar_t *)Ptr;
								break;
							}

							Ptr++;
						}
					}

					return (Results);
				}

				wchar_t	*
				String::strchr(const wchar_t * const InStr,
				               const wchar_t * const CharToFind) {
					wchar_t	*	Results = nullptr;

					if (InStr != nullptr && CharToFind != nullptr) {
						if (*CharToFind != 0) {
							size_t	Width = CharacterUnits(CharToFind);
							size_t	Offset;
							size_t	Len = strlen(CharToFind);

							for (Offset = 0; Offset < (Len - Width); Offset++) {
								if (memcmp(&InStr[Offset], CharToFind, Width) == 0) {
									Results = (wchar_t *)&InStr[Offset];
									break;
								}
							}
						}
					}

					return (Results);
				}

			}
		}
	}
