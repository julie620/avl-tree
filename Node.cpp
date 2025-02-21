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

    Node::Node(std::string title, std::string authorLast, std::string authorFirst, std::string publisher,
        std::string publicationDate, std::string genre, std::string synopsis, int isbn) {
            this->title = title;
            this->authorLast = authorLast;
            this-> authorFirst = authorFirst;
            this->publisher = publisher;
            this->publicationDate = publicationDate;
            this->genre = genre;
            this->synopsis = synopsis;
            this->isbn = isbn;
        }

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
        }

        std::string Node::getTitle() {
            return title;
        }

        std::string Node::getAuthorLast() {
            return authorLast;
        }

        std::string Node::getAuthorFirst() {
            return authorFirst;
        }   

        std::string Node::getPublisher() {
            return publisher;
        }

        std::string Node::getPublicationDate() {
            return publicationDate;
        }

        std::string Node::getGenre() {
            return genre;
        }

        std::string Node::getSynposis() {
            return synopsis;
        }

        int Node::getISBN() {
            return isbn;
        }

        Node* Node::getLeft() {
            return left;
        }

        Node* Node::getRight() {
            return right;
        }

        std::string Node::toString() {
            return "\nTitle: " + title + "\nAuthor Last Name: " + authorLast + "\nAuthor First Name: "
            + authorFirst + "\nPublisher: " + publisher + "\nPublication Date: " + publicationDate +
            "\nGenre: " + genre + "\nSynposis: " + synopsis + "\nISBN: " + std::to_string(isbn);
        }
