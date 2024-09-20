#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Trie.h"

using namespace std;

#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

int list_counter = 0;
extern int trie_counter; // You should implement in Trie.cpp

void TrieGamePlay(string targetWord, string firstGuess, Trie& trie);
void ListGamePlay(string targetWord, string firstGuess, list<string> wordList);
list<string> filterWordList(const list<string>& wordList, const string& guess, const string& colors);
void readWordTrie(const std::string& filename, Trie& trie);
void readWordList(const std::string& filename, std::list<std::string>& wordList);

string get_status_str(bool status) {
    return status ? "PASSED" : "FAILED";
}

class TrieTest {
private:
    bool test_result[5] = {0,0,0,0,0};
    string test_description[8] = {
            "Test1: New trie is valid",
            "Test2: Inserting new words is successful",
            "Test3: Inserting invalid words does not add words",
            "Test4: Filtering updates a trie to a correct filtered trie",
            "Test5: Filtering returns false if inputs are incorrect and does not update a trie",
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
    bool test5();
};


int main() {
    //wordilist.txt has a lot of words. readWordTrie function
    //may help you create a trie with a lot of words to test.
    Trie trie;
    readWordTrie("../wordlist.txt", trie);

    list<string> words;
    readWordList("../wordlist.txt", words);
    ListGamePlay("apple", "plrep", words);
    std::cout << "first" << trie.getFirstWord() << std::endl;
    TrieGamePlay("apple", "plrep", trie);
    //trie.filter("apple", "ggggg");
    //trie.print();

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
    TrieTest t_test;

    // You can check the description for each test to see
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above
    // where the test description is stored to read it.
    cout << t_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = t_test.test1();
    cout << "Test1: " << get_status_str(result) << endl;

    // Or you can run all of the tests at once and generate a report.
    t_test.runAllTests();
    t_test.printReport();

    return 0;
}



string TrieTest::getTestDescription(int test_num) {
    if (test_num < 1 || test_num > 5) {
        return "";
    }
    return test_description[test_num-1];
}

void TrieTest::runAllTests() {
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
    test_result[4] = test5();
}

void TrieTest::printReport() {
    cout << "  TRIE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 5; ++idx) {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl << endl;
    }
    cout << endl;
}

// Test 1: New trie is valid
bool TrieTest::test1() {
    Trie trie;

    ASSERT_TRUE(trie.size() == 0)
    ASSERT_TRUE(trie.root -> children.empty())
    ASSERT_FALSE(trie.insert("abc"))
    ASSERT_TRUE(trie.getFirstWord() == "")

    return true;
}

// Test 2: Inserting new words - valid and invalid - works properly
bool TrieTest::test2() {
    Trie t;

    ASSERT_TRUE(t.insert("apple"))
    ASSERT_FALSE(t.insert("banana"))
    ASSERT_TRUE(t.insert("appll"))
    ASSERT_FALSE(t.insert("apple"))
    ASSERT_TRUE(t.insert("mango"))
    ASSERT_TRUE(t.size() == 3);

    std::list<char> keys;
    for (const auto& child : t.root->children) {
        keys.push_back(child.first);
    }

    for (const auto& key : keys) {
        t.deleteTrie(t.root->children[key]);
        t.root->children.erase(key);
    }

    ASSERT_TRUE(t.root -> children.empty())
    ASSERT_TRUE(t.size() == 0)

    return true;
}

