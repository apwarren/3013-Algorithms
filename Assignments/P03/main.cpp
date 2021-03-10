/*********************************************************************************
*
* Author:           Allyson Warren
* Email:            allywarren7@gmail.com
* Label:            P02
* Title:            Processing in Linear Time
* Course:           3013
* Semester:         Spring 2021
*
* Description:
*       This program takes words and definition from a json file and places
*       the word and definition separately into a linked list. The list will
*       be sorted due to the JsonFacade class. After the list is sorted in 
*       O(n) time, the program will then prompt the user to type in a letter
*       and show how many words were found that matched with the letter typed. 
*       AFter each letter is typed, the computer will then continue to display how
*       many similar words appear in the list and will also give ten suggested words
*       from the list that it believes to be the word that is being typed by the 
*       user. The program also displays how long it takes to find all similar words 
*       and will display the time as well to the screen. As each letter is typed to 
*       the screen from the user the search will become faster as the program 
*       continues to look for similar words based on the last search it did. 
* Usage:
*       None for now
*
* Files:
*       main.cpp         :  driver program
*       dict_w_defs.json :  file containing words and definitions to be put in list
*       json.hpp         :  program to handle and retrieve dict_w_defs.json
*       JsonFacade.hpp   :  program to condense json.hpp
*       mygetch.hpp      :  program to allow getching and user input
*       Timer.hpp        :  program to time how long it takes to find similar words
*       trio.hpp         :  program to help with formatting screen ouput
*
*******************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include "JsonFacade.hpp"       // need to grab a copy from resources folder
#include "mygetch.hpp"
#include "trio.hpp"
#include "termcolor.hpp"
#include <time.h>
#include <chrono> 
#include "timer.hpp"            // need to grab a copy from resources folder
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
    *    Default Constructor. Sets both string to NULL
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
    *    Constructor that sets the two private string to
    *     a specific strings.
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
 *      A struct to create all nodes in the linked list.
 *      This function is only called in the List class.
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
    Node *left;     //Address of the left node of a parent node
    Node *right;    //Address of the right node (greater value than parent)
};	

Node* newNode(wordNode data);
/**
 * List
 *
 * Description:
 *      A linked list class to hold the words and definition from
 *      the json file. The class also keeps track of both the front and
 *      back of the list as well as the last placed viewed in the list
 *      locations.  The list can compare letters of words and also 
 *      search in the list for any words that may be similar to a given
 *      word and count how many are in the list. 
 *      
 *
 * Public Methods:
 *      - List()
 *      - void Insert(string, string)
 *      - void Fill(JsonFacade)
 *      - int Find(char)
 *      - string Suggestions(int)
 * 
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  List J;
 *  J.Insert("word", "word2");
 *  J.Fill(JsonF);
 *  J.Find('y');
 *  J.Suggestions(37);
 * 
 */
class BinarySearchTree
{
  private:
    Node* Head;           //Points the front of the tree
    Node* Current;        //Points to last placed viewed in list
    int size;             //Size of the list
    int index;            //Index of letter to compare
    vector<string> keys;  //Vector of words in json object
    vector<string> values;//Vector of defs in json object
    string suggestedWords[10]; //Array of 10 suggested words found
    bool Found;           //Flag to see if letter has been found

  public:
    /**
    * List
    *    Default constructor for list class. Sets everything 
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
    * Public: Insert
    *    Function to directly place words and definitions into
    *    the binary tree. Through recursion and binary searching, 
    *    the tree is ensured that it is implemented balanced and is
    *    allowed for logn search time. Each new node stores a word and 
    *    definition into a wordNode and then its left and right child is
    *    created and also called to be implemented. 
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
      if(start > end) //At the start or end of word array
      {
        return NULL;
      }

        int middle = (start+end)/2;

        Node* root = new Node;                                  //Create a new node/leaf
        root->Data = new wordNode(keys[middle], values[middle]);//Store new data into leaf

        root->left = Insert(keys, values, start,  middle - 1); //Create left side of branch

        root->right = Insert(keys, values, middle + 1, end); //Create right side of branch

        return root;
       
    } 

    /**
    * Public: Fill
    *    This function fills the list with values given from a JsonFacade class
    *    that gets words and definitions from a json file. The method 
    *    then calls the Insert function to directly place the items into
    *    the binary search tree. Insert is separate from fill as Insert handles placing
    *    items into the tree directlhy while Fill handles all json implementation. 
    * Params:
    *    JsonFacade :   Class containing words and defintions to place into list
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
    *    This function compares all words in the list to a given letter
    *    and keeps track of how many words contain the letter at that index.
    *    If the letter is found then the count will start until that letter 
    *    no longer matches. The list is sorted so it works. The location of 
    *    the letter is also taken into consideration; for instance: If it has 
    *    already found all 'W' words then it can compare the next letter in the 
    *    word to minimize the list. 
    * Params:
    *    string   :   typed word to compare with tree's node word
    *
    * Returns:
    *     int   :   Total number of similar words in list
    */
    int Find(string word)
    {
        return Find(Head, word, 0); //Call private method to traverse through tree
    }

  
    /**
    * Public: Suggestions
    *    This function returns words that closely match the word
    *    typed by the user. If there are more than ten words that
    *    match the input, then the function prints the first
    *    ten matching words in the list unless there are less.
    *    Otherwise, it will return all matching words if less 
    *    than 10 only. 
    * Params:
    *    int    :   # of words found to match input
    *
    * Returns:
    *    string :   first 10 or less similar words to input
    */
    void Suggestions(int total)
    {
        string suggests = "";   //All words that currently match
        int words = 0;          //Number of words added to string
        //Continue until 10 words found, no more matches, or end of list
        while(words < 10 && words < total)
        {
            if(words == 0)//First suggested word is printed in red
            {
              cout << termcolor::red;
            }
            cout << suggestedWords[words] + "  ";  //Print word to screen
            cout << termcolor::reset;              //Print in normal color
            words++;                               //Increment words to suggest
        }

    }
  private:
    int Find(Node* root, string word, int matches)
    {
        int SuggestedSum = matches; //Number of words added to suggestions
        if(root == NULL)//AT the end of tree branch, No more leaves
        {
          return 0;
        }
        string DictWord;    //Store word from tree to compare
        
        DictWord = root->Data->getWord();  //Get each dictionary word

        int comparison = DictWord.compare(0, word.size(), word);//Compare ascii values of words

        if(comparison == 0)//Word matches substring
        {       
          if(SuggestedSum < 10) 
          {
            suggestedWords[SuggestedSum] = DictWord;  //Add word to suggested words
            SuggestedSum++;                    //Word has been added to vector/ size increments
          }
          return 1 + Find(root->right, word, SuggestedSum) + Find(root->left, word, SuggestedSum); //save # of matches
        }
        else if(comparison < 0)//Word is after root word
        {
          return Find(root->right, word, SuggestedSum);
        }
        else  //Word is before root word in alphabet
        {
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

    WordDefs.Fill(J);    //Fill tree w/ dictionary words
    
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

        T.Start();                    //Begin timer to look for matches
        total = WordDefs.Find(word);  //Total is # of all matches found

        cout << termcolor::red << total;//Typed word is shown in red
        cout << termcolor::reset;       //Go back to normal ouput
        cout << " words found in ";
        T.End();                        //End timer- all matches have been found

        sec = T.Seconds();              //Set to number of seconds
        millsec = T.MilliSeconds();     //Set to number of milliseconds
        
        cout << setw(4) << sec << " seconds" << endl; //Diplay time to find matches
        WordDefs.Suggestions(total);
        io << endWord; //Display suggested matches
        
    }
}