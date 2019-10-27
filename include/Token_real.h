#ifndef REAL_TAKEN
#define REAL_TAKEN

#include "Token.h"

class Token_real : public Token
{
    private:
        float value;
    public:
        Token_real(float);
        float getVal();
};
#endif
