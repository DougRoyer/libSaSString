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

			const	char  *	const Locale::Abbay_s = "abbay";
			const char	*	const Locale::Abmon_s = "abmon";
			const char	*	const Locale::Abbreviation_s = "abbreviation";
			const char	*	const Locale::Address_s = "address";
			const char	*	const Locale::Alpha_s = "alpha";
			const char	*	const Locale::AltDigits_s = "alt_digits";
			const char	*	const Locale::AmPm_s = "am_pm";
			const char	*	const Locale::Application_s = "application";
			const char	*	const Locale::Audience_s = "audience";

			const char	*	const Locale::Blank_s = "blank";

			const char	*	const Locale::CalDirection_s = "cal_direction";
			const char	*	const Locale::CharClass_s = "char_class";
			const char	*	const Locale::CharConv_s = "charconv";
			const char	*	const Locale::CharMap_s = "CHARMAP";
			const char	*	const Locale::Class_s = "class";
			const char	*	const Locale::Cntrl_s = "cntrl";
			const char	*	const Locale::CodeSetName_s = "code_set_name";
			const char	*	const Locale::CollWeightMax_s = "coll_weight_max";
			const char	*	const Locale::CollatingElement_s = "collating-element";
			const char	*	const Locale::CollatingSymbol_s = "collating-symbol";
			const char	*	const Locale::CommentChar_s = "comment_char";
			const char	*	const Locale::Contact_s = "contact";
			const char	*	const Locale::Copy_s_s = "copy";
			const char	*	const Locale::CountryAb2_s = "country_ab2";	// 2-letter ISO-3166 country code.
			const char	*	const Locale::CountryAb3_s = "country_ab3";	// 3-letter ISO-3166 country code.
			const char	*	const Locale::CountryCar_s = "country_car";
			const char	*	const Locale::CountryIsbn_s = "country_isbn";
			const char	*	const Locale::CountryName_s = "country_name";
			const char	*	const Locale::CountryNum_s = "country_num";	// ISO-3166 Country number
			const char	*	const Locale::CountryPost_s = "country_post";
			const char	*	const Locale::CurrencySymbol_s = "currency_symbol";

			const char	Locale::DefaultEscape = '\\';
			const char	Locale::DefaultComment = '#';

			const char	* const Locale::DFmt_s = "d_fmt";
			const char	* const Locale::DTFmt_s = "d_t_fmt";
			const char	* const Locale::Date_s = "date";
			const char	* const Locale::DateFmt_s = "date_fmt";
			const char	* const Locale::Day_s = "day";
			const char	* const Locale::DecimalPoint_s = "decimal_point";
			const char	* const Locale::DefaultMissing_s = "default_mising";
			const char	* const Locale::Define_s = "define";
			const char	*	const Locale::Digit_s = "digit";

			const char	*	const Locale::Email_s = "email";
			const char	*	const Locale::Empty_s = "";
			const char	*	const Locale::END_LC_ADDRESS_s = "END LC_ADDRESS";
			const char	*	const Locale::END_LC_IDENTIFICATION_s = "END LC_IDENTIFICATION";
			const char	*	const Locale::END_LC_CTYPE_s = "END LC_CTYPE";
			const char	*	const Locale::END_LC_COLLATE_s = "END LC_COLLATE";
			const char	*	const Locale::END_LC_MEASUREMENT_s = "END LC_MEASUREMENT";
			const char	*	const Locale::END_LC_MESSAGES_s = "END LC_MESSAGES";
			const char	*	const Locale::END_LC_MONETARY_s = "END LC_MONETARY";
			const char	*	const Locale::END_LC_NAME_s = "END LC_NAME";
			const char	*	const Locale::END_LC_NUMERIC_s = "END LC_NUMERIC";
			const char	*	const Locale::END_LC_PAPER_s = "END LC_PAPER";
			const char	*	const Locale::END_LC_TELEPHONE_s = "END LC_TELEPHONE";
			const char	*	const Locale::END_LC_TIME_s = "END LC_TIME";
			const char	*	const Locale::Era_s = "era";
			const char	*	const Locale::EraDFmt_s = "era_d_fmt";
			const char	*	const Locale::EraTFmt_s = "era_t_fmt";
			const char	*	const Locale::EscapeChar_s = "escape_char";

			const char	*	const Locale::Fax_s = "fax";
			const char	*	const Locale::FirstWeekday_s = "first_weekday";
			const char	*	const Locale::FirstWorkday_s = "first_workday";
			const char	*	const Locale::FracDigits_s = "frac_digits";

			const char	*	const Locale::Graph_s = "graph";
			const char	*	const Locale::Grouping_s = "grouping";

			const char	*	const Locale::Height_s = "height";

			const char	*	const Locale::Include_s = "include";
			const char	*	const Locale::IntCurrSymbol_s = "int_curr_symbol";
			const char	*	const Locale::IntFracDigits_s = "int_frac_digits";
			const char	*	const Locale::IntPrefix_s = "int_prefix";
			const char	*	const Locale::IntSelect_s = "int_select";

			const char	*	const Locale::Language_s = "language";
			const char	*	const Locale::LangName_s = "lang_name";
			const char	*	const Locale::LangAb_s = "lang_ab";	// 2-digit ISO-639 language code
			const char	*	const Locale::LangTerm_s = "lang_term";	// 3-digit ISO-639-2/T language code
			const char	*	const Locale::LangLib_s = "lang_lib";	// 3-digit ISO-639-2/B language code
			const char	*	const Locale::LC_ADDRESS_s = "END LC_ADDRESS";
			const char	*	const Locale::LC_IDENTIFICATION_s = "END LC_IDENTIFICATION";
			const char	*	const Locale::LC_CTYPE_s = "LC_CTYPE";
			const char	*	const Locale::LC_COLLATE_s = "LC_COLLATE";
			const char	*	const Locale::LC_END_s = "END";
			const char	*	const Locale::LC_MEASUREMENT_s = "LC_MEASUREMENT";
			const char	*	const Locale::LC_MESSAGES_s = "LC_MESSAGES";
			const char	*	const Locale::LC_MONETARY_s = "LC_MONTARY";
			const char	*	const Locale::LC_NAME_s = "LC_NAME";
			const char	*	const Locale::LC_NUMERIC_s = "LC_NUMERIC";
			const char	*	const Locale::LC_PAPER_s = "LC_PAPER";
			const char	*	const Locale::LC_TELEPHONE_s = "LC_TELEPHONE";
			const char	*	const Locale::LC_TIME_s = "LC_TIME";

			const char	*	const Locale::MapToInPunct_s = "map to_inpunct";
			const char	*	const Locale::MapToOutPunct_s = "map to_outpunct";
			const char	*	const Locale::MapToTitle_s = "map totitle";
			const char	*	const Locale::MbCurMax_s = "mb_cur_max";
			const char	*	const Locale::MbCurMin_s = "mb_cur_min";
			const char	*	const Locale::Measurement_s = "measurement";
			const char	*	const Locale::Mon_s = "mon";
			const char	*	const Locale::MonDecimalPoint_s = "mon_decimal_point";
			const char	*	const Locale::MonGrouping_s = "mon_grouping";
			const char	*	const Locale::MonThousandsSep_s = "mon_thousands_sep";

			const char	*	const Locale::NameFmt_s = "name_fmt";
			const char	*	const Locale::NameGen_s = "name_gen";
			const char	*	const Locale::NameMr_s = "name_mr";
			const char	*	const Locale::NameMrs_s = "name_mrs";
			const char	*	const Locale::NameMiss_s = "name_miss";
			const char	*	const Locale::NameMs_s = "name_ms";
			const char	*	const Locale::NCsPrecedes_s = "n_cs_precedes";
			const char	*	const Locale::NSepBySpace_s = "n_sep_by_space";
			const char	*	const Locale::NSignPosn_s = "n_sign_posn";
			const char	*	const Locale::NegativeSign_s = "Negative_sign";
			const char	*	const Locale::Noexpr_s = "noexpr";
			const char	*	const Locale::Nostr_s = "nostr";

			const char	*	const Locale::OrderEnd_s = "order_end";
			const char	*	const Locale::OrderStart_s = "order_start";
			const char	*	const Locale::OutDigit_s = "outdigit";

			const char	*	const Locale::PCsPrecedes_s = "p_cs_precedes";
			const char	*	const Locale::PSignPosn_s = "p_sign_posn";
			const char	*	const Locale::PSepBySpace_s = "p_sep_by_space";
			const char	*	const Locale::PositiveSign_s = "positive_sign";
			const char	*	const Locale::PostalFmt_s = "postal_format";
			const char	*	const Locale::Print_s = "print";
			const char	*	const Locale::Punct_s = "punct";

			const char	*	const Locale::ReOrderAfter_s = "reorder-after";
			const char	*	const Locale::ReOrderEnd_s = "reorder-end";
			const char	*	const Locale::ReOrderSectionsAfter_s = "reorder-sections-after";
			const char	*	const Locale::ReOrderSectionsEnd_s = "reorder-sections-end";
			const char	*	const Locale::Revision_s = "revision";

			const char	*	const Locale::Script_s = "script";
			const char	*	const Locale::Source_s = "source";
			const char	*	const Locale::Space_s = "space";
			const char	*	const Locale::SymbolEquivalence_s = "symbol-equivalence";

			const char	* const Locale::TFmt_s = "t_fmt";
			const char	* const Locale::TFmtAmPm_s = "t_fmt_ampm";
			const char	*	const Locale::Tel_s = "tel";
			const char	*	const Locale::TelDomFmt_s = "tel_dom_fmt";
			const char	*	const Locale::TelIntFmt_s = "tel_int_fmt";
			const char	*	const Locale::Territory_s = "territory";
			const char	*	const Locale::ThousandsSep_s = "thousands_sep";
			const char	*	const Locale::Title_s = "title";
			const char	*	const Locale::ToLower_s = "tolower";
			const char	*	const Locale::ToUpper_s = "toupper";
			const char	*	const Locale::TranslitEnd_s = "translit_end";
			const char	*	const Locale::TranslitStart_s = "translit_start";

			const char	*	const Locale::Lower_s = "lower";

			const char	*	const Locale::Upper_s = "upper";

			const char	*	const Locale::Week_s = "week";
			const char	*	const Locale::Width_s = "width";
			const char	*	const Locale::WIDTH_s = "WIDTH";
			const char	*	const Locale::WIDTH_DEFAULT_s = "WIDTH_DEFAULT";

			const char	*	const Locale::XDigit_s = "xdigit";

			const char	*	const Locale::YesExpr_s = "yesexpr";
			const char	*	const Locale::YesStr_s = "yesstr";

			Locale::Charset_t			Locale::_LastCharMapFileIdUsed = 0;
			Locale::CharMapID_t		Locale::_LastCharMapIdUsed = 0;

			/**
			 * Measurement scale.
			 */
			enum Measurement_t {
				Metric = '1',
				UsCustomaryMeasurement = '2'
			};

			/**
			 * p_cs_precedes: The currency symbol precedes, or sycceeds the value.
			 * n_cs_precedes: The negagive symbol precedes, or sycceeds the value.
			 */
			enum Precedes_t {
				Succeeds = '0',
				Precedes = '1'
			};

			/**
			 * p_sep_by_space: Monetary: an integer that indicates the separation of
			 * currency_symbol, the sign string, and the value for a nonnegative
			 * formatted monetary quantity. The following values are recognized:
			 *
			 * n_sep_by_space: Monetary: an integer that indicates the separation
			 * of currency_symbol, the sign string, and the value for a nonnegative
			 * formatted monetary quantity. The following values are recognized:
			 */
			enum SepBySpace_t {
				/**
				 * No space separates the currency symbol and the value.
				 */
				NoSpace = '0',

				/**
				 * If the currency symbol and the sign string are adjacent, a
				 * space separates them from the value; otherwise a space separates
				 * the currency symbol and the value.
				 */
				CurrencyAdjacent = '1',

				/**
				 * If the currency symbol and the sign string are adjacent, a
				 * space separates them from the value; otherwise a space separates
				 * the sign string and the value.
				 */
				ValueAdjacent = '2'

			};

			/**
			 * followed by an integer that indicates where the positive_sign
			 * should be placed for a nonnegative monetary quantity:
			 */
			enum PSignPosn_t {
				/**
				 * Parentheses enclose the quantity and the currency_symbol or
				 * int_curr_symbol.
				 */
				Encloses = '0',

				/**
				 * The sign string precedes the quantity and the currency_symbol
				 * or the int_curr_symbol.
				 */
				PrecedesQuanity = '1',

				/**
				 * The sign string succeeds the quantity and the currency_symbol
				 * or the int_curr_symbol.
				 */
				SucceedsQuanity = '2',

				/**
				 * The sign string precedes the currency_symbol or the
				 * int_curr_symbol.
				 */
				PrecedesCurrency = '3',

				/**
				 * The sign string succeeds the currency_symbol or the
				 * int_curr_symbol.
				 */
				SucceedsCurrency = '4'
			};

			/**
			 * cal_direction: followed by a number value that indicates the direction for the
			 * display of calendar dates, as follows:
			 */
			enum CalDirection_t {
				/**
				 * Left-right from top.
				 */
				LeftRightTop = '1',

				/**
				 * Top-Down from Left.
				 */
				TopDownLeft = '2',

				/**
				 * Right-Left from Top.
				 */
				RightLeftTop = '3'
			};

			Locale::Locale()
			{
				_CharmapFp = nullptr;
				_LocaleFp = nullptr;
				_CommentChar = '#';
				_EscapeChar = '\\';

				return;
			}

			Locale::~Locale()
			{
				if (_CharmapFp != nullptr) {
					_CharmapFp->Close();
					delete _CharmapFp;
					_CharmapFp = nullptr;
				}

				if (_LocaleFp != nullptr) {
					_LocaleFp->Close();
					delete _LocaleFp;
					_LocaleFp = nullptr;
				}

				return;
			}

			Locale	*
			Locale::OpenLocale(const char * Path)
			{
				Locale			*			Results = nullptr;

				if (Path != nullptr) {
					Results-> _LocaleFp = new File();

					if (Results->_LocaleFp->Open(Path, O_RDONLY)) {
						Results = new Locale();

						if (!Results->_ParseLocale()) {
							delete Results;
							Results->_LocaleFp->Close();
							Results->_LocaleFp = nullptr;
						}
					}
				}

				return (Results);
			}

			Locale::Token_e
			Locale::_ParseEscapeChar(Locale & Parent, File * Fp)
			{
				Token_e				Results = EscapeChar_t;

				char				Ch = 0;

				while (isspace(Fp->LookNext())) {
					Fp->Read(&Ch, 1);

					if (Ch == '\n') {
						Results = Token_e_UnknownToken_t;
						break;
					}
				}

				if (Results) {
					Fp->Read(&Ch, 1);
					Parent._EscapeChar = Ch;
					Parent._SkipPastEol(Fp);
				}

				return (Results);
			}

			Locale::Token_e
			Locale::_ParseCommentChar(Locale & Parent, File * Fp)
			{
				Token_e				Results = CommentChar_t;

				char				Ch = 0;

				while (isspace(Fp->LookNext())) {
					Fp->Read(&Ch, 1);

					if (Ch == '\n') {
						Results = Token_e_UnknownToken_t;
						break;
					}
				}

				if (Results) {
					Fp->Read(&Ch, 1);
					Parent._CommentChar = Ch;
					Parent._SkipPastEol(Fp);
				}

				return (Results);
			}

			static bool
			SkipWS(File * Fp)
			{
				bool			Results = true;

				char			Ch = 0;

				do {
					Fp->Read(&Ch, 1);

					if (Ch == ' ' || Ch == '\t') {
						continue;
					}

					if (Ch == '\n') {
						fprintf(stderr,
						        "Unable to parse, found end of line too soon.\n");
						Results = false;
						break;
					}

					if (Fp->AtEOF()) {
						fprintf(stderr,
						        "Unable to parse, found end of file to soon.\n");
						Results = false;
						break;
					}
				} while (1);

				return (Results);
			}

			static bool
			SkipPastNL(File * Fp)
			{
				bool			Results = true;

				char			Ch = 0;

				do {
					Fp->Read(&Ch, 1);

					if (Ch == ' ' || Ch == '\t') {
						continue;
					}

					if (Ch == '\n') {
						Fp->Read(&Ch, 1);
						break;
					}

					if (Fp->AtEOF()) {
						fprintf(stderr,
						        "Unable to parse, found end of file to soon.\n");
						Results = false;
						break;
					}
				} while (1);

				return (Results);
			}

			static void
			SkipPastNL2(File * Fp)
			{
				char			Ch = 0;

				do {
					Fp->Read(&Ch, 1);

					if (Ch == ' ' || Ch == '\t') {
						continue;
					}

					if (Ch == '\n') {
						Fp->Read(&Ch, 1);
						break;
					}

					if (Fp->AtEOF()) {
						break;
					}
				} while (1);

				return;
			}

			bool
			Locale::_ParseCharmap(CharMapFile & NewMap)
			{
				bool		Results = false;

				char		Ch;
				char		Buf[1024];
				char	*	BufPtr = Buf;
				size_t	Len = 0;
				char		CommentChar = '#';
				char		EscapeChar = '\\';
				bool		GotError = false;

				while (!_CharmapFp->AtEOF()) {

					if (GotError) {
						break;
					}

					while (_CharmapFp->LookNext() == '<') {
						// Read past '<'
						_CharmapFp->Read(&Ch, 1);

						// Read until '>' or EOL or EOF
						// Read <code_set_name>, <comment_char>,
						// <escape_char>, <mb_cur_min>, <mb_cur_max>,
						// or it is an error.
						//
						while (_CharmapFp->LookNext() != '>') {
							_CharmapFp->Read(BufPtr, 1);
							Len++;

							if (Len > sizeof(Buf) - 2) {
								*BufPtr = 0;
								fprintf(stderr,
								        "Unable to parse Charmap, found too many character"
								        "before matching '<', '>' character,"
								        " while readin %s:\n",
								        Buf);
								GotError = true;
								break;

							} else if (*BufPtr == '\n') {
								*BufPtr = 0;
								fprintf(stderr,
								        "Unable to parse Charmap, found end of line"
								        "before matching '<', '>' character,"
								        " while readin %s:\n",
								        Buf);
								GotError = true;
								break;

							} else if (_CharmapFp->AtEOF()) {
								*BufPtr = 0;
								fprintf(stderr,
								        "Unable to parse Charmap, found end of file"
								        "before matching '<', '>' character,"
								        " while readin %s:\n",
								        Buf);
								GotError = true;
								break;
							}

							BufPtr++;
							*BufPtr = 0;
						}

						if (!GotError) {
							// Read past '>'
							//
							_CharmapFp->Read(&Ch, 1);

							// Skip following white space.
							//
							if (!SkipWS(_CharmapFp)) {
								// Error, found EOL or EOF.
								//
								GotError = true;
								break;
							}

							if (!GotError) {
								if (strcmp(CodeSetName_s, Buf) == 0) {
									BufPtr = Buf;

									// Read char_set_name until EOL, comment, or EOF.
									//
									do {
										_CharmapFp->Read(BufPtr, 1);

										if (*BufPtr == '\n'
										    || *BufPtr == ' '
										    || *BufPtr == '\t'
										    || *BufPtr == CommentChar) {
											*BufPtr = 0;
											NewMap.Name = strdup(Buf);
											break;
										}

										BufPtr++;

									} while (!_CharmapFp->AtEOF());

									if (!SkipPastNL(_CharmapFp)) {
										GotError = true;
										break;
									}

								} else if (CommentChar == *Buf) {
									if (!SkipWS(_CharmapFp)) {
										GotError = true;
										break;
									}

									_CharmapFp->Read(&Ch, 1);
									CommentChar = Ch;
									break;

								} else if (EscapeChar == *Buf) {
									if (!SkipWS(_CharmapFp)) {
										GotError = true;
										break;
									}

									_CharmapFp->Read(&Ch, 1);
									EscapeChar = Ch;
									break;

								} else if (strcmp(MbCurMax_s, Buf) == 0) {
									if (!SkipWS(_CharmapFp)) {
										GotError = true;
										break;
									}

									_CharmapFp->Read(Buf, 1);
									Buf[1] = 0;
									NewMap.MaxLength = atoi(Buf);
									break;

								} else if (strcmp(MbCurMin_s, Buf) == 0) {
									if (!SkipWS(_CharmapFp)) {
										GotError = true;
										break;
									}

									_CharmapFp->Read(Buf, 1);
									Buf[1] = 0;
									NewMap.MinLength = atoi(Buf);
									break;
								}
							}
						}
					}

					// Read the rest of the file.
					//
					while (!_CharmapFp->AtEOF()) {
						_CharmapFp->Read(&Ch, 1);

						if (Ch == CommentChar) {
							do {
								while (Ch != '\n') {
									_CharmapFp->Read(&Ch, 1);

									if (_CharmapFp->AtEOF()) {
										break;
									}
								}

								// Read past '\n'
								//
								_CharmapFp->Read(&Ch, 1);
								continue;
							} while (!_CharmapFp->AtEOF());

						} else {
							char			BigBuf[10240];
							char		*	Ptr = BigBuf;
							uint64_t	Len = 0;

							if (_CharmapFp->ReadLine((uint8_t **)&Ptr, Len)) {
								// End of file.
								break;
							}

							uint8_t	Ch8;
							uint8_t	Ch8_2;
							uint8_t		ChWidth;
							CharMap	*	CMap = nullptr;
							std::vector<uint8_t>	Bytes;
							std::vector<uint8_t>::iterator bIt;
							off_t				bOffset = 0;

							if (strcmp(BigBuf, CharMap_s) == 0) {
								// Read lines of the form:
								// <U####> hex comment
								//


								do {
									if (BigBuf[0] == '<') {
										Ptr = BigBuf + 1;
										char	*	End = strchr(Ptr, '>');

										CMap = new CharMap();
										CMap->SymbolicName = StringCache::Add(Ptr, (End - Ptr));
										Ptr = End + 1; // Point past '>'

									} else {
										fprintf(stderr, "Unable to parse: %s\n", BigBuf);
										GotError = true;
										break;
									}

									// Skip space after symbolic value.
									//
									while (*Ptr == ' ' && *Ptr == '\t') {
										Ptr++;
									}

									// Read bytes.
									//
									size_t				Len = 0;

									while (*Ptr == EscapeChar) {
										Ptr++;

										switch (*Ptr) {
											case 'x':
												Ptr++;
												Ch8 = (uint8_t)htoi(Ptr);
												break;

											case 'd':
												Ch8 = (uint8_t)atoi(Ptr);
												break;

											default:
												fprintf(stderr, "Unable to parse %s", Ptr);
												GotError = true;
												break;
										}

										Bytes.push_back(Ch8);

										while ((*Ptr != EscapeChar)
										       && *Ptr != ' '
										       && *Ptr != '\t') {
											Ptr++;
										}
									}

									CMap->OctetsLen = Bytes.size();
									CMap->Octets = new int8_t[CMap->OctetsLen];
									bOffset = 0;

									for (bIt = Bytes.begin(); bIt != Bytes.end(); bIt++) {
										CMap->Octets[bOffset++] = *bIt;
									}

									Bytes.clear();

									// Skip space after bytes.
									while (*Ptr == ' ' && *Ptr == '\t' && (*Ptr != '\n')) {
										Ptr++;
									}

									// Save comment
									//
									if (*Ptr != '\n') {
										char	*	Nl = strchr(Ptr, '\n');

										if (Nl != nullptr) {
											size_t	CLen = Nl - Ptr;

											CMap->Comment = new char[CLen + 1];
											strncpy(CMap->Comment, Ptr, CLen);
											CMap->Comment[CLen] = 0;
											Ptr = Nl + 1;
										}

									} else {
										CMap->Comment = nullptr;
									}
								} while (!GotError && !_CharmapFp->AtEOF());

							} else if (strcmp(BigBuf, WIDTH_s) == 0) {

								const char	*	Sym1Start = nullptr;
								const char	*	Sym1End = nullptr;
								char			*		Sym1 = nullptr;

								const char	*	Sym2Start = nullptr;
								const char	*	Sym2End = nullptr;
								char			*		Sym2 = nullptr;

								// <sym1>...<sym2> width
								// or
								// <Sym> width
								//
								SkipPastNL(_CharmapFp);
								Ptr = &BigBuf[0];

								do {
									// Reset
									//
									Sym1Start = nullptr;
									Sym1End = nullptr;
									Sym1 = nullptr;

									Sym2Start = nullptr;
									Sym2End = nullptr;
									Sym2 = nullptr;

									if (_CharmapFp->ReadLine((uint8_t **)Ptr, Len)) {
										fprintf(stderr, "Got to end of file, no END WIDTH\n");
										GotError = true;
										break;
									}

									Ptr = BigBuf;

									if (*Ptr == '<') {
										Ptr++;
										Sym1Start = Ptr;

										while (*Ptr != '>') {
											Ptr++;
										}

										Sym1End = Ptr;
										Ptr++;	// Past '>'

										// "..." or  "<"
										//
										if (strncmp(Ptr, "...<", 4) == 0) {
											Ptr += 4;
											Sym2Start = Ptr;

											while (*Ptr != '>') {
												Ptr++;
											}

											Sym2End = Ptr;
											Ptr++;	// Past '>'
										}

										// Parse width, skip space.
										//
										while ((*Ptr != ' ') && (*Ptr != '\t')) {
											Ptr++;
										}

										// At width, set it.
										//
										ChWidth = atoi(Ptr);

										// Update unicode data width(s)
										//
										Sym1 = String::strdup8(Sym1Start,
										                       (Sym1End - Sym1Start));

										if (Sym2Start != nullptr) {
											Sym2 = String::strdup8(Sym2Start,
											                       (Sym2End - Sym2Start));
										}

										NewMap.UpdateWidth(Sym1, ChWidth, Sym2);

									} else {
										fprintf(stderr, "Expected '<U', got %s\n", BigBuf);
										GotError = true;
										break;
									}
								}

								while (!GotError && !_CharmapFp->AtEOF());
							}
						}
					}
				}

				return (Results);
			}

			bool
			Locale::_ParseLocale()
			{
				bool				Results = false;

				Dispatch		Tokens[] = {

					{EscapeChar_s, _ParseEscapeChar, EscapeChar_t},
					{CommentChar_s, _ParseCommentChar, CommentChar_t},
					{LC_CTYPE_s, Lc_Ctype::Parse, LC_CTYPE_t},
					{LC_COLLATE_s, Lc_Collate::Parse, LC_COLLATE_t},
					{LC_MESSAGES_s, Lc_Messages::Parse, LC_MESSAGES_t},
					{LC_MONETARY_s, Lc_Monetary::Parse, LC_MONETARY_t},
					{LC_NUMERIC_s, Lc_Numeric::Parse, LC_NUMERIC_t},
					{LC_TIME_s, Lc_Time::Parse, LC_TIME_t},
					{LC_ADDRESS_s, Lc_Address::Parse, LC_ADDRESS_t},
					{LC_IDENTIFICATION_s, Lc_Identification::Parse, LC_IDENTIFICATION_t},
					{LC_MEASUREMENT_s, Lc_Measurement::Parse, LC_MEASUREMENT_t},
					{LC_NAME_s, Lc_Name::Parse, LC_NAME_t},
					{LC_PAPER_s, Lc_Paper::Parse, LC_PAPER_t},
					{LC_TELEPHONE_s, Lc_Telephone::Parse, LC_TELEPHONE_t},
					{nullptr, nullptr, Token_e_UnknownToken_t}
				};

				Token_e				What;

				do {
					What = _Parse(_LocaleFp, Tokens);

					if (What == Token_e_UnknownToken_t) {
						break;
					}
				} while (What != EOF_t);

				if (What == EOF_t) {
					Results = true;
				}

				return (Results);
			}

			void
			Locale::_SkipPastEol(File * Fp)
			{
				char			ch;

				while (Fp->LookNext() != '\n') {
					Fp->Read(&ch, 1);
				}

				if (!Fp->AtEOF()) {
					// Read the '\n', then go to first character after newline.
					//
					Fp->Read(&ch, 1);
				}

				return;
			}

			const char	*
			Locale::_ParseQuotedString(size_t & Len, File * Fp)
			{
				const char	*	Results = Empty_s;

				const char	*	Start = Fp->GetBuffer();
				off_t					Position = Fp->Tell();

				const char	*	Dot = &Start[Position];

				Len = 0;

				// Skip all leading spaces before the value.
				//
				while (isspace(*Dot)) {
					Dot++;
				}

				// Start of something.
				//
				Results = Dot;

				if (*Dot == '"') {
					Dot++;

					// Start of value.
					//
					Results = Dot;

					while (*Dot != '"') {
						if (*Dot == '\n') {
							break;
						}

						Dot++;
						Len++;
					}

				} else {
					// Non-quoted string.
					//
					const char	*	LastChar = Dot;

					Results = Dot;

					// Continue until newline or comment character.
					// Capture all characters, trimming whitespace off of the end.
					//
					while (*Dot != '\n') {
						Dot++;

						if (!isspace(*Dot)) {
							LastChar = Dot;
						}

						if (*Dot == _CommentChar) {
							_SkipPastEol(Fp);
							break;
						}
					}

					Dot = LastChar;
					Len = LastChar - Results;
				}

				if (Len > 0) {
					Fp->Lseek(Position + Len, File::SEEK_SET_t);
				}

				return (Results);
			}

			Locale::LcBase::LcBase(Locale & ParentObject, LcCategory_e Cat)
				: Parent(ParentObject)
			{
				Category = Cat;

				return;
			}

			Locale::LcBase::~LcBase()
			{
				Category = LC_UNDEFINED_t;

				return;
			}

			bool
			Locale::LcBase::InSet(const std::vector<USet> & Set,
			                      const char * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					std::vector<USet>::const_iterator	it;

					for (it = Set.begin(); it != Set.end(); it++) {
						if ((*it).Right > 0) {
							if ((*ToTest >= (*it).Left) && (*ToTest <= (*it).Right)) {
								Results = true;
								break;
							}

						} else {
							if (*ToTest == (*it).Left) {
								Results = true;
								break;
							}
						}
					}
				}

				return (Results);
			}

			bool
			Locale::LcBase::InSet(const std::vector<USet> & Set,
			                      const char16_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					std::vector<USet>::const_iterator	it;

					for (it = Set.begin(); it != Set.end(); it++) {
						if ((*it).Right > 0) {
							if ((*ToTest >= (*it).Left) && (*ToTest <= (*it).Right)) {
								Results = true;
								break;
							}

						} else {
							if (*ToTest == (*it).Left) {
								Results = true;
								break;
							}
						}
					}
				}

				return (Results);
			}

			bool
			Locale::LcBase::InSet(const std::vector<USet> & Set,
			                      const char32_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					std::vector<USet>::const_iterator	it;

					for (it = Set.begin(); it != Set.end(); it++) {
						if ((*it).Right > 0) {
							if ((*ToTest >= (*it).Left) && (*ToTest <= (*it).Right)) {
								Results = true;
								break;
							}

						} else {
							if (*ToTest == (*it).Left) {
								Results = true;
								break;
							}
						}
					}
				}

				return (Results);
			}

			bool
			Locale::LcBase::InSet(const std::vector<USet> & Set,
			                      const wchar_t * ToTest) const
			{
				bool				Results = false;

				if (ToTest != nullptr) {
					std::vector<USet>::const_iterator	it;

					for (it = Set.begin(); it != Set.end(); it++) {
						if ((*it).Right > 0) {
							if ((*ToTest >= (*it).Left) && (*ToTest <= (*it).Right)) {
								Results = true;
								break;
							}

						} else {
							if (*ToTest == (*it).Left) {
								Results = true;
								break;
							}
						}
					}
				}

				return (Results);
			}

			Locale::CharMapFile::CharMapFile()
			{
				ID = ++_LastCharMapFileIdUsed;
				Name = nullptr;
				Comment = nullptr;
				MinLength = 1;
				MaxLength = 1;

				return;
			}

			Locale::CharMapFile::~CharMapFile()
			{

				if (Name != nullptr) {
					StringCache::Remove(Name);
					Name = nullptr;
				}

				if (Comment != nullptr) {
					StringCache::Remove(Comment);
					Comment = nullptr;
				}

				MinLength = 0;
				MaxLength = 0;

				std::map<const char *, CharMap *>::iterator	nIt;
				std::map<CharMapID_t, CharMap *>::iterator	IdIt;
				CharMap	*	CMap = nullptr;

				for (nIt = MapBySymbolicName.begin(); nIt != MapBySymbolicName.end(); nIt++) {
					if (nIt->first != nullptr) {
						StringCache::Remove(nIt->first);
					}

					if (nIt->second != nullptr) {
						delete nIt->second;
					}
				}

				MapBySymbolicName.clear();

				for (IdIt = MapByID.begin(); IdIt != MapByID.end(); IdIt++) {

					CMap = IdIt->second;

					if (CMap != nullptr) {
						delete CMap;
					}
				}

				MapByID.clear();
				ID = 0;

				return;
			}

			void
			Locale::CharMapFile::UpdateWidth(const char * FirstSymbol,
			                                 uint8_t CWidth,
			                                 const char * LastSymbol)
			{
				std::vector<CharMap *>::iterator	cIt;
				bool				StartUpdating = false;

				// Go through the orderd lists, start updating on first (or only),
				// stop on last.
				//
				for (cIt = SymbolList.begin(); cIt != SymbolList.end(); cIt++) {

					if (!StartUpdating) {
						if (strcmp(FirstSymbol, (*cIt)->SymbolicName) == 0) {
							(*cIt)->Width = CWidth;

							if (LastSymbol == nullptr) {
								// Only one to update.
								//
								break;
							}

							StartUpdating = true;
						}

					} else {
						(*cIt)->Width = CWidth;

						if (strcmp(LastSymbol, (*cIt)->SymbolicName) == 0) {
							// Last one just updated.
							//
							break;
						}
					}
				}

				return;
			}

			Locale::CharMap::CharMap()
			{
				CharMapID = 0;
				Octets = nullptr;;
				OctetsLen = 0;
				Comment = nullptr;
				Width = 1;

				return;
			}

			Locale::CharMap::~CharMap()
			{
				CharMapID = 0;

				if (Octets != nullptr) {
					delete Octets;
					Octets = nullptr;
				}

				OctetsLen = 0;

				if (Comment != nullptr) {
					StringCache::Remove(Comment);
					Comment = nullptr;
				}

				Width = 0;

				return;
			}

			Locale::Token_e
			Locale::_Parse(File * Fp, const Dispatch * Table)
			{
				Token_e				Results = Token_e_UnknownToken_t;

				const char	*	Buf = Fp->GetBuffer();
				const char	*	Want = nullptr;
				off_t					Position = Fp->Tell();
				off_t					Len = 0;

				for (off_t Offset = 0; Table[Offset].LookFor != nullptr; Offset++) {
					Want = Table[Offset].LookFor;
					Len = strlen(Want);

					if (strncmp(Want, &Buf[Position], Len) == 0) {
						Fp->Lseek(Len, File::SEEK_CUR_t);

						if (Table[Offset].ParserPtr != nullptr) {
							Results = Table[Offset].ParserPtr(*this, Fp);

						} else {
							Results = Table[Offset].Token;
						}

						break;
					}
				}

				return (Results);
			}

		}
	}
}

