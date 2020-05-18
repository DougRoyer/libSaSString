//
// BEGIN_DOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2019 Douglas Mark Royer, All Rights Reserved.
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
#include <SaS/String/StringCache.hpp>
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

			String::const_iterator	&
			String::strpbrk(const std::string & Accept) const
			{
				return (strpbrk(Accept.c_str()));
			}

			String::const_iterator	&
			String::strpbrk(const std::u16string & Accept) const
			{
				return (strpbrk(Accept.c_str()));
			}

			String::const_iterator	&
			String::strpbrk(const std::u32string & Accept) const
			{
				return (strpbrk(Accept.c_str()));
			}

			String::const_iterator	&
			String::strpbrk(const std::wstring & Accept) const
			{
				return (strpbrk(Accept.c_str()));
			}

			String::const_iterator	&
			String::strpbrk(const String & Accept) const
			{
				ROString		RO(Accept);

				return (strpbrk(RO));
			}

			String::const_iterator	&
			String::strpbrk(const ROString & Accept) const
			{
				const_iterator		& Results = cend();

				const_iterator		InIt = cbegin();
				const_iterator		AcceptIt;

				size_t			InLen = 0;
				size_t			ALen = 0;

				bool			Done = false;

				String		*	AConverted = Accept.ToCharset(_InputCharset,
				                             _InputWidth);

				int			Mult = 0;

				switch (_InputWidth) {

					case IsUnknownBit_t:
						/*EMPTY*/
						break;

					case Is8Bit_t:
						Mult = sizeof(char);
						break;

					case Is16Bit_t:
						Mult = sizeof(char16_t);
						break;

					case Is32Bit_t:
						Mult = sizeof(char32_t);
						break;

					case IsWBit_t:
						Mult = sizeof(wchar_t);
						break;
				}

				if (AConverted != nullptr) {
					while (InIt != cend() && !Done) {
						AcceptIt = ((const String *)AConverted)->cbegin();
						InLen = CharacterUnits(InIt);
						ALen = CharacterUnits(AcceptIt);

						while (AcceptIt != Accept.cend()) {
							if (InLen != ALen) {
								InIt++;
								ALen = CharacterUnits(AcceptIt);
								continue;
							}

							// *InIt length == *AcceptIt length.
							// We just need the pointer, so str8() will do.
							//
							int	Cmp = memcmp(InIt.str8(), AcceptIt.str8(),
							                 InLen * Mult);

							if (Cmp == 0) {
								Done = true;
								Results = InIt;
								break;
							}

							AcceptIt++;
						}

						if (!Done) {
							InIt++;
						}
					}
				}

				return (Results);
			}

			String::const_iterator	&
			String::strpbrk(const char * const Accept) const
			{
				String::const_iterator		&	Results = cend();

				if (Accept != nullptr) {
					ROString			AsRO(Accept);

					Results = strpbrk(AsRO);
				}

				return (Results);
			}

			String::const_iterator	&
			String::strpbrk(const char16_t * const Accept) const
			{
				String::const_iterator		&	Results = cend();

				if (Accept != nullptr) {
					ROString			AsRO(Accept);

					Results = strpbrk(AsRO);
				}

				return (Results);
			}

			String::const_iterator	&
			String::strpbrk(const char32_t * const Accept) const
			{
				String::const_iterator		&	Results = cend();

				if (Accept != nullptr) {
					ROString			AsRO(Accept);

					Results = strpbrk(AsRO);
				}

				return (Results);
			}

			String::const_iterator	&
			String::strpbrk(const wchar_t * const Accept) const
			{
				String::const_iterator		&	Results = cend();

				if (Accept != nullptr) {
					ROString			AsRO(Accept);

					Results = strpbrk(AsRO);
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const char * const Accept)
			{
				const char	*	Results = nullptr;

				bool			Done = false;

				if (InStr != nullptr && Accept != nullptr) {
					const char  *	InPtr = InStr;
					const char  *	RPtr = Accept;
					size_t	InLen = 0;
					size_t	RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Accept;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							int	Cmp = strncmp(InPtr, RPtr, InLen);

							if (Cmp == 0) {
								Done = true;
								Results = InPtr;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
						}
					}
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const char16_t * const Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset16To8(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const char32_t * const Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char	*	Out = nullptr;

					if (String::Charset32To8(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const wchar_t * const Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char	*	Out = nullptr;

					if (String::CharsetWTo8(nullptr,
					                        Accept,
					                        nullptr,
					                        Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const String & Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr) {
					if (Accept.IsReadOnly()) {
						Results = strpbrk(InStr, (ROString &)Accept);

					} else {
						Results = strpbrk(InStr, Accept.Get8());
					}
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const ROString & Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr) {

					String	*	AsIn = Accept.ToCharset(Current8BitCharset,
					                                    Current8BitWidth);

					Results = strpbrk(InStr, AsIn->Get8());
					delete AsIn;
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const std::u16string & Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const std::u32string & Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char	*
			String::strpbrk(const char * const InStr,
			                const std::wstring & Accept)
			{
				const char	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const char * const Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset8To16(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const char16_t * const Accept)
			{
				const char16_t	*	Results = nullptr;

				bool		Done = false;

				if (InStr != nullptr && Accept != nullptr) {
					const char16_t  *	InPtr = InStr;
					const char16_t  *	RPtr = Accept;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Accept;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) == 0) {
								Done = true;
								Results = InPtr;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
						}
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const char32_t * const Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::Charset32To16(nullptr,
					                          Accept,
					                          nullptr,
					                          Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const wchar_t * const Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char16_t	*	Out = nullptr;

					if (String::CharsetWTo16(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const std::string & Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const std::u16string & Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const std::u32string & Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const std::wstring & Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char16_t	*
			String::strpbrk(const char16_t * const InStr,
			                const ROString & Accept)
			{
				const char16_t	*	Results = nullptr;

				if (InStr != nullptr) {

					String	*	AsIn = Accept.ToCharset(Current16BitCharset,
					                                    Current16BitWidth);

					Results = strpbrk(InStr, AsIn->Get16());
					delete AsIn;
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const char * const Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset8To32(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const char16_t * const Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::Charset16To32(nullptr,
					                          Accept,
					                          nullptr,
					                          Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const char32_t * const Accept)
			{
				const char32_t	*	Results = nullptr;

				bool		Done = false;

				if (InStr != nullptr && Accept != nullptr) {
					const char32_t  *	InPtr = InStr;
					const char32_t  *	RPtr = Accept;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Accept;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) == 0) {
								Done = true;
								Results = InPtr;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
						}
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const wchar_t * const Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					char32_t	*	Out = nullptr;

					if (String::CharsetWTo32(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const std::string & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const std::u16string & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const std::u32string & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const std::wstring & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const String & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {
					if (Accept.IsReadOnly()) {
						Results = strpbrk(InStr, (ROString &)Accept);

					} else {
						Results = strpbrk(InStr, Accept.Get32());
					}
				}

				return (Results);
			}

			const char32_t	*
			String::strpbrk(const char32_t * const InStr,
			                const ROString & Accept)
			{
				const char32_t	*	Results = nullptr;

				if (InStr != nullptr) {

					String	*	AsIn = Accept.ToCharset(Current32BitCharset,
					                                    Current32BitWidth);

					Results = strpbrk(InStr, AsIn->Get32());
					delete AsIn;
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const wchar_t * const Accept)
			{
				const wchar_t	*	Results = nullptr;

				bool		Done = false;

				if (InStr != nullptr && Accept != nullptr) {
					const wchar_t  *	InPtr = InStr;
					const wchar_t  *	RPtr = Accept;
					size_t		InLen = 0;
					size_t		RLen = 0;

					while (*InPtr != 0 && !Done) {
						RPtr = Accept;
						InLen = CharacterUnits(InPtr);
						RLen = CharacterUnits(RPtr);

						while (*RPtr != 0) {
							if (InLen != RLen) {
								InPtr += InLen;
								RPtr += RLen;
								RLen = CharacterUnits(RPtr);
								continue;
							}

							if (memcmp(InPtr, RPtr, InLen) == 0) {
								Done = true;
								Results = InPtr;
								break;
							}

							RPtr++;
						}

						if (!Done) {
							InPtr++;
						}
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const char * const Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset8ToW(nullptr,
					                        Accept,
					                        nullptr,
					                        Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const char16_t * const Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset16ToW(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const char32_t * const Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr && Accept != nullptr) {
					wchar_t	*	Out = nullptr;

					if (String::Charset32ToW(nullptr,
					                         Accept,
					                         nullptr,
					                         Out)) {
						Results = strpbrk(InStr, Out);
						delete Out;
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const std::string & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const std::u16string & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const std::u32string & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const std::wstring & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {
					Results = strpbrk(InStr, Accept.c_str());
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const String & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {
					if (Accept.IsReadOnly()) {
						Results = strpbrk(InStr, (ROString &)Accept);

					} else {
						Results = strpbrk(InStr, Accept.Get32());
					}
				}

				return (Results);
			}

			const wchar_t	*
			String::strpbrk(const wchar_t * const InStr,
			                const ROString & Accept)
			{
				const wchar_t	*	Results = nullptr;

				if (InStr != nullptr) {

					String	*	AsIn = Accept.ToCharset(CurrentWBitCharset,
					                                    CurrentWBitWidth);

					Results = strpbrk(InStr, AsIn->GetW());
					delete AsIn;
				}

				return (Results);
			}

		}
	}
}
