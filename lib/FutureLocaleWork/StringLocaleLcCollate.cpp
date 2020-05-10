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

			Locale::Lc_Collate::Lc_Collate(Locale & Parent)
				: LcBase(Parent, LC_COLLATE_Cat)
			{
				/*EMPTY*/

				return;
			}

			Locale::Lc_Collate::~Lc_Collate()
			{
				/*EMPTY*/

				return;
			}

			Locale::Token_e
			Locale::Lc_Collate::Parse(Locale & Parent, File * Fp)
			{
				Token_e					Results = Token_e_UnknownToken_t;

				Dispatch		Tokens[] = {
					{CollWeightMax_s, _ParseCollWeightMax, CollWeightMax_t},
					{CollatingElement_s, _ParseCollatingElement, CollatingElement_t},
					{CollatingSymbol_s, _ParseCollatingSymbol, CollatingSymbol_t},
					{Define_s, _ParseDefine, Define_t},
					{ReOrderAfter_s, _ParseReOrderAfter, ReOrderAfter_t},
					{ReOrderEnd_s, _ParseReOrderEnd, ReOrderEnd_t},
					{ReOrderSectionsAfter_s, _ParseReOrderSectionsAfter, ReOrderSectionsAfter_t},
					{ReOrderSectionsEnd_s, _ParseReOrderSectionsEnd, ReOrderSectionsEnd_t},
					{Script_s, _ParseScript, Script_t},
					{SymbolEquivalence_s, _ParseSymbolEquivalence, SymbolEquivalence_t},
					{OrderStart_s, _ParseOrderStart, OrderStart_t},
					{OrderEnd_s, _ParseOrderEnd, OrderEnd_t},
					{END_LC_COLLATE_s, _ParseEND_LC_COLLATE, END_LC_COLLATE_t},
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

			Locale::Token_e
			Locale::_ParseCollWeightMax(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseCollatingElement(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseCollatingSymbol(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseDefine(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseOrderEnd(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseOrderStart(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseReOrderAfter(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseReOrderEnd(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseReOrderSectionsAfter(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseReOrderSectionsEnd(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseScript(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseSymbolEquivalence(Locale & Parent, File * Fp)
			{
			}

			Locale::Token_e
			Locale::_ParseEND_LC_COLLATE(Locale & Parent, File * Fp)
			{
			}

		}
	}
}
