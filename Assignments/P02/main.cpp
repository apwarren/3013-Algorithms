#include <iostream>
#include <string>
#include "JsonFacade.hpp"       // need to grab a copy from resources folder
#include "mygetch.hpp"
#include "trio.hpp"
#include <time.h>
#include <chrono> 
#include "Timer.hpp"            // need to grab a copy from resources folder
using namespace std;

class wordNode
{
  private:
  string Word;
  string Definition;
  public:
  wordNode()
  {
    Word = "";
    Definition = "";
  }
  wordNode(string w, string def)
  {
    Word = w;
    Definition = def;
  }
  string getWord()
  {
    return Word;
  }
  char getWordLetter(int index)
  {
    return Word[index];
  }
};

 struct Node
  {
    wordNode* Data;
    Node *next;
  };	

class List
{
  private:
  wordNode* Data;
  Node* Head;
  Node* Tail;
  Node* Current;
  int size;
  int total;
  int index;
  string key;// key variable to access json object
  string value;
  vector<string> keys;
  bool Found;

  public:
  List()
  {
    Head = NULL;
    Current = NULL;
    Tail = NULL;
    size = 0;
  }
  void Insert(string Word, string Def)
  {
    Node* temp = new Node;
    temp->Data = new wordNode(Word, Def);
    temp->next = NULL;
    if (Head == NULL)  
    {  
        Head = temp;
        Current = Head;
        Tail = temp;  
        return;  
    } 
    else  
    {
        Tail->next = temp;
        Tail = temp;
    } 
    return;
  } 

  void Fill(JsonFacade J)
  {
    keys = J.getKeys();
    size = keys.size();
    //Fill in linked list
    for(int index = 0; index < size; index++)
    {
      key = J.getKey(index);
      value = J.getValue(key);
      Insert(key, value);
    }
  }
  int Find(char letter)
  {
    Node* temp = Current;
    Found = false;
    total = 0;
    static int LetterIndex = 0;
    while(temp != NULL && !Found)
    {
      if(temp->Data->getWordLetter(LetterIndex) == letter)
      {
        if(total == 0)
        {
          Current = temp;
        }
        total++;
      }
      else
      {
        if(total != 0)
        {
          Found = true;
        }
      }
      temp = temp->next;
    }
    LetterIndex++;
    return total;
  }
  string Suggestions(int total)
  {
    string suggests = "";
    Node* temp = Current;
    int words = 0;
    while(words < 10 && words < total && temp != NULL)
    {
      suggests += temp->Data->getWord() + " ";
      temp = temp->next;
      words++;
    }
    return suggests;
  }
};



int main() {
    List WordDefs;
    JsonFacade J("dict_w_defs.json");   // create instance of json class
    Timer T;
    double sec;
    long millsec;
    //Place Words and Definitions into singly linked list
    WordDefs.Fill(J);

    trio::IO io;
    char letter;
    string word = "";
    int index = 0;
    int total;
    while ((int)(letter = getch()) != 10) 
    {
        trio :: clear_screen();
        trio :: Point front(2,0); 
        word += letter;
        io<< front << word << '\n';
        T.Start();
        total = WordDefs.Find(letter);
        cout << total << " words found in ";
        T.End();
        sec = T.Seconds();
        millsec = T.MilliSeconds();
        
        cout << sec <<millsec << "seconds" << endl;
        cout << WordDefs.Suggestions(total);        
        index++;
    }
}