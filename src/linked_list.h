#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

struct linkedlist_map_entry {
    void *key;
    void *value;
    struct linkedlist_map_entry *next;
    struct linkedlist_map_entry *prev;
};


struct linkedlist_map {
    int (*cmp)(void *, void *);
    void (*keydel)(void *);
    void (*valdel)(void *);
    struct linkedlist_map_entry *head;
    size_t size;
};

/* @param
 * cmp will have it's own mechanism to compare two keys and return if they are equal or not.
 * This linked list will assume that it will return 0 if the key's are euqal
 * keydel and valdel will is a funtion to free the key and value when destorying the linked list. 
 */
struct linkedlist_map *linkedlist_map_new(int (*cmp)(void *, void *), 
    void (*keydel)(void *), void (*valdel)(void *));

/**
 * this function will place a key and value inside a linked list.  
 */
void linkedlist_map_put(struct linkedlist_map *map, void *key, void *value);

/**
 * This function will return the value according to the key
 * If their is no such key exist in the map it will return null. 
 */
void *linkedlist_map_get(struct linkedlist_map *map, void *key);

/**
 * This function will return the key and value pair from the linked list. 
 * However it will not free the contents inside the key and value because that is
 * what user has to do. And it user might have later usage of it. 
 */
void *linkedlist_map_remove(struct linkedlist_map *map, void *key);

/**
 * This function will return the size of linked list. 
 */
size_t linkedlist_map_size(struct linkedlist_map *map);

/**
 * This function will destroy the map and all the memory associated with key and value. 
 */
void linkedlist_map_destroy(struct linkedlist_map *n);

#endif