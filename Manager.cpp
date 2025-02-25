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

        void Manager::balancing(int balance, int isbn, Node* hold, Node* parent, Node* newParent) {
            if(balance > 1 && isbn < parent->isbn) {
                std::cout << "LL" << std::endl;
                if (hold == root) {
                    root = rotateRight(hold);
                } else {
                    if (isbn > root->isbn) {
                        newParent->right = rotateRight(hold);
                    } else {
                        newParent->left = rotateRight(hold);
                    }
                }
            } else if (balance > 1 && isbn > parent->isbn) {
                std::cout << "LR" << std::endl;
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
            } else if (balance < -1 && isbn > parent->isbn) {
                std::cout << "RR" << std::endl;
                if (hold == root) {
                    root = rotateLeft(hold);
                } else {
                    if (isbn < root->isbn) {
                        newParent->left = rotateLeft(hold);
                    } else {
                        newParent->right = rotateLeft(hold);
                    }
                }
            } else if (balance < -1 && isbn < parent->isbn) {
                std::cout << "RL" << std::endl;
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
    
        bool Manager::add(std::string title, std::string authorLast, std::string authorFirst,
            std::string publisher, std::string publicationDate, std::string genre, 
            std::string synopsis, int isbn) {
            Node* temp = new Node(title, authorLast, authorFirst, publisher, publicationDate, genre,
                synopsis, isbn, nullptr, nullptr);
            if (root == nullptr) {
                root = temp;
                return true;
            } else {
                Node* current = root;
                Node* parent = root;
                while (current != nullptr) {
                    if (isbn < current->getISBN()){
                        parent = current;
                        current = current->left;
                    } else if(isbn > current->getISBN()){
                        parent = current;
                        current = current->right;
                    } else {
                        return false;
                    }
                }
                if (isbn < parent->getISBN()) {
                    parent->left = temp;
                } else {
                    parent->right = temp;
                }
                Node* current2 = root;
                Node* parent2 = root;
                std::stack<Node*> ancestors;
                std::stack<Node*> parents;
                while (current2 != temp) {
                    if (isbn < current2->getISBN()){
                        parent2 = current2;
                        current2 = current2->left;
                        ancestors.push(parent2);
                    } else if(isbn > current2->getISBN()){
                        parent2 = current2;
                        current2 = current2->right;
                        ancestors.push(parent2);
                    }
                }
                Node* hold = nullptr;
                while(!ancestors.empty()) {
                    hold = ancestors.top();
                    hold->height = 1 + std::max(height(hold->left), height(hold->right));
                    ancestors.pop();
                    std::cout << hold->toString() << std::endl;
                    int balance = balanceFactor(hold);
                    std::cout << std::to_string(balance) << std::endl;
                    Node* newParent = root;
                    if (!ancestors.empty()) {
                        newParent = ancestors.top();
                    }
                    balancing(balance, isbn, hold, parent, newParent);
                }
                return true;
            }
        }   

        bool Manager::remove(int isbn) {
            Node* current = root;
            Node* parent = nullptr;
            std::stack<Node*> ancestors;
            while(current != nullptr && current->getISBN() != isbn){
                if (isbn < current->getISBN()){
                    parent = current;
                    current = current->left;
                    ancestors.push(parent);
                } else if (isbn > current->getISBN()) {
                    parent = current;
                    current = current->right;
                    ancestors.push(parent);
                } else {
                    return false;
                }
            }
            if (current->left == nullptr && current->right == nullptr) {
                removeLeaf(current, parent, isbn);
            } else if (current->left == nullptr) {
                removeChildR(current, parent, isbn);
            } else if (current->right == nullptr) {
                removeChildL(current, parent, isbn);
            } else {
                removeTwoChild(current, parent);
            }
            Node* hold = nullptr;
            while(!ancestors.empty()) {
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
            return true;
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

        void Manager::removeChildR(Node* current, Node* parent, int isbn){
            if (current == root) {
                root = root->right;
            } else if (isbn < parent->getISBN()) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
        }

        void Manager::removeChildL(Node* current, Node* parent, int isbn) {
            if (current == root) {
                root = root->left;
            } else if (isbn < parent->getISBN()) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
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
                Node* current = root;
                while (isbn != current->getISBN()) {
                    if (isbn < current->getISBN()) {
                        current = current->left;
                    } else if (isbn > current->getISBN()) {
                        current = current->right;
                    }
                }
                remove(isbn);
                add(title, authorLast, authorFirst, publisher, publicationDate, genre, synopsis, 
                    isbn);
                return true;
        }

        Node* Manager::traversal() {
            Node* current = root;
            return current;
        }

        void Manager::inorder() {
            std::vector<std::string> list;
            std::stack<Node*> s;
            
            Node* current = root;
            if (current == nullptr) {
                return;
            }
            while (current != nullptr || !s.empty()) {
                while (current != nullptr) {
                    s.push(current);
                    current = current->left;
                }
                current = s.top();
                s.pop();
                list.push_back(current->toString());
                current = current->right;
            }
            for (int i = 0; i < list.size(); i ++) {
                std::cout << list[i] << " ";
            }
        }

        void Manager::preorder() {
            if (root == nullptr) {
                return;
            }
            std::stack<Node*> s;
            s.push(root);
            while (s.empty() == false) {
                Node* temp = s.top();
                std::cout << temp->toString() << std::endl;
                s.pop();
                if (temp->right) {
                    s.push(temp->right);
                }
                if (temp->left) {
                    s.push(temp->left);
                }
            }
        }

        void Manager::postorder() {
            std::vector<std::string> list;
            std::stack<Node*> s;
            s.push(root);
            Node* previous = nullptr;
            while(!s.empty()) {
                Node* current = s.top();
                if (previous == nullptr || previous->left == current || 
                    previous->right == current) {
                    if (current->left) {
                        s.push(current->left);
                    } else if (current->right) {
                        s.push(current->right);
                    } else {
                        s.pop();
                        list.push_back(current->toString());
                    }
                } else if (current->left == previous) {
                    if (current->right) {
                        s.push(current->right);
                    } else {
                        s.pop();
                        list.push_back(current->toString());
                    }
                } else if (current->right == previous) {
                    s.pop();
                    list.push_back(current->toString());
                }
                previous = current;
            }
            for (int i = 0; i < list.size(); i ++) {
                std::cout << list[i] << " ";
            }
        }

        std::string Manager::title(int isbn) {
            return modNode(isbn)->getTitle();
        }

        std::string Manager::authorLast(int isbn) {
            return modNode(isbn)->getAuthorLast();
        }

        std::string Manager::authorFirst(int isbn) {
            return modNode(isbn)->getAuthorFirst();
        }

        std::string Manager::publisher(int isbn) {
            return modNode(isbn)->getPublisher();
        }

        std::string Manager::publicationDate(int isbn) {
            return modNode(isbn)->getPublicationDate();
        }

        std::string Manager::genre(int isbn) {
            return modNode(isbn)->getGenre();
        }

        std::string Manager::synopsis(int isbn) {
            return modNode(isbn)->getSynposis();
        }