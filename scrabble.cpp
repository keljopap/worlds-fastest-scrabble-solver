#include "Utility.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#define M 4
using namespace std;

int NUM_ROWS = 15;
int NUM_COLS = 15;
int RACK_SIZE = 7;
char scrabble_board[15][15];
int my_rack[27];

map<char, short> letter_values;
map<char, short> tile_bag;

/* Bonus Locations */

//Triple Word Scores:  1, 8, 15, 106, 120, 211, 225
//Double Word Scores:  17, 

void print_board() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
                cout << scrabble_board[i][j];
        }
        cout << endl;
    }
}

void init_letter_values() {
    letter_values = {{'a', 9}, {'b', 2}, {'c', 2}, {'d', 4}, {'e', 12}, {'f', 2}, {'g', 3}, {'h', 2}, {'i', 9}, 
                     {'j', 1}, {'k', 1}, {'l', 4}, {'m', 2}, {'n', 6}, {'o', 8}, {'p', 2}, {'q', 1}, {'r', 6}, 
                     {'s', 4}, {'t', 6}, {'u', 4}, {'v', 2}, {'w', 2}, {'x', 1}, {'y', 2}, {'z', 1}, {'?', 2}}; 
}

void init_tile_bag() {
    tile_bag = {{'a', 1}, {'b', 3}, {'c', 3}, {'d', 2}, {'e', 1}, {'f', 4}, {'g', 2}, {'h', 4}, {'i', 1}, 
                {'j', 8}, {'k', 5}, {'l', 1}, {'m', 3}, {'n', 1}, {'o', 1}, {'p', 3}, {'q', 10}, {'r', 1}, 
                {'s', 1}, {'t', 1}, {'u', 1}, {'v', 4}, {'w', 4}, {'x', 8}, {'y', 4}, {'z', 10}, {'?', 0}};
}

void set_rack(char rack[]) {
    for (int i = 0; i < RACK_SIZE; i++) {
        if (letter_values.count(rack[i])) {
            cout << "added to rack, value : " << rack[i] << endl;
        }
        else {
            cout << "could not add to rack, value : " << rack[i] << endl;
        }
    }
}

void add_word(int row, int col, string word, char orientation) {

	char test;

	try {
	    switch(orientation) {
	        case 'a':
	            if (col + word.length() < NUM_COLS && row < NUM_ROWS) {
	                for (int i = 0; i < word.length(); i++) {
	                	test = scrabble_board[row][col+i];
	                	if (test != word[i] &&
	                		test != '|' &&
	                		test != '_') {

	                		throw Error("You can't play on top of letter " +
	                			std::to_string(test) + " at (" + std::to_string(row) + ", " +
	                			std::to_string(col + i) + ")");
	                	}
	                }
	                for (int i = 0; i < word.length(); i++)
	                    scrabble_board[row][col+i] = word[i];
	            }
	            break;
	        case 'd':
	            if (row + word.length() < NUM_ROWS && col < NUM_COLS) {
	                for (int i = 0; i < word.length(); i++) {
	                	test = scrabble_board[row+i][col];
	                	if (test != word[i] &&
	                		test != '|' &&
	                		test != '_') {

	                		throw Error("You can't play on top of letter " +
	                			std::to_string(test) + " at (" + std::to_string(row+i) + ", " +
	                			std::to_string(col) + ")");
	                	}
	                }
	                for (int i = 0; i < word.length(); i++)
	                    scrabble_board[row+i][col] = word[i];
	            }
	            break;
	    }
	} catch (Error &e) {
		cout << e.what() << endl;
	}
}

// Helper functions for validating command input
static void read_int_persistently(int &x) {
   	
   	while (cin.good()) {
    	try {
   			if (!(cin >> x))
	        	throw Error("Expected an integer!");
    		break;
    	} catch (Error &e) {
    		cout << e.what() << endl;
            cin.clear();
            cin.ignore (numeric_limits<streamsize>::max(), '\n');
    	}
    }
}

void set_board() {

    int idx = 0;
    cout << "Constructing Scrabble board for:      (odd squares = '_', even squares = '|')" << endl;
    // This is where user can provide #across words followed by that #lines "{start pos} {word}",
    //                                #down words followed by that #lines "{start pos} {word}" (.txt file)

    string word;

    int across_words = 0;
    cout << "Enter words across:\n";
    read_int_persistently(across_words);
    cout << "# words across: " << across_words << endl;
    while (across_words-- > 0) {
        int row = NUM_ROWS, col = NUM_COLS;
        read_int_persistently(row);
        read_int_persistently(col);
        cin >> word;
        add_word(row, col, word, 'a');
    }

    int down_words = 0;
    cout << "Enter words down:\n";
    read_int_persistently(down_words);
    cout << "# words down: " << down_words << endl;
    while (down_words-- > 0) {
        int row = NUM_ROWS, col = NUM_COLS;
        read_int_persistently(row);
        read_int_persistently(col);
        cin >> word;
        add_word(row, col, word, 'd');
    }
}

int main(int argc, char* argv[]) {

        ifstream dictionary;
        dictionary.open("dictionary.txt");
        if (!dictionary.is_open()) {
                cerr << "error:  cannot open dictionary" << endl;
        }
        else {
                //Check that stream works
                //getline (dictionary, line);
                //cout << line << endl;
                dictionary.close();
        }

        // Going to use bitsets to optimize char storage (5 bits / char (instead of 8)
        bitset<M> dawg(string("1100"));
        cout << dawg << ' ' << sizeof(dawg) << endl;

        //int tile = 1;
        int tile = 0;
        for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++, tile++) {
                        if (tile == 113)
                                scrabble_board[i][j] = '*';
                        else if (tile % 2 == 0)
                                scrabble_board[i][j] = '|';
                        else
                                scrabble_board[i][j] = '_';
                }
        }

        set_board();

        print_board();
}

