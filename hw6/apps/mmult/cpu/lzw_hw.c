#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 4096 // Size of the dictionary
#define CHAR_MAX 256    // Initial characters in ASCII
#define INPUT_SIZE 256  // Maximum input string size

// Dictionary for encoding
typedef struct {
    char str[INPUT_SIZE];
    int code;
} DictionaryEntry;

// Dictionary for decoding
typedef struct {
    int code;
    char str[INPUT_SIZE];
} DecodeEntry;

int encoding(const char *s, int *output_code, int *output_size) {
    DictionaryEntry table[TABLE_SIZE];
    int code = CHAR_MAX; // Start from 256 for new codes
    int table_size = CHAR_MAX;

    // Initialize the dictionary with single characters
    for (int i = 0; i < CHAR_MAX; i++) {
        table[i].str[0] = (char)i;
        table[i].str[1] = '\0';
        table[i].code = i;
    }

    char p[INPUT_SIZE] = {s[0], '\0'};
    int out_index = 0;

    for (int i = 1; s[i] != '\0'; i++) {
        char c[2] = {s[i], '\0'};
        char temp[INPUT_SIZE];

        snprintf(temp, sizeof(temp), "%s%s", p, c);

        int found = -1;
        for (int j = 0; j < table_size; j++) {
            if (strcmp(table[j].str, temp) == 0) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            strcpy(p, temp);
        } else {
            // Output the code for p directly without searching
            for (int j = 0; j < table_size; j++) {
                if (strcmp(table[j].str, p) == 0) {
                    output_code[out_index++] = table[j].code;
                    break;
                }
            }
            // Add p + c to the table
            if (table_size < TABLE_SIZE) {
                strcpy(table[table_size].str, temp);
                table[table_size].code = code++;
                table_size++;
            }
            // Set p to the new character
            strcpy(p, c);
        }
    }

    // Output the code for the last sequence in p
    for (int j = 0; j < table_size; j++) {
        if (strcmp(table[j].str, p) == 0) {
            output_code[out_index++] = table[j].code;
            break;
        }
    }

    *output_size = out_index;
    return 0;
}

int decoding(const int *encoded_data, int encoded_size) {
    DecodeEntry table[TABLE_SIZE];
    int table_size = CHAR_MAX;

    // Initialize the dictionary with single characters
    for (int i = 0; i < CHAR_MAX; i++) {
        table[i].code = i;
        table[i].str[0] = (char)i;
        table[i].str[1] = '\0';
    }

    int old_code = encoded_data[0];
    char c = table[old_code].str[0];
    int count = CHAR_MAX;

    for (int i = 1; i < encoded_size; i++) {
        int new_code = encoded_data[i];
        char entry[INPUT_SIZE];

        if (new_code >= table_size) {
            snprintf(entry, sizeof(entry), "%s%c", table[old_code].str, c);
        } else {
            strcpy(entry, table[new_code].str);
        }

        c = entry[0];

        if (table_size < TABLE_SIZE) {
            snprintf(table[table_size].str, sizeof(table[table_size].str), "%s%c", table[old_code].str, c);
            table[table_size].code = count++;
            table_size++;
        }

        old_code = new_code;
    }
    return 0;
}

