#include "set.h"
#include <exception>
#include <iostream>
#include <string>
#include "common.h"

set<std::string> get_all_students() {
    set<std::string> chem101 = get_chem101<set<std::string>>();
    set<std::string> calc1 = get_calc1<set<std::string>>();

    set<std::string> result = chem101.set_union(calc1);

    return std::move(result);
}

set<std::string> get_students_in_both_classes() {
    set<std::string> chem101 = get_chem101<set<std::string>>();
    set<std::string> calc1 = get_calc1<set<std::string>>();

    set<std::string> result = chem101.set_intersection(calc1);

    return std::move(result);
}

set<std::string> get_students_only_in_chem101() {
    set<std::string> chem101 = get_chem101<set<std::string>>();
    set<std::string> calc1 = get_calc1<set<std::string>>();

    set<std::string> result = chem101.set_difference(calc1);

    return std::move(result);
}

set<std::string> students_only_in_one_class() {
    set<std::string> chem101 = get_chem101<set<std::string>>();
    set<std::string> calc1 = get_calc1<set<std::string>>();

    set<std::string> result = chem101.set_symmetric_difference(calc1);

    return std::move(result);
}


void main() {
    print_set(get_all_students());
    print_set(get_students_in_both_classes());
    print_set(get_students_only_in_chem101());
    print_set(students_only_in_one_class());
    
}