/*********************************************************************************
*
* Author:           Allyson Warren
* Email:            allywarren7@gmail.com
* Label:            P03
* Title:            Processing in Log Time
* Course:           3013
* Semester:         Spring 2021
*
* Description:
*       This program takes words and definition from a json file and places
*       the word and definition separately into a binary search tree. The tree will
*       be sorted due to the JsonFacade class. The tree will ensure that it is balanced
*       by finding the middle of the sorted list and branching off each middle section
*       so that the search will maintain logn time. After the tree is formed in 
*       O(n) time, the program will then prompt the user to type in a letter
*       and show how many words were found that matched with the letter typed. 
*       After each letter is typed, the computer will then continue to display how
*       many similar words appear in the tree and will also give ten suggested words
*       from the tree found first believed to be the word that is being typed by the 
*       user. The program also displays how long it takes to find all similar words 
*       and will display the time as well to the screen. As each letter is typed to 
*       the screen from the user the search will adjust accordingly and display any
*       matches.
* Usage:
*       None for now
*
* Files:
*       main.cpp         :  driver program
*       dict_w_defs.json :  file containing words and definitions to be put in tree
*       json.hpp         :  program to handle and retrieve dict_w_defs.json
*       JsonFacade.hpp   :  program to condense json.hpp
*       mygetch.hpp      :  program to allow getching and user input
*       timer.hpp        :  program to time how long it takes to find similar words
*       trio.hpp         :  program to help with formatting screen ouput
*       termcolor.hpp    :  program to allow for color change in the console
*
*******************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include "JsonFacade.hpp"       
#include "mygetch.hpp"
#include "trio.hpp"
#include "termcolor.hpp"
#include <time.h>
#include <chrono> 
#include "timer.hpp"            

using namespace std;

/**
 * wordNode
 *
 * Description:
 *      Class to store the word and definition from the json file.
 *      This class is only called and used in the List class. The 
 *      class also handles any letter or word manipulation/searching.
 *
 * Public Methods:
 *      - wordNode()
 *      - wordNode(string, string)
 *      - string getWord()
 *      - char getLetter()
 * 
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  wordNode Q;
 *  wordNode Q("word", "defs");
 *  Q.getWord();
 *  Q.getLetter();
 * 
 */
class wordNode
{
  private:
    string Word;        //String for each defintion's word
    string Definition;  //String for the entire definition

  public:
    /**
    * WordNode:
    *    Default Constructor. Sets both strings to NULL
    * Params:
    *    None
    *
    * Returns:
    *     Void
    */
    wordNode()
    {
        Word = "";
        Definition = "";
    }

    /**
    * WordNode(string, string):
    *    Constructor that sets the two private strings to
    *     a specific string.
    * Params:
    *    1 string   : word to be placed into list
    *    1 string   : definition of word to be placed in list
    *
    * Returns:
    *     Void
    */
    wordNode(string w, string def)
    {
        Word = w;
        Definition = def;
    }

    /**
    * Public: getWord
    *    Getter function to return entire word. Only returns
    *    the main word and not the definition.
    * Params:
    *    None
    *
    * Returns:
    *     String    :  Definition word
    */
    string getWord()
    {
        return Word;
    }
};

/**
 * Node
 *
 * Description:
 *      A struct to create all nodes for the binary search tree
 *      This function is only called in the BinarySearchTree class.
 *
 * Public Methods:
 *      - None
 * 
 * Private Methods:
 *      - None
 *
 * Usage:
 *     N/A
 *
 */
struct Node
{
    wordNode* Data; //Place to store any wordNode data in list
    Node *left;     //Address of the left node of a parent node (smaller value than parent)
    Node *right;    //Address of the right node (greater value than parent)
};	

/**
 * BinarySearchTree
 *
 * Description:
 *      A binary search tree class to hold the words and definition from
 *      the json file. The class keeps track of the tree's root and
 *      recursively traverses through to find a desired string. The tree
 *      finds a desired string in log(n) time and stores the first 10 matching
 *      strings found into a array of size 10 to be displayed when called in the 
 *      Suggestions method. The tree can be filled by using the Fill method which 
 *      takes in an instance of the JsonFacade class and puts the words from
 *      the json file into the tree. 
 *      
 *
 * Public Methods:
 *      - BinarySearchTree()
 *      - void Fill(JsonFacade)
 *      - int Find(string)
 *      - void Suggestions(int)
 * 
 * Private Methods:
 *      - Node* Insert(vector<string> &, vector<string> &, int, int)
 *      - int Find(Node*, string, int)
 *
 * Usage:
 *
 *  BinarySearchTree J;
 *  J.Fill(JsonF);
 *  J.Find("Hello");
 *  J.Suggestions(37);
 *  Insert(vect, vect2, 5, 20);
 *  Find(root, "Hello", 2);
 * 
 */
