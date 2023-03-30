#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"


int main(int argc, char** argv) {
    // file reading

    if (argc != 2) {
        return 1;
    }
    string inputString = "\n"
                         "\n"
                         "# project without re-order, no joins\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x,y)\n"
                         "  b(x,y,z)\n"
                         "\n"
                         "  c(x)\n"
                         "  d(x)\n"
                         "  e(x)\n"
                         "\n"
                         "  f(x,y)\n"
                         "  g(x,y)\n"
                         "  h(x,y)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1','4').\n"
                         "  a('2','4').\n"
                         "  a('2','5').\n"
                         "\n"
                         "  b('5','4','7').\n"
                         "  b('5','4','8').\n"
                         "  b('6','4','8').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "  c(x) :- a(x,y).\n"
                         "  d(y) :- b(x,y,z).\n"
                         "  e(z) :- b(x,y,z).\n"
                         "\n"
                         "  f(x,y) :- b(x,y,z).\n"
                         "  g(x,z) :- b(x,y,z).\n"
                         "  h(y,z) :- b(x,y,z).\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x,y)?\n"
                         "  b(x,y,z)?\n"
                         "\n"
                         "  c(x)?\n"
                         "  d(x)?\n"
                         "  e(x)?\n"
                         "\n"
                         "  f(x,y)?\n"
                         "  g(x,y)?\n"
                         "  h(x,y)?\n"
                         "\n"
                         "";
    string inputFileName = argv[1];
    ifstream input(inputFileName);

    while (input.peek() != EOF) {
        inputString += input.get();
    }
    input.close();

    Scanner s = Scanner(inputString);
    queue<Token> tokens = s.mainScanner();

    try {
        Parser p = Parser(tokens);
        auto datalogProgram = p.datalogProgram();
        auto interpreter = Interpreter(datalogProgram);

    } catch (Token t) {
        cout << "Failure!" << endl;
        cout << "  " << t.toString() << endl;
    }

    return 0;
}
