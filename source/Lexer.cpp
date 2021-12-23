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

void Lexer::pass(std::string line)
{
    line = line + " ";
    int state = 0;
    int x = 0;
    int input = 0; 
    int lexStart = 0;
    int num=0, tens=1;
    float decinum = 0;
    Token* t;
    int danger = 0;
    bool minusDetected =false;
    float f = 0;

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
            std::cout << "Invalid character ["<<line[x]<<"] at line "<<countLine<<std::endl;
            break;
        }


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
                    return;
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
                    if(minusDetected)
                   {
                       num = -num;
                       minusDetected = false;
                       danger = 0;
                   }
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
                    return;
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
                        f = (float)num + decinum;
                        if(minusDetected)
                        {
                            minusDetected = false;
                            danger =0;
                            f = -f;
                        }
                        t = new Token_real(f);
                        lexStart = x--;
                        num = 0;
                        decinum = 0;
                        tens = 1;
                        tokens.push_back(t);
                    }
                }
                break;

            case 4:
                f = (float)num + decinum;
                if(minusDetected)
                {
                    minusDetected = false;
                    danger = 0;
                    f = -f;
                }
                t = new Token_img(f);
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
                    state = 0;
                    num = 0;
                    int one = 1;
                    if(minusDetected)
                    {
                        minusDetected = false;
                        danger = 0;
                        one = -one;
                    }
                    t = new Token_img(one);
                    lexStart = x--;
                    tokens.push_back(t);
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
                    /// ______________________________  here was the problem _________________________________________
                    state = 0;
                    if(minusDetected)
                    {
                        minusDetected = false;
                        danger = 0;
                        num = -num;
                    }
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
                    return;
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
                    f = (float)num + decinum;
                    if(minusDetected)
                    {
                        minusDetected = false;
                        danger = 0;
                        f = -f;
                    }
                    t = new Token_img(f);
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
                x--;
                if(line[x] == '=')
                    danger = 1;
                else if(danger == 1 && line[x] == '-')
                {    danger = 2;
                    minusDetected = true;
                }
                else if(danger == 2 && line[x] == '(')
                    danger = 3;
                
                if(danger != 2)
                {
                    if(danger == 3)
                    {
                        minusDetected = false;
                        danger = 0;
                        t = new Token('-');
                        tokens.push_back(t);
                    }
                    t = new Token(line[x]);
                    tokens.push_back(t);
                    lexStart = x+1;
                }

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
        }
        //end of switch
        x++;

    }
}

void Lexer::show()
{
  //  //std::cout << " size is "<<tokens.size()<<std::endl;
    for(int i=0; i<tokens.size(); i++)
    {
        
        int t = tokens[i]->getType();// << " " <<iii->getVal()<<std::endl;
     //   std::cout<<t<<" ";
        if(t == id)
        {
            Token_id* iii = (Token_id*)tokens[i];
         //   std::cout << iii->getLex()<<std::endl;
        }
        else if(t == real_)
        {
            Token_real* iii = (Token_real*)tokens[i];
            //std::cout<< iii->getVal()<<std::endl;
        }
        else if(t == img)
        {
            Token_img* iii = (Token_img*)tokens[i];
          //  std::cout << iii->getVal()<<std::endl;
        }
        else
        {
         //   std::cout << std::endl;
        }
    
    }

}

int Lexer::getLine()
{
    return countLine;
}
