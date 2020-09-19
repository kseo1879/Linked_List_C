#ifndef HELPER_H
#define HELPER_H

#include "linked_list.h"

/**
 * This function is a compare function and it will return the address of the entry structure
 * if they key is found in the map and if not it will return NULL;
 * It will assume that map is not NULL;
 */
void *key_exist(struct linkedlist_map *map, void *key);


/**
 * This function will find the last entry before the next entry is null;
 * This function will iteratre throught the entries to find the last the element.
 */
void *last_node(struct linkedlist_map *map);

#endif