## P01 - Resizing the Stack
### Allyson Warren
### Description:

This program takes an array-based stack and is given values to be pushed and popped 
taken from an input file. An odd number means to remove a number currently in the 
stack and any even numbers are to be pushed and added to the stack. The stack adjusts 
and ensures that its size can hold at least ten integers at all times and then grows 
and shrinks the array based on either the default parameters implemented or any given
parameters stated in the command line. The default parameters ensure that if the stack
is completely full then it will double its size and if the stack only has 15% of its
full capacity, then it will downsize and shrink the stack to half its previous size 
unless the size becomes less than ten which will then set the size to be ten. If the
program is given parameters then the first parameter represents when the stack has 
become too full, the second is when it is too empty, the third represents how much 
to grow a full stack by, and the last parameter is how much to shrink an empty stack 
by. The program can accept 0-4 parameters from the command line following their specific 
order.

### Files:

|   #   | File                                                                                         | Description                     |
| :---: | -------------------------------------------------------------------------------------------- | ------------------------------- |
|   1   | [main.cpp](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/main.cpp) | Main driver of Stack program. |
|   2   | [nums_test.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/nums_test.dat) | File 1 of all numbers to be read by program |
|   3   | [nums.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/nums.dat) | File 2 of all numbers to be read by program |
|   4   | [commands.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/commands.dat) | File 3 of all numbers to be read by program |
|   5   | [nums_test_output.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/nums_test_output.dat) | Output file for nums_test.dat. Shows max size, final size, and resize count of stack. |
|   6   | [nums_output.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/nums_output.dat) | Output file for nums.dat. Shows max size, final size, and resize count of stack. |
|   7   | [commands_output.dat](https://github.com/apwarren/3013-Algorithms-Warren/blob/master/Assignments/P01/commands_output.dat) | Output file for commands.dat. Shows max size, final size, and resize count of stack. |





### Instructions

- This program can accept 0-4 command line parameters if desired.
- The order of the parameters is:
    - When stack is considered too full percent-wise (.8)
    - When stack is too empty percent-wise (.1)
    - How much to grow stack by (1.25)
    - How much to shrink stack by (.3)


### Example Command

- g++ main.cpp o- main
- ./main .8 .1 1.25 .3
