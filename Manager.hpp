#include <string>
#include "Node.hpp"
#ifndef MANAGER_H
#define MANAGER_H

class Manager{
    private:
        Node* root;
    public:
        Manager();
        bool add(std::string title, std::string authorLast, std::string authorFirst,
            std::string publisher, std::string publicationDate, std::string genre,
            std::string synopsis, int isbn);
        bool remove(int isbn);
        void removeRootTwo(Node* current);
        void removeLeaf(Node* current, Node* parent, int isbn);
        void removeChildR(Node* current, Node* parent, int isbn);
        void removeChildL(Node* current, Node* parent, int isbn);
        void removeTwoChild(Node* current, Node* parent);
        bool validMod(int isbn);
        Node* modNode(int isbn);
        bool modify(std::string title, std::string authorLast, std::string authorFirst, 
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn);
        Node* traversal();
        void inorder();
        void preorder();
        void postorder();
        std::string title(int isbn);
        std::string authorLast(int isbn);
        std::string  authorFirst(int isbn);
        std::string publisher(int isbn);
        std::string publicationDate(int isbn);
        std::string genre(int isbn);
        std::string synopsis(int isbn);
};

#endif 