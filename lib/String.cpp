//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2020 Software and Services LLC, All Rights Reserved.
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

#include <SaS/String/CopyRightNotice.h>

#define _MB_CAPABLE 1

#include <SaS/String/StringCache.hpp>
#include <SaS/String/ROString.hpp>
#include <SaS/Common/Error.hpp>

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <SaS/Common/version.hpp>
#include <ctype.h>
#include <wctype.h>

#ifndef WIN32
#include <langinfo.h>
#include <nl_types.h>
#include <unistd.h>
#include <pthread.h>
#else
#include <SaS/Common/osver.h>
#include <SaS/Common/winWrappers.hpp>
#endif

#include <wchar.h>

#include <locale.h>

#ifdef USE_LICENSE
#include "license.hpp"
#endif

#include <SaS/Common/osver.h>
#include <arpa/inet.h>
#include <ostream>

#include <SaS/Common/htonll.h>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			static const char		*	EmptyString8 = "";
			static const char16_t	*	EmptyString16 = u"";
			static const char32_t	*	EmptyString32 = U"";

#ifdef USE_LICENSE
			static SaS_License	*	mem = nullptr;
#else
			static const char		*	mem
			    = "Copyright (C) 2003-2012,2019 Software and Services LLC,"
			      "All Rights Reserved.";
#endif

			static pthread_mutex_t	memMutex = PTHREAD_MUTEX_INITIALIZER;

#ifdef USE_LICENSE
			static void
			SaSInitMem()
			{
				SaS_License::SaSInitMem(&mem,
				                        TARG_BINARY_s,
				                        FULLVERSION_s,
				                        SaS_License::StringRuntime_t,
#ifndef WIN32
				                        PSTAMP_s
#else
				                        nullptr
#endif
				                       );
				return;
			}
#else
			static void
			SaSInitMem()
			{
				return;
			}
