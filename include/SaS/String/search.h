// 
// BEGINSOFTWARE_AND_SERVICES_COPYRIGHT
//
// Copyright (C) 2010-2012 Software and Services LLC, All Rights Reserved.
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
// ENDSOFTWARE_AND_SERVICES_COPYRIGHT
//

/**
 * @file search.h "<SaS/String/search.h>"
 * @ingroup STORAGE
 * Emulation of the search function for non POSIX systems.
 */
#ifndef SOFTWARE_AND_SERVICES_LIBRARY_STRING_PC_SEARCH_H_
#define SOFTWARE_AND_SERVICES_LIBRARY_STRING_PC_SEARCH_H_

#ifdef WINDOWS
#pragma warning (disable : 4251)
#endif

#include <SaS/String/osver.h>

#if defined(SunOS) || defined(Linux)
#include "/usr/include/search.h"
#endif

#if defined(WINDOWS)

#ifdef	__cplusplus
extern "C" {
#endif

	/**
	 * @enum ACTION_t
	 * What action to perform.
	 */
	typedef enum ACTION_t {
		FIND,	/** Find a record */
		ENTER	/** Enter a record */
	} ACTION;

	/**
	 * @struct entry
	 * A datum entry.
	 */
	typedef struct entry {
		char	*	key;		/** The key */
		char	*	data;		/** The data */
	} ENTRY;

	/**
	 * @enum VISIT_t
	 * Inform the called fuction with information that includes
	 * on whether  this  is  the first,  second  or third time
	 * that the node has been visited (during a depth-first,
	 * left-to-right traversal of the tree), or whether the
	 * node  is a leaf. The third argument is the level of the
	 * node in the tree, with the root being  level zero.
	 */
	typedef enum VISIT_t { 
		preorder,	/** First */
		postorder,	/** Second */
		endorder,	/** Third */
		leaf		/** Is leaf */
	} VISIT;

#include <SaS/String/osver.h>

#ifndef _SIZE_T
#define	_SIZE_T
#ifndef mac

	/**
	 * @typedef size_t
	 * Standard size_t for system that do not have it defined.
	 */
	typedef unsigned	size_t;
#else
	/**
	 * @typedef size_t
	 * Standard size_t for system that do not have it defined.
	 */
	typedef long unsigned int	size_t;
#endif
#endif

	/**
	 * @struct pc_qelem
	 * The structure of the queue, a double linked list.
	 */
	struct pc_qelem {
		struct qelem	*q_forw;	/** Forward pointer */
		struct qelem	*q_back;	/** Backward pointer */
	};


	/**
	 * Create a hash.
	 * The hcreate() function allocates sufficient  space  for  the
     * table, and must be called before hsearch() is used.  The nel
     * argument is an estimate of the  maximum  number  of  entries
     * that  the  table  will  contain. This number may be adjusted
     * upward by the algorithm in order to obtain certain mathemat-
     * ically favorable circumstances.
	 *
	 * @param TheSize the size of the heap.
	 *
	 * @return Zero (0) if it can not create the hash.
	 */
	int hcreate(size_t TheSize);

	/**
	 * Destroy the hash.
	 */
	void hdestroy(void);

	/**
	 * Search for ENTRY, if not found perform ACTION.
	 *
	 * @param TheEntry What to look for.
	 *
	 * @param TheAction What to do if not found.
	 *
	 * @return The item, or NULL if not found.
	 */
	ENTRY *hsearch(ENTRY TheEntry, ACTION TheAction);

	/**
	 * Insert TheElement after Pred.
	 *
	 * @parram TheElement The element to insert into the queue.
	 *
	 * @param InsertAfter Insert it after this element. Or at the 
	 * begining if NULL>
	 */
	void insque(void * TheElement, void * InsertAfter);

	/**
	 * Remove item from the queue.
	 *
	 * @param ToBeRemvoed What item will be removed.
	 */
	void remque(void *);

	/**
	 * Delete an element.
	 * 
	 * @param Key The key to delete.
	 *
	 * @param root A pointer to the root of the tree.
	 *
	 * @param comp A compare function to determine if the item matched key.
	 *
	 * @return A poninter to the parent of the item found and deleted, or NULL if not found.
	 */
	EXPORT_STRING void *	tdelete(const void * Key, 
									void ** root, 
									int (*comp)(const void * CompareNode1, const void * CompareNode2));

	/**
	 * Find an element in the list.
	 *
	 * @param Key The key to find.
	 *
	 * @param root A pointer to the root of the tree.
	 *
	 * @param comp A compare function to determine if the item matched key.
	 *
	 * @return The item found, or NULL if not found.
	 */
	EXPORT_STRING void *	tfind(const void * key,
								  void *const * root,
								  int (*comp)(const void * CompareNode1, const void * CompareNode2));

	/**
	 * Like tfind(), except will insert key if not found.
	 *
	 * @param Key The key to find.
	 *
	 * @param root A pointer to the root of the tree.
	 *
	 * @param comp A compare function to determine if the item matched key.
	 *
	 * @return The item found or inserted.
	 */
	EXPORT_STRING void *	tsearch(const void * key,
									void ** root,
									int (*comp)(const void * CompareNode1, const void * CompareNode2));

	/**
	 * Like tfind(), except peform action TheAction on found nodes.
	 *
	 * @param Key The key to find.
	 *
	 * @param root A pointer to the root of the tree.
	 *
	 * @param TheAction The action to take when found.
	 *
	 * @return The item found or inserted.
	 */
	EXPORT_STRING void	twalk(const void * key,
							  void (*)(const void * FoundNode, VISIT ItsPosition, int LevelOfTree));

#ifndef WINDOWS
	void *bsearch(const void *, const void *, size_t, size_t,
		int (*)(const void *, const void *));

	void *lfind(const void *, const void *, size_t *, size_t,
		int (*)(const void *, const void *));
	void *lsearch(const void *, void *, size_t *, size_t,
		int (*)(const void *, const void *));
#endif

#ifdef	__cplusplus
}
#endif
#endif // !SunOS

#endif/* SOFTWARE_AND_SERVICES_LIBRARY_STRING_PC_SEARCH_H_*/
