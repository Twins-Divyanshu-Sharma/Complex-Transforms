/*
 * =====================================================================================
 *
 *       Filename:  Token_id.cpp
 *
 *    Description:  Drived class of Token
 *
 *        Version:  1.0
 *        Created:  09/18/2019 08:16:58 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  BRAHMIN TWINS (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Token_id.h"

Token_id::Token_id(std::string lex) : Token()
{
    lexeme = lex;
    type = id;
}

std::string Token_id::getLex()
{
    return lexeme;
}

void Token_id::setValues(float r, float i)
{
    this->r = r;
    this->i = i;
}
