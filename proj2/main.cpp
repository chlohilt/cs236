#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "Interpreter.h"


int main(int argc, char** argv) {
    // file reading

    if (argc != 2) {
        return 1;
    }
    string inputString = "\n"
                         "\n"
                         "# one simple rule\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x)\n"
                         "  b(y)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1').\n"
                         "  a('2').\n"
                         "  a('4').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "  b(y) :- a(y).\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x)?\n"
                         "  b(y)?\n"
                         "\n"
                         "";
    string inputFileName = argv[1];
    ifstream input(inputFileName);

/*    while (input.peek() != EOF) {
        inputString += input.get();
    }
    input.close();*/

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