// Test 3: Inserting invalid words does not add words
bool TrieTest::test3() {
    Trie trie;

    ASSERT_TRUE(trie.insert("ogens"));
    ASSERT_TRUE(trie.insert("opend"));
    ASSERT_TRUE(trie.insert("mopoi"));
    ASSERT_TRUE(trie.insert("kmire"));
    ASSERT_TRUE(trie.insert("bpees"));
    ASSERT_TRUE(trie.insert("bmicy"));
    ASSERT_TRUE(trie.insert("bmice"));

    ASSERT_TRUE(trie.size() == 7);

    ASSERT_FALSE(trie.insert("bmicy"));
    ASSERT_FALSE(trie.insert("bmice"));
    ASSERT_FALSE(trie.insert("ogens"));
    ASSERT_FALSE(trie.insert("opend"));
    ASSERT_FALSE(trie.insert("mopoi"));
    ASSERT_FALSE(trie.insert("kmire"));
    ASSERT_FALSE(trie.insert("bpees"));

    ASSERT_TRUE(trie.size() == 7);

    auto it = trie.root->children.find('b');
    trie.deleteTrie(it->second);
    trie.root->children.erase(it->first);

    ASSERT_TRUE(trie.size() == 4); // changed to 6 from 4 because can't guarantee which unordered map element is first

    return true;
}

// Test 4: Filtering updates a trie to a correct filtered trie
bool TrieTest::test4() {
    Trie trie;

    ASSERT_TRUE(trie.insert("ogens"));
    ASSERT_TRUE(trie.insert("opend"));
    ASSERT_TRUE(trie.insert("mopoi"));
    ASSERT_TRUE(trie.insert("kmire"));
    ASSERT_TRUE(trie.insert("bpees"));
    ASSERT_TRUE(trie.insert("bmicy"));
    ASSERT_TRUE(trie.insert("bmice"));

    ASSERT_TRUE(trie.filter("mopoi", "ggggg"))

    std::cout << "filtered: ";
    trie.print();

    Trie t;
    ASSERT_TRUE(t.insert("apple"));
    ASSERT_TRUE(t.insert("orang"));
    ASSERT_TRUE(t.insert("banan"));
    ASSERT_TRUE(t.insert("grape"));
    ASSERT_TRUE(t.insert("slide"));
    ASSERT_TRUE(t.insert("brain"));
    ASSERT_TRUE(t.insert("trail"));

    t.filter("brain","gbybg");

    t.print();

    return true;
}

// Test 5: Filtering returns false if inputs are incorrect and does not update a trie
bool TrieTest::test5() {
    Trie trie;

    ASSERT_TRUE(trie.insert("ogens"));
    ASSERT_TRUE(trie.insert("opend"));
    ASSERT_TRUE(trie.insert("mopoi"));
    ASSERT_TRUE(trie.insert("kmire"));
    ASSERT_TRUE(trie.insert("bpees"));
    ASSERT_TRUE(trie.insert("bmicy"));
    ASSERT_TRUE(trie.insert("bmice"));
    trie.print();

    ASSERT_FALSE(trie.filter("mopo", "gggg"))

    std::cout << "invalid filter" << std::endl;
    trie.print();

    ASSERT_TRUE(trie.filter("mopoi", "ggggg"))

    std::cout << "filtered: ";
    trie.print();
    return true;
}

