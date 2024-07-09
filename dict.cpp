// Do NOT add any other includes
#include "dict.h"
// #include<iostream>
// using namespace std;

Dict::Dict(){
    // Implement your function here   
    root=nullptr; 
}

 void Dict::deletecomplete(Node* node){
     if(node==nullptr){
         return;
     }
     deletecomplete(node->left);
     deletecomplete(node->right);
     delete node;
 }


Dict::~Dict(){
    // Implement your function here    
     deletecomplete(root);
}

Dict::Node* Dict::createnode(string word, int count) {
    Node* newnode = new Node();
    newnode->word = word;
    newnode->count = count;
    newnode->black = false;
    newnode->parent = nullptr;
    newnode->left = nullptr;
    newnode->right = nullptr;
    return newnode;
}

void Dict::leftrot(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }
    temp->left = node;
    node->parent = temp;
}


void Dict::rightrot(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else if (node == node->parent->right) {
        node->parent->right = temp;
    } else {
        node->parent->left = temp;
    }
    temp->right = node;
    node->parent = temp;
}

Dict::Node* Dict::bst(Node* root, Node* newnode) {
    if (newnode->word < root->word) {
        if (root->left == nullptr) {
            root->left = newnode;
            newnode->parent = root;
            return newnode;
        } else {
            return bst(root->left, newnode);
        }
    } else if (newnode->word > root->word) {
        if (root->right == nullptr) {
            root->right = newnode;
            newnode->parent = root;
            return newnode;
        } else {
            return bst(root->right, newnode);
        }
    } else {
        root->count += newnode->count;
        delete newnode; 
        return root;
    }
}

Dict::Node* Dict::insertupd(Node* root, Node* node) {
     if (node->parent == nullptr || !node->parent->black) {
        return root;
    }

    while (node->parent != nullptr && !node->parent->black) {
        Node* grandparent = node->parent->parent;
        Node* parent = node->parent;
        bool parentisleft = (grandparent->left == parent);
        Node* uncle = parentisleft ? grandparent->right : grandparent->left;

        if (uncle != nullptr && !uncle->black) {
            parent->black = true;
            uncle->black = true;
            grandparent->black = false;
            node = grandparent;
        } else {
            if (node == (parentisleft ? parent->right : parent->left)) {
                if (parentisleft) {
                    leftrot(parent);
                } else {
                    rightrot(parent);
                }
                node = parent;
                parent = node->parent;
            }
            parent->black = true;
            grandparent->black = false;
            if (parentisleft) {
                rightrot(grandparent);
            } else {
                leftrot(grandparent);
            }
        }
    }
    root->black = true;

    return root;
}

// bool Dict::is_separator(char c) {
//     string separators = ".,-:!\"'()?—[]“”‘’˙;@";
//     return separators.find(c) != string::npos;
// }

void Dict::insert(Node* &root, string word, int count) {
    Node* newnode = createnode(word, count);

    if (root == nullptr) {
        root = newnode;
        root->black = true;
        return;
    }

    // Perform standard BST insertion
    Node* insertednode = bst(root, newnode);

    // Fix any violations in the Red-Black Tree properties
    insertupd(root, insertednode);

    // Ensure the root is black
    root->black = true;
}


// Dict::Node* Dict::insert(Node* root,string word, int count){
//     if(root==nullptr){
//         return createnode(word, count);
//     }
//     if (word < root->word) {
//         root->left = insert(root->left, word, count);
//         root->left->parent = root;
//     } else if (word > root->word) {
//         root->right = insert(root->right, word, count);
//         root->right->parent = root;
//     } else {
//         root->count += count;
//     }
//     if (!root->black) {
//         if (root->parent == nullptr) {
//             root->black = true;
//         } else if (!root->parent->black) {
//             Node* uncle = (root->parent == root->parent->parent->left) ? root->parent->parent->right : root->parent->parent->left;
//             if (uncle != nullptr && !uncle->black) {
//                 root->parent->black = true;
//                 uncle->black = true;
//                 root->parent->parent->black = false;
//                 root = root->parent->parent;
//             } else {
//                 if (root == root->parent->right && root->parent == root->parent->parent->left) {
//                     leftrot(root->parent);
//                     root = root->left;
//                 } else if (root == root->parent->left && root->parent == root->parent->parent->right) {
//                     rightrot(root->parent);
//                     root = root->right;
//                 }
//                 root->parent->black = true;
//                 root->parent->parent->black = false;
//                 if (root == root->parent->left) {
//                     rightrot(root->parent->parent);
//                 } else {
//                     leftrot(root->parent->parent);
//                 }
//             }
//         }
//     }

//     return root;
// }
// void Dict::insert(Node* root, string word, int count) {
//     Node* newNode = createnode(word, count);

