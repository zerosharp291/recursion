//
// Created by zeros on 14.04.2025.
//

#ifndef BOTTLE_H
#define BOTTLE_H
# pragma once

#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <sstream>

class bottle {
    unsigned long filling; // время, необходимое на наполнение
    unsigned long capping; // время, необходимое на закупоривание
public:
    bottle(unsigned long f, unsigned long c);

    ~bottle() = default;

    [[nodiscard]] unsigned long get_filling() const;

    [[nodiscard]] unsigned long get_capping() const;

    [[nodiscard]] unsigned long get_processing_time() const;
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
    if (std::ofstream outfile{filename}; outfile.is_open()) {
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
        outfile.close();
    } else {
        throw std::runtime_error("Failed to open file");
    }
}

inline std::vector<bottle> get_bottles_from_file(const std::string &filename) {
    std::vector<bottle> bottles;

    if (std::ifstream infile{filename}; !infile.is_open()) {
        std::string filling_line;
        std::string capping_line;

        getline(infile, filling_line);
        getline(infile, capping_line);

        std::istringstream filling_stream(filling_line);
        std::istringstream capping_stream(capping_line);

        std::string fill_elem;
        std::string capp_elem;
        while (filling_stream >> fill_elem) {
            capping_stream >> capp_elem;
            bottles.emplace_back(std::stoul(fill_elem), std::stoul(capp_elem));
        }
    }

    return bottles;
}

#endif //BOTTLE_H
