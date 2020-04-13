//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2015 Software and Services LLC, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO SOFTWARE AND SERVICES LLC.
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
// PROVIDED ON AN "AS IS" BASIS AND SOFTWARE AND SERVICES LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN WILL NOT INFRINGE ANY RIGHTS OR ANY IMPLIED
// WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// THIS SOURCE CODE IS UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//

#include <SaS/String/StringCache.hpp>
#include <SaS/String/StringCompareOperator.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			bool
			CStringCompareOperator::operator()(const char * const One,
			                                   const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char * const One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char32_t * const
			                                  One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const wchar_t * const One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const String * const One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const char16_t * const
			                                  One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const String * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const ROString * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, *Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const char * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const char16_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const char32_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			StringCompareOperator::operator()(const ROString * const
			                                  One,
			                                  const wchar_t * const Two) const
			{
				bool			Results = true;

				if (One == nullptr && Two == nullptr) {
					Results = false;

				} else if (One == nullptr && Two != nullptr) {
					Results = true;

				} else if (One != nullptr && Two == nullptr) {
					Results = false;

				} else if (String::strcmp(*One, Two) < 0) {
					Results = true;
				}

				return (Results);
			}

		}
	}
}