//     if (root == nullptr) {
//         // If the tree is empty, make the new node the root and color it black
//         root = newNode;
//         root->black = true;
//         return;
//     }

//     // Perform standard BST insertion
//     Node* insertedNode = bst(root, newNode);

//     // Fix any violations in the Red-Black Tree properties
//     insertupd(root, insertedNode);

//     // Ensure the root is black
//     root->black = true;
// }

// void Dict::insertupd(Node* root, Node* node) {
//     if (node->parent == nullptr || !node->parent->black) {
//         return;
//     }

//     while (node->parent != nullptr && !node->parent->black) {
//         Node* grandparent = node->parent->parent;
//         Node* parent = node->parent;
//         bool parentisleft = (grandparent->left == parent);
//         Node* uncle = parentisleft ? grandparent->right : grandparent->left;

//         if (uncle != nullptr && !uncle->black) {
//             parent->black = true;
//             uncle->black = true;
//             grandparent->black = false;
//             node = grandparent;
//         } else {
//             if (node == (parentisleft ? parent->right : parent->left)) {
//                 if (parentisleft) {
//                     leftrot(parent);
//                 } else {
//                     rightrot(parent);
//                 }
//                 node = parent;
//                 parent = node->parent;
//             }
//             parent->black = true;
//             grandparent->black = false;
//             if (parentisleft) {
//                 rightrot(grandparent);
//             } else {
//                 leftrot(grandparent);
//             }
//         }
//     }
//     root->black = true;
// }

void Dict::dump(Node* node, std::ofstream& outp) {
    if (node == nullptr) {
        return;
    }

    dump(node->left, outp);
    string lowercaseword = node->word;
    // for (char& c : lowercaseWord) {
    //     if (isupper(c)) {
    //         c = tolower(c);
    //     }
    // }
    outp << lowercaseword << ", " << node->count << std::endl;
    dump(node->right, outp);

}


Dict::Node* Dict::search(Node* root, string word) {
    if (root == nullptr || root->word == word) {
        return root;
    }
    if (word < root->word) {
        return search(root->left, word);
    }
    return search(root->right, word);
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    std::vector<char> separators = {'.', ',', '-', ':', '\'', '"', '!', '(', ')', '?', '[', ']', ';', '@', ' '};
    sentence += ".";
    std::vector<std::string> words;
    std::string word = "";

    for (char c : sentence) {
        bool found = false;
        for (char separator : separators) {
            if (separator == c) {
                found = true;
                break;
            }
        }

        if (found || c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
            }
            word = "";
        } else {
            if (std::isalnum(c)) {
            c= std::tolower(c);
        }
        word+=c;
    }
    }

    for (const std::string w : words) {
        Node* node = search(root, w);
        if (node == nullptr) {
            insert(root, w, 1);
        } else {
            node->count++;
        }
    }
}

int Dict::get_word_count(string word) {
    Node* node = search(root, word);
    if (node != nullptr) {
        return node->count;
    } else {
        return 0;
    }
}
// void Dict::dump(Node* node, ofstream& outp) {
//     if (node == nullptr) {
//         return;
//     }
//     dump(node->left, outp);
//     outp << node->word << ", " << node->count << endl;
//     dump(node->right, outp);
// }


void Dict::dump_dictionary(string filename) {
    ofstream outp(filename);

    if (outp.is_open()) {
        dump(root, outp);
        outp.close();
    }
}



// int main() {
//     Dict dictionary;

//     // Insert sentences into the dictionary
//     dictionary.insert_sentence(1, 1, 1, 1, "This is a sample sentence.");
//     dictionary.insert_sentence(1, 1, 2, 2, "Another sample sentence.");

//     // Dump the dictionary to a file
//     dictionary.dump_dictionary("dict.txt");

//     // Get the word count for a specific word
//     string word_to_find = "sample";
//     int count = dictionary.get_word_count(word_to_find);
//     if (count > 0) {
//         cout << "The word '" << word_to_find << "' appears " << count << " times." << endl;
//     } else {
//         cout << "The word '" << word_to_find << "' was not found in the dictionary." << endl;
//     }

//     // Test inserting more sentences
//     dictionary.insert_sentence(2, 1, 1, 1, "A new sentence for testing.");
//     dictionary.insert_sentence(2, 1, 2, 2, "Testing with more sample words.");

//     // Dump the updated dictionary to a file
//     dictionary.dump_dictionary("updated_dict.txt");

//     // Get the word count for another word
//     string another_word = "testing";
//     int another_count = dictionary.get_word_count(another_word);
//     if (another_count > 0) {
//         cout << "The word '" << another_word << "' appears " << another_count << " times." << endl;
//     } else {
//         cout << "The word '" << another_word << "' was not found in the dictionary." << endl;
//     }

//     return 0;
// }
