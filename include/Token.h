#ifndef TAKEN
#define TAKEN

#include <iostream>

#define id 0
#define $ 1
#define img 2
#define real_ 3
#define add 4
#define sub 5
#define mul 6
#define div_ 7
#define eq_ 8
#define bracky_l 9
#define bracky_r 10

class Token
{
    private:
    protected:
        int type;
    public:
        Token();
        Token(char);
        int getType(); 

};
#endif
