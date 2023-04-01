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
                         "# larger input, snoopy example\n"
                         "\n"
                         "\n"
                         "Schemes:\n"
                         "   snap(s,n,a,p)\n"
                         "   csg(c,s,g)\n"
                         "   cp(c,q)\n"
                         "   cdh(x,y,z)\n"
                         "   cr(x,y)\n"
                         "   before(cc1,cc2)\n"
                         "   mwfCourses(c,r)\n"
                         "   Schedule(n,c,r,d,h)\n"
                         "   Grades(n,c,g)\n"
                         "   Roll(c,r,n,s,g)\n"
                         "\n"
                         "Facts:\n"
                         "   snap('1234','Charley','Apple St','555-1234'). \n"
                         "   snap('1111','Linus','Piano St','555-1111'). \n"
                         "   snap('1212','Lucy','Home Ln','555-1212'). \n"
                         "   snap('3333','Marcie','Banana St','555-3333'). \n"
                         "   snap('5678','Patty','Grape Blvd','555-5678').\n"
                         "   snap('7890','Pig Pen','Pear Ave','555-7890').\n"
                         "   snap('4321','Rerun','Peach St','555-4321'). \n"
                         "   snap('4444','Sally','Circle Dr','555-4444').\n"
                         "   snap('9876','Snoopy','Doghouse','555-9876').\n"
                         "   snap('0000','Woodstock','Treehouse','555-0000').\n"
                         "   csg('CS101','1234','A').\n"
                         "   csg('CS101','3333','B').\n"
                         "   csg('CS101','5678','B-').\n"
                         "   csg('CS101','4444','B').\n"
                         "   csg('CS101','0000','A-').\n"
                         "   csg('CS101','1212','A-').\n"
                         "   csg('EE200','1234','C').\n"
                         "   csg('EE200','3333','B').\n"
                         "   csg('EE200','7890','C').\n"
                         "   csg('EE200','4444','C').\n"
                         "   csg('EE200','9876','B+').\n"
                         "   csg('EE200','0000','B').\n"
                         "   csg('PH100','7890','C+').\n"
                         "   csg('PH100','9876','C+').\n"
                         "   csg('PH100','5678','C+').\n"
                         "   csg('PH100','4321','C+'). \n"
                         "   csg('PH100','0000','A').\n"
                         "   cp('CS101','CS100').\n"
                         "   cp('EE200','EE005').\n"
                         "   cp('EE200','CS100').\n"
                         "   cp('CS120','CS101').\n"
                         "   cp('CS121','CS120').\n"
                         "   cp('CS205','CS101').\n"
                         "   cp('CS206','CS121').\n"
                         "   cp('CS206','CS205').\n"
                         "   cdh('CS101','Tu','10AM').\n"
                         "   cdh('EE200','M','10AM').\n"
                         "   cdh('EE200','W','1PM').\n"
                         "   cdh('EE200','F','10AM').\n"
                         "   cdh('PH100','Tu','11AM').\n"
                         "   cr('CS101','Study').\n"
                         "   cr('EE200','Hall').\n"
                         "   cr('PH100','Lab').\n"
                         "\n"
                         "Rules:\n"
                         "   before(C1,C2):-cp(C2,C1).\n"
                         "   before(C1,C2):-cp(C3,C1),before(C3,C2).\n"
                         "   mwfCourses(C,R):-cdh(C,'M',H),cr(C,R).\n"
                         "   mwfCourses(C,R):-cdh(C,'W',H),cr(C,R).\n"
                         "   mwfCourses(C,R):-cdh(C,'F',H),cr(C,R).\n"
                         "   Schedule(N,C,R,D,H):-snap(S,N,A,P),csg(C,S,G),cr(C,R),cdh(C,D,H).\n"
                         "   Grades(N,C,G):-snap(S,N,A,P),csg(C,S,G).\n"
                         "   Roll(C,R,N,S,G):-snap(S,N,A,P),csg(C,S,G),cr(C,R).\n"
                         "\n"
                         "Queries: \n"
                         "   snap(S,N,A,P)? \n"
                         "   snap(Id,'Snoopy',Address,Phone)?\n"
                         "   csg(Course,'33333',Grade)?\n"
                         "   cp(Course,'CS100')?\n"
                         "   cdh('EE200',Day,Hour)?\n"
                         "   cr('CS101',Room)? \n"
                         "   mwfCourses (Course,Room)?\n"
                         "   Schedule('Snoopy',Course,Room,Day,Hour)?\n"
                         "   Grades('Snoopy',Course,Grade)? \n"
                         "   Grades('Woodstock',Course,Grade)?\n"
                         "   Roll('CS101',Room,Name,Id,Grade)? \n"
                         "   Roll('EE200',Room,Name,Id,Grade)? \n"
                         "   Roll('PH100',Room,Name,Id,Grade)?\n"
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
