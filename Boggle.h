// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "vector.h"
#include "grid.h"
#include"lexicon.h"
#include"set.h"
// TODO: include any other header files you need (e.g. Stanford collections)

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    void makeGrid();
    void makeCustomizedGrid(string line);
    void showGrid();
    bool containsWord(string word);
    void createDictionary();
    bool wordAcceptable(string word);
    bool addWord(string word);
    Set<string> showWords();
    Boggle();
    bool isOnBoard(string word);
    void searchAll();
    int countWords();
    void eraseWords(string player);
    void saveWords();
    int calculateScores();

private:
    Grid<char> faceUpGrid;
    Lexicon lex;
    Set<string> wordsFound;
    Set<string> UsersWords;
    Grid<char> trackGrid;
    void fillFaceUpGrid(Grid<char>& faceUpGrid, Grid<string>& mainGrid);
    void shuffleStr(string& str);
    void fillMainGrid(Grid<string>& mainGrid);
    bool findNext(string word, int row, int col, Grid<char>& faceUpGrid);
    bool notExplored(int row, int col);
    void initializeTrackGrid();
    void searchAllHelper(Grid<char>& faceUpGrid, int row, int col, string& word);

};

#endif
