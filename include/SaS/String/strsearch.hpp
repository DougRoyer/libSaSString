/* Binary tree data structure.
   Copyright (C) 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
   USA.  */

#ifndef _TSEARCH_H
#define _TSEARCH_H

#ifdef __cplusplus
extern "C" {
#endif


  struct node_t
  {
    node_t();

    ~node_t();

    const void     *	key;

    struct node_t  *	left;

    struct node_t  *	right;

    unsigned int	red;

  };

  typedef node_t * node;
  typedef const struct node_t * const_node;

  /*
   * See <http://www.opengroup.org/susv3xbd/search.h.html>,
   *     <http://www.opengroup.org/susv3xsh/tsearch.html>
   * for details.
   */

  typedef enum
  { 
    preorder,
    postorder, 
    endorder,
    leaf
  }
  VISIT;

  typedef int	(*strcompare_fn_t) (const void *, const void *);
  typedef void	(*straction_fn_t) (const node_t *, VISIT, int);
  typedef void	(*strfree_fn_t) (node_t *__nodep);

  /*
   * Searches an element in the tree *VROOTP that compares equal to KEY.
   * If one is found, it is returned.  Otherwise, a new element equal to KEY
   *    is inserted in the tree and is returned.
   */
  void * strsearch(const void * key,
		   node_t * const * vrootp,
		   strcompare_fn_t compare);

  /*
   * Searches an element in the tree *VROOTP that compares equal to KEY.
   * If one is found, it is returned.  Otherwise, nullptr is returned.
   */
  void * strfind(const void * key,
		 node_t * const * vrootp,
		 strcompare_fn_t compare);
  /*
   * Searches an element in the tree *VROOTP that compares equal to KEY.
   * If one is found, it is removed from the tree, and its parent node is
   * returned.  Otherwise, nullptr is returned.
   */
  void * strdelete(const void * key,
		   node_t ** vrootp,
		   strcompare_fn_t compare);

  /*
   * Perform a depth-first, left-to-right traversal of the tree VROOT.
   *The ACTION function is called:
   * - for non-leaf nodes: 3 times, before the left subtree traversal,
   *   after the left subtree traversal but before the right subtree traversal,
   *   and after the right subtree traversal,
   * - for leaf nodes: once.
   * The arguments passed to ACTION are:
   * 1. the node; it can be casted to a 'const void * const *', i.e. into a
   *    pointer to the key,
   * 2. an indicator which visit of the node this is,
   * 3. the level of the node in the tree (0 for the root).
  */
  extern void strwalk (const node_t * vroot,
		       void (*action) (const node_t *, VISIT, int));

#ifdef __cplusplus
}
#endif

#endif /* _TSEARCH_H */
