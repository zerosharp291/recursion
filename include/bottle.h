//
// Created by zeros on 14.04.2025.
//

#ifndef BOTTLE_H
#define BOTTLE_H
# pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <windows.h>

class bottle {
    unsigned long filling; // время, необходимое на наполнение
    unsigned long capping; // время, необходимое на закупоривание
    unsigned long processing_time;
    unsigned long id;

public:
    bottle(unsigned long f, unsigned long c, unsigned long _id);

    ~bottle() = default;

    [[nodiscard]] unsigned long get_filling() const;

    [[nodiscard]] unsigned long get_capping() const;

    [[nodiscard]] unsigned long get_processing_time() const;

    [[nodiscard]] unsigned long get_id() const;

    bool operator<(const bottle &b) const;

    bool operator==(const bottle &b) const;
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
    /*
        функция считывает параметры бутылок из файла
    */
    std::vector<bottle> bottles;

    if (std::ifstream infile{filename}; infile.is_open()) {
        std::string filling_line;
        std::string capping_line;

        getline(infile, filling_line);
        getline(infile, capping_line);

        std::istringstream filling_stream(filling_line);
        std::istringstream capping_stream(capping_line);

        std::string fill_elem;
        std::string capp_elem;
        unsigned long id = 0;
        while (filling_stream >> fill_elem) {
            capping_stream >> capp_elem;
            bottles.emplace_back(std::stoul(fill_elem), std::stoul(capp_elem), id);
            id++;
        }
    } else {
        throw std::runtime_error("Failed to open file");
    }

    return bottles;
}

inline double get_avg_processing_time(const std::vector<bottle> &bottles, const size_t i,
                                      const size_t j) {
    /*
     * Подсчитывает среднее значение обработки для вектора с бутылями
     * const std::vector<bottle>& bottles (вектор с бутылями),
     * const size_t i = 0, (начало суммирования)
     * const size_t j = bottles.size() (конец суммирования)
     */
    if (!bottles.empty()) {
        double sum = 0;

        for (size_t k = i; k < j; k++) {
            sum += bottles[k].get_processing_time();
        }

        return sum / static_cast<double>(bottles.size());
    }
    throw std::runtime_error("Empty bottles array");
}

inline double get_avg_processing_time(const std::vector<bottle> &bottles) {
    /*
     * Подсчитывает среднее значение обработки для вектора с бутылями
     * const std::vector<bottle>& bottles (вектор с бутылями),
     */
    if (!bottles.empty()) {
        double sum = 0;

        for (const bottle &bottle: bottles) {
            sum += bottle.get_processing_time();
        }

        return sum / static_cast<double>(bottles.size());
    }
    throw std::runtime_error("Empty bottles array");
}

inline void brute_distribution_two_conveyors(const std::vector<bottle> &source, std::vector<bottle> &conveyor1,
                                             std::vector<bottle> &conveyor2) {
    bool flag = true;

    for (bottle b: source) {
        if (flag) {
            conveyor1.push_back(b);
            flag = !flag;
        } else {
            conveyor2.push_back(b);
            flag = !flag;
        }
    }
}

inline void print_bottles_array(const std::vector<bottle> &bottles) {
    for (const bottle &b: bottles) {
        std::cout << "F" << b.get_filling() << " C" << b.get_capping() <<
                " P" << b.get_processing_time() << std::endl;
    }
}


inline unsigned long sum_bottles_array(const std::vector<bottle> &bottles) {
    if (!bottles.empty()) {
        unsigned long sum = 0;
        for (const bottle &b: bottles) {
            sum += b.get_processing_time();
        }

        return sum;
    }
    return 0;
}

inline void backtrack(
    const std::vector<bottle> &source,
    const size_t index,
    const double desired_sum,
    std::vector<bottle> &current_conveyor,
    const double current_sum,
    std::vector<bottle> &best_conveyor,
    double &best_sum
) {
    // Проверяем, является ли текущая сумма лучше предыдущей лучшей
    if (std::abs(current_sum - desired_sum) < std::abs(best_sum - desired_sum) || best_conveyor.empty()) {
        best_sum = current_sum;
        best_conveyor = current_conveyor;
    }

    // Если достигли конца массива или текущая сумма уже превышает desired_sum, выходим
    if (index == source.size() || current_sum >= desired_sum) {
        return;
    }

    // Рекурсивно пробуем добавить текущий элемент
    current_conveyor.push_back(source[index]);
    backtrack(source, index + 1, desired_sum, current_conveyor,
              current_sum + source[index].get_processing_time(), best_conveyor, best_sum);
    current_conveyor.pop_back();

    // Рекурсивно пробуем не добавлять текущий элемент
    backtrack(source, index + 1, desired_sum, current_conveyor, current_sum, best_conveyor, best_sum);
}

std::pair<std::vector<bottle>, std::vector<bottle> > generate_conveyor(const std::vector<bottle> &source);

#endif //BOTTLE_H
