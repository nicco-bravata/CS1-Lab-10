#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie 
{	
    struct Trie* children[26];
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* new_node = calloc(1, sizeof(struct Trie));
    return new_node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL) {
        struct Trie* pTrie = createTrie();
    }

    struct Trie* helper = pTrie;
    int length = strlen(word);
    int next_node;

    for (int i = 0; i < length; i++) {
        next_node = (word[i] - 'a');
        
        if (helper->children[next_node] == NULL) {
            helper->children[next_node] = createTrie();
        }

        helper = helper->children[next_node];
    }

    helper->count++;
    return;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL) {
        return 0;
    }

    struct Trie* helper = pTrie;
    int length = strlen(word);
    int next_node;

    for (int i = 0; i < length; i++) {
        next_node = (word[i] - 'a');
        
        if (helper->children[next_node] == NULL) {
            return 0;
        }

        helper = helper->children[next_node];
    }

    return helper->count;

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{

    struct Trie* helper;
    struct Trie* garbage;

    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            helper = pTrie->children[i];
            garbage = deallocateTrie(helper);
        }
    }

    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* readme;
    int numwords;

    readme = fopen(filename, "r");

    fscanf(readme, "%d", &numwords);

    for (int i = 0; i < numwords; i++) {
        pInWords[i] = malloc(sizeof(char) * 25);
        fscanf(readme, "%s", pInWords[i]);
    }

    return numwords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}