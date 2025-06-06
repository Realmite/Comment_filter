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

bool readFromFile(const string& filename, string& content) {
    ifstream inputFile(filename);
    if (!inputFile)
        return false;

    stringstream buffer;
    buffer << inputFile.rdbuf();
    content = buffer.str();
    return true;
}

bool writeToFile(const string& filename, const string& content) {
    ofstream outputFile(filename);
    if (!outputFile)
        return false;

    outputFile << content;
    return true;
}

string removeMultilineCommentsFromText(const string& text) {
    regex definePattern(R"(^\s*#\s*define\b)");
    istringstream iss(text);
    string line;
    int line_num = 1;

    while (getline(iss, line)) {
        if (regex_search(line, definePattern)) {
            Error err = Error::createInvalidInputError(line_num, -1, '#');
            reportError(err);
        }
        ++line_num;
    }

    State state = NORMAL;
    string result, output;
    bool escaped = false;
    int len = text.length();

    for (int i = 0; i < len; ++i) {
        char current = text[i];
        char next = (i + 1 < len) ? text[i + 1] : '\0';

        switch (state) {
        case NORMAL:
            if (current == '/' && next == '*') {
                state = MULTILINE_COMMENT;
                ++i;
            }
            else if (current == '/' && next == '/') {
                state = SINGLELINE_COMMENT;
                output += current;
                output += next;
                ++i;
            }
            else if (current == '"') {
                state = STRING_LITERAL;
                output += current;
                escaped = false;
            }
            else {
                output += current;
            }
            break;

        case MULTILINE_COMMENT:
            if (current == '*' && next == '/') {
                state = NORMAL;
                ++i;
            }
            break;

        case SINGLELINE_COMMENT:
            output += current;
            if (current == '\n') {
                state = NORMAL;
            }
            break;

        case STRING_LITERAL:
            output += current;
            if (current == '\\') {
                escaped = !escaped;
            }
            else if (current == '"' && !escaped) {
                state = NORMAL;
            }
            else {
                escaped = false;
            }
            break;
        }
    }

    result += output;
    return result;
}
