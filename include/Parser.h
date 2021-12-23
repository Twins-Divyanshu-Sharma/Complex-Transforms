#ifndef PAR_SEL
#define PAR_SEL

#include <map>
#include <string>
#include "Lexer.h"
#include "Node.h"

#define M 11
#define X 12
#define E 13
#define E_ 14
#define T 15
#define T_ 16
#define F 17
#define Y 18
#define H 19

class Parser
{
    private:

        typedef void (Parser::*prod_ptr)(void);
        
        std::string finalZ;
        std::string answer = "";

        struct Comp_lex
        {
            float r=1, i=0;
            std::string zString="null";
        };
        
        std::map<std::string,Comp_lex> symbolTable;
        Lexer* lex;     
        std::vector<Node> sstack;

        std::vector<std::string> variable;
        std::vector<int> brackySize;

        prod_ptr prod[19];
        int table[9][11];

        void fM();
        void fX0(); void fX1();
        void fE();
        void fE_0(); void fE_1(); void fE_2();
        void fT();
        void fT_0(); void fT_1(); void fT_2();
        void fF0(); void fF1(); void fF2(); void fF3();
        void fY0(); void fY1();
        void fH0(); void fH1();
        
        bool searchForString(std::string);
        void theMaker();

        std::string tempVariables();

    public:
        void initialize(std::string,Lexer*);
        void execute();
        std::string getans();

};
#endif
