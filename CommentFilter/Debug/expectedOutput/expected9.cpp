#include <iostream>

int main() {
    std::string quote = "Это строка с экранированной кавычкой: \\\" и всё ещё строка";
    std::cout << quote << std::endl;
    return 0;
}