#endif


			String::String()
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif

				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				_InputCharset = StringCache::Add(Current8BitCharset);
				_InputWidth = Is8Bit_t;
				_OutputCharset = StringCache::Add(Current8BitCharset);
				_OutputWidth = Is8Bit_t;

				return;
			}

			String::String(const char * const CSet,
			               CharacterUnitWidth_e Width)
			{

				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is8Bit_t;
					_OutputWidth = Is8Bit_t;
					Width = Is8Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {

					switch (Width) {

						default:

						/*FALLTHRU*/
						case IsUnknownBit_t:

						/*FALLTHRU*/

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

					}
				}

				return;
			}

			String::String(const char * const initStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{

				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is8Bit_t;
					_OutputWidth = Is8Bit_t;
					Width = Is8Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						default:

						/* 8-Bit initialize - set to 8-Bit */
						/*FALLTHRU*/

						case IsUnknownBit_t:

						/* 8-Bit initialize - set to 8-Bit */
						/*FALLTHRU*/

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;
					}
				}

				Append(initStr);

				return;
			}


			String::String(const ROString & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{

#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputCharset = StringCache::Add(InitStr._InputCharset);
					_InputWidth = InitStr.InputWidth();
					_OutputCharset = StringCache::Add(InitStr._InputCharset);
					_OutputWidth = InitStr.OutputWidth();
					Width = _InputWidth;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/
						case IsUnknownBit_t:
							break;
					}
				}

				Append(InitStr);

				return;
			}


			String::String(const String & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif

				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;


				if (Width == IsUnknownBit_t) {
					_InputCharset = StringCache::Add(InitStr._InputCharset);
					_InputWidth = InitStr.InputWidth();
					_OutputCharset = StringCache::Add(InitStr._InputCharset);
					_OutputWidth = InitStr.OutputWidth();
					Width = _InputWidth;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							break;

					}
				}

				Append(InitStr);

				return;
			}


			String::String(const char16_t * InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif

				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is16Bit_t;
					_OutputWidth = Is16Bit_t;
					Width = Is16Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

					}
				}

				Append(InitStr);

				return;
			}


			String::String(const char32_t * InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;


				if (Width == IsUnknownBit_t) {
					_InputWidth = Is32Bit_t;
					_OutputWidth = Is32Bit_t;
					Width = Is32Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;
					}
				}

				Append(InitStr);

				return;
			}


			String::String(const wchar_t * InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;


				if (Width == IsUnknownBit_t) {
					_InputWidth = IsWBit_t;
					_OutputWidth = IsWBit_t;
					Width = IsWBit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;
					}
				}

				Append(InitStr);

				return;
			}


			String::String(const std::string & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is8Bit_t;
					_OutputWidth = Is8Bit_t;
					Width = Is8Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;
					}
				}

				Append(InitStr.c_str());

				return;
			}


			String::String(const std::u16string & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is16Bit_t;
					_OutputWidth = Is16Bit_t;
					Width = Is16Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;
					}
				}

				Append(InitStr.c_str());

				return;
			}


			String::String(const std::u32string & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = Is32Bit_t;
					_OutputWidth = Is32Bit_t;
					Width = Is32Bit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;

					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;
					}
				}

				Append(InitStr.c_str());

				return;
			}


			String::String(const std::wstring & InitStr,
			               const char * const CSet,
			               CharacterUnitWidth_e Width)
			{
#ifdef USE_LICENSE

				if (mem == nullptr) {
					if (pthread_mutex_trylock(&memMutex) == 0) {
						(void)SaSInitMem();
					}
				}

#endif
				_StrW = nullptr;
				_Str32 = nullptr;
				_Str16 = nullptr;
				_Str8 = nullptr;
				_InputHasChanged = false;
				_ROString = false;
				_RO = nullptr;

				if (Width == IsUnknownBit_t) {
					_InputWidth = IsWBit_t;
					_OutputWidth = IsWBit_t;
					Width = IsWBit_t;

				} else {
					_InputWidth = Width;
					_OutputWidth = Width;
				}

				if (CSet != nullptr) {
					_InputCharset = StringCache::Add(CSet);
					_OutputCharset = StringCache::Add(CSet);

				} else {
					switch (Width) {

						case Is8Bit_t:
							_InputCharset = StringCache::Add(Current8BitCharset);
							_OutputCharset = StringCache::Add(Current8BitCharset);
							break;

						case Is16Bit_t:
							_InputCharset = StringCache::Add(Current16BitCharset);
							_OutputCharset = StringCache::Add(Current16BitCharset);
							break;

						case Is32Bit_t:
							_InputCharset = StringCache::Add(Current32BitCharset);
							_OutputCharset = StringCache::Add(Current32BitCharset);
							break;

						case IsWBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;

						default:

						/*FALLTHRU*/

						case IsUnknownBit_t:
							_InputCharset = StringCache::Add(CurrentWBitCharset);
							_OutputCharset = StringCache::Add(CurrentWBitCharset);
							break;
					}
				}

				Append(InitStr.c_str());

				return;
			}


			String::~String()
			{
				if (getInstance() == 1) {
					Clear();
				}

				if (_InputCharset != nullptr) {
					StringCache::Remove(_InputCharset);
					_InputCharset = nullptr;
				}

				if (_OutputCharset != nullptr) {
					StringCache::Remove(_OutputCharset);
					_OutputCharset = nullptr;
				}

				return;
			}

			bool
			String::IsReadOnly() const
			{
				return (_ROString);
			}

			String	&
			String::operator=(const char CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const char16_t CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const char32_t CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const wchar_t CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const char * CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const char16_t * CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const char32_t * CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const wchar_t * CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const String & CopyFrom)
			{

				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const ROString & CopyFrom)
			{

				if (!_ROString) {
					Clear();
					Append(CopyFrom);
				}

				return (*this);
			}

			String	&
			String::operator=(const std::string & CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom.c_str());
				}

				return (*this);
			}

			String	&
			String::operator=(const std::u16string & CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom.c_str());
				}

				return (*this);
			}

			String	&
			String::operator=(const std::u32string & CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom.c_str());
				}

				return (*this);
			}

			String	&
			String::operator=(const std::wstring & CopyFrom)
			{
				if (!_ROString) {
					Clear();
					Append(CopyFrom.c_str());
				}

				return (*this);
			}

			void
			String::Clear()
			{
				if (!_ROString) {
					std::vector<StringSeg *>::iterator	it;
					StringSeg	*	Seg = nullptr;

					for (it = _Segments.begin(); it != _Segments.end(); it++) {
						Seg = *it;

						if (Seg != nullptr) {
							delete Seg;
						}
					}

					_Segments.clear();

					if (_StrW != nullptr) {
						StringCache::Remove(_StrW);
						_StrW = nullptr;
					}

					if (_Str32 != nullptr) {
						StringCache::Remove(_Str32);
						_Str32 = nullptr;
					}

					if (_Str16 != nullptr) {
						StringCache::Remove(_Str16);
						_Str16 = nullptr;
					}

					if (_Str8 != nullptr) {
						StringCache::Remove(_Str8);
						_Str8 = nullptr;
					}

					_SetInputChanged();
				}

				return;
			}

			String	&
			String::Append(const DateTime & dt)
			{
				dt.Sprint(this);

				return (*this);
			}


			void *
			String::GetMem() const
			{
				return ((void *)mem);
			}

			bool
			String::Lock() const
			{
				bool		Results = false;
				int		GotLock = pthread_mutex_lock(&_Lock);

				if (GotLock == 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			String::TryLock() const
			{
				bool	Results = false;
				int	GotLock = pthread_mutex_trylock(&_Lock);

				if (GotLock == 0) {
					Results = true;
				}

				return (Results);
			}

			bool
			String::Unlock() const
			{
				bool	Results = false;
				int	GotUnLock = pthread_mutex_unlock(&_Lock);

				if (GotUnLock == 0) {
					Results = true;
				}

				return (Results);
			}

			const wchar_t	*
			String::GetW() const
			{
				const wchar_t	*	Results = nullptr;

				if (_ROString && _StrW == nullptr) {
					// Make a non-ROString, then Get8() it.
					//
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							if (_RO->Str.RO8 != nullptr) {
								_StrW = StringCache::Add(strdupW(_RO->Str.RO8,
								                                 _RO->StrUnits));
							}

							break;

						case Is16Bit_t:
							if (_RO->Str.RO16 != nullptr) {
								_StrW = StringCache::Add(strdupW(_RO->Str.RO16,
								                                 _RO->StrUnits));
							}

							break;

						case Is32Bit_t:
							if (_RO->Str.RO32 != nullptr) {
								_StrW = StringCache::Add(strdupW(_RO->Str.RO32,
								                                 _RO->StrUnits));
							}

							break;

						case IsWBit_t:
							if (_RO->Str.ROW != nullptr) {
								_StrW = StringCache::Add(strdupW(_RO->Str.ROW,
								                                 _RO->StrUnits));
							}

							break;
					}

					Results = _StrW;

				} else {

					if (_InputHasChanged || _StrW == nullptr) {
						std::vector<StringSeg *>::const_iterator	sIt;
						std::vector<wchar_t *>			Converted;
						std::vector<wchar_t *>::iterator		cIt;

						const StringSeg	*	Seg = nullptr;
						wchar_t		*	Str = nullptr;
						size_t			TotalLen = 0;

						for (sIt = _Segments.begin(); sIt != _Segments.end();
						     sIt++) {
							Seg = *sIt;

							if (Seg != nullptr) {
								switch (Seg->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t: {
											wchar_t	*	ToW = nullptr;
											const char	*	From = nullptr;

											if (Seg->IsReadOnly) {
												From = Seg->Str.RO8;

											} else {
												From = Seg->Str.Utf8->c_str();
											}

											if (Charset8ToW(Seg->Charset,
											                From,
											                Seg->StrUnits,
											                nullptr,
											                ToW)) {
												Converted.push_back(ToW);
												TotalLen += strlen(ToW);
											}
										}
										break;

									case Is16Bit_t: {
											wchar_t	*	ToW = nullptr;
											const char16_t	*	From = nullptr;

											if (Seg->IsReadOnly) {
												From = Seg->Str.RO16;

											} else {
												From = Seg->Str.Utf16->c_str();
											}

											if (Charset16ToW(Seg->Charset,
											                 From,
											                 Seg->StrUnits,
											                 nullptr,
											                 ToW)) {
												Converted.push_back(ToW);
												TotalLen += strlen(ToW);
											}
										}
										break;

									case Is32Bit_t: {
											wchar_t	*	ToW = nullptr;
											const char32_t	*	From = nullptr;

											if (Seg->IsReadOnly) {
												From = Seg->Str.RO32;

											} else {
												From = Seg->Str.Utf32->c_str();
											}

											if (Charset32ToW(Seg->Charset,
											                 From,
											                 Seg->StrUnits,
											                 nullptr,
											                 ToW)) {
												Converted.push_back(ToW);
												TotalLen += strlen(ToW);
											}
										}
										break;

									case IsWBit_t: {
											wchar_t	*	ToW = nullptr;
											const wchar_t	*	From = nullptr;

											if (Seg->IsReadOnly) {
												From = Seg->Str.ROW;

											} else {
												From = Seg->Str.W->c_str();
											}

											if (CharsetWToW(Seg->Charset,
											                From,
											                Seg->StrUnits,
											                nullptr,
											                ToW)) {
												Converted.push_back(ToW);
												TotalLen += strlen(ToW);
											}
										}
										break;
								}
							}
						}

						wchar_t	*	Tmp = new wchar_t[TotalLen + 1];
						Tmp[0] = 0;

						for (cIt = Converted.begin(); cIt != Converted.end();
						     cIt++) {
							Str = *cIt;
							strcatW(Tmp, Str);
							delete Str;
						}

						_StrW = StringCache::Add(Tmp);
						_InputHasChanged = false;
					}

					if (_StrW == nullptr) {
						_StrW = StringCache::Add(strdupW(EmptyString32));
					}

					Results = _StrW;
				}

				return (Results);
			}

			const char	*
			String::Get8() const
			{
				const char	*	Results = nullptr;

				if (_ROString && _Str8 == nullptr) {
					// Make a non-ROString, then Get8() it.
					//
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							if (_RO->Str.RO8 != nullptr) {
								_Str8 = StringCache::Add(strdup8(_RO->Str.RO8,
								                                 _RO->StrUnits));
							}

							break;

						case Is16Bit_t:
							if (_RO->Str.RO16 != nullptr) {
								_Str8 = StringCache::Add(strdup8(_RO->Str.RO16,
								                                 _RO->StrUnits));
							}

							break;

						case Is32Bit_t:
							if (_RO->Str.RO32 != nullptr) {
								_Str8 = StringCache::Add(strdup8(_RO->Str.RO32,
								                                 _RO->StrUnits));
							}

							break;

						case IsWBit_t:
							if (_RO->Str.ROW != nullptr) {
								_Str8 = StringCache::Add(strdup8(_RO->Str.ROW,
								                                 _RO->StrUnits));
							}

							break;
					}

					Results = _Str8;

				} else {

					if (_InputHasChanged || _Str8 == nullptr) {
						std::vector<StringSeg *>::const_iterator	sIt;
						std::vector<char *>				Converted;
						std::vector<char *>::iterator			cIt;

						const StringSeg	*	Seg = nullptr;
						char		*		Str = nullptr;
						size_t			TotalLen = 0;

						for (sIt = _Segments.begin(); sIt != _Segments.end();
						     sIt++) {
							Seg = *sIt;

							if (Seg != nullptr) {
								switch (Seg->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t: {
											char	*	To8 = nullptr;
											const char	*	From8 = Seg->Str.RO8;

											if (!Seg->IsReadOnly) {
												From8 = Seg->Str.Utf8->c_str();
											}

											if (Charset8To8(Seg->Charset,
											                From8,
											                Seg->StrUnits,
											                nullptr,
											                To8)) {
												Converted.push_back(To8);
												TotalLen += strlen(To8);
											}
										}
										break;

									case Is16Bit_t: {
											char		*	To8 = nullptr;
											const char16_t	*	From16 = Seg->Str.RO16;

											if (!Seg->IsReadOnly) {
												From16 = Seg->Str.Utf16->c_str();
											}

											if (Charset16To8(Seg->Charset,
											                 From16,
											                 Seg->StrUnits,
											                 nullptr,
											                 To8)) {
												Converted.push_back(To8);
												TotalLen += strlen(To8);
											}
										}
										break;

									case Is32Bit_t: {
											char		*	To8 = nullptr;
											const char32_t	*	From32 = Seg->Str.RO32;

											if (!Seg->IsReadOnly) {
												From32 = Seg->Str.Utf32->c_str();
											}

											if (Charset32To8(Seg->Charset,
											                 From32,
											                 Seg->StrUnits,
											                 nullptr,
											                 To8)) {
												Converted.push_back(To8);
												TotalLen += strlen(To8);
											}
										}
										break;

									case IsWBit_t: {
											char		*	To8 = nullptr;
											const wchar_t	*	FromW = Seg->Str.ROW;

											if (!Seg->IsReadOnly) {
												FromW = Seg->Str.W->c_str();
											}

											if (CharsetWTo8(Seg->Charset,
											                FromW,
											                Seg->StrUnits,
											                nullptr,
											                To8)) {
												Converted.push_back(To8);
												TotalLen += strlen(To8);
											}
										}
										break;
								}
							}
						}

						char	*	Tmp = new char[TotalLen + 1];
						Tmp[0] = 0;

						for (cIt = Converted.begin(); cIt != Converted.end();
						     cIt++) {
							Str = *cIt;
							strcat(Tmp, Str);
							delete Str;
						}

						_Str8 = StringCache::Add(Tmp);
						_InputHasChanged = false;
					}

					if (_Str8 == nullptr) {
						_Str8 = StringCache::Add(strdup(EmptyString8));
					}

					Results = _Str8;
				}

				return (Results);
			}

			const char16_t	*
			String::Get16() const
			{
				const char16_t	*	Results = nullptr;

				if (_ROString && _Str16 == nullptr) {
					// Make a non-ROString, then Get8() it.
					//
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							if (_RO->Str.RO8 != nullptr) {
								_Str16 = StringCache::Add(strdup16(_RO->Str.RO8,
								                                   _RO->StrUnits));
							}

							break;

						case Is16Bit_t:
							if (_RO->Str.RO16 != nullptr) {
								_Str16 = StringCache::Add(strdup16(_RO->Str.RO16,
								                                   _RO->StrUnits));
							}

							break;

						case Is32Bit_t:
							if (_RO->Str.RO32 != nullptr) {
								_Str16 = StringCache::Add(strdup16(_RO->Str.RO32,
								                                   _RO->StrUnits));
							}

							break;

						case IsWBit_t:
							if (_RO->Str.ROW != nullptr) {
								_Str16 = StringCache::Add(strdup16(_RO->Str.ROW,
								                                   _RO->StrUnits));
							}

							break;
					}

					Results = _Str16;

				} else {

					if (_InputHasChanged || _Str16 == nullptr) {
						std::vector<StringSeg *>::const_iterator	sIt;
						std::vector<char16_t *>			Converted;
						std::vector<char16_t *>::iterator		cIt;

						const StringSeg	*	Seg = nullptr;
						char16_t		*	Str = nullptr;
						size_t			TotalLen = 0;

						for (sIt = _Segments.begin(); sIt != _Segments.end();
						     sIt++) {
							Seg = *sIt;

							if (Seg != nullptr) {
								switch (Seg->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t: {
											char16_t	*	To16 = nullptr;
											const char	*	From8 = Seg->Str.RO8;

											if (!Seg->IsReadOnly) {
												From8 = Seg->Str.Utf8->c_str();
											}

											if (Charset8To16(Seg->Charset,
											                 From8,
											                 Seg->StrUnits,
											                 nullptr,
											                 To16)) {
												Converted.push_back(To16);
												TotalLen += strlen(To16);
											}
										}
										break;

									case Is16Bit_t: {
											char16_t		*	To16 = nullptr;
											const char16_t	*	From16 = Seg->Str.RO16;

											if (!Seg->IsReadOnly) {
												From16 = Seg->Str.Utf16->c_str();
											}

											if (Charset16To16(Seg->Charset,
											                  From16,
											                  Seg->StrUnits,
											                  nullptr,
											                  To16)) {
												Converted.push_back(To16);
												TotalLen += strlen(To16);
											}
										}
										break;

									case Is32Bit_t: {
											char16_t		*	To16 = nullptr;
											const char32_t	*	From32 = Seg->Str.RO32;

											if (!Seg->IsReadOnly) {
												From32 = Seg->Str.Utf32->c_str();
											}

											if (Charset32To16(Seg->Charset,
											                  From32,
											                  Seg->StrUnits,
											                  nullptr,
											                  To16)) {
												Converted.push_back(To16);
												TotalLen += strlen(To16);
											}
										}
										break;

									case IsWBit_t: {
											char16_t		*	To16 = nullptr;
											const wchar_t	*	FromW = Seg->Str.ROW;

											if (!Seg->IsReadOnly) {
												FromW = Seg->Str.W->c_str();
											}

											if (CharsetWTo16(Seg->Charset,
											                 FromW,
											                 Seg->StrUnits,
											                 nullptr,
											                 To16)) {
												Converted.push_back(To16);
												TotalLen += strlen(To16);
											}
										}
										break;
								}
							}
						}

						char16_t	*	Tmp = new char16_t[TotalLen + 1];
						Tmp[0] = 0;

						for (cIt = Converted.begin(); cIt != Converted.end();
						     cIt++) {
							Str = *cIt;
							strcat16(Tmp, Str);
							delete Str;
						}

						_Str16 = StringCache::Add(Tmp);
						_InputHasChanged = false;
					}

					if (_Str16 == nullptr) {
						_Str16 = StringCache::Add(strdup16(EmptyString16));
					}

					Results = _Str16;
				}

				return (Results);
			}

			const char32_t	*
			String::Get32() const
			{
				const char32_t	*	Results = nullptr;

				if (_ROString && _Str16 == nullptr) {
					// Make a non-ROString, then Get8() it.
					//
					switch (_RO->Width) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t:
							if (_RO->Str.RO8 != nullptr) {
								_Str32 = StringCache::Add(strdup32(_RO->Str.RO8,
								                                   _RO->StrUnits));
							}

							break;

						case Is16Bit_t:
							if (_RO->Str.RO16 != nullptr) {
								_Str32 = StringCache::Add(strdup32(_RO->Str.RO16,
								                                   _RO->StrUnits));
							}

							break;

						case Is32Bit_t:
							if (_RO->Str.RO32 != nullptr) {
								_Str32 = StringCache::Add(strdup32(_RO->Str.RO32,
								                                   _RO->StrUnits));
							}

							break;

						case IsWBit_t:
							if (_RO->Str.ROW != nullptr) {
								_Str32 = StringCache::Add(strdup32(_RO->Str.ROW,
								                                   _RO->StrUnits));
							}

							break;
					}

					Results = _Str32;

				} else {

					if (_InputHasChanged || _Str32 == nullptr) {
						std::vector<StringSeg *>::const_iterator	sIt;
						std::vector<char32_t *>			Converted;
						std::vector<char32_t *>::iterator		cIt;

						const StringSeg	*	Seg = nullptr;
						char32_t		*	Str = nullptr;
						size_t			TotalLen = 0;

						for (sIt = _Segments.begin(); sIt != _Segments.end();
						     sIt++) {
							Seg = *sIt;

							if (Seg != nullptr) {
								switch (Seg->Width) {

									case IsUnknownBit_t:
										/*EMPTY*/
										break;

									case Is8Bit_t: {
											char32_t	*	To32 = nullptr;
											const char	*	From8 = Seg->Str.RO8;

											if (!Seg->IsReadOnly) {
												From8 = Seg->Str.Utf8->c_str();
											}

											if (Charset8To32(Seg->Charset,
											                 From8,
											                 Seg->StrUnits,
											                 nullptr,
											                 To32)) {
												Converted.push_back(To32);
												TotalLen += strlen(To32);
											}
										}
										break;

									case Is16Bit_t: {
											char32_t		*	To32 = nullptr;
											const char16_t	*	From16 = Seg->Str.RO16;

											if (!Seg->IsReadOnly) {
												From16 = Seg->Str.Utf16->c_str();
											}

											if (Charset16To32(Seg->Charset,
											                  From16,
											                  Seg->StrUnits,
											                  nullptr,
											                  To32)) {
												Converted.push_back(To32);
												TotalLen += strlen(To32);
											}
										}
										break;

									case Is32Bit_t: {
											char32_t		*	To32 = nullptr;
											const char32_t	*	From32 = Seg->Str.RO32;

											if (!Seg->IsReadOnly) {
												From32 = Seg->Str.Utf32->c_str();
											}

											if (Charset32To32(Seg->Charset,
											                  From32,
											                  Seg->StrUnits,
											                  nullptr,
											                  To32)) {
												Converted.push_back(To32);
												TotalLen += strlen(To32);
											}
										}
										break;

									case IsWBit_t: {
											char32_t		*	To32 = nullptr;
											const wchar_t	*	FromW = Seg->Str.ROW;

											if (!Seg->IsReadOnly) {
												FromW = Seg->Str.W->c_str();
											}

											if (CharsetWTo32(Seg->Charset,
											                 FromW,
											                 Seg->StrUnits,
											                 nullptr,
											                 To32)) {
												Converted.push_back(To32);
												TotalLen += strlen(To32);
											}
										}
										break;
								}
							}
						}

						char32_t	*	Tmp = new char32_t[TotalLen + 1];
						Tmp[0] = 0;

						for (cIt = Converted.begin(); cIt != Converted.end();
						     cIt++) {
							Str = *cIt;
							strcat32(Tmp, Str);
							delete Str;
						}

						_Str32 = StringCache::Add(Tmp);
						_InputHasChanged = false;
					}

					if (_Str32 == nullptr) {
						_Str32 = StringCache::Add(strdup32(EmptyString32));
					}

					Results = _Str32;
				}

				return (Results);
			}

			size_t
			String::sprintf(const char * format, ...)
			{
				size_t			Results = 0;
				va_list			TheArgs;
				size_t			BigBufSize = 10240;

				// A big buffer.
				//
				char		*	BigBuff = new char[BigBufSize + 1];

				memset(BigBuff, 0, BigBufSize + 1);
				size_t			copied = 0;
				BigBuff[0] = '\0';

				va_start(TheArgs, format);

				do {
					copied = ::vsnprintf(BigBuff, BigBufSize, format, TheArgs);

					if (copied < BigBufSize) {
						Results = copied;
						break;
					}

					BigBufSize *= 10;
					delete [] BigBuff;
					BigBuff = new char[BigBufSize];
					memset(BigBuff, 0, BigBufSize + 1);

				} while (copied < BigBufSize);

				va_end(TheArgs);

				this->Append(BigBuff);

				return (Results);
			}

