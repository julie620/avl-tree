#include <string>
#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Manager.hpp"

    void menuOpt() {
        std::cout << "Choose an option: " << std::endl;
        std::cout << "1) Add Entry" << std::endl;
        std::cout << "2) Delete Entry" << std::endl;
        std::cout << "3) Modify Entry" << std::endl;
        std::cout << "4) Lookup" << std::endl;
        std::cout << "5) Exit" << std::endl;
    }

    void addOpt(Manager* myLibrary) {
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
        myLibrary->add(title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis,
            isbn);
    }

    void removeOpt(Manager* myLibrary) {
        std::cout << "Which entry would you like to delete (Enter ISBN)?";
        int entryNum;
        std::cin >> entryNum;
        myLibrary->remove(entryNum);
    }

    int entryIndex(Manager* mylibrary) {
        std::cout << "Which entry would you like to modify (Enter ISBN)?";
        int entryNum;
        std::cin >> entryNum;
        return entryNum;
    }

    int fieldOpt(Manager* myLibrary) {
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


    void modTitle(Manager* myLibrary, int isbn) {
        std::string newTitle;
        std::cin >> newTitle;
        myLibrary->modify(newTitle, myLibrary->authorLast(isbn), myLibrary->authorFirst(isbn), 
            myLibrary->publisher(isbn), myLibrary->publicationDate(isbn), myLibrary->genre(isbn), 
            myLibrary->synopsis(isbn), isbn);
    }

    void modAuthorLast(Manager* myLibrary, int isbn) {
        std::string newAuthorLast;
        std::cin >> newAuthorLast;
        myLibrary->modify(myLibrary->title(isbn), newAuthorLast, myLibrary->authorFirst(isbn), 
            myLibrary->publisher(isbn), myLibrary->publicationDate(isbn), myLibrary->genre(isbn), 
            myLibrary->synopsis(isbn), isbn);
    }

    void modAuthorFirst(Manager* myLibrary, int isbn) {
        std::string newAuthorFirst;
        std::cin >> newAuthorFirst;
        myLibrary->modify(myLibrary->title(isbn), myLibrary->authorLast(isbn), newAuthorFirst, 
            myLibrary->publisher(isbn), myLibrary->publicationDate(isbn), myLibrary->genre(isbn), 
            myLibrary->synopsis(isbn), isbn);
    }

    void modPublisher(Manager* myLibrary, int isbn) {
        std::string newPublisher;
        std::cin >> newPublisher;
        myLibrary->modify(myLibrary->title(isbn), myLibrary->authorLast(isbn), 
            myLibrary->authorFirst(isbn), newPublisher, myLibrary->publicationDate(isbn), 
            myLibrary->genre(isbn), myLibrary->synopsis(isbn), isbn);
    }

    void modPublicationDate(Manager* myLibrary, int isbn) {
        std::string newPublicationDate;
        std::cin >> newPublicationDate;
        myLibrary->modify(myLibrary->title(isbn), myLibrary->authorLast(isbn), 
            myLibrary->authorFirst(isbn), myLibrary->publisher(isbn), newPublicationDate, 
            myLibrary->genre(isbn), myLibrary->synopsis(isbn), isbn);
    }

    void modGenre(Manager* myLibrary, int isbn) {
        std::string newGenre;
        std::cin >> newGenre;
        myLibrary->modify(myLibrary->title(isbn), myLibrary->authorLast(isbn), 
            myLibrary->authorFirst(isbn), myLibrary->publisher(isbn), 
            myLibrary->publicationDate(isbn), newGenre, myLibrary->synopsis(isbn), isbn);
    }

    void modSynopsis(Manager* myLibrary, int isbn) {
        std::string newSynopsis;
        std::cin >> newSynopsis;
        myLibrary->modify(myLibrary->title(isbn), myLibrary->authorLast(isbn), 
            myLibrary->authorFirst(isbn), myLibrary->publisher(isbn), 
            myLibrary->publicationDate(isbn), myLibrary->genre(isbn), newSynopsis, isbn);
    }

    void modifyOpt(Manager* myLibrary) {
        int isbn = entryIndex(myLibrary);
        int field = fieldOpt(myLibrary);
        std::cout << "Enter new information: " << std::endl;
        switch(field) {
            case 1:
                modTitle(myLibrary, isbn);
                break;
            case 2:
                modAuthorLast(myLibrary, isbn);
                break;
            case 3:
                modAuthorFirst(myLibrary, isbn);
                break;
            case 4:
                modPublisher(myLibrary, isbn);
                break;
            case 5:
                modPublicationDate(myLibrary, isbn);
                break;
            case 6:
                modGenre(myLibrary, isbn);
                break;
            case 7:
                modSynopsis(myLibrary, isbn);
                break;
        }
    }

    int lookupType(Manager* myLibrary) {
        std::cout << "What type of lookup would you like?" << std::endl;
        std::cout << "1) Inorder" << std::endl;
        std::cout << "2) Preorder" << std::endl;
        std::cout << "3) Postorder" << std::endl;
        int type;
        std::cin >> type;
        return type;
    }

    void lookupOpt(Manager* myLibrary) {
        int type = lookupType(myLibrary);
        switch(type) {
            case 1:
                myLibrary->inorder();
                break;
            case 2:
                myLibrary->preorder();
                break;
            case 3:
                myLibrary->postorder();
                break;
        }
    }

    bool choice(Manager* myLibrary) {
        menuOpt();
        int response;
        std::cin >> response;
        switch (response) {
            case 1:
                addOpt(myLibrary);
                break;
            case 2:
                removeOpt(myLibrary);
                break;
            case 3:
                modifyOpt(myLibrary);
                break;
            case 4:
                lookupOpt(myLibrary);
                break;
            case 5:
                return false;
            default:
                std::cout << "That is not a valid option. Try again." << std::endl;
        }
        return true;
    }


    int main() {
        Manager* myLibrary = new Manager();
        std::cout << "Welcome to your Library" << std::endl;

        bool editing = true;

        do {
            editing = choice(myLibrary);
        }
        while(editing);

        return 0;
    }
