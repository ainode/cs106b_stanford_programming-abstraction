/*
 * CS 106B Huffman Encoding
 * This file declares the functions that you will need to write in this
 * assignment for your Huffman Encoder in huffmanencoding.cpp.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author : Marty Stepp
 * Version: Thu 2013/11/14
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include "bitstream.h"
#include "HuffmanNode.h"
#include "map.h"
#include "pqueue.h"
using namespace std;

/*
 * See huffmanencoding.cpp for documentation of these functions
 * (which you are supposed to write, based on the spec).
 */
Map<int, int> buildFrequencyTable(istream& input);
//build a tree based on frequency of characors to traverse
//and incode the charactors based on their frequency. Parameter: encoding tree
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable);
//build a map based on encoding tree that maps the ascii's charactor
//numbers to binary codes that are found through traversing the tree.
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
//encodes data recieved through an input stream and writes it to an output stream
//using map. input stream is in bytes and writes to output in bits.
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output);
//decode data recieved in bits from input stream and puts it out in bytes
//in an output stream, using an encoding tree.
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);

void compress(istream& input, obitstream& output);
void decompress(ibitstream& input, ostream& output);
void freeTree(HuffmanNode* node);
HuffmanNode* buildTree(PriorityQueue<HuffmanNode *> &pq);
void buildMap(HuffmanNode* &encodingTree, Map<int, string>& encodingMap, string binaryCode);

#endif
