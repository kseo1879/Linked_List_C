#include "./linked_list.h"
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* @param
 * cmp will have it's own mechanism to compare two keys and return if they are equal or not.
 * This linked list will assume that it will return 0 if the key's are euqal
 * keydel and valdel will is a funtion to free the key and value when destorying the linked list. 
 */
struct linkedlist_map *linkedlist_map_new(int (*cmp)(void *, void *), 
    void (*keydel)(void *), void (*valdel)(void *)) {
    
    //Map will only be constructed when the function pointers are not null;
    if((NULL == cmp) || (NULL == keydel) || (NULL == valdel)) {
        perror("The function pointer to cmp or keydel or valdel funtion is not valid\n");
        return NULL;
    }

    //Allocating the memory for the linked list and initializing it's local variable
    struct linkedlist_map *list = (struct linkedlist_map *)malloc(sizeof(struct linkedlist_map));
    list->cmp = cmp;
    list->keydel = keydel;
    list->valdel = valdel;
    list->head = NULL;
    list->size = 0;

    return list;
}

/**
 * this function will place a key and value inside a linked list.  
 * If the key already exist it will simply replace them. However it will not going to 
 */
void linkedlist_map_put(struct linkedlist_map *map, void *key, void *value) {

    //If map is null
    if(NULL == map) {
        perror("Map is not provided in put function\n");
        return;
    } else if(NULL == key || NULL == value) {
        perror("key or value is not valid in put function");
        return;
    }

    //This part is placing a value when the list has no entry yet.
    if(0 == map->size) {
        map->size = 1;
        map->head = (struct linkedlist_map_entry *)malloc(sizeof(struct linkedlist_map_entry)); 
        map->head->key = key;
        map->head->value = value;
        map->head->next = NULL;
        map->head->prev = NULL;
        return;
    }

    struct linkedlist_map_entry *result = NULL;
    //key_exist() is declared in helper.h and it will return the entry node if the key exist
    //It will return the NULL if their is no such key found;
    result = (struct linkedlist_map_entry *)key_exist(map, key);

    //If their is no such key exist than it will find the last node and return the malloc a new memory. 
    if(NULL == result) {
        map->size++;
        struct linkedlist_map_entry *cursur = (struct linkedlist_map_entry *)last_node(map);
        cursur->next = (struct linkedlist_map_entry *)malloc(sizeof(struct linkedlist_map_entry)); 
        cursur->next->key = key;
        cursur->next->value = value;
        cursur->next->next = NULL;
        cursur->next->prev = cursur;
    } else {
        //This means that their is already a entry with key exist therefore I need to replace the value. 
        //However I will not remove the old value since I do not know is user want it or not. 
        result->value = value;
    }

    return;
}

/**
 * This function will return the value according to the key
 * If their is no such key exist in the map it will return null. 
 */
void *linkedlist_map_get(struct linkedlist_map *map, void *key) {
    if(NULL == map || NULL == key) {
        perror("The map or key provided is invalid in get function\n");
    }

    struct linkedlist_map_entry *result = NULL;
    result = (struct linkedlist_map_entry *)key_exist(map, key);

    if(NULL == result) {
        return NULL;
    } else {
        return result->value;
    }

    return NULL;
}

/**
 * This function will return the key and value pair from the linked list. 
 * However it will not free the contents inside the key and value because that is
 * what user has to do. And it user might have later usage of it. 
 */
void *linkedlist_map_remove(struct linkedlist_map *map, void *key) {
    if(NULL == map || NULL == key) {
        perror("The map or key provided is invalid in get function\n");
    }

    struct linkedlist_map_entry *result = NULL;
    result = (struct linkedlist_map_entry *)key_exist(map, key);

    if(NULL == result) {
        return NULL;
    } 
        
    //Storing the value of the node because result will get freed. 
    void *value = result->value;

    //If it was the first element
    if(NULL == result->prev) {
        //If it was the only element
        if(NULL == result->next) {
            //NOTICE: I won't be freeing the value and keys. That what user will do. 
            free(map->head);
            map->head = NULL;
        } else {
            result->next->prev = NULL;
            map->head = result->next;
            free(result);
        }
        
    } else {//This means it has previous element.
        if(NULL == result->next) {
            //This means it was the last element
            result->prev->next = NULL;
            free(result);
        } else {
            //Updating the pointer values. 
            result->next->prev = result->prev;
            result->prev->next = result->next;
            free(result);
        }
    }
    map->size--;
    map->keydel(key);
    return value;
}

/**
 * This function will return the size of linked list. 
 */
size_t linkedlist_map_size(struct linkedlist_map *map) { 

    if(NULL == map) {
        perror("Map provided is invalid in size function\n");
        return -1;;
    }

    return map->size;
}

/**
 * This function will destroy the map and all the memory associated with key and value. 
 */
void linkedlist_map_destroy(struct linkedlist_map *n) {

    if(NULL == n) {
        perror("The map is invalid in destory function\n");
    }

    struct linkedlist_map *map = n;

    //if their is no element
    if(0 == n->size) {
        free(map);
        return;
    }

    //Otherwise their should be an element inside the funtion.
    struct linkedlist_map_entry *cursur = map->head;
    struct linkedlist_map_entry *tmp = NULL;

    while(NULL != cursur) {
        tmp = cursur->next;
        map->keydel(cursur->key);
        map->valdel(cursur->value);
        free(cursur);
        cursur = tmp;
    }

    free(map);

    return;
}