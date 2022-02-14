
#include <iostream>
#include "linelist.h"

LineList::LineList() {
	LineNode *line = new LineNode;
	LineNode *line2 = new LineNode;

	// currLine is the only master pointer for the implemented doubly-linked list.
	line -> info = topMessage;
	currLine = line;
	currLineNum = 1;
	length = 0;
	line2 -> info = bottomMessage;
	currLine -> back = NULL;
	currLine -> next = line2;
	line2 -> back = line;
	line2 -> next = NULL;
}

void LineList::goToTop() {
	// POST: Advances currLine to line 1
	while (currLineNum != 1) {
		// Keep moving up until currLine points to the node after *line
		currLine = currLine -> back;
		currLineNum--;
	}
}

void LineList::goToBottom() {
	// POST: Advances currLine to last line.
	while (currLine -> next -> info != bottomMessage) {
		// Keep moving down until currLine points to the node before *line2
		currLine = currLine -> next;
		currLineNum++;
	}
}

void LineList::insertLine(string newLine) {
	// PRE: A string containing what the user typed is passed as an argument.
	// POST: newLine has been inserted after the current line. 

	// Prevents insertions after the bottom buffer. 
	if (currLineNum > getLength() + 1) {
		currLine = currLine -> back;
		currLineNum--;
		return;
	}

	LineNode *temp = new LineNode;
	temp -> info = newLine;
	// Next 2 lines position the new line to be after currLine and before currLine's next node.
	temp -> back = currLine;
	temp -> next = currLine -> next;
	// Redirect the other nodes so that they connect to the new node.
	currLine -> next = temp; // currLine connects to the new node's next node.
	temp -> next -> back = temp; // currLine's former next node connects to the new node from the back.
	currLine = currLine -> next; // The new node becomes currLine.
	// Increment both the length of the linked list and currLineNum.
	length++;
	currLineNum++;
}

void LineList::deleteLine() {
	// PRE: currLine should not be pointing to either buffer. 
	// POST: Deletes the current line leaving currLine pointing to line following.

	// Makes sure that currLine will never point to buffers before deleting. 
	if (getCurrLineNum() - 1 == 0) return;
	if (getLength() == 0) return;

	LineNode *temp = new LineNode;
	temp = currLine;
	// Redirect nodes to have currLine's previous node connect to currLine's next node. 
	currLine = currLine -> next; // currLine no longer points to same node as temp
	currLine -> back = temp -> back;
	temp -> back -> next = currLine;
	delete temp; // Deallocate the node that temp points to.
	temp = NULL;
	length--; // Decrement length to keep track of amount of lines in the file. 

	// Readjust currLine and currLineNum to correct position
	if (currLineNum > getLength() + 1) {
		currLine = currLine -> back;
		currLineNum--;
	}
}

void LineList::printList() {
	// PRE: LineList has already been initialized.
	// POST: Prints every line from the file.
	LineNode *hold = currLine; // Keep track of the original node. 
	int position = getCurrLineNum(); // Keep track of the original index in list. 

	goToTop();
	LineNode *temp = currLine; // For traversal, starting at the top of list. 

	// Move temp pointer away from top buffer. 
	temp = temp -> next; 

	// Move temp pointer towards the bottom buffer
	while (temp -> info != bottomMessage) {
		cout << getCurrLineNum() << "> " << temp -> info << endl;
		currLineNum++;
		temp = temp -> next;
	}

	// Reset currLineNum and currLine to original position. 
	currLine = hold;
	currLineNum = position;
}

string LineList::getCurrLine() const {
	// POST: Returns the string at the current line
	return currLine -> info;
}

void LineList::moveNextLine() {
	// POST: Advances currLine (unless already at last line)
	if (currLine -> next -> info != bottomMessage) {
		currLine = currLine -> next;
		currLineNum++;
	} 
}

void LineList::movePrevLine() {
	// POST: Moves back currLine (unless already at first line)
	if (currLine -> info != topMessage) {
		currLine = currLine -> back;
		currLineNum--;
	}
}

int LineList::getCurrLineNum() const {
	// POST: Returns the current value of currLineNum
	return currLineNum;
}

int LineList::getLength() const {
	// POST: Returns the length of the linked list.
	return length;
}

