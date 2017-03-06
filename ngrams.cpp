// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
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
#include "vector.h"

using namespace std;
void fillMap(HashMap<Vector<string>, Vector<string> >& map, Vector<string>& v, int n);
void vectorizeFile(Vector<string>& v, ifstream& input);
string makeText(HashMap<Vector<string>, Vector<string> >& map, int len);

int main() {
    setConsoleSize(750, 450);
    setConsoleFont("Courier New-16");
    setConsoleEcho(true);

    string fileName = getLine("Please enter file name: ");
    int n = getInteger("Value of N? ");
    int outputLen = getInteger("# of random words to be generated (0 to quit)?");
    HashMap<Vector<string>, Vector<string> > map;
    ifstream input;
    input.open(fileName.c_str());
    Vector<string> vec;
    vectorizeFile(vec, input);
    fillMap(map, vec, n);
    string myText = makeText(map, outputLen);
    cout << "Final text: " <<myText;
    cout << "Exiting." << endl;
    return 0;
}

void fillMap(HashMap<Vector<string>, Vector<string> >& map, Vector<string>& v, int n){
    Vector<string> window;
    for(int i = 1; i < n; i++){
        v.add(v[i]);
        window.add(v[i]);
    }
    for(int cursor = n; cursor < v.size(); cursor++){
        if(map.containsKey(window)){
            //map.get(window).add(v[cursor]);
            Vector<string> vec = map.get(window);
            vec.add(v[cursor]);
            map.put(window, vec);
        }
        else{
            Vector<string> vec;
            vec.add(v[cursor]);
            map.put(window, vec);
        }

        window.remove(0);
        window.add(v[cursor]);
    }
}

void vectorizeFile(Vector<string>& v, ifstream& input){
    string line;
    while(getline(input, line)){
        istringstream tokens(line);
        while(true){
            string word;
            tokens >> word;
            if(tokens.fail()){
                break;
            }
            v.add(word);
        }
    }
}

string makeText(HashMap<Vector<string>, Vector<string> >& map, int len){
    string text;
    Vector<Vector<string> > mapKeys = map.keys();
    //cout << mapKeys.toString();
    int index = randomInteger(0, mapKeys.size() - 1);
    Vector<string> key = mapKeys[index];
    for(int i = 0; i < key.size(); i++){
        text += key[i];
        text += " ";
    }
    int lenDif = len - key.size();
    for(int j = 0; j < lenDif; j++){
        string nextWord = map.get(key)[randomInteger(0, map.get(key).size() - 1)];
        key.add(nextWord);
        key.remove(0);
        //cout << key << endl;
        text += nextWord;
        text += " ";
    }
    return text;
}
