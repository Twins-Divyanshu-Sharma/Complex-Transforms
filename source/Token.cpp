#include "Token.h"

Token::Token(char c)
{
    if(c == '+')
       type = add;
    else if(c == '-')
        type = sub;
    else if(c == '*')
        type = mul;
    else if(c == '/')
        type = div_;
    else if(c == '=')
        type = eq_;
    else if(c == '$')
        type = $;
    else if(c == '(')
        type = bracky_l;
    else if(c == ')')
        type = bracky_r;
}

Token::Token()
{}

int Token::getType()
{
    return type;
}

