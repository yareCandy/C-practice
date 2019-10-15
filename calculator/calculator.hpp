#ifndef Calculator_H
#define Calculator_H

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <stdexcept>

class Calculator
{
public:
    //定义错误类型
    class error:public std::logic_error
    {
    public:
        error(const std::string &s):std::logic_error(s){} 
    };

    //定义符号类型
    enum token{NUMBER, NAME, END, PLUS='+', MINUS='-', MUL='*', DIV='/', PRINT=';', ASSIGN='=', LB='(', RB=')'};

private:
    double expr(bool);
    double term(bool);
    double prim(bool);
    token getToken();

    std::istream *input;
    std::map<std::string,double> table;
    token curToken;
    double value;
    std::string stringValue;

public:
    void output(std::ostream &);
    Calculator(const std::string &);
    Calculator(std::istream &);
};

#endif