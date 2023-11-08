#include <iostream>
#include "AVL.h"
#include <regex>
#include <sstream>
#include <algorithm>
int main() {
    AVLTree tree;
    int commandCount = 0;
    cin >> commandCount;
    cin.ignore();
    for (int i = 0; i < commandCount; i++) {
        string command;
        getline(cin, command);
        if (command.find("insert") == 0) {
            string name, ufid;
            size_t firstQuote = command.find_first_of('"');
            size_t lastQuote = command.find_last_of('"');
            name = command.substr(firstQuote + 1, lastQuote - firstQuote - 1);
            ufid = command.substr(lastQuote + 2);
            // get rid of leading and trailing space
            name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
            ufid.erase(std::remove(ufid.begin(), ufid.end(), ' '), ufid.end());
            tree.Insert(name,ufid);
        }
        // this is before remove alone bc if not all the inorder commands go to remove (yes, I learned this the hard way)
        else if (command.find("removeInorder") == 0) {
            // get the n
            string query = command.substr(14);
            int removeN = stoi(query);
            tree.removeInorderN(removeN);
        }
        else if (command.find("remove") == 0) {
            // get the ufid after remove
            string ufid = command.substr(7);
            tree.Remove(ufid);
        } else if (command.find("search") == 0) {
            //get what is after the word search
            string query = command.substr(7);
            // check if in quotes
            if (query.front() == '"' && query.back() == '"') {
                // get rid of quotes
                query = query.substr(1, query.length() - 2);
                tree.SearchP2(query);
            } else {
                // assume it's ufid if it isnt name
                if (query.length() == 8 && regex_match(query, regex("[0-9]{8}"))) {
                    tree.Search(query);
                }
                else {
                    //invalid sitches in either case
                    cout << "unsuccessful" << endl;
                }
            }
        }
        // the prints done w j command bc they all start w print so too confusing
        else if (command == "printInorder") {
            tree.PrintInorder();
        } else if (command == "printPreorder") {
            tree.PrintPreorder();
        } else if (command == "printPostorder") {
            tree.PrintPostorder();
        } else if (command == "printLevelCount") {
            tree.printLevelCount();
        }
    }

    return 0;}

    //8
    //insert "Brandon" 45679999
    //insert "Brian" 35459999
    //insert "Briana" 87879999
    //insert "Bella" 95469999
    //printInorder
    //remove 45679999
    //removeInorder 2
    //printInorder

    //9
//insert "Caroline" 50005000
//insert "Cory" 35354334
//insert "Cecilia" 76543210
//insert "Carla" 56567342
//insert "Cody" 83711221
//insert "Chris" 17449900
//printInorder
//printPreorder
//printPostorder
