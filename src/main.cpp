#include <iostream>
#include <algorithm>

#include "../include/bottle.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const std::string filename = "bottles.txt";
    // generate_bottles_file(std::pair{1,10}, std::pair{1,10}, 10, filename);

    std::vector<bottle> bottles = get_bottles_from_file(filename);

    const double avg_processing_time = get_avg_processing_time(bottles);

    std::sort(bottles.rbegin(), bottles.rend());

    std::cout << "Среднее время обработки бутыли: " << avg_processing_time << std::endl;

    auto conveyor_pair = generate_conveyor(bottles);

    std::cout << "Конвейер 1" << std::endl;
    print_bottles_array(conveyor_pair.first);
    std::cout << "Общее время: " << sum_bottles_array(conveyor_pair.first) << std::endl;
    std::cout << std::endl;

    std::cout << "Конвейер 2" << std::endl;
    print_bottles_array(conveyor_pair.second);
    std::cout << "Общее время: " << sum_bottles_array(conveyor_pair.second) << std::endl;
    std::cout << std::endl;
    return 0;
}
