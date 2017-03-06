// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "AssassinsList.h"
#include "strlib.h"

AssassinsList::AssassinsList(istream& input) {
    string line;
    Node* previous = NULL;
    while(getline(input, line)){
        Node* newNode = new Node(line, previous);
        previous = newNode;
    }
    f_node = previous;
    checkIfEmpty(previous);

}

AssassinsList::~AssassinsList() {
    Node* trash;
    while(f_node != NULL ){
        trash = f_node;
        f_node = f_node->next;
        delete trash;
    }

}

void AssassinsList::printGameRing() {
    Node* fcurrent = f_node;
    if(fcurrent->next == NULL){
        cout << " the winner is: " << fcurrent->name;
    }
    while(fcurrent->next != NULL){
        cout << "  " << fcurrent->name << " is targeting " << fcurrent->next->name << endl;
        fcurrent = fcurrent->next;
    }
    cout << "  " << findLast() << " is targeting " << f_node ->name << endl;
}

void AssassinsList::printGraveyard() {
    Node* gcurrent = f_grave;
    while(gcurrent != NULL){
        cout << "  " << gcurrent->name << " was eliminated by " << gcurrent->killer << endl;
        gcurrent = gcurrent->next;
    }

}

bool AssassinsList::isAlive(string& player)  {
    Node* tempnode = f_node;
    return exists(player, tempnode);
}

bool AssassinsList::isDead(string& player) {
    Node* tempg = f_grave;
    return exists(player, tempg);
}

bool AssassinsList::isGameOver() const {
    return (f_node->next == NULL);
}

string AssassinsList::winner() {
    string winner = f_node->name;
    return winner;
}

void AssassinsList::eliminate(string& player) {
    Node* current = f_node;
    string msg;
    if(isGameOver()){
        msg = "game over";
        throw msg;
    }
    //if the first one in the ring is
    //to be eliminated.
    else if(toLowerCase(current->name) == toLowerCase(player)){
        current->killer = findLast();
        f_node = f_node->next;
        current->next = f_grave;
        f_grave = current;
    }
    else{
        while(current->next != NULL){
            if(toLowerCase(current->next->name) == toLowerCase(player)){
                current->next->killer = current->name;
                Node* temp = current->next;
                current->next = current->next->next;
                temp->next = f_grave;
                f_grave = temp;
                break;
            }
            else {
                current = current->next;
            }
        }
    }
}

void AssassinsList::checkIfEmpty(Node *f_node) const{
    if(f_node == NULL){
        throw " file is empty.";
    }
}

/* see if the given player exist in
 * the list. can be game ring or
 * grave yard.*/
bool AssassinsList::exists(string& player, Node*& node) const{
    while(node != NULL){
       if(toLowerCase(node->name) == toLowerCase(player)){
            return true;
        }
        else{
            node = node->next;
        }
    }
    return false;
}

/*find the last element in the
 * game ring.*/
string AssassinsList::findLast(){
    Node* killer;
    killer = f_node;
    while(killer->next != NULL){
        killer = killer->next;
    }
    return killer->name;
}
