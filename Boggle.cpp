// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include"lexicon.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[16] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    createDictionary();
    initializeTrackGrid();
}

void Boggle::makeGrid(){
    Grid<string> mainGrid(4, 4);
    fillMainGrid(mainGrid);
    shuffle(mainGrid);
    fillFaceUpGrid(faceUpGrid, mainGrid);
}

void Boggle::fillMainGrid(Grid<string>&mainGrid){
    for(int i = 0; i < NUM_CUBES; i++){
        int row = i / 4;
        int column = i % 4;
        string str = CUBES[i];
        shuffleStr(str);
        mainGrid[row][column] = str;
    }
}

void Boggle::shuffleStr(string& str){
        for (int i = 0; i < str.length(); i++) {
            int j = randomInteger(i, str.length() - 1);
            if (i != j) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }

void Boggle::fillFaceUpGrid(Grid<char>& faceUpGrid, Grid<string>& mainGrid){
    faceUpGrid.resize(4, 4);
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            string str = mainGrid[row][col];
            faceUpGrid[row][col] = tolower(str[0]);
        }
    }
}

void Boggle::makeCustomizedGrid(string line){
    faceUpGrid.resize(4, 4);
    for(int i = 0; i < line.length(); i++){
        int row = i / 4;
        int col = i % 4;
        faceUpGrid[row][col] = tolower(line[i]);
    }
}

void Boggle::showGrid(){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            cout << faceUpGrid[row][col];
        }
        cout << endl;
    }
}

void Boggle::createDictionary(){
    lex.addWordsFromFile("EnglishWords.dat");
}

bool Boggle::containsWord(string word){
    return lex.contains(word);
}

bool Boggle::wordAcceptable(string word){
    return lex.contains(word) && word.length() > 3; //&&  !wordsFound.contains(word);
}

void Boggle::initializeTrackGrid(){
    trackGrid.resize(4, 4);
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            trackGrid[row][col] = 0;
        }

    }
}

bool Boggle::isOnBoard(string word){
    initializeTrackGrid();
    for(int i = 0; i < faceUpGrid.nRows; i++ ){
        for(int j = 0; j < faceUpGrid.nCols; j++){
            if(faceUpGrid[i][j] == word[0]){
                trackGrid[i][j] = 1;
                char firstLetter = word[0];
                word.erase(0, 1);
                if(findNext(word, i, j, faceUpGrid)){
                    return true;
                }
                word.insert(0, 1, firstLetter);
                trackGrid[i][j] = 0;
            }
        }
    }
    return false;
}

bool Boggle::findNext(string word, int row, int col, Grid<char>& faceUpGrid){
    if(word.size() == 0){
        return true;
    }
    else{
        for(int rowChange = -1; rowChange < 2; rowChange++){
               for(int colChange = -1; colChange < 2; colChange++){
                    if(notExplored(row + rowChange, col + colChange)){
                        if(faceUpGrid[row + rowChange][col + colChange] == word[0]){
                            int nextLetter = word[0];
                            word.erase(0, 1);
                            trackGrid[row + rowChange][col + colChange] = 1;
                            if (Boggle::findNext(word, row + rowChange, col + colChange, faceUpGrid)){
                                return true;
                            }
                            word.insert(0, 1, nextLetter);
                            trackGrid[row + rowChange][col + colChange] = 0;
                        }
                    }
                }
            }
    }
    return false;
}

int Boggle::countWords(){
    return wordsFound.size();
}

bool Boggle::notExplored(int row, int col){
    if(trackGrid.inBounds(row, col)){
        return trackGrid[row][col] == 0;
    }
    else {
        return false;
    }
}

bool Boggle::addWord(string word){
    if(!wordsFound.contains(word)){
        wordsFound.add(word);
        return true;
    }
    else{
        return false;
    }
}

Set<string> Boggle::showWords(){

    return wordsFound;
}

//search all the possible words formed
//in the grid. this function is called
//when it's computer's turn.
void Boggle::searchAll(){
    for(int row = 0; row < faceUpGrid.numRows(); row++){
        for(int col = 0; col < faceUpGrid.numCols(); col++){
            string word = "";
            initializeTrackGrid();
            word += (faceUpGrid.get(row, col));
            trackGrid[row][col] = 1;
            searchAllHelper(faceUpGrid, row, col, word);
        }
    }
}

void Boggle::searchAllHelper(Grid<char>& faceUpGrid, int row, int col, string& word){
    if(lex.containsPrefix(word)){
        for(int rowChange = -1; rowChange < 2; rowChange++){
               for(int colChange = -1; colChange < 2; colChange++){
                    if(notExplored(row + rowChange, col + colChange)
                            && (lex.containsPrefix(word + faceUpGrid[row + rowChange][col + colChange]) || word.size() == 0)){
                        char nextLetter = faceUpGrid[row + rowChange][col + colChange];
                            word.insert(word.size(), 1, nextLetter);
                            if(lex.contains(word) && word.size() > 3 && !UsersWords.contains(word)){
                                wordsFound.add(word);
                            }
                            else{
                                trackGrid[row + rowChange][col + colChange] = 1;
                            }
                            (Boggle::searchAllHelper(faceUpGrid, row + rowChange, col + colChange, word));
                            word.erase(word.size() - 1, 1);
                            trackGrid[row + rowChange][col + colChange] = 0;
                    }
                }
            }
    }
}

void Boggle::eraseWords(string player){
    if(player == "computer"){
        wordsFound.clear();
    }
    else if(player == "user"){
        UsersWords.clear();
    }
}

void Boggle::saveWords(){
       foreach(string word in wordsFound){
           UsersWords.add(word);
       }
}

int Boggle::calculateScores(){
    int score = 0;
    foreach(string word in wordsFound){
        score += word.length() - 3;
    }
    return score;
}
