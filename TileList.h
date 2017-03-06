// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef _tilelist_h
#define _tilelist_h

#include <iostream>
#include <string>
#include "gobjects.h"
#include "gwindow.h"
#include "strlib.h"
#include "Tile.h"
using namespace std;

class TileList {
public:
    TileList();
    ~TileList();
    /*add a tile to the tile list*/
    void addTile(Tile tile);
    /*draw all the tiles from the tile list
     * using the window object*/
    void drawAll(GWindow& window);
    /*return the index of the topmost tile
     * in the tile list that touches coordinates
     * x and y*/
    int const indexOfTopTile(int x, int y);
    /*lower the topmost tile that touches
     * x and y to the bottom of the list*/
    void lower(int x, int y);
    /*raise the tile that touches x and y
     * to the top of the tile list*/
    void raise(int x, int y);
    /*remove the topmost tile that touches
     * x and y*/
    void remove(int x, int y);
    /*remove all the tiles that touch x and y*/
    void removeAll(int x, int y);

private:
    /*helper methods.
     * move the tile to the top of the list*/
    void moveToTop(Tile& tile, int i);
    /*return the index of the top tile and x and y*/
    int returnTopIndex(int x, int y);
    /* increase the capacity of the array
     * by 10.*/
    void increaseCapacity();
    Tile* listOfTiles;
    int capacity;
    int size;
};

#endif
