// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
#include "strlib.h"

TileList::TileList() {
    capacity = 10;
    size = 0;
    listOfTiles = new Tile[capacity];

}

TileList::~TileList() {
    delete[] listOfTiles;

}

void TileList::addTile(Tile tile) {
   if(size == capacity){
       increaseCapacity();
    }
   listOfTiles[size] = tile;
   size++;
}

void TileList::drawAll(GWindow& window) {
    for(int i = 0; i < size; i ++){
        listOfTiles[i].draw(window);
    }
}

const int TileList::indexOfTopTile(int x, int y) {

    returnTopIndex(x, y);
}

void TileList::raise(int x, int y) {
    for(int i = size - 1; i >= 0; i--){
        if(listOfTiles[i].contains(x, y)){
            moveToTop(listOfTiles[i], i);
            break;
        }
    }

}

void TileList::lower(int x, int y) {
    int index = returnTopIndex(x, y);
    if(index >= 0){
        Tile temp = listOfTiles[index];
        for(int i = index; i > 0; i--){
            listOfTiles[i] = listOfTiles[i - 1];
        }
        listOfTiles[0] = temp;
    }
}

void TileList::remove(int x, int y) {
    int index = returnTopIndex(x, y);
    if(index >= 0){
        if(capacity == size){
            increaseCapacity();
        }
        for(int i = index; i < size; i++){
            listOfTiles[i] = listOfTiles[i + 1];
        }
       size--;
    }
}

void TileList::removeAll(int x, int y) {
    for(int i = size - 1; i >= 0; i--){
        if(listOfTiles[i].contains(x, y)){
            remove(x, y);
        }
    }
}

void TileList::moveToTop(Tile& tile, int i){
    Tile temp = tile;
    for(int j = i; j < size; j++){
        listOfTiles[j] = listOfTiles[j + 1];
    }
    listOfTiles[size - 1] = temp;
}

int TileList::returnTopIndex(int x, int y){
    int inx = -1;
    for(int i = size - 1; i >= 0; i--){
        if(listOfTiles[i].contains(x, y)){
            inx = i;
            break;
        }
    }
    return inx;
}

void TileList::increaseCapacity(){
    capacity += 10;
    Tile* newArr = new Tile[capacity];

    //memcpy( newArr, listOfTiles, capacity * sizeof(Tile) );
    for(int i = 0; i < size; i++){
        newArr[i] = listOfTiles[i];
    }

    delete [] listOfTiles;
    listOfTiles = newArr;
}
