// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <vector.h>
#include <queue.h>
// TODO: include any other headers you need; remove this comment
using namespace std;

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    Vector<Vertex*> path;
    bool found = false;
    return helper(graph, start, end, path, found);
}

Vector<Vertex*> helper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path, bool& found){
    path.add(start);
    int startInx = path.size() - 1;
    start->visited = true;
    start->setColor(GREEN);
    if(start == end){
        found = true;
        return path;
    }
    else{
        Set<Arc*> nodeArcs = start->arcs;
        foreach(Arc* next in nodeArcs){
            if(!next->finish->visited){
              path = helper(graph, next->finish, end, path, found);
              if(found){
                  return path;
              }
              else{
                  path.get(path.size() - 1)->setColor(GRAY);
                  path.remove(path.size() - 1);
              }
            }
        }
    }
    return path;
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    Vector<Vertex*> path;
    Queue<Vertex*> q;
    q.enqueue(start);
    start->visited = true;
    while(!q.isEmpty()){
        Vertex* v = q.dequeue();
        v->setColor(GREEN);
        if (v == end){
            cout << "  !!FOUND!!  ";
            while(v != NULL){
                path.insert(0, v);
                v = v->previous;
            }
            return path;
        }
        Set<Arc*> nodeArcs = v->arcs;
        foreach(Arc* next in nodeArcs){
            cout << next->toString();
            if(!next->finish->visited){
              q.enqueue(next->finish);
              next->finish->visited = true;
              next->finish->setColor(YELLOW);
              next->finish->previous = v;
            }
        }
    }
}


Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    Set<Node*> graphNodes = graph.getVertexSet();
    foreach(Node* node in graphNodes){
        node->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    PriorityQueue<Vertex*> pq;
    pq.enqueue(start, 0);
    Vector<Vertex*> path;
    while(!pq.isEmpty()){
        Vertex* current = pq.dequeue();
        current->visited = true;
        current->setColor(GREEN);
        if(current == end){
            cout << "!!!FOUND!!!";
            while(current != NULL){
                path.insert(0, current);
                current = current->previous;
            }
            return path;
        }
        else{
            foreach (Arc* curArc in current->arcs) {
                int cost = current->cost + curArc->cost;
                if(cost < curArc->finish->cost){
                    curArc->finish->previous = current;
                    if(curArc->finish->cost != POSITIVE_INFINITY){
                        curArc->finish->cost = cost;
                        pq.changePriority(curArc->finish, cost);
                    }
                    else{
                        curArc->finish->setColor(YELLOW);
                        curArc->finish->cost = cost;
                        pq.enqueue(curArc->finish, cost);
                    }
                }

            }
        }
    }
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    Set<Node*> graphNodes = graph.getVertexSet();
    foreach(Node* node in graphNodes){
        node->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    PriorityQueue<Vertex*> pq;
    pq.enqueue(start, start->heuristic(end));
    Vector<Vertex*> path;
    while(!pq.isEmpty()){
        Vertex* current = pq.dequeue();
        current->visited = true;
        current->setColor(GREEN);
        if(current == end){
            cout << "!!!FOUND!!!";
            while(current != NULL){
                path.insert(0, current);
                current = current->previous;
            }
            return path;
        }
        else{
            foreach (Arc* curArc in current->arcs) {
                int cost = current->cost + curArc->cost;
                if(cost < curArc->finish->cost){
                    curArc->finish->previous = current;
                    if(curArc->finish->cost != POSITIVE_INFINITY){
                        curArc->finish->cost = cost;
                        pq.changePriority(curArc->finish, cost + curArc->finish->heuristic(end));
                    }
                    else{
                        curArc->finish->setColor(YELLOW);
                        curArc->finish->cost = cost;
                        pq.enqueue(curArc->finish, cost + curArc->finish->heuristic(end) );
                    }
                }

            }
        }
    }
}

findMinimumVertexCover(BasicGraph& graph){
    Set<Vertex*> nodes = graph.getNodeSet();
    Set<Arc*> arcs = graph.getArcSet();
    int num = arcs.size();


    return nodes;
}
