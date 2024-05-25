#pragma once
#include "BalancedTree.h"

class HashTable {
private:
    std::vector<std::list<BalancedTree>> table;

    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const std::string& key, const std::string& value) {
        int hash = hashFunction(key);
        bool collision = false;
        for (auto& tree : table[hash]) {
            if (!tree.search(key).empty() && tree.search(key).front() != "Not Found!") {
                collision = true;
                break;
            }
        }
        if (collision) {
            std::cout << "Collision at index " << hash << " for key " << key << std::endl;
        }
        BalancedTree newTree;
        newTree.insert(key, value);
        table[hash].push_back(newTree);
    }

    void remove(const std::string& key) {
        int hash = hashFunction(key);
        for (auto& tree : table[hash]) {
            tree.remove(key);
        }
    }

    std::list<std::string> search(const std::string& key) {
        int hash = hashFunction(key);
        for (auto& tree : table[hash]) {
            auto result = tree.search(key);
            if (!result.empty() && result.front() != "Not Found!") {
                return result;
            }
        }
        return { "Not Found!" };
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            std::cout << "Node" << i << ":" << std::endl;
            for (auto& tree : table[i]) {
                tree.display();
            }
        }
    }
};