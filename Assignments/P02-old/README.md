## P02 - Processing in Linear Time
### Allyson Warren
### Description:

This program takes words and definition from a json file and places 
the word and definition separately into a linked list. The list will 
be sorted due to the JsonFacade class. After the list is sorted in O(n) 
time, the program will then prompt the user to type in a letter and show 
how many words were found that matched with the letter typed. AFter each 
letter is typed, the computer will then continue to display how many similar 
words appear in the list and will also give ten suggested words from the 
list that it believes to be the word that is being typed by the user. The 
program also displays how long it takes to find all similar words and will 
display the time as well to the screen. As each letter is typed to the screen 
from the user the search will become faster as the program continues to look 
for similar words based on the last search it did. 

### Files:

|   #   | File                                                                                         | Description                     |
| :---: | -------------------------------------------------------------------------------------------- | ------------------------------- |
|   1   | [main.cpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/main.cpp) | Main driver of Stack program. |
|   2   | [dict_w_defs.json](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/dict_w_defs.json) | File containing all words and definitions. |
|   3   | [json.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/json.hpp) | Header file to manage the json file |
|   4   | [JsonFacade.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/JsonFacade.hpp) | Header file to condense json.hpp for easier use.|
|   5   | [mygetch.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/mygetch.hpp) | File to allow for getching user input without needing for any carriage returns |
|   6   | [Timer.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/Timer.hpp) | Header file for handling the timer for seeing how long program takes in searching |
|   7   | [trio.hpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P02/trio.hpp) | Header file for formatting and manipulating screen output. |





### Instructions
    - None for now
    
### Example Command
    - None for now