#ifdef WIN32
#define vswprintf _vsnwprintf
#endif

			size_t
			String::sprintf(const wchar_t * format, ...)
			{
				size_t			Results = 0;

				va_list			TheArgs;
				size_t			copied = 0;
				size_t			BigBufSize = 10240;
				wchar_t		*	BigBuff = new wchar_t[BigBufSize + 1];

				BigBuff[0] = L'\0';
				memset(BigBuff, 0, BigBufSize + 1);

				do {
					va_start(TheArgs, format);
					copied = ::vswprintf((wchar_t *)BigBuff,
					                     BigBufSize,
					                     (wchar_t *)format,
					                     TheArgs);

					if (copied < BigBufSize) {
						Results = copied;
						break;
					}

					BigBufSize *= 10;
					delete [] BigBuff;
					BigBuff = new wchar_t[BigBufSize];
					memset(BigBuff, 0, BigBufSize + 1);

					va_end(TheArgs);
				} while (copied < BigBufSize);

				this->Append(BigBuff);

				return (Results);
			}

			size_t
			String::sprintf(const char16_t * format, ...)
			{
				size_t			Results = 0;

				va_list			TheArgs;
#if __SIZEOF_WCHAR_T__ == 2
				Results = sprintf((wchar_t *)format, TheArgs);
#endif

#if __SIZEOF_WCHAR_T__ == 4
				String			Format32(format);

				Results = sprintf((wchar_t *)Format32.Get32(), TheArgs);
#endif
				va_end(TheArgs);

				return (Results);
			}

			size_t
			String::sprintf(const char32_t * format, ...)
			{
				size_t			Results = 0;
				va_list			TheArgs;

#if __SIZEOF_WCHAR_T__ == 2
				String			Format16(format);

				Results = sprintf((wchar_t *)Format16.Get16(), TheArgs);
#endif
#if __SIZEOF_WCHAR_T__ == 4
				Results = sprintf((wchar_t *)format, TheArgs);
#endif
				va_end(TheArgs);

				return (Results);
			}

			void
			String::ToLower()
			{
				// Works for UTF strings.
				//
				if (strncasecmp(_InputCharset, "UTF", 3) == 0) {

					switch (_InputWidth) {

						case IsUnknownBit_t:
							break;

						case Is8Bit_t: {
								char	*	In8 = strdup(Get8());
								char	*	Ptr = In8;

								while (*Ptr != 0) {
									if (isupper(*Ptr)) {
										*Ptr = (char)tolower(*Ptr);
									}

									Ptr++;
								}

								*this = In8;
								delete In8;
							}
							break;

						case Is16Bit_t: {
								char16_t	*	In16 = strdup16(Get16());
								char16_t	*	Ptr = In16;

								while (*Ptr != 0) {
									if (isupper(*Ptr)) {
										*Ptr = (char)tolower(*Ptr);
									}

									Ptr++;
								}

								*this = In16;
								delete In16;
							}
							break;

						case Is32Bit_t: {
								char32_t	*	In32 = strdup32(Get32());
								char32_t	*	Ptr = In32;

								while (*Ptr != 0) {
									if (isupper(*Ptr)) {
										*Ptr = (char)tolower(*Ptr);
									}

									Ptr++;
								}

								*this = In32;
								delete In32;
							}
							break;

						case IsWBit_t: {
								wchar_t	*	InW = strdupW(GetW());
								wchar_t	*	Ptr = InW;

								while (*Ptr != 0) {
									if (isupper(*Ptr)) {
										*Ptr = (char)tolower(*Ptr);
									}

									Ptr++;
								}

								*this = InW;
								delete InW;
							}
							break;

					}
				}

				return;
			}

			String	*
			String::ToLower(const char * SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToLower();

				return (Results);
			}

			String	*
			String::ToLower(const char32_t * SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToLower();

				return (Results);
			}

			String	*
			String::ToLower(const String & SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToLower();

				return (Results);
			}

			void
			String::ToUpper()
			{
				/*@todo */

				return;
			}

			String	*
			String::ToUpper(const char * SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToUpper();

				return (Results);
			}

			String	*
			String::ToUpper(const char32_t * SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToUpper();

				return (Results);
			}

			String	*
			String::ToUpper(const String & SomeString)
			{
				String		*	Results = new String(SomeString);

				Results->ToUpper();

				return (Results);
			}

			void
			String::Print(File & Out) const
			{
				Out.Printf("%s", Get8());

				return;
			}

			void
			String::Print(FILE & Out) const
			{
				fprintf(&Out, "%s", Get8());

				return;
			}

			void
			String::Print(std::ostream & Out) const
			{
				Out << Get8();

				return;
			}

			uint64_t
			String::Write(File & Fp)
			{
				uint64_t		Results = 0;

				uint64_t		hLen = 0;
				uint64_t		nLen = 0;
				char			W = 0;

				if (_ROString) {
					W = _RO->Width;
					Results = Fp.Write(&W, 1);
					nLen = htonll(_RO->StrUnits);
					Results += Fp.Write(&nLen, sizeof(nLen));

					switch (W) {

						case Is8Bit_t:
							if (_RO->Str.RO8 != nullptr) {
								Results += Fp.Write(_RO->Str.RO8, _RO->StrUnits);
							}

							break;

						case Is16Bit_t:
							if (_RO->Str.RO16 != nullptr) {
								Results += Fp.Write(_RO->Str.RO16, _RO->StrUnits * 2);
							}

							break;

						case Is32Bit_t:
							if (_RO->Str.RO32 != nullptr) {
								Results += Fp.Write(_RO->Str.RO32, _RO->StrUnits * 4);
							}

							break;
					}

				} else {

					Get8();	// Make sure _Str8 is set.
					W = 1;
					Results = Fp.Write(&W, 1);
					hLen = strlen(_Str8);
					nLen = htonll(hLen);
					Results = Fp.Write(&nLen, sizeof(nLen));
					Results += Fp.Write(_Str8, hLen);
				}

				return (Results);
			}


			uint64_t
			String::Read(File & Fp)
			{
				uint64_t		Results = 0;

				uint64_t		hLen = 0;
				uint64_t		nLen = 0;
				char			Width;

				Results = Fp.Read(&Width, 1);
				Results += Fp.Read(&nLen, sizeof(nLen));
				hLen = (uint64_t)ntohll(nLen);

				char		*	bytes = new char[hLen * Width];

				Results = Fp.Read(bytes, hLen);

				switch (Width) {

					case Is8Bit_t:
						Append((char *)bytes);
						break;

					case Is16Bit_t:
						Append((char16_t *)bytes);
						break;

					case Is32Bit_t:
						Append((char32_t *)bytes);
						break;
				}

				delete bytes;

				return (Results);
			}


			bool_t
			String::xdr(XDR * xdrs)
			{
				bool_t			Results = false;

				if (xdrs != nullptr) {
					switch (xdrs->x_op) {

						case XDR_ENCODE: {
								const char	*	Str = Get8();

								Results = xdr_wrapstring(xdrs, (char **)&Str);
							}
							break;

						case XDR_DECODE: {
								char		*	Tmp = nullptr;

								Results = xdr_wrapstring(xdrs, &Tmp);
								*this = Tmp;
								free(Tmp);
							}
							break;

						case XDR_FREE: {
								Results = true;
							}
							break;
					}
				}

				return (Results);
			}

			bool_t
			String::xdr_String(XDR * xdrs,
			                   String * Pointer)
			{
				bool_t		Results = false;

				if (xdrs != nullptr && Pointer != nullptr) {
					Results = Pointer->xdr(xdrs);
				}

				return (Results);
			}

			bool_t
			String::xdr_String(XDR * xdrs,
			                   void * Pointer)
			{
				bool_t			Results = false;

				if (xdrs != nullptr && Pointer != nullptr) {
					String	*	Str = (String *)Pointer;

					Results = Str->xdr(xdrs);
				}

				return (Results);
			}

