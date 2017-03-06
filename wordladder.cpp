// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "hashmap.h"
#include "hashset.h"
#include "map.h"
#include "queue.h"
#include "random.h"
#include "set.h"
#include "simpio.h"
#include "stack.h"
#include "vector.h"

int countStacks = 0;

using namespace std;
void readDictionary();
void wordLadder(string& w1, string& w2);
void examineNeighbors(Stack<string>& f, HashSet<string>& s, Queue<Stack<string> >& queue, HashSet<string> dict, string& word1, string& word2);
void createDictionary(HashSet<string>& dict);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);

    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    while(true){
        cout << "Please type two words: ";
        string word1;
        string word2;
        cin >> word1 >> word2;
        if(word1 == "")
            break;
        wordLadder(word1, word2);
    }
    cout << "Have a nice day." << endl;
    return 0;
}

void wordLadder(string& w1, string& w2){
    HashSet<string> dictionary;
    HashSet<string> seenWords;
    Queue<Stack<string> > q;
    Stack<string> stack1;
    createDictionary(dictionary);
    stack1.push(w1);
    q.enqueue(stack1);int count = 0;
    while(!q.isEmpty()){
       Stack<string> frontStack = q.dequeue();
       if(frontStack.peek() == w2){
           cout << "The answer is: ";
           cout << frontStack.toString() << endl;
           cout << q.size();
           break;
       }
       else{
           examineNeighbors(frontStack, seenWords, q, dictionary, w1, w2);count++;
       }
    }
    cout << "COUNT:  " << count << endl;
    cout << "Stack count:  " << countStacks;
}

void examineNeighbors(Stack<string>& f, HashSet<string>& s, Queue<Stack<string> >& queue, HashSet<string> dict, string& word1, string& word2){
    string currentWord = f.peek();
    //cout << currentWord;
    for(int i = 0; i < currentWord.size(); i++){
        if(currentWord[i] == word1[i])
            for(char j = 'a'; j <= 'z'; j++){
               string tempStr = currentWord;
               countStacks++;
               tempStr[i] = j;
               if(!s.contains(tempStr) && dict.contains(tempStr)){
                   string str = tempStr;
                   s.add(str);
                   Stack<string> newStack = f;
                   newStack.push(tempStr);
                   queue.enqueue(newStack);
                   if(tempStr == word2)
                       cout << "FOUND!!!!:  " << newStack.toString();
                }
            }
    }
}

void createDictionary(HashSet<string>& dict){
    ifstream input;
    input.open("dictionary.txt");
    string word;
    while(getline(input, word)){
        dict.add(word);
    }
}
