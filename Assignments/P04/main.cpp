/*********************************************************************************
*
* Author:           Allyson Warren
* Email:            allywarren7@gmail.com
* Label:            P04
* Title:            Processing in Trie Time
* Course:           3013
* Semester:         Spring 2021
*
* Description:
*       This program takes words from a text file and places
*       the word into a Trie Tree data structure. This tree allows for words
*       to be found from a list in O(MxNxC) time where N is the total number
*       of strings, M is the longest string length, and C is the alphabet size.
*       The program will then prompt the user to type in a letter and show how
*       many words were found that matched with the letter typed. AFter each 
*       letter is typed, the computer will then continue to display how many 
*       similar words appear in the Trie and will also give ten suggested words 
*       from the Trie that it believes to be the word that is being typed by the 
*       user. The program also displays how long it takes to find all similar words
*       and will also display this time to the screen. The typed word will appear 
*       in red on the screen as well as the time and first suggested word in the list.
* Usage:
*       None for now
*
* Files:
*       main.cpp         :  driver program
*       dictionary.txt   :  file containing words to be put in Trie
*       mygetch.hpp      :  program to allow getching and user input
*       timer.hpp        :  program to time how long it takes to find similar words
*       termcolor.hpp    :  program to help with formatting screen ouput
*       trio.hpp         :  program to help with formatting screen ouput
*
*******************************************************************************/

#include <fstream>
#include <iostream>
#include <vector>
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "trio.hpp"
#include "timer.hpp"

using namespace std;


/**
 * TrieNode
 *
  * Description:
 *      A struct to create all nodes in the Trie Tree.
 *      This function is only called in the Trie class.
 *      Each node keeps a flag to know if a word ends 
 *      at its location and will create and point to
 *      26 individual pointers, each one representing
 *      a letter of the alphabet to move to for the next
 *      letter in the word. 
 * 
 * Public Methods:
 *      - TrieNode()
 * 
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  TrieNode Q;
 * 
 */
struct TrieNode 
{
    bool isLeaf;                //Flag to determine if a word ends here
    TrieNode *character[26];    //Point to all letters of alphabet

    /**
    * WordNode:
    *    Default Constructor. Sets node to not be a
    *    complete word and creates NULL alphabet pointers for
    *   node to point at. 
    *   
    * Params:
    *    None
    *
    * Returns:
    *     Void
    */
    TrieNode() 
    {
        this->isLeaf = false;            //Not yet considered the end of a word

        for (int i = 0; i < 26; i++)     //Create pointer for each alphabet letter
        {
            this->character[i] = nullptr;//Set each pointer to NULL, no new letter yet
        }
    }
};

/**
 * Trie
 *
 * Description:
 *      A Trie Tree class to hold the words from the txt file. The trie
 *      stores words by its individual letters pointing to a TrieNode containing
 *      the next letter in the word. When the last letter of a word is added to 
 *      the Trie tree, then the node for that letter will be marked true as a word
 *      to indicate that a word ends at this TrieNode. When a given word is typed
 *      the user, the class can determine how many substrings match the given word
 *      and store the words in a vector to print out the first ten matching words
 *      and the total numbers of matches found overall in the Trie tree.
 *      
 *
 * Public Methods:
 *      - Trie()
 *      - void Insert(string)
 *      - int find_all(string)
 *      - void PrintSuggested()
 * 
 * Private Methods:
 *      - void find_all(TrieNode*&, string)
 *
 * Usage:
 *
 *  Trie J;
 *  J.Insert("dict_word");
 *  int num = J.find_all("words");
 *  J.PrintSuggested();
 * 
 */
class Trie 
{
  private:
    TrieNode *root;         //Head of the Trie tree, pointing to alphabet
    vector<string> results; //Vector of matching words

  public:
    /**
    * Trie
    *    Default constructor for Trie class. Creates a TrieNode
    *    pointing to all 26 letters of the alphabet with each pointer
    *    set to NULL.
    * Params:
    *    None
    *
    * Returns:
    *    Void
    */
    Trie() 
    {
        root = new TrieNode;
    }

    /**
    * Public: insert
    *    Function to directly place words into
    *    the Trie. Traverses through each letter of the word
    *    and if the Trie tree does not point to the next letter, then
    *    it will create a new TrieNode to go the the next letter. Once the
    *    last letter of the word has been reached, then the function will 
    *    set the last letter's pointer isLeaf to true to indicate that a 
    *    word ends at that location. 
    * Params:
    *    string :   word string to go into data
    *
    * Returns:
    *    void
    */
    void insert(string word) 
    {
        TrieNode *currentLetter = root;           // start from the root node

        for (int i = 0; i < word.length(); i++)   //Continue until the last letter of word
        {

            //Create a new node if path doesn't exist
            if (currentLetter->character[word[i] - 97] == nullptr)
            {
                  //Implement new TrieNode
                currentLetter->character[word[i] - 97] = new TrieNode();
            }

            //Go to next letter's node of the word
            currentLetter = currentLetter->character[word[i] - 97];
        }

            //Last letter of word/ Mark Node as complete word/leaf
        currentLetter->isLeaf = true;

    }

