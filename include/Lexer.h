#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <iostream>
#include "OneToken.h"
#define digit 0
#define letter_i 1
#define _i 2
#define dot 3
#define ws 4
#define op 5

class Lexer
{
    private:
        int countLine;
    public:
        std::vector<Token*> tokens;
        int getLine();
        void pass(std::string);
        void show();
};

#endif
