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
// all OF THIS CODE IS ORIGINAL WORK BY THE COPYRIGHT HOLDER.
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

/**
 * @file String.hpp "<SaS/String/String.hpp>"
 * @ingroup STRING
 * String manipulation routines for C++
 */
#ifndef SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRING_LOCALE_HPP_
#define SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRING_LOCALE_HPP_

#include <map>
#include <memory>
#include <stdint.h>
#include <SaS/Common/hex.hpp>
#include <SaS/String/StringCompareOperator.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			/**
			 * @class Locale StringLocale.hpp "<SaS/String/StringLocale.hpp>"
			 * POSIX, UNIX, and Linux locale implementations allow for only
			 * one locale at a time. these SaS objects allow for loading
			 * an providing isprint(), isalpha(), ... for randon character
			 * sets and locals.
			 */
			class Locale
				: public instance<Locale> {

					static const char	*	const Abbay_s; /** "abbay" */
					static const char	*	const Abmon_s; /** "abmon" */
					static const char	*	const	Abbreviation_s; /** "abbreviation" */
					static const char	*	const Address_s; /** "address" */
					static const char	*	const Alpha_s; /** "alpha" */
					static const char	*	const AltDigits_s; /** "alt_digits" */
					static const char	*	const AmPm_s; /** "am_pm" */
					static const char	*	const	Application_s; /** "application" */
					static const char	*	const Audience_s; /** "audience" */

					static const char	*	const Blank_s; /** "blank" */

					static const char	*	const	CalDirection_s; /** "cal_direction" */
					static const char	*	const CharClass_s; /** "char_class" */
					static const char	*	const CharConv_s; /** "charconv" */
					static const char	*	const CharMap_s; /** "CHARMAP" */
					static const char	*	const Class_s; /** "class" */
					static const char	*	const Cntrl_s; /** "cntrl" */
					static const char	*	const CodeSetName_s; /** "code_set_name" */
					static const char	*	const	CollWeightMax_s; /* "coll_weight_max" */
					static const char	*	const	CollatingElement_s; /* "collating-element" */
					static const char	*	const	CollatingSymbol_s; /* "collating-symbol" */
					static const char	*	const	CommentChar_s; /** "comment_char" */
					static const char	*	const Contact_s; /** "contact" */
					static const char	*	const Copy_s_s; /** "copy" */
					static const char	*	const	CountryAb2_s; /* "country_ab2"	// 2-letter ISO-3166 country code. */
					static const char	*	const	CountryAb3_s; /* "country_ab3"	// 3-letter ISO-3166 country code. */
					static const char	*	const CountryCar_s; /** "country_car" */
					static const char	*	const	CountryIsbn_s; /** "country_isbn" */
					static const char	*	const	CountryName_s; /** "country_name" */
					static const char	*	const	CountryNum_s; /* "country_num"	// ISO-3166 Country number */
					static const char	*	const	CountryPost_s; /** "country_post" */
					static const char	*	const	CurrencySymbol_s; /* "currency_symbol" */

					static const char	DefaultEscape; /** '\\' */
					static const char	DefaultComment; /** '#' */

					static const char	* const DFmt_s; /** "d_fmt" */
					static const char	* const DTFmt_s; /** "d_t_fmt" */
					static const char	* const Date_s; /** "date" */
					static const char	* const DateFmt_s; /** "date_fmt" */
					static const char	* const Day_s; /** "day" */
					static const char	* const	DecimalPoint_s; /** "decimal_point" */
					static const char	* const	DefaultMissing_s; /* "default_mising" */
					static const char	* const Define_s; /** "define" */
					static const char	*	const Digit_s; /** "digit" */

					static const char	*	const Email_s; /** "email" */
					static const char	*	const Empty_s; /** "" */
					static const char	*	const END_LC_ADDRESS_s; /** "END LC_ADDRESS" */
					static const char	*	const END_LC_IDENTIFICATION_s; /** "END LC_IDENTIFICATION" */
					static const char	*	const END_LC_CTYPE_s; /** "END LC_CTYPE" */
					static const char	*	const END_LC_COLLATE_s; /** "END LC_COLLATE" */
					static const char	*	const END_LC_MEASUREMENT_s; /** "END LC_MEASUREMENT" */
					static const char	*	const END_LC_MESSAGES_s; /** "END LC_MESSAGES" */
					static const char	*	const END_LC_MONETARY_s; /** "END LC_MONETARY" */
					static const char	*	const END_LC_NAME_s; /** "END LC_NAME" */
					static const char	*	const END_LC_NUMERIC_s; /** "END LC_NUMERIC" */
					static const char	*	const END_LC_PAPER_s; /** "END LC_PAPER" */
					static const char	*	const END_LC_TELEPHONE_s; /** "END LC_TELEPHONE" */
					static const char	*	const END_LC_TIME_s; /** "END LC_TIME" */
					static const char	*	const Era_s; /** "era" */
					static const char	*	const EraDFmt_s; /** "era_d_fmt" */
					static const char	*	const EraTFmt_s; /** "era_t_fmt" */
					static const char	*	const EscapeChar_s; /** "escape_char" */

					static const char	*	const Fax_s; /** "fax" */
					static const char	*	const	FirstWeekday_s; /** "first_weekday" */
					static const char	*	const	FirstWorkday_s; /** "first_workday" */
					static const char	*	const FracDigits_s; /** "frac_digits" */

					static const char	*	const Graph_s; /** "graph" */
					static const char	*	const Grouping_s; /** "grouping" */

					static const char	*	const Height_s; /** "height" */

					static const char	*	const Include_s; /** "include" */
					static const char	*	const	IntCurrSymbol_s; /* "int_curr_symbol" */
					static const char	*	const	IntFracDigits_s; /* "int_frac_digits" */
					static const char	*	const IntPrefix_s; /** "int_prefix" */
					static const char	*	const IntSelect_s; /** "int_select" */

					static const char	*	const Language_s; /** "language" */
					static const char	*	const LangName_s; /** "lang_name" */
					static const char	*	const	LangAb_s; /* "lang_ab"	// 2-digit ISO-639 language code */
					static const char	*	const	LangTerm_s; /* "lang_term"	// 3-digit ISO-639-2/T language code */
					static const char	*	const	LangLib_s; /* "lang_lib"	// 3-digit ISO-639-2/B language code */
					static const char	*	const LC_ADDRESS_s; /** "LC_ADDRESS" */
					static const char	*	const LC_COLLATE_s; /** "LC_COLLATE" */
					static const char	*	const LC_CTYPE_s; /** "LC_CTYPE" */
					static const char	*	const LC_END_s; /** "END" */
					static const char	*	const	LC_IDENTIFICATION_s; /* "LC_IDENTIFICATION" */
					static const char	*	const	LC_MEASUREMENT_s; /* "LC_MEASUREMENT" */
					static const char	*	const	LC_MESSAGES_s; /** "LC_MESSAGES" */
					static const char	*	const	LC_MONETARY_s; /** "LC_MONETARY" */
					static const char	*	const LC_NAME_s; /** "LC_NAME" */
					static const char	*	const LC_NUMERIC_s; /** "LC_NUMERIC" */
					static const char	*	const LC_PAPER_s; /** "LC_PAPER" */
					static const char	*	const	LC_TELEPHONE_s; /** "LC_TELEPHONE" */
					static const char	*	const LC_TIME_s; /** "LC_TIME" */

					static const char	*	const	MapToInPunct_s; /** "map to_inpunct" */
					static const char	*	const	MapToOutPunct_s; /** "map to_outpunct" */
					static const char	*	const MapToTitle_s; /** "map totitle" */
					static const char	*	const MbCurMax_s; /** "mb_cur_max" */
					static const char	*	const MbCurMin_s; /** "mb_cur_min" */
					static const char	*	const	Measurement_s; /** "measurement" */
					static const char	*	const Mon_s; /** "mon" */
					static const char	*	const	MonDecimalPoint_s; /* "mon_decimal_point" */
					static const char	*	const	MonGrouping_s; /** "mon_grouping" */
					static const char	*	const	MonThousandsSep_s; /* "mon_thousands_sep" */

					static const char	*	const NameFmt_s; /** "name_fmt" */
					static const char	*	const NameGen_s; /** "name_gen" */
					static const char	*	const NameMr_s; /** "name_mr" */
					static const char	*	const NameMrs_s; /** "name_mrs" */
					static const char	*	const NameMiss_s; /** "name_miss" */
					static const char	*	const NameMs_s; /** "name_ms" */
					static const char	*	const	NCsPrecedes_s; /** "n_cs_precedes" */
					static const char	*	const	NSepBySpace_s; /** "n_sep_by_space" */
					static const char	*	const NSignPosn_s; /** "n_sign_posn" */
					static const char	*	const	NegativeSign_s; /** "Negative_sign" */
					static const char	*	const Noexpr_s; /** "noexpr" */
					static const char	*	const Nostr_s; /** "nostr" */

					static const char	*	const OrderEnd_s; /** "order_end" */
					static const char	*	const OrderStart_s; /** "order_start" */
					static const char	*	const OutDigit_s; /** "outdigit" */

					static const char	*	const	PCsPrecedes_s; /** "p_cs_precedes" */
					static const char	*	const PSignPosn_s; /** "p_sign_posn" */
					static const char	*	const	PSepBySpace_s; /** "p_sep_by_space" */
					static const char	*	const	PositiveSign_s; /** "positive_sign" */
					static const char	*	const	PostalFmt_s; /** "postal_format" */
					static const char	*	const Print_s; /** "print" */
					static const char	*	const Punct_s; /** "punct" */
					static const char	*	const	ReOrderAfter_s; /** "reorder-after" */
					static const char	*	const ReOrderEnd_s; /** "reorder-end" */
					static const char	*	const	ReOrderSectionsAfter_s; /* "reorder-sections-after" */
					static const char	*	const	ReOrderSectionsEnd_s; /* "reorder-sections-end" */
					static const char	*	const Revision_s; /** "revision" */
					static const char	*	const Script_s; /** "script" */
					static const char	*	const Source_s; /** "source" */
					static const char	*	const Space_s; /** "space" */
					static const char	*	const	SymbolEquivalence_s; /* "symbol-equivalence" */

					static const char	* const TFmt_s; /** "t_fmt" */
					static const char	* const TFmtAmPm_s; /** "t_fmt_ampm" */
					static const char	*	const Tel_s; /** "tel" */
					static const char	*	const TelDomFmt_s; /** "tel_dom_fmt" */
					static const char	*	const TelIntFmt_s; /** "tel_int_fmt" */
					static const char	*	const Territory_s; /** "territory" */
					static const char	*	const	ThousandsSep_s; /** "thousands_sep" */
					static const char	*	const Title_s; /** "title" */
					static const char	*	const ToLower_s; /** "tolower" */
					static const char	*	const ToUpper_s; /** "toupper" */
					static const char	*	const	TranslitEnd_s; /** "translit_end" */
					static const char	*	const	TranslitStart_s; /* "translit_start" */

					static const char	*	const Lower_s; /** "lower" */

					static const char	*	const Upper_s; /** "upper" */

					static const char	*	const Week_s; /** "week" */
					static const char	*	const Width_s; /** "width" */
					static const char	*	const WIDTH_s; /** "WIDTH" */
					static const char	*	const WIDTH_DEFAULT_s; /** "WIDTH_DEFAULT" */

					static const char	*	const XDigit_s; /** "xdigit" */

					static const char	*	const YesExpr_s; /** "yesexpr" */
					static const char	*	const YesStr_s; /** "yesstr" */

					/**
					 * Locale - Default constructor.
					 */
					Locale();

					/**
					 * Locale - Destructor.
					 */
					~Locale();

					/**
					 * Handle for a charset.
					 */
					typedef uint64_t			Charset_t;

					/**
					 * Handle for a character maping.
					 */
					typedef uint64_t			CharMapID_t;

					/**
					 * Handle for a locale. (Note POSIX is local_t - not the same thing)
					 */
					typedef uint64_t			Locale_t;

					/**
					 * Parse a locale file.
					 *
					 * @param Path The locale file to open.
					 *
					 * @return A new Locale, or nullptr when unable to open Path,
					 * or when Path is not a locale file.
					 */
					static Locale	*	OpenLocale(const char * Path);

					/**
					 * All implemented tokens.
					 */
					enum Token_e {
						Token_e_UnknownToken_t = 0,
						Abbay_t,
						Abmon_t,
						Abbreviation_t,
						Address_t,
						Alpha_t,
						AltDigits_t,
						AmPm_t,
						Application_t,
						Audience_t,
						Blank_t,
						CalDirection_t,
						CharClass_t,
						CharConv_t,
						Class_t,
						Cntrl_t,
						CollWeightMax_t,
						CollatingElement_t,
						CollatingSymbol_t,
						CommentChar_t,
						Contact_t,
						Copy_t,
						CountryAb2_t,
						CountryAb3_t,
						CountryCar_t,
						CountryIsbn_t,
						CountryName_t,
						CountryNum_t,
						CountryPost_t,
						CurrencySymbol_t,
						DefaultEscape_t,
						DefaultComment_t,
						DFmt_t,
						DTFmt_t,
						Date_t,
						DateFmt_t,
						Day_t,
						DecimalPoint_t,
						DefaultMissing_t,
						Define_t,
						Digit_t,
						EOF_t,
						Email_t,
						END_LC_ADDRESS_t,
						END_LC_CTYPE_t,
						END_LC_COLLATE_t,
						END_LC_IDENTIFICATION_t,
						END_LC_MEASUREMENT_t,
						END_LC_MESSAGES_t,
						END_LC_MONETARY_t,
						END_LC_NAME_t,
						END_LC_NUMERIC_t,
						END_LC_PAPER_t,
						END_LC_TELEPHONE_t,
						END_LC_TIME_t,
						Era_t,
						EraDFmt_t,
						EraTFmt_t,
						EscapeChar_t,
						Fax_t,
						FirstWeekday_t,
						FirstWorkday_t,
						FracDigits_t,
						Graph_t,
						Grouping_t,
						Height_t,
						Include_t,
						IntCurrSymbol_t,
						IntFracDigits_t,
						IntPrefix_t,
						IntSelect_t,
						Language_t,
						LangName_t,
						LangAb_t,
						LangTerm_t,
						LangLib_t,
						LC_ADDRESS_t,
						LC_CTYPE_t,
						LC_COLLATE_t,
						LC_END_t,
						LC_IDENTIFICATION_t,
						LC_MEASUREMENT_t,
						LC_MESSAGES_t,
						LC_MONETARY_t,
						LC_NAME_t,
						LC_NUMERIC_t,
						LC_PAPER_t,
						LC_TELEPHONE_t,
						LC_TIME_t,
						MapToInPunct_t,
						MapToOutPunct_t,
						MapToTitle_t,
						Measurement_t,
						Mon_t,
						MonDecimalPoint_t,
						MonGrouping_t,
						MonThousandsSep_t,
						NameFmt_t,
						NameGen_t,
						NameMr_t,
						NameMrs_t,
						NameMiss_t,
						NameMs_t,
						NCsPrecedes_t,
						NSepBySpace_t,
						NSignPosn_t,
						NegativeSign_t,
						Noexpr_t,
						Nostr_t,
						OrderEnd_t,
						OrderStart_t,
						OutDigit_t,
						PCsPrecedes_t,
						PSignPosn_t,
						PSepBySpace_t,
						PositiveSign_t,
						PostalFmt_t,
						Print_t,
						Punct_t,
						ReOrderAfter_t,
						ReOrderEnd_t,
						ReOrderSectionsAfter_t,
						ReOrderSectionsEnd_t,
						Revision_t,
						Script_t,
						Source_t,
						Space_t,
						SymbolEquivalence_t,
						TFmt_t,
						TFmtAmPm_t,
						Tel_t,
						TelDomFmt_t,
						TelIntFmt_t,
						Territory_t,
						ThousandsSep_t,
						Title_t,
						ToLower_t,
						ToUpper_t,
						TranslitEnd_t,
						TranslitStart_t,
						Lower_t,
						Upper_t,
						Week_t,
						Width_t,
						XDigit_t,
						YesExpr_t,
						YesStr_t
					};

					/**
					 * @enum LcCategory StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 */
					enum LcCategory_e {
						LC_UNDEFINED_t = Token_e_UnknownToken_t,
						LC_CTYPE_Cat = LC_CTYPE_t,
						LC_COLLATE_Cat = LC_COLLATE_t,
						LC_MESSAGES_Cat = LC_MESSAGES_t,
						LC_MONETARY_Cat = LC_MONETARY_t,
						LC_NUMERIC_Cat = LC_NUMERIC_t,
						LC_TIME_Cat = LC_TIME_t,
						LC_ADDRESS_Cat = LC_ADDRESS_t,
						LC_IDENTIFICATION_Cat = LC_IDENTIFICATION_t,
						LC_MEASUREMENT_Cat = LC_MEASUREMENT_t,
						LC_NAME_Cat = LC_NAME_t,
						LC_PAPER_Cat = LC_PAPER_t,
						LC_TELEPHONE_Cat = LC_TELEPHONE_t
					};

					/**
					 * This object is a parser dispatch table.
					 *
					 * @param Parent The parent Locale object.
					 *
					 * @param Fp The File object to parse from.
					 */
					typedef Token_e (*LcParser)(Locale & Parent, File * Fp);
					struct Dispatch {
						/**
						 * When you find this string.
						 */
						const char *	LookFor;

						/**
						 * Call this method if it is not nullptr.
						 */
						LcParser			ParserPtr;

						/**
						 * Return this token.
						 * When ParserPtr is nullptr.
						 */
						Token_e				Token;
					};

					/**
					 * @struct USet StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * A set or range of characters, by unicode value.
					 *
					 * For a single value, only Left is used, Right will be zero (0).
					 */
					struct USet
						: public instance<USet> {
						char32_t			Left;
						char32_t			Right;
					};

					/**
					 * @class LcBase StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * Base class for LC categories.
					 */
					class LcBase
						: public instance<LcBase> {

						public:

							/**
							 * LcBase - Constructor.
							 *
							 * @param ParentObject The parent Locale object.
							 *
							 * @param Cat The name of the catagory (LC_CTYPE, LC_...)
							 */
							LcBase(Locale & ParentObject, LcCategory_e Cat);

							/**
							 * LcBase - Destructor.
							 */
							~LcBase();

							/**
							 * Print an entity.
							 *
							 * @enum Fp The File handle to write to.
							 */
							virtual bool		Print(File * Fp) = 0;

							/**
							 * This object category.
							 */
							LcCategory_e		Category;

							/**
							 * Parent Locale object.
							 */
							Locale			&		Parent;

							/**
							 * Determine if ToTest is in Set.
							 *
							 * @param ToTest the character to test.
							 *
							 * @return true when ToTest is in Set.
							 */
							bool	InSet(const std::vector<USet> & Set,
							              const char * ToTest) const;

							/**
							 * Determine if ToTest is in Set.
							 *
							 * @param ToTest the character to test.
							 *
							 * @return true when ToTest is in Set.
							 */
							bool	InSet(const std::vector<USet> & Set,
							              const char16_t * ToTest) const;

							/**
							 * Determine if ToTest is in Set.
							 *
							 * @param ToTest the character to test.
							 *
							 * @return true when ToTest is in Set.
							 */
							bool	InSet(const std::vector<USet> & Set,
							              const char32_t * ToTest) const;

							/**
							 * Determine if ToTest is in Set.
							 *
							 * @param ToTest the character to test.
							 *
							 * @return true when ToTest is in Set.
							 */
							bool	InSet(const std::vector<USet> & Set,
							              const wchar_t * ToTest) const;

					};

					/**
					 * @class Lc_Ctype StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_CTYPE
					 */
					class Lc_Ctype
						:	public LcBase {

						public:

							/**
							 * Lc_CType - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Ctype(Locale & Parent);

							/**
							 * Lc_CType - Destructor.
							 */
							~Lc_Ctype();

							/**
							 * Parse an CTYPE entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_CTYPE_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an upper case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an upper case character.
							 */
							bool	IsUpper(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an upper case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an upper case character.
							 */
							bool	IsUpper(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an upper case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an upper case character.
							 */
							bool	IsUpper(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an upper case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an upper case character.
							 */
							bool	IsUpper(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an lower case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an lower case character.
							 */
							bool	IsLower(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an lower case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an lower case character.
							 */
							bool	IsLower(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an lower case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an lower case character.
							 */
							bool	IsLower(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an lower case character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an lower case character.
							 */
							bool	IsLower(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an alpha character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an alpha character.
							 */
							bool	IsAlpha(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an alpha character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an alpha character.
							 */
							bool	IsAlpha(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an alpha character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an alpha character.
							 */
							bool	IsAlpha(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an alpha character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an alpha character.
							 */
							bool	IsAlpha(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an digit character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an digit character.
							 */
							bool	IsDigit(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an digit character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an digit character.
							 */
							bool	IsDigit(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an digit character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an digit character.
							 */
							bool	IsDigit(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an digit character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an digit character.
							 */
							bool	IsDigit(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an space character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an space character.
							 */
							bool	IsSpace(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an space character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an space character.
							 */
							bool	IsSpace(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an space character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an space character.
							 */
							bool	IsSpace(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an space character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an space character.
							 */
							bool	IsSpace(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an control (cntrl) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an control (cntrl) character.
							 */
							bool	IsCntrl(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an control (cntrl) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an control (cntrl) character.
							 */
							bool	IsCntrl(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an control (cntrl) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an control (cntrl) character.
							 */
							bool	IsCntrl(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an control (cntrl) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an control (cntrl) character.
							 */
							bool	IsCntrl(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an punctuation (punct) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an punctuation
							 * (punct) character.
							 */
							bool	IsPunct(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an punctuation (punct) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an punctuation
							 * (punct) character.
							 */
							bool	IsPunct(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an punctuation (punct) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an punctuation
							 * (punct) character.
							 */
							bool	IsPunct(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an punctuation (punct) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an punctuation
							 * (punct) character.
							 */
							bool	IsPunct(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (graph) character.
							 * Not including space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (graph) character.
							 */
							bool	IsGraph(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (graph) character.
							 * Not including space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (graph) character.
							 */
							bool	IsGraph(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (graph) character.
							 * Not including space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (graph) character.
							 */
							bool	IsGraph(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (graph) character.
							 * Not including space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (graph) character.
							 */
							bool	IsGraph(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (print) character.
							 * Does include space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (print) character including space characters.
							 */
							bool	IsPrint(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (print) character.
							 * Does include space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (print) character including space characters.
							 */
							bool	IsPrint(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (print) character.
							 * Does include space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (print) character including space characters.
							 */
							bool	IsPrint(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is an printable (print) character.
							 * Does include space characters.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an printable
							 * (print) character including space characters.
							 */
							bool	IsPrint(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a hexadecimal (xdigit) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an hexadecimal
							 * (xdigit) character.
							 */
							bool	IsXDigit(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a hexadecimal (xdigit) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an hexadecimal
							 * (xdigit) character.
							 */
							bool	IsXDigit(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a hexadecimal (xdigit) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an hexadecimal
							 * (xdigit) character.
							 */
							bool	IsXDigit(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a hexadecimal (xdigit) character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an hexadecimal
							 * (xdigit) character.
							 */
							bool	IsXDigit(const wchar_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a blank character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an blank character.
							 */
							bool	IsBlank(const char * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a blank character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an blank character.
							 */
							bool	IsBlank(const char16_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a blank character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an blank character.
							 */
							bool	IsBlank(const char32_t * ToTest) const;

							/**
							 * Determine if the character (which might be
							 * multi-character-unit), is a blank character.
							 *
							 * @param ToTest The start of the character to test.
							 *
							 * @return true when ToTest is an blank character.
							 */
							bool	IsBlank(const wchar_t * ToTest) const;

							/**
							 * Determine if the string is a locale charclass name.
							 *
							 * @param ToTest The start of the string to test.
							 * In the locale file, all class names are 8-bit strings.
							 *
							 * @return true when ToTest is a locale charclass name.
							 */
							bool	IsCharClass(const char * ToTest) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to an upper case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 * The results are from StringCache, and must be freed
							 * with
							 * @note
							 * When ToConvert is not a lower case charecter, this
							 * method returns the original character.
							 *
							 * @note
							 * This method does not convert the character in place.
							 * It returns the results, which may be the same value.
							 */
							std::shared_ptr<char>	ToUpper(const char * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to an upper case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not a lower case charecter, this
							 * method returns the original character.
							 */
							std::shared_ptr<char16_t>	ToUpper(const char16_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to an upper case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not a lower case charecter, this
							 * method returns the original character.
							 */
							std::shared_ptr<char32_t> ToUpper(const char32_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to an upper case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not a lower case charecter, this
							 * method returns the original character.
							 */
							std::shared_ptr<wchar_t> ToUpper(const wchar_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a lower case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not an upper case charecter, this
							 * method returns the original character.
							 */
							char	* ToLower(const char * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a lower case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not an upper case charecter, this
							 * method returns the original character.
							 */
							char16_t	* ToLower(const char16_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a lower case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not an upper case charecter, this
							 * method returns the original character.
							 */
							char32_t	* ToLower(const char32_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a lower case value.
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * When ToConvert is not an upper case charecter, this
							 * method returns the original character.
							 */
							wchar_t	* ToLower(const wchar_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a title character
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * May return the same character, whenToConvert
							 * is not convertable, or when it is already a title
							 * character.
							 */
							char	* MapToTitle(const char * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a title character
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * May return the same character, whenToConvert
							 * is not convertable, or when it is already a title character.
							 */
							char16_t	* MapToTitle(const char16_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a title character
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * May return the same character, whenToConvert
							 * is not convertable, or when it is already a title
							 * character.
							 */
							char32_t	* MapToTitle(const char32_t * ToConvert) const;

							/**
							 * Convert a character (which might be multi-character-unit)
							 * character to a title character
							 *
							 * @param ToConvert Pointer to the character to convert.
							 *
							 * @return A pointer to the converted staring.
							 *
							 * @note
							 * May return the same character, whenToConvert
							 * is not convertable, or when it is already a title
							 * character.
							 */
							wchar_t	* MapToTitle(const wchar_t * ToConvert) const;

							/**
							 * Check if ToTest is a character in class ClassName.
							 * When ToTest is nullptr, then tests if ClassName
							 * exists.
							 *
							 * @param ClassName The class name to check.
							 * The locale file always is in UTF-8, so the class name
							 * is always an 8-bit string.
							 *
							 * @param ToTest The character to check if it in ClassName.
							 * Or nullptr to test if ClassName exists.
							 *
							 * @return true when ClassName exists and ToTest is in the
							 * set of ClassName. When ToTest is nullptr, returns
							 * true when ClassName exits.
							 */
							bool	IsInClass(const char * ClassName,
							                  const char * ToTest) const;

							/**
							 * Check if ToTest is a character in class ClassName.
							 * When ToTest is nullptr, then tests if ClassName
							 * exists.
							 *
							 * @param ClassName The class name to check.
							 * The locale file always is in UTF-8, so the class name
							 * is always an 8-bit string.
							 *
							 * @param ToTest The character to check if it in ClassName.
							 * Or nullptr to test if ClassName exists.
							 *
							 * @return true when ClassName exists and ToTest is in the
							 * set of ClassName. When ToTest is nullptr, returns
							 * true when ClassName exits.
							 */
							bool	IsInClass(const char * ClassName,
							                  const char16_t * ToTest) const;

							/**
							 * Check if ToTest is a character in class ClassName.
							 * When ToTest is nullptr, then tests if ClassName
							 * exists.
							 *
							 * @param ClassName The class name to check.
							 * The locale file always is in UTF-8, so the class name
							 * is always an 8-bit string.
							 *
							 * @param ToTest The character to check if it in ClassName.
							 * Or nullptr to test if ClassName exists.
							 *
							 * @return true when ClassName exists and ToTest is in the
							 * set of ClassName. When ToTest is nullptr, returns
							 * true when ClassName exits.
							 */
							bool	IsInClass(const char * ClassName,
							                  const char32_t * ToTest) const;

							/**
							 * Check if ToTest is a character in class ClassName.
							 * When ToTest is nullptr, then tests if ClassName
							 * exists.
							 *
							 * @param ClassName The class name to check.
							 * The locale file always is in UTF-8, so the class name
							 * is always an 8-bit string.
							 *
							 * @param ToTest The character to check if it in ClassName.
							 * Or nullptr to test if ClassName exists.
							 *
							 * @return true when ClassName exists and ToTest is in the
							 * set of ClassName. When ToTest is nullptr, returns
							 * true when ClassName exits.
							 */
							bool	IsInClass(const char * ClassName,
							                  const wchar_t * ToTest) const;


							/**
							 * Check to see if a character conversion table named
							 * ConvTable exists.
							 *
							 * @param ConvTable The name of the conversion table.
							 * The locale file always is in UTF-8, so the conversion
							 * table name is always an 8-bit string.
							 *
							 * @return true when ConvTable exists
							 */
							bool	IsCharConv(const char * ConvTable) const;

							bool	IsOutDigit(const char * ToTest) const;
							bool	IsOutDigit(const char16_t * ToTest) const;
							bool	IsOutDigit(const char32_t * ToTest) const;
							bool	IsOutDigit(const wchar_t * ToTest) const;

							bool	IsMapToInPunct(const char * ToTest) const;
							bool	IsMapToInPunct(const char16_t * ToTest) const;
							bool	IsMapToInPunct(const char32_t * ToTest) const;
							bool	IsMapToInPunct(const wchar_t * ToTest) const;

							bool	IsMapToOutPunct(const char * ToTest) const;
							bool	IsMapToOutPunct(const char16_t * ToTest) const;
							bool	IsMapToOutPunct(const char32_t * ToTest) const;
							bool	IsMapToOutPunct(const wchar_t * ToTest) const;

							bool	IsTransLit(const char * ToTest) const;
							bool	IsTransLit(const char16_t * ToTest) const;
							bool	IsTransLit(const char32_t * ToTest) const;
							bool	IsTransLit(const wchar_t * ToTest) const;

							bool	IsDefaultMissing(const char * ToTest) const;
							bool	IsDefaultMissing(const char16_t * ToTest) const;
							bool	IsDefaultMissing(const char32_t * ToTest) const;
							bool	IsDefaultMissing(const wchar_t * ToTest) const;

							/**
							 * Followed by a list of uppercase letters.
							 * The letters A through Z are included automatically.
							 * Characters also specified as cntrl, digit, punct, or
							 * space are not allowed.
							 */
							std::vector<USet>	UpperValues;

							/**
							 * Followed by a list of lowercase letters.
							 * The letters a through z are included automatically.
							 * Characters also specified as cntrl, digit, punct, or
							 * space are not allowed.
							 */
							std::vector<USet>	LowerValues;

							/**
							 * Followed by a list of letters.
							 * All character specified as either upper or lower are
							 * automatically included.
							 * Characters also specified as cntrl, digit, punct, or space
							 * are not allowed.
							 */
							std::vector<USet>	AlphaValues;

							/**
							 * Followed by the characters classified as numeric digits.
							 * Only the digits 0 through 9 are allowed.
							 * They are included by default in this class.
							 */
							std::vector<USet>	DigitValues;

							/**
							 * Followed by a list of characters defined as white-space
							 * characters. Characters also specified as upper, lower,
							 * alpha, digit, graph, or xdigit are not allowed.
							 * The characters <space>, <form-feed>, <newline>,
							 * <carriage-return>, <tab>,  and  <vertical-tab> are
							 * automatically included.
							 */
							std::vector<USet>	SpaceValues;

							/**
							 * Followed by a list of control characters.
							 * Characters also specified as upper, lower, alpha, digit,
							 * punct, graph, print, or xdigit are not allowed.
							 */
							std::vector<USet>	CntrlValues;

							/**
							 * Followed by a list of punctuation characters.
							 * Characters also specified as upper, lower, alpha, digit,
							 * cntrl, xdigit, or the <space> character are not allowed.
							 */
							std::vector<USet>	PunctValues;

							/**
							 * Followed by a list of printable characters, not including
							 * the <space> character. The characters defined as upper,
							 * lower, alpha, digit, xdigit, and punct are automatically
							 * included. Characters also specified as cntrl are not allowed.
							 */
							std::vector<USet>	GraphValues;

							/**
							 * Followed by a list of printable characters, including the
							 * <space> character. The characters defined as upper, lower,
							 * alpha, digit, xdigit, punct, and the <space> character are
							 * automatically included.
							 * Characters also specified as cntrl are not allowed.
							 */
							std::vector<USet>	PrintValues;

							/**
							 * Followed by a list of characters classified as hexadecimal
							 * digits. The decimal digits must be included followed by one
							 * or more set of six characters in ascending order. The
							 * following characters are included by default: 0 through 9,
							 * a through f, A through F.
							 */
							std::vector<USet>	XDigitValues;

							/**
							 * Followed by a list of characters classified as blank.
							 * The characters <space> and <tab> are automatically included.
							 */
							std::vector<USet>	BlankValues;

							/**
							 * Followed by a list  of locale-specific character class names
							which are then to be defined in the locale.
							 */
							std::vector<const char *>	CharClassValues;

							/**
							 * Followed by a list of mappings from lowercase to uppercase
							 * letters. Each mapping is a pair of a lowercase and an
							 * uppercase letter separated with a , and enclosed in
							 * parentheses.
							 */
							std::vector<USet>	ToUpperValues;

							/**
							 * Followed by a list of mappings from uppercase to lowercase
							 * letters. If the keyword tolower is not present, the reverse
							 * of the toupper list is used.
							 */
							std::vector<USet>	ToLowerValues;

							/**
							 * Followed by a list of mapping pairs of characters and
							 * letters to be used in titles (headings).
							 */
							std::vector<USet>	MapToTitleValues;

							/**
							 * Followed by a locale-specific character class definition,
							 * starting with the class name followed by the characters
							 * belonging to the class.
							 */
							std::map<const char *, std::vector<USet *>*>	ClassValues;

							/**
							 * Followed by a list of locale-specific character mapping
							 * names which are later defined in the locale.
							 */
							std::vector<const char *>	CharConvValues;

							/**
							 * Followed by a list of alternate output digits for the
							 * locale.
							 */
							std::vector<char32_t>	OutDigitValues;

							/**
							 * Followed by a list of mapping pairs of alternate digits and
							 * separators for input digits for the locale
							 */
							std::vector<USet>	MapToInPunctValues;

							/**
							 * Followed by a list of mapping pairs of alternate separators
							 * for output for the locale.
							 */
							std::vector<USet>	MapToOutPunctValues;

							/**
							 * A transliteration rule consist of a character to be
							 * transliterated followed by a list of transliteration targets
							 * separated by semicolons. The first target which can be
							 * presented in the target character set is used, if none of
							 * them can be used the default_missing character will be used
							 * instead.
							 */
							std::map<const char32_t, char32_t *>	TransLitValues;

							/**
							 * In the transliteration rules section defines the default
							 * character to be used for transliteration where none of the
							 * targets cannot be presented in the target character set.
							 */
							std::vector<char32_t>	DefaultMissingValues;

					};

					/**
					 * @class Lc_Collate StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_COLLATE
					 */
					class Lc_Collate
						:	public LcBase {

						public:
							/**
							 * Lc_Collate - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Collate(Locale & Parent);

							/**
							 * Lc_Collate - Destructor.
							 */
							~Lc_Collate();

							/**
							 * Parse a LC_COLLATE entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_COLLATE_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);

					};

					/**
					 * @class Lc_Messages StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_MESSAGES
					 */
					class Lc_Messages
						:	public LcBase {

						public:
							/**
							 * Lc_Messages - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Messages(Locale & Parent);

							/**
							 * Lc_Messages - Destructor.
							 */
							~Lc_Messages();

							/**
							 * Parse a LC_MESSAGES entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_MESSAGES_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Monetary StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_MONETARY
					 */
					class Lc_Monetary
						:	public LcBase {

						public:
							/**
							 * Lc_Monetary - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Monetary(Locale & Parent);

							/**
							 * Lc_Monetary - Destructor.
							 */
							~Lc_Monetary();

							/**
							 * Parse a LC_MONETARY entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_MONETARY_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Numeric StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_NUMERIC
					 */
					class Lc_Numeric
						:	public LcBase {

						public:
							/**
							 * Lc_Numeric - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Numeric(Locale & Parent);

							/**
							 * Lc_Numeric - Destructor.
							 */
							~Lc_Numeric();

							/**
							 * Parse a LC_NUMERIC entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_NUMERIC_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Time StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_TIME
					 */
					class Lc_Time
						:	public LcBase {

						public:
							/**
							 * Lc_Time - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Time(Locale & Parent);

							/**
							 * Lc_Time - Destructor.
							 */
							~Lc_Time();

							/**
							 * Parse a LC_TIME entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_TIME_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class LC_ADDRESS StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_ADDRESS
					 */
					class Lc_Address
						:	public LcBase {
						public:

							/**
							 * Lc_Address - Default Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Address(Locale & ParentObj);

							/**
							 * Lc_Address - Destructor.
							 */
							~Lc_Address();

							/**
							 * PostalFmt.
							 *
							 * @note
							 * This is a get and set method. Supply nullptr to get it.
							 * Supply a pointer to a string to set it.
							 *
							 * LC_ADDRESS: postal_fmt
							 * Followed by a string containing field descriptors that
							 * define	the format used for postal addresses in the locale.
							 * The following field descriptors are recognized:
							 *
							 * -%n	Person's name, possibly constructed with the LC_NAME
							 * name_fmt keyword (since glibc 2.24).
							 *
							 * -%a Care of person, or organization.
							 *
							 * -%f Firm name.
							 *
							 * -%d Department name.
							 *
							 * -%b Building name.
							 *
							 * -%s Street or block (e.g., Japanese) name.
							 *
							 * -%h House number or designation.
							 *
							 * -%N Insert an end-of-line if the previous descriptor's
							 * value was not an empty string; otherwise ignore.
							 *
							 * -%t Insert a space if the previous descriptor's value was
							 * not an	empty string; otherwise ignore.
							 *
							 * -%r Room number, door designation.
							 *
							 * -%e Floor number.
							 *
							 * -%C Country designation, from the country_post keyword.
							 *
							 * -%l Local township within town or city.
							 *
							 * -%z Zip number, postal code.
							 *
							 * -%T Town, city.
							 *
							 * -%S State, province, or prefecture.
							 *
							 * -%c Country, as taken from data record.
							 *
							 * Each field descriptor may have an 'R' after the '%' to
							 * specify that the information is taken from a Romanized
							 * version string of the entity.
							 *
							 * @param Which Which LC_ADDRESS field to get or set.
							 *
							 * @param Value A caller supplied pointer that will
							 * be updated with a pointer to the value. Caller
							 * MUST initialize Value to nullptr get it. When Value is
							 * non-nullptr, then PostalFmt will be set to Value.
							 * If Value or what it points to are the same as the
							 * existing value, nothing is done.
							 *
							 * @return true if PostalFmt was available. Returns false
							 * if PostalFmt was not set prior to the call.
							 *
							 * When true, Value will be updated to point to the
							 * value.
							 */
							bool			PostalFmt(Token_e Which,
							                          const ROString *& Value);

							/**
							 * Parse a LC_ADDRESS entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_ADDRESS_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);

							/**
							 * Print an entity.
							 *
							 * @enum Fp The File handle to write to.
							 */
							virtual bool		Print(File * Fp);

							const ROString	*	PostalFmtValue;
							const ROString	*	CountryNameValue;
							const ROString	*	CountryPostValue;
							const ROString	*	CountryAb2Value;
							const ROString	*	CountryAb3Value;
							const ROString	*	CountryNumValue;
							const ROString	*	CountryCarValue;
							const ROString	*	CountryIsbnValue;
							const ROString	*	LangNameValue;
							const ROString	*	LangAbValue;
							const ROString	*	LangTermValue;
							const ROString	*	LangLibValue;

					};

					/**
					 * @class Lc_Identification StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_IDENTIFICATION
					 */
					class Lc_Identification
						:	public LcBase {

						public:
							/**
							 * Lc_Identification - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Identification(Locale & Parent);

							/**
							 * Lc_Identification - Destructor.
							 */
							~Lc_Identification();

							/**
							 * Parse a LC_IDENTIFICATION entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_IDENTIFICATION_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);

					};

					/**
					 * @class Lc_Measurement StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_MEASUREMENT
					 */
					class Lc_Measurement
						:	public LcBase {

						public:
							/**
							 * Lc_Measurement - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Measurement(Locale & Parent);

							/**
							 * Lc_Measurement - Destructor.
							 */
							~Lc_Measurement();

							/**
							 * Parse a LC_MEASUREMENT entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_MEASUREMENT_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Name StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_NAME
					 */
					class Lc_Name
						:	public LcBase {

						public:
							/**
							 * Lc_Name - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Name(Locale & Parent);

							/**
							 * Lc_Name - Destructor.
							 */
							~Lc_Name();

							/**
							 * Parse a LC_NAME entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_NAME_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Paper StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_PAPER
					 */
					class Lc_Paper
						:	public LcBase {

						public:
							/**
							 * Lc_Paper - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Paper(Locale & Parent);

							/**
							 * Lc_Paper - Destructor.
							 */
							~Lc_Paper();

							/**
							 * Parse a LC_PAPER entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_PAPER_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					/**
					 * @class Lc_Telephone StringLocale.hpp "<SaS/String/StringLocale.hpp>"
					 * An object and methods for LC_TELEPHONE
					 */
					class Lc_Telephone
						:	public LcBase {

						public:
							/**
							 * Lc_Telephone - Constructor.
							 *
							 * @param Parent The parent Locale object.
							 */
							Lc_Telephone(Locale & Parent);

							/**
							 * Lc_Telephone - Destructor.
							 */
							~Lc_Telephone();

							/**
							 * Parse a LC_TELEPHONE entity.
							 *
							 * @param Parent The parent Locale object.
							 *
							 * @param Fp The File handle to read from.
							 *
							 * @return LC_TELEPHONE_t on success.
							 */
							static Token_e		Parse(Locale & Parent, File * Fp);
					};

					Lc_Address	*	LC_ADDRESS_Value;

				private:

					struct CharMapFile;	// Forward ref.

					/**
					 * Parse a string and return the token id for the match.
					 * If Table has a parser method, it is called and the
					 * result Token_e will be returned.
					 *
					 * @param Table The StringDispatch table to use.
					 *
					 * @return The Table.Token matched as the offset into Table.
					 * Or (-1) if not found.
					 */
					Token_e		_Parse(File * Fp, const Dispatch * Table);

					/**
					 * The comment character.
					 */
					char		_CommentChar;

					/**
					 * The escape character.
					 */
					char		_EscapeChar;

					/**
					 * Parse a locale(5) file.
					 *
					 * @return true when the locale file was parsed without errors.
					 */
					bool			_ParseLocale();

					/**
					 * Parse a charmap(5) file.
					 *
					 * @param Map The struct CharMapFile object to parse into.
					 *
					 * @return true when the charmap file was parsed
					 * without errors and Map updated.
					 */
					bool			_ParseCharmap(CharMapFile & Map);

					/**
					 * Parse next quoted string.
					 * The name is a bit of a lie. It might not be quoted.
					 *
					 * It will find the start of the first character after
					 * the first quote, or the first character if no quote.
					 *
					 * It does not processes <Uxxxx> values into their value.
					 *
					 * Skips comments.
					 *
					 * @param[out] LenOut The length of the string, may be zero.
					 * The length will be the lenght of characters inside the quotes.
					 * When no quotes it will be up to the last non-blank character.
					 *
					 * @param Fp  The File object to parse from.
					 *
					 * @return the start point of the first character
					 * inside the string. Or nullptr when no string is
					 * found before a newline.
					 */
					const char	*	_ParseQuotedString(size_t & LenOut,
					                                   File * Fp);

					/**
					 * Parse 'escape_char'
					 *
					 * @param Parent The parent Locale object.
					 *
					 * @param Fp The File object to read from.
					 *
					 * @param Fp  The File object to parse from.
					 *
					 * @return EscapeChar_t on success.
					 */
					static Token_e	_ParseEscapeChar(Locale & Parent,
					                                 File * Fp);

					/**
					 * Parse 'comment_char'
					 *
					 * @param Parent The parent Locale object.
					 *
					 * @param Fp The File object to read from.
					 *
					 * @return CommentChar_t on success
					 */
					static Token_e	_ParseCommentChar(Locale & Parent, File * Fp);

					/**
					 * Skip to the end of the line + 1.
					 *
					 * @param Fp  The File object to parse from.
					 */
					void		_SkipPastEol(File * Fp);

					/**
					 * Parse a unicode hex value <Uxxxx>
					 *
					 * @param Val The start of the value to convert.
					 *
					 * @param Fp  The File object to parse from.
					 *
					 * @return The code, or zero when invalid.
					 */
					char32_t	_ParseCode(const char * Val,
					                       File * Fp);

					/**
					 * The locale file handle.
					 */
					File		*		_LocaleFp;

					/**
					 * The charmap file handle.
					 */
					File		*		_CharmapFp;

				private:

					/**
					 * A single character mapping.
					 */
					struct CharMap
						: public instance<CharMap> {

						/**
						 * CharMap - Default Constructor.
						 */
						CharMap();

						/**
						 * CharMap - Destructor.
						 */
						~CharMap();

						/**
						 * The symbolic name. From StringCache::Add().
						 */
						const char	*	SymbolicName;

						/**
						 * Unique runtime mapping ID, or handle.
						 */
						CharMapID_t	CharMapID;

						/**
						 * Array of octets, not zero terminated.
						 */
						int8_t	*	Octets;

						/**
						 * Number of valid Octets.
						 */
						size_t		OctetsLen;

						/**
						 * Any comment - StringCache.
						 */
						char	*	Comment;

						/**
						 * Width: Some, (like control characters) have a width of zero.
						 */
						uint8_t	Width;
					};

					/**
					 * A Charset definition.
					 */
					struct CharMapFile
						: public instance<CharMapFile> {

						/**
						 * CharMapFile - Default Constructor.
						 */
						CharMapFile();

						/**
						 * CharMapFile - Destructor.
						 */
						~CharMapFile();

						/**
						 * Runtime unique ID for this mapping.
						 */
						Charset_t			ID;

						/**
						 * Name of the map.
						 */
						char	*	Name;

						/**
						 * Optional comment.
						 */
						char	*	Comment;

						/**
						 * Minimum number of octets in this charset.
						 */
						uint8_t				MinLength;

						/**
						 * Maximum number of octets in this charset.
						 */
						uint8_t				MaxLength;

						/**
						 * The symbol list is ordered.
						 * The maps below are indexes.
						 *
						 * Here is the ordered list.
						 */
						std::vector<CharMap *>	SymbolList;

						/**
						 * A map of symbolic name, to mapping definition.
						 *
						 * <symbolic-name, Octets>
						 *
						 * To get the ID for a symbolic name:
						 *
						 * It = MapBySymbolicName.find(sym-name);
						 * Id = (*It).CharMapID;
						 *
						 * @note
						 *
						 */
						std::map<const char *, CharMap *, CStringCompareOperator>	MapBySymbolicName;

						/**
						 * A map of a character ID, to mapping definition.
						 *
						 * <ID, Octets>
						 */
						std::map<CharMapID_t, CharMap *>	MapByID;

						/**
						 * Update the Map with the provided width.
						 *
						 * @param FirstSymbol The first, or only symbol to update.
						 *
						 * @param CWidth The character width of the character.
						 *
						 * @param Second When non-nullptr, the last symbol name
						 * to set the width of.
						 */
						void UpdateWidth(const char * FirstSymbol,
						                 uint8_t CWidth,
						                 const char * LastSymbol = nullptr);

					};

					/**
					 * A Locale definition.
					 */
					struct Charset
						: public instance<Charset> {

						const char	*	Name;
						Locale_t			ID;
						Charset_t			CharsetID;
						/** @todo MORE*/
					};

					/**
					 * Charset cache - Charset name to Charset
					 */
					static std::map<const char *, Charset *>	_CharsetNameCache;

					/**
					 * Charset cache - Charset ID to Charset
					 */
					static std::map<Charset_t, Charset *>	_CharsetIdCache;

					/**
					 * Locale cache - Locale name to Locale.
					 */
					static std::map<const char *, Locale *>	_LocaleNameCache;

					/**
					 * Locale cache - Locale ID to Locale.
					 */
					static std::map<Locale_t, Locale *>	_LocaleIdCache;

					// LC_ADDRESS
					static Token_e	_ParsePostalFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryName(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryPost(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryAb2(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryAb3(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryNum(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryCar(Locale & Parent, File * Fp);
					static Token_e	_ParseCountryIsbn(Locale & Parent, File * Fp);
					static Token_e	_ParseLangName(Locale & Parent, File * Fp);
					static Token_e	_ParseLangAb(Locale & Parent, File * Fp);
					static Token_e	_ParseLangTerm(Locale & Parent, File * Fp);
					static Token_e	_ParseLangLib(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_ADDRESS(Locale & Parent, File * Fp);

					// LC_CTYPE
					static Token_e	_ParseUpper(Locale & Parent, File * Fp);
					static Token_e	_ParseLower(Locale & Parent, File * Fp);
					static Token_e	_ParseAlpha(Locale & Parent, File * Fp);
					static Token_e	_ParseDigit(Locale & Parent, File * Fp);
					static Token_e	_ParseSpace(Locale & Parent, File * Fp);
					static Token_e	_ParseCntrl(Locale & Parent, File * Fp);
					static Token_e	_ParsePunct(Locale & Parent, File * Fp);
					static Token_e	_ParseGraph(Locale & Parent, File * Fp);
					static Token_e	_ParsePrint(Locale & Parent, File * Fp);
					static Token_e	_ParseXDigit(Locale & Parent, File * Fp);
					static Token_e	_ParseBlank(Locale & Parent, File * Fp);
					static Token_e	_ParseCharClass(Locale & Parent, File * Fp);
					static Token_e	_ParseToUpper(Locale & Parent, File * Fp);
					static Token_e	_ParseToLower(Locale & Parent, File * Fp);
					static Token_e	_ParseMapToTitle(Locale & Parent, File * Fp);
					static Token_e	_ParseClass(Locale & Parent, File * Fp);
					static Token_e	_ParseCharConv(Locale & Parent, File * Fp);
					static Token_e	_ParseOutDigit(Locale & Parent, File * Fp);
					static Token_e	_ParseMapToInPunct(Locale & Parent, File * Fp);
					static Token_e	_ParseMapToOutPunct(Locale & Parent, File * Fp);
					static Token_e	_ParseTranslitStart(Locale & Parent, File * Fp);
					static Token_e	_ParseInclude(Locale & Parent, File * Fp);
					static Token_e	_ParseDefaultMissing(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_CTYPE(Locale & Parent, File * Fp);

					// LC_COLLATE
					static Token_e	_ParseCollWeightMax(Locale & Parent, File * Fp);
					static Token_e	_ParseCollatingElement(Locale & Parent, File * Fp);
					static Token_e	_ParseCollatingSymbol(Locale & Parent, File * Fp);
					static Token_e	_ParseDefine(Locale & Parent, File * Fp);
					static Token_e	_ParseOrderEnd(Locale & Parent, File * Fp);
					static Token_e	_ParseOrderStart(Locale & Parent, File * Fp);
					static Token_e	_ParseReOrderAfter(Locale & Parent, File * Fp);
					static Token_e	_ParseReOrderEnd(Locale & Parent, File * Fp);
					static Token_e	_ParseReOrderSectionsAfter(Locale & Parent, File * Fp);
					static Token_e	_ParseReOrderSectionsEnd(Locale & Parent, File * Fp);
					static Token_e	_ParseScript(Locale & Parent, File * Fp);
					static Token_e	_ParseSymbolEquivalence(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_COLLATE(Locale & Parent, File * Fp);

					// LC_IDENTIFICATION
					static Token_e	_ParseTitle(Locale & Parent, File * Fp);
					static Token_e	_ParseAddress(Locale & Parent, File * Fp);
					static Token_e	_ParseContect(Locale & Parent, File * Fp);
					static Token_e	_ParseEmail(Locale & Parent, File * Fp);
					static Token_e	_ParseTel(Locale & Parent, File * Fp);
					static Token_e	_ParseFaxLanguage(Locale & Parent, File * Fp);
					static Token_e	_ParseTerritory(Locale & Parent, File * Fp);
					static Token_e	_ParseAudience(Locale & Parent, File * Fp);
					static Token_e	_ParseApplication(Locale & Parent, File * Fp);
					static Token_e	_ParseAbbreviation(Locale & Parent, File * Fp);
					static Token_e	_ParseRevision(Locale & Parent, File * Fp);
					static Token_e	_ParseDate(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_IDENTIFICATION(Locale & Parent, File * Fp);

					// LC_MESSAGES
					static Token_e	_ParseYesExpr(Locale & Parent, File * Fp);
					static Token_e	_ParseNoExpr(Locale & Parent, File * Fp);
					static Token_e	_ParseYesStr(Locale & Parent, File * Fp);
					static Token_e	_ParseNoStr(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_MESSAGES(Locale & Parent, File * Fp);

					// LC_MEASUREMENT
					static Token_e	_ParseMeasurement(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_MEASUREMENT(Locale & Parent, File * Fp);

					// LC_MONENTARY
					static Token_e	_ParseIntCurrSymbol(Locale & Parent, File * Fp);
					static Token_e	_ParseCurrencySymbol(Locale & Parent, File * Fp);
					static Token_e	_ParseMonDecimalPoint(Locale & Parent, File * Fp);
					static Token_e	_ParseMonThousandsSep(Locale & Parent, File * Fp);
					static Token_e	_ParseMonGrouping(Locale & Parent, File * Fp);
					static Token_e	_ParsePositiveSign(Locale & Parent, File * Fp);
					static Token_e	_ParseNegativeSign(Locale & Parent, File * Fp);
					static Token_e	_ParseIntFracDigits(Locale & Parent, File * Fp);
					static Token_e	_ParseFracDigits(Locale & Parent, File * Fp);
					static Token_e	_ParsePCsPrecedes(Locale & Parent, File * Fp);
					static Token_e	_ParsePSepBySpace(Locale & Parent, File * Fp);
					static Token_e	_ParseNCsPrecedes(Locale & Parent, File * Fp);
					static Token_e	_ParseNSepBySpace(Locale & Parent, File * Fp);
					static Token_e	_ParsePSignPosn(Locale & Parent, File * Fp);
					static Token_e	_ParseNSignPost(Locale & Parent, File * Fp);
					static Token_e	_ParseIntPCsPrecedes(Locale & Parent, File * Fp);
					static Token_e	_ParseIntNCsPrecedes(Locale & Parent, File * Fp);
					static Token_e	_ParseIntPSepBySpace(Locale & Parent, File * Fp);
					static Token_e	_ParseIntNSepBySpace(Locale & Parent, File * Fp);
					static Token_e	_ParseIntPSignPosn(Locale & Parent, File * Fp);
					static Token_e	_ParseIntNSIgnPosn(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_MOENTARY(Locale & Parent, File * Fp);

					// LC_NAME
					static Token_e	_ParseNameFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseNameGen(Locale & Parent, File * Fp);
					static Token_e	_ParseNameMr(Locale & Parent, File * Fp);
					static Token_e	_ParseNameMrs(Locale & Parent, File * Fp);
					static Token_e	_ParseNameMiss(Locale & Parent, File * Fp);
					static Token_e	_ParseNameMs(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_NAME(Locale & Parent, File * Fp);

					// LC_NUMERIC
					static Token_e	_ParseDecimalPoint(Locale & Parent, File * Fp);
					static Token_e	_ParseThousandsSep(Locale & Parent, File * Fp);
					static Token_e	_ParseGrouping(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_NUMERIC(Locale & Parent, File * Fp);

					// LC_PAPER
					static Token_e	_ParseHeight(Locale & Parent, File * Fp);
					static Token_e	_ParseWidth(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_PAPER(Locale & Parent, File * Fp);

					// LC_TELEPHONE
					static Token_e	_ParseTelIntFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseTelDomFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseIntSelect(Locale & Parent, File * Fp);
					static Token_e	_ParseIntPrefix(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_TELEPHONE(Locale & Parent, File * Fp);

					// LC_TIME
					static Token_e	_ParseAbDay(Locale & Parent, File * Fp);
					static Token_e	_ParseDay(Locale & Parent, File * Fp);
					static Token_e	_ParseAbMon(Locale & Parent, File * Fp);
					static Token_e	_ParseMon(Locale & Parent, File * Fp);
					static Token_e	_ParseDTFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseDFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseTFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseAmPm(Locale & Parent, File * Fp);
					static Token_e	_ParseEra(Locale & Parent, File * Fp);
					static Token_e	_ParseEraDFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseEraTFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseEraDTFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseAltDigits(Locale & Parent, File * Fp);
					static Token_e	_ParseWeek(Locale & Parent, File * Fp);
					static Token_e	_ParseFirstWeekday(Locale & Parent, File * Fp);
					static Token_e	_ParseFirstWorkday(Locale & Parent, File * Fp);
					static Token_e	_ParseDateFmt(Locale & Parent, File * Fp);
					static Token_e	_ParseEND_LC_TIME(Locale & Parent, File * Fp);

					/**
					 * The last file ID used. The ID's are runtime generated
					 * based on the load order. As in, the handles are
					 * only runtime unique.
					 */
					static Charset_t			_LastCharMapFileIdUsed;

					/**
					 * The last character ID used. The ID's are runtime generated
					 * based on the load order. As in, the handles are
					 * only runtime unique.
					 */
					static CharMapID_t			_LastCharMapIdUsed;

			};

			/**
			* Determine Token_e the character is uppercase(Locale & Parent, File * Fp).
			*
			* @param TheChar The character to test.
			*
			* @param TheLocal The locale of TheChar. When zero (0),
			* TheChar must be in Current8BitLocale.
			*
			* @return true if TheChar is uppercase.
			*/
			bool			IsUpper(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is uppercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is uppercase.
			 */
			bool			IsUpper(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is lowercase.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is lowercase.
			 */
			bool			IsLower(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is alpha.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is alpha.
			 */
			bool			IsAlpha(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is digit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is digit.
			 */
			bool			IsDigit(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is space.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is space.
			 */
			bool			IsSpace(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is cntrl.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is cntrl.
			 */
			bool			IsCntrl(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is punct.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is punct.
			 */
			bool			IsPunct(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is graph.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is graph.
			 */
			bool			IsGraph(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is print.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is print.
			 */
			bool			IsPrint(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(const char * TheChar,
			                         locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is xdigit.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is xdigit.
			 */
			bool			IsXdigit(const wchar_t * TheChar,
			                         locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(char TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(const char * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(char16_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(char16_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(char32_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(char32_t * TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(wchar_t TheChar, locale_t TheLocale = 0);

			/**
			 * Determine if the character is blank.
			 *
			 * @param TheChar The character to test.
			 *
			 * @param TheLocal The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return true if TheChar is blank.
			 */
			bool			IsBlank(const wchar_t * TheChar,
			                        locale_t TheLocale = 0);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString	*	ToTitle(char TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString	*	ToTitle(const char * TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString	*	ToTitle(char16_t TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	ToTitle(const char16_t * TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	ToTitle(char32_t TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			p			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	ToTitle(const char32_t * TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	ToTitle(wchar_t TheChar);

			/**
			 * Convert the character to upper case, if the character
			 * is convertable, and lower case. Else does nothing.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	ToTitle(const wchar_t * TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(char TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(const char * TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(char16_t TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(const char16_t * TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(char32_t TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(const char32_t * TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(wchar_t TheChar);

			/**
			 * Convert the character to outdigit. Some charactersets
			 * use alternate characters (not 0-9).
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutDigit(const wchar_t * TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(char TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(const char * TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			char16_t	InPunct(char16_t TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(const char16_t * TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			char32_t	InPunct(char32_t TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(const char32_t * TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(wchar_t TheChar);

			/**
			 * Convert the character to inpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	InPunct(const wchar_t * TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(char TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(const char * TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(char16_t TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(const char16_t * TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(char32_t TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(const char32_t * TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(wchar_t TheChar);

			/**
			 * Convert the character to outpunct.
			 *
			 * @param TheChar The character to convert.
			 *
			 * @param TheLocale The locale of TheChar. When zero (0),
			 * TheChar must be in Current8BitLocale.
			 *
			 * @return The converted character, or the original if
			 * not convertable.
			 */
			ROString *	OutPunct(const wchar_t * TheChar);

		}
	}
}
#endif //SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRING_LOCALE_HPP_

