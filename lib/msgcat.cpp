//
// BEGIN_INET_COPYRIGHT
//
// Copyright (C) 1993-2004,2016 Douglas Mark Royer, All Rights Reserved.
// Copyright (C) 2000-2004 INET-Consulting LLC, All Rights Reserved.
// Copyright (C) 2002-2004 INET-Consulting.com, Inc., All Rights Reserved.
// Copyright (C) 2004 INET-Products.com, All Rights Reserved.
//
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO INET-CONSULTING.COM, INCORPORATED
// CORPORATION, A NEVADA CORPORATION.  THIS CODE IS CONSIDERED A
// TRADE SECRET AND IS NOT TO BE DIVULGED OR USED BY PARTIES WHO HAVE
// NOT RECEIVED WRITTEN AUTHORIZATION FROM THE OWNER.
//
// THIS PROGRAM IS AN UNPUBLISHED WORK FULLY PROTECTED BY THE UNITED
// STATES COPYRIGHT LAWS AND IS CONSIDERED A TRADE SECRET BELONGING
// TO THE COPYRIGHT HOLDER.
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
// PROVIDED  ON  AN "AS IS" BASIS AND INET-CONSULTING.COM, INC.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,  INCLUDING  BUT
// NOT  LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN  WILL  NOT  INFRINGE  ANY  RIGHTS  OR   ANY   IMPLIED
// WARRANTIES  OF  MERCHANTABILITY  OR FITNESS FOR A PARTICULAR
// PURPOSE.  ANY SERVICE CONTRACT  WILL  BE  UNDER  A  SEPARATE
// LICENSE.
//
//
// END_INET_COPYRIGHT
//

#include <SaS/String/StringCache.hpp>
#include "msgcat.hpp"
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <SaS/Common/nl_types.h>
//#define catgets _catgets
//#define catopen _catopen
//#define catclose _catclose;
#endif

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			// Open by library (or program) name.
			//
#ifdef NOPE

			MsgCat::MsgCat(const char * libName)
			{
				(void)Open(libName);
			}


			MsgCat::MsgCat(const char * libName, unsigned int msgnum)
			{
				(void)Open(libName);
				(void)GetMsg(msgnum, "<can't find message catalog>");
			}
#endif
			// Done

			MsgCat::~MsgCat()
			{
				Close();
			}

			// Get from default set number (1).
			//
			const char	*
			MsgCat::GetMsg(unsigned int msgNum, const char * defaultMsg)
			{
#ifndef NEED_PC_INCLUDES
				return (catgets(_handle, 1, msgNum, defaultMsg));
#else
				return (defaultMsg);
#endif
			}

			// Get from set number (setNum).
			//
			const char	*
			MsgCat::GetMsg(unsigned int msgNum,
			               unsigned int setNum,
			               const char * defaultMsg)
			{
#ifndef NEED_PC_INCLUDES
				return (catgets(_handle, setNum, msgNum, defaultMsg));
#else
				return (defaultMsg);
#endif
			}


			// Open (or re-open)
			//
			nl_catd
			MsgCat::Open(const char * lib)
			{
				if (_handle != (nl_catd) - 1) {
					Close();
				}

#ifndef NEED_PC_INCLUDES
				_handle = catopen(lib, NL_CAT_LOCALE);
#endif

				if (_libName != nullptr) {
					free((void *)_libName);
					_libName = nullptr;
				}

				if (_handle != (nl_catd) - 1) {
					_libName = strdup(lib);
				}

				return (_handle);
			}


			// Close the catalog
			//
			void
			MsgCat::Close()
			{
				if (_handle != (nl_catd) - 1) {
					(void)catclose(_handle);
					_handle = (nl_catd) - 1;
				}

				if (_libName != nullptr) {
					free((void *)_libName);
					_libName = nullptr;
				}

				return;
			}

		}
	}
}
