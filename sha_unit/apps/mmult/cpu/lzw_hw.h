#ifndef LZW_HW_H
#define LZW_HW_H

#include <stdint.h>

#define TABLE_SIZE 4096   
#define CHAR_MAX 256      
#define INPUT_SIZE 256     

typedef struct {
    char str[INPUT_SIZE];  
    int code;              
} DictionaryEntry;

typedef struct {
    int code;              
    char str[INPUT_SIZE];  
} DecodeEntry;

int encoding(const char *s, int *output_code, int *output_size);

int decoding(const int *encoded_data, int encoded_size);

#endif 
