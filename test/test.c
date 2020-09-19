#include "../src/linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This will the the cmp function for the map.
int my_strcmp(void *a, void *b) {
    if(0 == strcmp((char *)a, (char *)b)) {
        return 0;
    } else {
        return -1;
    }
}

//This function will be called when the map gets destoryed. 
void keydel(void *key) {
    printf("Key: %s got removed\n", (char *)key);
    return;
}

//This function is for deleting the value function. 
void valdel(void *value) {
    printf("Value: %s got removed\n", (char *)value);
    free(value);
    return;
}

//Test1
void new_map_test() {
    struct linkedlist_map *map = linkedlist_map_new(my_strcmp, keydel, valdel);
    printf("Succesfully created function\n");
    linkedlist_map_destroy(map);
    //If this prints out without any memory leak than it's good. 
    printf("Sucessfully Destroyed the function\n");
    return;
}

/** Test2
 * This function will test the put and get function
 */
void map_put_and_get() {
    //First consctuct the map
    struct linkedlist_map *map = linkedlist_map_new(my_strcmp, keydel, valdel);
    char *value = NULL;

    printf("This will test 'put' and 'get' function \n\n");
    printf("This will be the key and value pair: \n{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}\n\n");

    //Initializing the value
    char *a = (char *)malloc(sizeof(char) * 20);
    memset(a, 0, 20);
    strcpy(a, "apple");

    char *b = (char *)malloc(sizeof(char) * 20);
    memset(b, 0, 20);
    strcpy(b, "banana");

    char *c = (char *)malloc(sizeof(char) * 20);
    memset(c, 0, 20);
    strcpy(c, "cake");


    linkedlist_map_put(map, "1", a);
    value = (char *)linkedlist_map_get(map, "1");
    printf("Value retrieved for key 1 is %s\n", value);

    linkedlist_map_put(map, "2", b);
    value = (char *)linkedlist_map_get(map, "2");
    printf("Value retrieved for key 2 is %s\n", value);

    linkedlist_map_put(map, "3", c);
    value = (char *)linkedlist_map_get(map, "3");
    printf("Value retrieved for key 1 is %s\n", value);

    printf("\nNow I will put the different value 'cupcake' for key 3 which already exists\n");
    strcpy(c, "cupcake");
    linkedlist_map_put(map, "3", c);
    value = (char *)linkedlist_map_get(map, "3");
    printf("Value retrieved for key 3 is %s\n", value);

   
    //Now Destory the function
    printf("\nNow Destory the function\n\n");
    linkedlist_map_destroy(map);
    printf("\nTest2 Successful for 'put' and 'get' function\n");

    return;
}

/** Test3
 * This function will test the remove function
 */
void map_remove() {
    //First consctuct the map
    struct linkedlist_map *map = linkedlist_map_new(my_strcmp, keydel, valdel);
    char *value = NULL;

    printf("This will test remove function \n\n");
    printf("This will be the key and value pair: \n{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}\n\n");

    //Initializing the value
    char *a = (char *)malloc(sizeof(char) * 20);
    memset(a, 0, 20);
    strcpy(a, "apple");

    char *b = (char *)malloc(sizeof(char) * 20);
    memset(b, 0, 20);
    strcpy(b, "banana");

    char *c = (char *)malloc(sizeof(char) * 20);
    memset(c, 0, 20);
    strcpy(c, "cake");


    linkedlist_map_put(map, "1", a);
    linkedlist_map_put(map, "2", b);
    linkedlist_map_put(map, "3", c);

    printf("\nNow I will remove the key 1\n");
    value = (char *)linkedlist_map_remove(map, "1");
    printf("Value removed for key 1 is %s\n", value);
    value = (char *)linkedlist_map_remove(map, "1");
    printf("If try to remove it again the value should be (null)\nValue returned: %s\n", value);
    //This will be for freed by the user. 
    free(a);

   
    //Now Destory the function
    printf("\nNow Destory the function\n\n");
    linkedlist_map_destroy(map);
    printf("\nTest3 Successful for 'remove' function\n");

    return;
}

/** Test4
 * This function will test the size function from the map. 
 */
void map_size() {
    //First consctuct the map
    struct linkedlist_map *map = linkedlist_map_new(my_strcmp, keydel, valdel);
    size_t value = 0;

    printf("This will test for size function \n\n");
    printf("This will be the key and value pair: \n{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}\n\n");

    //Initializing the value
    char *a = (char *)malloc(sizeof(char) * 20);
    memset(a, 0, 20);
    strcpy(a, "apple");

    char *b = (char *)malloc(sizeof(char) * 20);
    memset(b, 0, 20);
    strcpy(b, "banana");

    char *c = (char *)malloc(sizeof(char) * 20);
    memset(c, 0, 20);
    strcpy(c, "cake");


    linkedlist_map_put(map, "1", a);
    linkedlist_map_put(map, "2", b);
    linkedlist_map_put(map, "3", c);

    printf("\nNow I will test the size of the linked list \n");
    value = linkedlist_map_size(map);
    printf("The size of the linked list is %ld\n\n", value);
    linkedlist_map_remove(map, "2");
    value = linkedlist_map_size(map);
    printf("Removed one of the key, the size should be 2.\nReturned size: %ld\n", value);
    //This will be for freed by the user. 
    free(b);

   
    //Now Destory the function
    printf("\nNow Destory the function\n\n");
    linkedlist_map_destroy(map);
    printf("\nTest4 Successful for 'size' function\n");

    return;
}

int main(int argc, char **argv) {
    if(argc <= 1) {
        perror("Not Enough Argument\n");
        return -1;
    }

    if(0 == strcmp(argv[1], "1")) {
        new_map_test();
    }

    if(0 == strcmp(argv[1], "2")) {
        map_put_and_get();
    }

    if(0 == strcmp(argv[1], "3")) {
        map_remove();
    }

    if(0 == strcmp(argv[1], "4")) {
        map_size();
    }

    return 0;
}