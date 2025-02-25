/*
 * Author: Juliana Serrano
 * Last Modified: 02/25/2025
 * Lab 5: AVL Tree
 * Test.cpp allows you to run all the files together and test the AVL tree implementation
*/

#include <string>
#include <iostream>
#include <vector>

#include "Node.hpp"
#include "Manager.hpp"

    int main() {
        Manager* myLibrary = new Manager();
        std::cout << "Welcome to your Library" << std::endl;

        myLibrary->run();

        return 0;
    }
