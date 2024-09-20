#include "Trie.h"
#include <iostream>
#include <stack>

// trie_counter should be incremented by one after 
// each word is checked in the 'filter' function.
int trie_counter = 0;

TrieNode::TrieNode() {
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    deleteTrie(root);
}

void Trie::deleteTrie(TrieNode* node) {
    if (node == nullptr)
        return;
    for (const auto& pair : node -> children) {
        deleteTrie(pair.second);
    }
    node -> children.clear();
    delete node;
    node = nullptr;
}

unsigned int Trie::countLeaves(TrieNode* node) const {
    unsigned int leaves = 0;

    if (node -> children.empty())
        return 0;

    for (const auto& pair : node -> children) {
        if (pair.second -> children.empty())
            leaves++;
        else
            leaves += countLeaves(pair.second);
    }

    return leaves;
}

unsigned int Trie::size() const {
   unsigned int size = countLeaves(root);
   return size;
}

bool Trie::insert(const std::string &word) {
    if (word.length() != 5) {
        return false;
    }

    TrieNode* temp = root;
    bool newWord = false;

    for (int i = 0; i < 5; i++) {
        if (temp -> children.find(word[i]) == temp -> children.end()) {
            TrieNode *newNode = new TrieNode();
            temp->children[word[i]] = newNode;
            newWord = true;
        }
        temp = temp->children[word[i]];
    }

    if (!newWord)
        return false;

    return true;
}

std::string Trie::getFirstWord() {
    TrieNode* temp = root;
    if (temp -> children.empty()) {
        return "";
    }

    std::list<std::string> words = getAllWords();
    return words.front();
}

std::list<std::string> Trie::getAllWords() const {
    std::list<std::string> words;
    std::string currentWord = "";
    getWordsRecursively(root, currentWord, words);
    return words;
}

void Trie::getWordsRecursively(TrieNode *node, std::string currentWord, std::list<std::string> &words) const {
    if (currentWord.size() == 5) {
        words.push_back(currentWord);
    }

    for (auto& child : node->children) {
        getWordsRecursively(child.second, currentWord + child.first, words);
    }
}

bool Trie::filter(const std::string &guess, const std::string &pattern) {
    if (guess.size() != 5 || pattern.size() != 5)
        return false;
    else {
        filterRecursively(root, "", guess, pattern);
        return true;
    }
}

void Trie::filterRecursively(TrieNode* node, std::string currentWord, const std::string &guess, const std::string &pattern) {
    bool valid = true;
    int depth = currentWord.size();
    std::list<char> invalidWords;

    if (depth == 5) {
        trie_counter++;
        return;
    }

    // Iterate over children and recursively filter them
    for (auto& letter : node->children) {
        std::string word = currentWord + letter.first;

        if (word.size() == 5) {
            valid = true;
            for (int i = 0; i < 5; i++) {
                if ((pattern[i] == 'g' && word[i] != guess[i]) || (pattern[i] == 'y' && (word.find(guess[i]) == std::string::npos || word[i] == guess[i])) || (pattern[i] == 'b' && word.find(guess[i]) != std::string::npos))
                    valid = false;
            }

            if (!valid) {
                invalidWords.push_back(letter.first);
                continue;
            }
        }

        filterRecursively(letter.second, word, guess, pattern);
    }

    for (char letter : invalidWords) {
        if (node->children.find(letter) != node->children.end()) {
            deleteTrie(node->children[letter]);
            node->children.erase(letter);
        }
    }
}

void Trie::print() {
    std::list<std::string> words = getAllWords();
    for (auto &word : words) {
        if (word.size() == 5)
            std::cout << word << std::endl;
    }
}