// 
// BEGIN_COPYRIGHT
//
// Copyright (C) 2010-2014,2019 Software and Services LLC, All Rights Reserved.
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
// END_COPYRIGHT
//

/**
 * @file replaceText.hpp "<SaS/Common/replaceText.hpp>"
 * @ingroup PARSE
 * Within a buffer, replace OLD with NEW.
 */
#ifndef _SOFTWARE_AND_SERVICES_LIBRARY_STRING_REPLACE_TEXT_HPP__
#define _SOFTWARE_AND_SERVICES_LIBRARY_STRING_REPLACE_TEXT_HPP__

#ifdef WIN32
#pragma warning (disable : 4251)
#endif

#include <SaS/Common/osver.h>
#include <SaS/Common/instance.hpp>
#include <vector>

namespace SoftwareAndServices
{
  namespace Library 
  {
    namespace Common
    {

      /**
       * @class replaceText replaceText.hpp "<SaS/Common/replaceText.hpp>"
       * An object to minipulate and replace text.
       */
      class replaceText
	: virtual public instance<replaceText>
      {

      public:

	/**
	 * replaceText - Constructor.
	 */
	replaceText();

	/**
	 * replaceText - Destructor.
	 */
	virtual ~replaceText();

	/**
	 * Multiple replacements can take place.
	 * They are done in order.
	 */
	struct set {

	  /**
	   * Old Text.
	   */
	  const char	*	replace;

	  /**
	   * New Text.
	   */
	  const char	*	with;
	};

	/**
	 * Replace the text.
	 *
	 * @param ofSet The set of replacements to make.
	 *
	 * @param result A pointer to a (char*) that will be filled in
	 * with the new data. Caller must delete results.
	 *
	 * @param source The original source text.
	 */
	static bool	replace(std::vector<set*> & ofSet,
				char ** result,
				const char * source);
      };

    }
  }
}

#endif// _SOFTWARE_AND_SERVICES_LIBRARY_STRING_REPLACE_TEXT_HPP__
