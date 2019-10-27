#ifndef TAKEN_ID_H
#define TAKEN_ID_H

#include "Token.h"
#include <string>

class Token_id : public Token
{
    private:
        std::string lexeme;
        float r, i;

    public:
        Token_id(std::string);
        std::string getLex();
        void setValues(float r, float i);
};
#endif
