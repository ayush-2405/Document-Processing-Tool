// Do NOT add any other includes
#include "search.h"
// #include <bits/stdc++.h> 
// #include "iostream"
// using namespace std;
// #include "Node.cpp"
// #define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

int hash_func(string s){
    return 1;
}

bool Rabin_Karp(string s, string pattern)
{
    int hash_pattern = hash_func(pattern);
    int hash_s = hash_func(s);
    if (hash_s = hash_pattern)
    {
        if (s == pattern)
        {
            return true;
        }
    }
    return false;
}

SearchEngine::SearchEngine()
{
    // Implement your function here
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here

    vector<int> temp = {book_code, page, paragraph, sentence_no};
    for (int i = 0; i < sentence.length(); i++)
    {
        if (isupper(sentence.at(i)))
        {
            sentence.at(i) = tolower(sentence.at(i));
        }
    }
    all_sentences.push_back(sentence);
    location.push_back(temp);
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    // cout<<"In Search"<<endl;
    int p = pattern.size();
    Node *root = new Node();
    root->left = nullptr;
    root->right = nullptr;
    int size = 0;

    Node *temp = root;
    for (int i = 0; i < all_sentences.size(); i++)
    {
        // cout<<i;
        // cout<<"In sentence "<<i+1<<endl;
        string sentence = all_sentences.at(i);

        // cout<<sentence.length()<<" "<<p<<" "<<sentence.length() - p +1 <<endl;
        // cout<<sentence.length()<<" "<<p<<" "<<int(sentence.length()) - int(p)+1 <<endl;
        for (int j = 0; j < int(sentence.length()) - int(p) + 1 ; j++)
        {
            // cout<<"hh";
            // cout<<j;
            // sentence.substr(j, p);
            // cout<<j;
            // cout<<"IN "<<sentence.substr(j, p)<< " ans "<<Rabin_Karp(sentence.substr(j, p), pattern)<<" size "<<size<<endl;
            if (Rabin_Karp(sentence.substr(j, p), pattern))
            {
                if (size == 0)
                {
                    // cout<<"in zero size"<<endl;
                    root->book_code = location.at(i).at(0);
                    root->page = location.at(i).at(1);
                    root->paragraph = location.at(i).at(2);
                    root->sentence_no = location.at(i).at(3);
                    root->offset = j;
                    size++;
                }
                else
                {
                    Node *n = new Node(location.at(i).at(0), location.at(i).at(1), location.at(i).at(2), location.at(i).at(3), j);
                    temp->right = n;
                    n->left = temp;
                    n->right = nullptr;
                    temp = temp->right;
                    size++;
                }
            }
        }
        // cout<<root->paragraph;
    }
    //  cout<<root->paragraph;
    // cout<<"Out Search"<<endl;
    n_matches = size;
    return root;
}

// int main(){
//     int n_matches=0;
//    SearchEngine s;
// //    cout<<Rabin_Karp("how","how");
//    s.insert_sentence(1,1,1,1,"Then he");
// //    cout<<s.all_sentences.at(0);
// //    cout<<s.location.at(0).at(0);
// //    cout<<s.location.at(0).at(1);
// //    cout<<s.location.at(0).at(2);
// //    cout<<s.location.at(0).at(3);
//    Node* n= s.search("talk with him",n_matches);
//    cout<< "done" ;
//     return 0;
// }



// int main() {
//     std::ifstream inputFile(FILENAME);

//     if (!inputFile.is_open()) {
//         std::cerr << "Error: Unable to open the input file." << std::endl;
//         return 1;
//     }

//     std::string tuple;
//     std::string sentence;

//     // Dict d;
//     SearchEngine d ;

//     while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
//         // Get a line in the sentence
//         tuple += ')';

//         std::vector<int> metadata;    
//         std::istringstream iss(tuple);

//         // Temporary variables for parsing
//         std::string token;

//         // Ignore the first character (the opening parenthesis)
//         iss.ignore(1);

//         // Parse and convert the elements to integers
//         while (std::getline(iss, token, ',')) {
//             // Trim leading and trailing white spaces
//             size_t start = token.find_first_not_of(" ");
//             size_t end = token.find_last_not_of(" ");
//             if (start != std::string::npos && end != std::string::npos) {
//                 token = token.substr(start, end - start + 1);
//             }
            
//             // Check if the element is a number or a string
//             if (token[0] == '\'') {
//                 // Remove the single quotes and convert to integer
//                 int num = std::stoi(token.substr(1, token.length() - 2));
//                 metadata.push_back(num);
//             } else {
//                 // Convert the element to integer
//                 int num = std::stoi(token);
//                 metadata.push_back(num);
//             }
//         }

//         // Now we have the string in sentence
//         // And the other info in metadata
//         // Add to the dictionary

//         // Insert in the dictionary
//         d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
//     }

//     inputFile.close();

//     int s=0;
//     d.search("talk with him",s);

// std::cout<<"done";
//     // // Get the counts of some words
//     // std::ifstream dict("counts.txt"); 
//     // if (!dict.is_open()) {
//     //     std::cerr << "Error: Unable to open the file." << std::endl;
//     //     return 1;
//     // }

//     // bool passed = true;
//     // std::string l;
//     // while (std::getline(dict, l)) {
//     //     std::istringstream iss(l);
//     //     std::string key;
//     //     int value;

//     //     if (std::getline(iss, key, ',') && iss >> value) {
//     //         if(d.get_word_count(key) != value) {
//     //             cout << "Expected count for word " << key << ": " << value << ", received: " << d.get_word_count(key) << endl;
//     //             passed = false; 
//     //             break;
//     //         }
//     //     }
//     // }

//     // if (passed) {
//     //     cout << "Passed" << endl;
//     // } else {
//     //     cout << "Failed" << endl;
//     // }

//     // dict.close();

//     return 0;
// }
