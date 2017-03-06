// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "console.h"
#include "simpio.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    boggle.createDictionary();
    string prompt = "Do you want the computer to give you the choice of dices?";
    if(yesOrNo(prompt)){
        boggle.makeGrid();
        play(boggle);
    }
    else{
        string line;
        while(true){
            line = getLine("Enter 16 letters:");
            if(evaluate(line)){
                boggle.makeCustomizedGrid(line);
                play(boggle);
                break;
            }
        }
    }
    boggle.searchAll();
    cout << "Words found (" << boggle.countWords() << ") :" << boggle.showWords() << endl;
    cout << "My scores: " << boggle.calculateScores() <<endl;
    boggle.eraseWords("user");
    boggle.eraseWords("computer");
}

bool evaluate(string line){
    if(line.length() != 16){
        cout << "Please enter 16 charactors: " << endl;
        return false;
    }
    else{
        foreach(char ch in line){
                if(!isalpha(ch)){
                    return false;
                }
            }
    }
    return true;
}

void play(Boggle& boggle){
    int humanScore = 0;
    boggle.showGrid();
    while(true){
        string word = getLine("Enter your word or enter to exit: ");
        word = toLowerCase(word);
        if(word == ""){
            break;
        }
        if(boggle.wordAcceptable(word)&& boggle.isOnBoard(word)){
            if(!boggle.addWord(word)){
                cout << "word already found." << endl;
            }
            else{
                cout << "You found a new word: " << word << endl;
                humanScore += word.size() - 3;
            }
            cout << "Words found (" << boggle.countWords() << "): " <<boggle.showWords() << endl;
            string response = "Do you want to enter another word? ";
            if(!yesOrNo(response)){
                break;
            }
        }
        else{
             cout << "not acceptable" << endl;
        }
    }
    boggle.saveWords();
    boggle.eraseWords("computer");
    cout << "Your score: " << humanScore << endl;
}

