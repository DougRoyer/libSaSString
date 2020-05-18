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

			// The result is in _InputWidth units.
			//
			size_t
			String::Length() const
			{
				size_t		Results = 0;

				if (_ROString) {
					Results = _RO->StrUnits;

				} else {

					switch (InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = strlen(Get8());
							break;

						case Is16Bit_t:
							Results = strlen(Get16());
							break;

						case Is32Bit_t:
							Results = strlen(Get32());
							break;

						case IsWBit_t:
							Results = strlen(GetW());
							break;
					}
				}

				return (Results);
			}

			size_t
			String::strlen(const char * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
					Results = ::strlen(FromStr);
				}

				return (Results);
			}

			size_t
			String::strlen(const char16_t * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
#if __SIZEOF_WCHAR_T__ == 2
					Results = ::wcslen((wchar_t *)FromStr);
#elif __SIZEOF_WCHAR_T__ == 4
					const char16_t * Ptr = FromStr;

					while (*Ptr != 0) {
						Results++;
						Ptr++;
					}

#else
					ERROR What size is WCHAR_T;
#endif
				}

				return (Results);
			}

			size_t
			String::strlen(const char32_t * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
#if __SIZEOF_WCHAR_T__ == 4
					Results = ::wcslen((wchar_t *)FromStr);
#elif __SIZEOF_WCHAR_T__ == 2
					const char32_t * Ptr = FromStr;

					while (*Ptr != 0) {
						Results++;
						Ptr++;
					}

#else
					ERROR What size is WCHAR_T;
#endif
				}

				return (Results);
			}

			size_t
			String::strlen(const wchar_t * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
					Results = wcslen(FromStr);
				}

				return (Results);
			}

			size_t
			String::strlen(const String & FromStr)
			{
				size_t		Results = 0;

				Results = FromStr.Length();

				return (Results);
			}

			size_t
			String::strlen(const ROString & FromStr)
			{
				size_t		Results = 0;

				Results = FromStr.Length();

				return (Results);
			}

			size_t
			String::CharacterLen() const
			{
				size_t			Results = 0;

				if (IsReadOnly()) {
					size_t		NotUsed = 0;
					ROString	*	RO = (ROString *)this;

					switch (InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = CharacterLen(RO->Get8(NotUsed));
							break;

						case Is16Bit_t:
							Results = CharacterLen(RO->Get16(NotUsed));
							break;

						case Is32Bit_t:
							Results = CharacterLen(RO->Get32(NotUsed));
							break;

						case IsWBit_t:
							Results = CharacterLen(RO->GetW(NotUsed));
							break;
					}

				} else {

					switch (InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = CharacterLen(Get8());
							break;

						case Is16Bit_t:
							Results = CharacterLen(Get16());
							break;

						case Is32Bit_t:
							Results = CharacterLen(Get32());
							break;

						case IsWBit_t:
							Results = CharacterLen(GetW());
							break;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const char * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
					size_t		Units = 0;
					const char	*	Ptr = FromStr;

					while (*Ptr != 0) {
						Units = CharacterUnits(Ptr);
						Ptr += Units;
						Results++;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const char16_t * const FromStr)
			{
				size_t				Results = 0;

				if (FromStr != nullptr) {
					size_t			Units = 0;
					const char16_t	*	Ptr = FromStr;

					while (*Ptr != 0) {
						Units = CharacterUnits(Ptr);
						Ptr += Units;
						Results++;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const char32_t * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
					size_t			Units = 0;
					const char32_t	*	Ptr = FromStr;

					while (*Ptr != 0) {
						Units = CharacterUnits(Ptr);
						Ptr += Units;
						Results++;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const wchar_t * const FromStr)
			{
				size_t		Results = 0;

				if (FromStr != nullptr) {
					size_t		Units = 0;
					const wchar_t	*	Ptr = FromStr;

					while (*Ptr != 0) {
						Units = CharacterUnits(Ptr);
						Ptr += Units;
						Results++;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const std::string & FromStr)
			{
				return (CharacterLen(FromStr.c_str()));
			}

			size_t
			String::CharacterLen(const std::u16string & FromStr)
			{
				return (CharacterLen(FromStr.c_str()));
			}

			size_t
			String::CharacterLen(const std::u32string & FromStr)
			{
				return (CharacterLen(FromStr.c_str()));
			}

			size_t
			String::CharacterLen(const std::wstring & FromStr)
			{
				return (CharacterLen(FromStr.c_str()));
			}

			size_t
			String::CharacterLen(const String & FromStr)
			{
				size_t			Results = 0;

				if (FromStr.IsReadOnly()) {
					Results = CharacterLen((const ROString &)FromStr);

				} else {

					switch (FromStr.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = CharacterLen(FromStr.Get8());
							break;

						case Is16Bit_t:
							Results = CharacterLen(FromStr.Get16());
							break;

						case Is32Bit_t:
							Results = CharacterLen(FromStr.Get32());
							break;

						case IsWBit_t:
							Results = CharacterLen(FromStr.GetW());
							break;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const ROString & FromStr)
			{
				size_t			Results = 0;

				switch (FromStr.InputWidth()) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t: {
							size_t		Len = 0;
							size_t		Units = 0;
							const char	*	Ptr = FromStr.Get8(Len);

							while (Len > 0) {
								Units = CharacterUnits(Ptr);
								Ptr += Units;
								Results++;
								Len -= Units;
							}
						}
						break;

					case Is16Bit_t: {
							size_t			Len = 0;
							size_t			Units = 0;
							const char16_t	*	Ptr = FromStr.Get16(Len);

							while (Len > 0) {
								Units = CharacterUnits(Ptr);
								Ptr += Units;
								Results++;
								Len -= Units;
							}
						}
						break;

					case Is32Bit_t: {
							size_t			Len = 0;
							size_t			Units = 0;
							const char32_t	*	Ptr = FromStr.Get32(Len);

							while (Len > 0) {
								Units = CharacterUnits(Ptr);
								Ptr += Units;
								Results++;
								Len -= Units;
							}
						}
						break;

					case IsWBit_t: {
							size_t			Len = 0;
							size_t			Units = 0;
							const wchar_t	*	Ptr = FromStr.GetW(Len);

							while (Len > 0) {
								Units = CharacterUnits(Ptr);
								Ptr += Units;
								Results++;
								Len -= Units;
							}
						}
						break;
				}

				return (Results);
			}

			size_t
			String::CharacterLen(const_iterator & FromIt) const
			{
				size_t		Results = 0;

				while (FromIt != cend()) {
					//Units = CharacterUnits(FromIt);
					FromIt++;
					Results++;
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const iterator & It)
			{
				size_t		Results = 0;

				switch (It._Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = CharacterUnits(It.str8());
						break;

					case Is16Bit_t:
						Results = CharacterUnits(It.str16());
						break;

					case Is32Bit_t:
						Results = CharacterUnits(It.str32());
						break;

					case IsWBit_t:
						Results = CharacterUnits(It.strW());
						break;
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const const_iterator & It)
			{
				size_t		Results = 0;

				switch (It._Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Results = CharacterUnits(It.str8());
						break;

					case Is16Bit_t:
						Results = CharacterUnits(It.str16());
						break;

					case Is32Bit_t:
						Results = CharacterUnits(It.str32());
						break;

					case IsWBit_t:
						Results = CharacterUnits(It.strW());
						break;
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const char SOne)
			{
				size_t			Results = 0;

				unsigned char	One = (unsigned char)SOne;

				if (strcmp(Current8BitCharset, Utf8_s) == 0) {

					if (One < 0x7f) {
						Results = 1;

					} else if (One >= 0xc2 && One < 0xe0) {
						Results = 2;

					} else if (One >= 0e0 && One < 0xf0) {
						Results = 3;

					} else if (One >= 0xf0 && One < 0xf4) {
						Results = 4;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const char * const Str)
			{
				size_t			Results = 0;

				if (Str != nullptr) {
					// We only test the 1 character (not octet).
					//
					Results = CharacterUnits(Str[0]);
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const std::string & Str)
			{
				return (CharacterUnits(Str.c_str()[0]));
			}

			size_t
			String::CharacterUnits(const char16_t One)
			{
				size_t			Results = 0;

				// UTF-16, UTF-16LE, UTF-16BE
				//
				if (strncmp(Current16BitCharset, Utf16_s, 6) == 0) {
					if (One < 0xd800) {
						Results = 1;

					} else if (One >= 0xd800) {
						Results = 2;
					}
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const char16_t * const Str)
			{
				size_t			Results = 0;

				if (Str != nullptr) {
					Results = CharacterUnits(Str[0]);
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const std::u16string & Str)
			{
				return (CharacterUnits(Str.c_str()[0]));
			}

			size_t
			String::CharacterUnits(const char32_t /*One*/)
			{
				size_t		Results = 0;

				if (strncmp(Current32BitCharset, Utf32_s, 6) == 0) {
					Results = 1;
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const char32_t * const Str)
			{
				size_t			Results = 0;

				if (Str != nullptr) {
					Results = CharacterUnits(Str[0]);
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const std::u32string & Str)
			{
				return (CharacterUnits(Str.c_str()[0]));
			}

			size_t
			String::CharacterUnits(const wchar_t One)
			{
				size_t			Results = 0;

				// UTF-16, UTF-16LE, UTF-16BE
				//
				if (strncmp(CurrentWBitCharset, Utf16_s, 6) == 0) {
					if (One < 0xd800) {
						Results = 1;

					} else if (One >= 0xd800) {
						Results = 2;
					}

				} else if (strncmp(CurrentWBitCharset, Utf32_s, 6) == 0) {
					Results = 1;
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const wchar_t * const Str)
			{
				size_t			Results = 0;

				if (Str != nullptr) {
					Results = CharacterUnits(Str[0]);
				}

				return (Results);
			}

			size_t
			String::CharacterUnits(const std::wstring & Str)
			{
				return (CharacterUnits(Str.c_str()[0]));
			}

			size_t
			String::CharacterUnits(const String & Str)
			{
				size_t			Results = 0;

				if (Str.IsReadOnly()) {
					size_t		Len = 0;
					ROString	*	ROStr = (ROString *)&Str;

					switch (Str.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = CharacterUnits(ROStr->Get8(Len));
							break;

						case Is16Bit_t:
							Results = CharacterUnits(ROStr->Get16(Len));
							break;

						case Is32Bit_t:
							Results = CharacterUnits(ROStr->Get32(Len));
							break;

						case IsWBit_t:
							Results = CharacterUnits(ROStr->Get8(Len));
							break;
					}

				} else {
					switch (Str.InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = CharacterUnits(Str.Get8());
							break;

						case Is16Bit_t:
							Results = CharacterUnits(Str.Get16());
							break;

						case Is32Bit_t:
							Results = CharacterUnits(Str.Get32());
							break;

						case IsWBit_t:
							Results = CharacterUnits(Str.Get8());
							break;
					}
				}

				return (Results);
			}

			size_t
			String::Octets8() const
			{
				size_t		Results = 0;

				if (_ROString) {
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _RO->StrUnits;
							break;

						case Is16Bit_t:
							Results = (_RO->StrUnits * sizeof(char16_t));
							break;

						case Is32Bit_t:
							break;
							Results = (_RO->StrUnits * sizeof(char32_t));

						case IsWBit_t:
							break;
							Results = (_RO->StrUnits * sizeof(wchar_t));
					}

				} else {
					Results = strlen(Get8());
				}

				return (Results);
			}

			size_t
			String::Octets16() const
			{
				size_t		Results = 0;

				if (_ROString) {
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _RO->StrUnits;
							break;

						case Is16Bit_t:
							Results = (_RO->StrUnits * sizeof(char16_t));
							break;

						case Is32Bit_t:
							break;
							Results = (_RO->StrUnits * sizeof(char32_t));

						case IsWBit_t:
							break;
							Results = (_RO->StrUnits * sizeof(wchar_t));
					}

				} else {
					Results = strlen(Get16()) * sizeof(char16_t);
				}

				return (Results);
			}

			size_t
			String::Octets32() const
			{
				size_t		Results = 0;

				if (_ROString) {
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _RO->StrUnits;
							break;

						case Is16Bit_t:
							Results = (_RO->StrUnits * sizeof(char16_t));
							break;

						case Is32Bit_t:
							break;
							Results = (_RO->StrUnits * sizeof(char32_t));

						case IsWBit_t:
							break;
							Results = (_RO->StrUnits * sizeof(wchar_t));
					}

				} else {
					Results = strlen(Get32()) * sizeof(char32_t);
				}

				return (Results);
			}

			size_t
			String::OctetsW() const
			{
				size_t		Results = 0;

				if (_ROString) {
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							Results = _RO->StrUnits;
							break;

						case Is16Bit_t:
							Results = (_RO->StrUnits * sizeof(char16_t));
							break;

						case Is32Bit_t:
							break;
							Results = (_RO->StrUnits * sizeof(char32_t));

						case IsWBit_t:
							break;
							Results = (_RO->StrUnits * sizeof(wchar_t));
					}

				} else {
					Results = strlen(GetW()) * sizeof(wchar_t);
				}

				return (Results);
			}

		}
	}
}
