#ifndef COMMENT_FILTER_H
#define COMMENT_FILTER_H

#include <string>

/**
 * @brief Represents the finite automaton states for text parsing.
 */
enum State {
    NORMAL,             ///< Normal code, outside comments and strings
    MULTILINE_COMMENT,  ///< Inside a multiline comment (/* ... */)
    SINGLELINE_COMMENT, ///< Inside a single-line comment (// ...)
    STRING_LITERAL      ///< Inside a string literal ("...")
};

/**
 * @brief Defines the types of errors the program can report.
 */
enum ErrorType {
    INVALID_INPUT_FORMAT,    ///< Invalid input format (e.g. use of #define)
    INPUT_FILE_ERROR,        ///< Failed to open input file
    OUTPUT_FILE_ERROR,       ///< Failed to write or create output file
    NOT_ENOUGH_ARGUMENTS,    ///< Not enough command-line arguments provided
    TOO_MANY_ARGUMENTS       ///< Too many command-line arguments provided
};

/**
 * @brief Structure for detailed error representation.
 */
struct Error {
    ErrorType type;       ///< The type of the error
    int line_num;         ///< Line number (optional, -1 if unknown)
    int col_num;          ///< Column number (optional, -1 if unknown)
    char symbol;          ///< Related symbol (optional)
    std::string message;  ///< Error message

     /**
     * @brief Constructs an error with optional details.
     * @param t The error type
     * @param msg The error message
     * @param line Line number (optional)
     * @param col Column number (optional)
     * @param sym Offending symbol (optional)
     */
    Error(ErrorType t, const std::string& msg = "", int line = -1, int col = -1, char sym = '\0')
        : type(t), line_num(line), col_num(col), symbol(sym), message(msg) {}

    /// Factory method for invalid input format errors
    static Error createInvalidInputError(int line = -1, int col = -1, char sym = '\0') {
        return Error(INVALID_INPUT_FORMAT, "Неверный формат входных данных", line, col, sym);
    }

    /// Factory method for input file opening errors
    static Error createInputFileError(const std::string& filename) {
        return Error(INPUT_FILE_ERROR, "Не удалось открыть входной файл: " + filename);
    }

    /// Factory method for output file writing errors
    static Error createOutputFileError(const std::string& filename) {
        return Error(OUTPUT_FILE_ERROR, "Не удалось создать выходной файл: " + filename);
    }

    /// Factory method for not enough command-line arguments
    static Error createNotEnoughArgumentsError() {
        return Error(NOT_ENOUGH_ARGUMENTS, "Недостаточно аргументов командной строки");
    }

    /// Factory method for too many command-line arguments
    static Error createTooManyArgumentsError() {
        return Error(TOO_MANY_ARGUMENTS, "Слишком много аргументов командной строки");
    }
};

/**
 * @brief Reports an error and exits the program with a corresponding code.
 * @param error Error object to report
 */
void reportError(const Error& error);

/**
 * @brief Reads the contents of a text file into a string.
 * @param filename Path to the file
 * @param content Output parameter to receive the file contents
 * @return true if successful, false otherwise
 */
bool readFromFile(const std::string& filename, std::string& content);

/**
 * @brief Writes the given text content to a file.
 * @param filename Path to the output file
 * @param content The content to write
 * @return true if successful, false otherwise
 */
bool writeToFile(const std::string& filename, const std::string& content);

/**
 * @brief Removes multiline comments from C++ source text.
 *        Preserves string literals and single-line comments.
 * @param text The input source code
 * @return The processed code without multiline comments
 */
std::string removeMultilineCommentsFromText(const std::string& text);

#endif

