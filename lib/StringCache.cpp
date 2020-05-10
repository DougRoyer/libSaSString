//
// BEGIN_COPYRIGHT
//
// Copyright (C) 2010-2017,2020 Software and Services LLC, All Rights Reserved.
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
// THIS  DOCUMENT  AND  THE  INFORMATION  CONTAINED  HEREIN  IS
// PROVIDED  ON  AN "AS IS" BASIS AND Software and Services LLC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,  INCLUDING  BUT
// NOT  LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN  WILL  NOT  INFRINGE  ANY  RIGHTS  OR   ANY   IMPLIED
// WARRANTIES  OF  MERCHANTABILITY  OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// THIS SOURCE CODE IS UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
//
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//
#include <SaS/Common/TreeSearch.hpp>
#include <SaS/String/StringCache.hpp>
#include <SaS/Common/File.hpp>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#if defined(XSH4_2) && !defined(WIN32)
#define SAS_FOO	_POSIX_C_SOURCE
#undef _POSIX_C_SOURCE
#include <widec.h>
#define _POSIX_C_SOURCE SAS_FOO
#undef SAS_FOO
#endif

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			pthread_mutex_t	StringCacheOnceMutex =
			    PTHREAD_MUTEX_INITIALIZER;


#ifdef SunOS
			wchar_t	*
			wcsdup(wchar_t * orig)
			{
				size_t		origLen = wcslen(orig);

				wchar_t	*	results = (wchar_t *)malloc((origLen + 1) * sizof(
				        wchar_t));

				wcscpy(results, orig);

				return (results);
			}
