#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define TOP_N 50

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} Word;

typedef struct {
    Word *array;
    int size;
    int capacity;
} WordArray;

// stopwords: articles, prepositions, pronouns, auxiliary verbs, conjunctions
const char *stopwords[] = {
    "and","or","but","so","because","if","while","although","though",
    "for","nor","yet","after","before","once","since","until","when","where",
    "whether","as","than","that","which","who","whom","whose",
    "the","a","an","in","on","at","by","of","to","with","from","is","was","were",
    "be","been","being","am","i","you","he","she","it","we","they","me","him","her",
    "us","them","my","your","his","her","its","our","their", NULL
};

// Check if word is a stopword
int isStopword(const char *word) {
    for (int i = 0; stopwords[i]; i++) {
        if (strcmp(word, stopwords[i]) == 0) return 1;
    }
    return 0;
}

// Initialize dynamic array
void initWordArray(WordArray *wa) {
    wa->size = 0;
    wa->capacity = 100;
    wa->array = (Word *)malloc(sizeof(Word) * wa->capacity);
}

// Resize dynamic array
void resizeWordArray(WordArray *wa) {
    wa->capacity *= 2;
    wa->array = (Word *)realloc(wa->array, sizeof(Word) * wa->capacity);
}

// Convert string to lowercase
void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

// Remove punctuation in place
void removePunct(char *str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (isalnum(str[i])) str[j++] = str[i];
    }
    str[j] = '\0';
}

// Binary search: returns index if found, else -1
int binarySearch(WordArray *wa, char *word, int *insertPos) {
    int left = 0, right = wa->size - 1;
    while (left <= right) {
        int mid = left + (right - left)/2;
        int cmp = strcmp(word, wa->array[mid].word);
        if (cmp == 0) return mid;
        else if (cmp < 0) right = mid - 1;
        else left = mid + 1;
    }
    *insertPos = left;
    return -1;
}

// Insert word in sorted order or increment count
void insertWord(WordArray *wa, char *word) {
    if (strlen(word) == 0) return;      // skip empty
    if (isStopword(word)) return;        // skip stopwords
    int pos;
    int idx = binarySearch(wa, word, &pos);
    if (idx != -1) {
        wa->array[idx].count++;
    } else {
        if (wa->size == wa->capacity) resizeWordArray(wa);
        for (int i = wa->size; i > pos; i--)
            wa->array[i] = wa->array[i-1];
        strcpy(wa->array[pos].word, word);
        wa->array[pos].count = 1;
        wa->size++;
    }
}

// Compare function for qsort: descending by count
int compareCount(const void *a, const void *b) {
    Word *wa = (Word *)a;
    Word *wb = (Word *)b;
    return wb->count - wa->count;
}

// Process a single file
void processFile(WordArray *wa, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return;
    }
    char word[MAX_WORD_LEN];
    while (fscanf(fp, "%99s", word) == 1) {
        toLowerStr(word);
        removePunct(word);
        insertWord(wa, word);
    }
    fclose(fp);
}

// Process all files in folder
void processFolder(WordArray *wa, char *foldername) {
    struct dirent *entry;
    DIR *dp = opendir(foldername);
    if (!dp) {
        perror(foldername);
        exit(EXIT_FAILURE);
    }

    char filepath[1024];
    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_REG) { // regular file
            snprintf(filepath, sizeof(filepath), "%s/%s", foldername, entry->d_name);
            processFile(wa, filepath);
        }
    }
    closedir(dp);
}

// Print histogram
void printHistogram(WordArray *wa) {
    printf("\n--- Top %d Words Histogram ---\n", TOP_N);
    int n = wa->size < TOP_N ? wa->size : TOP_N;
    for (int i = 0; i < n; i++) {
        printf("%-15s | %4d | ", wa->array[i].word, wa->array[i].count);
        int stars = wa->array[i].count > 50 ? 50 : wa->array[i].count;
        for (int j = 0; j < stars; j++) printf("*");
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <foldername>\n", argv[0]);
        return 1;
    }

    WordArray wa;
    initWordArray(&wa);

    processFolder(&wa, argv[1]);

    // Sort by count descending
    qsort(wa.array, wa.size, sizeof(Word), compareCount);

    // Print word counts
    // printf("--- Word Counts ---\n");
    // for (int i = 0; i < wa.size; i++) {
    //     printf("%-15s %d\n", wa.array[i].word, wa.array[i].count);
    // }

    // Print histogram
    printHistogram(&wa);

    free(wa.array);
    return 0;
}
