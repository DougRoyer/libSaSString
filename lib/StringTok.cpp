//
// BEGIN_DOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2017-2019 Douglas Mark Royer, All Rights Reserved.
//
// Moved from libSaSXML - 2019
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
#include <SaS/String/ROString.hpp>
#include <sys/param.h>
#include <algorithm>
#include <ostream>

#include <unistr.h>
#include <unitypes.h>

#include <iconv.h>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			/**
			 * This object is used by sttok() when InStr is a
			 * String or ROString, it is saved in TokSave.SavePtr.
			 */
			struct TokSaveS {
				/**
				 * The strtok() code below allocates this, so free
				 * when done with this object.
				 */
				String::const_iterator	*	it;

				/**
				 * These are just copied pointers, do not free.
				 */
				union {
					const ROString	*	RO;
					const String		*	Str;
				} Ptr;
			};

			ROString	*
			String::strtok(const ROString * InStr,
			               const ROString & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (InStr != nullptr) {
					size_t		DLen = Delim.Length();
					size_t		Len = InStr->Length();

					CharacterUnitWidth_e	Width;

					if (InStr->IsReadOnly()) {
						Width = InStr->_RO->Width;

						// When needed, convert Delim to the same character set
						// and width as InStr.
						//
						if (strcmp(InStr->_RO->Charset, Delim._InputCharset) != 0) {
							DelimS = Delim.ToCharset(InStr->_InputCharset,
							                         InStr->_InputWidth);

						} else {
							DelimS = new String(Delim);
						}

					} else {
						Width = InStr->_InputWidth;

						// When needed, convert Delim to the same character set
						// and width as InStr.
						//
						if (strcmp(InStr->_InputCharset,
						           Delim._InputCharset) != 0) {
							DelimS = Delim.ToCharset(InStr->_InputCharset,
							                         InStr->_InputWidth);

						} else {
							DelimS = new String(Delim);
						}
					}

					if (DelimS != nullptr) {
						switch (Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok(InStr->_RO->Str.RO8, Len,
								                  DelimS->Get8(), DLen,
								                  Saved);
								break;

							case Is16Bit_t:
								Results = strtok(InStr, DelimS->Get16(), Saved);
								break;

							case Is32Bit_t:
								Results = strtok(InStr, DelimS->Get32(), Saved);
								break;

							case IsWBit_t:
								Results = strtok(InStr, DelimS->GetW(), Saved);
								break;

						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const ROString * InStr,
			               const char * Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (Delim != nullptr) {
					String		Tmp(Delim);

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset,
						                       Saved.Width);

						if (DelimS != nullptr) {

							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Width = InStr->_InputWidth;
						Saved.Charset = InStr->_InputCharset;

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok(InStr->_RO->Str.RO8,
									                  InStr->Length(),
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok(InStr->_RO->Str.RO16,
									                  InStr->Length(),
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok(InStr->_RO->Str.RO32,
									                  InStr->Length(),
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok(InStr->_RO->Str.ROW,
									                  InStr->Length(),
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const ROString * InStr,
			               const char16_t * Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (Delim != nullptr) {
					if (InStr == nullptr) {
						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(Saved.Charset,
						                       Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {

						Saved.Width = InStr->_InputWidth;
						Saved.Charset = InStr->_InputCharset;

						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(InStr->_InputCharset,
						                       InStr->_InputWidth);

						if (DelimS != nullptr) {
							switch (InStr->_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok(InStr->_RO->Str.RO8,
									                  InStr->Length(),
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok(InStr->_RO->Str.RO16,
									                  InStr->Length(),
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok(InStr->_RO->Str.RO32,
									                  InStr->Length(),
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok(InStr->_RO->Str.ROW,
									                  InStr->Length(),
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const ROString * InStr,
			               const char32_t * Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (Delim != nullptr) {
					if (InStr == nullptr) {
						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(Saved.Charset,
						                       Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {

						Saved.Width = InStr->_InputWidth;
						Saved.Charset = InStr->_InputCharset;

						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(InStr->_InputCharset,
						                       InStr->_InputWidth);

						if (DelimS != nullptr) {
							switch (InStr->_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok(InStr->_RO->Str.RO8,
									                  InStr->Length(),
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok(InStr->_RO->Str.RO16,
									                  InStr->Length(),
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok(InStr->_RO->Str.RO32,
									                  InStr->Length(),
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok(InStr->_RO->Str.ROW,
									                  InStr->Length(),
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const ROString * InStr,
			               const wchar_t * Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (Delim != nullptr) {
					if (InStr == nullptr) {
						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(Saved.Charset,
						                       Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {

						Saved.Width = InStr->_InputWidth;
						Saved.Charset = InStr->_InputCharset;

						String		Tmp(Delim);

						DelimS = Tmp.ToCharset(InStr->_InputCharset,
						                       InStr->_InputWidth);

						if (DelimS != nullptr) {
							switch (InStr->_RO->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok(InStr->_RO->Str.RO8,
									                  InStr->Length(),
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok(InStr->_RO->Str.RO16,
									                  InStr->Length(),
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok(InStr->_RO->Str.RO32,
									                  InStr->Length(),
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok(InStr->_RO->Str.ROW,
									                  InStr->Length(),
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const String * InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (InStr == nullptr) {

					DelimS = Delim.ToCharset(Saved.Charset, Saved.Width);

					if (DelimS != nullptr) {
						switch (Saved.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)nullptr,
								                  0,
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)nullptr,
								                  0,
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)nullptr,
								                  0,
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)nullptr,
								                  0,
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Saved);
								break;
						}

						delete DelimS;
					}

				} else {

					Saved.Width = InStr->_InputWidth;
					Saved.Charset = InStr->_InputCharset;

					DelimS = Delim.ToCharset(InStr->_InputCharset,
					                         InStr->_InputWidth);

					if (DelimS != nullptr) {
						switch (InStr->_InputWidth) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok(InStr->Get8(),
								                  InStr->Length(),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is16Bit_t:
								Results = _strtok(InStr->Get16(),
								                  InStr->Length(),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is32Bit_t:
								Results = _strtok(InStr->Get32(),
								                  InStr->Length(),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case IsWBit_t:
								Results = _strtok(InStr->GetW(),
								                  InStr->Length(),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Saved);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const String * InStr,
			               const char * Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					String	*	DelimS = nullptr;

					if (InStr != nullptr) {
						Saved.Width = InStr->_InputWidth;
						Saved.Charset = InStr->_InputCharset;
					}

					String		Tmp(Delim);

					DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

					if (DelimS != nullptr) {
						switch (Saved.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								if (InStr != nullptr) {
									Results = _strtok(InStr->Get8(),
									                  InStr->Length(),
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);

								} else {
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
								}

								break;

							case Is16Bit_t:
								if (InStr != nullptr) {
									Results = _strtok(InStr->Get16(),
									                  InStr->Length(),
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);

								} else {
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
								}

								break;

							case Is32Bit_t:
								if (InStr != nullptr) {
									Results = _strtok(InStr->Get32(),
									                  InStr->Length(),
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);

								} else {
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
								}

								break;

							case IsWBit_t:
								if (InStr != nullptr) {
									Results = _strtok(InStr->GetW(),
									                  InStr->Length(),
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);

								} else {
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
								}

								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {

					String	*	DelimS = nullptr;
					String		Tmp(Delim);

					if (InStr == nullptr) {
						// Do the work in the Saved.Charset, when InStr is nullptr.
						//
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}
						}

					} else {
						// Do the work in Current8BitCharset, when InStr is not nullptr.
						//
						Saved.Width = Is8Bit_t;
						Saved.Charset = Current8BitCharset;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current8BitCharset,
						                       Current8BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get8(),
							                  DelimS->Length(),
							                  Saved);
						}
					}

					delete DelimS;
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current8BitCharset;
						Saved.Width = Current8BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current8BitCharset,
						                       Current8BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get8(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current8BitCharset;
						Saved.Width = Current8BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current8BitCharset,
						                       Current8BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get8(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current8BitCharset;
						Saved.Width = Current8BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current8BitCharset,
						                       Current8BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get8(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String		*	DelimS = nullptr;

				if (InStr == nullptr) {

					DelimS = Delim.ToCharset(Saved.Charset, Saved.Width);

					if (DelimS != nullptr) {
						switch (Saved.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)nullptr,
								                  0,
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)nullptr,
								                  0,
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)nullptr,
								                  0,
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Saved);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)nullptr,
								                  0,
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Saved);
								break;
						}

						delete DelimS;
					}

				} else {
					DelimS = Delim.ToCharset(Current8BitCharset,
					                         Current8BitWidth);

					if (DelimS != nullptr) {
						Results = _strtok(InStr,
						                  strlen(InStr),
						                  DelimS->Get8(),
						                  DelimS->Length(),
						                  Saved);
					}

					delete DelimS;
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				String			Tmp(Delim);
				String		*	DelimS = nullptr;

				if  (Delim != nullptr) {
					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current16BitCharset;
						Saved.Width = Current16BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current16BitCharset,
						                       Current16BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get16(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current16BitCharset;
						Saved.Width = Current16BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current16BitCharset,
						                       Current16BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get16(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset32To16(nullptr,
					                          Delim,
					                          nullptr,
					                          Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Delim,
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results
				    = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString *	Results = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				Results = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Delim.c_str(),
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				Results = strtok(InStr, Delim.Get16(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset8To32(nullptr,
					                         Delim,
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset16To32(nullptr,
					                          Delim,
					                          nullptr,
					                          Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = Current32BitCharset;
						Saved.Width = Current32BitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(Current32BitCharset,
						                       Current32BitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->Get32(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         Delim,
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results
				    = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results
				    = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results
				    = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results
				    = strtok(InStr, Delim.c_str(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				Results = strtok(InStr, Delim.Get32(), Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset8ToW(nullptr,
					                        Delim,
					                        nullptr,
					                        Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset16ToW(nullptr,
					                         Delim,
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset32ToW(nullptr,
					                         Delim,
					                         nullptr,
					                         Out)) {
						Results = strtok(InStr, Out, Saved);
						delete Out;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if  (Delim != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = nullptr;

					if (InStr == nullptr) {
						DelimS = Tmp.ToCharset(Saved.Charset, Saved.Width);

						if (DelimS != nullptr) {
							switch (Saved.Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Results = _strtok((const char *)nullptr,
									                  0,
									                  DelimS->Get8(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is16Bit_t:
									Results = _strtok((const char16_t *)nullptr,
									                  0,
									                  DelimS->Get16(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case Is32Bit_t:
									Results = _strtok((const char32_t *)nullptr,
									                  0,
									                  DelimS->Get32(),
									                  DelimS->Length(),
									                  Saved);
									break;

								case IsWBit_t:
									Results = _strtok((const wchar_t *)nullptr,
									                  0,
									                  DelimS->GetW(),
									                  DelimS->Length(),
									                  Saved);
									break;
							}

							delete DelimS;
						}

					} else {
						Saved.Charset = CurrentWBitCharset;
						Saved.Width = CurrentWBitWidth;
						Saved.SavePtr = (void *)InStr;
						DelimS = Tmp.ToCharset(CurrentWBitCharset,
						                       CurrentWBitWidth);

						if (DelimS != nullptr) {
							Results = _strtok(InStr,
							                  strlen(InStr),
							                  DelimS->GetW(),
							                  DelimS->Length(),
							                  Saved);
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = strtok(InStr,
				                                 Delim.c_str(),
				                                 Saved);

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr, Delim.GetW(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.GetW(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.Get8(), Saved);

				} else {
					Results = strtok((const char *)nullptr, Delim.Get8(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.Get16(), Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim.Get16(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string * InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char16_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.Get32(), Saved);

				} else {
					Results = strtok((const char32_t *)nullptr, Delim.Get32(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const char * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const char16_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const char32_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const wchar_t * const Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim, Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim, Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const std::string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const std::u16string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const std::u32string & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * InStr,
			               const std::wstring & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.c_str(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.c_str(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring * const InStr,
			               const String & Delim,
			               TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strtok(InStr->c_str(), Delim.GetW(), Saved);

				} else {
					Results = strtok((const wchar_t *)nullptr, Delim.GetW(),
					                 Saved);
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char * const Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr && Save.SavePtr != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  Delim,
								                  strlen(Delim),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char16_t * const Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr && Save.SavePtr != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const char32_t * const Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr && Save.SavePtr != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const wchar_t * const Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Delim != nullptr && Save.SavePtr != nullptr) {
					String		Tmp(Delim);
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = strtok((const char16_t *)Save.SavePtr,
								                 DelimS->Get16(),
								                 Save);
								break;

							case Is32Bit_t:
								Results = strtok((const char32_t *)Save.SavePtr,
								                 DelimS->Get32(),
								                 Save);
								break;

							case IsWBit_t:
								Results = strtok((const wchar_t *)Save.SavePtr,
								                 DelimS->GetW(),
								                 Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const String & Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Save.SavePtr != nullptr) {
					String	*	DelimS = Delim.ToCharset(Save.Charset,
					                                     Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::string & Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Save.SavePtr != nullptr) {
					String		Tmp(Delim.c_str());
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u16string & Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Save.SavePtr != nullptr) {
					String		Tmp(Delim.c_str());
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::u32string & Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Save.SavePtr != nullptr) {
					String		Tmp(Delim.c_str());
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::strtok(const std::wstring & Delim, TokSave & Save)
			{
				ROString	*	Results = nullptr;

				if (Save.SavePtr != nullptr) {
					String		Tmp(Delim.c_str());
					String	*	DelimS = Tmp.ToCharset(Save.Charset,
					                                   Save.Width);

					if (DelimS != nullptr) {
						switch (Save.Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Results = _strtok((const char *)Save.SavePtr,
								                  strlen((const char *)Save.SavePtr),
								                  DelimS->Get8(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is16Bit_t:
								Results = _strtok((const char16_t *)Save.SavePtr,
								                  strlen((const char16_t *)Save.SavePtr),
								                  DelimS->Get16(),
								                  DelimS->Length(),
								                  Save);
								break;

							case Is32Bit_t:
								Results = _strtok((const char32_t *)Save.SavePtr,
								                  strlen((const char32_t *)Save.SavePtr),
								                  DelimS->Get32(),
								                  DelimS->Length(),
								                  Save);
								break;

							case IsWBit_t:
								Results = _strtok((const wchar_t *)Save.SavePtr,
								                  strlen((const wchar_t *)Save.SavePtr),
								                  DelimS->GetW(),
								                  DelimS->Length(),
								                  Save);
								break;
						}

						delete DelimS;
					}
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const char * const InStr,
			                size_t InLen,
			                const char * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				const char	*	In = InStr;
				size_t			Len = InLen;

				if (InStr == nullptr) {
					In = (const char *)Saved.SavePtr;
				}

				size_t			TokenLength = strcspn(In, Len,
				                                      Delim, DelimLen);

				while (TokenLength == 0 && *In != 0) {
					In++;
					Len--;
					TokenLength = strcspn(In, Len,
					                      Delim, DelimLen);
				}

				if (TokenLength > 0) {
					Results = new ROString(In, TokenLength);
				}

				if (In[TokenLength] == 0) {
					Saved.SavePtr = (void *)&In[TokenLength];

				} else {
					Saved.SavePtr = (void *) (In + TokenLength + 1);
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const char16_t * const InStr,
			                size_t InLen,
			                const char16_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				const char16_t	*	In = InStr;
				size_t			Len = InLen;

				if (InStr == nullptr) {
					In = (const char16_t *)Saved.SavePtr;
				}

				size_t			TokenLength = strcspn(In, Len,
				                                      Delim, DelimLen);

				while (TokenLength == 0 && *In != 0) {
					In++;
					Len--;
					TokenLength = strcspn(In, Len,
					                      Delim, DelimLen);
				}

				if (TokenLength > 0) {
					Results = new ROString(In, TokenLength);
				}

				if (In[TokenLength] == 0) {
					Saved.SavePtr = (void *)&In[TokenLength];

				} else {
					Saved.SavePtr = (void *) (In + TokenLength + 1);
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const char32_t * const InStr,
			                size_t InLen,
			                const char32_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				const char32_t	*	In = InStr;
				size_t			Len = InLen;

				if (InStr == nullptr) {
					In = (const char32_t *)Saved.SavePtr;
				}

				size_t			TokenLength = strcspn(In, Len,
				                                      Delim, DelimLen);

				while (TokenLength == 0 && *In != 0) {
					In++;
					Len--;
					TokenLength = strcspn(In, Len,
					                      Delim, DelimLen);
				}

				if (TokenLength > 0) {
					Results = new ROString(In, TokenLength);
				}

				if (In[TokenLength] == 0) {
					Saved.SavePtr = (void *)&In[TokenLength];

				} else {
					Saved.SavePtr = (void *) (In + TokenLength + 1);
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const wchar_t * const InStr,
			                size_t InLen,
			                const wchar_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				const wchar_t	*	In = InStr;
				size_t			Len = InLen;

				if (InStr == nullptr) {
					In = (const wchar_t *)Saved.SavePtr;
				}

				size_t			TokenLength = strcspn(In, Len,
				                                      Delim, DelimLen);

				while (TokenLength == 0 && *In != 0) {
					In++;
					Len--;
					TokenLength = strcspn(In, Len,
					                      Delim, DelimLen);
				}

				if (TokenLength > 0) {
					Results = new ROString(In, TokenLength);
				}

				if (In[TokenLength] == 0) {
					Saved.SavePtr = (void *)&In[TokenLength];

				} else {
					Saved.SavePtr = (void *) (In + TokenLength + 1);
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const ROString * InStr,
			                size_t InLen,
			                const char * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				const ROString	*	In = nullptr;
				const_iterator		it;
				size_t			Len = InLen;
				TokSaveS	*	SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

				if (InStr != nullptr) {
					// New InStr, initialize Saved and local vars.
					//
					it = InStr->cbegin();
					In = InStr;

					if (SSaved != nullptr) {
						delete SSaved;
					}

					SSaved = new TokSaveS();
					SSaved->it = nullptr;
					SSaved->Ptr.RO = InStr;
					Saved.SavePtr = static_cast<void *>(SSaved);

				} else {
					SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

					if (SSaved != nullptr) {
						it = *SSaved->it;
						In = SSaved->Ptr.RO;
					}
				}

				if (In != nullptr && Delim != nullptr) {
					size_t		TokenLength = strcspn(*In, Len,
					                                  it,
					                                  Delim, DelimLen);

					while (TokenLength == 0 && it != In->cend()) {
						it++;
						Len--;
						TokenLength = strcspn(*In, Len,
						                      it,
						                      Delim, DelimLen);
					}

					if (TokenLength > 0) {
						Results = new ROString(InStr, it, TokenLength);
					}

					if (it == In->cend()) {
						if (SSaved != nullptr) {
							if (SSaved->it != nullptr) {
								delete SSaved->it;
							}

							delete SSaved;
						}

						Saved.SavePtr = nullptr;

					} else {
						*SSaved->it = it;
						SSaved->Ptr.RO = In;
						Saved.SavePtr = SSaved;
					}
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const ROString * InStr,
			                size_t InLen,
			                const char16_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				size_t			Len = InLen;
				const ROString	*	In = nullptr;
				const_iterator		it;
				TokSaveS	*	SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

				if (InStr != nullptr) {
					// New InStr, initialize Saved and local vars.
					//
					it = InStr->cbegin();
					In = InStr;

					if (SSaved != nullptr) {
						delete SSaved;
					}

					SSaved = new TokSaveS();
					SSaved->it = nullptr;
					SSaved->Ptr.RO = InStr;
					Saved.SavePtr = static_cast<void *>(SSaved);

				} else {
					SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

					if (SSaved != nullptr) {
						it = *SSaved->it;
						In = SSaved->Ptr.RO;
					}
				}

				if (In != nullptr && Delim != nullptr) {
					size_t		TokenLength = strcspn(*In, Len,
					                                  it,
					                                  Delim, DelimLen);

					while (TokenLength == 0 && it != In->cend()) {
						it++;
						Len--;
						TokenLength = strcspn(*In, Len,
						                      it,
						                      Delim, DelimLen);
					}

					if (TokenLength > 0) {
						Results = new ROString(InStr, it, TokenLength);
					}

					if (it == In->cend()) {
						if (SSaved != nullptr) {
							if (SSaved->it != nullptr) {
								delete SSaved->it;
							}

							delete SSaved;
						}

						Saved.SavePtr = nullptr;

					} else {
						*SSaved->it = it;
						SSaved->Ptr.RO = In;
						Saved.SavePtr = SSaved;
					}
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const ROString * InStr,
			                size_t InLen,
			                const char32_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				size_t			Len = InLen;
				const ROString	*	In = nullptr;
				const_iterator		it;
				TokSaveS	*	SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

				if (InStr != nullptr) {
					// New InStr, initialize Saved and local vars.
					//
					it = InStr->cbegin();
					In = InStr;

					if (SSaved != nullptr) {
						delete SSaved;
					}

					SSaved = new TokSaveS();
					SSaved->it = nullptr;
					SSaved->Ptr.RO = InStr;
					Saved.SavePtr = static_cast<void *>(SSaved);

				} else {
					SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

					if (SSaved != nullptr) {
						it = *SSaved->it;
						In = SSaved->Ptr.RO;
					}
				}

				if (In != nullptr && Delim != nullptr) {
					size_t		TokenLength = strcspn(*In, Len,
					                                  it,
					                                  Delim, DelimLen);

					while (TokenLength == 0 && it != In->cend()) {
						it++;
						Len--;
						TokenLength = strcspn(*In, Len,
						                      it,
						                      Delim, DelimLen);
					}

					if (TokenLength > 0) {
						Results = new ROString(InStr, it, TokenLength);
					}

					if (it == In->cend()) {
						if (SSaved != nullptr) {
							if (SSaved->it != nullptr) {
								delete SSaved->it;
							}

							delete SSaved;
						}

						Saved.SavePtr = nullptr;

					} else {
						*SSaved->it = it;
						SSaved->Ptr.RO = In;
						Saved.SavePtr = SSaved;
					}
				}

				return (Results);
			}

			ROString	*
			String::_strtok(const ROString * InStr,
			                size_t InLen,
			                const wchar_t * const Delim,
			                size_t DelimLen,
			                TokSave & Saved)
			{
				ROString	*	Results = nullptr;

				size_t			Len = InLen;
				const ROString	*	In = nullptr;
				const_iterator		it;
				TokSaveS	*	SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

				if (InStr != nullptr) {
					// New InStr, initialize Saved and local vars.
					//
					it = InStr->cbegin();
					In = InStr;

					if (SSaved != nullptr) {
						delete SSaved;
					}

					SSaved = new TokSaveS();
					SSaved->it = nullptr;
					SSaved->Ptr.RO = InStr;
					Saved.SavePtr = static_cast<void *>(SSaved);

				} else {
					SSaved = static_cast<TokSaveS *>(Saved.SavePtr);

					if (SSaved != nullptr) {
						it = *SSaved->it;
						In = SSaved->Ptr.RO;
					}
				}

				if (In != nullptr && Delim != nullptr) {
					size_t		TokenLength = strcspn(*In, Len,
					                                  it,
					                                  Delim, DelimLen);

					while (TokenLength == 0 && it != In->cend()) {
						it++;
						Len--;
						TokenLength = strcspn(*In, Len,
						                      it,
						                      Delim, DelimLen);
					}

					if (TokenLength > 0) {
						Results = new ROString(InStr, it, TokenLength);
					}

					if (it == In->cend()) {
						if (SSaved != nullptr) {
							if (SSaved->it != nullptr) {
								delete SSaved->it;
							}

							delete SSaved;
						}

						Saved.SavePtr = nullptr;

					} else {
						*SSaved->it = it;
						SSaved->Ptr.RO = In;
						Saved.SavePtr = SSaved;
					}
				}

				return (Results);
			}

		}
	}
}
