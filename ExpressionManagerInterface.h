#ifndef EXPRESSIONS_EXPRESSIONMANAGERINTERFACE_H
#define EXPRESSIONS_EXPRESSIONMANAGERINTERFACE_H
#include <string>

using namespace std;

//template<typename T>

class Interface
{
private:
public:
    Interface(void) {}
    virtual ~Interface(void) {}
    virtual string infix(void) = 0;
    virtual string postfix(void) = 0;
    virtual int value(void) = 0;
    virtual string prefix(void) = 0;
};
#endif //EXPRESSIONS_EXPRESSIONMANAGERINTERFACE_H