#ifdef USE_COMPRESS_SEG
			void
			String::_CompressSegments() const
			{

				std::vector<StringSeg *>::iterator	it;
				StringSeg	*	Seg1 = nullptr;
				StringSeg	*	Seg2 = nullptr;
				size_t			Max = _Segments.size();
				size_t			Offset = 0;

				bool			SameLang = false;
				bool			SameCharset = false;
				bool			SameType = false;

				if (Max > 0) {
					// Can't compare last to the one after last, so (Max -1).
					//
					Max--;

					while (Offset < Max) {
						SameLang = false;
						SameCharset = false;
						SameType = false;

						Seg1 = _Segments[Offset];
						Seg2 = _Segments[Offset + 1];

						if (Seg1->Type == Seg2->Type) {
							SameType = true;

							if (Seg1->Language == Seg2->Language) {
								SameLang = true;
							}

							if ((Seg1->Charset == Seg2->Charset)
							    || (Seg1->Charset == nullptr && Seg2->Charset == nullptr)
							    || (::strcmp(Seg1->Charset, Seg2->Charset) == 0)) {
								SameLang = true;
							}
						}

						// If same Type, Language, and Charset.
						//
						if (SameType && SameLang && SameCharset) {
							switch (Seg1->Type) {

								case Is8Bit_t:
									Seg1->Str.Utf8->append(*Seg2->Str.Utf8);
									break;

								case Is16Bit_t:
									Seg1->Str.Utf16->append(*Seg2->Str.Utf16);
									break;

								case Is32Bit_t:
									Seg1->Str.Utf32->append(*Seg2->Str.Utf32);
									break;
							}

							// Remove Seq2 from memory, and erase it from the vector.
							//
							delete _Segments[Offset];
							_Segments.erase(_Segments.begin() + Offset + 1);

						} else {
							// Go to next set.
							//
							Offset++;
						}
					}
				}

				return;
			}
