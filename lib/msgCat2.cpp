//
// BEGIN_SOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2015,2019 Software and Services LLC, All Rights Reserved.
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

#include <SaS/String/String.hpp>
#include <SaS/String/StringCache.hpp>
#include <SaS/String/msgCat2.hpp>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#define NEED_PC_INCLUDES
#endif

using namespace SoftwareAndServices::Library::Common;

namespace SoftwareAndServices {
	namespace Library {
		namespace Common {

			std::vector<msgCat::guidMap *>		msgCat::guidMap::catmap;

			// Open by library (or program) name.
			//

			msgCat::msgCat(const char * catName, const char * guid)
			{
				if (catName != nullptr) {
					_catName = StringCache::Add(catName);

				} else {
					_catName = nullptr;
				}

				if (guid != nullptr) {
					_catGuid = StringCache::Add(guid);

				} else {
					_catGuid = nullptr;
				}

				_handle = (nl_catd) - 1;

				return;
			}

			// Done

			msgCat::~msgCat()
			{
				if (getInstance() == 1) {
					(void)close();

					msgCat::guidMap::removeIfLast(this);

					if (_catName != nullptr) {
						StringCache::Remove(_catName);
						_catName = nullptr;
					}

					if (_catGuid != nullptr) {
						StringCache::Remove(_catGuid);
						_catGuid = nullptr;
					}
				}

				return;
			}

			// Get from default set number (1).
			//
			const char	*
			msgCat::getMsg(msgCat * cat,
			               unsigned int msgNum,
			               const char * defaultMsg,
			               const char * locale)
			{
				const char		*	results = nullptr;

				if (cat != nullptr) {
					results = cat->getMsg(cat,
					                      msgNum,
					                      1,
					                      defaultMsg,
					                      locale);
				}

				return (results);
			}

			const char	*
			msgCat::getMsg(const char * guid,
			               unsigned int msgNum,
			               const char * defaultMsg,
			               const char * locale)
			{
				const char		*	results = nullptr;

				if (guid != nullptr) {
					results = getMsg(guid, msgNum, 1, defaultMsg, locale);
				}

				return (results);
			}

			// Get from set number (setNum).
			//
			const char	*
			msgCat::getMsg(const char * guid,
			               unsigned int msgNum,
			               unsigned int setNum,
			               const char * defaultMsg,
			               const char * locale)
			{
				const char		*	results = nullptr;

				if (guid != nullptr) {
					msgCat		*	cat = msgCat::guidMap::getCat(guid);

					if (cat != nullptr) {
						results = getMsg(cat,
						                 msgNum,
						                 setNum,
						                 defaultMsg,
						                 locale);

					} else {
						results = defaultMsg;
					}
				}

				return (results);
			}

			// Get from set number (setNum).
			//
			const char	*
			msgCat::getMsg(msgCat * cat,
			               unsigned int msgNum,
			               unsigned int setNum,
			               const char * defaultMsg,
			               const char * /*locale*/)
			{
				const char		*	results = nullptr;

				if (cat != nullptr) {
					bool			isOpen = cat->_isOpen();

					if (!isOpen) {
						isOpen = cat->open();
					}

					if (isOpen) {
#ifndef NEED_PC_INCLUDES
						results = catgets(cat->_handle,
						                  setNum,
						                  msgNum,
						                  defaultMsg);
#else
						results = defaultMsg;
#endif

					} else  {
						results = defaultMsg;
					}
				}

				return (results);
			}

			// Open (or re-open)
			//
			bool
			msgCat::open()
			{
				bool				results = false;

				if (!_isOpen() && _catName != nullptr) {
#ifndef NEED_PC_INCLUDES
					_handle = catopen(_catName, NL_CAT_LOCALE);
#endif

					if (_handle != (nl_catd) - 1) {
						results = true;
						(void)msgCat::guidMap::map(this, _catGuid);
					}
				}

				return (results);
			}


			// Close the catalog
			//
			void
			msgCat::close()
			{
				if (_isOpen()) {
#ifndef NEED_PC_INCLUDES
					(void)catclose(_handle);
#endif
					_handle = (nl_catd) - 1;
				}

				return;
			}

			bool
			msgCat::_isOpen()
			{
				return (_handle != (nl_catd) - 1 ? true : false );
			}

			msgCat::guidMap::guidMap()
			{
				cat = nullptr;
				guid = nullptr;

				return;
			}

			msgCat::guidMap::~guidMap()
			{
				if (decInstance() == 1) {
					cat = nullptr;		// Copy always, do not delete.
					guid = nullptr;	// Copy always, do not delete.
				}

				return;
			}

			msgCat::guidMap	*
			msgCat::guidMap::getMap(const char * aGuid)
			{
				guidMap		*	results = nullptr;

				// Determine if it is already cached.
				//
				const size_t		max  = catmap.size();

				msgCat::guidMap	*	mapP = nullptr;
				unsigned int			offset;

				for (offset = 0; offset < max ; offset++) {
					mapP = (msgCat::guidMap *)msgCat::guidMap::catmap[offset];

					if (mapP != nullptr) {
						if (::strcmp(mapP->guid, aGuid) == 0) {
							results = mapP;
							break;
						}
					}
				}

				return (results);
			}

			msgCat	*
			msgCat::guidMap::getCat(const char * aGuid)
			{
				msgCat		*	results = nullptr;
				msgCat::guidMap	*	mapP = msgCat::guidMap::getMap(aGuid);

				if (mapP != nullptr) {
					results = mapP->cat;
				}

				return (results);
			}

			bool
			msgCat::guidMap::map(msgCat * newCat, const char * newGuid)
			{
				bool			results = false;
				msgCat::guidMap	*	mapP = msgCat::guidMap::getMap(newGuid);

				if (mapP == nullptr) {
					// Not in cache, add it.
					//
					mapP = new msgCat::guidMap();

					if (mapP != nullptr) {
						mapP->cat = newCat;
						mapP->guid = newGuid;
						results = true;
						catmap.push_back(mapP);
					}
				}

				return (results);
			}

			void
			msgCat::guidMap::removeIfLast(msgCat * aCat)
			{
				// Remove, when last instance.
				//
				msgCat::guidMap	  *  	mapP = nullptr;
				std::vector<guidMap *>::iterator	it;
				//unsigned int		offset;

				for (it = catmap.begin(); it != catmap.end(); it++) {
					mapP = *it;

					if (mapP != nullptr) {
						if (mapP->cat == aCat) {
							if (mapP->getInstance() == 1) {
								delete mapP;
								catmap.erase(it);
							}

							break;
						}
					}
				}

				return;
			}

		}
	}
}
