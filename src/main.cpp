#include "../include/bottle.h"

int main() {
    generate_bottles_file(std::pair{1,10}, std::pair{1,10}, 10, "bottles.txt");
    return 0;
}