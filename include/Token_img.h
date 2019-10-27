#ifndef IMAGINARY_TAKEN
#define IMAGINARY_TAKEN

#include "Token.h"

class Token_img : public Token
{
    private:
        float value;
    public:
        Token_img(float val);
        float getVal();
};
#endif
