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
#include <SaS/String/StringCache.hpp>

#ifdef USE_ICONV
#ifdef SunOS
#include "/usr/include/iconv.h"
#else
#include <iconv.h>
#endif
#endif

#ifdef USE_ICU
#include <unicode/ucnv_err.h>
#include <unicode/uenum.h>
#include <unicode/localpointer.h>
#include <unicode/ucnv.h>
#endif

#include <langinfo.h>

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {
			static pthread_mutex_t	OnceMutex =
			    PTHREAD_MUTEX_INITIALIZER;

			const char * const	Utf8_s = "UTF-8";
			const char * const	Utf16_s = "UTF-16";
			const char * const	Utf16LE_s = "UTF-16LE";
			const char * const	Utf16BE_s = "UTF-16-BE";
			const char * const	Utf32_s = "UTF-32";
			const char * const	Utf32LE_s = "UTF-32LE";
			const char * const	Utf32BE_s = "UTF-32BE";

			locale_t			Default8BitLocale = 0;
			locale_t			Default16BitLocale = 0;
			locale_t			Default32BitLocale = 0;
			locale_t			DefaultWBitLocale = 0;

			locale_t			Current8BitLocale = 0;
			locale_t			Current16BitLocale = 0;
			locale_t			Current32BitLocale = 0;
			locale_t			CurrentWBitLocale = 0;

			const char * const	Default8BitCharset = strdup(Utf8_s);
			const char * const	Default16BitCharset = strdup(Utf16LE_s);
			const char * const	Default32BitCharset = strdup(Utf32LE_s);

#if __SIZEOF_WCHAR_T__ == 2
			const char * const	DefaultWBitCharset = strdup(Utf16LE_s);
#elif __SIZEOF_WCHAR_T__ == 4
			const char * const	DefaultWBitCharset = strdup(Utf32LE_s);
#else
			ERROR What size is WCHAR_T;
#endif

			const char	*	Current8BitCharset = strdup(
			        Default8BitCharset);
			const char	*	Current16BitCharset = strdup(
			        Default16BitCharset);
			const char	*	Current32BitCharset = strdup(
			        Default32BitCharset);
			const char	*	CurrentWBitCharset = strdup(
			        DefaultWBitCharset);

			const CharacterUnitWidth_e	Default8BitWidth = Is8Bit_t;
			const CharacterUnitWidth_e	Default16BitWidth = Is16Bit_t;
			const CharacterUnitWidth_e	Default32BitWidth = Is32Bit_t;
			const CharacterUnitWidth_e	DefaultWBitWidth = IsWBit_t;

			const CharacterUnitWidth_e	Current8BitWidth =
			    Default8BitWidth;
			const CharacterUnitWidth_e	Current16BitWidth =
			    Default16BitWidth;
			const CharacterUnitWidth_e	Current32BitWidth =
			    Default32BitWidth;
			const CharacterUnitWidth_e	CurrentWBitWidth =
			    DefaultWBitWidth;

			struct IconvCache {

				/**
				 * IconvCache - Current Constructor.
				 */
				IconvCache();

				/**
				 * IconvCache - Destructor.
				 */
				~IconvCache();

				/**
				 * Open or find match.
				 *
				 * @param InCSet The input charset.
				 *
				 * @param OutCSet The output charset.
				 *
				 * @return The result of iconv_open().
				 */
				static std::vector<IconvCache *>::iterator Open(
				    const char * InCSet, const char * OutCSet);

				/**
				 * Find match.
				 *
				 * @param InCSet The input charset.
				 *
				 * @param OutCSet The output charset.
				 *
				 * @return The result of iconv_open().
				 */
				static std::vector<IconvCache *>::iterator Find(
				    const char * InCSet, const char * OutCSet);


#ifdef USE_ICONV
				::iconv_t		Fd;
#endif
#ifdef USE_ICU
				UConverter	*	InConverter;
				UConverter	*	OutConverter;
#endif
				const char	 *	InCharset;
				const char	 * 	OutCharset;


				/**
				 * List of open objects.
				 */
				static std::vector<IconvCache *>	Existing;
			};

			typedef std::vector<IconvCache *>::iterator	iconv_t;

			std::vector<IconvCache *>	IconvCache::Existing;

			IconvCache::IconvCache()
			{
#ifdef USE_ICONV
				Fd = (::iconv_t) -1;
#endif
#ifdef USE_ICU
				InConverter = nullptr;
				OutConverter = nullptr;
#endif
				InCharset = nullptr;
				OutCharset = nullptr;

				return;
			}

			IconvCache::~IconvCache()
			{
#ifdef USE_ICONV

				if (Fd != (::iconv_t) -1) {
					iconv_close(Fd);
					Fd = (::iconv_t) -1;
				}

#endif
#ifdef USE_ICU

				if (InConverter != nullptr) {
					ucnv_close(InConverter);
					InConverter = nullptr;
				}

				if (OutConverter != nullptr) {
					ucnv_close(OutConverter);
					OutConverter = nullptr;
				}

#endif

				if (InCharset != nullptr) {
					delete InCharset;
					InCharset = nullptr;
				}

				if (OutCharset != nullptr) {
					delete OutCharset;
					OutCharset = nullptr;
				}

				return;
			}

			std::vector<IconvCache *>::iterator
			IconvCache::Find(const char * InCSet,  const char * OutCSet)
			{
				std::vector<IconvCache *>::iterator	Results =
				    Existing.end();

				std::vector<IconvCache *>::iterator	it;
				const IconvCache	*	Entry = nullptr;

				for (it = Existing.begin(); it != Existing.end(); it++) {
					Entry = *it;

					if (Entry != nullptr) {
						if (::strcmp(InCSet, Entry->InCharset) == 0) {
							if (::strcmp(OutCSet, Entry->OutCharset) == 0) {
#ifdef USE_ICONV

								if (Entry->Fd != (::iconv_t) -1) {
									Results = it;
									break;
								}

#endif
#ifdef USE_ICU

								if (Entry->InConverter != nullptr
								    && Entry->OutConverter != nullptr) {
									Results = it;
									break;
								}

#endif
							}
						}
					}
				}

				return (Results);
			}

			std::vector<IconvCache *>::iterator
			IconvCache::Open(const char * InCSet,  const char * OutCSet)
			{
				iconv_t		Results = Existing.end();

				if (pthread_mutex_trylock(&OnceMutex) == 0) {
					Current32BitLocale = Current16BitLocale = Current8BitLocale
					                     = duplocale(LC_GLOBAL_LOCALE);
				}

				if (InCSet != nullptr && OutCSet != nullptr) {
					std::vector<IconvCache *>::iterator	it = Find(InCSet,
					        OutCSet);
					IconvCache	*	Entry = nullptr;
					bool			DoOpen = false;

					if (it != Existing.end()) {
						Entry = *it;
#ifdef USE_ICONV

						if (Entry->Fd == (::iconv_t) -1) {
							DoOpen = true;

						} else {
							Results = it;
						}

#endif
#ifdef USE_ICU

						if (Entry->InConverter == nullptr
						    || Entry->OutConverter == nullptr) {
							DoOpen = true;

						} else {
							Results = it;
						}

#endif
					}

					if (DoOpen || it == Existing.end()) {
						if (!DoOpen) {
							Entry = new IconvCache();
						}

#ifdef USE_ICONV
						Entry->Fd = iconv_open(OutCSet, InCSet);

						if (Entry->Fd != (::iconv_t) -1) {
							Entry->InCharset = strdup(InCSet);
							Entry->OutCharset = strdup(OutCSet);
							Existing.push_back(Entry);
							Results = std::prev(Existing.end());
						}

#endif
#ifdef USE_ICU
						UErrorCode		Err = U_ZERO_ERROR;

						Entry->InConverter = ucnv_open(InCSet, &Err);

						if (Entry->InConverter != nullptr && Err == U_ZERO_ERROR) {
							Entry->OutConverter = ucnv_open(OutCSet, &Err);

							if (Entry->OutConverter != nullptr && Err == U_ZERO_ERROR) {
								Entry->InCharset = strdup(InCSet);
								Entry->OutCharset = strdup(OutCSet);
								Existing.push_back(Entry);
								Results = std::prev(Existing.end());
							}
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset8To8(const char * const FromCharset,
			                    const char * const From,
			                    size_t FromUnits,
			                    const char * const ToCharset,
			                    char *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current8BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current8BitCharset;
					}

					if ((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0)) {
						To = strdup8(From, FromUnits);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen;
							size_t		OutLeft = (InLeft * 4) + sizeof(char);
							const char * const	InPtr = From;
							char	*	OutStr = new char[OutLeft];
							char	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t	Err = iconv(Cache->Fd,
							                    (char **)&InPtr, &InLeft,
							                    &OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdup(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               &OutPtr, OutPtr + OutLeft,
							               (const char **)&InPtr, InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdup(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			bool
			String::Charset8To16(const char * const FromCharset,
			                     const char * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char16_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current8BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current16BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen;
						size_t		OutLeft = (InLeft * 4) + sizeof(char16_t);
						const char * const	InPtr = From;
						char16_t	*	OutStr = new char16_t[OutLeft];
						char16_t	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup16(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup16(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset8To32(const char * const FromCharset,
			                     const char * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char32_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current8BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen;
						size_t		OutLeft = (InLeft * 4) + sizeof(char32_t);
						const char * const	InPtr = From;
						char32_t	*	OutStr = new char32_t[OutLeft];
						char32_t	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup32(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup32(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset8ToW(const char * const FromCharset,
			                    const char * const From,
			                    size_t FromUnits,
			                    const char * const ToCharset,
			                    wchar_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current8BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = CurrentWBitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen;
						size_t		OutLeft = (InLeft * 4) + sizeof(wchar_t);
						const char * const	InPtr = From;
						wchar_t	*	OutStr = new wchar_t[OutLeft];
						wchar_t	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdupW(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdupW(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			//
			bool
			String::Charset16To8(const char * const FromCharset,
			                     const char16_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current16BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current8BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen * sizeof(char16_t);
						size_t		OutLeft = (InLeft * 4) + sizeof(char);
						const char16_t * const	InPtr = From;
						char	*	OutStr = new char[OutLeft];
						char	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup8(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               &OutPtr, OutPtr + OutLeft,
						               (const char **)&From, (const char *)From + InLen,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset16To16(const char * const FromCharset,
			                      const char16_t * const From,
			                      size_t FromUnits,
			                      const char * const ToCharset,
			                      char16_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current16BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current16BitCharset;
					}

					if ((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0)) {
						To = strdup16(From, FromUnits);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(char16_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(char16_t);
							const char16_t * const	InPtr = From;
							char16_t	*	OutStr = new char16_t[OutLeft];
							char16_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdup16(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdup16(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			bool
			String::Charset16To32(const char * const FromCharset,
			                      const char16_t * const From,
			                      size_t FromUnits,
			                      const char * const ToCharset,
			                      char32_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current16BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen * sizeof(char16_t);
						size_t		OutLeft = (InLeft * 4) + sizeof(char32_t);
						const char16_t * const	InPtr = From;
						char32_t	*	OutStr = new char32_t[OutLeft];
						char32_t	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup32(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, (char *)InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup32(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset16ToW(const char * const FromCharset,
			                     const char16_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     wchar_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current16BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					if (((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0))
					    && (__SIZEOF_WCHAR_T__ == 2)) {
						To = ::wcsdup((wchar_t *)From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(char16_t);
							size_t		OutLeft = (InLeft * sizeof(char16_t)) + sizeof(
							                          wchar_t);
							const char16_t * const	InPtr = From;
							wchar_t	*	OutStr = new wchar_t[OutLeft];
							wchar_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			//
			bool
			String::Charset32To8(const char * const FromCharset,
			                     const char32_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current8BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen * sizeof(char32_t);
						size_t		OutLeft = (InLeft * 4) + sizeof(char);
						const char32_t * const	InPtr = From;
						char	*	OutStr = new char[OutLeft];
						char	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup8(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, (char *)InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset32To16(const char * const FromCharset,
			                      const char32_t * const From,
			                      size_t FromUnits,
			                      const char * const ToCharset,
			                      char16_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current16BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen  * sizeof(char32_t);
						size_t		OutLeft = (InLeft * 4) + sizeof(char16_t);
						const char32_t * const	InPtr = From;
						char16_t	*	OutStr = new char16_t[OutLeft];
						char16_t	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup16(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, (char *)InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup16(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::Charset32To32(const char * const FromCharset,
			                      const char32_t * const From,
			                      size_t FromUnits,
			                      const char * const ToCharset,
			                      char32_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					if (((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0))
					    && ( __SIZEOF_WCHAR_T__ == 4)) {
						To = (char32_t *)::wcsdup((wchar_t *)From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(char32_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(char32_t);
							const char32_t * const	InPtr = From;
							char32_t	*	OutStr = new char32_t[OutLeft];
							char32_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdup32(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdup32(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			bool
			String::Charset32ToW(const char * const FromCharset,
			                     const char32_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     wchar_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = CurrentWBitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = CurrentWBitCharset;
					}

					if (((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0))
					    && (__SIZEOF_WCHAR_T__ == 4)) {
						To = ::wcsdup((wchar_t *)From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(wchar_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(wchar_t);
							const char32_t * const	InPtr = From;
							wchar_t	*	OutStr = new wchar_t[OutLeft];
							wchar_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			//
			bool
			String::CharsetWTo8(const char * const FromCharset,
			                    const wchar_t * const From,
			                    size_t FromUnits,
			                    const char * const ToCharset,
			                    char *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current8BitCharset;
					}

					iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

					if (Fd != IconvCache::Existing.end()) {
						ssize_t		InLen = FromUnits;
						size_t		InLeft = InLen * sizeof(wchar_t);
						size_t		OutLeft = (InLeft * sizeof(wchar_t)) + sizeof(char);
						const wchar_t * const	InPtr = From;
						char	*	OutStr = new char[OutLeft];
						char	*	OutPtr = OutStr;
						IconvCache *	Cache = *Fd;

						memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
						ssize_t             Err = iconv(Cache->Fd,
						                                (char **)&InPtr, &InLeft,
						                                (char **)&OutPtr, &OutLeft);

						if (Err != (ssize_t) -1 && OutStr != nullptr) {
							To = strdup8(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
#ifdef USE_ICU
						UErrorCode	Err = U_ZERO_ERROR;

						ucnv_convertEx(Cache->OutConverter,
						               Cache->InConverter,
						               (char **)&OutPtr, (char *)OutPtr + OutLeft,
						               (const char **)&InPtr, (char *)InPtr + InLeft,
						               nullptr, nullptr, nullptr, nullptr,
						               true, true,
						               &Err);

						if (Err == U_ZERO_ERROR) {
							To = strdup(OutStr);
							Results = true;
							delete OutStr;
						}

#endif
					}
				}

				return (Results);
			}

			bool
			String::CharsetWTo16(const char * const FromCharset,
			                     const wchar_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char16_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current16BitCharset;
					}

					if (((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0))
					    && (__SIZEOF_WCHAR_T__ == 2)) {
						To = (char16_t *)::wcsdup(From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(wchar_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(char16_t);
							const wchar_t * const	InPtr = From;
							char16_t	*	OutStr = new char16_t[OutLeft];
							char16_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdup16(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdup16(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			bool
			String::CharsetWTo32(const char * const FromCharset,
			                     const wchar_t * const From,
			                     size_t FromUnits,
			                     const char * const ToCharset,
			                     char32_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					if (((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0))
					    && (__SIZEOF_WCHAR_T__ == 4)) {
						To = (char32_t *)::wcsdup(From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(wchar_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(char32_t);
							const wchar_t * const	InPtr = From;
							char32_t	*	OutStr = new char32_t[OutLeft];
							char32_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdup32(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdup32(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			bool
			String::CharsetWToW(const char * const FromCharset,
			                    const wchar_t * const From,
			                    size_t FromUnits,
			                    const char * const ToCharset,
			                    wchar_t *& To)
			{
				bool			Results = false;

				const char	*	FromCs = FromCharset;
				const char	*	ToCs = ToCharset;

				if (From != nullptr) {
					if (FromUnits == 0) {
						FromUnits = strlen(From);
					}

					if (FromCharset == nullptr) {
						FromCs = Current32BitCharset;
					}

					if (ToCharset == nullptr) {
						ToCs = Current32BitCharset;
					}

					if ((FromCs == ToCs) || (strcasecmp(FromCs, ToCs) == 0)) {
						To = ::wcsdup(From);
						Results = true;

					} else {
						iconv_t	Fd = IconvCache::Open(FromCs, ToCs);

						if (Fd != IconvCache::Existing.end()) {
							ssize_t		InLen = FromUnits;
							size_t		InLeft = InLen * sizeof(wchar_t);
							size_t		OutLeft = (InLeft * 4) + sizeof(wchar_t);
							const wchar_t * const	InPtr = From;
							wchar_t	*	OutStr = new wchar_t[OutLeft];
							wchar_t	*	OutPtr = OutStr;
							IconvCache *	Cache = *Fd;

							memset(OutStr, 0, OutLeft);
#ifdef USE_ICONV
							ssize_t             Err = iconv(Cache->Fd,
							                                (char **)&InPtr, &InLeft,
							                                (char **)&OutPtr, &OutLeft);

							if (Err != (ssize_t) -1 && OutStr != nullptr) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
#ifdef USE_ICU
							UErrorCode	Err = U_ZERO_ERROR;

							ucnv_convertEx(Cache->OutConverter,
							               Cache->InConverter,
							               (char **)&OutPtr, (char *)OutPtr + OutLeft,
							               (const char **)&InPtr, (char *)InPtr + InLeft,
							               nullptr, nullptr, nullptr, nullptr,
							               true, true,
							               &Err);

							if (Err == U_ZERO_ERROR) {
								To = strdupW(OutStr);
								Results = true;
								delete OutStr;
							}

#endif
						}
					}
				}

				return (Results);
			}

			String	*
			String::ToCharset(const char * ToCharset,
			                  CharacterUnitWidth_e Width) const
			{
				String		*	Results = new String();

				// Search through all segments, and convert them
				// to ToCharset.
				//
				std::vector<StringSeg *>::const_iterator	It;
				StringSeg	*	InSeg = nullptr;
				StringSeg	*	OutSeg = nullptr;
				const char	*	CSName  = nullptr;

				for (It = _Segments.begin(); It != _Segments.end(); It++) {
					InSeg = *It;

					if (InSeg != nullptr) {

						CSName = Charset(InSeg->Locale);

						if (strcmp(ToCharset, CSName) == 0) {
							OutSeg = new StringSeg(*InSeg);
							Results->_Segments.push_back(OutSeg);

						} else {
							switch (InSeg->Width) {

								case IsUnknownBit_t:
									/*EMPTY*/
									break;

								case Is8Bit_t: {
										switch (Width) {

											case IsUnknownBit_t:
												/*EMPTY*/
												break;

											case Is8Bit_t: {
													// From 8 to 8
													//
													char	*	Out = nullptr;

													if (String::Charset8To8(nullptr,
													                        Get8(),
													                        ToCharset,
													                        Out)) {

														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is16Bit_t: {
													// From 8 to 16
													//
													char16_t	*	Out = nullptr;

													if (String::Charset8To16(nullptr,
													                         Get8(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is32Bit_t: {
													// From 8 to 32
													//
													char32_t	*	Out = nullptr;

													if (String::Charset8To32(nullptr,
													                         Get8(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case IsWBit_t: {
													// From 8 to W
													//
													wchar_t	*	Out = nullptr;

													if (String::Charset8ToW(nullptr,
													                        Get8(),
													                        ToCharset,
													                        Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;
										}
									}
									break;

								case Is16Bit_t: {
										switch (Width) {

											case IsUnknownBit_t:
												/*EMPTY*/
												break;

											case Is8Bit_t: {
													// From 16 to 8
													//
													char	*	Out = nullptr;

													if (String::Charset16To8(nullptr,
													                         Get16(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is16Bit_t: {
													// From 16 to 16
													//
													char16_t	*	Out = nullptr;

													if (String::Charset16To16(nullptr,
													                          Get16(),
													                          nullptr,
													                          Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is32Bit_t: {
													// From 16 to 32
													//
													char32_t	*	Out = nullptr;

													if (String::Charset16To32(nullptr,
													                          Get16(),
													                          ToCharset,
													                          Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case IsWBit_t: {
													// From 16 to W
													//
													wchar_t	*	Out = nullptr;

													if (String::Charset16ToW(nullptr,
													                         Get16(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;
										}
									}
									break;

								case Is32Bit_t: {
										switch (Width) {

											case IsUnknownBit_t:
												/*EMPTY*/
												break;

											case Is8Bit_t: {
													// From 32 to 8
													//
													char	*	Out = nullptr;

													if (String::Charset32To8(nullptr,
													                         Get32(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is16Bit_t: {
													// From 32 to 16
													//
													char16_t	*	Out = nullptr;

													if (String::Charset32To16(nullptr,
													                          Get32(),
													                          ToCharset,
													                          Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is32Bit_t: {
													// From 32 to 32
													//
													char32_t	*	Out = nullptr;

													if (String::Charset32To32(nullptr,
													                          Get32(),
													                          ToCharset,
													                          Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case IsWBit_t: {
													// From 32 to W
													//
													wchar_t	*	Out = nullptr;

													if (String::Charset32ToW(nullptr,
													                         Get32(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;
										}
									}
									break;

								case IsWBit_t: {
										switch (Width) {

											case IsUnknownBit_t:
												/*EMPTY*/
												break;

											case Is8Bit_t: {
													// From W to 8
													//
													char	*	Out = nullptr;

													if (String::CharsetWTo8(nullptr,
													                        GetW(),
													                        ToCharset,
													                        Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is16Bit_t: {
													// From W to 16
													//
													char16_t	*	Out = nullptr;

													if (String::CharsetWTo16(nullptr,
													                         GetW(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case Is32Bit_t: {
													// From W to 32
													//
													char32_t	*	Out = nullptr;

													if (String::CharsetWTo32(nullptr,
													                         GetW(),
													                         ToCharset,
													                         Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;

											case IsWBit_t: {
													// From W to W
													//
													wchar_t	*	Out = nullptr;

													if (String::CharsetWToW(nullptr,
													                        GetW(),
													                        ToCharset,
													                        Out)) {
														if (Out != nullptr) {
															OutSeg = new StringSeg(Out);
															Results->_Segments.push_back(OutSeg);
															delete Out;
														}
													}
												}
												break;
										}
									}
									break;
							}

						}
					}
				}

				return (Results);
			}

		}
	}
}
