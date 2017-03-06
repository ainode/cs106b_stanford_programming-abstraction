// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"

//find out how frequently charactors are occuring in the file.
Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    while(true){
        int byte = input.get();
        cout << "byte: " << byte;
        if( byte == -1){
            break;
        }
        else{
            if(freqTable.containsKey(byte)){
                freqTable.put(byte, freqTable.get(byte) + 1);
            }
            else{
                freqTable.put(byte, 1);
            }
        }
    }
    //add a specific marker to mark end of file
    freqTable.put(PSEUDO_EOF, 1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pq;
    foreach(int byteKey in freqTable){
        HuffmanNode* node = new HuffmanNode(byteKey, freqTable.get(byteKey), NULL, NULL);
        double priority = (double)freqTable.get(byteKey);
        pq.enqueue(node, priority);
    }
    return buildTree(pq);
}

HuffmanNode* buildTree(PriorityQueue<HuffmanNode*>& pq){
    if(pq.size() == 1){HuffmanNode* final = pq.dequeue();
        return final;
    }
    else{
        HuffmanNode* node1 = pq.dequeue();
        HuffmanNode* node2 = pq.dequeue();
        HuffmanNode* newNode = new HuffmanNode(NOT_A_CHAR, node1->count + node2->count, node1, node2);
        pq.enqueue(newNode, newNode->count);
        buildTree(pq);
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    string binaryCode = "";
    buildMap(encodingTree, encodingMap, binaryCode);
    freeTree(encodingTree);
    return encodingMap;
}

void buildMap(HuffmanNode* &encodingTree, Map<int, string>& encodingMap, string binaryCode){
    if(encodingTree->isLeaf()){
        encodingMap.put(encodingTree->character, binaryCode);
    }
    else{
       buildMap(encodingTree->zero, encodingMap, binaryCode + "0");
       buildMap(encodingTree->one, encodingMap, binaryCode + "1");
    }
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    while(true){
        int ch = input.get();
        //end of file (-1)
        if(ch == -1){
            break;
        }
        string bits = encodingMap.get(ch);
        for(int i = 0; i < bits.length(); i ++){
            //turning bits in string form to
            //numbers representing bits.
            output.writeBit(bits[i] - '0');
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* cur = encodingTree;
    while(true){
        if(cur->isLeaf()){
            output.put(cur->character);
            cur = encodingTree;
        }
        int bit = input.readBit();
        if(bit == -1){
            break;
        }
        if(bit == 1){
            cur = cur->one;
        }
        else if (bit == 0){
            cur = cur->zero;
        }
    }
}

void compress(istream& input, obitstream& output) {
    Map<int, int> frequencyTable = buildFrequencyTable(input);
    output << frequencyTable;
    //cout << "frequency table: " << frequencyTable;
    HuffmanNode* root = buildEncodingTree(frequencyTable);
    Map<int, string> encodingMap = buildEncodingMap(root);
    freeTree(root);
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> frequencyTable;
    input >> frequencyTable;
    HuffmanNode* root = buildEncodingTree(frequencyTable);
    decodeData(input, root, output);
}

void freeTree(HuffmanNode* node) {
    if(node != NULL){
        if(node->one != NULL){
            if(node->one->isLeaf()){
                HuffmanNode* trash = node->one;
                node->one = NULL;
                delete trash;
            }
            else{
                freeTree(node->one);
            }
        }
        if(node->zero != NULL){
            if(node->zero->isLeaf()){
                HuffmanNode* trash = node->zero;
                node->zero = NULL;
                delete trash;
            }
            else{
                freeTree(node->zero);
            }
        }
    }
    delete node;
}
