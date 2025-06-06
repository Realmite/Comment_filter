/**
 * @file main.cpp
 * @brief Entry point for the comment filtering program.
 *        It handles argument parsing, file I/O, and invokes the main logic.
 */

#include "comment_filter.h"
#include <iostream>

using namespace std;

/**
 * @brief Program entry point.
 * @param argc Argument count
 * @param argv Argument values. Expects two: input file and output file.
 * @return Exit code: 0 on success, >0 on error
 */
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if (argc < 3) {
        reportError(Error::createNotEnoughArgumentsError());
    }
    if (argc > 3) {
        reportError(Error::createTooManyArgumentsError());
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];
    string fileContent;

    if (!readFromFile(inputFileName, fileContent)) {
        reportError(Error::createInputFileError(inputFileName));
    }

    string cleanContent = removeMultilineCommentsFromText(fileContent);

    if (!writeToFile(outputFileName, cleanContent)) {
        reportError(Error::createOutputFileError(outputFileName));
    }

    cout << "Обработка завершена. Результат сохранён в " << outputFileName << endl;
    return 0;
}
