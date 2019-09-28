#include <iostream>
#include <string>

template<class T>
T get_chem101() {
    T students;
    students.insert("Cathy");
    students.insert("Evelyn");
    students.insert("Franklin");
    students.insert("Jim");
    students.insert("Mary");
    students.insert("Steve");

    return std::move(students);
}

template<class T>
T get_calc1() {
    T students;
    students.insert("Abby");
    students.insert("Cindy");
    students.insert("Evelyn");
    students.insert("Fredrick");
    students.insert("Jim");
    students.insert("Mary");

    return std::move(students);
}

template<class T>
void print_set(T& data) {
    for (auto& value : data) {
        std::cout << value << " ";
    }

    std::cout << std::endl;
}
