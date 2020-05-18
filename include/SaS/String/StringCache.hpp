//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2015,2020 Software and Services LLC, All Rights Reserved.
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
// END_SOFTWARE_AND_SERVICES_COPYRIGHT
//

/**
 * @file StringCache.hpp "<SaS/String/StringCache.hpp>"
 * @ingroup STRING
 * Cache commonly used strings.
 */
#ifndef SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRINGCACHE_HPP_
#define SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRINGCACHE_HPP_

#ifdef WIN32
#pragma warning (disable : 4251)
#endif
#
#include <SaS/Common/osver.h>
#include <SaS/Common/instance.hpp>
#include <SaS/String/String.hpp>
#include <SaS/Common/XdrSerialize.hpp>
#include <SaS/Common/File.hpp>

#include <inttypes.h>

using namespace SoftwareAndServices::Library::Common;

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			class String;       // Forward ref.

			/**
			 * @class StringCache StringCache.hpp "<SaS/String/StringCache.hpp>"
			 *
			 * This class keeps a reference count of constant strings.
			 * The entry will be deleted when its reference count is zero.
			 * Once in the cache, it can have more references to it.
			 *  it can have referenced removed from it.
			 *  it can be deleted, when the reference count reaches zero.
			 *
			 * @note
			 * DO NOT change the value of the returned string.
			 *
			 * When you are done with the strings in the cache - DO NOT DELETE
			 * or FREE them. Call StringCache::Remove() to keep the reference
			 * count accurate. This StrimgCache is for commonly used read-only
			 * strings.
			 */
			class StringCache
				: virtual public instance<StringCache> {
				public:

					/**
					 * StringCache - Constructor.
					 */
					StringCache();

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const char * ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const char16_t * ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const char32_t * ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const wchar_t * ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const std::string & ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const std::u16string & ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const std::u32string & ToAdd, size_t Len = 0);

					/**
					 * String Cache - Constructor.
					 *
					 * @param ToAdd A string to add to the cache.
					 * The string will be copied, then placed into the cache.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 */
					StringCache(const std::wstring & ToAdd, size_t Len = 0);

					/**
					 * String Cache - Destructor.
					 */
					virtual ~StringCache();

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char	*	const Add(const char * StringToCache,
					                                  size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char16_t	*	const Add(const char16_t * StringToCache,
					                                      size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char32_t	*	const Add(const char32_t * StringToCache,
					                                      size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const wchar_t	*	const Add(const wchar_t * StringToCache,
					                                      size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char	*	const Add(const std::string & StringToCache,
					                                  size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char16_t	*	const Add(const std::u16string & StringToCache,
					                                      size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const char32_t	*	const Add(const std::u32string & StringToCache,
					                                      size_t Len = 0);

					/**
					 * Add or get a reference to an entry in the cache.
					 *
					 * @param StringToCache The string to add and get the reference to.
					 *
					 * @param Len Optional. When provided, only Len characters
					 * will be added.
					 *
					 * @return The pointer to use when referencing this string.
					 */
					static const wchar_t	*	const Add(const std::wstring & StringToCache,
					                                      size_t Len = 0);

					/**
					 * Decrement the reference count to the string. Remove it
					 * from the cache if the reference count is zero.
					 *
					 * If StringToRemove is not in the cache, then delete will
					 * be called to free it. This is so, if your not sure,
					 * you can call Remove to free the space,
					 *
					 * @param StringToRemove The string to remove from the cache.
					 *
					 * @return TRUE if in the cache, and removed.
					 */
					static bool		    Remove(const char * StringToRemove);

					/**
					 * Decrement the reference count to the string. Remove it
					 * from the cache if the reference count is zero.
					 *
					 * If StringToRemove is not in the cache, then delete will
					 * be called to free it. This is so, if your not sure,
					 * you can call Remove to free the space,
					 *
					 * @param StringToRemove The string to remove from the cache.
					 *
					 * @return TRUE if in the cache, and removed.
					 */
					static bool		    Remove(const char16_t * StringToRemove);

					/**
					 * Decrement the reference count to the string. Remove it
					 * from the cache if the reference count is zero.
					 *
					 * If StringToRemove is not in the cache, then delete will
					 * be called to free it. This is so, if your not sure,
					 * you can call Remove to free the space,
					 *
					 * @param StringToRemove The string to remove from the cache.
					 *
					 * @return TRUE if in the cache, and removed.
					 */
					static bool		    Remove(const char32_t * StringToRemove);

					/**
					 * Decrement the reference count to the string. Remove it
					 * from the cache if the reference count is zero.
					 *
					 * If StringToRemove is not in the cache, then delete will
					 * be called to free it. This is so, if your not sure,
					 * you can call Remove to free the space,
					 *
					 * @param StringToRemove The string to remove from the cache.
					 *
					 * @return TRUE if in the cache, and removed.
					 */
					static bool		    Remove(const wchar_t * StringToRemove);

					/**
					 * Find the provided string, and get the number of references
					 * to it.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return The number of times the string is referenced in the
					 * cache.
					 *
					 * Zero means it is not in the cache.
					 */
					static uint64_t	Count(const char * LookForString);

					/**
					 * Find the provided string, and get the number of references
					 * to it.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return The number of times the string is referenced in the
					 * cache.
					 *
					 * Zero means it is not in the cache.
					 */
					static uint64_t	Count(const char16_t * LookForString);

					/**
					 * Find the provided string, and get the number of references
					 * to it.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return The number of times the string is referenced in the
					 * cache.
					 *
					 * Zero means it is not in the cache.
					 */
					static uint64_t	Count(const char32_t * LookForString);

					/**
					 * Find the provided string, and get the number of references
					 * to it.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return The number of times the string is referenced in the
					 * cache.
					 *
					 * Zero means it is not in the cache.
					 */
					static uint64_t	Count(const wchar_t * LookForString);

					/**
					 * Determine if LookForString is in the cache.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return true when LookForString is in the cache,
					 * else returns false.
					 */
					static bool	IsInCache(const char * LookForString);

					/**
					 * Determine if LookForString is in the cache.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return true when LookForString is in the cache,
					 * else returns false.
					 */
					static bool	IsInCache(const char16_t * LookForString);

					/**
					 * Determine if LookForString is in the cache.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return true when LookForString is in the cache,
					 * else returns false.
					 */
					static bool	IsInCache(const char32_t * LookForString);

					/**
					 * Determine if LookForString is in the cache.
					 *
					 * @param LookForString The string to look for.
					 *
					 * @return true when LookForString is in the cache,
					 * else returns false.
					 */
					static bool	IsInCache(const wchar_t * LookForString);

					/**
					 * Get a hash for the string.
					 *
					 * @param HashThisString The string to get a hash for.
					 *
					 * @return The has for the provided string.
					 */
					static uint64_t		GetHash(const char * HashThisString);

					/**
					 * Get a hash for the string.
					 *
					 * @param HashThisString The string to get a hash for.
					 *
					 * @return The has for the provided string.
					 */
					static uint64_t		GetHash(const char16_t * HashThisString);

					/**
					 * Get a hash for the string.
					 *
					 * @param HashThisString The string to get a hash for.
					 *
					 * @return The has for the provided string.
					 */
					static uint64_t		GetHash(const char32_t * HashThisString);

					/**
					 * Get a hash for the string.
					 *
					 * @param HashThisString The string to get a hash for.
					 *
					 * @return The has for the provided string.
					 */
					static uint64_t		GetHash(const wchar_t * HashThisString);

			};

		}
	}
}

#ifdef BUILDING_SAS_LIBRARY_STRING_PHP
namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			class PhpStringCache
				: public Php::Base {

				public:

					static Php::Value
					Add(Php::Parameters & Val) {
						const char	*	CVal = Val[0];

						return (StringCache::Add(CVal));
					}

					static void
					Remove(Php::Parameters & Val) {
						const char	*	CVal = Val[0];

						StringCache::Remove(CVal);
					}
			};
		}
	}
}

#endif

#endif // SOFTWARE_AND_SERVICES_LIBRARY_STRING_STRINGCACHE_HPP_
