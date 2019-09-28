#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> split_line(std::string line, std::string delims)
{
    std::vector<std::string> words;
    boost::split(words, line, boost::is_any_of(delims));

    return words;
}

std::vector<std::string> load_words(std::string path)
{
    std::vector<std::string> words;
    std::ifstream input(path);

    while (input.good())
    {
        std::string line;
        std::getline(input, line);
        std::vector<std::string> split = split_line(line, " \t,.-()\"");
        words.insert(words.end(), split.begin(), split.end());
    }

    input.close();

    return words;
}

