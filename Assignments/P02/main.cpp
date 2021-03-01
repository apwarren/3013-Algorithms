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
*       This program takes words from a text file and places
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
*       dictionary.txt   :  file containing words and definitions to be put in list
*       mygetch.hpp      :  program to allow getching and user input
*       Timer.hpp        :  program to time how long it takes to find similar words
*       termcolor.hpp         :  program to help with formatting screen ouput
*
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "trio.hpp"
#include <time.h>
#include <chrono> 
#include "timer.hpp"            // need to grab a copy from resources folder
using namespace std;

/**
 * wordNode
 *
 * Description:
 *      Class to store the word from the dictionary.txt file.
 *      This class is only called and used in the List class. The 
 *      class also handles any letter or word manipulation/searching.
 *
 * Public Methods:
 *      - wordNode()
 *      - wordNode(string)
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
    }

    /**
    * WordNode(string):
    *    Constructor that sets the two private string to
    *     a specific strings.
    * Params:
    *    1 string   : word to be placed into list
    *
    * Returns:
    *     Void
    */
    wordNode(string wor)
    {
        Word = wor;
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
    Node *next;     //Address of the next node in list
};	

/**
 * List
 *
 * Description:
 *      A linked list class to hold the words and definition from
 *      the txt file. The class also keeps track of both the front and
 *      back of the list as well as the last placed viewed in the list
 *      locations.  The list can compare letters of words and also 
 *      search in the list for any words that may be similar to a given
 *      word and count how many are in the list. 
 *      
 *
 * Public Methods:
 *      - List()
 *      - void Insert(string, string)
 *      - void Fill(string)
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
class List
{
  private:
    Node* Head;           //Points the front of the List
    Node* Tail;           //Points to the back of the List
    Node* Current;        //Points to last placed viewed in list
    int size;             //Size of the list
    int total;            //Number of matching words in list compared to input
    int index;            //Index of letter to compare
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
    List()
    {
        Head = NULL;        //No items in list yet
        Current = NULL;
        Tail = NULL;
        size = 0;           //List is empty
    }

    /**
    * Public: Insert
    *    Function to directly place words into
    *    the list. Sets the Tail pointer to last item in list
    *    and the Head pointer to front if the item is first in
    *    the list. The words are placed into a wordNode.
    * Params:
    *    string :   word string to go into data
    *    string :   definition string to go into data space
    *
    * Returns:
    *    void
    */
    void Insert(string Word)
    {
        Node* temp = new Node;               //Create a temporary node
        temp->Data = new wordNode(Word);//Store new data into temp node
        temp->next = NULL;                   //Temp node is last in list

        if (Head == NULL)                    //Temp is first item in list
        {  
            Head = temp;                     //Temp is at front of list
            Current = Head;                  //No current suggestions
            Tail = temp;                     //The end of the list is front of list
            return;  
        } 

        else                                 //There are already items in the list
        {
            Tail->next = temp;               //Tail points to the end of the list
            Tail = temp;                     //Temp is the end of the list
        } 
        return;
    } 

    /**
    * Public: Fill
    *    This function fills the list with values given from a JsonFacade class
    *    that gets words and definitions from a json file. The method 
    *    then calls the Insert function to directly place the items into
    *    the linked list. Fill handles all input reading while the 
    *    Insert function actually places values into the linked list. 
    * Params:
    *    JsonFacade :   Class containing words and defintions to place into list
    *
    * Returns:
    *    Void
    */
    void Fill(string filename)
    {
        ifstream infile;      //Open dictionary word file
        infile.open(filename);

        string word;          //Dictionary word to be stored

        //Fill in linked list
        while(!infile.eof())  //Read until end of file
        {
          infile >> word;     //Get word from input file
          Insert(word);       //Place word into list
        }
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
    *    char   :   Letter to compare with words in list
    *
    * Returns:
    *     int   :   Total number of similar words in list
    */
    int Find(string word)
    {
        Node* temp = Head;            //Start search at list beginning
        Found = false;                //No matches have been found
        total = 0;                    //There are no similar words yet
        string DictWord;

        while(temp != NULL && !Found) //Keep going unless at end or found all match
        {         
            DictWord = temp->Data->getWord();  //Get each dictionary word
                                               //Word contains current typing
            if(DictWord.compare(0,word.size(), word) == 0)
            {
                if(total == 0)            
                {
                    Current = temp;       //Set current to first found match in list
                }

                total++;                  //Increment total number of matches
            }

            else                          //Letters do not match
            {
                if(total != 0)            //All macthes have been found
                {
                Found = true;             //Can stop searching
                }
            }
            
            temp = temp->next;            //Move to next word in list
        }

        return total;                     //Return number of matches found
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
        Node* temp = Current;   //Temp node that points to first matching word
        int words = 0;          //Number of words added to string

        //Continue until 10 words found, no more matches, or end of list
        while(words < 10 && words < total && temp != NULL)
        {
            if(words == 0)//First suggested word is printed in red
            {
              cout << termcolor::red;
            }
            cout << temp->Data->getWord() + "  ";  //Print word to screen
            cout << termcolor::reset;              //Print in normal color
            temp = temp->next;                     //Move on to next word
            words++;                               //Increment words to suggest
        }

    }
};



int main() 
{
    List WordDefs;                      //Create linked list
    Timer T;                            //Create timer
    double sec;                         //Number of seconds of timer
    long millsec;                       //Number of milliseconds of timer
    trio::IO io;                        //Create instance of IO 
    char letter;                        //Letter to look at from input
    string word = "";                   //Total word being typed by user
    int total;                          //total matches found in list
    int wordSize = 0;                   //Size of typed word

    WordDefs.Fill("dictionary.txt");    //Fill list w/ dictionary wordSize
    
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