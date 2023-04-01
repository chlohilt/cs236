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
                         "# constants in rule body, double vars in rule body\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x,y,z,w)\n"
                         "  b(x,y,z,w,v)\n"
                         "\n"
                         "  c(x,y,z)\n"
                         "  d(x,y,z)\n"
                         "  e(x,y,z,w)\n"
                         "  f(x,y)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1','2','3','4').\n"
                         "  a('3','2','4','1').\n"
                         "  a('2','2','4','4').\n"
                         "  a('2','2','4','4').\n"
                         "  a('4','2','3','2').\n"
                         "\n"
                         "  b('1','2','3','4','5').\n"
                         "  b('5','2','2','4','2').\n"
                         "  b('3','4','3','4','3').\n"
                         "  b('2','1','2','1','2').\n"
                         "  b('2','1','2','1','2').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "  c(z,w,x) :- a(w,x,'4',z).\n"
                         "  d(v,z,x) :- b(v,'2',x,'4',z).\n"
                         "  e(x,w,v,y) :- b(v,w,x,y,'2').\n"
                         "  f(x,y) :- b(x,y,x,y,x).\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x,y,z,w)?\n"
                         "  b(x,y,z,w,v)?\n"
                         "\n"
                         "  c(x,y,z)?\n"
                         "  d(x,y,z)?\n"
                         "  e(x,y,z,w)?\n"
                         "  f(x,y)?\n"
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
