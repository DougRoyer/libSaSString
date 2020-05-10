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

			Locale::Lc_Ctype::Lc_Ctype(Locale & Parent)
				:	LcBase(Parent, LC_CTYPE_Cat)
			{

				return;
			}

			Locale::Lc_Ctype::~Lc_Ctype()
			{

				return;
			}

			bool
			Locale::Lc_Ctype::IsUpper(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= 'A') && ((*ToTest <= 'Z'))) {
						Results = true;

					} else {
						Results = InSet(UpperValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsUpper(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= u'A') && ((*ToTest <= u'Z'))) {
						Results = true;

					} else {
						Results = InSet(UpperValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsUpper(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= U'A') && ((*ToTest <= U'Z'))) {
						Results = true;

					} else {
						Results = InSet(UpperValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsUpper(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= L'A') && ((*ToTest <= L'Z'))) {
						Results = true;

					} else {
						Results = InSet(UpperValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsLower(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= 'a') && ((*ToTest <= 'z'))) {
						Results = true;

					} else {
						Results = InSet(LowerValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsLower(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= u'a') && ((*ToTest <= u'z'))) {
						Results = true;

					} else {
						Results = InSet(LowerValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsLower(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= U'a') && ((*ToTest <= U'z'))) {
						Results = true;

					} else {
						Results = InSet(LowerValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsLower(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ( ((*ToTest) >= L'a') && ((*ToTest <= L'z'))) {
						Results = true;

					} else {
						Results = InSet(LowerValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsAlpha(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsLower(ToTest)	|| IsUpper(ToTest)) {
						Results = true;

					} else {
						Results = InSet(AlphaValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsAlpha(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsLower(ToTest)	|| IsUpper(ToTest)) {
						Results = true;

					} else {
						Results = InSet(AlphaValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsAlpha(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsLower(ToTest)	|| IsUpper(ToTest)) {
						Results = true;

					} else {
						Results = InSet(AlphaValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsAlpha(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsLower(ToTest)	|| IsUpper(ToTest)) {
						Results = true;

					} else {
						Results = InSet(AlphaValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsDigit(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest >= '0' && *ToTest <= '9') {
						Results = true;

					} else {
						Results = InSet(DigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsDigit(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest >= u'0' && *ToTest <= u'9') {
						Results = true;

					} else {
						Results = InSet(DigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsDigit(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest >= U'0' && *ToTest <= U'9') {
						Results = true;

					} else {
						Results = InSet(DigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsDigit(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest >= L'0' && *ToTest <= L'9') {
						Results = true;

					} else {
						Results = InSet(DigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsSpace(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == ' '
					    || *ToTest == '\f'
					    || *ToTest == '\n'
					    || *ToTest == '\r'
					    || *ToTest == '\t'
					    || *ToTest == '\v') {
						Results = true;

					} else {
						Results = InSet(SpaceValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsSpace(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == u' '
					    || *ToTest == u'\f'
					    || *ToTest == u'\n'
					    || *ToTest == u'\r'
					    || *ToTest == u'\t'
					    || *ToTest == u'\v') {
						Results = true;

					} else {
						Results = InSet(SpaceValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsSpace(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == U' '
					    || *ToTest == U'\f'
					    || *ToTest == U'\n'
					    || *ToTest == U'\r'
					    || *ToTest == U'\t'
					    || *ToTest == U'\v') {
						Results = true;

					} else {
						Results = InSet(SpaceValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsSpace(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == L' '
					    || *ToTest == L'\f'
					    || *ToTest == L'\n'
					    || *ToTest == L'\r'
					    || *ToTest == L'\t'
					    || *ToTest == L'\v') {
						Results = true;

					} else {
						Results = InSet(SpaceValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsCntrl(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(CntrlValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsCntrl(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(CntrlValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsCntrl(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(CntrlValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPunct(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(PunctValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPunct(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(PunctValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPunct(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(PunctValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPunct(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					Results = InSet(PunctValues, ToTest);
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsGraph(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)) {
						Results = true;

					} else {
						Results = InSet(GraphValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsGraph(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)) {
						Results = true;

					} else {
						Results = InSet(GraphValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsGraph(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)) {
						Results = true;

					} else {
						Results = InSet(GraphValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsGraph(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)) {
						Results = true;

					} else {
						Results = InSet(GraphValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPrint(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)
					    || IsSpace(ToTest)) {
						Results = true;

					} else {
						Results = InSet(PrintValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPrint(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)
					    || IsSpace(ToTest)) {
						Results = true;

					} else {
						Results = InSet(PrintValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPrint(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)
					    || IsSpace(ToTest)) {
						Results = true;

					} else {
						Results = InSet(PrintValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsPrint(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (IsUpper(ToTest)
					    || IsLower(ToTest)
					    || IsAlpha(ToTest)
					    || IsDigit(ToTest)
					    || IsXDigit(ToTest)
					    || IsPunct(ToTest)
					    || IsSpace(ToTest)) {
						Results = true;

					} else {
						Results = InSet(PrintValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsXDigit(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ((*ToTest >= '0' && *ToTest <= '9')
					    || (*ToTest >= 'a' && *ToTest <= 'f')
					    || (*ToTest >= 'A' && *ToTest <= 'F')) {
						Results = true;

					} else {
						Results = InSet(XDigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsXDigit(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ((*ToTest >= u'0' && *ToTest <= u'9')
					    || (*ToTest >= u'a' && *ToTest <= u'f')
					    || (*ToTest >= u'A' && *ToTest <= u'F')) {
						Results = true;

					} else {
						Results = InSet(XDigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsXDigit(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ((*ToTest >= U'0' && *ToTest <= U'9')
					    || (*ToTest >= U'a' && *ToTest <= U'f')
					    || (*ToTest >= U'A' && *ToTest <= U'F')) {
						Results = true;

					} else {
						Results = InSet(XDigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsXDigit(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if ((*ToTest >= L'0' && *ToTest <= L'9')
					    || (*ToTest >= L'a' && *ToTest <= L'f')
					    || (*ToTest >= L'A' && *ToTest <= L'F')) {
						Results = true;

					} else {
						Results = InSet(XDigitValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsBlank(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == ' ' || *ToTest == '\t') {
						Results = true;

					} else {
						Results = InSet(BlankValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsBlank(const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == u' ' || *ToTest == u'\t') {
						Results = true;

					} else {
						Results = InSet(BlankValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsBlank(const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == U' ' || *ToTest == U'\t') {
						Results = true;

					} else {
						Results = InSet(BlankValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsBlank(const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					if (*ToTest == L' ' || *ToTest == L'\t') {
						Results = true;

					} else {
						Results = InSet(BlankValues, ToTest);
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsCharClass(const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					std::vector<const char *>::const_iterator	It;

					for (It = CharClassValues.begin(); It != CharClassValues.end(); It++) {
						if (strcmp(ToTest, *It) == 0) {
							Results = true;
							break;
						}
					}
				}

				return (Results);
			}

			std::shared_ptr<char>
			Locale::Lc_Ctype::ToUpper(const char * ToConvert) const
			{
				// Convert
			}

			bool
			Locale::Lc_Ctype::IsInClass(const char * ClassName,
			                            const char * ToTest) const
			{
				bool				Results = false;

				if (ClassName != nullptr) {
					if (IsCharClass(ClassName)) {
						if (ToTest != nullptr) {

							std::map<const char *, std::vector<USet *>*>::const_iterator	It;
							It = ClassValues.find(ClassName);

							if (It != ClassValues.end()) {
								std::vector<USet *>	*	Set = It->second;
								std::vector<USet *>::const_iterator	cIt;
								String		Original(ToTest);

								const char32_t	*	In32 = Original.Get32();
								USet				*			Range = nullptr;

								for (cIt = It->second->begin()
								           ; cIt != It->second->end(); cIt++) {
									Range = *cIt;

									if (Range->Right == 0) {
										if (*In32 == Range->Left) {
											Results = true;
											break;
										}

									} else {
										if (*In32 >= Range->Left && *In32 <= Range->Right) {
											Results = true;
											break;
										}
									}
								}
							}

						} else {
							Results = true;
						}
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsInClass(const char * ClassName,
			                            const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ClassName != nullptr) {
					if (IsCharClass(ClassName)) {
						if (ToTest != nullptr) {

							std::map<const char *, std::vector<USet *>*>::const_iterator	It;
							It = ClassValues.find(ClassName);

							if (It != ClassValues.end()) {
								std::vector<USet *>	*	Set = It->second;
								std::vector<USet *>::const_iterator	cIt;
								String		Original(ToTest);

								const char32_t	*	In32 = Original.Get32();
								USet				*			Range = nullptr;

								for (cIt = It->second->begin()
								           ; cIt != It->second->end(); cIt++) {
									Range = *cIt;

									if (Range->Right == 0) {
										if (*In32 == Range->Left) {
											Results = true;
											break;
										}

									} else {
										if (*In32 >= Range->Left && *In32 <= Range->Right) {
											Results = true;
											break;
										}
									}
								}
							}

						} else {
							Results = true;
						}
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsInClass(const char * ClassName,
			                            const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ClassName != nullptr) {
					if (IsCharClass(ClassName)) {
						if (ToTest != nullptr) {

							std::map<const char *, std::vector<USet *>*>::const_iterator	It;
							It = ClassValues.find(ClassName);

							if (It != ClassValues.end()) {
								std::vector<USet *>	*	Set = It->second;
								std::vector<USet *>::const_iterator	cIt;
								String		Original(ToTest);

								const char32_t	*	In32 = ToTest;
								USet				*			Range = nullptr;

								for (cIt = It->second->begin()
								           ; cIt != It->second->end(); cIt++) {
									Range = *cIt;

									if (Range->Right == 0) {
										if (*In32 == Range->Left) {
											Results = true;
											break;
										}

									} else {
										if (*In32 >= Range->Left && *In32 <= Range->Right) {
											Results = true;
											break;
										}
									}
								}
							}

						} else {
							Results = true;
						}
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsInClass(const char * ClassName,
			                            const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ClassName != nullptr) {
					if (IsCharClass(ClassName)) {
						if (ToTest != nullptr) {

							std::map<const char *, std::vector<USet *>*>::const_iterator	It;
							It = ClassValues.find(ClassName);

							if (It != ClassValues.end()) {
								std::vector<USet *>	*	Set = It->second;
								std::vector<USet *>::const_iterator	cIt;
								String		Original(ToTest);

								const char32_t	*	In32 = Original.Get32();
								USet				*			Range = nullptr;

								for (cIt = It->second->begin()
								           ; cIt != It->second->end(); cIt++) {
									Range = *cIt;

									if (Range->Right == 0) {
										if (*In32 == Range->Left) {
											Results = true;
											break;
										}

									} else {
										if (*In32 >= Range->Left && *In32 <= Range->Right) {
											Results = true;
											break;
										}
									}
								}
							}

						} else {
							Results = true;
						}
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsCharConv(const char * ConvTable) const
			{
				bool			Results = false;

				if (ConvTable != nullptr) {
					std::vector<const char *>::const_iterator	It;

					for (It = CharConvValues.begin(); It != CharConvValues.end(); It++) {
						if (strcmp(*It, ConvTable) == 0) {
							Results = true;
							break;
						}
					}
				}

				return (Results);
			}

			bool
			Locale::Lc_Ctype::IsOutDigit(const char * ToTest) const
			{
			}

			Locale::Token_e
			Locale::Lc_Ctype::Parse(Locale & Parent, File * Fp)
			{
				Token_e				Results = Token_e_UnknownToken_t;

				Dispatch		Tokens[] = {
					{Upper_s, _ParseUpper},
					{Lower_s, _ParseLower},
					{Alpha_s, _ParseAlpha},
					{Digit_s, _ParseDigit},
					{Space_s, _ParseSpace},
					{Cntrl_s, _ParseCntrl},
					{Punct_s, _ParsePunct},
					{Graph_s, _ParseGraph},
					{Print_s, _ParsePrint},
					{XDigit_s, _ParseXDigit},
					{Blank_s, _ParseBlank},
					{CharClass_s, _ParseCharClass},
					{ToUpper_s, _ParseToUpper},
					{ToLower_s, _ParseToLower},
					{MapToTitle_s, _ParseMapToTitle},
					{Class_s, _ParseClass},
					{CharConv_s, _ParseCharConv},
					{OutDigit_s, _ParseOutDigit},
					{MapToInPunct_s, _ParseMapToInPunct},
					{MapToOutPunct_s, _ParseMapToOutPunct},
					{TranslitStart_s, _ParseTranslitStart}, // Absorbs translit_end
					{Include_s, _ParseInclude},
					{DefaultMissing_s, _ParseDefaultMissing},
					{END_LC_CTYPE_s, nullptr, END_LC_CTYPE_t},
					{nullptr, nullptr}
				};

				Token_e				What;

				do {
					What = Parent._Parse(Fp, Tokens);

					if (What == Token_e_UnknownToken_t) {
						break;
					}
				} while (What != EOF_t && What != END_LC_CTYPE_t);

				Results = What;

				return (Results);
			}

			Locale::Token_e
			Locale::_ParseUpper(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseLower(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseAlpha(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseDigit(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseSpace(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseCntrl(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParsePunct(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseGraph(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParsePrint(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseXDigit(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseBlank(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseCharClass(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseToUpper(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseToLower(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseMapToTitle(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseClass(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseCharConv(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseOutDigit(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseMapToInPunct(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseMapToOutPunct(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseTranslitStart(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseInclude(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseDefaultMissing(Locale & Parent, File * Fp)
			{
			}

		}
	}
}
