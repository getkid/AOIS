#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

#define TABLE_SIZE 20

enum Color { RED, BLACK };

struct TreeNode {
    std::string key;
    std::string value;
    Color color;
    std::shared_ptr<TreeNode> left, right, parent;

    TreeNode(std::string k, std::string v) : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

using NodePtr = std::shared_ptr<TreeNode>;

class BalancedTree {
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->key = "";
        node->color = BLACK;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
    }

    NodePtr searchTreeHelper(NodePtr node, const std::string& key) {
        if (node == TNULL || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    void deleteNodeHelper(NodePtr node, std::string key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            std::cout << "Couldn't find key in the tree" << std::endl;
            return;
        }

        y = z;
        Color original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (original_color == BLACK) {
            deleteFix(x);
        }
    }

    void transplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                }
                else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void balanceInsert(NodePtr k) {
        NodePtr u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void printHelper(NodePtr root, std::string indent, bool last) {
        if (root != TNULL) {
            std::cout << indent;
            if (last) {
                indent += "   ";
            }
            else {
                indent += "|  ";
            }

            std::cout << root->key << "[" << root->value << "]" << std::endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

public:
    BalancedTree() {
        TNULL = std::make_shared<TreeNode>("", "");
        TNULL->color = BLACK;
        root = TNULL;
    }

    void insert(const std::string& key, const std::string& value) {
        NodePtr node = std::make_shared<TreeNode>(key, value);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }
            else if (node->key > x->key) {
                x = x->right;
            }
            else {
                std::cout << "Key already exists. Adding a new entry." << std::endl;
                break;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->key < y->key) {
            y->left = node;
        }
        else if (node->key > y->key) {
            y->right = node;
        }
        else {
            std::cout << "Collision detected." << std::endl;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        balanceInsert(node);
    }

    std::list<std::string> search(const std::string& key) {
        NodePtr node = searchTreeHelper(this->root, key);
        if (node != TNULL) {
            return { node->value };
        }
        else {
            return { "Not Found!" };
        }
    }

    void remove(const std::string& key) {
        deleteNodeHelper(this->root, key);
    }

    void display() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};