class BinarySearchTree
{
  private:
    Node* Head;                //Points the front of the tree
    Node* Current;             //Points to last placed viewed in list
    int size;                  //Size of the list
    vector<string> keys;       //Vector of words in json object
    vector<string> values;     //Vector of defs in json object
    string suggestedWords[10]; //Array of 10 suggested words found

  public:
    /**
    * List
    *    Default constructor for binary tree class. Sets everything 
    *    to nothing(NULL, 0 , "", etc.)
    * Params:
    *    None
    *
    * Returns:
    *    Void
    */
    BinarySearchTree()
    {
        Head = NULL;        //No items in list yet
        Current = NULL;     //Not on a specific node yet
        size = 0;           //Tree is empty
    }

    /**
    * Public: Fill
    *    This function fills the list with values given from a JsonFacade class
    *    that gets words and definitions from a json file. The method 
    *    then calls the Insert function to directly place the items into
    *    the binary search tree. Insert is separate from fill as Insert handles placing
    *    items into the tree directlhy while Fill handles all json implementation. 
    * Params:
    *    JsonFacade :   Class containing words and defintions to place into tree
    *
    * Returns:
    *    Void
    */
    void Fill(JsonFacade J)
    {
        keys = J.getKeys();          //Get vector of all words for list
        values = J.getValues();      //Get vector of all defs for list
        size = keys.size();          //Size of vector = size of list

        Head = Insert(keys, values, 0, size-1); //Implement tree recursively. Head is root of tree
    }

    /**
    * Public: Find
    *    This function compares all words in the list to the current typed word
    *    and only compares a substring with the same length from the dictionary word.
    *    This function hides all the innerworkings of the tree and its nodes. It allows 
    *    for anything outside of the class to compare a string without showing and relying on
    *    it to know how its achieved. This method calls the private Find function to actually
    *    begin the search and recursively return how many matches were found in the tree. 
    * Params:
    *    string   :   typed word to compare with tree's node word
    *
    * Returns:
    *     int   :   Total number of similar words in list
    */
    int Find(string word)
    {
        return Find(Head, word, 0); //Call private method to traverse through tree
                                    //No words have been found yet
    }

  
    /**
    * Public: Suggestions
    *    This function returns words that closely match the word
    *    typed by the user. If there are more than ten words that
    *    match the input, then the function prints the first
    *    ten matching words in the tree unless there are less.
    *    Otherwise, it will return all matching words if less 
    *    than 10 only. The 10 words printed are the first 10
    *    found in the tree. The first match printed will appear
    *    red while the rest will show as default white on the console.
    * Params:
    *    int    :   # of words found to match input
    *
    * Returns:
    *    void
    */
    void Suggestions(int total)
    {
        int words = 0;          //Number of words already printed

        //Continue until 10 words found, no more matches, or end of list
        while(words < 10 && words < total)
        {
            if(words == 0)      //First suggested word is printed in red
            {
              cout << termcolor::red;
            }

            cout << suggestedWords[words] + "  ";  //Print word to screen
            cout << termcolor::reset;              //Print in normal color

            words++;                               //Increment words to suggest
        }

    }

  private:  
    /**
    * Private: Insert
    *    Function to directly place words and definitions into
    *    the binary tree. Through recursion and binary searching, 
    *    the tree is ensured that it is balanced when implemented and
    *    allows for logn search time. Each new node stores a word and 
    *    definition into a wordNode and then its left and right child is
    *    created and also called to be implemented. This method is only called
    *    in this class.
    * Params:
    *    vector<string>& : address of vector of words
    *    vector<string>& : address of vector of definitions
    *    int             : beginning of search index
    *    int             : end of search index
    *
    * Returns:
    *    Node*  : new Node added to the end of tree
    */
    Node* Insert(vector<string> &keys, vector<string> &values, int start, int end)
    {
        if(start > end) //At the start or end of vector search
        {
            return NULL;
        }

        int middle = (start+end)/2; //Get middle to binary traverse for balanced tree

        Node* root = new Node;                                  //Create a new node/leaf
        root->Data = new wordNode(keys[middle], values[middle]);//Store new data into leaf


        root->left = Insert(keys, values, start,  middle - 1);  //Create left side of branch
        root->right = Insert(keys, values, middle + 1, end);    //Create right side of branch

        return root;
       
    } 

