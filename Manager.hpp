#include <string>
#include "Node.hpp"
#ifndef MANAGER_H
#define MANAGER_H

class Manager{
    private:
        Node* root;
    public:
        Manager();
        int height(Node* node);
        int balanceFactor(Node* node);
        Node* rotateRight(Node* parent);
        Node* rotateLeft(Node* parent);
        void balancing(int balance, int isbn,  Node* hold, Node* parent, Node* newParent);
        void add(std::string title, std::string authorLast, std::string authorFirst,
            std::string publisher, std::string publicationDate, std::string genre,
            std::string synopsis, int isbn);
        void addOpt();
        void remove(int isbn);
        void removeLeaf(Node* current, Node* parent, int isbn);
        void removeChild(Node* current, Node* parent, int isbn);
        void removeTwoChild(Node* current, Node* parent);
        void removeOpt();
        bool validMod(int isbn);
        Node* modNode(int isbn);
        bool modify(std::string title, std::string authorLast, std::string authorFirst, 
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn);
        int entryIndex();
        int fieldOpt();
        void modifyOpt();
        void inorder();
        void preorder();
        void postorder();
        int lookupType();
        void lookupOpt();
        void menuOpt();
        bool menuChoice();
        void run();
};

#endif 