#endif

			static const char		*		empty8 = "";
			static const char16_t	*	empty16 = u"";
			static const char32_t	*	empty32 = U"";
			static const wchar_t	*	emptyW = L"";

			class StringCacheDatum8
				: public instance<StringCacheDatum8> {

				public:

					StringCacheDatum8() {
						value = nullptr;

						return;
					}

					virtual
					~StringCacheDatum8() {
						if (getInstance() == 1) {
							if (value != nullptr) {
								delete value;
								value = nullptr;
							}
						}

						return;
					}

					const char		*		value;
					static uint64_t		itemCount;
					static File		*		printFile;
			};

			class StringCacheDatum16
				: public instance<StringCacheDatum16> {

				public:

					StringCacheDatum16() {
						value = nullptr;

						return;
					}

					virtual
					~StringCacheDatum16() {
						if (getInstance() == 1) {
							if (value != nullptr) {
								delete value;
								value = nullptr;
							}
						}

						return;
					}

					const char16_t	*	value;
					static uint64_t		itemCount;
					static File		*		printFile;
			};

			class StringCacheDatum32
				: public instance<StringCacheDatum32> {

				public:

					StringCacheDatum32() {
						value = nullptr;

						return;
					}

					virtual
					~StringCacheDatum32() {
						if (getInstance() == 1) {
							if (value != nullptr) {
								delete value;
								value = nullptr;
							}
						}

						return;
					}

					const char32_t	*	value;
					static uint64_t		itemCount;
					static File		*		printFile;
			};

			class StringCacheDatumW
				: public instance<StringCacheDatumW> {

				public:

					StringCacheDatumW() {
						value = nullptr;

						return;
					}

					virtual
					~StringCacheDatumW() {
						if (getInstance() == 1) {
							if (value != nullptr) {
								delete value;
								value = nullptr;
							}
						}

						return;
					}

					const wchar_t		*	value;
					static uint64_t		itemCount;
					static File		*		printFile;
			};

			static int	cmp(const StringCacheDatum8 * One,
			                const StringCacheDatum8 * Two);

			static int	cmp(const StringCacheDatum16 * One,
			                const StringCacheDatum16 * Two);

			static int	cmp(const StringCacheDatum32 * One,
			                const StringCacheDatum32 * Two);

			static int	cmp(const StringCacheDatumW * One,
			                const StringCacheDatumW * Two);

			class StringCacheTree8
				: public Tree_t<StringCacheDatum8> {

				public:

					/**
					 * StringCacheTree8 - Default Constructor.
					 */
					StringCacheTree8();

					/**
					 * StringCacheTree8 - Destructor.
					 */
					~StringCacheTree8();

					// Should be power of 2 value (2^n).
					//
#define STRING_KEYS		ULONGLONG_MAX

					// Tree of StringCacheDatum8.
					//
					static Tree_t<StringCacheDatum8>	*	root;
			};

			class StringCacheTree16
				: public Tree_t<StringCacheDatum16> {

				public:

					/**
					 * StringCacheTree16 - Default Constructor.
					 */
					StringCacheTree16();

					/**
					 * StringCacheTree16 - Destructor.
					 */
					~StringCacheTree16();

					// Should be power of 2 value (2^n).
					//
#define STRING_KEYS		ULONGLONG_MAX

					// Tree of StringCacheDatum16.
					//
					static Tree_t<StringCacheDatum16>	*	root;
			};

			class StringCacheTree32
				: public Tree_t<StringCacheDatum32> {

				public:

					/**
					 * StringCacheTree32 - Default Constructor.
					 */
					StringCacheTree32();

					/**
					 * StringCacheTree32 - Destructor.
					 */
					~StringCacheTree32();

					// Should be power of 2 value (2^n).
					//
#define STRING_KEYS		ULONGLONG_MAX

					// Tree of StringCacheDatum32.
					//
					static Tree_t<StringCacheDatum32>	*	root;
			};

			class StringCacheTreeW
				: public Tree_t<StringCacheDatumW> {

				public:

					/**
					 * StringCacheTreeW - Default Constructor.
					 */
					StringCacheTreeW();

					/**
					 * StringCacheTreeW - Destructor.
					 */
					~StringCacheTreeW();

					// Should be power of 2 value (2^n).
					//
#define STRING_KEYS		ULONGLONG_MAX

					// Tree of StringCacheDatumW.
					//
					static Tree_t<StringCacheDatumW>	*	root;
			};

			Tree_t<StringCacheDatum8>	*	StringCacheTree8::root =
			    nullptr;
			Tree_t<StringCacheDatum16>	*	StringCacheTree16::root =
			    nullptr;
			Tree_t<StringCacheDatum32>	*	StringCacheTree32::root =
			    nullptr;
			Tree_t<StringCacheDatumW>	*	StringCacheTreeW::root =
			    nullptr;

			uint64_t		StringCacheDatum8::itemCount = 0;
			uint64_t		StringCacheDatum16::itemCount = 0;
			uint64_t		StringCacheDatum32::itemCount = 0;
			uint64_t		StringCacheDatumW::itemCount = 0;

			File		*	StringCacheDatum8::printFile = nullptr;
			File		*	StringCacheDatum16::printFile = nullptr;
			File		*	StringCacheDatum32::printFile = nullptr;
			File		*	StringCacheDatumW::printFile = nullptr;

			int
			cmp(const StringCacheDatum8 * dOne,
			    const StringCacheDatum8 * dTwo)
			{
				int				results = -1;

				if (dOne == dTwo) {
					results = 0;

				} else {

					if (dOne->value != nullptr && dTwo->value != nullptr) {
						results = strcmp(dOne->value, dTwo->value);

					} else if (dOne->value == nullptr
					           && dTwo->value != nullptr) {
						results = 1;

					} else if (dOne->value != nullptr
					           && dTwo->value == nullptr) {
						results = -1;
					}
				}

				return (results);
			}

			int
			cmp(const StringCacheDatum16 * dOne,
			    const StringCacheDatum16 * dTwo)
			{
				int				results = -1;

				if (dOne == dTwo) {
					results = 0;

				} else {

					if (dOne->value != nullptr && dTwo->value != nullptr) {
						results = String::strcmp(dOne->value, dTwo->value);

					} else if (dOne->value == nullptr
					           && dTwo->value != nullptr) {
						results = 1;

					} else if (dOne->value != nullptr
					           && dTwo->value == nullptr) {
						results = -1;
					}
				}

				return (results);
			}

			int
			cmp(const StringCacheDatum32 * dOne,
			    const StringCacheDatum32 * dTwo)
			{
				int				results = -1;

				if (dOne == dTwo) {
					results = 0;

				} else {

					if (dOne->value != nullptr && dTwo->value != nullptr) {
						results = String::strcmp(dOne->value, dTwo->value);

					} else if (dOne->value == nullptr
					           && dTwo->value != nullptr) {
						results = 1;

					} else if (dOne->value != nullptr
					           && dTwo->value == nullptr) {
						results = -1;
					}
				}

				return (results);
			}

			int
			cmp(const StringCacheDatumW * dOne,
			    const StringCacheDatumW * dTwo)
			{
				int				results = -1;

				if (dOne == dTwo) {
					results = 0;

				} else {

					if (dOne->value != nullptr && dTwo->value != nullptr) {
						results = String::strcmp(dOne->value, dTwo->value);

					} else if (dOne->value == nullptr
					           && dTwo->value != nullptr) {
						results = 1;

					} else if (dOne->value != nullptr
					           && dTwo->value == nullptr) {
						results = -1;
					}
				}

				return (results);
			}

			// DO NOT EXPORT
			//
			void
			StringCache_Init()
			{
				if (StringCacheTree8::root == nullptr) {
					StringCacheTree8::root = new Tree_t<StringCacheDatum8>();
				}

				if (StringCacheTree16::root == nullptr) {
					StringCacheTree16::root = new Tree_t<StringCacheDatum16>();
				}

				if (StringCacheTree32::root == nullptr) {
					StringCacheTree32::root = new Tree_t<StringCacheDatum32>();
				}

				if (StringCacheTreeW::root == nullptr) {
					StringCacheTreeW::root = new Tree_t<StringCacheDatumW>();
				}

				return;
			}


			StringCache::StringCache()
			{
				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				return;
			}

			StringCache::StringCache(const char * str, size_t Len)
			{
				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				Add(str, Len);

				return;
			}

			StringCache::StringCache(const char16_t * str, size_t Len)
			{
				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				Add(str, Len);

				return;
			}

			StringCache::StringCache(const char32_t * str, size_t Len)
			{
				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				Add(str, Len);

				return;
			}

			StringCache::StringCache(const wchar_t * str, size_t Len)
			{
				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				Add(str, Len);

				return;
			}

			StringCache::~StringCache()
			{
				/*EMPTY*/

				return;
			}

			const char	*
			StringCache::Add(const char * str, size_t Len)
			{
				const char	*	Results = nullptr;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty8;
				}

				StringCacheDatum8	*	datum = new StringCacheDatum8;
				StringCacheDatum8	**	datumPP = nullptr;
				StringCacheDatum8	*	datumP = nullptr;

				const char	*	Tmp = str;

				if (Len > 0) {
					Tmp = String::strdup8(str, Len);
				}

				datum->value = Tmp;

				datumPP
				    = Tree_t<StringCacheDatum8>::Search(datum,
				                                        &StringCacheTree8::root,
				                                        cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP != datum) {
							datumP->incInstance();
							datum->value = nullptr;	// We had only copied the pointer.
							delete datum;

						} else {
							if (Len == 0) {
								datum->value = strdup(str);
							}
						}
					}

					Results = datumP->value;
				}

				StringCacheDatum8::itemCount++;

				return (Results);
			}

			const char16_t	*
			StringCache::Add(const char16_t * str, size_t Len)
			{
				const char16_t	*	Results = nullptr;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty16;
				}

				StringCacheDatum16	*	datum = new StringCacheDatum16;
				StringCacheDatum16	**	datumPP = nullptr;
				StringCacheDatum16	*	datumP = nullptr;

				const char16_t	*	Tmp = str;

				if (Len > 0) {
					Tmp = String::strdup16(str, Len);
				}

				datum->value = Tmp;

				datumPP
				    = Tree_t<StringCacheDatum16>::Search(datum,
				            &StringCacheTree16::root,
				            cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP != datum) {
							datumP->incInstance();
							datum->value = nullptr;	// We had only copied the pointer.
							delete datum;

						} else {
							if (Len == 0) {
								datum->value = String::strdup16(str);
							}
						}
					}

					Results = datumP->value;
				}

				StringCacheDatum16::itemCount++;

				return (Results);
			}

			const char32_t	*
			StringCache::Add(const char32_t * str, size_t Len)
			{
				const char32_t	* Results = nullptr;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty32;
				}

				StringCacheDatum32	*	datum = new StringCacheDatum32;
				StringCacheDatum32	**	datumPP = nullptr;
				StringCacheDatum32	*	datumP = nullptr;

				const char32_t	*	Tmp = str;

				if (Len > 0) {
					Tmp = String::strdup32(str, Len);
				}

				datum->value = Tmp;

				datumPP
				    = Tree_t<StringCacheDatum32>::Search(datum,
				            &StringCacheTree32::root,
				            cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP != datum) {
							datumP->incInstance();
							datum->value = nullptr;	// We had only copied the pointer.
							delete datum;

						} else {
							if (Len == 0) {
								datum->value = String::strdup32(str);
							}
						}
					}

					Results = datumP->value;
				}

				StringCacheDatum32::itemCount++;

				return (Results);
			}

			const wchar_t	*
			StringCache::Add(const wchar_t * str, size_t Len)
			{
				const wchar_t	* Results = nullptr;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				const wchar_t	*	Tmp = str;

				if (str == nullptr) {
					str = emptyW;
				}

				StringCacheDatumW	*	datum = new StringCacheDatumW;
				StringCacheDatumW	**	datumPP = nullptr;
				StringCacheDatumW	*	datumP = nullptr;

				if (Len > 0) {
					Tmp = String::strdupW(str, Len);
				}

				datum->value = Tmp;

				datumPP
				    = Tree_t<StringCacheDatumW>::Search(datum,
				                                        &StringCacheTreeW::root,
				                                        cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP != datum) {
							datumP->incInstance();
							datum->value = nullptr;	// We had only copied the pointer.
							delete datum;

						} else {
							if (Len == 0) {
								datum->value = String::strdupW(str);
							}
						}
					}

					Results = datumP->value;
				}

				StringCacheDatumW::itemCount++;

				return (Results);
			}

			uint64_t
			StringCache::Count(const char * str)
			{
				uint64_t			Results = 0;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty8;
				}

				StringCacheDatum8	**	datumPP;
				StringCacheDatum8	*	datumP;
				StringCacheDatum8		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum8>::Find(&datum,
				                                      &StringCacheTree8::root,
				                                      cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						Results = datumP->getInstance();
					}
				}

				return (Results);
			}

			uint64_t
			StringCache::Count(const char16_t * str)
			{
				uint64_t			Results = 0;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty16;
				}

				StringCacheDatum16	**	datumPP;
				StringCacheDatum16	*	datumP;
				StringCacheDatum16		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum16>::Find(&datum,
				                                       &StringCacheTree16::root,
				                                       cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						Results = datumP->getInstance();
					}
				}

				return (Results);
			}

			uint64_t
			StringCache::Count(const char32_t * str)
			{
				uint64_t			Results = 0;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty32;
				}

				StringCacheDatum32	**	datumPP;
				StringCacheDatum32	*	datumP;
				StringCacheDatum32		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum32>::Find(&datum,
				                                       &StringCacheTree32::root,
				                                       cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						Results = datumP->getInstance();
					}
				}

				return (Results);
			}

			uint64_t
			StringCache::Count(const wchar_t * str)
			{
				uint64_t			Results = 0;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = emptyW;
				}

				StringCacheDatumW	**	datumPP;
				StringCacheDatumW	*	datumP;
				StringCacheDatumW		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatumW>::Find(&datum,
				                                      &StringCacheTreeW::root,
				                                      cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						Results = datumP->getInstance();
					}
				}

				return (Results);
			}

			bool
			StringCache::IsInCache(const char * str)
			{
				return ((Count(str) == 0 ? true : false));
			}

			bool
			StringCache::IsInCache(const char16_t * str)
			{
				return ((Count(str) == 0 ? true : false));
			}

			bool
			StringCache::IsInCache(const char32_t * str)
			{
				return ((Count(str) == 0 ? true : false));
			}

			bool
			StringCache::IsInCache(const wchar_t * str)
			{
				return ((Count(str) == 0 ? true : false));
			}

			bool
			StringCache::Remove(const char * str)
			{
				bool				Results = false;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty8;
				}

				StringCacheDatum8	**	datumPP;
				StringCacheDatum8	*	datumP;
				StringCacheDatum8		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum8>::Find(&datum,
				                                      &StringCacheTree8::root,
				                                      cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP->getInstance() == 1) {
							StringCacheDatum8::itemCount--;

							Tree_t<StringCacheDatum8>::Delete(datumP,
							                                  &StringCacheTree8::root,
							                                  cmp);

							if (datumP->value == str) {
								datumP->value = nullptr;
							}

							delete datumP;
						}

					} else {
						delete str;
					}

					Results = true;

				} else {
					delete str;
				}

				// this was a StringCache value, don't delete it.
				//
				datum.value = nullptr;

				return (Results);
			}

			bool
			StringCache::Remove(const char16_t * str)
			{
				bool				Results = false;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty16;
				}

				StringCacheDatum16	**	datumPP;
				StringCacheDatum16	*	datumP;
				StringCacheDatum16	datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum16>::Find(&datum,
				                                       &StringCacheTree16::root,
				                                       cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP->getInstance() == 1) {
							StringCacheDatum16::itemCount--;

							Tree_t<StringCacheDatum16>::Delete(datumP,
							                                   &StringCacheTree16::root,
							                                   cmp);

							if (datumP->value == str) {
								datumP->value = nullptr;
							}

							delete datumP;
						}

					} else {
						delete str;
					}

					Results = true;

				} else {
					delete str;
				}

				// this was a StringCache value, don't delete it.
				//
				datum.value = nullptr;

				return (Results);
			}

			bool
			StringCache::Remove(const char32_t * str)
			{
				bool				Results = false;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = empty32;
				}

				StringCacheDatum32	**	datumPP;
				StringCacheDatum32	*	datumP;
				StringCacheDatum32		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatum32>::Find(&datum,
				                                       &StringCacheTree32::root,
				                                       cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP->getInstance() == 1) {
							StringCacheDatum32::itemCount--;

							Tree_t<StringCacheDatum32>::Delete(datumP,
							                                   &StringCacheTree32::root,
							                                   cmp);

							if (datumP->value == str) {
								datumP->value = nullptr;
							}

							delete datumP;
						}

					} else {
						delete str;
					}

					Results = true;

				} else {
					delete str;
				}

				// this was a StringCache value, don't delete it.
				//
				datum.value = nullptr;

				return (Results);
			}

			bool
			StringCache::Remove(const wchar_t * str)
			{
				bool				Results = false;

				if (pthread_mutex_trylock(&StringCacheOnceMutex) == 0) {
					StringCache_Init();
				}

				if (str == nullptr) {
					str = emptyW;
				}

				StringCacheDatumW	**	datumPP;
				StringCacheDatumW	*	datumP;
				StringCacheDatumW		datum;

				datum.value = str;

				datumPP
				    = Tree_t<StringCacheDatumW>::Find(&datum,
				                                      &StringCacheTreeW::root,
				                                      cmp);

				if (datumPP != nullptr) {
					datumP = *datumPP;

					if (datumP != nullptr) {
						if (datumP->getInstance() == 1) {
							StringCacheDatumW::itemCount--;

							Tree_t<StringCacheDatumW>::Delete(datumP,
							                                  &StringCacheTreeW::root,
							                                  cmp);

							if (datumP->value == str) {
								datumP->value = nullptr;
							}

							delete datumP;
						}

					} else {
						delete str;
					}

					Results = true;

				} else {
					delete str;
				}

				// this was a StringCache value, don't delete it.
				//
				datum.value = nullptr;

				return (Results);
			}

		}
	}
}
