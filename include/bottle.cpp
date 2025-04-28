//
// Created by zeros on 14.04.2025.
//

#include "bottle.h"

#include <set>

bottle::bottle(const unsigned long f, const unsigned long c, unsigned long _id): filling(f), capping(c),
    processing_time(f + c), id(_id) {
    /*
     * const unsigned long f (время заполнения), const unsigned long c (время закупоривания)
     */
}

unsigned long bottle::get_filling() const {
    return filling;
}

unsigned long bottle::get_capping() const {
    return capping;
}

unsigned long bottle::get_processing_time() const {
    return processing_time;
}

unsigned long bottle::get_id() const { return id; }

bool bottle::operator<(const bottle &b) const {
    return get_processing_time() < b.get_processing_time();
}

bool bottle::operator==(const bottle &b) const {
    return (this->get_processing_time() == b.get_processing_time() && this->get_filling() == b.get_filling() && this->
            get_capping() == b.get_capping());
}


std::pair<std::vector<bottle>, std::vector<bottle> > generate_conveyor(const std::vector<bottle> &source) {
    const double desired_sum = static_cast<double>(sum_bottles_array(source)) / 2;
    std::cout << "Desired sum: " << desired_sum << std::endl;
    std::vector<bottle> conveyor1;
    std::vector<bottle> tmp_conveyor;
    double best_sum = 0;

    backtrack(source, 0, desired_sum, tmp_conveyor, 0, conveyor1, best_sum);

    // Вывод для отладки
    std::cout << "Best sum found: " << best_sum << std::endl;

    std::set<unsigned long> id_set;

    for (auto element : conveyor1) {
        id_set.insert(element.get_id());
    }

    std::vector<bottle> conveyor2;
    for (auto element : source) {
        if (!id_set.contains(element.get_id())) {
            conveyor2.push_back(element);
        }
    }

    return std::make_pair(conveyor1, conveyor2);
}
