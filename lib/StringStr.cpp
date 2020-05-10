//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2019 Software and Services LLC, All Rights Reserved.
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
#include <SaS/String/String.hpp>
#include <SaS/String/ROString.hpp>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			String::const_iterator	&
			String::strstr(const char * const LookFor) const
			{
				const_iterator		&	Results = cend();

				if (LookFor != nullptr) {
					size_t			StrLen = Length();
					size_t			LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {

						const_iterator	it = cbegin();

						while (it != cend()) {

							int		Cmp = 0;

							switch (_InputWidth) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Cmp = strncmp(it.str8(), LookFor, LookLen);
									break;

								case Is16Bit_t:
									Cmp = strncmp(it.str16(), LookFor, LookLen);
									break;

								case Is32Bit_t:
									Cmp = strncmp(it.str32(), LookFor, LookLen);
									break;

								case IsWBit_t:
									Cmp = strncmp(it.strW(), LookFor, LookLen);
									break;

									Results = it;
									break;
							}

							if (Cmp == 0) {
								Results = it;
								break;
							}

							it++;
						}
					}
				}

				return (Results);
			}

			String::const_iterator	&
			String::strstr(const char16_t * const LookFor) const
			{
				const_iterator		&		Results = cend();

				if (LookFor != nullptr) {
					size_t			StrLen = Length();
					size_t			LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {

						const_iterator		it = cbegin();

						while (it != cend()) {
							int		Cmp = 0;

							switch (_InputWidth) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Cmp = strncmp(it.str8(), LookFor, LookLen);
									break;

								case Is16Bit_t:
									Cmp = strncmp(it.str16(), LookFor, LookLen);
									break;

								case Is32Bit_t:
									Cmp = strncmp(it.str32(), LookFor, LookLen);
									break;

								case IsWBit_t:
									Cmp = strncmp(it.strW(), LookFor, LookLen);
									break;

									Results = it;
									break;
							}

							if (Cmp == 0) {
								Results = it;
								break;
							}

							it++;
						}
					}
				}

				return (Results);
			}

			String::const_iterator	&
			String::strstr(const char32_t * const LookFor) const
			{
				const_iterator		&		Results = cend();

				if (LookFor != nullptr) {
					size_t			StrLen = Length();
					size_t			LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {

						const_iterator		it = cbegin();

						while (it != cend()) {
							int		Cmp = 0;

							switch (_InputWidth) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Cmp = strncmp(it.str8(), LookFor, LookLen);
									break;

								case Is16Bit_t:
									Cmp = strncmp(it.str16(), LookFor, LookLen);
									break;

								case Is32Bit_t:
									Cmp = strncmp(it.str32(), LookFor, LookLen);
									break;

								case IsWBit_t:
									Cmp = strncmp(it.strW(), LookFor, LookLen);
									break;

									Results = it;
									break;
							}

							if (Cmp == 0) {
								Results = it;
								break;
							}

							it++;
						}
					}
				}

				return (Results);
			}

			String::const_iterator	&
			String::strstr(const wchar_t * const LookFor) const
			{
				const_iterator		&		Results = cend();

				if (LookFor != nullptr) {
					size_t			StrLen = Length();
					size_t			LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {

						const_iterator		it = cbegin();

						while (it != cend()) {
							int		Cmp = 0;

							switch (_InputWidth) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t:
									Cmp = strncmp(it.str8(), LookFor, LookLen);
									break;

								case Is16Bit_t:
									Cmp = strncmp(it.str16(), LookFor, LookLen);
									break;

								case Is32Bit_t:
									Cmp = strncmp(it.str32(), LookFor, LookLen);
									break;

								case IsWBit_t:
									Cmp = strncmp(it.strW(), LookFor, LookLen);
									break;

									Results = it;
									break;
							}

							if (Cmp == 0) {
								Results = it;
								break;
							}

							it++;
						}
					}
				}

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const char * const LookFor)
			{
				const char	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					Results = ::strstr(Str, LookFor);
				}

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const char16_t * const LookFor)
			{
				const char	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char		*	Out = nullptr;

					if (Charset16To8(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const char32_t * const LookFor)
			{
				const char	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char		*	Out = nullptr;

					if (Charset32To8(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const wchar_t * const LookFor)
			{
				const char	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char		*	Out = nullptr;

					if (CharsetWTo8(nullptr,
					                LookFor,
					                nullptr,
					                Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const std::string & LookFor)
			{
				const char	*	Results = strstr(Str, LookFor.c_str());

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const std::u16string & LookFor)
			{
				const char	*	Results = strstr(Str, LookFor.c_str());

				return (Results);
			}


			const char	*
			String::strstr(const char * const Str,
			               const std::u32string & LookFor)
			{
				const char	*	Results = strstr(Str, LookFor.c_str());

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const std::wstring & LookFor)
			{
				const char	*	Results = strstr(Str, LookFor.c_str());

				return (Results);
			}

			const char	*
			String::strstr(const char * const Str,
			               const String & LookFor)
			{
				const char	*	Results = strstr(Str, LookFor.Get8());

				return (Results);
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const char * const LookFor)
			{
				const char16_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char16_t	*	Out = nullptr;

					if (Charset8To16(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const char16_t * const LookFor)
			{
				const char16_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					size_t		StrLen = strlen(Str);
					size_t		LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {
						size_t		Offset = 0;

						for (Offset = 0
						              ; Offset <= (StrLen - LookLen)
						     ; Offset++) {

							if (strncmp(&Str[Offset], LookFor, LookLen) == 0) {
								Results = &Str[Offset];
								break;
							}
						}
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const char32_t * const LookFor)
			{
				const char16_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char16_t	*	Out = nullptr;

					if (Charset32To16(nullptr,
					                  LookFor,
					                  nullptr,
					                  Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const wchar_t * const LookFor)
			{
				const char16_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char16_t	*	Out = nullptr;

					if (CharsetWTo16(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const std::string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const std::u16string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const std::u32string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const std::wstring & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char16_t	*
			String::strstr(const char16_t * const Str,
			               const String & LookFor)
			{
				const char16_t	*	Results = nullptr;

				if (Str != nullptr) {
					Results = strstr(Str, LookFor.Get16());
				}

				return (Results);
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const char * const LookFor)
			{
				const char32_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char32_t	*	Out = nullptr;

					if (Charset8To32(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const char16_t * const LookFor)
			{
				const char32_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char32_t	*	Out = nullptr;

					if (Charset16To32(nullptr,
					                  LookFor,
					                  nullptr,
					                  Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const char32_t * const LookFor)
			{
				const char32_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					size_t		StrLen = strlen(Str);
					size_t		LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {
						size_t		Offset = 0;

						for (Offset = 0
						              ; Offset <= (StrLen - LookLen)
						     ; Offset++) {

							if (strncmp(&Str[Offset], LookFor, LookLen) == 0) {
								Results = &Str[Offset];
								break;
							}
						}
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const wchar_t * const LookFor)
			{
				const char32_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					char32_t	*	Out = nullptr;

					if (CharsetWTo32(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const std::string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const std::u16string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const std::u32string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const std::wstring & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const char32_t	*
			String::strstr(const char32_t * const Str,
			               const String & LookFor)
			{
				const char32_t	*	Results = nullptr;

				if (Str != nullptr) {
					Results = strstr(Str, LookFor.Get32());
				}

				return (Results);
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const char * const LookFor)
			{
				const wchar_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					wchar_t	*	Out = nullptr;

					if (Charset8ToW(nullptr,
					                LookFor,
					                nullptr,
					                Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const char16_t * const LookFor)
			{
				const wchar_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					wchar_t	*	Out = nullptr;

					if (Charset16ToW(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const char32_t * const LookFor)
			{
				const wchar_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					wchar_t	*	Out = nullptr;

					if (Charset32ToW(nullptr,
					                 LookFor,
					                 nullptr,
					                 Out)) {
						Results = strstr(Str, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const wchar_t * const LookFor)
			{
				const wchar_t	*	Results = nullptr;

				if (Str != nullptr && LookFor != nullptr) {
					size_t		StrLen = strlen(Str);
					size_t		LookLen = strlen(LookFor);

					if (StrLen >= LookLen) {
						size_t		Offset = 0;

						for (Offset = 0
						              ; Offset <= (StrLen - LookLen)
						     ; Offset++) {

							if (strncmp(&Str[Offset], LookFor, LookLen) == 0) {
								Results = &Str[Offset];
								break;
							}
						}
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const std::string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const std::u16string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const std::u32string & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const std::wstring & LookFor)
			{
				return (strstr(Str, LookFor.c_str()));
			}

			const wchar_t	*
			String::strstr(const wchar_t * const Str,
			               const String & LookFor)
			{
				return (strstr(Str, LookFor.GetW()));
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const char * const LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0 && LookFor != nullptr) {
					size_t		LookLen = strlen(LookFor);

					while (*It != 0) {
						if (strncmp(It, LookFor, LookLen) == 0) {
							break;
						}
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const char16_t * const LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0 && LookFor != nullptr) {
					size_t		LookLen = strlen(LookFor);

					while (*It != 0) {
						if (strncmp(It, LookFor, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const char32_t * const LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0 && LookFor != nullptr) {
					size_t		LookLen = strlen(LookFor);

					while (*It != 0) {
						if (strncmp(It, LookFor, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const wchar_t * const LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0 && LookFor != nullptr) {
					size_t		LookLen = strlen(LookFor);

					while (*It != 0) {
						if (strncmp(It, LookFor, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const std::string & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const char	*	Look = LookFor.c_str();
					size_t		LookLen = strlen(Look);

					while (*It != 0) {
						if (strncmp(It, Look, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const std::u16string & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const char16_t	*	Look = LookFor.c_str();
					size_t		LookLen = strlen(Look);

					while (*It != 0) {
						if (strncmp(It, Look, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const std::u32string & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const char32_t	*	Look = LookFor.c_str();
					size_t		LookLen = strlen(Look);

					while (*It != 0) {
						if (strncmp(It, Look, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const std::wstring & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const wchar_t	*	Look = LookFor.c_str();
					size_t		LookLen = strlen(Look);

					while (*It != 0) {
						if (strncmp(It, Look, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const String & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const_iterator	LIt = LookFor.cbegin();
					size_t		LookLen = LookFor.Length();

					while (*It != 0) {
						if (strncmp(It, LIt, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const ROString & LookFor)
			{
				const_iterator	&	Results = It;

				if (*It != 0) {
					const_iterator	LIt = LookFor.cbegin();
					size_t		LookLen = LookFor.Length();

					while (*It != 0) {
						if (strncmp(It, LIt, LookLen) == 0) {
							break;
						}

						It++;
					}
				}

				return (Results);
			}

			String::const_iterator
			String::strstr(const_iterator & It,
			               const_iterator & LookFor)
			{
				/**@todo */
			}

		}
	}
}
