/*
 * =====================================================================================
 *
 *       Filename:  Token_real.cpp
 *
 *    Description:  Drived class of Token. Stores real value
 *
 *        Version:  1.0
 *        Created:  09/18/2019 09:23:01 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  BRAHMIN TWINS (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Token_real.h"

Token_real::Token_real(float val) : Token()
{
   value = val;
   type = real_;
}

float Token_real::getVal()
{
    return value;
}
