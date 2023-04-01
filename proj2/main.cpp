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
                         "# joins: more than one common variable\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  c(x,y,z,w)\n"
                         "  d(x,y,z,w,v)\n"
                         "\n"
                         "  e(j,k,x,y,v,w,z)\n"
                         "  f(p,q,r,s,t,u)\n"
                         "  g(q,r,s,t,u)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  c('1','2','3','4').\n"
                         "  c('3','2','4','1').\n"
                         "  c('2','2','4','4').\n"
                         "  c('2','2','4','4').\n"
                         "  c('4','2','3','2').\n"
                         "\n"
                         "  d('1','2','3','4','5').\n"
                         "  d('5','2','2','4','2').\n"
                         "  d('3','4','3','4','3').\n"
                         "  d('2','1','2','1','2').\n"
                         "  d('2','1','2','1','2').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "  e(j,k,x,y,v,w,z) :- c(j,x,k,y), d(v,x,w,y,z).   # join on x,y\n"
                         "  f(w,x,y,z,j,k) :- c(x,y,z,w), d(j,x,y,z,k).     # join on x,y,z\n"
                         "  f(w,x,y,z,j,k) :- c(w,x,y,z), d(j,x,y,z,k).     # join on x,y,z\n"
                         "  f(w,z,x,y,j,k) :- c(z,x,y,w), d(j,x,y,z,k).     # join on x,y,z\n"
                         "  f(w,y,x,z,j,k) :- c(y,x,w,z), d(j,z,k,y,x).     # join on x,y,z\n"
                         "  g(z,y,x,w,k) :- c(z,y,x,w), d(w,x,y,z,k).       # join on w,x,y,z\n"
                         "  g(y,x,z,w,k) :- c(y,x,z,w), d(w,x,y,z,k).       # join on w,x,y,z\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  c(x,y,z,w)?\n"
                         "  d(x,y,z,w,v)?\n"
                         "\n"
                         "  e(j,k,x,y,v,w,z)?\n"
                         "  f(p,q,r,s,t,u)?\n"
                         "  g(q,r,s,t,u)?\n"
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
