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

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			ROString::ROString(const char * const Start, size_t Len)
				: String(Default8BitCharset, Default8BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is8Bit_t;
				_RO->Str.RO8 = Start;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				_RO->StrUnits = Len;

				return;
			}


			ROString::ROString(const char16_t * const Start, size_t Len)
				: String(Default16BitCharset, Default16BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is16Bit_t;
				_RO->Str.RO16 = Start;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				_RO->StrUnits = Len;

				return;
			}


			ROString::ROString(const char32_t * const Start, size_t Len)
				: String(Default32BitCharset, Default32BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is32Bit_t;
				_RO->Str.RO32 = Start;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				_RO->StrUnits = Len;

				return;
			}


			ROString::ROString(const wchar_t * const Start, size_t Len)
				: String(DefaultWBitCharset, DefaultWBitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = IsWBit_t;
				_RO->Str.ROW = Start;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					Len = strlen(Start);
				}

				_RO->StrUnits = Len;

				return;
			}


			ROString::ROString(const std::string & Start, size_t Len)
				: String(Default8BitCharset, Default8BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is8Bit_t;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					_RO->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					_RO->StrUnits = Len;
				}

				_RO->Str.RO8 = Start.c_str();

				return;
			}


			ROString::ROString(const std::u16string & Start, size_t Len)
				: String(Default16BitCharset, Default16BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is16Bit_t;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					_RO->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					_RO->StrUnits = Len;
				}

				_RO->Str.RO16 = Start.c_str();

				return;
			}


			ROString::ROString(const std::u32string & Start, size_t Len)
				: String(Default32BitCharset, Default32BitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Is32Bit_t;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					_RO->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					_RO->StrUnits = Len;
				}

				_RO->Str.RO32 = Start.c_str();

				return;
			}


			ROString::ROString(const std::wstring & Start, size_t Len)
				: String(DefaultWBitCharset, DefaultWBitWidth)
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = IsWBit_t;
				_RO->IsReadOnly = true;

				if (Len == 0) {
					_RO->StrUnits = Start.length();

				} else {
					if (Len > Start.length()) {
						Len = Start.length();
					}

					_RO->StrUnits = Len;
				}

				_RO->Str.ROW = Start.c_str();

				return;
			}


			ROString::ROString(const String & Init, size_t Len)
				: String(Init.InputCharset(), Init.InputWidth())
			{
				bool			Has8 = false;
				bool			Has16 = false;
				bool			Has32 = false;
				bool			HasW = false;

				_ROString = true;

				if (Init._ROString) {
					_RO = new StringSeg();
					_RO->Width = Init._RO->Width;

					// It does not matter which we use, they are a union of pointers.
					//
					_RO->Str.RO16 = Init._RO->Str.RO16;
					_RO->IsReadOnly = true;

					if (Len == 0) {
						_RO->StrUnits = Init._RO->StrUnits;

					} else {
						if (Len > Init._RO->StrUnits) {
							Len = Init._RO->StrUnits;
						}

						_RO->StrUnits = Len;
					}

				} else {
					std::vector<StringSeg *>::const_iterator	InIt;
					StringSeg		*	Seg = nullptr;
					const char		*	Cs8 = Current8BitCharset;
					const char		*	Cs16 = Current16BitCharset;
					const char		*	Cs32 = Current32BitCharset;
					const char		*	CsW = CurrentWBitCharset;

					// We upgrade to the widest characters set used in Init.
					//
					for (InIt = Init._Segments.begin()
					            ; InIt != Init._Segments.end()
					     ; InIt++) {

						Seg = *InIt;

						if (Seg != nullptr) {
							switch (Seg->Width) {

								case Is8Bit_t:
									Has8 = true;

									if (Seg->Charset != nullptr) {
										Cs8 = Seg->Charset;
									}

									break;

								case Is16Bit_t:
									Has16 = true;

									if (Seg->Charset != nullptr) {
										Cs16 = Seg->Charset;
									}

									break;

								case Is32Bit_t:
									Has32 = true;

									if (Seg->Charset != nullptr) {
										Cs32 = Seg->Charset;
									}

									break;

								case IsWBit_t:
									HasW = true;

									if (Seg->Charset != nullptr) {
										CsW = Seg->Charset;
									}

									break;

								default:
									/*EMPTY*/
									break;

							}
						}
					}

					_ROString = true;
					_RO = new StringSeg();
					_RO->IsReadOnly = true;

					// Use the widest character type.
					//
					if (Has32) {
						_RO->Str.RO32 = Init.Get32();
						_RO->Width = Is32Bit_t;
						_InputWidth = Is32Bit_t;
						_InputCharset = strdup(Cs32);
						_RO->StrUnits = strlen(_RO->Str.RO32);

					} else if (HasW) {
						_RO->Str.ROW = Init.GetW();
						_RO->Width = IsWBit_t;
						_InputWidth = IsWBit_t;
						_InputCharset = strdup(CsW);
						_RO->StrUnits = strlen(_RO->Str.ROW);

					} else if (Has16) {
						_RO->Str.RO16 = Init.Get16();
						_RO->Width = Is16Bit_t;
						_InputWidth = Is16Bit_t;
						_InputCharset = strdup(Cs16);
						_RO->StrUnits = strlen(_RO->Str.RO16);

					} else if (Has8) {
						_RO->Str.RO8 = Init.Get8();
						_RO->Width = Is8Bit_t;
						_InputWidth = Is8Bit_t;
						_InputCharset = strdup(Cs8);
						_RO->StrUnits = strlen(_RO->Str.RO8);
					}
				}

				return;
			}


			ROString::ROString(const ROString & Init, size_t Len)
				: String(Init.InputCharset(), Init.InputWidth())
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Init._RO->Width;
				_RO->IsReadOnly = true;

				// It does not matter which we use, they are a union of pointers.
				//
				_RO->Str.RO16 = Init._RO->Str.RO16;

				if (Len == 0) {
					_RO->StrUnits = Init._RO->StrUnits;

				} else {
					if (Len > Init._RO->StrUnits) {
						Len = Init._RO->StrUnits;
					}

					_RO->StrUnits = Len;
				}

				return;
			}


			ROString::ROString(const String * Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String()
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->IsReadOnly = true;

				if (Init != nullptr) {
					_RO->Charset = strdup(Init->InputCharset());
					_RO->Width = Init->InputWidth();

					size_t		Measured = 0;
					const_iterator	At(It);

					// How many character to the end, or to Len?
					//
					while (At != Init->cend()) {
						At++;
						Measured++;

						if (Measured == Len) {
							break;
						}
					}

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
				}

				return;
			}


			ROString::ROString(const String & Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String(Init.InputCharset(), Init.InputWidth())
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Init.InputWidth();
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


			ROString::ROString(const ROString * Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String()
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->IsReadOnly = true;

				if (Init != nullptr) {
					_RO->Charset = strdup(Init->InputCharset());
					_RO->Width = Init->InputWidth();

					size_t		Measured = 0;
					const_iterator	At(It);

					// How many character to the end, or to Len?
					//
					while (At != Init->cend()) {
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
				}

				return;
			}


			ROString::ROString(const ROString & Init,
			                   String::const_iterator & It,
			                   size_t Len)
				: String(Init.InputCharset(), Init.InputWidth())
			{
				_ROString = true;
				_RO = new StringSeg();
				_RO->Width = Init.InputWidth();
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
				_ROString = false;

				if (_ROString) {

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


				if (_ROString) {
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

				if (_ROString) {
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

				if (_ROString) {
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

				if (_ROString) {
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

				if (_ROString) {
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
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is8Bit_t;
						_RO->Str.RO8 = It.str8();
						_RO->StrUnits = Len;
						break;

					case Is16Bit_t:
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is16Bit_t;
						_RO->Str.RO16 = It.str16();
						_RO->StrUnits = Len;
						break;

					case Is32Bit_t:
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is32Bit_t;
						_RO->Str.RO32 = It.str32();
						_RO->StrUnits = Len;
						break;

					case IsWBit_t:
						_ROString = true;
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
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is8Bit_t;
						_RO->Str.RO8 = It.str8();
						_RO->StrUnits = Len;
						break;

					case Is16Bit_t:
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is16Bit_t;
						_RO->Str.RO16 = It.str16();
						_RO->StrUnits = Len;
						break;

					case Is32Bit_t:
						_ROString = true;
						_RO = new StringSeg();
						_RO->Width = Is32Bit_t;
						_RO->Str.RO32 = It.str32();
						_RO->StrUnits = Len;
						break;

					case IsWBit_t:
						_ROString = true;
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
