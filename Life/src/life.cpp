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
#include "gwindow.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

struct subject{
    string name;
    int min = 0;
    int max = 0;
    int ave = 0;
};

void introduction();
void getFileName(ifstream& input);
void showOriginalGrid(ifstream& input, Grid<char>& grid);
void fillGrid(ifstream& input, Grid<char>& grid);
char usersChoice();
void play(Grid<char> grid);
void nextGen(Grid<char>& grid);
int countLiveNabours(int numRow, int numCol, Grid<char> &grid);
void checkForNabours(int numRow, int numCol, int &nabourCount, Grid<char> grid);
void showGrid(Grid<char>& grid);
void MergeVectors(Vector<int>& v1, Vector<int>& v2);
 subject buildSubject();





subject buildSubject(){
    subject sub;
    ifstream inp;
    string fileName;
    cout << "Enter file name: " << endl;
    cin >> fileName;
    inp.open(fileName.c_str());
    string line;
    int ave = 0, min = 0, max = 0, sum = 0, count = 0;
    while(getline(inp, line)){
        count ++;
        int result = 0;
        result = stringToInteger(line);
        if(result > max)
            max = result;
        if(result < min)
            min = result;
        sum += result;
    }
    ave = sum/count;
    sub.max = max;
    sub.min = min;
    sub.name = fileName;
    sub.ave = ave;
    return sub;
}

int main() {
    ifstream input;
    Grid<char> grid;
    setConsoleSize(700, 400);
    introduction();
    getFileName(input);
    showOriginalGrid(input, grid);
    play(grid);
    cout << "Have a nice Life!" << endl;
    input.close();
/*this part upto the end of main is not
 * related to the (game of)life project. I have used
 * the main to solve the problem of constructing a
 * vector from two vectors which holds the members
 * that are common between the two.
 */

    Vector<int> vec1; vec1 += 2; vec1 += 4; vec1 += 5; vec1 += 8; vec1 += 11;
    Vector<int> vec2;vec2 += 1;vec2 += 2;vec2 += 3;vec2 += 5;vec2 += 6;vec2 += 8; vec2 += 9;

    cout << vec1 << endl;
    cout << vec2 << endl;

    MergeVectors(vec1, vec2);

    cout << "result:" << endl;
    cout << vec1 << endl;

    cout << buildSubject().max;

    return 0;
}

void introduction(){
    cout << "Welcome to cs107 Game of life,this program simulates" << endl;
    cout << "the life cyle of a bacteria." << endl;
    cout << "this is how it works: " << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." <<endl;
    cout << "- Locations with 3 neighbors will create life." <<endl;
    cout << "- A cell with 4 or more neighbors dies." <<endl;
    cout << endl;
}

/*get file name containing the grid
 * from the user.
 */
void getFileName(ifstream& input){
    while(true){
       cout << "Grid input file name: " ;
       string name;
       cin >> name;
       input.open(name);
       if(!input.fail()){
           break;
       }
       else{
           cout << "could not opet the file." << endl;
       }
    }
}

/* shows the original grid and fills
 * up the grid data structure accordingly
 * */
void showOriginalGrid(ifstream& input, Grid<char>& grid){
    string line;
    int row;
    int collumn;
    getline(input, line);
    row = stringToInteger(line);
    getline(input, line);
    collumn = stringToInteger(line);
    grid.resize(row, collumn);
    fillGrid(input, grid);
}

/*fill the grid with data from the given file*/
void fillGrid(ifstream& input, Grid<char>& grid){
    string line;
    int rowCount = 0;
    while (getline(input, line)){
        if (line.empty()){
            break;
        }
        for(int unsigned i = 0; i < line.size(); i++){
            grid[rowCount][i] = line[i];
        }
        rowCount ++;
        cout << line << endl;
    }
}

/* ask user for the choice of
 * number of times for animation
 * or quitting.
 */
void play(Grid<char> grid){
    while(true){
        char choice = usersChoice();
        if (choice == 'q'){
            break;
        }
        else if(choice == 'a'){
            int animateNum;
            cout << "how many times? ";
            cin >> animateNum;
            for(int i = 0; i < animateNum; i++){
                nextGen(grid);
                pause(10);
            }
        }
        else {
            nextGen(grid);
        }
    }
}

char usersChoice(){
    char choice;
    cout << "a)nimate t)ick q)uit ? ";
    cin >> choice;
    return choice;
}

/* produce the next generation of
 * the game of life.
 */
void nextGen(Grid<char>& grid){
    Grid<char> temp = grid;
    for(int i = 0; i < grid.numRows(); i ++){
        for(int j = 0; j < grid.numCols(); j++){
            if(countLiveNabours(i, j, grid) <= 1 || countLiveNabours(i, j, grid) >= 4){
                temp[i][j] = '-';
            }
            else if (countLiveNabours(i, j, grid) == 3) {
                temp[i][j] = 'X';
            }
        }
    }
    grid = temp;
    showGrid(grid);
}

/*go through all 8 neibours and see
 * which one is alive. return the count.
 */
int countLiveNabours(int numRow, int numCol, Grid<char>& grid){
    int nabourCount = 0;
    checkForNabours(numRow + 1, numCol, nabourCount, grid);
    checkForNabours(numRow + 1, numCol + 1, nabourCount, grid);
    checkForNabours(numRow, numCol + 1, nabourCount, grid);
    checkForNabours(numRow - 1, numCol - 1, nabourCount, grid);
    checkForNabours(numRow - 1, numCol, nabourCount, grid);
    checkForNabours(numRow - 1, numCol + 1, nabourCount, grid);
    checkForNabours(numRow, numCol - 1, nabourCount, grid);
    checkForNabours(numRow + 1, numCol - 1, nabourCount, grid);
    return nabourCount;
}

void checkForNabours(int numRow, int numCol, int& nabourCount, Grid<char> grid){
    if(grid.inBounds(numRow, numCol) && grid[numRow][numCol] == 'X'){
        nabourCount += 1;
    }
}

void showGrid(Grid<char> &grid){
    for(int i = 0; i < grid.nRows; i++){
        for(int j = 0; j < grid.nCols; j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
}

/* this function is unrelated to the game
 * of life and I just used this project to
 * test the solution to a different problem.
 */
void MergeVectors(Vector<int> &v1, Vector<int> &v2){
    int j = 0;
    int i = 0;
    while(i < v1.size() && j < v2.size()){
        if(v1.get(i) < v2.get(j)){
            v1.remove(i);
         }
        else if (v1.get(i) == v2.get(j)){
            i++;
        }
        else if (v1.get(i) > v2.get(j)){
            j++;
            if (j >= v2.size()){
                v1.remove(i);
            }
        }
    }
}
