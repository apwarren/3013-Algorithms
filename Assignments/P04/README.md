## P04 - Processing in Trie Time
### Allyson Warren
### Description:

This program takes words from a text file and places
the word into a Trie Tree data structure. This tree allows for words
to be found from a list in O(MxNxC) time where N is the total number
of strings, M is the longest string length, and C is the alphabet size.
The program will then prompt the user to type in a letter and show how
many words were found that matched with the letter typed. AFter each 
letter is typed, the computer will then continue to display how many 
similar words appear in the Trie and will also give ten suggested words 
from the Trie that it believes to be the word that is being typed by the 
user. The program also displays how long it takes to find all similar words
and will also display this time to the screen. The typed word will appear 
in red on the screen as well as the time and first suggested word in the list.


<[Link to Program on Replit](https://replit.com/@apwarren/ProcessTrieTime#main.cpp)>

### Files:

|   #   | File                                                                                         | Description                     |
| :---: | -------------------------------------------------------------------------------------------- | ------------------------------- |
|   1   | [main.cpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/main.cpp) | Main driver of Trie Tree program. |
|   2   | [dictionary.txt](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/dictionary.txt) | File containing all words. |
|   3   | [mygetch.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/mygetch.hpp) | File to allow for getching user input without needing for any carriage returns |
|   4   | [timer.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/timer.hpp) | Header file for handling the timer for seeing how long program takes in searching |
|   5   | [trio.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/trio.hpp) | Header file for formatting and manipulating screen output. |
|   6   | [termcolor.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P04/termcolor.hpp) | Header file for manipulating color in command prompt. |


### Instructions
    - None for now
    
### Example Command
    - None for now
