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
        regex(R"(-a\n?\s*([^\n]+))"),
        regex(R"(-b\n?\s*([^\n]+))"),
        regex(R"(-c\n?\s*([^\n]+))"),
        regex(R"(-d\n?\s*([^\n]+))"),
        regex(R"(-e\n?\s*([^\n]+))"),
        regex(R"(-f\n?\s*([^\n]+))"),
        regex(R"(-g\n?\s*([^\n]+))"),
        regex(R"(-h\n?\s*([^\n]+))"),
        regex(R"(-i\n?\s*([^\n]+))"),
        regex(R"(-j\n?\s*([^\n]+))"),
        regex(R"(-k\n?\s*([^\n]+))"),
        regex(R"(-l\n?\s*([^\n]+))"),
        regex(R"(-m\n?\s*([^\n]+))"),
        regex(R"(-n\n?\s*([^\n]+))"),
        regex(R"(-o\n?\s*([^\n]+))"),
        regex(R"(-p\n?\s*([^\n]+))"),
        regex(R"(-q\n?\s*([^\n]+))"),
        regex(R"(-r\n?\s*([^\n]+))"),
        regex(R"(-s\n?\s*([^\n]+))"),
        regex(R"(-t\n?\s*([^\n]+))"),
        regex(R"(-u\n?\s*([^\n]+))"),
        regex(R"(-v\n?\s*([^\n]+))"),
        regex(R"(-w\n?\s*([^\n]+))"),
        regex(R"(-x\n?\s*([^\n]+))"),
        regex(R"(-y\n?\s*([^\n]+))"),
        regex(R"(-z\n?\s*([^\n]+))")
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

