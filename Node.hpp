#include <string>

#ifndef NODE_H
#define NODE_H

 class Node {
    private: 
        std::string title;
        std::string authorLast;
        std::string authorFirst;
        std::string publisher;
        std::string publicationDate;
        std::string genre;
        std::string synopsis;
        int isbn;
    protected:
        Node* left;
        Node* right;
        int height;
        friend class Manager;

    public:

        Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
            std::string publicationDate, std::string genre, std::string synopsis, int isbn, 
            Node* left, Node* right);

        int getISBN();
        std::string toString();
};

#endif