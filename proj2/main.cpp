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
                         "# dependency cycle with one rule\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x,y)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1','2').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "  a(x,y) :- a(y,x).\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x,y)?\n"
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

