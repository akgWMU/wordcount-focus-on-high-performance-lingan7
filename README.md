Word Frequency Analyzer

This project contains two C programs that analyze text files in a folder, count word frequencies, filter out stopwords, and display a histogram of the most frequent words.
Both programs avoid hash maps and instead maintain words in sorted arrays using binary search insertion.

📌 Programs
1. DynamicWordCounter
    #Uses a dynamic array (malloc + realloc) for storing words.
    #Reads files word-by-word using fscanf.
    #Grows in memory as needed → can handle an unlimited number of unique words.
    #Slightly slower for large files due to many I/O calls.

2. BufferedWordCounter
    #Uses a static array (WordFreq words[MAX_WORDS], max = 100,000 words).
    #Reads files using an 8KB buffer with fgets, which is faster for large files.
    #Limited to MAX_WORDS unique words.

🚀 Features
    #Counts word frequencies across all text files in a given folder.
    #Filters out common stopwords (articles, pronouns, prepositions, auxiliary verbs, conjunctions).
    #Converts all words to lowercase and strips punctuation.
    #Prints a histogram of the top 50 most frequent words, capped at 50 stars per line.
    #Sorting is done by frequency (descending) using qsort.
    
⚙️ Requirements
    #GCC or Clang compiler
    #macOS/Linux (uses <dirent.h> for folder traversal)
    #Standard C libraries only: stdio.h, stdlib.h, string.h, ctype.h, dirent.h

📂 Project Structure
    src/
     ├── sample_texts/           # Testing input text files
     ├── BufferedWordCounter.c   # Buffered version (static array)
     ├── DynamicWordCounter.c    # Dynamic version (malloc/realloc)
     ├── BWC_output              # Example output file (BufferedWordCounter)
     ├── DWC_output              # Example output file (DynamicWordCounter)
     ├── notes.txt               # Personal notes
     └── README.md               # Project documentation

🖥️ Compilation & Output
    2 executables: **DynamicWordCounter** & **BufferedWordCounter**
    For Compilation,
            gcc -o DWC_output DynamicWordCounter.c
            gcc -o BWC_output BufferedWordCounter.c
    For Running,
            ./DWC_output sample_texts
            ./BWC_output sample_texts

📊 Sample Output
 Program 1:- gcc -o DWC_output DynamicWordCounter.c
             ./DWC_output sample_texts
             
 --- Top 50 Words Histogram ---
had             | 18162 | **************************************************
not             | 17135 | **************************************************
all             | 12496 | **************************************************
this            | 10197 | **************************************************
said            | 9134 | **************************************************
one             | 8639 | **************************************************
what            | 8417 | **************************************************
have            | 8066 | **************************************************
there           | 6551 | **************************************************
now             | 6102 | **************************************************
up              | 6048 | **************************************************
no              | 5811 | **************************************************
prince          | 5515 | **************************************************
are             | 5505 | **************************************************
would           | 5283 | **************************************************
pierre          | 5224 | **************************************************
out             | 5127 | **************************************************
did             | 5114 | **************************************************
only            | 4919 | **************************************************
more            | 4601 | **************************************************
then            | 4575 | **************************************************
into            | 4486 | **************************************************
man             | 4411 | **************************************************
some            | 4308 | **************************************************
will            | 4242 | **************************************************
do              | 3940 | **************************************************
could           | 3920 | **************************************************
about           | 3863 | **************************************************
like            | 3835 | **************************************************
time            | 3675 | **************************************************
old             | 3673 | **************************************************
how             | 3598 | **************************************************
himself         | 3578 | **************************************************
very            | 3263 | **************************************************
natsha          | 3250 | **************************************************
down            | 3098 | **************************************************
andrew          | 3069 | **************************************************
over            | 2953 | **************************************************
men             | 2932 | **************************************************
has             | 2914 | **************************************************
these           | 2907 | **************************************************
see             | 2907 | **************************************************
other           | 2903 | **************************************************
know            | 2894 | **************************************************
face            | 2890 | **************************************************
eyes            | 2879 | **************************************************
still           | 2872 | **************************************************
those           | 2835 | **************************************************
went            | 2819 | **************************************************
such            | 2812 | **************************************************
**./DWC_output sample_texts  5.58s user 0.22s system 65% cpu 8.810 total**

USER TIME 5.58 seconds
SYSTEM TIME 0.22 seconds
TOTAL TIME 8.810 seconds

Now, For checking with Buffer concept

Program 2:- 

--- Top 50 Words Histogram ---
had             | 18162 | **************************************************
not             | 17135 | **************************************************
all             | 12496 | **************************************************
this            | 10197 | **************************************************
said            | 9134 | **************************************************
one             | 8639 | **************************************************
what            | 8417 | **************************************************
have            | 8066 | **************************************************
there           | 6551 | **************************************************
now             | 6102 | **************************************************
up              | 6048 | **************************************************
no              | 5811 | **************************************************
prince          | 5515 | **************************************************
are             | 5505 | **************************************************
would           | 5283 | **************************************************
pierre          | 5224 | **************************************************
out             | 5127 | **************************************************
did             | 5114 | **************************************************
only            | 4919 | **************************************************
more            | 4601 | **************************************************
then            | 4575 | **************************************************
into            | 4486 | **************************************************
man             | 4411 | **************************************************
some            | 4308 | **************************************************
will            | 4242 | **************************************************
do              | 3940 | **************************************************
could           | 3920 | **************************************************
about           | 3863 | **************************************************
like            | 3835 | **************************************************
time            | 3675 | **************************************************
old             | 3673 | **************************************************
how             | 3598 | **************************************************
himself         | 3578 | **************************************************
very            | 3263 | **************************************************
natsha          | 3250 | **************************************************
down            | 3098 | **************************************************
andrew          | 3069 | **************************************************
over            | 2953 | **************************************************
men             | 2932 | **************************************************
has             | 2914 | **************************************************
these           | 2907 | **************************************************
see             | 2907 | **************************************************
other           | 2903 | **************************************************
know            | 2894 | **************************************************
face            | 2890 | **************************************************
eyes            | 2879 | **************************************************
still           | 2872 | **************************************************
those           | 2835 | **************************************************
went            | 2819 | **************************************************
such            | 2812 | **************************************************
**./DWC_output sample_texts  5.86s user 0.23s system 83% cpu 7.317 total**

