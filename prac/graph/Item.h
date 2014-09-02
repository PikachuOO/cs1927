// Item.h  ... definition for items in Queues
// Written by John Shepherd, March 2013

#ifndef ITEM_H
#define ITEM_H

#include "Graph.h"

typedef Edge Item;

#define ItemCopy(i)     (i)
#define ItemShow(i)     printf("(%d,%d: %d)",(i).start,(i).end,(i).type)

#endif

