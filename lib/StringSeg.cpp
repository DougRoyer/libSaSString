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

			String::StringSeg::StringSeg()
			{
				Width = Is8Bit_t;
				Str.Utf8 = nullptr;
				Language = 0;
				Charset = nullptr;
				IsReadOnly = false;

				return;
			}

			String::StringSeg::StringSeg(const StringSeg & CopyFrom,
			                             uint64_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				IsReadOnly = CopyFrom.IsReadOnly;
				Width = CopyFrom.Width;

				if (IsReadOnly) {
					// In a union, so whatever the size, the pointer is valid.
					//
					Str.RO8 = CopyFrom.Str.RO8;
					StrUnits = CopyFrom.StrUnits;

				} else {
					Copy(CopyFrom, Len);
				}

				Charset = StringCache::Add(CopyFrom.Charset);

				return;
			}

			String::StringSeg::StringSeg(const char * const In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Width = Is8Bit_t;
				Charset = nullptr;
				IsReadOnly = false;

				if (In != nullptr) {
					if (Len == 0) {
						Str.Utf8 = new std::string(In);
						StrUnits = Str.Utf8->length();

					} else {
						Str.Utf8 = new std::string();
						Str.Utf8->append(In, Len);
					}

					StrUnits = Str.Utf8->length();
				}

				Charset = StringCache::Add(Current8BitCharset);

				return;
			}

			String::StringSeg::StringSeg(const char16_t * const In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Width = Is16Bit_t;
				Charset = nullptr;
				IsReadOnly = false;

				if (In != nullptr) {
					if (Len == 0) {
						Str.Utf16 = new std::u16string(In);

					} else {
						Str.Utf16 = new std::u16string();
						Str.Utf16->append(In, Len);
					}

					StrUnits = Str.Utf16->length();
				}

				Charset = StringCache::Add(Current16BitCharset);

				return;
			}

			String::StringSeg::StringSeg(const char32_t * const In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Charset = nullptr;
				Width = Is32Bit_t;
				IsReadOnly = false;

				if (In != nullptr) {
					if (Len == 0) {
						Str.Utf32 = new std::u32string(In);

					} else {
						Str.Utf32 = new std::u32string();
						Str.Utf32->append(In, Len);
					}

					StrUnits = Str.Utf32->length();
				}

				Charset = StringCache::Add(Current32BitCharset);

				return;
			}

			String::StringSeg::StringSeg(const wchar_t * const In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Charset = nullptr;
				Width = IsWBit_t;
				IsReadOnly = false;

				if (In != nullptr) {
					if (Len == 0) {
						Str.W = new std::wstring(In);

					} else {
						Str.W = new std::wstring();
						Str.W->append(In, Len);
					}

					StrUnits = Str.W->length();
				}

				Charset = StringCache::Add(CurrentWBitCharset);

				return;
			}

			String::StringSeg::StringSeg(const std::wstring & In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Charset = nullptr;
				Width = IsWBit_t;
				IsReadOnly = false;

				if (Len == 0) {
					Str.W = new std::wstring(In.c_str());

				} else {
					Str.W = new std::wstring();
					Str.W->append(In.c_str(), Len);
				}

				StrUnits = Str.W->length();
				Charset = StringCache::Add(CurrentWBitCharset);

				return;
			}

			String::StringSeg::StringSeg(const std::string & In,
			                             size_t Len)
			{
				Str.Utf8 = nullptr;
				Language = 0;
				Charset = nullptr;
				Width = Is8Bit_t;
				IsReadOnly = false;

				if (In.length() == 0) {
					Str.Utf8 = new std::string(In);

				} else {
					Str.Utf8 = new std::string();
					Str.Utf8->append(In, Len);
				}

				StrUnits = Str.Utf8->length();
				Charset = StringCache::Add(Current8BitCharset);

				return;
			}

			String::StringSeg::StringSeg(const std::u16string & In,
			                             size_t Len)
			{
				Str.Utf16 = nullptr;
				Language = 0;
				Width = Is16Bit_t;
				Charset = nullptr;
				IsReadOnly = false;

				if (In.length() == 0) {
					Str.Utf16 = new std::u16string(In);

				} else {
					Str.Utf16 = new std::u16string();
					Str.Utf16->append(In, Len);
				}

				StrUnits = Str.Utf16->length();
				Charset = StringCache::Add(Current16BitCharset);

				return;
			}

			String::StringSeg::StringSeg(const std::u32string & In,
			                             size_t Len)
			{
				Str.Utf32 = nullptr;
				Language = 0;
				Charset = nullptr;
				Width = Is32Bit_t;
				IsReadOnly = false;

				if (In.length() == 0) {
					Str.Utf32 = new std::u32string(In);

				} else {
					Str.Utf32 = new std::u32string();
					Str.Utf32->append(In, Len);
				}

				StrUnits = Str.Utf32->length();
				Charset = StringCache::Add(Current32BitCharset);

				return;
			}

			String::StringSeg::~StringSeg()
			{
				Clear();

				return;
			}

			size_t
			String::StringSeg::Length() const
			{
				size_t		Results = 0;

				if (IsReadOnly) {
					Results = StrUnits;

				} else {
					switch (Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							if (Str.Utf8 != nullptr) {
								Results = Str.Utf8->length();
							}

							break;

						case Is16Bit_t:
							if (Str.Utf16 != nullptr) {
								Results = Str.Utf16->length();
							}

							break;

						case Is32Bit_t:
							if (Str.Utf32 != nullptr) {
								Results = Str.Utf32->length();
							}

							break;

						case IsWBit_t:
							if (Str.W != nullptr) {
								Results = Str.W->length();
							}

							break;
					}
				}

				return (Results);
			}

			void
			String::StringSeg::SetLocale(locale_t TheLocale)
			{
				Language = TheLocale;

				return;
			}

			void
			String::StringSeg::Set(const StringSeg & CopyFrom,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Clear();
				Language = TheLocale;
				Copy(CopyFrom, Len);
				Charset = StringCache::Add(CopyFrom.Charset);
			}

			void
			String::StringSeg::Set(const char * const In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Clear();
				Language = TheLocale;
				Width = Is8Bit_t;
				StrUnits = 0;

				if (In != nullptr) {
					Str.Utf8 = new std::string();

					if (Len == 0) {
						Str.Utf8->append(In);

					} else {
						Str.Utf8->append(In, Len);
					}

					StrUnits = Str.Utf8->length();
				}

				Charset = StringCache::Add(Current8BitCharset);

				return;
			}

			void
			String::StringSeg::Set(const char16_t * const In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Clear();
				Language = TheLocale;
				Width = Is16Bit_t;
				StrUnits = 0;

				if (In != nullptr) {
					Str.Utf16 = new std::u16string();

					if (Len == 0) {
						Str.Utf16->append(In);

					} else {
						Str.Utf16->append(In, Len);
					}

					StrUnits = Str.Utf16->length();
				}

				Charset = StringCache::Add(Current16BitCharset);

				return;
			}

			void
			String::StringSeg::Set(const char32_t * const In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Clear();
				Language = TheLocale;
				Width = Is32Bit_t;
				StrUnits = 0;

				if (In != nullptr) {
					Str.Utf32 = new std::u32string();

					if (Len == 0) {
						Str.Utf32->append(In);

					} else {
						Str.Utf32->append(In, Len);
					}

					StrUnits = Str.Utf32->length();
				}

				Charset = StringCache::Add(Current32BitCharset);

				return;
			}

			void
			String::StringSeg::Set(const wchar_t * const In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Clear();
				Language = TheLocale;
				Width = IsWBit_t;
				StrUnits = 0;

				if (In != nullptr) {
					Str.W = new std::wstring();

					if (Len == 0) {
						Str.W->append(In);

					} else {
						Str.W->append(In, Len);
					}

					StrUnits = Str.W->length();
				}

				Charset = StringCache::Add(CurrentWBitCharset);

				return;
			}

			void
			String::StringSeg::Set(const std::string & In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Set(In.c_str(), Len, TheLocale);

				return;
			}

			void
			String::StringSeg::Set(const std::u16string & In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Set(In.c_str(), Len, TheLocale);

				return;
			}

			void
			String::StringSeg::Set(const std::u32string & In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Set(In.c_str(), Len, TheLocale);

				return;
			}

			void
			String::StringSeg::Set(const std::wstring & In,
			                       size_t Len,
			                       locale_t TheLocale)
			{
				Set(In.c_str(), Len, TheLocale);

				return;
			}

			void
			String::StringSeg::Copy(const StringSeg & CopyFrom,
			                        size_t Len)
			{
				Clear();
				Language = CopyFrom.Language;

				Width = CopyFrom.Width;

				switch (CopyFrom.Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (CopyFrom.IsReadOnly) {
							Set(CopyFrom.Str.RO8, CopyFrom.StrUnits);

						} else {
							if (CopyFrom.Str.Utf8 != nullptr) {
								Set(*CopyFrom.Str.Utf8, Len);
							}
						}

						break;

					case Is16Bit_t:
						if (CopyFrom.IsReadOnly) {
							Set(CopyFrom.Str.RO16, CopyFrom.StrUnits);

						} else {
							if (CopyFrom.Str.Utf16 != nullptr) {
								Set(*CopyFrom.Str.Utf16, Len);
							}
						}

						break;

					case Is32Bit_t:
						if (CopyFrom.IsReadOnly) {
							Set(CopyFrom.Str.RO32, CopyFrom.StrUnits);

						} else {
							if (CopyFrom.Str.Utf32 != nullptr) {
								Set(*CopyFrom.Str.Utf32, Len);
							}
						}

						break;

					case IsWBit_t:
						if (CopyFrom.IsReadOnly) {
							Set(CopyFrom.Str.ROW, CopyFrom.StrUnits);

						} else {
							if (CopyFrom.Str.W != nullptr) {
								Set(*CopyFrom.Str.W, Len);
							}
						}

						break;
				}

				return;
			}

			void
			String::StringSeg::Clear()
			{
				switch (Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						if (IsReadOnly) {
							Str.RO8 = nullptr;

						} else {
							if (Str.Utf8 != nullptr) {
								delete Str.Utf8;
								Str.Utf8 = nullptr;
							}
						}

						break;

					case Is16Bit_t:
						if (IsReadOnly) {
							Str.RO16 = nullptr;

						} else {
							if (Str.Utf16 != nullptr) {
								delete Str.Utf16;
								Str.Utf16 = nullptr;
							}
						}

						break;

					case Is32Bit_t:
						if (IsReadOnly) {
							Str.RO32 = nullptr;

						} else {
							if (Str.Utf32 != nullptr) {
								delete Str.Utf32;
								Str.Utf32 = nullptr;
							}
						}

						break;

					case IsWBit_t:
						if (IsReadOnly) {
							Str.ROW = nullptr;

						} else {
							if (Str.W != nullptr) {
								delete Str.W;
								Str.W = nullptr;
							}

							break;
						}
				}

				Language = 0;

				if (Charset != nullptr) {
					StringCache::Remove(Charset);
					Charset = nullptr;
				}

				return;
			}

		}
	}
}
