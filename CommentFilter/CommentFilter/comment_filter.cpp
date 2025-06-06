#include "comment_filter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>

using namespace std;

void reportError(const Error& error) {
    cerr << "Ошибка: " << error.message << endl;
    if (error.line_num != -1)
        cerr << "Строка: " << error.line_num;
    if (error.col_num != -1)
        cerr << ", Столбец: " << error.col_num;
    if (error.symbol != '\0')
        cerr << ", Символ: '" << error.symbol << "'";
    cerr << endl;
    exit(static_cast<int>(error.type));
}