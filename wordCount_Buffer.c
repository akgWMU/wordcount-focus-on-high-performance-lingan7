#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 100000
#define BUFFER_SIZE 8192  // 8KB buffer

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

WordFreq words[MAX_WORDS];
int word_count = 0;

// stopwords: articles, prepositions, pronouns, auxiliary verbs, conjunctions
const char *stop_words[] = {
    "and","or","but","so","because","if","while","although","though",
    "for","nor","yet","after","before","once","since","until","when","where",
    "whether","as","than","that","which","who","whom","whose",
    "the","a","an","in","on","at","by","of","to","with","from","is","was","were",
    "be","been","being","am","i","you","he","she","it","we","they","me","him","her",
    "us","them","my","your","his","her","its","our","their", NULL
};

// Check if a word is a stop word
int is_stop_word(const char *w) {
    for(int i=0; stop_words[i]!=NULL; i++)
        if(strcmp(w, stop_words[i])==0) return 1;
    return 0;
}

// Compare for qsort
int cmp_desc(const void *a, const void *b) {
    WordFreq *wa = (WordFreq*)a;
    WordFreq *wb = (WordFreq*)b;
    return wb->count - wa->count;  // descending
}

// Binary search to find word index
int binary_search(char *w, int low, int high) {
    while(low <= high) {
        int mid = (low + high)/2;
        int cmp = strcmp(words[mid].word, w);
        if(cmp == 0) return mid;
        else if(cmp < 0) low = mid +1;
        else high = mid -1;
    }
    return -1;
}

// Insert word into sorted array using binary search
void insert_word(char *w) {
    int idx = binary_search(w, 0, word_count-1);
    if(idx != -1) {
        words[idx].count++;
        return;
    }

    // Insert into sorted position
    int pos = 0;
    while(pos < word_count && strcmp(words[pos].word, w) < 0) pos++;

    for(int i=word_count; i>pos; i--) words[i] = words[i-1];
    strncpy(words[pos].word, w, MAX_WORD_LEN);
    words[pos].count = 1;
    word_count++;
}

// Clean word: lowercase and remove punctuation
void clean_word(char *w) {
    int j=0;
    for(int i=0; w[i]; i++) {
        if(isalpha(w[i])) w[j++] = tolower(w[i]);
    }
    w[j] = '\0';
}

void process_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        perror(filename);
        return;
    }

    char buffer[BUFFER_SIZE];
    while(fgets(buffer, sizeof(buffer), fp)) {
        char *token = strtok(buffer, " \t\n\r");
        while(token) {
            clean_word(token);
            if(strlen(token) > 0 && !is_stop_word(token))
                insert_word(token);
            token = strtok(NULL, " \t\n\r");
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <folder>\n", argv[0]);
        return 1;
    }

    DIR *d = opendir(argv[1]);
    if(!d) {
        perror("Folder");
        return 1;
    }

    struct dirent *entry;
    char filepath[1024];
    while((entry = readdir(d)) != NULL) {
        if(entry->d_type == DT_REG) {
            snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name);
            process_file(filepath);
        }
    }
    closedir(d);

    // Sort by count descending
    qsort(words, word_count, sizeof(WordFreq), cmp_desc);

    // printf("Word counts (top %d):\n", word_count);
    // for(int i=0; i<word_count; i++)
    //     printf("%s: %d\n", words[i].word, words[i].count);

    // Histogram for top 50
    int top = word_count < 50 ? word_count : 50;
    printf("\nHistogram (Top %d words):\n", top);
    for(int i=0; i<top; i++) {
        printf("%-15s | ", words[i].word);
        for(int j=0; j<words[i].count && j<50; j++) printf("*");
        printf(" (%d)\n", words[i].count);
    }

    return 0;
}
