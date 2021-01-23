/**************************************************************************
*
* Author:      Allyson Warren
* Email:       allywarren7@gmail.com
* Label:       A03
* Title:       Commenting Code
* Course:      CMPS 3013
* Semester:    Spring 2021
*
* Description:
*     This program implements a data structure using a linked list. 
*     While being used to print out integers starting from the first 
*     value, the list is also implemented to where it can be used like 
*     an array by overloading the [] operator to traverse through
*     the list. Values can be added to both the front and end
*     of the list through Insert and Push.
*     
* Usage:
*     None
* Files:
*     main.cpp     :   driver program
**************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int A[100];             
/**
* Struct
*
* Description:
*     This struct implements a node. It holds an integer for data
*     and a pointer to connect to the previous node in the list.
* 
* Public Methods:
*                   Node()
*                   Node(val)
*
* Usage:
*     Node *Head;                    //Create Instance of Node
*
*     Node *Temp = new Node(val);    //Create Instance of Node that holds 
*                                    //a specific value
*
*     Node();                        //Node constructor
*                                    //-defaults data value to -1
*
*/
struct Node             
{
    int x;                           //Data value to be stored in the node       
    Node* next;                      //Pointer to point to the next node
    Node()                           //Default Constructor 
    {                                   
        x = -1;                      //Defaults data in node to -1
        next = NULL;                 //Currently last node in list so points to NULL
    }
    Node(int n)                      //Constructor to hold a specific value
    {
        x = n;                       //Sets data to hold a specific value
        next = NULL;
    }
};
/**
* List
*
* Description:
*     This class implements a data structure called a Queue using a 
*     linked list where the last integer added to the list will be the last 
*     to be printed. This class can add, insert, and print the list
*     as well as the last integer in the list. It can also be used
*     like an array by holding its size. The size decrements and
*     increments as nodes in the list are deleted or added.
*
* Public Methods:
*                   List()
*     void          Push(int val)
*     void          Insert(int val)
*     void          PrintTail()
*     string        Print()
*     int           Pop()
*     List          operator+(const List& Rhs)
*     int           operator[](int index)
*     friend        ostream& operator<<(ostream& os, List L)
*
* Private Methods:
*     No private methods
*
* Usage:
*     List L;            //Create instance of List
*     L.Push(val);       //Add an integer to the end of the list
*                        //or
*     L.Insert(val);     //insert an integer to the beginning of the list

*     L.PrintTail();     //Print out the very last integer in the list
*     L.Print();         //Prints out the entire list
*     L.Pop();           //Returns the first integer in list and deletes it 
*                        //from the list
*     L = L1 + L2;       //Combines two List classes together into one List
*     L[index];          //gets a specific value from the list using array notation
*     cout << L;         //Prints from the list using the insertion operator
*     
*/
class List
{
private:
    Node* Head;          //Pointer to beginning of List
    Node* Tail;          //Pointer to end of List
    int Size;            //Size of List

public:
    List()                          //Defaults an empty List
    {
        Head = Tail = NULL;             
        Size = 0;
    }
/**
* Public : Push
*
* Description:
*     Adds an integer to the end of the linked list.
*
* Params:
*     int     :   value to be added
*
* Returns:
*     No return type
*/
    void Push(int val)
    {
        
        Node* Temp = new Node(val);     //Allocate new memory and initialize node

        if (!Head && !Tail)             //List is empty
        {
            Head = Tail = Temp;         //Set Head and Tail to the new node
        }
        else                            //List is not empty
        {
            Tail->next = Temp;          //Previous node points to new node
            Tail = Temp;                //Tail points to new node at end of List
        }
        Size++;                         //Increment list size 
    }
/**
* Public : Insert
*
* Description:
*     Inserts an integer to the beginning of the linked list.
*
* Params:
*     int     :   value to be added at the beginning
*
* Returns:
*     No return type
*/
    void Insert(int val)
    {
        
        Node* Temp = new Node(val);     //Allocate new memory and initialize node

        Temp->next = Head;              //Point new node to initial head of the list
        Head = Temp;                    //Set new node to be head of the list
        if (!Tail)                      //Tail points to NULL -List is empty
        {
            Tail = Head;                //Tail points to new head node
        }
        Size++;                         //Increment list size
    }
/**
* Public : PrintTail
*
* Description:
*     Prints out the last integer in the list.
*
* Params:
*     No parameters
*
* Returns:
*     No return type
*/
    void PrintTail()
    {
        cout << Tail->x << endl;    //Print value stored in the last node in list
    }
/**
* Public : Print
*
* Description:
*     Puts all the integers from the list into a string to be 
*     formatted and printed out.
*
* Params:
*     No parameters
*
* Returns:
*     string      :  a string of all the list's integers separated.
*/
    string Print()
    {
        Node* Temp = Head;          //Get Address to the beginning of the list
        string list;                //Holds all values from the list

        while (Temp != NULL)        //Not at the end of the list
        {
                                    //Add values from list and separate with arrow 
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;      //Go to next value in list
        }

        return list;                //return string with list's values
    }
/**
* Public : Pop
*
* Description:
*     Grabs the first integer in the list and then removes it from the list.
*
* Params:
*     No parameters
*
* Returns:
*     int     :   the first integer in the linked list
*/
    
