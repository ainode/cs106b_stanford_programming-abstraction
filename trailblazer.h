/*
 * CS 106B Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Version: 2013/11/24 (initial version for 13au)
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include "vector.h"
#include "set.h"
#include "BasicGraph.h"
#include <pqueue.h>

Vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);
Vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);
Vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);
Vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);
Vector<Vertex*> helper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path, bool& found);


#endif
