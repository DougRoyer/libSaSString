//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2020 Douglas Mark Royer, All Rights Reserved.
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
// THIS DOCUMENT AND THE INFORMATION CONTAINED HEREIN IS
// PROVIDED ON AN "AS IS" BASIS AND DOUGLAS MARK ROYER
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//
#include <SaS/String/String.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			Locale::Lc_Address::Lc_Address(Locale & Parent)
				:	LcBase(Parent, LC_ADDRESS_Cat)
			{
				PostalFmtValue = nullptr;
				CountryNameValue = nullptr;
				CountryPostValue = nullptr;
				CountryAb2Value = nullptr;
				CountryAb3Value = nullptr;
				CountryNumValue = nullptr;
				CountryCarValue = nullptr;
				CountryIsbnValue = nullptr;
				LangNameValue = nullptr;
				LangAbValue = nullptr;
				LangTermValue = nullptr;
				LangLibValue = nullptr;

				return;
			}

			Locale::Lc_Address::~Lc_Address()
			{
				if (PostalFmtValue == nullptr) {
					delete PostalFmtValue;
					PostalFmtValue = nullptr;
				}

				if (CountryNameValue == nullptr) {
					delete CountryNameValue;
					CountryNameValue = nullptr;
				}

				if (CountryPostValue == nullptr) {
					delete CountryPostValue;
					CountryPostValue = nullptr;
				}

				if (CountryAb2Value == nullptr) {
					delete CountryAb2Value;
					CountryAb2Value = nullptr;
				}

				if (CountryAb3Value == nullptr) {
					delete CountryAb3Value;
					CountryAb3Value = nullptr;
				}

				if (CountryNumValue == nullptr) {
					delete CountryNumValue;
					CountryNumValue = nullptr;
				}

				if (CountryCarValue == nullptr) {
					delete CountryCarValue;
					CountryCarValue = nullptr;
				}

				if (CountryIsbnValue == nullptr) {
					delete CountryIsbnValue;
					CountryIsbnValue = nullptr;
				}

				if (LangNameValue == nullptr) {
					delete LangNameValue;
					LangNameValue = nullptr;
				}

				if (LangAbValue == nullptr) {
					delete LangAbValue;
					LangAbValue = nullptr;
				}

				if (LangTermValue == nullptr) {
					delete LangTermValue;
					LangTermValue = nullptr;
				}

				if (LangLibValue == nullptr) {
					delete LangLibValue;
					LangLibValue = nullptr;
				}

				return;
			}

			bool
			Locale::Lc_Address::PostalFmt(Token_e
			                              Which,
			                              const ROString *& Value)
			{
				bool				Results = false;

				if (Value = nullptr) {
					// Get.
					//
					switch (Which) {

						case PostalFmt_t:
							Value = PostalFmtValue;
							break;

						case CountryName_t:
							Value = CountryNameValue;
							break;

						case CountryPost_t:
							Value = CountryPostValue;
							break;

						case CountryAb2_t:
							Value = CountryAb2Value;
							break;

						case CountryAb3_t:
							Value = CountryAb3Value;
							break;

						case CountryNum_t:
							Value = CountryNumValue;
							break;

						case CountryCar_t:
							Value = CountryCarValue;
							break;

						case CountryIsbn_t:
							Value = CountryIsbnValue;
							break;

						case LangName_t:
							Value = LangNameValue;
							break;

						case LangAb_t:
							Value = LangAbValue;
							break;

						case LangTerm_t:
							Value = LangTermValue;
							break;

						case LangLib_t:
							Value = LangLibValue;
							break;

					}

					if (Value != nullptr) {
						// Valule was nullptr, not it is not, so it was fetched == true.
						Results = true;
					}

				} else {
					switch (Which) {

						case PostalFmt_t:
							if (PostalFmtValue != nullptr) {
								delete PostalFmtValue;
								Results = true;
							}

							PostalFmtValue = Value;
							Value->incInstance();
							break;

						case CountryName_t:
							if (CountryNameValue != nullptr) {
								delete CountryNameValue;
								Results = true;
							}

							CountryNameValue = Value;
							Value->incInstance();
							break;

						case CountryPost_t:
							if (CountryPostValue != nullptr) {
								delete CountryPostValue;
								Results = true;
							}

							CountryPostValue = Value;
							Value->incInstance();
							break;

						case CountryAb2_t:
							if (CountryAb2Value != nullptr) {
								delete CountryAb2Value;
								Results = true;
							}

							CountryAb2Value = Value;
							Value->incInstance();
							break;

						case CountryAb3_t:
							if (CountryAb3Value != nullptr) {
								delete CountryAb3Value;
								Results = true;
							}

							CountryAb3Value = Value;
							Value->incInstance();
							break;

						case CountryNum_t:
							if (CountryNumValue != nullptr) {
								delete CountryNumValue;
								Results = true;
							}

							CountryNumValue = Value;
							Value->incInstance();
							break;

						case CountryCar_t:
							if (CountryCarValue != nullptr) {
								delete CountryCarValue;
								Results = true;
							}

							CountryCarValue = Value;
							Value->incInstance();
							break;

						case CountryIsbn_t:
							if (CountryIsbnValue != nullptr) {
								delete CountryIsbnValue;
								Results = true;
							}

							CountryIsbnValue = Value;
							Value->incInstance();
							break;

						case LangName_t:
							if (LangNameValue != nullptr) {
								delete LangNameValue;
								Results = true;
							}

							LangNameValue = Value;
							Value->incInstance();
							break;

						case LangAb_t:
							if (LangAbValue != nullptr) {
								delete LangAbValue;
								Results = true;
							}

							LangAbValue = Value;
							Value->incInstance();
							break;

						case LangTerm_t:
							if (LangTermValue != nullptr) {
								delete LangTermValue;
								Results = true;
							}

							LangTermValue = Value;
							Value->incInstance();
							break;

						case LangLib_t:
							if (LangLibValue != nullptr) {
								delete LangLibValue;
								Results = true;
							}

							LangLibValue = Value;
							Value->incInstance();
							break;

					}
				}

				return (Results);

			}

			Locale::Token_e
			Locale::_ParsePostalFmt(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->PostalFmtValue = new ROString(StartData, Len);

				return (PostalFmt_t);
			}

			Locale::Token_e
			Locale::_ParseCountryName(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryNameValue = new ROString(StartData, Len);

				return (CountryName_t);
			}

			Locale::Token_e
			Locale::_ParseCountryPost(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryPostValue = new ROString(StartData, Len);

				return (CountryPost_t);
			}

			Locale::Token_e
			Locale::_ParseCountryAb2(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryAb2Value = new ROString(StartData, Len);

				return (CountryAb2_t);
			}

			Locale::Token_e
			Locale::_ParseCountryAb3(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryAb3Value = new ROString(StartData, Len);

				return (CountryAb3_t);
			}

			Locale::Token_e
			Locale::_ParseCountryNum(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryNumValue = new ROString(StartData, Len);

				return (CountryNum_t);
			}

			Locale::Token_e
			Locale::_ParseCountryCar(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryCarValue = new ROString(StartData, Len);

				return (CountryCar_t);
			}

			Locale::Token_e
			Locale::_ParseCountryIsbn(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->CountryIsbnValue = new ROString(StartData, Len);

				return (CountryIsbn_t);
			}

			Locale::Token_e
			Locale::_ParseLangName(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->LangNameValue = new ROString(StartData, Len);

				return (LangName_t);
			}

			Locale::Token_e
			Locale::_ParseLangAb(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->LangAbValue = new ROString(StartData, Len);

				return (LangAb_t);
			}

			Locale::Token_e
			Locale::_ParseLangTerm(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->LangTermValue = new ROString(StartData, Len);

				return (LangTerm_t);
			}

			Locale::Token_e
			Locale::_ParseLangLib(Locale & Parent, File * Fp)
			{
				size_t				Len = 0;
				const char	*	StartData = Parent._ParseQuotedString(Len, Fp);

				Parent.LC_ADDRESS_Value->LangLibValue = new ROString(StartData, Len);

				return (LangLib_t);
			}

			Locale::Token_e
			Locale::_ParseEND_LC_ADDRESS(Locale & Parent, File * Fp)
			{
				/*EMPTY*/
				return (END_LC_ADDRESS_t);
			}

			Locale::Token_e
			Locale::Lc_Address::Parse(Locale & Parent, File * Fp)
			{
				Token_e					Results = Token_e_UnknownToken_t;

				Dispatch		Tokens[] = {
					{PostalFmt_s, _ParsePostalFmt, PostalFmt_t},
					{CountryName_s, _ParseCountryName, CountryName_t},
					{CountryPost_s, _ParseCountryPost, CountryPost_t},
					{CountryAb2_s, _ParseCountryAb2, CountryAb2_t},
					{CountryAb3_s, _ParseCountryAb3, CountryAb3_t},
					{CountryNum_s, _ParseCountryNum, CountryNum_t},
					{CountryCar_s, _ParseCountryCar, CountryCar_t},
					{CountryIsbn_s, _ParseCountryIsbn, CountryIsbn_t},
					{LangName_s, _ParseLangName, LangName_t},
					{LangAb_s, _ParseLangAb, LangAb_t},
					{LangTerm_s, _ParseLangTerm, LangTerm_t},
					{LangLib_s, _ParseLangLib, LangLib_t},
					{END_LC_ADDRESS_s, _ParseEND_LC_ADDRESS, LC_ADDRESS_t},
					{nullptr, nullptr, Token_e_UnknownToken_t}
				};

				Token_e				What;
				size_t				Len = 0;
				const char	*	StartData = nullptr;
				bool					Done = false;
				Lc_Address	*	NewObject = new Lc_Address(Parent);

				do {
					What = Parent._Parse(Fp, Tokens);
				} while (!Done && What != END_LC_ADDRESS_t);

				Results = What;

				return (Results);
			}

			bool
			Locale::Lc_Address::Print(File * Fp)
			{
				bool Results = true;

				Fp->Printf("%s\n", LC_ADDRESS_s);

				if (PostalFmtValue != nullptr) {
					PostalFmtValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryNameValue != nullptr) {
					CountryNameValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryPostValue != nullptr) {
					CountryPostValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryAb2Value != nullptr) {
					CountryAb2Value->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryAb3Value != nullptr) {
					CountryAb3Value->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryNumValue != nullptr) {
					CountryNumValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryCarValue != nullptr) {
					CountryCarValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (CountryIsbnValue != nullptr) {
					CountryIsbnValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (LangNameValue != nullptr) {
					LangNameValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (LangAbValue != nullptr) {
					LangAbValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (LangTermValue != nullptr) {
					LangTermValue->Print(*Fp);
					Fp->Printf("\n");
				}

				if (LangLibValue != nullptr) {
					LangLibValue -> Print(*Fp);
					Fp->Printf("\n");
				}

				Fp->Printf("%s %s\n\n", LC_END_s, LC_ADDRESS_s);

				return (Results);
			}

		}
	}
}
