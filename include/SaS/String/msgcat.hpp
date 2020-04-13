// 
// BEGINDOUGLAS_MARK_ROYER_COPYRIGHT
//
// Copyright (C) 2010-2015 Douglas Mark Royer, All Rights Reserved.
//
// NOTICE:
//
// THIS SOURCE CODE BELONGS TO DOUGLAS MARK ROYER.
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
// PROVIDED  ON  AN "AS IS" BASIS AND DOUGLAS MARK ROYER.
// DISCLAIM ALL WARRANTIES, EXPRESS OR IMPLIED,  INCLUDING  BUT
// NOT  LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION
// HEREIN  WILL  NOT  INFRINGE  ANY  RIGHTS  OR   ANY   IMPLIED
// WARRANTIES  OF  MERCHANTABILITY  OR FITNESS FOR A PARTICULAR
// PURPOSE.  
//
// ENDDOUGLAS_MARK_ROYER_COPYRIGHT
//
//
#ifndef _DOUGLAS_MARK_ROYER_LIBSASTRING_CAT_H__
#define _DOUGLAS_MARK_ROYER_LIBSASTRING_CAT_H__

#include <SaS/Common/osver.h>
#include <SaS/Common/Error.hpp>
#include <SaS/Common/winWrappers.hpp>

#ifndef WIN32
#include <nl_types.h>
#endif

using namespace SoftwareAndServices::Library::Common;

namespace SoftwareAndServices
{
	namespace Library 
	{
		namespace Common
		{

			class MsgCat
				: public Error
			{

			public:

				// Open by library (or program) name.
				//
				MsgCat(const char * libName);
				MsgCat(const char * libName, unsigned int msgnum);

				// Done
				virtual ~MsgCat();

				// Get from default set number (1).
				//
				const char		*	GetMsg(unsigned int MsgNum,
										   const char * DefaultMsg);

				// Get from set number (setNum).
				//
				const char		*	GetMsg(unsigned int MsgNum,
										   unsigned int SetNum,
										   const char * DefaultMsg);
	
				// Open (or re-open)
				//
				nl_catd				Open(const char * Lib);

				void				Close();

			private:

				const char	*	_libName;
				nl_catd			_handle;

			};
      
		}
	}
}

#endif // _DOUGLAS_MARK_ROYER_LIBSASTRING_CAT_H__

