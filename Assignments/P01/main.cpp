/*********************************************************************************
*
* Author:           Allyson Warren
* Email:            allywarren7@gmail.com
* Label:            P01
* Title:            Resizing the Stack
* Course:           3013
* Semester:         Spring 2021
*
* Description:
*       This program takes an array-based stack and is given values to be
*       pushed and popped taken from an input file. An odd number means to remove
*       a number currently in the stack and any even numbers are to be pushed
*       and added to the stack. The stack adjusts and ensures that its size can
*       hold at least ten integers at all times and then grows and shrinks the array
*       based on either the default parameters implemented or any given parameters
*       stated in the command line. The default paramters ensure that if the
*       stack is completely full then it will double its size and if the stack
*       only has 15% of its full capacity, then it will downsize and shrink
*       the stack to half its previous size unless the size becomes less than ten 
*       which will then set the size to be ten. If the program is given parameters
*       then the first parameter represents when the stack has become too full,
*       the second is when it is too empty, the third represents how much to grow
*       a full stack by, and the last parameter is how much to shrink an empty stack 
*       by. The program can accept 0-4 parameters from the command line following 
*       their specific order.
*
* Usage:
*       None for now
*
* Files:
*       main.cpp         :  driver program
*       numbers_test.dat : input file containing values to be pushed or popped
*
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

/**
 * Stack
 *
 * Description:
 *      Integer array based stack implementation. Adjusts based on
 *      a specific parameters can be given or are default. The stack keeps control
 *      of when to grow and shrink based on these parameters and how much to
 *      resize the stack when needed. The stack also keeps track of how many times
 *      it has been resized, what its current size is, and what its largest
 *      array size was overall. The stack will automatically adjust based on its
 *      paramters without any assistance or input outside of the class.
 *
 * Public Methods:
 *      - Stack(double = , double =, double =, double = ,)
 *      - void Push()
 *      - int Pop()
 *      - int Peek()
 *      - int getMaxSize()
 *      - int getFinalSize()
 *      - int getResizeCount()
 *      - void Print()
 *
 * Private Methods:
 *      - bool Empty()
 *      - void CheckResize()
 *      - void ContainerGrow()
 *      - void ContainerShrink()
 *
 * Usage:
 *
 *  Stack S;
 *  Stack T(.75, .15, 1.5, .25);
 *  S.Push(80);
 *  S.Push(90);
 *  S.Pop();
 *  S.Peek();
 *  S.getMaxSize();
 *  S.getFinalSize();
 *  S.getResizeCount();
 *  S.Print();
 *  !Empty();
 *  CheckResize();
 *  ContainerGrow();
 *  ContainerShrink();
 *
 */
class Stack
{
private:
    int* S;                 //Array pointer
    const int MinSize = 10; //Stack must hold at least 10 items
    int StackSize;          //Current max stack size
    int ItemSize;           //Current num items
    int LargestSize;        //Maximum size of array overall
    int ResizeCount;        //How many times stack has grown or shrunk
    int StackTop;           //Current top of stack (index)
    double TooFull;         //Percentage of when stack is too full
    double TooEmpty;        //Percentage of when stack is too empty 
    double GrowSize;        //How much to grow stack by
    double ShrinkSize;      //How much to shrink stack by

public:
    /**
    * Stack:
    *    Default Constructor. Defaults parameters unless given new parameters
    * Params:
    *    Default parameters: 4 int
    *      - full is defaulted to 100% unless given
    *      - empty is defaulted to 15% unless given
    *      - grow is defaulted to 2 unless given
    *      - shrink is defaulted to 1/2 unless given
    *
    * Returns:
    *     Void
    */
    Stack(double full = 1, double empty = .15, double grow = 2, double shrink = .5)
    {
        S = new int[MinSize];   //Allocate new memory with size 10
        StackSize = MinSize;    //Stack size is initially 10
        ItemSize = 0;           //Stack is empty
        LargestSize = MinSize;  //Starting array is largest size initially
        ResizeCount = 0;        //Stack has not been shrunk or grown
        StackTop = -1;          //Stack is empty when created
        TooFull = full;         //What percentage of stack is too full
        TooEmpty = empty;       //What percentage of stack is too empty
        GrowSize = grow;        //How much to grow the stack by
        ShrinkSize = shrink;    //How much to shrink stack by

    }

    /**
    * Public: Push
    *    Push and add an item onto the stack. The method checks to
    *    see if the stack can hold the value and will adjust automatically
    *    and resize the array to be able to hold the new value.
    * Params:
    *    int : data
    *
    * Returns:
    *     Void
    */
    void Push(int data)
    {
        CheckSize();        //Check and adjust stack size if needed
        StackTop++;         //Move top of stack up
        ItemSize++;         //Increment size of integers in stack
        S[StackTop] = data; //Add item to array

    }