    /**
    * Private: Find
    *    This function compares all words in the list to the current typed word
    *    and only compares a substring with the same length from the dictionary word.
    *    The strings are compared using the compare method in the string library in 
    *    which it total the ascii value of the typed word with the matching substring
    *    of the tree's word. It then subtracts the two values. If the strings match
    *    then the value will be 0 and the tree branches off both left and right to 
    *    continue to see if more matches are nearby. If the subtracted value is a 
    *    negative number then the dictionary word is after the desired word in the
    *    alphabet and only the left side of the node will be traversed as none of the 
    *    right side can match. Similarly, if the subtraction is greater than 0, the
    *    substring is before the typed word in the alphabet and only the right side of
    *    the current node is traversed. This allows for log(n) search time where not 
    *    all of the tree has to be searched to find all matches. The method also fills
    *    an array of size 10 with the first ten matching words fourd in the tree to be
    *    printed later in the Suggestions function. The function returns the total 
    *    number of matches found in the tree through recursion.
    * Params:
    *    Node*    :   current root node to compare with string
    *    string   :   typed word to compare with tree's node word
    *    int      :   number of words placed into array of matches
    *
    * Returns:
    *     int   :   Total number of similar words in list
    */
    int Find(Node* root, string word, int matches)
    {
        int SuggestedSum = matches; //Number of words already added to suggestions

        if(root == NULL)//AT the end of tree branch, Base case
        {
          return 0;     //Go back to previous call
        }

        string DictWord;                   //Store word from tree to compare
        
        DictWord = root->Data->getWord();  //Get each dictionary word

        int comparison = DictWord.compare(0, word.size(), word);//Get difference of ascii values from strings


        if(comparison == 0)                         //Word matches substring
        {       
          if(SuggestedSum < 10)     //Place first 10 matches into array
          {
            suggestedWords[SuggestedSum] = DictWord;//Add word to suggested words
            SuggestedSum++;                         //Word has been added to vector/ size increments
          }
                                                    //Continue looking for matches
          return 1 + Find(root->right, word, SuggestedSum) + Find(root->left, word, SuggestedSum); //save # of matches
        }


        else if(comparison < 0)                     //Word is after root word
        {
                                                    //Only search right side of branch
          return Find(root->right, word, SuggestedSum);
        }

        else                                        //Word is before root word in alphabet
        {
                                                    //Only search left side of branch
          return Find(root->left, word, SuggestedSum);
        }
    }
};



int main() 
{
    BinarySearchTree WordDefs;          //Create binary tree
    JsonFacade J("dict_w_defs.json");   //Create instance of json class
    Timer T;                            //Create timer
    double sec;                         //Number of seconds of timer
    long millsec;                       //Number of milliseconds of timer
    trio::IO io;                        //Create instance of IO 
    char letter;                        //Letter to look at from input
    string word = "";                   //Total word being typed by user
    int total;                          //total matches found in list
    int wordSize = 0;                   //Size of typed word

    WordDefs.Fill(J);                   //Fill tree w/ dictionary words
    
    cout << setprecision(3) << "input: ";//Prompt user to type & set decimals

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
        cout << termcolor::red << word; //Word is printed red
        cout << termcolor::reset <<'\n';//Reset coloring to normal

        T.Start();                      //Begin timer to look for matches
        total = WordDefs.Find(word);    //Total is # of all matches found

        cout << termcolor::red << total;//Typed word is shown in red
        cout << termcolor::reset;       //Go back to normal ouput
        cout << " words found in ";
        T.End();                        //End timer- all matches have been found

        sec = T.Seconds();              //Set to number of seconds
        millsec = T.MilliSeconds();     //Set to number of milliseconds
        
        cout << setw(4) << sec << " seconds" << endl; //Diplay time to find matches
        WordDefs.Suggestions(total);                  //Display suggested matches
        io << endWord;                                //Place cursor after typed word
        
    }
}