
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "linelist.h"
using namespace std;

void fileCheck(int argc, ifstream &input, char *argv[]);
void initialize(LineList &list, ifstream &file);
void execute(LineList &list);
void saveChanges(LineList &list, ofstream &output, char *argv[], int argc);

int main(int argc, char *argv[]) {
	// PRE: On the command line, "./a.out" and the file name are passed as arguments to launch the editor.
	// POST: Editor is launched, with a linked list built using each line from the file.
	ifstream inFile;
	ofstream outFile;
	LineList editor;

	fileCheck(argc, inFile, argv);
	initialize(editor, inFile);
	execute(editor);
	saveChanges(editor, outFile, argv, argc);

	return 0;
}

void fileCheck(int argc, ifstream &input, char *argv[]) {
	// PRE: User must have inputted an argument specifying the file name.
	// POST: File will have been opened. 
	if (argc == 1) {
		// Execute when the user does not specify a file name.
		cout << "File name not present..." << endl;
		exit(1);
	} else {
		string filename = argv[argc - 1];
		input.open(filename.c_str());

		if (!input) {
			// Execute when user inputs an invalid file name. 
			cout << "File does not exist..." << endl;
			exit(1);
		}
	}
}

void initialize(LineList &list, ifstream &file) {
	// PRE: LineList object and file both exist and are in the same directory.
	// POST: Editor is set up with each node being a line from the input file.
	string temp;
 	while (!file.eof()) {
		// Keep inserting lines from the file until end of file has been reached. 
		getline(file, temp);
		list.insertLine(temp);
	}	
}

void execute(LineList &list) {
	// PRE: LineList must have already been initialized.
	// POST: User is able to interact in the editor and write to file.
	list.printList();
	bool active = true;

	while (active) {
		string input;
		string newLine;

		cout << list.getCurrLineNum() - 1 << "> ";
		getline(cin, input);
		if (input.length() == 1) {
			switch (*input.c_str()) {
				case 'I': // Insert line command
					cout << list.getCurrLineNum() << "> ";
					cin >> ws; // Flush out the input buffer before getting input
					getline(cin, newLine);
					list.insertLine(newLine);
					break;

				case 'D': // Delete line command
					list.deleteLine();
					break;

				case 'L': // Print all lines command
					list.printList();
					break;

				case 'P': // Move to previous line command
					list.movePrevLine();
					break;

				case 'N': // Move to next line command
					list.moveNextLine();
					break;

				case 'E': // Exit out of editor
					active = false;
					break;

				default: // Don't do anything for any other character. 
					break;	
			}
		}
	}
}

void saveChanges(LineList &list, ofstream &output, char *argv[], int argc) {
	// PRE: User inputted 'E' at the command line to finish editing.
	// POST: Changes done in the editor are applied to the file.
	string filename = argv[argc - 1];
	output.open(filename.c_str());
	
	list.goToTop(); // Start traversal at the top of the list. 
	list.moveNextLine();
	while (list.getCurrLineNum() <= list.getLength()) {
		output << list.getCurrLine() << endl; // Write current line into new file. 

		// Allow the final line in the list to be written into new file. 
		if (list.getCurrLineNum() == list.getLength()) {
			list.moveNextLine();
			output << list.getCurrLine() << endl;
		}
		list.moveNextLine(); // Go the next line after extracting info. 
	}
	output.close();
}

