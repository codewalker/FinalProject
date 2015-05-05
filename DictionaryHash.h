#ifndef DICTIONARYHASH_H
#define DICTIONARYHASH_H

#include <string>
#include <vector>

struct dictionaryWord{
    std::string word;
    std::string type;
    std::string definition;
    dictionaryWord *next;

    dictionaryWord(){};

    dictionaryWord(std::string newWord, std::string newType, std::string newDefinition)
    {
        word = newWord;
        type = newType;
        definition = newDefinition;
    }

};

class DictionaryHash
{
    public:
        DictionaryHash(int x);
        virtual ~DictionaryHash();
        int hashTableSize(std::string);
        void readInDictionary(std::string);
        dictionaryWord* RandomWordGenerator();
        int randomNumber(int rangeMax);
        dictionaryWord* findWord(std::string wordToFind);
        void addToFavorites(dictionaryWord* wordFavorite);
        dictionaryWord* getRandomType(std::string wordType);
        void displayFavorites();
        std::string createAdlib(std::string baseSentence);

    protected:
    private:
        void insertWord(dictionaryWord* wordForInsertion);
        int hashFunction(std::string title);
        dictionaryWord* createWordStruct(std::string line_In_File);
        std::string getWordType(std::string wordType);
        dictionaryWord** hashTable;
        int arraysize;                                                          //private variable to track amount of buckets in hash table array
        std::vector<dictionaryWord*> verbVector;            //Three vectors for storage of pointers to word structs that are nouns, verbs or adjectives respectively
        std::vector<dictionaryWord*> nounVector;            // Vectors will be used exclusively for Adlib public function
        std::vector<dictionaryWord*>adjVector;
        std::vector<dictionaryWord*> favoriteWords;
        int wordCount = 0;
        std::string typeOfWord_Delimiter[18] = {"adj.", "Adj.", "-adj.", "-Adj.", "n.", "N.", "-n.", "n.pl.", "v.", "-v.", "V.", "-V.", "abbr.", "Abbr.", "coarse slang", "slang", "comb.", "Comb."}; //array of different types found in dictionary file to use as delimiters when separating a word from its definition
};

#endif // DICTIONARYHASH_H
