#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Database.h"
#include "Interpreter.h"

/*
int main() {

    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();

}
 */

int main(int argc, char** argv) {
    // file reading

    if (argc != 2) {
        return 1;
    }
    string inputString = "\n"
                         "\n"
                         "# one, two, three param predicates, with vars, some renames\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x)\n"
                         "  b(x,y)\n"
                         "  c(x,y,z)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1').\n"
                         "  a('4').\n"
                         "  a('2').\n"
                         "\n"
                         "  b('1','2').\n"
                         "  b('2','2').\n"
                         "  b('2','1').\n"
                         "\n"
                         "  c('2','2','2').\n"
                         "  c('4','2','1').\n"
                         "  c('1','2','4').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x)?\n"
                         "\n"
                         "  b(x,y)?\n"
                         "  b(x,'2')?\n"
                         "  b(x,'4')?\n"
                         "  b('2',y)?\n"
                         "  b('4',y)?\n"
                         "\n"
                         "  c(x,y,z)?\n"
                         "  c(x,y,'2')?\n"
                         "  c(x,'1',z)?\n"
                         "  c(x,'2',z)?\n"
                         "  c('4',y,z)?\n"
                         "  c('4','2',z)?\n"
                         "\n"
                         "  a(a)?\n"
                         "  b(a,b)?\n"
                         "  c(a,b,c)?\n"
                         "\n"
                         "";
    //string inputFileName = argv[1];
    /*string inputFileName = "input.txt";
    ifstream input(inputFileName);

    while (input.peek() != EOF) {
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
