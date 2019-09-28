#include <set>
#include <string>
#include <algorithm>
#include "common.h"

using std::string;

std::set<string> get_all_students() {
    std::set<string> chem101 = get_chem101<std::set<string>>();
    std::set<string> calc1 = get_calc1<std::set<string>>();

    std::set<string> all_students;

    std::set_union(chem101.begin(), chem101.end(), 
                   calc1.begin(), calc1.end(),
                   std::inserter(all_students, 
                                 all_students.end()));

    return std::move(all_students);
}

std::set<string> get_students_in_both_classes() {
    std::set<string> chem101 = get_chem101<std::set<string>>();
    std::set<string> calc1 = get_calc1<std::set<string>>();

    std::set<string> in_both_classes;

    std::set_intersection(chem101.begin(), chem101.end(),
                          calc1.begin(), calc1.end(),
                          std::inserter(in_both_classes, 
                                        in_both_classes.end()));

    return std::move(in_both_classes);
}

std::set<string> get_students_only_in_chem101() {
    std::set<string> chem101 = get_chem101<std::set<string>>();
    std::set<string> calc1 = get_calc1<std::set<string>>();

    std::set<string> only_in_chem;

    std::set_difference(chem101.begin(), chem101.end(),
                        calc1.begin(), calc1.end(),
                        std::inserter(only_in_chem, 
                                      only_in_chem.end()));

    return std::move(only_in_chem);
}

std::set<string> students_only_in_one_class() {
    std::set<string> chem101 = get_chem101<std::set<string>>();
    std::set<string> calc1 = get_calc1<std::set<string>>();

    std::set<string> in_one_class;

    std::set_symmetric_difference(chem101.begin(), chem101.end(),
                                  calc1.begin(), calc1.end(),
                                  std::inserter(in_one_class, 
                                                in_one_class.end()));

    return std::move(in_one_class);

}
