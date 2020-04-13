// 
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2014,2019-2020 Software and Services LLC, All Rights Reserved.
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
//

/**
 * @file msgCat2.hpp
 * @ingroup INTERNATIONAL
 * Routines for getting and setting L10N messages.
 */
#ifndef SOFTWARE_AND_SERVICES_LIBRARY_STRING_MSGCAT2_HPP_
#define SOFTWARE_AND_SERVICES_LIBRARY_STRING_MSGCAT2_HPP_

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include <SaS/Common/osver.h>
#include <SaS/Common/instance.hpp>
#include <SaS/Common/Error.hpp>
#include <vector>

#ifndef WIN32
#include <nl_types.h>
#else
#ifdef BUILDING_SAS_LIBRARY_STRING
#include "nl_types.h"
#include "winWrappers.hpp"
#else
#include <SaS/Common/nl_types.h>
#include <SaS/Common/winWrappers.hpp>
#endif
#endif

using namespace SoftwareAndServices::Library::Common;

namespace SoftwareAndServices
{
  namespace Library 
  {
    namespace Common
    {

      /**
       * @class msgCat msgCat2.hpp "<SaS/String/msgCat2.hpp>"
       * A C++ for internationalization (I18N) of messages.
       */
      class msgCat
	: virtual public instance<msgCat>
      {

      public:

	/**
	 * msgCat - Constructor
	 *
	 * @param catName Name of the catalog to open.
	 *
	 * @param guid The ID of the calling program or library.
	 */
	msgCat(const char * catName, const char * guid);

	/**
	 * msgCat - Destructor.
	 */
	virtual ~msgCat();

	/**
	 * Get the specified message - from the default set..
	 *
	 * @param cat Pointer to an open I18N catalog.
	 *
	 * @param msgNum The ID of the message to get.
	 *
	 * @param defaultMsg A default message to display, if
	 * the catalog or msgNum can not be found.
	 *
	 * @param locale In the named (or default if nullptr) locale.
	 *
	 * @return The message.
	 */
	static const char	*	
	  getMsg(msgCat * cat, 
		 unsigned int msgNum, 
		 const char * defaultMsg = nullptr,
		 const char * locale = nullptr);

	/**
	 * Get the specified message - from the default set.
	 *
	 * @param guid The ID of the program or library calling
	 * the I18N  code.
	 *
	 * @param msgNum The ID of the message to get.
	 *
	 * @param defaultMsg A default message to display, if the
	 * catalog or msgNum can not be found.
	 *
	 * @param locale In the named (or default if nullptr) locale.
	 *
	 * @return The message.
	 */
	static const char	*	
	  getMsg(const char * guid,
		 unsigned int msgNum,
		 const char * defaultMsg = nullptr,
		 const char * locale = nullptr);

	/**
	 * Get the specified message - from the named set.
	 *
	 * @param cat Pointer to an open I18N catalog.
	 *
	 * @param msgNum The ID of the message to get.
	 *
	 * @param setNum There can be more than one set of messages
	 * in a catalog.
	 *
	 * @param defaultMsg A default message to display, if the
	 * catalog or msgNum can not be found.
	 *
	 * @param locale In the named (or default if nullptr) locale.
	 *
	 * @return The message.
	 */
	static const char	*	  getMsg(msgCat * cat, 
						 unsigned int msgNum,
						 unsigned int setNum,
						 const char * defaultMsg,
						 const char * locale = nullptr);

	/**
	 * Get the specified message - from the named set.
	 *
	 * @param guid The ID of the program or library calling the
	 * I18N code.
	 *
	 * @param msgNum The ID of the message to get.
	 *
	 * @param setNum There can be more than one set of messages
	 * in a catalog.
	 *
	 * @param defaultMsg A default message to display, if the
	 * catalog or msgNum can not be found.
	 *
	 * @param locale In the named (or default if nullptr) locale.
	 *
	 * @return The message.
	 */
	static const char	*	getMsg(const char * guid,
					       unsigned int msgNum,
					       unsigned int setNum,
					       const char * defaultMsg, 
					       const char * locale = nullptr);

	/**
	 * @return TRUE when the catalog is opened.
	 */
	bool				open();
                
	/**
	 * @return Close the catalog and return TRUE when closed.
	 */
	void				close();

	/**
	 * Get the current applications GUID.
	 */
	const char		*	getGuid() const;

      private:

	/**
	 * @class guidMap
	 * Object for caching messages per GUID.
	 */
	class guidMap
	  : public instance<guidMap>
	{
	public:

	  /**
	   * guidMap - default Constructor.
	   */
	  guidMap();

	  /**
	   * guidMap - Destructor.
	   */
	  virtual ~guidMap();

	  /**
	   * Map the named catalog to the GUID.
	   *
	   * @param cat The catalog to map.
	   *
	   * @param guid The GUID to map it to.
	   */
	  static bool		map(msgCat * cat, const char * guid);

	  /**
	   * @param aGuid The GUID for which a message catalog
	   * is desired.
	   *
	   * @return The message catalog for that GUID.
	   * Returns nullptr if not available (not cached yet(.
	   */
	  static msgCat	*	getCat(const char * aGuid);

	  /**
	   * Remove the catalog from the cache, if there are
	   * no more references to it.
	   *
	   * @param cat The message catalog to remove from 
	   * the cache.
	   */
	  static void		removeIfLast(msgCat * cat);

	  /**
	   * Get the object for the named GUID.
	   *
	   * @param aGuid The GUID for which a guidMap is desired.
	   * 
	   * @return the guidMap or nullptr if not cached.
	   */
	  static guidMap *	getMap(const char * aGuid);

	  /**
	   * Array of guidMap pointers.
	   */
	  static std::vector<guidMap*>		catmap;

	  /**
	   * This objects msgCat.
	   */
	  msgCat	*	cat;

	  /**
	   * This obeject GUID
	   */
	  const char	*	guid;
	};

	/**
	 * @return TRUE when the catalog is open.
	 */
	bool			_isOpen();

	/**
	 * The name of the current catalog.
	 */
	const char	*	_catName;

	/**
	 * The GUID associated with the current catalog.
	 */
	const char	*	_catGuid;
				
	/**
	 * Handle to lower layer OS catalog functions.
	 */
	nl_catd		        _handle;
      };
			
    }
  }
}

#endif//SOFTWARE_AND_SERVICES_LIBRARY_STRING_MSGCAT2_HPP_
