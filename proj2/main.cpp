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
                         "# single params, only constants\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "A(X)\n"
                         "B(Y)\n"
                         "C(Z)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "A('1').\n"
                         "A('2').\n"
                         "\n"
                         "B('2').\n"
                         "B('3').\n"
                         "\n"
                         "C('').\n"
                         "C('4').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "A('2')?\n"
                         "B('4')?\n"
                         "C('')?\n"
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
