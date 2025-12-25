#include "compileTypes.hpp"
#include "replacer.hpp"
#include <iostream>
enum class CompileType {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

CompileType getCompileType(const str& typeStr) {
    if (typeStr == "-a") return CompileType::A;
    if (typeStr == "-b") return CompileType::B;
    if (typeStr == "-c") return CompileType::C;
    if (typeStr == "-d") return CompileType::D;
    if (typeStr == "-e") return CompileType::E;
    if (typeStr == "-f") return CompileType::F;
    if (typeStr == "-g") return CompileType::G;
    if (typeStr == "-h") return CompileType::H;
    if (typeStr == "-i") return CompileType::I;
    if (typeStr == "-j") return CompileType::J;
    if (typeStr == "-k") return CompileType::K;
    if (typeStr == "-l") return CompileType::L;
    if (typeStr == "-m") return CompileType::M;
    if (typeStr == "-n") return CompileType::N;
    if (typeStr == "-o") return CompileType::O;
    if (typeStr == "-p") return CompileType::P;
    if (typeStr == "-q") return CompileType::Q;
    if (typeStr == "-r") return CompileType::R;
    if (typeStr == "-s") return CompileType::S;
    if (typeStr == "-t") return CompileType::T;
    if (typeStr == "-u") return CompileType::U;
    if (typeStr == "-v") return CompileType::V;
    if (typeStr == "-w") return CompileType::W;
    if (typeStr == "-x") return CompileType::X;
    if (typeStr == "-y") return CompileType::Y;
    if (typeStr == "-z") return CompileType::Z;
    throw std::invalid_argument("Unknown compile type: " + typeStr);
}

int main(int argc, char** argv) {
    str arg1 = argc >= 2 ? argv[1] : "";
    if(arg1 == "--help" || arg1 == "-h") {
        str help =
            "Compile usage: PMAKE -<type> <cmake file>\n"
            "Show usage: PMAKE -<type> <cmake file> -s\n"
            "Types:\n"
            "  -a : Compile type A\n"
            "  -b : Compile type B\n"
            "  -c : Compile type C\n"
            "and so on, up to -z\n";
        std::cout << help;
        return 0;
    }
    if (argc > 4) {
        std::cerr << "\u001b[31mUsage:\nCompile: PMAKE -<type> <cmake file>\nShow: PMAKE -<type> <cmake file> -s\u001b[0m" << "\n";
        return 1;
    }
    str fileContent = readFile(argv[2]);
    fileContent = replace_vars(fileContent);
    ListStr compileTypes = extractCompileType(fileContent);
    CompileType Type = getCompileType(arg1);
    
    short index = static_cast<short>(Type);

    if (argc == 4 && str(argv[3]) == "-s") {
        std::cout << "Compile command for " << arg1 << ":\n";
        std::cout << compileTypes[index] << "\n";
        return 0;
    }

    system(compileTypes[index].c_str());
    return 0;
}