    /**
    * Public : Pop
    *    Removes item from stack back of array/ top of stack.

   *    Then calls the CheckSize method to see if stack needs to be
    *    resized if the stack becomes too empty.
    * Params:
    *    void
    *
    * Returns:
    *     int : removed value
    */
    int Pop()
    {
        if (Empty())             //Checks for empty stack
        {                        //Cannot pop anything
            return -1;           //Returns -1 and moves on
        }
        //If stack is not empty

        int data = S[StackTop];  //Pull item from stack and store it
        StackTop--;              //Shrink the stack
        ItemSize--;              //Update new item size

        CheckSize();             //Check if stack needs to be resized

        return data;             //Send item back
    }

    /**
      * Public: Peek
      *
      * Description:
      *      Returns top value without altering the stack
      *
      * Params:
      *      NULL
      *
      * Returns:
      *      [int] top value of stack if any
      */
    int Peek() {
        if (!Empty()) {
            return S[StackTop];
        }

        return -1;  // some sentinel value
                    // not a good solution
    }
    /**
      * Public: getLargestSize
      *    Returns the largest size the array grew to overall
      * Params:
      *    void
      *
      * Returns:
      *     int  :   Largest size of array
      */
    int getLargestSize()
    {
        return LargestSize;     //Return biggest size array grew to
    }

    /**
    * Public : getFinalSize
    *    Returns the final size of array after all values have been pushed or popped
    * Params:
    *    void
    *
    * Returns:
    *     int  :   Final size of array
    */
    int getFinalSize()
    {
        return StackSize;     //Return final size of array
    }

    /**
    * Public : getResizeCount
    *    Returns how many times the array was altered through growing or shrinking
    * Params:
    *    void
    *
    * Returns:
    *     int  :   number of times stack was resized
    */
    int getResizeCount()
    {
        return ResizeCount;     //Return how many times stack was resized
    }

    /**
    * Public : Print
    *    Method to print out all values in stack. Mainly for testing purposes
    *    The first value pushed will be the last value to be printed.
    * Params:
    *    void
    *
    * Returns:
    *     void
    */
    void Print()
    {
        for (int i = StackTop; i >= 0; i--)
        {   // Prints last data value to the first
            cout << S[i] << endl;
        }
    }

    /**
    * Private : Empty
    *    Checks for empty stack. Stack has no items inside itself.
    * Params:
    *    void
    *
    * Returns:
    *     bool : true == stack is empty
    */
    bool Empty()
    {
        return ItemSize == 0;
    }

    /**
    * Private : CheckSize
    *   Checks to see if the stack is either too full or empty
    *   based on the given parameters TooFull and TooEmpty. The two
    *   parameters are decimal values representing the max and min percentage
    *   that the stack can contain before needing to be resized. This Method
    *   will take the ratio of dividing the ItemSize by the StackSize to determine
    *   what percentage of space the pushed values take up in the stack currently.
    *   It will then either call ContainerGrow or ContainerShrink to adjust the
    *   stack if necessary. The stack will always have at least a size of 10.
    *
    * Params:
    *    void
    *
    * Returns:
    *     None
    */
    void CheckSize()
    {
        double Ratio = (double)ItemSize / StackSize; //Percent of taken stack space
        if (Ratio >= TooFull)                        //Stack has too many values
            ContainerGrow();                         //Resize and grow stack

        else if (Ratio <= TooEmpty)                  //Stack has too few values
            ContainerShrink();                       //Resize and shrink stack
    }

    /**
    * Private : ContainerGrow
    *   This method is called if the stack is considered too full
    *   and needs to be grown and resized to accommodate for more input.
    *   It will create a new array with a new size being the current sizes
    *   multiplied by a given GrowSize. The values in the old array are then
    *   transferred to the new array and the old array is deleted. Because the
    *   array is grown to a proportion, if the newSize has any decimal values,
    *   then its size is pushed up rather than truncated because the stack
    *   is to be increased and wants the most space possible for new data.
    *   For example, if the new size is 12.5 then the new stack size is 13 as
    *   we want as much space as possible when the array gets too full.
    *   If the new size of the array is the greatest size it has been
    *   overall, then its size is recorded as the current LargestSize as
    *   well. The ResizeCount will also increment as we are manipulating the
    *   stack's size.
    *
    * Params:
    *    void
    *
    * Returns:
    *     None
    */
    void ContainerGrow()
    {
                                            //New stack size-Decimal round up
        int newSize = int(ceil(StackSize * GrowSize));

        int* newStack = new int[newSize];   //New stack with increased size

        for (int x = 0; x < ItemSize; x++)
        {
            newStack[x] = S[x];             //Fill new stack with current values
        }

        delete[] S;                         //Delete previous stack
        S = newStack;                       //Point to new stack
        StackSize = newSize;                //Change stack size to new size 

        if (LargestSize < StackSize)        //New size is larger than previous size  
            LargestSize = StackSize;        //Store new largest size

        ResizeCount++;                      //Stack has been resized

    }

