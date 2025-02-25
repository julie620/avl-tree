/*
 * Author: Juliana Serrano
 * Last Modified: 02/25/2025
 * Lab 5: AVL Tree
 * Manager.cpp defines functions to add, remove, modify, and traverse through AVL Tree
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "Manager.hpp"

    Node* root;

    Manager::Manager() {
        root = nullptr;
    } 
    
    int Manager::height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int Manager::balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }  
        return height(node->left) - height (node->right);
    }

    Node* Manager::rotateRight(Node* parent) {
        Node* x = parent->left;
        Node* temp = x->right;

        x->right = parent;
        parent->left = temp;

        parent->height = std::max(height(parent->left), height(parent->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* Manager::rotateLeft(Node* parent) {
        Node* y = parent->right;
        Node* temp = y->left;

        y->left = parent;
        parent->right = temp;

        parent->height = std::max(height(parent->left), height(parent->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // determines "out of balance" case and peforms necessary rotations
    void Manager::balancing(int balance, int isbn, Node* hold, Node* parent, Node* newParent) {
        if(balance > 1 && isbn < parent->isbn) { //LL case and rotation
            if (hold == root) {
                root = rotateRight(hold);
            } else {
                if (isbn > root->isbn) {
                    newParent->right = rotateRight(hold);
                } else {
                    newParent->left = rotateRight(hold);
                }
            }
        } else if (balance > 1 && isbn > parent->isbn) { // LR case and rotation
            hold->left = rotateLeft(hold->left);
            if (hold == root) {
                root = rotateRight(hold);
            } else {
                if (isbn > root->isbn) {
                    newParent->right = rotateRight(hold);
                } else {
                    newParent->left = rotateRight(hold);
                }
            }
        } else if (balance < -1 && isbn > parent->isbn) { // RR case and rotation
            if (hold == root) {
                root = rotateLeft(hold);
            } else {
                if (isbn < root->isbn) {
                    newParent->left = rotateLeft(hold);
                } else {
                    newParent->right = rotateLeft(hold);
                }
            }
        } else if (balance < -1 && isbn < parent->isbn) { // RL case and rotation
            hold->right = rotateRight(hold->right);
            if (hold == root) {
                root = rotateLeft(hold);
            } else {
                if (isbn < root->isbn) {
                    newParent->left = rotateLeft(hold);
                } else {
                    newParent->right = rotateLeft(hold);
                }
            }
        }
    }
    
    void Manager::add(std::string title, std::string authorLast, std::string authorFirst,
        std::string publisher, std::string publicationDate, std::string genre, 
        std::string synopsis, int isbn) {
        Node* temp = new Node(title, authorLast, authorFirst, publisher, publicationDate, genre,
            synopsis, isbn, nullptr, nullptr);
        if (root == nullptr) {
            root = temp;
            return;
        } else {
            Node* current = root;
            Node* parent = root;
            std::stack<Node*> ancestors; // tracks and stores nodes that may be affected by insert
            while (current != nullptr) { // finds parent of node to be added
                if (isbn < current->getISBN() || isbn > current->getISBN()){
                    parent = current;
                    current = (isbn < current->getISBN()) ? current->left : current->right;
                    if (current!= temp) {
                        ancestors.push(parent);
                    }
                } else {
                    std::cout << "ERROR" << std::endl;
                    return;
                }
            }
            if (isbn < parent->getISBN()) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
            Node* hold = nullptr;
            while(!ancestors.empty()) { // adjust height and balance nodes
                hold = ancestors.top();
                hold->height = 1 + std::max(height(hold->left), height(hold->right));
                ancestors.pop();
                int balance = balanceFactor(hold);
                Node* newParent = root;
                if (!ancestors.empty()) {
                    newParent = ancestors.top();
                }
                balancing(balance, isbn, hold, parent, newParent);
            }
        }
    }   

    void Manager::addOpt() {
        std::string title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis;
        int isbn;
        std::cout << "Title: " << std::endl;
        std::cin >> title;
        std::cout << "Author Last Name: " << std::endl;
        std::cin >> authorLast;
        std::cout << "Author First Name: " << std::endl;
        std::cin >> authorFirst;
        std::cout << "Publisher: " << std::endl;
        std::cin >> publisher;
        std::cout << "Publication Date: " << std::endl;
        std::cin >> publicationDate;
        std::cout << "Genre: " << std::endl;
        std::cin >> genre;
        std::cout << "Synopsis: " << std::endl;
        std::cin >> synopsis;
        std::cout << "ISBN: " << std::endl;
        std::cin >> isbn;
        add(title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis, isbn);
    }

    void Manager::remove(int isbn) {
        Node* current = root;
        Node* parent = nullptr;
        std::stack<Node*> ancestors; // tracks and stores nodes that may be affected by removal
        while(current != nullptr && current->getISBN() != isbn){ // sets current to node that is to be removed
            if (isbn < current->getISBN()){
                parent = current;
                current = current->left;
                ancestors.push(parent);
            } else if (isbn > current->getISBN()) {
                parent = current;
                current = current->right;
                ancestors.push(parent);
            } else {
                std::cout << "ERROR" << std::endl;
                return;
            }
        }
        if (current->left == nullptr && current->right == nullptr) { // leaf removal
            removeLeaf(current, parent, isbn);
        } else if (current->left == nullptr || current->right == nullptr) { // removal of node with a singular child
            removeChild(current, parent, isbn);
        } else { // removal of node with two children
            removeTwoChild(current, parent);
        }
        Node* hold = nullptr;
        while(!ancestors.empty()) { // adjust height and balance nodes
            hold = ancestors.top();
            hold->height = 1 + std::max(height(hold->left), height(hold->right));
            ancestors.pop();
            int balance = balanceFactor(hold);
            Node* newParent = root;
            if (!ancestors.empty()) {
                newParent = ancestors.top();
            }
            balancing(balance, isbn, hold, parent, newParent);
        }
    }

    void Manager::removeLeaf(Node* current, Node* parent, int isbn) {
        if (current == root) {
            root = nullptr;
        } else if (parent->left == nullptr|| parent->right  == nullptr) {
            if (parent->right == nullptr) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else {
            if (parent->left->getISBN() == isbn) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
    }

    void Manager::removeChild(Node* current, Node* parent, int isbn){
        if (current == root) {
            root = (current->left == nullptr) ? root->right : root->left;
        } else if (isbn < parent->getISBN()) {
            parent->left = (current->left == nullptr) ? current->right : current->left;
        } else {
            parent->right = (current->left == nullptr) ? current->right : current->left;
        }
    }
        
    void Manager::removeTwoChild(Node* current, Node* parent) {
        Node* replacement = current->right;
        Node* parent2 = current;
        while (replacement->left != nullptr) {
            parent2 = replacement;
            replacement = replacement->left;
        }
        if (parent2->left == nullptr|| parent2->right  == nullptr) {
            if (parent2->right == nullptr) {
                parent2->left = nullptr;
            } else {
                parent2->right = nullptr;
            }
        } else {
            if (parent2->left->getISBN() == replacement->isbn) {
                parent2->left = nullptr;
            } else {
                parent2->right = nullptr;
            }
        }
        if (current->right != nullptr || current->left != nullptr) {
            if (current->right != nullptr) {
                replacement->right = current->right;
            }
            if (current->left != nullptr) {
                replacement->left = current->left;
            }
        }
        if (parent == nullptr) {
            root = replacement;
        } else {
            parent->right = replacement;
        }

    }

    void Manager::removeOpt() {
        std::cout << "Which entry would you like to delete (Enter ISBN)?";
        int entryNum;
        std::cin >> entryNum;
        remove(entryNum);
    }

    // checks if the node requested for modification is valid/exists
    bool Manager::validMod(int isbn) {
        Node* current = root;
        while (isbn != current->getISBN()) {
            if (isbn < current->getISBN()) {
                current = current->left;
            } else if (isbn > current->getISBN()) {
                current = current->right;
            } else {
                return false;
            }
        }
        return true;
    }

    // returns the node to be modified
    Node* Manager::modNode(int isbn) {
        Node* current = root;
        while (isbn != current->getISBN()) {
            if (isbn < current->getISBN()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return current;
    }

    bool Manager::modify(std::string title, std::string authorLast, std::string authorFirst, 
        std::string publisher, std::string publicationDate, std::string genre, 
        std::string synopsis, int isbn) {
        if (validMod(isbn) != true) {
            std::cout << "false" << std::endl;
            return false;
        }
        remove(isbn);
        add(title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis, 
            isbn);
        return true;
    }

    int Manager::entryIndex() {
        std::cout << "Which entry would you like to modify (Enter ISBN)?";
        int entryNum;
        std::cin >> entryNum;
        return entryNum;
    }

    int Manager::fieldOpt(){
        std::cout << "Which field would you like to modify?" << std::endl;
        std::cout << "1) Title" << std::endl;
        std::cout << "2) Author Last Name" << std::endl;
        std::cout << "3) Author First Name" << std::endl;
        std::cout << "4) Publisher" << std::endl;
        std::cout << "5) Publication Date" << std::endl;
        std::cout << "6) Genre" << std::endl;
        std::cout << "7) Synopsis" << std::endl;
        int field;
        std::cin >> field;
        return field;
    }

    void Manager::modifyOpt() {
        int isbn = entryIndex();
        int field = fieldOpt();
        std::cout << "Enter new information: " << std::endl;
        Node* current = modNode(isbn);
        std::string modField;
        std::cin >> modField;
        switch(field) {
            case 1: // TITLE
                modify(modField, current->authorLast, current->authorFirst, current->publisher,
                    current->publicationDate, current->genre, current->synopsis, isbn);
                break;
            case 2: // AUTHOR LAST
                modify(current->title, modField, current->authorFirst, current->publisher,
                    current->publicationDate, current->genre, current->synopsis, isbn);
                break;
            case 3: // AUTHOR FIRST
                modify(current->title, current->authorLast, modField, current->publisher,
                    current->publicationDate, current->genre, current->synopsis, isbn);
                break;
            case 4: // PUBLISHER
                modify(current->title, current->authorLast, current->authorFirst, modField,
                    current->publicationDate, current->genre, current->synopsis, isbn);
                break;
            case 5: // PUBLICATION DATE
                modify(current->title, current->authorLast, current->authorFirst, current->publisher,
                    modField, current->genre, current->synopsis, isbn);
                break;
            case 6: // GENRE
                modify(current->title, current->authorLast, current->authorFirst, current->publisher,
                    current->publicationDate, modField, current->synopsis, isbn);
                break;
            case 7: // SYNOPSIS
                modify(current->title, current->authorLast, current->authorFirst, current->publisher,
                    current->publicationDate, current->genre, modField, isbn);
                break;
        }
    }

    // traverses nodes from left subtree to root to right subtree
    void Manager::inorder() {
        std::vector<std::string> list;
        std::stack<Node*> nodes;
        
        Node* current = root;
        if (current == nullptr) {
            return;
        }
        while (current != nullptr || !nodes.empty()) {
            while (current != nullptr) {
                nodes.push(current);
                current = current->left;
            }
            current = nodes.top();
            nodes.pop();
            list.push_back(current->toString());
            current = current->right;
        }
        for (int i = 0; i < list.size(); i ++) {
            std::cout << list[i] << std::endl;
        }
    }

    // traverses nodes from root to left subtree to right subtree
    void Manager::preorder() {
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> nodes;
        nodes.push(root);
        while (nodes.empty() == false) {
            Node* temp = nodes.top();
            std::cout << temp->toString() << std::endl;
            nodes.pop();
            if (temp->right) {
                nodes.push(temp->right);
            }
            if (temp->left) {
                nodes.push(temp->left);
            }
        }
    }

    // traverses nodes from left to subtree to right subtree to root
    void Manager::postorder() {
        std::vector<std::string> list;
        std::stack<Node*> nodes;
        nodes.push(root);
        Node* previous = nullptr;
        while(!nodes.empty()) {
            Node* current = nodes.top();
            if (previous == nullptr || previous->left == current || 
                previous->right == current) {
                if (current->left) {
                    nodes.push(current->left);
                } else if (current->right) {
                    nodes.push(current->right);
                } else {
                    nodes.pop();
                    list.push_back(current->toString());
                }
            } else if (current->left == previous) {
                if (current->right) {
                    nodes.push(current->right);
                } else {
                    nodes.pop();
                    list.push_back(current->toString());
                }
            } else if (current->right == previous) {
                nodes.pop();
                list.push_back(current->toString());
            }
            previous = current;
        }
        for (int i = 0; i < list.size(); i ++) {
            std::cout << list[i] << std::endl;
        }
    }

    int Manager::lookupType() {
        std::cout << "What type of lookup would you like?" << std::endl;
        std::cout << "1) Inorder" << std::endl;
        std::cout << "2) Preorder" << std::endl;
        std::cout << "3) Postorder" << std::endl;
        int type;
        std::cin >> type;
        return type;
    }

    void Manager::lookupOpt() {
        int type = lookupType();
        switch(type) {
            case 1:
                inorder();
                break;
            case 2:
                preorder();
                break;
            case 3:
                postorder();
                break;
        }
    }

    void Manager::menuOpt() {
        std::cout << "\nChoose an option: " << std::endl;
        std::cout << "1) Add Entry" << std::endl;
        std::cout << "2) Delete Entry" << std::endl;
        std::cout << "3) Modify Entry" << std::endl;
        std::cout << "4) Lookup" << std::endl;
        std::cout << "5) Exit" << std::endl;
    }

    bool Manager::menuChoice() {
        menuOpt();
        int response;
        std::cin >> response;
        switch (response) {
            case 1:
                addOpt();
                break;
            case 2:
                removeOpt();
                break;
            case 3:
                modifyOpt();
                break;
            case 4:
                lookupOpt();
                break;
            case 5:
                return false;
            default:
                std::cout << "That is not a valid option. Try again." << std::endl;
        }
        return true;
    }

    // will keep tree open for modification until the user quits/exits
    void Manager::run() {
        bool editing = true;
        do {
            editing = menuChoice();
        }
        while(editing);
    }