    int Pop()             //Not implemented 
    {
        Size--;           //Decrements list size
        return 0; 
    }
/**
* Public : operator+
*
* Description:
*     Uses the + operator to be able to combine two separate
*     lists together.
*
* Params:
*     const List&   :   the address of the second list to be added
*
* Returns:
*     List          :  A new list of the two lists combined
*/
    List operator+(const List& Rhs)
    {
        
        List NewList;            //Create a new list that contains both when done

        Node* Temp = Head;       //Get a reference to beginning of local list

        while (Temp != NULL)     //traverse local list and Push values onto new list
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;   //Go to next node in list
        }
                               
        Temp = Rhs.Head;         //Get a reference to head of Rhs

        while (Temp != NULL)     //Same as above, loop and push
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        
        return NewList;            //Return new concatenated version of lists
    }
/**
* Public : operator[]
*
* Description:
*     Returns a desired int value using array notation.
*
* Params:
*     int     :   how far to traverse through the list
*
* Returns:
*     int     :   returns the value located at the desired node
*/
    
             //Implementation of [] operator.
             //Returns an int value as if the list were an array.
    int operator[](int index)  
    {                          
        Node* Temp = Head;

              //Index is out of bounds
        if (index >= Size)     
        {
              //Display error message
            cout << "Index out of bounds, exiting";
              //Terminate program
            exit(0);           
        }
        else
        {     //Traverse through the list to the desired node
            for (int i = 0; i < index; i++)
            {   
                Temp = Temp->next;
            }
              //Return value stored at desired node
            return Temp->x;
        }
    }
/**
* Public : operator<<
*
* Description:
*     Prints out the list to the screen by implementing the Print() function.
*
* Params:
*     ostream&    :   handles the output stream   
*     List        :   list to be printed out
*
* Returns:
*     ostream&      :   returns list and outputs it to screen
*/
    friend ostream& operator<<(ostream& os, List L)
    {
        os << L.Print();    //Calls Print function to get formatted string of values 
        return os;          //Assign << operator to print the list to the screen
    }
};

int main(int argc, char** argv)
{
    List L1;                //First List object
    List L2;                //Second List object

    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);         //Add numbers 0-24 to list
    }

    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);         //Add numbers 50-99 to list
    }

    //cout << L1 << endl;
    L1.PrintTail();       //Prints last value of first list
    L2.PrintTail();       //Prints last value of second list

    List L3 = L1 + L2;    //Combine first and second lists together to a third list
    cout << L3 << endl;   //Prints out entire third list with specific formatting

    cout << L3[5] << endl;//Print out the fifth value from the third list
    return 0;
}