    /**
    * Public: find_all
    *    This function takes a given word and traverses through the Trie
    *    to find all matching words and stores the matches in a vector. 
    *    This function calls the private find_all method to go through
    *    the tree recursively once it reaches to typed word's substring.
    *    After finding and storing all matches, the function then returns
    *    the size of the vector to give the total number of matches found. 
    * Params:
    *    string   :  Substring word to find matches of in tree
    *
    * Returns:
    *     int   :   Total number of similar words in Trie tree
    */
    int find_all(string Word)
    {
        TrieNode* currentLetter = root;         //Start at the beginning of tree

        results.clear();                        //Remove previous matches from vector

        for (int i = 0; i < Word.length(); i++) //Traverse through tree until pointing 
                                                //  at last letter of typed word
        {   
              //Word doesn't exist in Trie Tree
            if (currentLetter->character[Word[i] - 97] == nullptr) 
            {
                return 0;       //No words match: leave function
            }                                    
              //Move to next letter node
            currentLetter = currentLetter->character[Word[i] - 97]; 

        }

        find_all(currentLetter, Word);          //Call private function to find matches

        return results.size();                  //Return number of matches found

    }

    /**
    * Public: PrintSuggested
    *    This function prints out the first 10 words found in 
    *    the Trie tree that matches with the typed word given by
    *    the user. The matches are found through the find_all method
    *    and stored into the vector results. This function prints
    *    out the first 10 words of that vector to the screen. If less
    *    than 10 words match in the Trie then the function will
    *    only print out the number of matches in the vector. The
    *    first word printed will be colored red and the rest of 
    *    the matching words will be printed in normal color. 
    * Params:
    *    None
    *
    * Returns:
    *     Void
    */
    void PrintSuggested()
  {
    if(results.size() >= 10)        //At least 10 matches found
    {
      for (int i = 0; i < 10; i++)  //Print out first 10 matches
      {
        if(i == 0)                  //First word to be printed
        {
        cout << termcolor::red;     //Print in red color
        }

        cout << results[i] << "   ";//Print matching word to screen
        cout << termcolor::reset;   //Print in normal color
      }
    }

    else                            //Less than 10 words match in tree
    {
      for (int i = 0; i < results.size(); i++) 
      {                             //Print all matches found
        if(i == 0)
        {
        cout << termcolor::red;     //Print first word in red
        }
        cout << results[i] << "   ";//Print matching word to screen
        cout << termcolor::reset;   //Print in normal color
      }
    }
  }

  private:
    /**
    * Private: find_all
    *    This function is called from the public find_all
    *    method to traverse through the trie tree and find all
    *    nodes that are marked as a word(Leaf). This function gets
    *    called once the substring to be matched has already been pointed
    *    to and now each alphabet pointer of the last letter of the given 
    *    word is to be looked at to find all paths leading to a word. If 
    *    a word is found then it is added to the vector results to be stored
    *    in order to know the total matches and suggestions.
    * Params:
    *    TrieNode*&   : Location pointing to next letter to be checked for words
    *    string       : Current set of letters making up a possible word
    *
    * Returns:
    *    None
    */
    void find_all(TrieNode *&curr,string word)
    {
        if(curr->isLeaf)            //The node is the last letter of a word
        {
          results.push_back(word);  //Add the word to the vector of matches
        }

        for (int i = 0; i < 26; i++)//Look to see is more words come after letter in string
        {
          if(curr->character[i])    //Check entire alphabet for any locations of TrieNodes-not NULL
          {
            find_all(curr->character[i], word+char(i+97));  //Traverse through found match letter
                                                            //Add letter to currently formed word
          }
        }
      
    }
};

int main() 
{
    Trie *DictWords = new Trie();       //Create Trie tree 
    Timer clock;                        //Create timer
    ifstream infile;                    //Open input file
    infile.open("dictionary.txt");      //Open file of dictionary words
    double sec;                         //Number of seconds of timer
    trio::IO io;                        //Create instance of IO 
    char letter;                        //Letter to look at from input
    string word = "";                   //Total word being typed by user
    string FileWord;                    //Input file word to add to trie tree
    int total;                          //Total matches found in list
    int wordSize = 0;                   //Size of typed word

    while (!infile.eof()) 
    {
        infile >> FileWord;             //Get words from text file
        DictWords->insert(FileWord);    //Add words to the Trie tree
    }
    cout << "input: ";                  //Prompt user to type

                                        //Continue until user presses enter
    while ((int)(letter = getch()) != 10) 
    {
        wordSize++;                    //User has pressed a key

        if((int)letter == 127)         //If the input is a backspace
        {
          if(wordSize > 0)             //A letter has been pressed previously
          {
            word.erase(wordSize-2, 1); //Remove last letter typed
            wordSize-=2;               //Size is now 1 less than before
          }
        }

        else                            //Input is a character
        {
          word += letter;               //Add letter pressed to total word
        }

        trio :: clear_screen();                   //Clear the screen
        trio :: Point front(1,0);                 //Set the pointer to top of list
        trio :: Point endWord(1, (wordSize + 7)); //Set point to back of typed word

        //Print current word to screen
        io<< front << "input: ";
        cout << termcolor::red << word;   //Word is printed red
        cout << termcolor::reset <<'\n';  //Reset coloring to normal

        clock.Start();                    //Begin timer to look for matches
        total = DictWords->find_all(word);//Total is # of all matches found

        cout << termcolor::red << total;  //Typed word is shown in red
        cout << termcolor::reset;         //Go back to normal ouput
        cout << " words found in ";
        clock.End();                      //End timer- all matches have been found

        sec = clock.Seconds();            //Set to number of seconds        
        cout << sec << " seconds" << endl;//Diplay time to find matches
        DictWords->PrintSuggested();      //Display suggested matches
        io << endWord;                    
        
    }
}