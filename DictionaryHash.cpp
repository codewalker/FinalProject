#include "DictionaryHash.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

DictionaryHash::DictionaryHash(int x)
{
    arraysize = x; //private variable defined for use in hashing function. The variable stores the size of the created Hash Table
    hashTable =  new dictionaryWord *[x];   //dynamically sized hash table array based on number of words from file to be read in

   //initialize all array positions to NULL
    for (int i = 0; i < x; i++){
        hashTable[i] = NULL;
    }
        //delimiterArraySize = sizeof(typeOfWord_Delimiter)/sizeof(typeOfWord_Delimiter[0]);
}

DictionaryHash::~DictionaryHash()
{
    //dtor
}


int DictionaryHash::hashTableSize(string file)  //function will open file to count number of words. Total number of words in the file will then be the size of the hash table array
{
    int lineCounter = 0;
    string temp;
    ifstream inFile;
    inFile.open(file);
    if(inFile.is_open()){
            while(!inFile.eof()){
                getline(inFile, temp);
                if (temp.length() > 10) lineCounter++;          //this conditional statement ensures that empty lines and lines in the file for file organization are not included in the word count
            }
    }
    inFile.close();

    return lineCounter;
}
void DictionaryHash::readInDictionary(string fileName)
{
    //Declaration of variable to store file data accessed by getline. Will be used to pass information into hash table data-structure
    string tempLine;
    dictionaryWord* newWord;

    ifstream inFile;
    inFile.open(fileName);
    if(inFile.is_open())
    {

        while( getline(inFile, tempLine))
        {
            size_t threshHold = 10;

            if(tempLine.length() > threshHold)  //string length of line is compared to thresh hold in order to differentiate empty lines, lines with one letter/number, etc. from lines with word and definition
            {
                    newWord = createWordStruct(tempLine);   //create word struct takes the lines, separates it into its 2 to 3 parts (word, definition, and type) and stores in a
                                                                                           // dictionaryWord struct which is then returned for insertion
                    if(newWord->word != "exception") insertWord(newWord);
                    else delete newWord;
            }
        }
        inFile.close(); //closing file as program is done reading data
    }
}

int DictionaryHash::hashFunction(std::string hashKey)       //function creates hash index from string key using the division method. implementation of rolling hash would be great as an improvement
{
    int address = 0;

    for(size_t i = 0; i < hashKey.length(); i++){
        if(hashKey[i] >= 0 && hashKey[i] <= 128)    //conditional statement used to avoid seg faults and errors from trying to access the ASCII integer value of characters outside the scope, i.e. accented letters
        {
            address = address + hashKey[i];
        }

    }
    address = address % arraysize;
    return address;
}

dictionaryWord* DictionaryHash::createWordStruct(std::string line_In_File)
{
    string tempWord;
    string tempType;
    string tempDefinition;

    size_t index = line_In_File.find("  ");
    tempWord = line_In_File.substr(0, index);                   //separation of a line in a file into the word and the definition. definition contains the word type


    tempDefinition = line_In_File.substr(index +2);
    int index1 = tempDefinition.find(" "); // dictionary file is organized as such:     <word> (double space) <type> (single space)
    tempType = tempDefinition.substr(0, index1);
    tempType = getWordType(tempType);   //function that searches the string where the type is with an array with all the different notations of noun, verb, and adjective types.
                                                                            // returns one of the three above types in simple string format for simplicity
   if(tempType == "adjective" || tempType == "verb" || tempType == "noun")
    {
            dictionaryWord* newWord = new dictionaryWord(tempWord, tempType, tempDefinition);   // creation of new word struct
            wordCount ++;   //keep count of all words stored by the program from the inFile

            if(newWord->type == "adjective") adjVector.push_back(newWord);  //three vectors used to store words of the same type for random generation capabilities
            if(tempType == "noun") nounVector.push_back(newWord);
            if(tempType == "verb") verbVector.push_back(newWord);


            return newWord;
    }


            dictionaryWord* wordException = new dictionaryWord(tempWord, tempType, tempDefinition); //save word and definition into hash table even if it is not in one of the three above categories
            wordCount++;
            return wordException;
}

void DictionaryHash::insertWord(dictionaryWord* wordForInsertion)
{
    int hashAddress = hashFunction(wordForInsertion->word);

    if(hashTable[hashAddress] == NULL){
    hashTable[hashAddress] = wordForInsertion;
    wordForInsertion->next = NULL;
    }

    else{
        dictionaryWord* tempNode = hashTable[hashAddress];

        while(tempNode->next != NULL){
                    tempNode = tempNode->next;
        }

        tempNode->next = wordForInsertion;
        wordForInsertion->next = NULL;
    }
}

