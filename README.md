# CommandLineTextEditor
Command line text editor for Data Structures & Algorithms class done in C++

Designed by Ervin Pangilinan

Spring 2022 Semester (v1.0) February 11, 2022

Course: Data Structures & Algorithms Analysis

Objective:
The goal of this project is to create a line editor, similar to
programs such as vim by implementing a doubly-linked list. The user
will launch the program on the command line and will provide an
additional command line argument to specify the file to edit.
After launching the editor for the file, the user will be able
to manipulate each line of the program via specific commands.

Command Line Syntax:
./a.out [filename]

Note: The file that the user wants to edit must be in the same
      directory as the program.

Sample Input:
The input file will contain any amount of strings in a file such
as the example below:

      This is the first line!
      This is the second line!
      This is the third line!
    
Sample Output: 
When the editor is launched, the user will see the file brpoken down into
individual lines such as shown below:

      1> This is the first line!
      2> This is the second line!
      3> This is the third line!
      3>

The output will still be on the command line. Also included in the file
that the user does not see are 2 buffer regions at the very top and bottom
of the file. When the user exits the editor, the output file will overwrite 
the input file to update changes.

OOP Design:
The following classes/libraries are included in the program:
  - iostream
  - fstream
  - cstdlib
  - string

A LineList class is implemented to model a doubly-linked list for the editor.
The LineList ADT is described below:
  - PRIVATE ATTRIBUTES:
    -  An external pointer for traversing the list
    -  An integer variable specifiying the current line number
    -  An integer variable specifying the length of the list.

  - PUBLIC ATTRIBUTES: 
    -  A struct is defined for the individual nodes of the list.
    -  Functions for going to the top or bottom of the list.
    -  Functions for inserting to and deleting from the list.
    -  Functions for traversing the list by either moving to the
          next or previous line.
    -  A function for printing the entire list. 
    -  Observer functions to return the string at a particular line,
          returning the length of the list, and value of the current line
          number.

Client Program Outline:
The client program can be broken down into 4 steps:
      - File Checking
      - Building the List
      - Executing Commands
      - Saving Changes
      
File Checking Phase:
In this phase, the program will use the file name specified on the 
command line to open a file. If no file name is listed as a command
line argument or if an invalid file name is passed as an argument,
then the program will exit. 

Building the List:
In this phase, the list will be built by reading each line from the file.
The information from each line will be inserted as a node into the list,
and will continue to do so until the the end-of-file has been reached.

Executing Commands:
The client program uses the following uppercase characters to represent
different commands to be executed:

  - D (Delete the current line.) 
  - I (Insert a new line after the current line.)
  - N (Move to the next line.)
  - P (Move to the previous line.)
  - L (Print the entire file, list by list.)
  - E (Save changes to the file and exit the program.)

All of these different commands make use of the external pointer provided
by the LineList ADT. The functions for these commands also make use of a
dynamically-created, temporary pointer to compensate for the LineList ADT
having one external pointer to use. Also included in these functions are
safeguards to prevent accessing any region past the buffers at the top and
bottom of the file.

Saving Changes:
Saving changes to the file is done as a traversal through the list starting
at the top line. For each node in the list, the contents of that node are
written to a line in the output file. This is done until the last node of the
LineList has been accessed and its contents have been copied over to the output
file. The output file will then be saved as the same name as the input file
to overwrite the file and lock in changes.