USER TIME 5.86 seconds
SYSTEM TIME 0.23 seconds
TOTAL TIME 7.317 seconds


KEY DIFFERENCES:-

1. Memory Management Strategy

    BufferedWordCounter (Static Arrays):
    WordFreq words[MAX_WORDS];           // Fixed 100,000 slots
    int word_count = 0;                  // Simple counter
    #define MAX_WORDS 100000


    DynamicWordCounter (Dynamic Arrays):
    typedef struct {
        Word *array;                     // Dynamically allocated
        int size;                        // Current elements
        int capacity;                    // Current capacity
    } WordArray;
    
    void resizeWordArray(WordArray *wa) {
        wa->capacity *= 2;               // Doubles when full
        wa->array = realloc(wa->array, sizeof(Word) * wa->capacity);
    }
        Trade-offs:
        BufferedWordCounter: Simple, fast allocation, but wastes memory and has hard limits
        DynamicWordCounter: Memory efficient, unlimited growth, but adds complexity and reallocation overhead

2. Data Structure Design

BufferedWordCounter:
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;


DynamicWordCounter:    
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} Word;

typedef struct {
    Word *array;
    int size;
    int capacity;
} WordArray;

DynamicWordCounter adds an abstraction layer with WordArray, providing better encapsulation.

3. File Processing Methods
**BufferedWordCounter (Line-based with strtok):**
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


**DynamicWordCounter (Word-based with fscanf):**
char word[MAX_WORD_LEN];
while (fscanf(fp, "%99s", word) == 1) {
    toLowerStr(word);
    removePunct(word);
    insertWord(wa, word);
}
Trade-offs:
BufferedWordCounter: More robust, handles long lines, uses buffered I/O
DynamicWordCounter: Simpler code, but less efficient for very large files and vulnerable to very long words

4. String Processing Approaches

BufferedWordCounter (In-place cleaning):

void clean_word(char *w) {
    int j=0;
    for(int i=0; w[i]; i++) {
        if(isalpha(w[i])) w[j++] = tolower(w[i]);
    }
    w[j] = '\0';
}


DynamicWordCounter (Separate functions):

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void removePunct(char *str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (isalnum(str[i])) str[j++] = str[i];  // Note: isalnum vs isalpha
    }
    str[j] = '\0';
}


Key Difference: DynamicWordCounter uses isalnum() (allows digits) vs BufferedWordCounter’s isalpha() (letters only).

5. Binary Search Implementation

BufferedWordCounter:
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


DynamicWordCounter:
int binarySearch(WordArray *wa, char *word, int *insertPos) {
    int left = 0, right = wa->size - 1;
    while (left <= right) {
        int mid = left + (right - left)/2;        // Overflow-safe
        int cmp = strcmp(word, wa->array[mid].word);
        if (cmp == 0) return mid;
        else if (cmp < 0) right = mid - 1;
        else left = mid + 1;
    }
    *insertPos = left;                           // Returns insertion position
    return -1;
}


DynamicWordCounter improvements:

Overflow-safe midpoint calculation

Returns insertion position via pointer

More descriptive variable names

6. Output Format

BufferedWordCounter:

printf("%-15s | ", words[i].word);
for(int j=0; j<words[i].count && j<50; j++) printf("*");
printf(" (%d)\n", words[i].count);


Output:

word            | ***** (5)


DynamicWordCounter:

printf("%-15s | %4d | ", wa->array[i].word, wa->array[i].count);
int stars = wa->array[i].count > 50 ? 50 : wa->array[i].count;
for (int j = 0; j < stars; j++) printf("*");
printf("\n");


Output:

word            |    5 | *****

**Performance Comparison**

**Time Complexity**
        Both have the same:
        Word insertion: O(log n) + O(n) shifting = O(n)
        Final sorting: O(w log w)

**Space Complexity**
        BufferedWordCounter: O(MAX_WORDS), always allocates full array
        DynamicWordCounter: O(w), grows as needed

**Code Quality Analysis**
        Strengths of BufferedWordCounter:
        ✅ Robust file processing with buffered I/O
        ✅ Simple memory management
        ✅ Efficient for very large datasets

        Strengths of DynamicWordCounter:
        ✅ Memory efficient (grows only as needed)
        ✅ Better encapsulation with WordArray
        ✅ Overflow-safe binary search
        ✅ Cleaner separation of concerns

        Weaknesses of BufferedWordCounter:
        ❌ Fixed-size, wastes memory
        ❌ Hard word limit
        ❌ Less modular
        
        Weaknesses of DynamicWordCounter:
        ❌ fscanf less robust for big text
        ❌ More complex memory handling
        ❌ Reallocation overhead

**Benchmark Scenarios**

Small datasets (<1k words) → DynamicWordCounter wins (less memory).
Large datasets (50k+ words) → BufferedWordCounter wins (no reallocations).

Memory-constrained → DynamicWordCounter.
High-performance needs → BufferedWordCounter.

Recommendations

Use BufferedWordCounter for large text files where speed matters.

Use DynamicWordCounter for flexible, memory-sensitive applications.

BufferedWordCounter → Performance & robustness

DynamicWordCounter → Memory efficiency & flexibility





    
