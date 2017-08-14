#include <iostream>
#include <fstream>
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
                         {'s', 4}, {'t', 6}, {'u', 4}, {'v', 2}, {'w', 2}, {'x', 1}, {'y', 2}, {'z', 1}, {' ', 2}}; 
}

void init_tile_bag() {
        tile_bag = {{'a', 1}, {'b', 3}, {'c', 3}, {'d', 2}, {'e', 1}, {'f', 4}, {'g', 2}, {'h', 4}, {'i', 1}, 
                    {'j', 8}, {'k', 5}, {'l', 1}, {'m', 3}, {'n', 1}, {'o', 1}, {'p', 3}, {'q', 10}, {'r', 1}, 
                    {'s', 1}, {'t', 1}, {'u', 1}, {'v', 4}, {'w', 4}, {'x', 8}, {'y', 4}, {'z', 10}, {' ', 0}};
}

void set_rack(char rack[]) {
        for (int i = 0; i < RACK_SIZE; i++) {
                
        }
}

int main(int argc, char* argv[]) {

        ifstream dictionary;
        string line;
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

        int idx = 0;
        cout << "Constructing Scrabble board for: " << endl;
        // This is where user can provide #across words followed by that #lines "{start pos} {word}",
        //                                #down words followed by that #lines "{start pos} {word}" (.txt file)
        while (getline(cin, line)) {
                cout << idx++ << ") " << line << endl;
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
                                scrabble_board[i][j] = 'E';
                        } else {
                                scrabble_board[i][j] = 'O';
                        }
                }
        }
        print_board();
}

