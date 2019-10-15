#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <stdexcept>
#include "calculator.hpp"

//构造函数与构造函数的重载
Calculator::Calculator(const std::string &s)
    :input(new std::istringstream(s)), curToken(PRINT)
{
    table["pie"] = 3.1415926; 
    table["e"] = 2.718218;
}

Calculator::Calculator(std::istream &s)
    :input(&s), curToken(PRINT)
{
    table["pie"] = 3.1415926; 
    table["e"] = 2.718218;
}

//
double Calculator::expr(bool get)
{
	double left=term(get);
	while(true)
    	switch(curToken){
    	case PLUS:
    	    left+=term(true);
    	    break;
        case MINUS:
            left-=term(true);
            break;
        default:
            return left;
    	}
}

double Calculator::term(bool get)
{
	double left=prim(get);
	while(true)
    	switch(curToken){
    	case MUL:
    	    left*=prim(true);
    	    break;
        case DIV:
            if(double d=prim(true)){
                left/=d;
                break;
            }
            throw error("divide by 0");
        default:
            return left;
    	}
}

double Calculator::prim(bool get)
{
	if(get) getToken();
	
	switch(curToken){
	case NUMBER:
	{
	    double v=value;
	    getToken();
	    return v;
	}
    case NAME:
	{
        double &v=table[stringValue];
        if(getToken()==ASSIGN) v=expr(true);
        return v;
    }
    case MINUS:
        return -prim(true);
    case LB:{
        double e = expr(true);
        if(curToken!=RB) throw error(") expected");
        getToken();//吃掉 )
		return e;}
	default:
	    throw error("primary expected");
	}
}

Calculator::token Calculator::getToken()
{
    char ch;
    do{
        if(!input->get(ch)) return curToken=END;
    }while(ch!='\n' && isspace(ch));

    switch(ch)
    {
        case ';':
        case '\n':return curToken = PRINT;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=': return curToken = token(ch);
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '.':
            input ->putback(ch);
            input ->operator >>(value);
            return curToken = NUMBER;
        default:
            if(isspace(ch))
            {
                stringValue = ch;
                while(input ->get(ch) && isalnum(ch))
                    stringValue.push_back(ch);
                input ->putback(ch);
                return curToken=NAME;
            }
            curToken = PRINT;
            throw(error("bad token"));
    }
}

void Calculator::output(std::ostream &)
{
    while(*input)
    {
        getToken();
        if(curToken == END) break;
        if(curToken == PRINT) continue;
        std::cout << expr(false) << std::endl;
    }
}