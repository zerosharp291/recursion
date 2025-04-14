//
// Created by zeros on 14.04.2025.
//

#ifndef BOTTLE_H
#define BOTTLE_H
# pragma once

#include <string>
#include <fstream>
#include <random>

class bottle {
    int filling; // время, необходимое на наполнение
    int capping; // время, необходимое на закупоривание
public:
    bottle(int f, int c);

    ~bottle() = default;

    int get_filling() const;

    int get_capping() const;
};

inline void generate_bottles_file(
    const std::pair<unsigned, unsigned> &filling_range,
    const std::pair<unsigned, unsigned> &capping_range,
    const int count,
    const std::string &filename
) {
    /*
     * Генератор значений для бутылок
     * const std::pair<unsigned, unsigned> &filling_range, -- диапазон генерации для времени заполнения
     * const std::pair<unsigned, unsigned> &capping_range, -- диапазон генерации для времени закупоривания
     * const int count, -- число бутылок
     * const std::string &filename -- имя выходного файла
     */
    std::ofstream outfile{filename};

    std::random_device rd;
    std::mt19937 gen{rd()};

    std::uniform_int_distribution dist{filling_range.first, filling_range.second};

    for (int i = 0; i < count; i++) {
        outfile << dist(gen) << " ";
    }
    outfile << "\n";
    std::uniform_int_distribution dist2{capping_range.first, capping_range.second};
    for (int i = 0; i < count; i++) {
        outfile << dist2(gen) << " ";
    }
}

#endif //BOTTLE_H
