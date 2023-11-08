#pragma once
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    //follow similar structure to setup in slides, except w name and ufid and I'm calling it node bc that means less typing everytime
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;
    Node(const string& name, const string& ufid)
            : name(name), ufid(ufid), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node *root;

    int getHeight(Node *node) {
        return (node != nullptr) ? node->height : 0;
    };

    // find balance factor
    int getBalanceFactor(Node *node) {
        // where I learned what ? is used for https://www.tutorialspoint.com/cplusplus/cpp_conditional_operator.htm
        return (node != nullptr) ? getHeight(node->left) - getHeight(node->right) : 0;
    };

    // all these coming functions for basic turns are from my understanding that I got in the slides, so credit to Aman and the slides.
    // rotate right function
    Node *rotateRight(Node *treenode) {
        Node *x = treenode->left;
        Node *T2 = x->right;
        x->right = treenode;
        treenode->left = T2;
        treenode->height = 1 + max(getHeight(treenode->left), getHeight(treenode->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    };

    // rotate left function
    Node *rotateLeft(Node *treenode) {
        Node *y = treenode->right;
        Node *T2 = y->left;
        y->left = treenode;
        treenode->right = T2;
        treenode->height = 1 + max(getHeight(treenode->left), getHeight(treenode->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    // balance the tree
    Node *balance(Node *node) {
        int balanceFactor = getBalanceFactor(node);
        // if it goes left heavy
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        // if it goes right heavy
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    // now create bool to check if it is an id
    bool containsID(Node *node, const string &ufid) {
        if (node == nullptr) {
            return false;
        }
        if (ufid < node->ufid) {
            return containsID(node->left, ufid);
        } else if (ufid > node->ufid) {
            return containsID(node->right, ufid);
        } else {
            return true;
        }
    }

public:
    // public functions are the ones we will directly call in main
    AVLTree() : root(nullptr) {}

    // check if the name and ufid are valid (aka have right names and chars and length etc yktv)
    bool isValidNameAndUFID(const string &name, const string &ufid) {
        for (char c: name) {
            if (!(isalpha(c) || c == ' ')) {
                // an invalid char was found in name...
                return false;
            }
        }
        if (ufid.length() != 8) {
            // ufid is the wrong length...
            return false;
        }
        for (char c: ufid) {
            if (!isdigit(c)) {
                // ufid has a letter or smth not a digit in there
                return false;
            }
        }
        // both are perf y
        return true;
    }

    // the function that will insert the node
    Node *insert(Node *node, const string &name, const string &ufid) {
        if (node == nullptr) {
            return new Node(name, ufid);
        }
        if (ufid < node->ufid) {
            node->left = insert(node->left, name, ufid);
        } else if (ufid > node->ufid) {
            node->right = insert(node->right, name, ufid);
        } else {
            // if it gets here, means we at a duplicate and dont add it baby
            return node;
        }
        // add new node to the height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        // check balance factor and if needed move tree around to balance
        int balanceFactor = getBalanceFactor(node);
        // left heavy sitch
        if (balanceFactor > 1) {
            if (ufid < node->left->ufid) {
                // left-left
                return rotateRight(node);
            } else {
                // left-right
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        // right heavy sitch
        if (balanceFactor < -1) {
            if (ufid > node->right->ufid) {
                // right-right
                return rotateLeft(node);
            } else {
                // right-left
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    // this is the insert we call in the main that will take in the name nad ufid
    void Insert(const string &name, const string &ufid) {
        // check if they are valid
        if (isValidNameAndUFID(name, ufid)) {
            if (!containsID(this->root, ufid)) {
                // if valid and not duplicate, use the other real insert function to insert the node
                this->root = insert(this->root, name, ufid);
                cout << "successful" << endl;
            } else {
                // duplicate
                cout << "unsuccessful" << endl;
            }
        } else {
            // invalid id or name
            cout << "unsuccessful" << endl;
        }
    }

    // now we do the same type of sitch but for removing nodes
    Node *remove(Node *node, const string &ufid) {
        if (node == nullptr) {
            //print unsuccessful if no ufid
            cout << "unsuccessful" << endl;
            return node;
        }
        if (ufid < node->ufid) {
            node->left = remove(node->left, ufid);
        } else if (ufid > node->ufid) {
            node->right = remove(node->right, ufid);
        } else {
            // ufid is found
            // node w 1 or no kids
            if (node->left == nullptr || node->right == nullptr) {
                Node *temp = node->left ? node->left : node->right;
                // no kid
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    // one kid
                    *node = *temp; // copy kid node bc we're deleting its mommy
                }
                // delete old node
                delete temp;
            } else {
                // node w 2 kids case
                Node *current = node->right;
                while (current && current->left) {
                    current = current->left;
                }
                Node *temp = current;
                // copy inorder successor
                node->ufid = temp->ufid;
                node->name = temp->name;
                // delete inorder successor
                node->right = remove(node->right, temp->ufid);
            }
            // if tree had only one node, return
            if (node == nullptr) {
                return node;
            }
        }
        // update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        // balance node
        return balance(node);
    };

    //second remove that we call in main
    void Remove(const string &ufid) {
        if (containsID(root, ufid)) {
            root = remove(root, ufid);
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // ufid search function (sorry I called it search I first thought there was only one search needed)
    Node *search(Node *node, const string &ufid) {
        if (node == nullptr || node->ufid == ufid) {
            return node;
        }
        if (ufid < node->ufid) {
            return search(node->left, ufid);
        } else {
            return search(node->right, ufid);
        }
    }

    bool Search(const string &ufid) {
        // look for the ufid
        Node *result = search(root, ufid);
        if (result != nullptr) {
            // cout name if there
            cout << result->name << endl;
            return true;
        } else {
            // if not there it is...
            cout << "unsuccessful" << endl;
            return false;
        }
    }

    // second search function for the name
    void searchp2(Node *node, const string &name, bool &found) {
        // load el node (i rhymned hehe)
        if (node == nullptr) {
            return;
        }
        if (node->name == name) {
            cout << node->ufid << endl;
            found = true;
        }
        //recursion recursion
        searchp2(node->left, name, found);
        searchp2(node->right, name, found);
    };

    void SearchP2(const string &name) {
        // set bool automatic to false and change only if name is found
        bool found = false;
        searchp2(root, name, found);
        if (!found) {
            cout << "unsuccessful" << endl;
        }
    }

    // now do the three print functions in the same type of way
    void printinorder(Node *node, bool &first) {
        if (node == nullptr) {
            return;
        }
        printinorder(node->left, first);
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        cout << node->name;
        printinorder(node->right, first);
    };

    void PrintInorder() {
        // set to true automatically
        bool first = true;
        printinorder(root, first);
        cout << endl;
    }

    void printPreorder(Node *node, bool &first) {
        if (node == nullptr) {
            return;
        }
        if (!first) {
            cout << ", ";
        } else {
            first = false;
        }
        cout << node->name;
        printPreorder(node->left, first);
        printPreorder(node->right, first);
    }

    void PrintPreorder() {
        bool first = true;
        printPreorder(root, first);
        cout << endl;
    }

    void printPostorder(Node *node, bool &first) {
        if (node == nullptr) {
            return;
        }
        printPostorder(node->left, first);
        printPostorder(node->right, first);
        if (!first) {
            cout << ", ";
        } else {
            first = false;
        }
        cout << node->name;
    };

    void PrintPostorder() {
        bool first = true;
        printPostorder(root, first);
        cout << endl;
    }

    // level count printer
    int printLevelCount() {
        cout << countcurlevels(root) << endl;
    }
    // level count finder
    int countcurlevels(Node *node) {
        // if list is empty obvi level count is 0
        if (node == nullptr) {
            return 0;
        }
        // count levels on left and right and then add one to it because the root
        int leftLevels = countcurlevels(node->left);
        int rightLevels = countcurlevels(node->right);
        return max(leftLevels, rightLevels) + 1;
    };

    // remove in order function. def hardest one we've had to do lol
    void removeInorderN(int n) {
        int count = 0;
        bool removed = false;
        root = removeInorderN(root, n, count, removed);
        if (removed) {
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    Node* removeInorderN(Node* node, int n, int& count, bool& removed) {
        if (node == nullptr) {
            return nullptr;
        }
        // Recursively traverse the left subtree
        node->left = removeInorderN(node->left, n, count, removed);
        if (removed) {
            return node;
        }
        // if current node is the nth remove it
        if (count == n) {
            removed = true;
            return removeNode(node);
        }
        // add to count after the left subtree
        count++;
        // traverse the right subtree
        node->right = removeInorderN(node->right, n, count, removed);
        return node;
    }
    Node* removeNode(Node* node) {
        // had to write this j for this function above it bc the og remove cant do it;
        if (node == nullptr) {
            return nullptr;
        }
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* minRight = findMin(node->right);
        node->ufid = minRight->ufid;
        node->name = minRight->name;
        node->right = removeNode(minRight);
        return node;
    }

    Node* findMin(Node* node) {
        // same w this one lol.
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};