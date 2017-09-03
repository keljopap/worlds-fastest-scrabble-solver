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
    switch(orientation) {
        case 'a':
            if (col + word.length() < NUM_COLS && row < NUM_ROWS) {
                for (int i = 0; i < word.length(); i++) {
                    scrabble_board[row][col+i] = word[i];
                }
            }
            break;
        case 'd':
            if (row + word.length() < NUM_ROWS && col < NUM_COLS) {
                for (int i = 0; i < word.length(); i++) {
                    scrabble_board[row+i][col] = word[i];
                }
            }
            break;
    }
}

void set_board() {

    int idx = 0;
    cout << "Constructing Scrabble board for:      (odd squares = '_', even squares = '|')" << endl;
    // This is where user can provide #across words followed by that #lines "{start pos} {word}",
    //                                #down words followed by that #lines "{start pos} {word}" (.txt file)

    string line;
    int across_words = 0;
    int down_words = 0;

    getline(cin, line);
    across_words = std::stoi(line);
    cout << "across: " << across_words << endl;

    while (across_words-- > 0) {
        getline(cin, line);
        
        cout << idx++ << ") " << line << endl;
        istringstream iss(line);
        int row = NUM_ROWS, col = NUM_COLS;
        iss >> row >> col;
        string word;
        iss >> word;
        add_word(row, col, word, 'a');
    }

    getline(cin, line);
    down_words = std::stoi(line);
    cout << "down: " << down_words << endl;

    while (down_words-- > 0) {
        getline(cin, line);
        cout << idx++ << ") " << line << endl;

        istringstream iss(line);
        int row = NUM_ROWS, col = NUM_COLS;
        iss >> row >> col;
        string word;
        iss >> word;
        add_word(row, col, word, 'd');
    }
    cout << endl;
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

        int tile = 1;
        for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                        tile = 1 + (i*NUM_ROWS)+j;
                        if (tile < argc) {
                                scrabble_board[i][j] = *argv[tile];
                        } else if (tile == 113) {
                                scrabble_board[i][j] = '*';
                        } else if (tile%2==0) {
                                scrabble_board[i][j] = '|';
                        } else {
                                scrabble_board[i][j] = '_';
                        }
                }
        }

        set_board();

        print_board();
}

