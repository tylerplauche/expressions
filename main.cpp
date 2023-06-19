#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <map>
#include <vector>
#include "ExpressionManager.h"
#include "ExpressionManagerInterface.h"
using namespace std;


#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

/*map<char, int> opPrecedence = { {'(', 0},
                                {'+', 1},
                                {'-', 1},
                                {'*', 2},
                                {'/', 2},
                                {'%', 2} };*/

using namespace std;

int main(int argc, char *argv[]) {
    VS_MEM_CHECK
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    vector<string> myExps;
    ExpressionManager<string> expressionManager;
    vector<string>::iterator iter = myExps.begin();
    //cout << *iter;

    string line, command,expString;
    while (getline(in, line))
    {
        try
        {
            if (line.size() == 0) continue;
            istringstream iss(line);
            iss >> command;
            if (command == "Expression:")
            {
                out << endl << line;
                expString = line.erase(0, 11);
                myExps.push_back(expString);
                iter = myExps.begin();
            }
            else if (command == "Infix:")
            {
                out << endl << command << " " << expressionManager.Infix(expString);
            }
            else if (command == "Postfix:")
            {
                out << endl << command << " ";
                out << expressionManager.postfix(expString);

            }
            else if (command == "Prefix:")
            {
                out << endl << command << " ";
            }
            else if (command == "Value:")
            {
                out << endl << command << " ";
                out << expressionManager.Value(expressionManager.postfix(expString));
                out << endl;
            }

        }
        catch (const string &s) { out << s << endl; }
        ++iter;
        myExps.clear();
    }


    return 0;
}