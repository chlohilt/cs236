#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

int main() {

    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    pair<string,vector<string>> ruleNames[] = {
            { "A", { "B", "C" } },
            { "B", { "A", "D" } },
            { "B", { "B" } },
            { "E", { "F", "G" } },
            { "E", { "E", "F" } },
    };

    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Rule rule = Rule(Predicate(headName));
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames)
            rule.addBodyPredicate(Predicate(bodyName));
        rules.push_back(rule);
    }

    Graph graph = Interpreter::makeGraph(rules);
    Graph reverseGraph = graph.reverseDependencyGraph();
    cout << graph.toString();
    cout << "Reverse Dependency Graph" << endl;
    cout << reverseGraph.toString();
    stack<int> postOrder = reverseGraph.dfs();
    vector<vector<int>> scComponents = graph.dfsForestReversePostOrder(postOrder);

}


/*
int main(int argc, char** argv) {
    // file reading

    if (argc != 2) {
        return 1;
    }
    string inputString = "";
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
*/