    /**
    * Private : ContainerShrink
    *   This method is called if the stack is considered too empty for its
    *   current size and needs to be shrunk to not take up so much space.
    *   It will create a new array with a new size being the current size
    *   multiplied by a given ShrinkSize. The values in the old array are then
    *   transferred to the new array and the old array is deleted. Because the
    *   array is shrunk to a proportion, if the newSize contains any decimal values,
    *   then its size will be truncated because the stack is to be downsized
    *   and wants the to take up the least space possible. If the new size is less
    *   than 10 then its new size will default to 10 as that is the minimum size
    *   the stack can be. The ResizeCount will also increment as we are manipulating
    *   the stack's size.
    *
    * Params:
    *    void
    *
    * Returns:
    *     None
    */
    void ContainerShrink()
    {
                                          //Get new stack size-Decimal is dropped
        int newSize = int(StackSize * ShrinkSize);
        if (newSize <= 10)                //Stack must be at least size 10
        {
            if (StackSize == 10)          //Stack is already min size, don't resize
                return;
            else
                newSize = 10;
        }

        int* newStack = new int[newSize]; //New stack with shrunken size

        for (int x = 0; x < ItemSize; x++)
        {
            newStack[x] = S[x];           //Fill new stack with current values
        }

        delete[] S;                       //Delete previous stack
        S = newStack;                     //Point to new stack
        StackSize = newSize;              //Change stack size to new size 

        ResizeCount++;                    //Stack has been resized
    }
};

/**
* Header:
*    Returns a string containing program #, class, and name
* Params:
*    void
*
* Returns:
*     string : Header for both output file and screen
*/
string Header()     //Returns student information
{
    //Prints out program #, class, and name on separate lines
    return "Assignment 4 - Resizing the Stack\nCMPS 3013\nAllyson Warren\n\n";
}

int main(int argc, char** argv)
{

    Stack* S;                       //Create a stack pointer
    switch (argc)                   //Check for command line parameters
    {                               //Create Stack
    case 1:                         //No given parameters
        S = new Stack();            //Create Default Stack Object
        break;

    case 2:                         //Declare when stack is too full only
        S = new Stack(atof(argv[1]));
        break;

    case 3:                         //Declare when stack is full and empty
        S = new Stack(atof(argv[1]), atof(argv[2]));
        break;

    case 4:                         //Declare Fullness, Emptiness, and Growth
        S = new Stack(atof(argv[1]), atof(argv[2]), atof(argv[3]));
        break;

    default:                        //Declare all parameters
        S = new Stack(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]));
    }

    ifstream infile;                //Read from input  file
    infile.open("nums_test.dat");
    ofstream outfile;               //Make and open  output file
    outfile.open("nums_test_output.txt");

    int data;                       //Value to either push or pop
    while (infile >> data)          //Read all data items in file
    {
        if (data & 1)               //Int is odd, call pop function
        {
            S->Pop();               //Remove last int added to stack
        }
        else                        //Int is even, add to stack
        {
            S->Push(data);          //Add number to stack        
        }
    }

    //Print to output file
    outfile << 
    "######################################################################\n";
    // Prints student information to output file
    outfile << Header();
    //Print out largest and final size of the stack. 
    outfile << "Max Stack Size: " << S->getLargestSize() << endl;
    outfile << "End Stack Size: " << S->getFinalSize() << endl;
    //Print out how many times stack was resized
    outfile << "Stack Resized: " << S->getResizeCount() << endl;
    outfile << 
    "######################################################################\n";

    //Print to Student Information to screen
    cout << 
    "######################################################################\n";
    cout << Header(); 
    //Print out largest and final size of the stack. 
    cout << "Max Stack Size: " << S->getLargestSize() << endl;
    cout << "End Stack Size: " << S->getFinalSize() << endl;
    //Print out how many times stack was resized
    cout << "Stack Resized: " << S->getResizeCount() << endl;
    cout << 
    "######################################################################\n";

    infile.close();
    outfile.close();
    return 0;
}