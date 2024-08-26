#include <iostream>
#include "util.hpp"

Board::Board(int v): value(v) {}

const int Board::getValue() const{
    return value;
}
