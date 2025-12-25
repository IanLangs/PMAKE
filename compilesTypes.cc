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
        regex(R"(-c\n([^\n]+))"),
        regex(R"(-d\n([^\n]+))"),
        regex(R"(-e\n([^\n]+))"),
        regex(R"(-f\n([^\n]+))"),
        regex(R"(-g\n([^\n]+))"),
        regex(R"(-h\n([^\n]+))"),
        regex(R"(-i\n([^\n]+))"),
        regex(R"(-j\n([^\n]+))"),
        regex(R"(-k\n([^\n]+))"),
        regex(R"(-l\n([^\n]+))"),
        regex(R"(-m\n([^\n]+))"),
        regex(R"(-n\n([^\n]+))"),
        regex(R"(-o\n([^\n]+))"),
        regex(R"(-p\n([^\n]+))"),
        regex(R"(-q\n([^\n]+))"),
        regex(R"(-r\n([^\n]+))"),
        regex(R"(-s\n([^\n]+))"),
        regex(R"(-t\n([^\n]+))"),
        regex(R"(-u\n([^\n]+))"),
        regex(R"(-v\n([^\n]+))"),
        regex(R"(-w\n([^\n]+))"),
        regex(R"(-x\n([^\n]+))"),
        regex(R"(-y\n([^\n]+))"),
        regex(R"(-z\n([^\n]+))")
    };

    std::smatch match;
    auto searchStart = fileContent.cbegin();

    for (const auto& re : patterns) {
        if (std::regex_search(searchStart, fileContent.cend(), match, re)) {
            compiles.push_back(match[match.size() -1].str());
            searchStart = match.suffix().first;
        } else {
            compiles.push_back("null");
        }
    }

    return compiles;
}

