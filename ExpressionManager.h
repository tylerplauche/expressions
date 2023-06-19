
#ifndef EXPRESSIONS_EXPRESSIONMANAGER_H
#define EXPRESSIONS_EXPRESSIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "ExpressionManagerInterface.h"
using namespace std;

template<typename T>
class ExpressionManager{
private:

public:
    ExpressionManager(){}
    ~ExpressionManager(){}

    map<char, int> opPrecedence = {
            {'(', 0},
            {'{', 0},
            {'[', 0},
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2},
            {'%', 2}
    };

    string Infix(const string& exp) {
        string Infix = "";
        int opCount = 0, cpCount = 0;
        int obCount = 0, cbCount = 0;
        int osCount = 0, csCount = 0;
        string::const_iterator iter = exp.cbegin();
        try {
            while (iter != exp.cend()) {

                char myChar = *iter++;
                switch (myChar) {
                    case ' ':
                        break;

                    case '(':
                        Infix += myChar;
                        Infix += " ";
                        opCount++;
                        break;
                    case ')':
                        Infix += myChar;
                        Infix += " ";
                        cpCount++;
                        break;
                    case '[':
                        Infix += myChar;
                        Infix += " ";
                        obCount++;
                        break;
                    case ']':
                        Infix += myChar;
                        Infix += " ";
                        cbCount++;
                        break;
                    case '{':
                        Infix += myChar;
                        Infix += " ";
                        osCount++;
                        break;
                    case '}':
                        Infix += myChar;
                        Infix += " ";
                        csCount++;
                        break;
                    default:
                        Infix += myChar;
                        if (isdigit(myChar && isdigit(*iter)))
                        {
                            throw string("Missing operator");
                        }

                        if (!isdigit(*iter)) {
                            Infix += " ";
                        }
                        break;
                }
            }
            if (opCount != cpCount || obCount != cbCount || osCount != csCount )
            {
                throw string("Unbalanced");
            }
            else {
                return Infix;
            }

        }
        catch (const string &s) { return s; }
    }

    string postfix(const string& exp)
    {
        string postfix = "";
        stack<char> opStack;
        char expression;
        string::const_iterator iter = exp.cbegin();
        while (iter != exp.cend())
        {
            istringstream temp(exp);
            temp >> expression;
            char myChar = *iter++;
            switch (myChar)
            {
                case '+':
                    while (!opStack.empty() && (opPrecedence[myChar] <= opPrecedence[opStack.top()]))
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.push(myChar);
                    break;
                case '-':
                    while (!opStack.empty() && (opPrecedence[myChar] <= opPrecedence[opStack.top()]))
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.push(myChar);
                    break;
                case '*':
                    while (!opStack.empty() && (opPrecedence[myChar] <= opPrecedence[opStack.top()]))
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.push(myChar);
                    break;
                case '/':
                    while (!opStack.empty() && (opPrecedence[myChar] <= opPrecedence[opStack.top()]))
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.push(myChar);
                    break;
                case '(':
                    opStack.push(myChar);
                    break;
                case '[':
                    opStack.push(myChar);
                    break;
                case '{':
                    opStack.push(myChar);
                    break;

                case ')':
                    while (opStack.top() != '(')
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.pop();
                    break;
                case ']':
                    while (opStack.top() != '[')
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.pop();
                    break;
                case '}':
                    while (opStack.top() != '{')
                    {
                        postfix += opStack.top();
                        postfix += " ";
                        opStack.pop();
                    }
                    opStack.pop();
                    break;

                case ' ':
                    break;

                default:
                    // send operands to posfix
                    postfix += myChar;
                    if (!isdigit(*iter)){
                        postfix += " ";
                    }
                    break;
            }
        }
        // pop all operators off stack
        while (!opStack.empty())
        {
            postfix += opStack.top();
            postfix += " ";
            opStack.pop();
        }
        return postfix;
    }

    int Value(const string& exp)
    {
        stack<int> myStack;
        string::const_iterator iter = exp.cbegin();
        string temp;
        while (iter != exp.cend())
        {
            char ch = *iter++;
            if (isdigit(*iter) && isdigit(ch))
            {
                temp = string(1,ch) + *iter++;
                int itoc = stoi(temp);

                if(!isdigit(*iter))
                {
                    myStack.push(itoc);
                }
                else if (isdigit(*iter))
                {
                    temp = temp + *iter;
                    int itoc = stoi(temp);
                    myStack.push(itoc);
                }

                continue;
            }
            switch (ch)
            {
                case '+':
                {
                    int rhs = myStack.top();
                    myStack.pop();
                    int lhs = myStack.top();
                    myStack.pop();
                    myStack.push(lhs + rhs);
                    break;
                }

                case '*':
                {
                    int rhs = myStack.top();
                    myStack.pop();
                    int lhs = myStack.top();
                    myStack.pop();
                    myStack.push(lhs * rhs);
                    break;
                }

                case '-':
                {
                    int rhs = myStack.top();
                    myStack.pop();
                    int lhs = myStack.top();
                    myStack.pop();
                    myStack.push(lhs - rhs);
                    break;
                }

                case '/':
                {
                    int rhs = myStack.top();
                    myStack.pop();
                    int lhs = myStack.top();
                    myStack.pop();
                    myStack.push(lhs / rhs);
                    break;
                }

                case ' ':
                    break;

                default:
                    myStack.push(ch - '0');
                    break;
            }
        }
        return myStack.empty() ? 0 : myStack.top();
    }

};
#endif //EXPRESSIONS_EXPRESSIONMANAGER_H
