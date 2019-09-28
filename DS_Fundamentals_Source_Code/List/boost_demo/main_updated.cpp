#include <boost/container/list.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include<boost/tokenizer.hpp>

using std::cout;
using std::endl;
using std::string;


typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

void load_words(std::istream& input, boost::container::list<string>& words)
{
    boost::char_separator<char> sep(" \t,.-()\"");

    while (input.good())
    {
        std::string line;
        std::getline(input, line);

        tokenizer tok(line, sep);

        words.splice(words.end(), tok.begin(), tok.end());

        cout << words.size() << endl;
    }
}

void load_words(std::string path)
{
    boost::container::list<string> words;
    std::ifstream input(path);

    load_words(input, words);

    input.close();

    words.sort();

    for (string word : words)
    {
        cout << word << " ";
    }
}

int main()
{
    load_words("washington.txt");
}