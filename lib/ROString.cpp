//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2019-2020 Software and Services LLC, All Rights Reserved.
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

// Indicate to the library at compile time, that
// we do support multibyte characters.
//

#include <SaS/Common/CopyRightNotice.h>
#include <SaS/String/StringCache.hpp>
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			ROString::ROString(const char * const Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current8BitLocale;
				NewSeg->Width = Is8Bit_t;
				NewSeg->Str.RO8 = Start;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				NewSeg->StrUnits = Len;

				return;
			}

			ROString::ROString(const char16_t * const Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current16BitLocale;
				NewSeg->Width = Is16Bit_t;
				NewSeg->Str.RO16 = Start;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				NewSeg->StrUnits = Len;

				return;
			}

			ROString::ROString(const char32_t * const Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current32BitLocale;
				NewSeg->Width = Is32Bit_t;
				NewSeg->Str.RO32 = Start;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				NewSeg->StrUnits = Len;

				return;
			}


			ROString::ROString(const wchar_t * const Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _CurrentWBitLocale;
				NewSeg->Width = IsWBit_t;
				NewSeg->Str.ROW = Start;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				NewSeg->StrUnits = Len;

				return;
			}


			ROString::ROString(const std::string & Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current8BitLocale;
				NewSeg->Width = Is8Bit_t;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					NewSeg->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					NewSeg->StrUnits = Len;
				}

				NewSeg->Str.RO8 = Start.c_str();

				return;
			}


			ROString::ROString(const std::u16string & Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current16BitLocale;
				NewSeg->Width = Is16Bit_t;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					NewSeg->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					NewSeg->StrUnits = Len;
				}

				NewSeg->Str.RO16 = Start.c_str();

				return;
			}


			ROString::ROString(const std::u32string & Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _Current32BitLocale;
				NewSeg->Width = Is32Bit_t;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					NewSeg->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					NewSeg->StrUnits = Len;
				}

				NewSeg->Str.RO32 = Start.c_str();

				return;
			}


			ROString::ROString(const std::wstring & Start, size_t Len)
				: String()
			{
				StringSeg		*	NewSeg = new StringSeg();

				_Segments.push_back(NewSeg);
				_IsROString = true;
				NewSeg->Locale = _CurrentWBitLocale;
				NewSeg->Width = IsWBit_t;
				NewSeg->IsReadOnly = true;

				if (Len == 0) {
					NewSeg->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					NewSeg->StrUnits = Len;
				}

				NewSeg->Str.ROW = Start.c_str();

				return;
			}


			ROString::ROString(const String & Init, size_t Len)
				: String()
			{
				std::vector<StringSeg *>::const_iterator	InIt;
				StringSeg		*	NewSeg = nullptr;
				StringSeg		*	OldSeg = nullptr;
				size_t				ToGo = Len;

				_IsROString = true;

				if (Len == 0) {
					Len = Init.Length();
					ToGo = Len;
				}

				for (InIt = Init._Segments.begin(); InIt != Init._Segments.end(); InIt++) {
					OldSeg = * InIt;

					if (OldSeg != nullptr) {
						if ((OldSeg->StrUnits + NewSeg->StrUnits) < ToGo) {
							ToGo -= OldSeg->StrUnits;
							NewSeg = new StringSeg(*OldSeg);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);

							if (ToGo <= 0) {
								break;
							}

						} else {
							NewSeg = new StringSeg(*OldSeg, ToGo);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);
							break;
						}
					}
				}

				return;
			}

			ROString::ROString(const ROString & Init, size_t Len)
				: String()
			{
				std::vector<StringSeg *>::const_iterator	InIt;
				StringSeg		*	NewSeg = nullptr;
				StringSeg		*	OldSeg = nullptr;
				size_t				ToGo = Len;

				_IsROString = true;

				if (Len == 0) {
					Len = Init.Length();
					ToGo = Len;
				}

				for (InIt = Init._Segments.begin(); InIt != Init._Segments.end(); InIt++) {
					OldSeg = * InIt;

					if (OldSeg != nullptr) {
						if ((OldSeg->StrUnits + NewSeg->StrUnits) < ToGo) {
							ToGo -= OldSeg->StrUnits;
							NewSeg = new StringSeg(*OldSeg);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);

							if (ToGo <= 0) {
								break;
							}

						} else {
							NewSeg = new StringSeg(*OldSeg, ToGo);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);
							break;
						}
					}
				}

				return;
			}

			ROString::ROString(const String & Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String()
			{
				std::vector<StringSeg *>::const_iterator	InIt;
				StringSeg		*	NewSeg = nullptr;
				StringSeg		*	OldSeg = nullptr;
				size_t				ToGo = Len;

				_IsROString = true;

				if (Len == 0) {
					Len = Init.Length();
					ToGo = Len;
				}

				for (InIt = Init._Segments.begin(); InIt != Init._Segments.end(); InIt++) {
					OldSeg = * InIt;

					if (OldSeg != nullptr) {
						if ((OldSeg->StrUnits + NewSeg->StrUnits) < ToGo) {
							ToGo -= OldSeg->StrUnits;
							NewSeg = new StringSeg(*OldSeg);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);

							if (ToGo <= 0) {
								break;
							}

						} else {
							NewSeg = new StringSeg(*OldSeg, ToGo);
							NewSeg->IsReadOnly = true;
							_Segments.push_back(NewSeg);
							break;
						}
					}
				}

				return;
			}

			ROString::ROString(const ROString & Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String()
			{
				IsROString = true;
				_RO = new StringSeg();
				_RO->Width = Init._RO->Width;
				_RO->IsReadOnly = true;

				size_t		Measured = 0;
				const_iterator	At(It);

				// How many character to the end, or to Len?
				//
				while (At != Init.cend()) {
					At++;
					Measured++;

					if (Measured == Len) {
						break;
					}
				}

				_RO->StrUnits = std::distance(It, At);

				switch (_RO->Width) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						_RO->Str.RO8 = It.str8();
						break;

					case Is16Bit_t:
						_RO->Str.RO16 = It.str16();
						break;

					case Is32Bit_t:
						_RO->Str.RO32 = It.str32();
						break;

					case IsWBit_t:
						_RO->Str.ROW = It.strW();
						break;

				}

				return;
			}


			ROString::~ROString()
			{
				IsROString = false;

				if (IsROString) {

					// Can not delete RO (const or staticlly alloced strings),
					// clear the data first.
					//
					_RO->Str.RO8 = nullptr;
					delete _RO;
					_RO = nullptr;
				}

				return;
			}


			bool_t
			ROString::xdr(XDR * xdrs)
			{
				bool_t			Results = false;

				if (xdrs != nullptr) {
					switch (xdrs->x_op) {

						case XDR_ENCODE: {
								size_t			Len = 0;
								const char	*	Str = Get8(Len);

								Results = xdr_string(xdrs, (char **)&Str, (u_int)Len);
							}
							break;

						case XDR_DECODE:
							/* CAN NOT DECODE a Read Only String */
							break;

						case XDR_FREE: {
								Results = true;
							}
							break;
					}
				}

				return (Results);
			}

			const char	*
			ROString::Get8(size_t & Len) const
			{
				const char	*	Results = nullptr;


				if (IsROString) {
					if (_RO->Width == Is8Bit_t) {
						Results = _RO->Str.RO8;
						Len = _RO->StrUnits;
					}
				}

				return (Results);
			}

			const char16_t	*
			ROString::Get16(size_t & Len) const
			{
				const char16_t	*	Results = nullptr;

				if (IsROString) {
					if (_RO->Width == Is16Bit_t) {
						Results = _RO->Str.RO16;
						Len = _RO->StrUnits;
					}
				}

				return (Results);
			}

			const char32_t	*
			ROString::Get32(size_t & Len) const
			{
				const char32_t	*	Results = nullptr;

				if (IsROString) {
					if (_RO->Width == Is32Bit_t) {
						Results = _RO->Str.RO32;
						Len = _RO->StrUnits;
					}
				}

				return (Results);
			}

			const wchar_t	*
			ROString::GetW(size_t & Len) const
			{
				const wchar_t	*	Results = nullptr;

				if (IsROString) {
					if (_RO->Width == IsWBit_t) {
						Results = _RO->Str.ROW;
						Len = _RO->StrUnits;
					}
				}

				return (Results);
			}

			CharacterUnitWidth_e
			ROString::Width() const
			{
				CharacterUnitWidth_e	Results = IsUnknownBit_t;

				if (IsROString) {
					Results = _RO->Width;
				}

				return (Results);
			}

			ROString::ROString(String::const_iterator & It,
			                   size_t Len)
				: String()
			{
				switch (It.Width()) {

					case Is8Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is8Bit_t;
						_RO->Str.RO8 = It.str8();
						_RO->StrUnits = Len;
						break;

					case Is16Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is16Bit_t;
						_RO->Str.RO16 = It.str16();
						_RO->StrUnits = Len;
						break;

					case Is32Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is32Bit_t;
						_RO->Str.RO32 = It.str32();
						_RO->StrUnits = Len;
						break;

					case IsWBit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = IsWBit_t;
						_RO->Str.ROW = It.strW();
						_RO->StrUnits = Len;
						break;

					default:
						/*EMPTY*/
						break;

				}

				return;
			}
			ROString::ROString(String::iterator & It,
			                   size_t Len)
				: String()
			{
				switch (It.Width()) {

					case Is8Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is8Bit_t;
						_RO->Str.RO8 = It.str8();
						_RO->StrUnits = Len;
						break;

					case Is16Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is16Bit_t;
						_RO->Str.RO16 = It.str16();
						_RO->StrUnits = Len;
						break;

					case Is32Bit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = Is32Bit_t;
						_RO->Str.RO32 = It.str32();
						_RO->StrUnits = Len;
						break;

					case IsWBit_t:
						IsROString = true;
						_RO = new StringSeg();
						_RO->Width = IsWBit_t;
						_RO->Str.ROW = It.strW();
						_RO->StrUnits = Len;
						break;

					default:
						/*EMPTY*/
						break;

				}

				return;
			}

		}
	}
}