string DictionaryHash::getWordType(string wordType)
{
    string adj = "adjective";
    string noun = "noun";
    string verb = "verb";
    int arrayIndex;



    for(int i = 0; i < 17; i++)         //search array of word Type notations for a match
    {
            if(typeOfWord_Delimiter[i] == wordType) arrayIndex = i; //if match found
    }
                //notatons were grouped together in the hard coded array to know which type based of index number
    if(arrayIndex < 4) return adj; //adjective
    else if(arrayIndex > 3 && arrayIndex < 8) return noun;  //noun
    else if(arrayIndex > 7 && arrayIndex < 12) return verb; //verb
    else return ""; //returns nothing if no notation match

}

dictionaryWord* DictionaryHash::RandomWordGenerator()
{
    dictionaryWord* tempNode;
    int listLength= 1;
    int arrayIndex;

    dictionaryWord* randomWord;

   do{
        arrayIndex = randomNumber(arraysize);
        randomWord = hashTable[arrayIndex];         //do/while loop continues to generate random hash table index until it finds an open bucket
   } while (randomWord == NULL);

        tempNode = randomWord;

        while(tempNode->next != NULL)       //traversal of linked list to ascertain length of chain
        {
            listLength++;
            tempNode = tempNode->next;
        }

        tempNode = randomWord;  //reset tempNode to head of linked list

        if(listLength == 1) return randomWord;
        else
        {
            int listIndex = randomNumber(listLength);   //get random number between 0 and the length of the list

            for(int i = 0; i < listIndex; i++)  // random list index used to traverse chain to what will be the random word
            {
                tempNode = tempNode->next;
            }

            randomWord = tempNode;
            return tempNode;    //return random word struct

        }
}


int DictionaryHash::randomNumber(int rangeMax)
{

    static default_random_engine generator;     // include <random> used for this functionality. rand and srand not used because a modulo operation would be needed to get the random number
    uniform_int_distribution <int> distribution (0, rangeMax);              // in the range desired. This implementation is favors lower indices, aka not as random
    int randNum = distribution(generator);                  //random engine is the seed generator with distribution declaring all values in the range are equally as likely to be picked. upper limit taken as parameter

    return randNum;
}

dictionaryWord* DictionaryHash::findWord(string wordToFind)
{
    int hashAddress = hashFunction(wordToFind);
    dictionaryWord* tempWord;

    if(hashTable[hashAddress]->next == NULL)
    {
        return hashTable[hashAddress];
    }
    else
    {
        tempWord = hashTable[hashAddress];

        while  (tempWord->next != NULL)
        {
            if(tempWord->word == wordToFind)
                {
                    return tempWord;
                }
            else
                {
                    tempWord = tempWord->next;
                }
        }

        if(tempWord->word == wordToFind) return tempWord;
        else
        {
            dictionaryWord* emptyWord = NULL;       //return null pointer if word not found.
            return emptyWord;
        }
    }
}

void DictionaryHash::addToFavorites(dictionaryWord* wordFavorite)
{
    favoriteWords.push_back(wordFavorite);
}

dictionaryWord* DictionaryHash::getRandomType(string wordType)  //use the parameter(can only be one of three things, strings used instead of int for readability) to set what type of random word
{
    dictionaryWord* tempWord;

    if(wordType == "noun")
    {
            return nounVector[randomNumber(nounVector.size())];
    }
    else if (wordType == "verb") return verbVector[randomNumber(verbVector.size())];
    else return adjVector[randomNumber(adjVector.size())];
}

void DictionaryHash::displayFavorites()
{
    dictionaryWord* tempWord;

    for(int i = 0; i < favoriteWords.size(); i++)
    {
        tempWord = favoriteWords[i];
        cout << i+1 << ":  " << tempWord->word << ":" << "\n" << "\t" << tempWord->definition << "\n" << endl;
    }
}

string DictionaryHash::createAdlib(string baseSentence)
{
    string adLib;
    int index;
    string replaceElement;
    string workingSentence = baseSentence;

    while(workingSentence.find("*") != string::npos)    //while statement continues to look for key words until there are no more in the parameter string sentence
    {
        index = workingSentence.find("*");
        replaceElement = workingSentence.substr(index + 1, 4);

        if(replaceElement == "noun") workingSentence.replace(index, 5, getRandomType("noun")->word);
        else if (replaceElement == "verb") workingSentence.replace(index, 5, getRandomType("verb")->word);
        else workingSentence.replace(index, 5, getRandomType("adjective")->word);

    }

    return workingSentence;
}










