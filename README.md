# Linked List Map (HW3)

This is a source code for making a liked list that will save the value according to the key. 

## How to use

### 1. First you need to build and link each object file:
You can simply type 'make' on your command line. 

```bash
make
```

However if you don't want to use the test code I have provided, you need to copile and link your test code with with separate command. 

```bash
gcc -c ./src/linked_list.c -o ./src/linked_list.o
gcc -c ./src/helper.c -o ./src/helper.o
gcc -c ./test/yourtestcode.c -o ./test/yourtestcode.o
gcc ./src/linkedlist.o ./src/helper.o ./test/yourtestcode.o -o map
./map
```

### 2. After you build your program here is the option:

#### This is a testing function that will test building a map and destorying a map.
```bash
make test1
```

- This is the result of the following test.
```bash
./map 1
Succesfully created function
Sucessfully Destroyed the function
```

#### This is a testing function that will test putting and getting from the map.
```bash
make test2
```

- This is the result of the following test.
```bash
./map 2
This will test 'put' and 'get' function 

This will be the key and value pair: 
{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}

Value retrieved for key 1 is apple
Value retrieved for key 2 is banana
Value retrieved for key 1 is cake

Now I will put the different value 'cupcake' for key 3 which already exists
Value retrieved for key 3 is cupcake

Now Destory the function

Key: 1 got removed
Value: apple got removed
Key: 2 got removed
Value: banana got removed
Key: 3 got removed
Value: cupcake got removed

Test2 Successful for 'put' and 'get' function
```


#### This is a testing function that will test removing an entry from the map
```bash
make test3
```

- This is the result of the following test.
```bash
./map 3
This will test remove function 

This will be the key and value pair: 
{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}


Now I will remove the key 1
Key: 1 got removed
Value removed for key 1 is apple
If try to remove it again the value should be (null)
Value returned: (null)

Now Destory the function

Key: 2 got removed
Value: banana got removed
Key: 3 got removed
Value: cake got removed

Test3 Successful for 'remove' function
```

#### This is a testing function that will test on getting the size of the map
```bash
make test4
```

- This is the result of the following test.
```bash
./map 4
This will test for size function 

This will be the key and value pair: 
{['1', 'apple'], ['2', 'banana'], ['3', 'cake']}


Now I will test the size of the linked list 
The size of the linked list is 3

Key: 2 got removed
Removed one of the key, the size should be 2.
Returned size: 2

Now Destory the function

Key: 1 got removed
Value: apple got removed
Key: 3 got removed
Value: cake got removed

Test4 Successful for 'size' function
```

### 3. To clean the directory

```bash
make clean
```

## Functions

All of these functions are declared in linked_list.h file under src folder. 
It will also utilise some of the helper function that is declared at header.h.

### 1. struct linkedlist_map *linkedlist_map_new(int (*cmp)(void *, void *), void (*keydel)(void *), void (*valdel)(void *));

- This function will create the map and return to the user. cmp function should be designed so that it should return 0 if two of the two parameter has the same key or other compare method. If it's not equal it should return -1. Keydel and valdel are also user defined function that fill destory the keys and value or even free if necessary.
- I have done some defensive coding so that their should be cmp function, keydel function and valdel function should not be NULL. It will also initialize some of the variables of the struc linkedlist_map. 

### 2. void linkedlist_map_put(struct linkedlist_map *map, void *key, void *value);

- This function will place the values by it's keys. 
- I have done some defensive coding so taht map and key and value should not be NULL. Also if the key already exist in the map it will simply replace the value. However it will not free it because that should be user responsibility. 

### 3. void *linkedlist_map_get(struct linkedlist_map *map, void *key);

- This function is a get function
- If the key is null or map is null that it will return NULL. It will also return null if the key is not found. 

### 4. void *linkedlist_map_remove(struct linkedlist_map *map, void *key);

- This function will remove the key from the map and return it's value.
- If the key or the map does not exist it will return NULL
- It will not use valdel funtion from the map when this function is called. This should be user responsibility however it will use keydel funtion to destory the key. 
- It will free the allocated memory for creating an entry. 

### 5. size_t linkedlist_map_size(struct linkedlist_map *map);

- This will simply return the size of the map based on how many keys it is storing.
- If the map is NULL it will return -1; 

### 6. void linkedlist_map_destroy(struct linkedlist_map *n) {

- If n is not null it will desotry and free every allocated memory. 
- It will use keydel and valdel functions to also destory each key and value.
