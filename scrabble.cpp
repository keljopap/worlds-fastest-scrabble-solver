#include <iostream>
#include <fstream>
using namespace std;

int NUM_ROWS = 25;
int NUM_COLS = 25;
int RACK_SIZE = 7;
char scrabble_board[25][25];
int my_rack[27];

void print_board() {
        for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {
                        cout << scrabble_board[i][j];
                }
                cout << endl;
        }
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
                while ( getline (dictionary, line) ) {
                        cout << line << '\n';
                }
                dictionary.close();
        }

        int tile = 1;
        for (int i = 0; i < NUM_ROWS; i++) {
                for (int j = 0; j < NUM_COLS; j++) {

                        tile = (i*NUM_ROWS)+j;
                        if (tile < argc) {
                                scrabble_board[i][j] = *argv[tile];
                        } else {
                                scrabble_board[i][j] = ' ';
                        }
                }
        }
        print_board();
}

