/*
 * =====================================================================================
 *
 *       Filename:  Lexer.cpp
 *
 *    Description:  The Lexer
 *
 *        Version:  1.0
 *        Created:  09/18/2019 09:30:56 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  BRAHMIN TWINS (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Lexer.h"

void Lexer::pass(std::string& line)
{
    line = line + " ";
    int state = 0;
    int x = 0;
    int input = 0; 
    int lexStart = 0;
    int num=0, tens=1;
    float decinum = 0;
    Token* t;
    parsable = true;
    while( x < line.size())
    {
        char c = line[x];

        if(c == 'i')
            input = _i;
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=' )
            input = op;
        else if(c >= 'a' && c <= 'z')
            input = letter_i;
        else if(c >= 'A' && c <= 'Z')
            input = letter_i;
        else if(c >= '0' && c <= '9')
            input = digit;
        else if(c == ' ')
            input = ws;
        else if(c == '.')
            input = dot;
        else if(c == '$')
            state = 12;
        else
        {
            std::cout << "Invalid character ["<<line[x]<<"] at line "<<countLine<<" parser dont recognise this character "<<std::endl;
            state = 13; 
            parsable = false;
        }

       // std::cout << "state is " << state << std::endl;
        switch(state)
        {
            case 0:
                if(input == digit)
                {
                    num *= 10;
                    num = num + c - 48;
                   //std::cout <<"("<< c << " "<< num<<")";
                    state = 1;
                }
                else if(input == _i)
                {
                    state = 5;
                }
                else if(input == letter_i)
                {
                    state = 9;
                }
                else if(input == op)
                {
                    state = 10;
                }
                else if(input == ws)
                {
                    state = 11;
                }
                else
                {
                    std::cerr << "Error : The compiler dont recognise the character "<<line[x]<<" at line "<<countLine<<std::endl;
                    state = 13;
                }
                break;

            case 1 :
                if(input == digit)
                {
                      num *= 10;
                    num = num + c - 48;
                                      
                    state = 1;
                }
                else if(input == dot)
                {
                    state = 2;
                }
                else if(input == _i)
                {
                    state = 4;
                }
                else
                {
                    state = 0;
                    lexStart = x--; //retract as well
                    t = new Token_real(num);
                    tokens.push_back(t);
                    num = 0;
                }
                break;
                
            case 2:
                if(input == digit)
                {
                     decinum *= 10;
                    decinum = decinum + c - 48;
                   state = 3;
                    tens *=10;
                }
                else
                {
                    std::cerr << " Error: Expected only digits after a decimal point at line "<<countLine<<std::endl;
                    state = 13;
                }
                break;
                
            case 3:
                if(input == digit)
                {
                      decinum *= 10;
                    decinum = decinum + c - 48;
                   
                    state = 3;
                    tens *= 10;
                }
                else
                {
                    decinum = decinum / tens;
                    
                    if(input == _i)
                        state = 4;
                    else
                    {
                        state = 0;
                        t = new Token_real((float)num + decinum);
                        lexStart = x--;
                        num = 0;
                        decinum = 0;
                        tens = 1;
                        tokens.push_back(t);
                    }
                }
                break;

            case 4:
                t = new Token_img((float)num + decinum);
                lexStart = x--;
                num = 0;
                decinum = 0;
                tens = 1;
                state = 0;
                tokens.push_back(t);
                break;

            case 5:
                if(input == letter_i)
                {
                    state = 9;
                }
                else if(input == digit)
                {
                    state = 6;
                      num *= 10;
                    num = num + c - 48;
                     
                }
                else
                {
                    std::cerr <<"error in line "<<countLine<<" unexpected character"<<std::endl;
                    state = 13;
                }
                break;
                
            case 6:
                if(input == dot)
                {
                    state = 7;
                }
                else if(input == letter_i)
                {
                    state = 9;
                }
                else if(input == digit)
                {
                    state = 6;
                      num *= 10;
                    num = num + c - 48; 
                }
                else
                {
                    state = 0;
                    t = new Token_img(num);
                    lexStart = x--;
                    tokens.push_back(t);
                    num = 0;
                }
                break;

            case 7:
                if(input == digit)
                {
                      decinum *= 10;
                    decinum = decinum + c - 48;
                   
                    tens *= 10;
                    state = 8;
                }
                else
                {
                    std::cerr<<" only digits expected after a decimal point :: at line "<<countLine<<std::endl;
                    state = 13;
                }
                break;

            case 8:
                if(input == digit)
                {
                      decinum *= 10;
                    decinum = decinum + c - 48;
                   
                    tens *= 10;
                    state = 8;
                }
                else
                {
                    decinum = decinum / tens;
                    lexStart = x--;
                    t = new Token_img((float)num + decinum);
                    num = 0; decinum = 0; tens = 1;
                    state = 0;
                    tokens.push_back(t);
                }
                break;

            case 9:
                if(input == letter_i || input == _i || input == digit)
                {
                    state = 9;
                }
                else
                {
                    std::string alphanum = "";
                    for(int j=lexStart; j<x; j++)
                    {
                        alphanum = alphanum + line[j];
                    }
                    lexStart = x--;
                    t = new Token_id(alphanum);
                    tokens.push_back(t);
                    state = 0;
                }
                break;

            case 10:
                state = 0; 
                t = new Token(line[--x]);
                tokens.push_back(t);
                lexStart = x+1;
                break;

            case 11:
                if(input == ws)
                {
                    state = 11;
                }
                else
                {
                    state = 0;
                    lexStart = x--;
                }
                break; 

            case 12:
                t = new Token('$');
                tokens.push_back(t);
                state = 0;
                countLine++;
                break;
            
            case 13:
                countLine++;
                x = line.size() + 2;
                parsable = false;
                break;
        }
        //end of switch
        x++;
    }
    
}

void Lexer::show()
{
    std::cout << " size is "<<tokens.size()<<std::endl;
    for(int i=0; i<tokens.size(); i++)
    {
        
        int t = tokens[i]->getType();// << " " <<iii->getVal()<<std::endl;
        std::cout<<t<<" ";
        if(t == id)
        {
            Token_id* iii = (Token_id*)tokens[i];
            std::cout << iii->getLex()<<std::endl;
        }
        else if(t == real_)
        {
            Token_real* iii = (Token_real*)tokens[i];
            std::cout<< iii->getVal()<<std::endl;
        }
        else if(t == img)
        {
            Token_img* iii = (Token_img*)tokens[i];
            std::cout << iii->getVal()<<std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    
    }

}

int Lexer::getLine()
{
    return countLine;
}

bool Lexer::isParsable()
{
    return parsable;
}

