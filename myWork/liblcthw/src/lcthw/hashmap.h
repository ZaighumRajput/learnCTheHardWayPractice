#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h
#include <lcthw/darray.h>
#include <stdint.h>
#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare) (void *a, void *b);
typedef uint32_t(*Hashmap_hash) (void *key);
//the map
typedef struct Hashmap {
	DArray *buckets; //the apartments or houses on a dynamic street
	Hashmap_compare compare; //used to find elements by their key (gps)
	Hashmap_hash hash; // hashing function, takes a key, processes its content and produces a single uint32_t index number (addressing method)
} Hashmap;

//a house
typedef struct HashmapNode {
	void *key;
	void *data;
	//(key value pair)
	uint32_t hash; //used to identify this house
} HashmapNode;

typedef int (*Hashmap_traverse_cb) (HashmapNode * node);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash hash);
int Hashmap_set(Hashmap *map, void *key, void *data);
void Hashmap_destroy(Hashmap *map);
void *Hashmap_get(Hashmap * map, void *key);
int Hashmap_traverse(Hashmap * map, Hashmap_traverse_cb traverse_cb);
void *Hashmap_delete(Hashmap * map, void *key);
#endif
