// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    struct Node {
        string word;
        int count;
        bool black;  // true for black, false for red
        Node* parent;
        Node* left;
        Node* right;
    };

    Node* root;

    void deletecomplete(Node* node);
    Node* createnode(string word, int count);
    void leftrot(Node* node);
    void rightrot(Node* node);
    Node* insertupd(Node* root, Node* node);
    Node* bst(Node* root, Node* newNode);
    void insert(Node* &root, string word, int count);

    void dump(Node* node, ofstream& outp);
    Node* search(Node* root, string word);

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
// private:
//     Node* root;
//     void deletecomplete(Node* node);
};