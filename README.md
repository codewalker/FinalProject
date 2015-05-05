# CSCI2270: Final Project README
Trevor Stephens; github ID: codewalker

PROJECT SUMMARY:

In this program I started with a raw text file of the oxford english dictionary. The program is encapsulated in the class but the entire program is dependent, without some degree of tailoring, on the specific dictionary text file and its organization of lines. The program stores the words from the file into a hash table along with specific vectors depending on types. This allows for word look up to find the word's definition. The program also has a "word of the day" functionality to generate a random word from the dictionary to display. The user can find random words as many times as he/she wants. There is also an option to save interesting words to a favorites container along with the ability to randomly generate specific types of words, i.e. adj, v, and nouns. The program also uses a random number generator to have the user create adlib sentences that are then "completed" by filling the gaps with random words of the right type.


HOW TO RUN: clone repo, make folder with all files included (especially the dictionary). Open the two .cpp files and the one .h file in codeblocks. add one to a new project. add the others by right clicking on the tabs and selecting 'add to current project'. build. compile. Drop me a line if there are issues or this method is rudimentary.

DEPENDENCIES: This program only uses the basic cpp libraries. The only glaring dependency is on the use of the oxford dictionary text file which is included in the repo. 

SYSTEM REQUIREMENTS:  run on the cuvm and windows 7. untested on MAC OS.  win32.

CONTRIBUTORS: Just the author currently.

OPEN ISSUES/BUGS: 
  1. Some of the words in the dictionary are not standard ASCII 128 characters. This causes some printing issues where the hex key is shown instead of the correct character. This also causes a currently mitigated complication with hashing.
  2. The only word types the program is set up for is nouns, verbs and adjectives. Some words of these types are still not identified as such due to one word having multiple stated types in the definition but not in an organized, consistent location. 
  3. some words that have multiple meanings are relisted with the a number at the end. The program doesn't handle these instances.