#endif

			void
			String::_SetInputChanged()
			{
				if (_Str8 != nullptr) {
					StringCache::Remove(_Str8);
					_Str8 = nullptr;
				}

				if (_Str16 != nullptr) {
					StringCache::Remove(_Str16);
					_Str16 = nullptr;
				}

				if (_Str32 != nullptr) {
					StringCache::Remove(_Str32);
					_Str32 = nullptr;
				}

				if (_StrW != nullptr) {
					StringCache::Remove(_StrW);
					_StrW = nullptr;
				}

				_InputHasChanged = true;

				return;
			}

			/**
			 * Find the nTh character in the string.
			 *
			 * @param Str the string to search.
			 *
			 * @param nTh Which character (not octet and not
			 * character unit) we want.
			 *
			 * @Param Max The number of octets in Str.
			 *
			 * @param Len[out] The character width of the nTh
			 * character in character units.
			 * Set to 1000 to mean nTh is out of range.
			 */
			static size_t
			FindOffset(const char * const Str,
			           uint64_t nTh,
			           size_t Max,
			           uint64_t & Len)
			{
				size_t			Results = 0;

				if (nTh > 0 && Max > 0) {
					const char	*	Ptr = Str;
					uint64_t		Offset = 0;
					uint64_t		OOffset = 0;
					size_t		Inc = 0;

					while (*Ptr != 0) {
						Inc = String::CharacterUnits(Ptr);
						OOffset += Inc;
						Ptr += Inc;

						if (++Offset == nTh || OOffset > Max) {
							break;
						}
					}

					if (OOffset < Max) {
						Len = String::CharacterUnits(Ptr);

					} else {
						// Fake value meaning we hit end of string
						// and nTh is out of range.
						//
						Len = 1000;
					}
				}

				return (Results);
			}

			/**
			 * Find the nTh character in the string.
			 *
			 * @param Str the string to search.
			 *
			 * @param nTh Which character (not octet and not
			 * character unit) we want.
			 *
			 * @Param Max The number of octets in Str.
			 *
			 * @param Len[out] The character width of the nTh
			 * character in character units.
			 * Set to 1000 to mean nTh is out of range.
			 */
			static size_t
			FindOffset(const char16_t * const Str,
			           uint64_t nTh,
			           size_t Max,
			           uint64_t & Len)
			{
				size_t			Results = 0;

				if (nTh > 0) {
					const char16_t *	Ptr = Str;
					uint64_t		Offset = 0;
					uint64_t		OOffset = 0;
					size_t		Inc = 0;

					while (*Ptr != 0) {
						Inc = String::CharacterUnits(Ptr);
						Ptr += Inc;
						OOffset += (Inc * sizeof(char16_t));

						if (++Offset == nTh || OOffset > Max) {
							break;
						}
					}

					if (OOffset < Max) {
						Len = String::CharacterUnits(Ptr);

					} else {
						// Fake value meaning we hit end of string
						// and nTh is out of range.
						//
						Len = 1000;
					}
				}

				return (Results);
			}

			/**
			 * Find the nTh character in the string.
			 *
			 * @param Str the string to search.
			 *
			 * @param nTh Which character (not octet and not
			 * character unit) we want.
			 *
			 * @Param Max The number of octets in Str.
			 *
			 * @param Len[out] The character width of the nTh
			 * character in character units.
			 * Set to 1000 to mean nTh is out of range.
			 */
			static size_t
			FindOffset(const char32_t * const Str,
			           uint64_t nTh,
			           size_t Max,
			           uint64_t & Len)
			{
				size_t			Results = 0;

				if (nTh > 0) {
					const char32_t *	Ptr = Str;
					uint64_t		Offset = 0;
					uint64_t		OOffset = 0;
					size_t		Inc = 0;

					while (*Ptr != 0) {
						Inc = String::CharacterUnits(Ptr);
						Ptr += Inc;
						OOffset += (Inc * sizeof(char32_t));

						if (++Offset == nTh || OOffset > Max) {
							break;
						}
					}

					if (OOffset < Max) {
						Len = String::CharacterUnits(Ptr);

					} else {
						// Fake value meaning we hit end of string
						// and nTh is out of range.
						//
						Len = 1000;
					}
				}

				return (Results);
			}

			/**
			 * Find the nTh character in the string.
			 *
			 * @param Str the string to search.
			 *
			 * @param nTh Which character (not octet and not
			 * character unit) we want.
			 *
			 * @Param Max The number of octets in Str.
			 *
			 * @param Len[out] The character width of the nTh
			 * character in character units.
			 * Set to 1000 to mean nTh is out of range.
			 */
			static size_t
			FindOffset(const wchar_t * const Str,
			           uint64_t nTh,
			           size_t Max,
			           uint64_t & Len)
			{
				size_t			Results = 0;

				if (nTh > 0) {
					const wchar_t *	Ptr = Str;
					uint64_t		Offset = 0;
					uint64_t		OOffset = 0;
					size_t		Inc = 0;

					while (*Ptr != 0) {
						Inc = String::CharacterUnits(Ptr);
						Ptr += Inc;
						OOffset += (Inc * sizeof(wchar_t));

						if (++Offset == nTh || OOffset > Max) {
							break;
						}
					}

					if (OOffset < Max) {
						Len = String::CharacterUnits(Ptr);

					} else {
						// Fake value meaning we hit end of string
						// and nTh is out of range.
						//
						Len = 1000;
					}
				}

				return (Results);
			}

			uint32_t
			String::Item(uint64_t nTh) const
			{
				uint32_t	Results = 0;

				if (nTh < _RO->StrUnits) {

					switch (InputWidth()) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								const char	*	As8 = Get8();

								Results = As8[nTh];
							}
							break;

						case Is16Bit_t: {
								const char16_t	*	As16 = Get16();

								Results = As16[nTh];
							}
							break;

						case Is32Bit_t: {
								const char32_t	*	As32 = Get32();

								Results = As32[nTh];
							}
							break;

						case IsWBit_t: {
								const wchar_t	*	AsW = GetW();

								Results = AsW[nTh];
							}
							break;
					}
				}

				return (Results);
			}

			ROString	*
			String::operator[](uint64_t nThCharacter) const
			{
				ROString	*	Results = nullptr;

				uint64_t		Len = 0;
				size_t			Offset = 0;
				size_t			StrLen = 0;

				if (_ROString) {
					if (nThCharacter < _RO->StrUnits) {
						StrLen = _RO->StrUnits;

						switch (_RO->Width) {

							case IsUnknownBit_t:
								/*EMPTY*/
								break;

							case Is8Bit_t:
								Offset = FindOffset(_RO->Str.RO8, nThCharacter, StrLen,
								                    Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&_RO->Str.RO8[Offset], Len);
								}

								break;

							case Is16Bit_t:
								Offset = FindOffset(_RO->Str.RO16, nThCharacter, StrLen,
								                    Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&_RO->Str.RO16[Offset], Len);
								}

								break;

							case Is32Bit_t:
								Offset = FindOffset(_RO->Str.RO32, nThCharacter, StrLen,
								                    Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&_RO->Str.RO32[Offset], Len);
								}

								break;

							case IsWBit_t:
								Offset = FindOffset(_RO->Str.ROW, nThCharacter, StrLen,
								                    Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&_RO->Str.ROW[Offset], Len);
								}

								break;
						}
					}

				} else {
					switch (_OutputWidth) {

						case IsUnknownBit_t:
							/*EMPTY*/
							break;

						case Is8Bit_t: {
								const char	*	Str = Get8();

								StrLen = strlen(Str);

								Offset = FindOffset(Str, nThCharacter, StrLen, Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&Str[Offset], Len);
								}
							}
							break;

						case Is16Bit_t: {
								const char16_t	*	Str = Get16();

								StrLen = strlen(Str);

								Offset = FindOffset(Str, nThCharacter, StrLen, Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&Str[Offset], Len);
								}
							}
							break;

						case Is32Bit_t: {
								const char32_t	*	Str = Get32();

								StrLen = strlen(Str);

								Offset = FindOffset(Str, nThCharacter, StrLen, Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&Str[Offset], Len);
								}
							}
							break;

						case IsWBit_t: {
								const wchar_t	*	Str = GetW();

								StrLen = strlen(Str);

								Offset = FindOffset(Str, nThCharacter, StrLen, Len);

								// 1000 is fake value meaning we hit end of string
								// and nTh is out of range.
								//
								if (Len != 1000) {
									Results = new ROString(&Str[Offset], Len);
								}
							}
							break;
					}
				}

				return (Results);
			}

		}
	}
}

extern "C" {
	bool_t
	xdr_String(XDR * xdrs, String * Pointer)
	{
		bool_t		Results = false;

		if (xdrs != nullptr && Pointer != nullptr) {
			String	*	Str = (String *)Pointer;

			Results = Str->xdr(xdrs);
		}

		return (Results);
	}

	void
	ToUpper(char * Convert)
	{
		char	*	Ptr = Convert;

		while (*Ptr != '\0') {
			*Ptr = (char)toupper(*Ptr);
			Ptr++;
		}

		return;
	}

	void
	ToLower(char * Convert)
	{
		char	*	Ptr = Convert;

		while (*Ptr != '\0') {
			*Ptr = (char)tolower(*Ptr);
			Ptr++;
		}

		return;
	}

}
