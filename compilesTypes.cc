#include "compileTypes.hpp"
#include <regex>
#include <vector>
#include <fstream>

str readFile(const str& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    return str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

ListStr extractCompileType(const str& fileContent) {
    ListStr compiles;

    const std::regex patterns[] = {
        regex(R"(-a\n([^\n]+))"),
        regex(R"(-b\n([^\n]+))"),
        regex(R"(-c\n([^\n]+))")
    };

    std::smatch match;
    auto searchStart = fileContent.cbegin();

    for (const auto& re : patterns) {
        if (std::regex_search(searchStart, fileContent.cend(), match, re)) {
            compiles.push_back(match[1].str());
            searchStart = match.suffix().first;
        } else {
            compiles.push_back("null");
        }
    }

    return compiles;
}

