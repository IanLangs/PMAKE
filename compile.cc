#include "compileTypes.hpp"

enum class CompileType {
    A,
    B,
    C
};

CompileType getCompileType(const str& typeStr) {
    if (typeStr == "-a") return CompileType::A;
    if (typeStr == "-b") return CompileType::B;
    if (typeStr == "-c") return CompileType::C;
    throw std::invalid_argument("Unknown compile type: " + typeStr);
}

int main(int argc, char** argv) {
    if (argc != 3) throw std::runtime_error("Usage: PMAKE -<type> <cmake file>");
    str fileContent = readFile(argv[2]);
    ListStr compileTypes = extractCompileType(fileContent);
    CompileType Type = getCompileType(argv[1]);
    
    switch (Type) {
        case CompileType::A:
            system(compileTypes[0].c_str());
            break;
        case CompileType::B:
            system(compileTypes[1].c_str());
            break;
        case CompileType::C:
            system(compileTypes[2].c_str());
            break;
    }
    return 0;
}