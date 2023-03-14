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
                         "# repeated two-var selects\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "\n"
                         "  a(x,y,z,w)\n"
                         "  b(x,y,z,w,v)\n"
                         "\n"
                         "Facts:\n"
                         "\n"
                         "  a('1','2','3','4').\n"
                         "  a('3','2','4','1').\n"
                         "  a('2','2','4','4').\n"
                         "  a('2','2','4','4').\n"
                         "  a('4','2','3','2').\n"
                         "  a('4','4','4','4').\n"
                         "  a('2','2','2','2').\n"
                         "  a('4','4','2','2').\n"
                         "\n"
                         "  b('1','2','3','4','5').\n"
                         "  b('5','2','2','4','2').\n"
                         "  b('3','4','3','4','3').\n"
                         "  b('2','1','2','1','2').\n"
                         "  b('2','1','2','1','2').\n"
                         "  b('2','2','4','4','4').\n"
                         "  b('2','2','4','2','2').\n"
                         "\n"
                         "Rules:\n"
                         "\n"
                         "Queries:\n"
                         "\n"
                         "  a(x,x,x,x)?\n"
                         "  a(x,x,y,y)?\n"
                         "  a(x,y,x,y)?\n"
                         "  a(A,B,B,A)?\n"
                         "  a(x,x,'1',x)?\n"
                         "  a(x,'2',x,x)?\n"
                         "\n"
                         "  b(x,x,x,x,x)?\n"
                         "  b(x,y,x,y,x)?\n"
                         "  b(x,x,x,z,z)?\n"
                         "  b(z,z,x,z,z)?\n"
                         "  b(x,x,z,z,z)?\n"
                         "  b(x,z,z,z,z)?\n"
                         "  b(x,x,'4',x,x)?\n"
                         "  b(x,'2',x,'2',x)?\n"
                         "\n"
                         "";
    /*string inputFileName = argv[1];
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
