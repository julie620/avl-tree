/*
 *Author: Juliana Serrano
 * Last Modified: 02/25/2025
 * Lab 5: AVL Tree
 * Node.cpp defines constructors of Node and method to return information as a string
*/

#include <string>
#include "Node.hpp"

        std::string title;
        std::string authorLast;
        std::string authorFirst;
        std::string publisher;
        std::string publicationDate;
        std::string genre;
        std::string synopsis;
        int isbn;

        Node* left;
        Node* right;
        int height;


    Node::Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
        std::string publicationDate, std::string genre, std::string synopsis, int isbn, Node* left, Node* right) {
        this->title = title;
        this->authorLast = authorLast;
        this-> authorFirst = authorFirst;
        this->publisher = publisher;
        this->publicationDate = publicationDate;
        this->genre = genre;
        this->synopsis = synopsis;
        this->isbn = isbn;
        this->left = left;
        this->right = right;
        height = 1;
    }

    int Node::getISBN() {
        return isbn;
    }

    std::string Node::toString() {
        return "\nTitle: " + title + "\nAuthor Last Name: " + authorLast + "\nAuthor First Name: "
        + authorFirst + "\nPublisher: " + publisher + "\nPublication Date: " + publicationDate +
        "\nGenre: " + genre + "\nSynposis: " + synopsis + "\nISBN: " + std::to_string(isbn);
    }
