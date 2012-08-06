//============================================================================
// Name        : ttbf-cgcc.cpp
// Author      : Jesse Litton
// Version     :
// Copyright   : GPL v3
// Description : Text To brainfuck - converts text to a not
//             :    very optimized brainfuck program.
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

	// Open input file
	ifstream stream(argv[1]);

	// Build initial quick table:
	//	This table will be used to find the 'closest' pointer
	//	to a particular character.

	// Common values
	// 010 (LF), 032 (space), 048 (zero), 065 (A), 074 (J)
	// 083 (S), 097 (a), 106 (j), 115 (s)
	// Table is:  10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120

	// The Original Array... which is static
	unsigned int o_array[11] = {10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
	// This bf initialization table/code matches the above array
	string bf_table = "++++++++++[>+>+++>++++>+++++>++++++>+++++++>++++++++>+++++++++>++++++++++>+++++++++++>++++++++++++<<<<<<<<<<<-]>";
	cout << bf_table;

	// Our Working Array...  which will change.
	unsigned int w_array[11] = {10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
	unsigned int array_pos = 0;

    while(!stream.eof()) {
    	string text;
		getline(stream, text);
    	text = text + '\n';
    	unsigned int length = text.length();

		// Process each letter
		for(unsigned int x=0; x<length; x++) {

			// Check letter against array to find closest match
			unsigned int closest_item = 10;
			unsigned int closest_value = 255;
			for(unsigned int y=0; y<(sizeof(o_array)/sizeof(o_array[0])); y++) {
				// find closest match for letter
				unsigned int diff = text[x] - o_array[y];
				if(diff < closest_value) {
					closest_value = o_array[y];
					closest_item = y;
				}
			}

			// Output bf code to move position to closest match
			while(array_pos < closest_item) {
					cout << ">";
					array_pos++;
			}
			while(array_pos > closest_item) {
					cout << "<";
					array_pos--;
			}

			if((unsigned int)text[x] > w_array[array_pos]) {
				unsigned int base_diff = (unsigned int)text[x] - w_array[array_pos];
				// Output code to increment closest working item to match
				for(unsigned int count=0; count< base_diff; count++) {
					cout << "+";
					w_array[array_pos]++;
				}
			} else if((unsigned int)text[x] < w_array[array_pos]) {
				unsigned int base_diff = w_array[array_pos] - (unsigned int)text[x];
				// Output code to decrement closest working item to match
				for(unsigned int count=0; count<base_diff; count++) {
					cout << "-";
					w_array[array_pos]--;
				}
			}

			// Print it!
			cout << '.';
		}
    }

	cout << endl;
	return 0;

}
