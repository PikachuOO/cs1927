// words.c ... Build a tree of words from /usr/dict/words
// Written by John Shepherd, August 2008
// Modified by Angela Finlayson, January 2009

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "Item.h"
#include "Tree.h"

#define WORD_FILE "/usr/dict/words"
#define MAX_WORD_SIZE 100 

void getAllWords(FILE *, Tree t);
void searchAllWords(FILE *f, Tree t);

// Get words, store in tree, print tree stats
int main(int argc, char **argv){
    char *wordsFile; // name of file containing words
    FILE *wordf;     // file handle for file containing words
    Tree wordTree; 
    int strategy = NO_REBALANCE;
    // access the word file
    if (argc > 1){
	wordsFile = argv[1];
    }else{
	wordsFile = WORD_FILE;
    }
    if(argc > 2){
        strategy = atoi(argv[2]);
    }
    wordf = fopen(wordsFile,"r");
    if (wordf == NULL) {
        printf("Can't open %s\n",wordsFile);
        exit(1);
    }
    wordTree = TREEinit(strategy);
    printf("Reading words from %s\n",wordsFile);    
    // build tree containing all words
    getAllWords(wordf, wordTree);
    TREEshowStats(wordTree);
//    searchAllWords(wordf,wordTree);
    // print some properties of the Tree
    TREEdisplay(wordTree);
    TREEshowStats(wordTree);
    TREEdestroy(wordTree);
    return 0;
}

// Search the given tree for all words from the given file
void searchAllWords(FILE *f, Tree wordTree){
    char word[MAX_WORD_SIZE];
    rewind(f);
    while (fgets(word,MAX_WORD_SIZE,f) != NULL) {
        int n = strlen(word);
	word[n-1] = '\0'; // strip off \n
	// filter out empty words
	if (strcmp(word,"") != 0){
	    //If we are using the tree that we loaded all the words
            //into, all the words we search for should be there
            assert(TREEsearch(wordTree,word) == 1); 
        }                             
    }
    
}


// Read all words from file into tree 
void getAllWords(FILE *f, Tree wordTree){
    char word[MAX_WORD_SIZE];

    while (fgets(word,MAX_WORD_SIZE,f) != NULL) {
        int n = strlen(word);
	word[n-1] = '\0'; // strip off \n
	// filter out empty words
	if (strcmp(word,"") != 0) {
       	    TREEinsert(wordTree,strdup(word));
           
        }
        
    }
}
