#ifndef CHUNK_DEDUPLICATION_H
#define CHUNK_DEDUPLICATION_H

#include <stdint.h>
#include <stdbool.h>
#include "lzw_hw.h"
#define NUM_CHUNKS 3
#define MAX_CHUNK_SIZE 8192
#define HASH_TABLE_SIZE 1000
#define INPUT_SIZE 256

typedef struct HashEntry {
    uint64_t key;
    int *value;             
    int size;               
    struct HashEntry *next; 
} HashEntry;

typedef struct {
    HashEntry **entries;   
    int size;               
} HashTable;


uint64_t compute_hash(const unsigned char *chunk, int size);

void initialize_hash_table(HashTable *table);

void free_hash_table(HashTable *table);

void insert_hash_table(HashTable *table, uint64_t key, int *value, int size);

int *lookup_hash_table(HashTable *table, uint64_t key, int *size);

int deduplicate_chunks(const unsigned char *chunk, int chunk_size, HashTable *hash_table);

#endif 
