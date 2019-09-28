#pragma once

#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

class RandomWord {
    std::vector<std::string> words_;
    std::mt19937 generator;

    void add(const std::string& word) {
        words_.push_back(word);
    }

public:
    RandomWord() : generator(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())) {}

    std::string get() {
        std::uniform_int_distribution<int> distribution(0, words_.size()-1);
        return words_[distribution(generator)];
    }

    void load(const std::string& file) {
        std::ifstream infile(file);
        while (infile.good()) {
            std::string line;
            std::getline(infile, line);
            if (!line.empty()) {
                add(line);
            }
        }
    }
};

template<typename Distribution, typename T>
class NumberGenerator {
    std::mt19937 generator;
    Distribution distribution;

    std::string to_str(T value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }

public:
    NumberGenerator(T min, T max)
        : generator(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())),
        distribution(min, max) { }

    T get() {
        return distribution(generator);
    }

    std::string get_str() {
        return to_str(get());
    }
};

class PhoneNumberGenerator {
    NumberGenerator<std::uniform_int_distribution<int>, int> areaCode;
    NumberGenerator<std::uniform_int_distribution<int>, int> prefix;
    NumberGenerator<std::uniform_int_distribution<int>, int> suffix;
public:
    PhoneNumberGenerator()
        : areaCode(110, 990), prefix(110, 990), suffix(0, 9999) { }

    std::string get() {
        return areaCode.get_str() + "-" + prefix.get_str() + "-" + suffix.get_str();
    }
};

class DataGenerator {
    RandomWord first_name;
    RandomWord last_name;
    NumberGenerator<std::uniform_int_distribution<int>, int> street_number;
    RandomWord street_name;
    RandomWord street_type;
    RandomWord state_abbrv;
    RandomWord city_name;
    PhoneNumberGenerator phone_gen;
    NumberGenerator<std::uniform_int_distribution<int>, int> zip5;
    NumberGenerator<std::uniform_int_distribution<int>, int> stars;

public:
    DataGenerator() 
        : street_number(10, 2000), zip5(150, 92000), stars(1, 5) {
        first_name.load("mocks\\data\\firstnames.txt");
        last_name.load("mocks\\data\\lastnames.txt");
        street_name.load("mocks\\data\\streetnames.txt");
        street_type.load("mocks\\data\\streettypes.txt");
        state_abbrv.load("mocks\\data\\stateabbrv.txt");
        city_name.load("mocks\\data\\citynames.txt");
    }

    std::string Zip5() {
        return zip5.get_str();
    }

    std::string FirstName() {
        return first_name.get();
    }

    std::string LastName() {
        return first_name.get();
    }

    std::string PhoneNumber() {
        return phone_gen.get();
    }

    std::string Address1() {
        return street_number.get_str() + " " + street_name.get() + " " + street_type.get();
    }
    
    std::string City() {
        return city_name.get();
    }

    std::string State() {
        return state_abbrv.get();
    }

    std::string Email(const std::string& firstName, const std::string& lastName) {
        return firstName + "." + lastName + "@example.com";
    }

    int Stars() {
        return stars.get();
    }

    std::string ReviewContent() {
        return "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec bibendum lorem eget magna dignissim, non consectetur metus pharetra. Praesent sit amet commodo ligula, lobortis laoreet lorem. Vestibulum aliquet pharetra nibh, at finibus tortor facilisis eu. Donec eget nunc ultricies, egestas orci non, vehicula nunc. Sed quis odio sed augue viverra imperdiet gravida sit amet mauris. Donec odio quam, luctus a nisi sit amet, sodales pretium velit. Vestibulum mattis pharetra ante id auctor. Phasellus erat dui, efficitur et justo sed, dictum pulvinar sapien.";
    }
};

extern DataGenerator Generator;