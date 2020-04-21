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

			/*STRCMP*/
			int
			String::strcmp(const char * const One,
			               const char * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					Results = ::strcmp(One, Two);
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const char16_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char * TwoStr = nullptr;

					if (String::Charset16To8(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = ::strcmp(One, TwoStr);
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const char32_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char * TwoStr = nullptr;

					if (String::Charset32To8(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = ::strcmp(One, TwoStr);
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const wchar_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char * TwoStr = nullptr;

					if (String::CharsetWTo8(nullptr,
					                        Two,
					                        nullptr,
					                        TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = ::strcmp(One, TwoStr);
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const String & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t	Len1 = strlen(One);
					size_t	Len2 = strlen(Two.Get8());

					if (Len1 < Len2) {
						Results = -1;

					} else if (Len1 > Len2) {
						Results = 1;

					} else {
						// Lengths equal.
						//
						if (!Two.IsReadOnly()) {
							Results = ::strcmp(One, Two.Get8());

						} else {
							ROString	RO(Two);

							Results = String::strcmp(One, RO);
						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const ROString & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t		OneLen = strlen(One);
					size_t		TwoLen = Two.Length();

					if (OneLen < TwoLen) {
						Results = -1;

					} else if (TwoLen > OneLen) {
						Results = 1;

					} else {
						// Length is equal
						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		*	OneStr = nullptr;

									if (Charset8To8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t		*	OneStr = nullptr;

									if (Charset8To16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().str16(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t		*	OneStr = nullptr;

									if (Charset8To32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().str32(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	OneStr = nullptr;

									if (Charset8ToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().strW(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const ROString & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t		OneLen = strlen(One);
					size_t		TwoLen = Two.Length();

					if (OneLen < TwoLen) {
						Results = -1;

					} else if (TwoLen < OneLen) {
						Results = 1;

					} else {
						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		*	OneStr = nullptr;

									if (Charset16To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().str8(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t		*	OneStr = nullptr;

									if (Charset16To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t		*	OneStr = nullptr;

									if (Charset16To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	OneStr = nullptr;

									if (Charset16ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().strW(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const ROString & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t	OneLen = strlen(One);
					size_t	TwoLen = Two.Length();

					if (OneLen < TwoLen) {
						Results = -1;

					} else if (TwoLen < OneLen) {
						Results = 1;

					} else {
						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		*	OneStr = nullptr;

									if (Charset32To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr,
										                  Two.cbegin().str8(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t		*	OneStr = nullptr;

									if (Charset32To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t		*	OneStr = nullptr;

									if (Charset32To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	OneStr = nullptr;

									if (Charset32ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().strW(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const ROString & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t	OneLen = strlen(One);
					size_t	TwoLen = Two.Length();

					if (OneLen < TwoLen) {
						Results = -1;

					} else if (TwoLen < OneLen) {
						Results = 1;

					} else {
						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		*	OneStr = nullptr;

									if (CharsetWTo8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t		*	OneStr = nullptr;

									if (CharsetWTo16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t		*	OneStr = nullptr;

									if (CharsetWTo32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	OneStr = nullptr;

									if (CharsetWToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().strW(),
										                  Two.Length());
										delete OneStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const std::string & Two)
			{
				int		Results = ::strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const std::u16string & Two)
			{
				int		Results = strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const std::u32string & Two)
			{
				int		Results = strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char * const One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char16_t * const One,
			               const char * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char16_t * TwoStr = nullptr;

					if (String::Charset8To16(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const char16_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					size_t	Len1 = strlen(One);
					size_t	Len2 = strlen(Two);

					if (Len1 < Len2) {
						Results = -1;

					} else if (Len1 > Len2) {
						Results = 1;

					} else {
						Results = memcmp(One, Two, Len1 * sizeof(char16_t));
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const char32_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char16_t * TwoStr = nullptr;

					if (String::Charset32To16(nullptr,
					                          Two,
					                          nullptr,
					                          TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const wchar_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char16_t * TwoStr = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const std::string & Two)
			{
				int		Results = strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const std::u16string & Two)
			{
				int		Results = strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const std::u32string & Two)
			{
				int		Results = strcmp(One, Two.c_str());

				return (Results);
			}

			int
			String::strcmp(const char16_t * const One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char16_t * const One,
			               const String & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					if (Two.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(One, RO);

					} else {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset16To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strcmp(OneStr, Two.Get8());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset16To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strcmp(OneStr, Two.Get16());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset16To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strcmp(OneStr, Two.Get32());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset16ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strcmp(OneStr, Two.GetW());
										delete OneStr;
									}
								}
								break;
						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const char * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char32_t * TwoStr = nullptr;

					if (String::Charset8To32(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const char16_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char32_t * TwoStr = nullptr;

					if (String::Charset16To32(nullptr,
					                          Two,
					                          nullptr,
					                          TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const char32_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					size_t	Len1 = strlen(One);
					size_t	Len2 = strlen(Two);

					if (Len1 < Len2) {
						Results = -1;

					} else if (Len1 > Len2) {
						Results = 1;

					} else {
						Results = memcmp(One, Two, Len1 * sizeof(char32_t));
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const wchar_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					char32_t * TwoStr = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const char32_t * const One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char32_t * const One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char32_t * const One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char32_t * const One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const char32_t * const One,
			               const String & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					if (Two.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(One, RO);

					} else {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset32To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strcmp(OneStr, Two.Get8());
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset32To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strcmp(OneStr, Two.Get16());
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset32To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strcmp(OneStr, Two.Get32());
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset32ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strcmp(OneStr, Two.GetW());
										delete OneStr;
									}
								}
								break;
						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const char * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					wchar_t	* TwoStr = nullptr;

					if (String::Charset8ToW(nullptr,
					                        Two,
					                        nullptr,
					                        TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(wchar_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const char16_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					wchar_t	* TwoStr = nullptr;

					if (String::Charset16ToW(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(wchar_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const char32_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					wchar_t	* TwoStr = nullptr;

					if (String::Charset32ToW(nullptr,
					                         Two,
					                         nullptr,
					                         TwoStr)) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(TwoStr);

						if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;

						} else {
							Results = memcmp(One, TwoStr, Len1 * sizeof(wchar_t));
						}

						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const wchar_t * const Two)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					Results = wcscmp(One, Two);
				}

				return (Results);
			}

			int
			String::strcmp(const wchar_t * const One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const wchar_t * const One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const wchar_t * const One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const wchar_t * const One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const wchar_t * const One,
			               const String & Two)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					if (Two.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(One, RO);

					} else {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		* OneStr = nullptr;

									if (String::CharsetWTo8(nullptr,
									                        One,
									                        nullptr,
									                        OneStr)) {

										size_t	Len1 = strlen(OneStr);
										size_t	Len2 = strlen(Two);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(OneStr, Two.Get8(), Len1);
										}

										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	* OneStr = nullptr;

									if (String::CharsetWTo16(nullptr,
									                         One,
									                         nullptr,
									                         OneStr)) {

										size_t	Len1 = strlen(OneStr);
										size_t	Len2 = strlen(Two);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(OneStr, Two.Get16(),
											                 Len1 * sizeof(char16_t));
										}

										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (String::CharsetWTo32(nullptr,
									                         One,
									                         nullptr,
									                         OneStr)) {

										size_t	Len1 = strlen(OneStr);
										size_t	Len2 = strlen(Two);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(OneStr, Two.Get32(),
											                 Len1 * sizeof(char32_t));
										}

										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	OneStr = nullptr;

									if (String::CharsetWToW(nullptr,
									                        One,
									                        nullptr,
									                        OneStr)) {

										size_t	Len1 = strlen(OneStr);
										size_t	Len2 = strlen(Two);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(OneStr, Two.GetW(),
											                 Len1 * sizeof(wchar_t));
										}

										delete OneStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const char * const Two)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					if (One.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(RO, Two);

					} else {

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		* TwoStr = nullptr;

									if (String::Charset8To8(nullptr,
									                        Two,
									                        nullptr,
									                        TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get8(), Two, Len1);
										}

										delete TwoStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	* TwoStr = nullptr;

									if (String::Charset8To16(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get16(), TwoStr,
											                 Len1 * sizeof(char16_t));
										}

										delete TwoStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	TwoStr = nullptr;

									if (String::Charset8To32(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get32(), TwoStr,
											                 Len1 * sizeof(char32_t));
										}

										delete TwoStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	TwoStr = nullptr;

									if (String::Charset8ToW(nullptr,
									                        Two,
									                        nullptr,
									                        TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.GetW(), TwoStr,
											                 Len1 * sizeof(wchar_t));
										}

										delete TwoStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const ROString & One,
			               const char * const Two)
			{
				int			Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {

					switch (One._RO->Width) {

						case IsUnknownBit_t:
							Results = -1;
							break;

						case Is8Bit_t: {
								char	*	TwoStr = nullptr;

								if (Charset8To8(nullptr,
								                Two,
								                One._RO->Charset,
								                TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One.cbegin().str8(), TwoStr, Len1);
									}

									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	TwoStr = nullptr;

								if (Charset8To16(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One.cbegin().str16(), TwoStr, Len1);
									}

									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset8To32(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One.cbegin().str32(), TwoStr, Len1);
									}

									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset8ToW(nullptr,
								                Two,
								                One._RO->Charset,
								                TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One.cbegin().strW(), TwoStr, Len1);
									}

									delete TwoStr;
								}
							}
							break;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const char16_t * const Two)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					if (One.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(RO, Two);

					} else {

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		* TwoStr = nullptr;

									if (String::Charset16To8(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One.Get8());
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get8(), TwoStr, Len1);
										}

										delete TwoStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	* TwoStr = nullptr;

									if (String::Charset16To16(nullptr,
									                          Two,
									                          nullptr,
									                          TwoStr)) {

										size_t	Len1 = strlen(One.Get16());
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get16(),
											                 TwoStr,
											                 Len1 * sizeof(char16_t));
										}

										delete TwoStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	TwoStr = nullptr;

									if (String::Charset16To32(nullptr,
									                          Two,
									                          nullptr,
									                          TwoStr)) {

										size_t	Len1 = strlen(One.Get32());
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get32(),
											                 TwoStr,
											                 Len1 * sizeof(char32_t));
										}

										delete TwoStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	TwoStr = nullptr;

									if (String::Charset16ToW(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One.GetW());
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.GetW(),
											                 TwoStr,
											                 Len1 * sizeof(wchar_t));
										}

										delete TwoStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const ROString & One,
			               const char16_t * const Two)
			{
				int			Results = 0;

				if (Two != nullptr) {

					switch (One._RO->Width) {

						case IsUnknownBit_t:
							Results = -1;
							break;

						case Is8Bit_t: {
								char	*	TwoStr = nullptr;

								if (Charset16To8(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	NotUsed = 0;
									size_t	Len1 = strlen(One.Get8(NotUsed));
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO8,
										                 TwoStr,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	TwoStr = nullptr;

								if (Charset16To16(nullptr,
								                  Two,
								                  One._RO->Charset,
								                  TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO16,
										                 TwoStr,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset16To32(nullptr,
								                  Two,
								                  One._RO->Charset,
								                  TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO32,
										                 TwoStr,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset16ToW(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.ROW,
										                 TwoStr,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;
					}

				} else {
					Results = 1;
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const char32_t * const Two)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					if (One.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(RO, Two);

					} else {

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		* TwoStr = nullptr;

									if (String::Charset32To8(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get8(), TwoStr, Len1);
										}

										delete TwoStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	* TwoStr = nullptr;

									if (String::Charset32To16(nullptr,
									                          Two,
									                          nullptr,
									                          TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get16(), TwoStr,
											                 Len1 * sizeof(char16_t));
										}

										delete TwoStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	TwoStr = nullptr;

									if (String::Charset32To32(nullptr,
									                          Two,
									                          nullptr,
									                          TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get32(), TwoStr,
											                 Len1 * sizeof(char32_t));
										}

										delete TwoStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	TwoStr = nullptr;

									if (String::Charset32ToW(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.GetW(), TwoStr,
											                 Len1 * sizeof(wchar_t));
										}

										delete TwoStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const ROString & One,
			               const char32_t * const Two)
			{
				int			Results = 0;

				if (Two != nullptr) {

					switch (One._RO->Width) {

						case IsUnknownBit_t:
							Results = -1;
							break;

						case Is8Bit_t: {
								char	*	TwoStr = nullptr;

								if (Charset32To8(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO8,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	TwoStr = nullptr;

								if (Charset32To16(nullptr,
								                  Two,
								                  One._RO->Charset,
								                  TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO16,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset32To32(nullptr,
								                  Two,
								                  One._RO->Charset,
								                  TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO32,
										                 Two,
										                 One._RO->StrUnits);

									}

									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset32ToW(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.ROW,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;
					}

				} else {
					Results = 1;
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const wchar_t * const Two)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					if (One.IsReadOnly()) {
						ROString	RO(Two);

						Results = strcmp(RO, Two);

					} else {

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char		* TwoStr = nullptr;

									if (String::CharsetWTo8(nullptr,
									                        Two,
									                        nullptr,
									                        TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get8(), TwoStr, Len1);
										}

										delete TwoStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	* TwoStr = nullptr;

									if (String::CharsetWTo16(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get16(), TwoStr,
											                 Len1 * sizeof(char16_t));
										}

										delete TwoStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	TwoStr = nullptr;

									if (String::CharsetWTo32(nullptr,
									                         Two,
									                         nullptr,
									                         TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.Get32(), TwoStr,
											                 Len1 * sizeof(char32_t));
										}

										delete TwoStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t		*	TwoStr = nullptr;

									if (String::CharsetWToW(nullptr,
									                        Two,
									                        nullptr,
									                        TwoStr)) {

										size_t	Len1 = strlen(One);
										size_t	Len2 = strlen(TwoStr);

										if (Len1 < Len2) {
											Results = -1;

										} else if (Len1 > Len2) {
											Results = 1;

										} else {
											Results = memcmp(One.GetW(), TwoStr,
											                 Len1 * sizeof(wchar_t));
										}

										delete TwoStr;
									}
								}
								break;

						}
					}
				}

				return (Results);
			}

			int
			String::strcmp(const ROString & One,
			               const wchar_t * const Two)
			{
				int			Results = 0;

				if (Two != nullptr) {

					switch (One._RO->Width) {

						case IsUnknownBit_t:
							Results = -1;
							break;

						case Is8Bit_t: {
								char	*	TwoStr = nullptr;

								if (CharsetWTo8(nullptr,
								                Two,
								                One._RO->Charset,
								                TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO8,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	TwoStr = nullptr;

								if (CharsetWTo16(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO16,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (CharsetWTo32(nullptr,
								                 Two,
								                 One._RO->Charset,
								                 TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.RO32,
										                 Two,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (CharsetWToW(nullptr,
								                Two,
								                One._RO->Charset,
								                TwoStr)) {

									size_t	Len1 = strlen(One);
									size_t	Len2 = strlen(TwoStr);

									if (Len1 < Len2) {
										Results = -1;

									} else if (Len1 > Len2) {
										Results = 1;

									} else {
										Results = memcmp(One._RO->Str.ROW,
										                 TwoStr,
										                 One._RO->StrUnits);
									}

									delete TwoStr;
								}
							}
							break;
					}

				} else {
					Results = 1;
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const String & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const String & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const String & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const ROString & One,
			               const String & Two)
			{
				int		Results = One == Two;

				if (Results != 0) {
					if (One < Two) {
						Results = -1;

					} else {
						Results = 1;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const String & Two)
			{
				int		Results = 0;

				if (One.IsReadOnly()) {
					if (Two.IsReadOnly()) {
						Results = strcmp((ROString &)One, (ROString &)Two);

					} else {
						Results = strcmp((ROString &)One, Two);
					}

				} else if (Two.IsReadOnly()) {
					Results = strcmp(One, (ROString &)Two);

				} else {
					Results = strcmp(One.Get32(), Two.Get32());
				}

				return (Results);
			}

			int
			String::strcmp(const String & One,
			               const ROString & Two)
			{
				int		Results = 0;

				size_t		Len = 0;
				size_t		OneLen = One.Length();
				size_t		TwoLen = Two.Length();

				if (OneLen < TwoLen) {
					Results = -1;

				} else if (TwoLen < OneLen) {
					Results = 1;

				} else {
					// Length equal
					//
					switch (Two.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(One.Get8(), Two.Get8(Len), TwoLen);
							break;

						case Is16Bit_t:
							Results = strncmp(One.Get16(), Two.Get16(Len), TwoLen);
							break;

						case Is32Bit_t:
							Results = strncmp(One.Get32(), Two.Get32(Len), TwoLen);
							break;

						case IsWBit_t:
							Results = strncmp(One.GetW(), Two.GetW(Len), TwoLen);
							break;
					}
				}

				return (Results);
			}

			int
			String::strcmp(const ROString & One,
			               const ROString & Two)
			{
				int		Results = 0;

				if (&One != &Two) {	// If they are, they are equal.
					if (One._RO != Two._RO) {	// if they are, they are equal.
						if (One._RO->Str.RO8 !=
						    Two._RO->Str.RO8) {// if they are, they are equal.
							size_t		Len1 = One.Length();
							size_t		Len2 = Two.Length();

							if (Len1 < Len2) {
								Results = -1;

							} else if (Len1 > Len2) {
								Results = 1;

							} else {
								if ((strcmp(One.InputCharset(), Two.InputCharset()) == 0)
								    && One.InputWidth() == Two.InputWidth()) {

									switch (One.InputWidth()) {

										case IsUnknownBit_t:
											/*EMPTY*/
											break;

										case Is8Bit_t:
											Results = memcmp(One._RO->Str.RO8,
											                 Two._RO->Str.RO8,
											                 Len1);
											break;

										case Is16Bit_t:
											Results = memcmp(One._RO->Str.RO16,
											                 Two._RO->Str.RO16,
											                 Len1 * sizeof(char16_t));
											break;

										case Is32Bit_t:
											Results = memcmp(One._RO->Str.RO32,
											                 Two._RO->Str.RO32,
											                 Len1 * sizeof(char32_t));
											break;

										case IsWBit_t:
											Results = memcmp(One._RO->Str.ROW,
											                 Two._RO->Str.ROW,
											                 Len1 * sizeof(wchar_t));
											break;
									}

								} else {
									// Different charaset, same size characters.
									//
									// or
									//
									// Different charaset, different size characters.
									//
									// Same string length.
									//
									String	*	InOneCs
									    = Two.ToCharset(One.InputCharset(),
									                    One.InputWidth());
									Results = strcmp(One, *InOneCs);
									delete InOneCs;
								}
							}
						}
					}
				}

				return (Results);
			}

			/*STRNCMP*/
			int
			String::strncmp(const char * const One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					Results = ::strncmp(One, Two, Len);

				}

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char	 *	TwoStr = nullptr;

						if (String::Charset16To8(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = ::strlen(One);
							size_t	Len2 = ::strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;
					\

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char	 *	TwoStr = nullptr;

						if (String::Charset32To8(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = ::strlen(One);
							size_t	Len2 = ::strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char	 *	TwoStr = nullptr;

						if (String::CharsetWTo8(nullptr,
						                        Two,
						                        nullptr,
						                        TwoStr)) {

							size_t	Len1 = ::strlen(One);
							size_t	Len2 = ::strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const std::string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const std::u16string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const std::u32string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const char * const One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset8To8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset8To16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset8To32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset8ToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char * const One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset8To8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset8To16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset8To32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset8ToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, ((String &)Two).Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char16_t *	TwoStr = nullptr;

						if (String::Charset8To16(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {

						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(Two);

						if (Len1 > Len) {
							Len1 = Len;
						}

						if (Len2 > Len) {
							Len2 = Len;
						}

						if (Len1 == Len2) {
							Results = memcmp(One, Two, Len1 * sizeof(char16_t));

						} else if (Len1 < Len2) {
							Results = -1;

						} else {
							Results = 1;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char16_t *	TwoStr = nullptr;

						if (String::Charset32To16(nullptr,
						                          Two,
						                          nullptr,
						                          TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {

						char16_t *	TwoStr = nullptr;

						if (String::CharsetWTo16(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const std::string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const std::u16string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const std::u32string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char16_t * const One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const char16_t * const One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset16To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset16To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset16To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset16ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}
			int
			String::strncmp(const char16_t * const One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset16To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset16To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset16To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset16ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, ((String &)Two).Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t *	TwoStr = nullptr;

						if (String::Charset8To32(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t *	TwoStr = nullptr;

						if (String::Charset16To32(nullptr,
						                          Two,
						                          nullptr,
						                          TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {
						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(Two);

						if (Len1 > Len) {
							Len1 = Len;
						}

						if (Len2 > Len) {
							Len2 = Len;
						}

						if (Len1 == Len2) {
							Results = memcmp(One, Two, Len1 * sizeof(char16_t));

						} else if (Len1 < Len2) {
							Results = -1;

						} else {
							Results = 1;
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					char32_t	*	TwoStr = nullptr;

					if (CharsetWTo32(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One, TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const std::string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const std::u16string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const std::u32string & Two,
			                size_t Len)
			{
				int		Results = strncmp(One, Two.c_str(), Len);

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const char32_t * const One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset32To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset32To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset32To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset32ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const char32_t * const One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset32To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset32To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset32To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset32ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, ((String &)Two).Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					wchar_t	*	TwoStr = nullptr;

					if (Charset8ToW(nullptr,
					                Two,
					                nullptr,
					                TwoStr)) {
						Results = strncmp(One, TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					wchar_t	*	TwoStr = nullptr;

					if (Charset16ToW(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One, TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					wchar_t	*	TwoStr = nullptr;

					if (Charset32ToW(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One, TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					Results = wcsncmp(One, Two, Len);
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const std::string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const wchar_t * const One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const wchar_t * const One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const wchar_t * const One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const wchar_t * const One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (CharsetWTo8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (CharsetWTo16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (CharsetWTo32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (CharsetWToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const wchar_t * const One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (CharsetWTo8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (CharsetWTo16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (CharsetWTo32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (CharsetWToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, ((String &)Two).Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					Results = ::strncmp(One.c_str(), Two, Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset16To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = ::strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset32To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = ::strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (CharsetWTo8(nullptr,
					                Two,
					                nullptr,
					                TwoStr)) {
						Results = ::strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const std::string & Two,
			                size_t Len)
			{
				return (::strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::string & One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::string & One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::string & One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::string & One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (Charset8To8(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (Charset8To16(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (Charset8To32(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (Charset8ToW(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {

									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, Two.Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::string & One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (Charset8To8(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (Charset8To16(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (Charset8To32(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (Charset8ToW(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {

									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, ((String &)Two).Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					Results = strncmp(One.c_str(), Two, Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset16To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset32To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (CharsetWTo8(nullptr,
					                Two,
					                nullptr,
					                TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const std::string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u16string & One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u16string & One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u16string & One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u16string & One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (Charset16To8(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (Charset16To16(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (Charset16To32(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (Charset16ToW(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, ((String &)Two).Get16(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u16string & One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (Charset16To8(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (Charset16To16(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (Charset16To32(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (Charset16ToW(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {

									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, ((String &)Two).Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					Results = strncmp(One.c_str(), Two, Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset16To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset32To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (CharsetWTo8(nullptr,
					                Two,
					                nullptr,
					                TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const std::string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u32string & One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u32string & One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u32string & One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::u32string & One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset8To32(Two._InputCharset,
								                 Two.Get8(),
								                 nullptr,
								                 TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset16To32(Two._InputCharset,
								                  Two.Get16(),
								                  nullptr,
								                  TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	TwoStr = nullptr;

								if (Charset32To32(Two._InputCharset,
								                  Two.Get32(),
								                  nullptr,
								                  TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								char32_t	*	TwoStr = nullptr;

								if (CharsetWTo32(Two._InputCharset,
								                 Two.GetW(),
								                 nullptr,
								                 TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, Two.Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::u32string & One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (Charset32To8(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (Charset32To16(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (Charset32To32(nullptr,
								                  One.c_str(),
								                  Two._InputCharset,
								                  OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (Charset32ToW(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {

									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, ((String &)Two).Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					Results = strncmp(One.c_str(), Two, Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset16To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (Charset32To8(nullptr,
					                 Two,
					                 nullptr,
					                 TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two == nullptr) {
					Results = 1;

				} else {
					char	*	TwoStr = nullptr;

					if (CharsetWTo8(nullptr,
					                Two,
					                nullptr,
					                TwoStr)) {
						Results = strncmp(One.c_str(), TwoStr, Len);
						delete TwoStr;
					}
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const std::string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::wstring & One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::wstring & One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::wstring & One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One.c_str(), Two.c_str(), Len));
			}

			int
			String::strncmp(const std::wstring & One,
			                const String & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset8ToW(Two._InputCharset,
								                Two.Get8(),
								                nullptr,
								                TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case Is16Bit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset16ToW(Two._InputCharset,
								                 Two.Get16(),
								                 nullptr,
								                 TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case Is32Bit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (Charset32ToW(Two._InputCharset,
								                 Two.Get32(),
								                 nullptr,
								                 TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	TwoStr = nullptr;

								if (CharsetWToW(Two._InputCharset,
								                Two.GetW(),
								                nullptr,
								                TwoStr)) {
									Results = strncmp(One.c_str(), TwoStr, Len);
									delete TwoStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, Two.Get8(), Len);
				}

				return (Results);
			}

			int
			String::strncmp(const std::wstring & One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {

					switch (Two._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								char	*	OneStr = nullptr;

								if (CharsetWTo8(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str8(), Len);
									delete OneStr;
								}
							}
							break;

						case Is16Bit_t: {
								char16_t	*	OneStr = nullptr;

								if (CharsetWTo16(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str16(), Len);
									delete OneStr;
								}
							}
							break;

						case Is32Bit_t: {
								char32_t	*	OneStr = nullptr;

								if (CharsetWTo32(nullptr,
								                 One.c_str(),
								                 Two._InputCharset,
								                 OneStr)) {
									Results = strncmp(OneStr, Two.cbegin().str32(), Len);
									delete OneStr;
								}
							}
							break;

						case IsWBit_t: {
								wchar_t	*	OneStr = nullptr;

								if (CharsetWToW(nullptr,
								                One.c_str(),
								                Two._InputCharset,
								                OneStr)) {

									Results = strncmp(OneStr, Two.cbegin().strW(), Len);
									delete OneStr;
								}
							}
							break;

					}

				} else {
					Results = strncmp(One, ((String &)Two).Get8(), Len);
				}

				return (Results);
			}

			/*STRCASECMP*/
			int
			String::strncasecmp(const char * const One,
			                    const char * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len == 0) {
						Results = ::strcasecmp(One, Two);

					} else {
						Results = ::strncasecmp(One, Two, Len);
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char * const One,
			                    const char16_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {


					if (Len > 0) {
						char * TwoStr = nullptr;

						if (String::Charset16To8(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = ::strlen(One);
							size_t	Len2 = ::strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char * const One,
			                    const char32_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {

						char * TwoStr = nullptr;

						if (String::Charset32To8(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = ::strlen(One);
							size_t	Len2 = ::strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;

							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char * const One,
			                    const wchar_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						wchar_t	*	TwoStr = nullptr;

						if (String::Charset8ToW(nullptr,
						                        One,
						                        nullptr,
						                        TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(TwoStr, Two, Len1 * sizeof(wchar_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;

							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char * const One,
			                    const String & Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset8To8(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset8To16(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset8To32(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset8ToW(nullptr,
									                One,
									                Two._InputCharset,
									                OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char * const One,
			                    const std::string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char * const One,
			                    const std::u16string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char * const One,
			                    const std::u32string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char * const One,
			                    const std::wstring & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const char * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char16_t * TwoStr = nullptr;

						if (String::Charset8To16(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const char16_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {
						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(Two);

						if (Len1 > Len) {
							Len1 = Len;
						}

						if (Len2 > Len) {
							Len2 = Len;
						}

						if (Len1 == Len2) {
							Results = memcmp(One, Two, Len1 * sizeof(char16_t));

						} else if (Len1 < Len2) {
							Results = -1;

						} else {
							Results = 1;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const char32_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {

						char16_t * TwoStr = nullptr;

						if (String::Charset32To16(nullptr,
						                          Two,
						                          nullptr,
						                          TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const wchar_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char16_t	*	TwoStr = nullptr;

						if (String::CharsetWTo16(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char16_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const std::string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const std::u16string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const std::u32string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const std::wstring & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char16_t * const One,
			                    const String & Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset16To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset16To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset16To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset16ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const char * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t * TwoStr = nullptr;

						if (String::Charset8To32(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const char16_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t * TwoStr = nullptr;

						if (String::Charset16To32(nullptr,
						                          Two,
						                          nullptr,
						                          TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const char32_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {
						size_t	Len1 = strlen(One);
						size_t	Len2 = strlen(Two);

						if (Len1 > Len) {
							Len1 = Len;
						}

						if (Len2 > Len) {
							Len2 = Len;
						}

						if (Len1 == Len2) {
							Results = memcmp(One, Two, Len1 * sizeof(char32_t));

						} else if (Len1 < Len2) {
							Results = -1;

						} else {
							Results = 1;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const wchar_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t	*	TwoStr = nullptr;

						if (String::CharsetWTo32(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1 * sizeof(char32_t));

							} else if (Len1 < Len2) {
								Results = -1;

							} else if (Len1 > Len2) {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const std::string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const std::u16string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const std::u32string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const std::wstring & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const char32_t * const One,
			                    const String & Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {

					if (Two.IsReadOnly()) {

						switch (Two._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t: {
									char	*	OneStr = nullptr;

									if (Charset32To8(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str8(), Len);
										delete OneStr;
									}
								}
								break;

							case Is16Bit_t: {
									char16_t	*	OneStr = nullptr;

									if (Charset32To16(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str16(), Len);
										delete OneStr;
									}
								}
								break;

							case Is32Bit_t: {
									char32_t	*	OneStr = nullptr;

									if (Charset32To32(nullptr,
									                  One,
									                  Two._InputCharset,
									                  OneStr)) {
										Results = strncmp(OneStr, Two.cbegin().str32(), Len);
										delete OneStr;
									}
								}
								break;

							case IsWBit_t: {
									wchar_t	*	OneStr = nullptr;

									if (Charset32ToW(nullptr,
									                 One,
									                 Two._InputCharset,
									                 OneStr)) {

										Results = strncmp(OneStr, Two.cbegin().strW(), Len);
										delete OneStr;
									}
								}
								break;

						}

					} else {
						Results = strncmp(One, Two.Get8(), Len);
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const char * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						wchar_t	*	TwoStr = nullptr;

						if (String::Charset8ToW(nullptr,
						                        Two,
						                        nullptr,
						                        TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else if (Len1 > Len2) {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const char16_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						wchar_t	*	TwoStr = nullptr;

						if (String::Charset16ToW(nullptr,
						                         Two,
						                         nullptr,
						                         TwoStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(TwoStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(One, TwoStr, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else if (Len1 > Len2) {
								Results = 1;
							}

							delete TwoStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const char32_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {

					if (Len > 0) {
						char32_t	*	OneStr = nullptr;

						if (String::CharsetWTo32(nullptr,
						                         One,
						                         nullptr,
						                         OneStr)) {

							size_t	Len1 = strlen(One);
							size_t	Len2 = strlen(OneStr);

							if (Len1 > Len) {
								Len1 = Len;
							}

							if (Len2 > Len) {
								Len2 = Len;
							}

							if (Len1 == Len2) {
								Results = memcmp(OneStr, Two, Len1);

							} else if (Len1 < Len2) {
								Results = -1;

							} else if (Len1 > Len2) {
								Results = 1;
							}

							delete OneStr;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const wchar_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One != nullptr && Two == nullptr) {
					Results = 1;

				} else if (One == nullptr && Two != nullptr) {
					Results = -1;

				} else if (One == nullptr && Two == nullptr) {
					Results = 0;

				} else {
					if (Len > 0) {
						size_t	Len1 = wcslen(One);
						size_t	Len2 = wcslen(Two);

						if (Len1 > Len) {
							Len1 = Len;
						}

						if (Len2 > Len) {
							Len2 = Len;
						}

						if (Len1 == Len2) {
							Results = memcmp(One, Two, Len1);

						} else if (Len1 < Len2) {
							Results = -1;

						} else if (Len1 > Len2) {
							Results = 1;
						}
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const std::string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const std::u16string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const std::u32string & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const std::wstring & Two,
			                    size_t Len)
			{
				return (strncasecmp(One, Two.c_str(), Len));
			}

			int
			String::strncasecmp(const wchar_t * const One,
			                    const String & Two,
			                    size_t Len)
			{
				int		Results = 0;

				if (One == nullptr) {
					Results = -1;

				} else {
					size_t	OneLen = strlen(One);
					size_t	TwoLen = Two.Length();

					if (OneLen < TwoLen) {
						Results = -1;

					} else if (OneLen > TwoLen) {
						Results = 1;

					} else {
						// Lengths equal.
						//
						if (!Two.IsReadOnly()) {
							Results = strncasecmp(One, Two.GetW(), Len);

						} else {
							ROString	RO(Two);

							Results = strcmp(One, RO);
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(const String & One,
			                const char * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two != nullptr) {
					ROString	*	TwoS = new ROString(Two);
					String	*	TwoInOneCharset
					    = TwoS->ToCharset(One._InputCharset,
					                      One._InputWidth);

					if (TwoInOneCharset != nullptr) {
						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = strncmp(One.Get8(), TwoInOneCharset->Get8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.Get16(), TwoInOneCharset->Get16(),
								                  Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.Get32(), TwoInOneCharset->Get32(),
								                  Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.GetW(), TwoInOneCharset->GetW(), Len);
								break;
						}

						delete TwoInOneCharset;
					}

					delete TwoS;

				} else {
					Results = -1;
				}

				return (Results);
			}

			int
			String::strncmp(const String & One,
			                const char16_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two != nullptr) {
					String	*	TwoS = new String(Two);
					String	*	InCharset
					    = TwoS->ToCharset(One._InputCharset,
					                      One._InputWidth);

					if (InCharset != nullptr) {
						size_t		OLen = 0;

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = strncmp(One.Get8(), InCharset->Get8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.Get16(), InCharset->Get16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.Get32(), InCharset->Get32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.GetW(), InCharset->GetW(), Len);
								break;
						}

						delete InCharset;
					}

					delete TwoS;

				} else {
					Results = -1;
				}

				return (Results);
			}

			int
			String::strncmp(const String & One,
			                const char32_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two != nullptr) {
					String	*	TwoS = new String(Two);
					String	*	InCharset
					    = TwoS->ToCharset(One._InputCharset,
					                      One._InputWidth);

					if (InCharset != nullptr) {
						size_t		OLen = 0;

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = strncmp(One.Get8(), InCharset->Get8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.Get16(), InCharset->Get16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.Get32(), InCharset->Get32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.GetW(), InCharset->GetW(), Len);
								break;
						}

						delete InCharset;
					}

					delete TwoS;

				} else {
					Results = -1;
				}

				return (Results);
			}

			int
			String::strncmp(const String & One,
			                const wchar_t * const Two,
			                size_t Len)
			{
				int		Results = 0;

				if (Two != nullptr) {
					ROString	*	Ro = new ROString(One, Len);
					String	*	TwoS = new String(Two);
					String	*	InCharset
					    = TwoS->ToCharset(One._InputCharset,
					                      One._InputWidth);

					if (InCharset != nullptr) {
						size_t		OLen = 0;

						switch (One._InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = strncmp(Ro->Get8(OLen), InCharset->Get8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(Ro->Get16(OLen), InCharset->Get16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(Ro->Get32(OLen), InCharset->Get32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(Ro->GetW(OLen), InCharset->GetW(), Len);
								break;
						}

						delete InCharset;
					}

					delete TwoS;

				} else {
					Results = -1;
				}

				return (Results);
			}

			int
			String::strncmp(const String & One,
			                const std::string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const String & One,
			                const std::u16string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const String & One,
			                const std::u32string & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const String & One,
			                const std::wstring & Two,
			                size_t Len)
			{
				return (strncmp(One, Two.c_str(), Len));
			}

			int
			String::strncmp(const String & One,
			                const String & Two,
			                size_t Len)
			{
				ROString	*	RO1 = new ROString(One);
				ROString	*	RO2 = new ROString(Two);

				return (strncmp(*RO1, *RO2, Len));
			}

			int
			String::strcmp(String::const_iterator & One,
			               const char * Two)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcmp(One.str8(), Two);
						break;

					case Is16Bit_t:
						Results = strcmp(One.str16(), Two);
						break;

					case Is32Bit_t:
						Results = strcmp(One.str32(), Two);
						break;

					case IsWBit_t:
						Results = strcmp(One.strW(), Two);
						break;

				}

				return (Results);
			}

			int
			String::strcmp(String::const_iterator & One,
			               const char16_t * Two)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcmp(One.str8(), Two);
						break;

					case Is16Bit_t:
						Results = strcmp(One.str16(), Two);
						break;

					case Is32Bit_t:
						Results = strcmp(One.str32(), Two);
						break;

					case IsWBit_t:
						Results = strcmp(One.strW(), Two);
						break;

				}

				return (Results);
			}

			int
			String::strcmp(String::const_iterator & One,
			               const char32_t * Two)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcmp(One.str8(), Two);
						break;

					case Is16Bit_t:
						Results = strcmp(One.str16(), Two);
						break;

					case Is32Bit_t:
						Results = strcmp(One.str32(), Two);
						break;

					case IsWBit_t:
						Results = strcmp(One.strW(), Two);
						break;

				}

				return (Results);
			}

			int
			String::strcmp(String::const_iterator & One,
			               const wchar_t * Two)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strcmp(One.str8(), Two);
						break;

					case Is16Bit_t:
						Results = strcmp(One.str16(), Two);
						break;

					case Is32Bit_t:
						Results = strcmp(One.str32(), Two);
						break;

					case IsWBit_t:
						Results = strcmp(One.strW(), Two);
						break;

				}

				return (Results);
			}

			int
			String::strcmp(String::const_iterator & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(String::const_iterator & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(String::const_iterator & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(String::const_iterator & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::string & One,
			               const char * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::string & One,
			               const char16_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::string & One,
			               const char32_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::string & One,
			               const wchar_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::string & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::string & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::string & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::string & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::string & One,
			               const String & Two)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {
					ROString	RO(Two);

					Results = strcmp(One.c_str(), RO);

				} else {

					String	*	Copy = Two.ToCharset(Current8BitCharset,
					                                 Is8Bit_t);

					Results = strcmp(One.c_str(), Copy->Get8());
					delete Copy;
				}

				return (Results);
			}

			int
			String::strcmp(const std::string & One,
			               const ROString & Two)
			{
				int		Results = 0;

				String		OneCopy(One.c_str());
				String	*	InRoCs = OneCopy.ToCharset(Two.InputCharset(),
				                                       Two.InputWidth());

				if (InRoCs != nullptr) {
					size_t		Len = 0;

					switch (Two.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(InRoCs->Get8(), Two.Get8(Len),
							                  Two.Length());
							break;

						case Is16Bit_t:
							Results = strncmp(InRoCs->Get16(),
							                  Two.Get16(Len),
							                  Two.Length());
							break;

						case Is32Bit_t:
							Results = strncmp(InRoCs->Get32(),
							                  Two.Get32(Len),
							                  Two.Length());
							break;

						case IsWBit_t:
							Results = strncmp(InRoCs->GetW(), Two.GetW(Len),
							                  Two.Length());
							break;
					}

					delete InRoCs;
				}

				return (Results);
			}

			int
			String::strcmp(const std::u16string & One,
			               const char * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u16string & One,
			               const char16_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u16string & One,
			               const char32_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u16string & One,
			               const wchar_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u16string & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u16string & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u16string & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u16string & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u16string & One,
			               const String & Two)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {
					ROString	RO(Two);

					Results = strcmp(One.c_str(), RO);

				} else {
					String	*	Copy = Two.ToCharset(Current16BitCharset,
					                                 Is16Bit_t);

					Results = strcmp(One.c_str(), Copy->Get16());
					delete Copy;
				}

				return (Results);
			}

			int
			String::strcmp(const std::u16string & One,
			               const ROString & Two)
			{
				int		Results = 0;

				String		OneCopy(One.c_str());
				String	*	InRoCs = OneCopy.ToCharset(Two.InputCharset(),
				                                       Two.InputWidth());

				if (InRoCs != nullptr) {
					size_t		Len = 0;

					switch (Two.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(InRoCs->Get8(), Two.Get8(Len),
							                  Two.Length());
							break;

						case Is16Bit_t:
							Results = strncmp(InRoCs->Get16(),
							                  Two.Get16(Len),
							                  Two.Length());
							break;

						case Is32Bit_t:
							Results = strncmp(InRoCs->Get32(),
							                  Two.Get32(Len),
							                  Two.Length());
							break;

						case IsWBit_t:
							Results = strncmp(InRoCs->GetW(), Two.GetW(Len),
							                  Two.Length());
							break;
					}

					delete InRoCs;
				}

				return (Results);
			}

			int
			String::strcmp(const std::u32string & One,
			               const char * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u32string & One,
			               const char16_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u32string & One,
			               const char32_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u32string & One,
			               const wchar_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::u32string & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u32string & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u32string & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u32string & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::u32string & One,
			               const String & Two)
			{
				int		Results = 0;

				if (Two.IsReadOnly()) {
					ROString	RO(Two);

					Results = strcmp(One, RO);

				} else {
					String	*	Copy = Two.ToCharset(Current32BitCharset,
					                                 Is32Bit_t);

					Results = strcmp(One.c_str(), Copy->Get32());
					delete Copy;
				}

				return (Results);
			}

			int
			String::strcmp(const std::u32string & One,
			               const ROString & Two)
			{
				int		Results = 0;

				String		OneCopy(One.c_str());
				String	*	InRoCs = OneCopy.ToCharset(Two.InputCharset(),
				                                       Two.InputWidth());

				if (InRoCs != nullptr) {
					size_t		Len = 0;

					switch (Two.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(InRoCs->Get8(), Two.Get8(Len),
							                  Two.Length());
							break;

						case Is16Bit_t:
							Results = strncmp(InRoCs->Get16(),
							                  Two.Get16(Len),
							                  Two.Length());
							break;

						case Is32Bit_t:
							Results = strncmp(InRoCs->Get32(),
							                  Two.Get32(Len),
							                  Two.Length());
							break;

						case IsWBit_t:
							Results = strncmp(InRoCs->GetW(), Two.GetW(Len),
							                  Two.Length());
							break;
					}

					delete InRoCs;
				}

				return (Results);
			}

			int
			String::strcmp(const std::wstring & One,
			               const char * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::wstring & One,
			               const char16_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::wstring & One,
			               const char32_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::wstring & One,
			               const wchar_t * const Two)
			{
				return (strcmp(One.c_str(), Two));
			}

			int
			String::strcmp(const std::wstring & One,
			               const std::string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::wstring & One,
			               const std::u16string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::wstring & One,
			               const std::u32string & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::wstring & One,
			               const std::wstring & Two)
			{
				return (strcmp(One, Two.c_str()));
			}

			int
			String::strcmp(const std::wstring & One,
			               const String & Two)
			{
				int		Results = 0;

				String	*	Copy = Two.ToCharset(CurrentWBitCharset,
				                                 IsWBit_t);

				Results = strcmp(One.c_str(), Copy->GetW());
				delete Copy;

				return (Results);
			}

			int
			String::strcmp(const std::wstring & One,
			               const ROString & Two)
			{
				int		Results = 0;

				String		OneCopy(One.c_str());
				String	*	InRoCs = OneCopy.ToCharset(Two.InputCharset(),
				                                       Two.InputWidth());

				if (InRoCs != nullptr) {
					size_t		Len = 0;

					switch (Two.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(InRoCs->Get8(), Two.Get8(Len),
							                  Two.Length());
							break;

						case Is16Bit_t:
							Results = strncmp(InRoCs->Get16(),
							                  Two.Get16(Len),
							                  Two.Length());
							break;

						case Is32Bit_t:
							Results = strncmp(InRoCs->Get32(),
							                  Two.Get32(Len),
							                  Two.Length());
							break;

						case IsWBit_t:
							Results = strncmp(InRoCs->GetW(), Two.GetW(Len),
							                  Two.Length());
							break;
					}

					delete InRoCs;
				}

				return (Results);
			}

			int
			String::strncmp(String::const_iterator & One,
			                const char * Two,
			                size_t Len)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strncmp(One.str8(), Two, Len);
						break;

					case Is16Bit_t:
						Results = strncmp(One.str16(), Two, Len);
						break;

					case Is32Bit_t:
						Results = strncmp(One.str32(), Two, Len);
						break;

					case IsWBit_t:
						Results = strncmp(One.strW(), Two, Len);
						break;

				}

				return (Results);
			}

			int
			String::strncmp(String::const_iterator & One,
			                const char16_t * Two,
			                size_t Len)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strncmp(One.str8(), Two, Len);
						break;

					case Is16Bit_t:
						Results = strncmp(One.str16(), Two, Len);
						break;

					case Is32Bit_t:
						Results = strncmp(One.str32(), Two, Len);
						break;

					case IsWBit_t:
						Results = strncmp(One.strW(), Two, Len);
						break;

				}

				return (Results);
			}

			int
			String::strncmp(String::const_iterator & One,
			                const char32_t * Two,
			                size_t Len)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strncmp(One.str8(), Two, Len);
						break;

					case Is16Bit_t:
						Results = strncmp(One.str16(), Two, Len);
						break;

					case Is32Bit_t:
						Results = strncmp(One.str32(), Two, Len);
						break;

					case IsWBit_t:
						Results = strncmp(One.strW(), Two, Len);
						break;

				}

				return (Results);
			}

			int
			String::strncmp(String::const_iterator & One,
			                const wchar_t * Two,
			                size_t Len)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = strncmp(One.str8(), Two, Len);
						break;

					case Is16Bit_t:
						Results = strncmp(One.str16(), Two, Len);
						break;

					case Is32Bit_t:
						Results = strncmp(One.str32(), Two, Len);
						break;

					case IsWBit_t:
						Results = strncmp(One.strW(), Two, Len);
						break;

				}

				return (Results);
			}

			int
			String::strncmp(const ROString & One,
			                const String & Two,
			                size_t Len)
			{
				int			Results = 0;

				ROString	*	Ro = new ROString(Two);

				Results = strncmp(One, *Ro, Len);
				delete Ro;

				return (Results);
			}

			int
			String::strncmp(const ROString & One,
			                const ROString & Two,
			                size_t Len)
			{
				int		Results = 0;

				size_t		OLen1 = 0;

				if (strcmp(One._InputCharset, Two._InputCharset) == 0) {

					switch (One._InputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strncmp(One.Get8(OLen1), Two, Len);
							break;

						case Is16Bit_t:
							Results = strncmp(One.Get16(OLen1), Two, Len);
							break;

						case Is32Bit_t:
							Results = strncmp(One.Get32(OLen1), Two, Len);
							break;

						case IsWBit_t:
							Results = strncmp(One.GetW(OLen1), Two, Len);
							break;
					}

				} else {
					String	*	TwoCs = Two.ToCharset(One._InputCharset,
					                                  One._InputWidth);

					if (TwoCs != nullptr) {
						Results = strncmp(One, *TwoCs, Len);
						delete TwoCs;
					}
				}

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const char * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const char16_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const char32_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const wchar_t * const Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const std::string & Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const std::u16string & Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const std::u32string & Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const std::wstring & Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			int
			String::strncasecmp(const String & One,
			                    const String & Two,
			                    size_t Len)
			{
				int		Results = 0;

				ROString	*	Ro = new ROString(One, Len);

				Results = *Ro == Two;
				delete Ro;

				return (Results);
			}

			bool
			String::operator ==(char Other) const
			{
				bool		Results = false;

				char		Two[2];

				Two[0] = Other;
				Two[1] = 0;

				if (_ROString) {
					size_t	OLen = 1;

					if (OLen == _RO->StrUnits) {
						switch (_RO->Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								if (_RO->Str.RO8 != nullptr) {
									Results = (::strncmp(_RO->Str.RO8, Two, 1) == 0);
								}

								break;

							case Is16Bit_t:
								if (_RO->Str.RO16 != nullptr) {
									Results = (strncmp(_RO->Str.RO16, Two, 1) == 0);
								}

								break;

							case Is32Bit_t:
								if (_RO->Str.RO32 != nullptr) {
									Results = (strncmp(_RO->Str.RO32, Two, 1) == 0);
								}

								break;

							case IsWBit_t:
								if (_RO->Str.ROW != nullptr) {
									Results = (strncmp(_RO->Str.ROW, Two, 1) == 0);
								}

								break;

						}

					} else {
						const char * const	OutUs = Get8();

						Results = (strcmp(OutUs, Two) == 0);
					}

				} else {
					Results = (strcmp(Get8(), Two) == 0);
				}

				return (Results);
			}

			bool
			String::operator ==(char16_t Other) const
			{
				bool			Results = false;

				char16_t	Two[2];

				Two[0] = Other;
				Two[1] = 0;

				if (_ROString) {
					size_t	OLen = 1;

					if (OLen == _RO->StrUnits) {
						switch (_RO->Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								if (_RO->Str.RO8 != nullptr) {
									Results = (strncmp(_RO->Str.RO8, Two, 1) == 0);
								}

								break;

							case Is16Bit_t:
								if (_RO->Str.RO16 != nullptr) {
									Results = (strncmp(_RO->Str.RO16, Two, 1) == 0);
								}

								break;

							case Is32Bit_t:
								if (_RO->Str.RO32 != nullptr) {
									Results = (strncmp(_RO->Str.RO32, Two, 1) == 0);
								}

								break;

							case IsWBit_t:
								if (_RO->Str.ROW != nullptr) {
									Results = (strncmp(_RO->Str.ROW, Two, 1) == 0);
								}

								break;

						}

					} else {
						const char16_t * const	OutUs = Get16();

						Results = (strcmp(OutUs, Two) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(char32_t Other) const
			{
				bool			Results = false;

				char32_t	Two[2];

				Two[0] = Other;
				Two[1] = 0;

				if (_ROString) {
					size_t	OLen = 1;

					if (OLen == _RO->StrUnits) {
						switch (_RO->Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								if (_RO->Str.RO8 != nullptr) {
									Results = (strncmp(_RO->Str.RO8, Two, 1) == 0);
								}

								break;

							case Is16Bit_t:
								if (_RO->Str.RO16 != nullptr) {
									Results = (strncmp(_RO->Str.RO16, Two, 1) == 0);
								}

								break;

							case Is32Bit_t:
								if (_RO->Str.RO32 != nullptr) {
									Results = (strncmp(_RO->Str.RO32, Two, 1) == 0);
								}

								break;

							case IsWBit_t:
								if (_RO->Str.ROW != nullptr) {
									Results = (strncmp(_RO->Str.ROW, Two, 1) == 0);
								}

								break;

						}

					} else {
						const char32_t * const	OutUs = Get32();

						Results = (strcmp(OutUs, Two) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(wchar_t Other) const
			{
				bool		Results = false;

				wchar_t	Two[2];

				Two[0] = Other;
				Two[1] = 0;

				if (_ROString) {
					size_t	OLen = 1;

					if (OLen == _RO->StrUnits) {
						switch (_RO->Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								if (_RO->Str.RO8 != nullptr) {
									Results = (strncmp(_RO->Str.RO8, Two, 1) == 0);
								}

								break;

							case Is16Bit_t:
								if (_RO->Str.RO16 != nullptr) {
									Results = (strncmp(_RO->Str.RO16, Two, 1) == 0);
								}

								break;

							case Is32Bit_t:
								if (_RO->Str.RO32 != nullptr) {
									Results = (strncmp(_RO->Str.RO32, Two, 1) == 0);
								}

								break;

							case IsWBit_t:
								if (_RO->Str.ROW != nullptr) {
									Results = (strncmp(_RO->Str.ROW, Two, 1) == 0);
								}

								break;

						}

					} else {
						const wchar_t * const	OutUs = GetW();

						Results = (strcmp(OutUs, Two) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(const char * Other) const
			{
				bool		Results = false;

				if (Other != nullptr) {
					if (_ROString) {
						size_t		OLen = strlen(Other);

						if (OLen == _RO->StrUnits) {
							switch (_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									if (_RO->Str.RO8 != nullptr) {
										Results = (::strncmp(_RO->Str.RO8, Other, OLen) == 0);
									}

									break;

								case Is16Bit_t:
									if (_RO->Str.RO16 != nullptr) {
										Results = (strncmp(_RO->Str.RO16, Other, OLen) == 0);
									}

									break;

								case Is32Bit_t:
									if (_RO->Str.RO32 != nullptr) {
										Results = (strncmp(_RO->Str.RO32, Other, OLen) == 0);
									}

									break;

								case IsWBit_t:
									if (_RO->Str.ROW != nullptr) {
										Results = (strncmp(_RO->Str.ROW, Other, OLen) == 0);
									}

									break;

							}
						}

					} else {
						const char * const	OutUs = Get8();

						Results = (strcmp(OutUs, Other) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(const char16_t * Other) const
			{
				bool		Results = false;

				if (Other != nullptr) {
					if (_ROString) {
						size_t		OLen = strlen(Other);

						if (OLen == _RO->StrUnits) {
							switch (_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									if (_RO->Str.RO8 != nullptr) {
										Results = (strncmp(_RO->Str.RO8, Other, OLen) == 0);
									}

									break;

								case Is16Bit_t:
									if (_RO->Str.RO16 != nullptr) {
										Results = (strncmp(_RO->Str.RO16, Other, OLen) == 0);
									}

									break;

								case Is32Bit_t:
									if (_RO->Str.RO32 != nullptr) {
										Results = (strncmp(_RO->Str.RO32, Other, OLen) == 0);
									}

									break;

								case IsWBit_t:
									if (_RO->Str.ROW != nullptr) {
										Results = (strncmp(_RO->Str.ROW, Other, OLen) == 0);
									}

									break;

							}
						}

					} else {
						const char * const	OutUs = Get8();

						Results = (strcmp(OutUs, Other) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(const char32_t * Other) const
			{
				bool		Results = false;

				if (Other != nullptr) {
					if (_ROString) {
						size_t		OLen = strlen(Other);

						if (OLen == _RO->StrUnits) {
							switch (_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									if (_RO->Str.RO8 != nullptr) {
										Results = (strncmp(_RO->Str.RO8, Other, OLen) == 0);
									}

									break;

								case Is16Bit_t:
									if (_RO->Str.RO16 != nullptr) {
										Results = (strncmp(_RO->Str.RO16, Other, OLen) == 0);
									}

									break;

								case Is32Bit_t:
									if (_RO->Str.RO32 != nullptr) {
										Results = (strncmp(_RO->Str.RO32, Other, OLen) == 0);
									}

									break;

								case IsWBit_t:
									if (_RO->Str.ROW != nullptr) {
										Results = (strncmp(_RO->Str.ROW, Other, OLen) == 0);
									}

									break;

							}
						}

					} else {
						const char * const	OutUs = Get8();

						Results = (strcmp(OutUs, Other) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(const wchar_t * Other) const
			{
				bool		Results = false;

				if (Other != nullptr) {
					if (_ROString) {
						size_t		OLen = strlen(Other);

						if (OLen == _RO->StrUnits) {
							switch (_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									if (_RO->Str.RO8 != nullptr) {
										Results = (strncmp(_RO->Str.RO8, Other, OLen) == 0);
									}

									break;

								case Is16Bit_t:
									if (_RO->Str.RO16 != nullptr) {
										Results = (strncmp(_RO->Str.RO16, Other, OLen) == 0);
									}

									break;

								case Is32Bit_t:
									if (_RO->Str.RO32 != nullptr) {
										Results = (strncmp(_RO->Str.RO32, Other, OLen) == 0);
									}

									break;

								case IsWBit_t:
									if (_RO->Str.ROW != nullptr) {
										Results = (strncmp(_RO->Str.ROW, Other, OLen) == 0);
									}

									break;

							}
						}

					} else {
						const char * const	OutUs = Get8();

						Results = (strcmp(OutUs, Other) == 0);
					}
				}

				return (Results);
			}

			bool
			String::operator ==(const std::string & other) const
			{
				return (*this == other.c_str());
			}

			bool
			String::operator ==(const std::u16string & other) const
			{
				return (*this == other.c_str());
			}

			bool
			String::operator ==(const std::u32string & other) const
			{
				return (*this == other.c_str());
			}

			bool
			String::operator ==(const std::wstring & other) const
			{
				return (*this == other.c_str());
			}

			bool
			String::operator ==(const ROString & Other) const
			{
				bool			Results = false;

				if (_ROString) {
					if (Other._ROString) {
						if (_RO->StrUnits == Other._RO->StrUnits) {
							if (_RO->Width == Other._RO->Width) {
								switch (_RO->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t:
										if (_RO->Str.RO8 != nullptr) {
											if (memcmp(_RO->Str.RO8,
											           Other._RO->Str.RO8,
											           _RO->StrUnits) == 0) {
												Results = true;
											}
										}

										break;

									case Is16Bit_t:
										if (_RO->Str.RO16 != nullptr) {
											if (memcmp(_RO->Str.RO16,
											           Other._RO->Str.RO16,
											           _RO->StrUnits * sizeof(char16_t)) == 0) {
												Results = true;
											}
										}

										break;

									case Is32Bit_t:
										if (_RO->Str.RO32 != nullptr) {
											if (memcmp(_RO->Str.RO32,
											           Other._RO->Str.RO32,
											           _RO->StrUnits * sizeof(char32_t)) == 0) {
												Results = true;
											}
										}

										break;

									case IsWBit_t:
										if (_RO->Str.ROW != nullptr) {
											if (memcmp(_RO->Str.ROW,
											           Other._RO->Str.ROW,
											           _RO->StrUnits *  sizeof(wchar_t)) == 0) {
												Results = true;
											}
										}

										break;
								}

							} else {
								// this this->Width != Other.Width
								//
								String	*	OtherS = Other.ToCharset(_RO->Charset,
								                                     _RO->Width);

								if (OtherS != nullptr) {
									Results = (*this == *OtherS);
									delete OtherS;
								}
							}
						}

					} else {
						// this is RO, Other is !RO
						//
						String	*	OtherS = Other.ToCharset(_RO->Charset,
						                                     _RO->Width);

						if (OtherS != nullptr) {
							Results = (*this == *OtherS);
							delete OtherS;
						}
					}

				} else {
					Results = ((String &) * this == (String &)Other);
				}

				return (Results);
			}

			bool
			String::operator ==(const String & Other) const
			{
				bool			Results = false;

				if (Length() == Other.Length()) {
					if (_ROString && Other._ROString) {
						Results = ((ROString &) * this == (ROString &)Other);

					} else {
						const String	*	OtherS = &Other;

						if (strcmp(_InputCharset, Other._InputCharset) != 0) {
							OtherS = Other.ToCharset(_InputCharset,
							                         _InputWidth);
						}

						if (OtherS != nullptr) {
							size_t		OutLen = 0;

							if (_ROString) {
								ROString	*	Us = (ROString *)this;
								size_t			Len = Length();

								switch (_InputWidth) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t:
										Results = (strncmp(Us->Get8(OutLen),
										                   OtherS->Get8(),
										                   Len) == 0);
										break;

									case Is16Bit_t:
										Results = (strncmp(Us->Get16(OutLen),
										                   OtherS->Get16(),
										                   Len) == 0);
										break;

									case Is32Bit_t:
										Results = (strncmp(Us->Get32(OutLen),
										                   OtherS->Get32(),
										                   Len) == 0);
										break;

									case IsWBit_t:
										Results = (strncmp(Us->GetW(OutLen),
										                   OtherS->GetW(),
										                   Len) == 0);
										break;
								}

							} else {
								switch (_InputWidth) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t:
										Results = (strcmp(Get8(), OtherS->Get8()) == 0);
										break;

									case Is16Bit_t:
										Results = (strcmp(Get16(), OtherS->Get16()) == 0);
										break;

									case Is32Bit_t:
										Results = (strcmp(Get32(), OtherS->Get32()) == 0);
										break;

									case IsWBit_t:
										Results = (strcmp(GetW(), OtherS->GetW()) == 0);
										break;
								}
							}

							if (&Other != OtherS) {
								delete OtherS;
							}
						}
					}
				}

				return (Results);
			}

			int
			String::strncmp(String::const_iterator & One,
			                String::const_iterator & Two,
			                size_t Len)
			{
				int		Results = 0;

				switch (One.Width()) {

					default:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						switch (Two.Width()) {

							case Is8Bit_t:
								Results = strncmp(One.str8(), Two.str8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.str8(), Two.str16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.str8(), Two.str32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.str8(), Two.strW(), Len);
								break;
						}

						break;

					case Is16Bit_t:
						switch (Two.Width()) {

							case Is8Bit_t:
								Results = strncmp(One.str16(), Two.str8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.str16(), Two.str16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.str16(), Two.str32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.str16(), Two.strW(), Len);
								break;
						}

						break;

					case Is32Bit_t:
						switch (Two.Width()) {

							case Is8Bit_t:
								Results = strncmp(One.str32(), Two.str8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.str32(), Two.str16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.str32(), Two.str32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.str32(), Two.strW(), Len);
								break;
						}

						break;

					case IsWBit_t:
						switch (Two.Width()) {

							case Is8Bit_t:
								Results = strncmp(One.strW(), Two.str8(), Len);
								break;

							case Is16Bit_t:
								Results = strncmp(One.strW(), Two.str16(), Len);
								break;

							case Is32Bit_t:
								Results = strncmp(One.strW(), Two.str32(), Len);
								break;

							case IsWBit_t:
								Results = strncmp(One.strW(), Two.strW(), Len);
								break;
						}

						break;

				}

				return (Results);
			}

		}
	}
}
