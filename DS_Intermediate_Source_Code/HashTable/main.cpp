#include "hashtable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>

// splits an input streams into words
// and performs a callback for each word found
template<typename WordFoundCallback>
void split_words(std::istream &input,
    WordFoundCallback callback) {
    std::vector<char> word;
    char current;

    while (input.get(current)) {
        if (std::isalpha(current)) {
            word.push_back(current);
        }
        else {
            if (!word.empty()) {
                std::string found(word.begin(), word.end());
                callback(found);
                word.clear();
            }
        }
    }
}


struct sdbm {
    size_t operator()(const std::string& str) {
        const char* buffer = str.c_str();

        unsigned long hash = 0;
        int c;

        while (c = *buffer++) {
            hash = c + (hash << 6) 
                     + (hash << 16) 
                     - hash;
        }

        return hash;
    }
};




void main() {
    // open the text file for reading
    std::ifstream infile("c:\\temp\\marktwain.txt", std::ios_base::in);

    // hash table containing the word and occurance count
    // uses the custom sdbm algorithm
    hashtable<std::string, int> words;

    // split the stream into words and count
    // the occurance of each word in the hashtable
    split_words(infile,
        [&words](std::string& word) {
            // ignore single-letter words
            if (word.size() > 2) {

                // increment the word - the default value
                // will be zero if the entry does not exist
                // and needs to be created.
                words[word]++;
            }
        }
    );

    // print out the words used more than 1000 times.
    for (auto iter : words) {
        if (iter.second > 1000){
            std::cout << iter.first << " " << iter.second << std::endl;
        }
    }
}
