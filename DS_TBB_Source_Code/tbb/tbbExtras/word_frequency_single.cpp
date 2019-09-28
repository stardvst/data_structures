#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <istream>
#include <queue>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <vector>

namespace single {

    class word_priority {
        bool reverse;
    public:
        word_priority(const bool revparam = false)
        {
            reverse = revparam;
        }

        bool operator() (
            const std::pair<std::string, unsigned int>& lhs,
            const std::pair<std::string, unsigned int>& rhs) const
        {
            return reverse
                ? (lhs.second > rhs.second)
                : (lhs.second < rhs.second);
        }
    };

    class word_frequency {
        std::map<std::string, unsigned int> frequency;
        typedef std::pair<std::string, unsigned int> frequency_pair;

    public:
        void add(std::string word) {
            ++frequency[word];
        }

        void get_top(int count, std::vector<frequency_pair>& trimmed) {
            std::priority_queue<frequency_pair,
                std::vector<frequency_pair>,
                word_priority> top_queue(frequency.begin(), frequency.end());

            for (int i = 0; i < count; i++){
                if (top_queue.empty()) { break; }
                trimmed.push_back(top_queue.top());
                top_queue.pop();
            }
        }
    };

    template<typename KeepCharFilter, typename WordFoundCallback>
    void split_words(std::istream &input, KeepCharFilter filter, WordFoundCallback callback) {
        std::vector<char> word;
        char current;

        while (input.get(current)) {
            if (filter(current)) {
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

    void populate_words_queue(std::string& filename, word_frequency& words) {
        std::ifstream infile(filename, std::ios_base::in);
        split_words(infile,
            [](unsigned char c) {
            return std::isalpha(c);
        },
            [&words](std::string& word) {
            if (word.size() > 2) {
                words.add(word);
            }
        }
        );
    }

    void count_word_frequency() {
        word_frequency words;

        std::vector<std::string> content = {
            "c:\\temp\\greatexpectations.txt",
            "c:\\temp\\marktwain.txt",
            "c:\\temp\\iliad.txt",
            "c:\\temp\\prideprejudice.txt",
            "c:\\temp\\shakespeare.txt",
            "c:\\temp\\warpeace.txt",
        };

        for (auto book : content) {
            populate_words_queue(book, words);
        }

        std::vector<std::pair<std::string, unsigned int>> top_words;
        words.get_top(10, top_words);

        for (auto word : top_words) {
            std::cout << word.first << " " << word.second << std::endl;
        }
    }
}