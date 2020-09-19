#include "helper.h"

/**
 * This function is a compare function and it will return the address of the entry structure
 * if they key is found in the map and if not it will return NULL;
 * It will assume that map is not NULL;
 */
void *key_exist(struct linkedlist_map *map, void *key) {
    //This means that there is no variable inside the map
    struct linkedlist_map_entry *cursur = map->head;
    int result = -1;

    while(NULL != cursur) {
        result = map->cmp(cursur->key, key);
        if(0 == result) {
            return cursur;
        } else {
            cursur = cursur->next;
        }
    }

    return NULL;
}

/**
 * This function will find the last entry before the next entry is null;
 * This function will iteratre throught the entries to find the last the element.
 */
void *last_node(struct linkedlist_map *map) {

    struct linkedlist_map_entry *cursur = map->head;

    //Looping thourgh the nodes to find the last element. 
    while(1) {
        if(NULL == cursur->next) {
            return cursur;
        } else {
            cursur = cursur->next;
        }
    }
    return NULL;
}