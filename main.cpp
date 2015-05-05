#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include "DictionaryHash.h"


using namespace std;

int getInt(istream &is);    //single helper function for getting int from cin


int main()
{
    string fileName = "Oxford_English_Dictionary.txt";  //txt file to be read in by Dictionary Hash Class. Entire class is built around the specifics of this file, thus the file
                                                                                        // was hard coded to prevent the accidental use of other files via command line arguments
    DictionaryHash newHash = DictionaryHash(newHash.hashTableSize(fileName));   //creation of class object, the constructer takes an int parameter, in this case, the amount of words in the dictionary file.
                                                                                                                                        // by calling the appropriate function after declaring the new object
    cout << "There are " << newHash.hashTableSize(fileName) << " words in the Oxford English Dictionary" << endl;   //print number of words in the dictionary to screen with same function

    newHash.readInDictionary(fileName); //call class function to read in data from dictionary txt file into the Dictionary Hash object


 int menuTracker = 0;   // int variable used for flow control pertaining to main menu options


while ( menuTracker < 1){                           //main menu, reprints after each selection
    cout << "OXFORD ENGLISH DICTIONARY" << endl;
    cout <<	"======Main Menu======" << endl;                    //MAIN MENU printed to screen
    cout <<	"1. Random Dictionary Word" << endl;
    cout <<	"2. Display Favorite Words" << endl;
    cout << "3. Find Word" << endl;
    cout <<	"4. Make Adlib" << endl;
    cout << "5. Quit" << endl;

    int command = getInt(cin);      //user input in response to main menu

if ( command == 1){

    dictionaryWord* randomWord; //pointer to assign word structs accessed by public methods to
    int randomCommand = 0;  //int for flow control of random word sub menu

    while(randomCommand != 1)
    {
            cout << "What type of word would you like?" << endl;
            cout << "=============" << endl;
            cout << "1. Noun" << endl;
            cout << "2. Verb" << endl;
            cout << "3. Adjective" << endl;
            cout << "4. Any type of word will do" << endl;
            cout << "5. Return to Main Menu" << endl;

            int selection = getInt(cin);    //user input in response to sub menu

            if (selection ==1)
            {
                randomWord = newHash.getRandomType("noun");     //get random noun from class object
            }
            else if(selection == 2)
            {
                randomWord = newHash.getRandomType("verb");     //get random verb
            }
            else if (selection == 3)
            {
                randomWord = newHash.getRandomType("adj");  //get random adjective
            }
            else if (selection == 4)
            {
                randomWord = newHash.RandomWordGenerator();     //get random word struct from hash table in class object

            }
            else
            {
                randomCommand = 1;      //quit command with break to immediately exit sub menu
                break;
            }

            cout << "\n" << randomWord->word <<  " = " << endl;             //print specified random word to screen with definition
            cout << "\t" << randomWord->definition << "\n" << endl;

            cout << "Would you like to add this word to your favorites?" << endl;   //choice of user to add displayed word to favorites
            cout << "1. Yes" << endl;
            cout << "2. No" << "\n" << endl;


            selection = getInt(cin);
            if (selection == 1) newHash.addToFavorites(randomWord); //public method for saving a new favorite word struct
    }
}

else if (command == 2){

        newHash.displayFavorites();     //display all words marked as favorites

    }

else if (command == 3){

            cout << "\n" << "Enter a word to search Oxford Dictionary for. (begin your word with a capital letter)" << endl;
            string wordForSearch;
            dictionaryWord* foundWord;                          //print directions to the screen, then getline and a new string used to store user's word

            getline(cin, wordForSearch);
            foundWord = newHash.findWord(wordForSearch);    //method for searching hash table in class object for user defined word

            if(foundWord != NULL)   //condictional to check if the word was found, a null pointer is returned by findWord if no matching word was found
            {
                cout << "\n" << foundWord->word << ":" << "\n" << "\t" << foundWord->definition << "\n" << endl;    //print the found word and definition
            }
            else cout << "Word Not Found" << "\n" << endl;

}

else if (command == 4){

            cout << "Enter a sentence with *<word type> where you want to have random words entered." << "\n" << endl;
            cout << "Example:  The *noun can *verb like a *adje *noun " << "\n" <<   "(*noun = noun, *verb = verb, *adje = adjective)" << "\n" << endl; //printing of instructions for adlib functionality

            string baseSentence;
            getline(cin, baseSentence);     //store the users adlib sentence

            baseSentence = newHash.createAdlib(baseSentence);   //public method that searches for key words to replace with random respective word types

            cout << "\n" << "\t" << baseSentence << "\n" << endl;   // print the new sentence with replaced keys to screen
    }

else if (command == 5){
            menuTracker = 1;        //Quit command, flow control variable set to value that will exit the main menu loop

            cout << "Goodbye!" << endl;
    }
else {
    cout << "That is an invalid input. Please enter a number between 1 and 5." << endl; //default answer printed to screen if one of the specific number commands is not entered by the user
}
}
}

 int getInt(istream &is){   //function for getting int value from user input without using cin.ignore and/or cin.clear
    string input;
    getline(is, input);
    return stoi(input);
}