/*
Similar to the ‘ListGamePlay’ function, the ‘TrieGamePlay’ function simulates the Wordle 
game but uses a Trie instead of a List. Given three parameters, it iteratively guesses a 
word from the pool of words and uses the feedback to refine its guesses until the target 
word is found. After the target word is found, the program displays the total number of 
words checked along the process, which is tracked by the global variable ‘trie_counter’. 
A Trie is initialized with all the words from the wordlist inserted into it. Then the 
‘filter’ function in the Trie class is called to eliminate words that do not match the 
feedback (about colour pattern requirements) from the Trie. 

The function is case-sensitive so the string of word and color pattern should be lower case.
 
Note regarding the global variable ‘trie_counter’. Global variables are declared at the 
top of a file, outside of functions, and have a wide scope, meaning they can be accessed 
and changed from any part of the program. Therefore, one copy of it is used throughout 
all functions. The implementation of ‘trie_counter’ is similar to ‘list_counter’. First, 
the ‘trie_counter’ is declared as a global variable in ‘main.cpp’, and it is defined in 
‘Trie.cpp’. The ‘extern’ keyword allows the variable to be accessed from anywhere in the 
program, even from other files. In this case, we access it from ‘Trie.cpp’. Second, the 
‘trie_counter’ should be incremented in the Trie class, specifically in the ‘filter’ 
function. The ‘list_counter’ is a global variable, but its scope is limited to ‘main.cpp’. 
By checking the ‘filterWordList’ function in ‘main.cpp’, you can see how ‘list_counter’ is 
implemented. You will need to implement ‘trie_counter’ in a similar way, incrementing it 
by one after each word is checked along the process to find the answer to the question. 
 
The following are the three parameters the function, ‘TrieGamePlay’, takes in:
string targetWord - This is the Wordle answer the program aims to guess. 
string firstGuess - This is a random 5-letter word used as the initial guess. 
Trie& trie - This is a trie of all the words from ‘wordlist.txt’.
 
Output:
Using a Trie, the program found the word “scent” in ___ words.
 
Note: In the output, the number of words checked is left blank. Once you successfully 
implement the functions in the Trie class, you will notice a significant difference 
between using a list and a trie.
*/
void TrieGamePlay(string targetWord, string firstGuess, Trie& trie) {
    int attemptsTrie = 0;
    string guess, colors;
    while (true) {
        attemptsTrie++;
        if (attemptsTrie == 1) {
            guess = firstGuess;
        } else {
            guess = trie.getFirstWord(); // The programs' guess is the first word in the trie
        }

        // Compare the program guess and target word to determine the color code
        colors = "";
        for (int i = 0; i < 5; ++i) {
            if (guess[i] == targetWord[i]) {
                colors += 'g'; // Green
            } else if (targetWord.find(guess[i]) != string::npos) {
                colors += 'y'; // Yellow
            } else {
                colors += 'b'; // Grey
            }
        }

        if (colors == "ggggg") {
            cout << "Using a Trie, the program found the word \"" << targetWord << "\" in " << trie_counter << " words."
                 << endl;
            break;
        }

        // Filter the trie based on the guess and colors
        trie.filter(guess, colors);
    }
}

// This function simulates the Wordle game using Lists and displays the number of words checked.
void ListGamePlay(string targetWord, string firstGuess, list<string> wordList) {
    int attemptsList = 0;
    string guess, colors;
    while (true) {
        attemptsList++;
        if (attemptsList == 1) {
            guess = firstGuess;
        } else {
            guess = wordList.front(); // The programs' guess is the first word in the list
        }

        // Compare the program guess and target word to determine the color code
        colors = "";
        for (int i = 0; i < 5; ++i) {
            if (guess[i] == targetWord[i]) {
                colors += 'g'; // Green
            } else if (targetWord.find(guess[i]) != string::npos) {
                colors += 'y'; // Yellow
            } else {
                colors += 'b'; // Grey
            }
        }

        if (colors == "ggggg") {
            cout << "Using a List, the program found the word \"" << targetWord << "\" in " << list_counter << " words." << endl;
            break;
        }

        // Filter the word list based on the guess and colors
        wordList = filterWordList(wordList, guess, colors);
    }
}

list<string> filterWordList(const list<string>& wordList, const string& guess, const string& colors) {
    list<string> filteredWords;

    for (const auto& word : wordList) {
        list_counter ++;
        bool matches = true;
        for (int i = 0; i < 5; ++i) {
            if (colors[i] == 'g' && word[i] != guess[i]) { // Green - correct position
                matches = false;
                break;
            } else if (colors[i] == 'y') { // Yellow - correct letter, wrong position
                if (word[i] == guess[i] || word.find(guess[i]) == string::npos) { // Checks if the letters are equal or if the letter exists in the word
                    matches = false;
                    break;
                }
            } else if (colors[i] == 'b' && word.find(guess[i]) != string::npos) { // Grey - letter not in word
                matches = false;
                break;
            }
        }
        if (matches) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}

void readWordTrie(const std::string& filename, Trie& trie) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
            trie.insert(word);
}

void readWordList(const std::string& filename, std::list<std::string>& wordList) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        if (word.length() == 5) {
            wordList.push_back(word);
        }
    }
}