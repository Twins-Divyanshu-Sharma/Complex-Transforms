/*
 * =====================================================================================
 *
 *       Filename:  Token_img.cpp
 *
 *    Description:  Drived class of Token. Stores imaginary value
 *
 *        Version:  1.0
 *        Created:  09/18/2019 09:16:44 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  BRAHMIN TWINS (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Token_img.h"

Token_img::Token_img(float val) : Token()
{
    value = val;
    type = img;
}

float Token_img::getVal()
{
    return value;
}
