/*
 * =====================================================================================
 *
 *       Filename:  Parser.cpp
 *
 *    Description:  Validates syntax of the grammar
 *
 *        Version:  1.0
 *        Created:  09/21/2019 12:52:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BRAHMIN TWINS (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Parser.h"

void Parser::initialize(std::string finalZ, Lexer* lex)
{
    this->finalZ = finalZ;
    this->lex = lex;
    prod[0] = &Parser::fM;
    prod[1] = &Parser::fX0;   prod[2] = &Parser::fX1;
    prod[3] = &Parser::fE;
    prod[4] = &Parser::fE_0;  prod[5] = &Parser::fE_1;  prod[6] = &Parser::fE_2;
    prod[7] = &Parser::fT;
    prod[8] = &Parser::fT_0;  prod[9] = &Parser::fT_1;  prod[10] = &Parser::fT_2;
    prod[11] = &Parser::fF0;  prod[12] = &Parser::fF1;
    prod[13] = &Parser::fF2;  prod[14] = &Parser::fF3;
    prod[15] = &Parser::fY0;  prod[16] = &Parser::fY1;
    prod[17] = &Parser::fH0;  prod[18] = &Parser::fH1;

    brackySize.push_back(0);

    Comp_lex c;
    symbolTable.insert(std::pair<std::string,Comp_lex>(finalZ,c));
    theMaker();

    Node m(M);
    Node e($);
    sstack.push_back(e);
    sstack.push_back(m);
}

void Parser::fM()
{
  if(!sstack.back().processed)
  {
      sstack.back().processed = true;
      sstack.back().prodno = 0;
      Node a(id);
      Node b(eq_);
      Node c(X);
      Token_id* td = (Token_id*)(lex->tokens.front());
      sstack.back().inh.zString = td->getLex();
      //sstack.back().inh.zString = (Token_id*)(lex->tokens.front())->getLex();
      sstack.push_back(c); 
      sstack.push_back(b);
      sstack.push_back(a);
  }
  else
  {
      std::string s = sstack.back().inh.zString;
      float rrr = sstack.back().syn.r;
      float iii = sstack.back().syn.i;
      bool identity = (rrr == 0 && iii == 0) ? true : false;
      if(s == finalZ)
      {
          symbolTable[s].r = 1; symbolTable[s].i = 0;
          if(identity)
              symbolTable[s].zString = "";
          else
             symbolTable[s].zString = "vec2("+std::to_string(rrr)+","+std::to_string(iii) + ")";
          
          if(sstack.back().syn.zString != "")
          {
              if(identity)
                  symbolTable[s].zString += sstack.back().syn.zString;
              else
                 symbolTable[s].zString += "+" + sstack.back().syn.zString ;
          }
      }
      else if(searchForString(s))
      {
          if(sstack.back().syn.zString == "")
          { 
              symbolTable[s].r = rrr;
              symbolTable[s].i = iii;
              symbolTable[s].zString = sstack.back().syn.zString;
          }
          else
          {
             symbolTable[s].r = 1;
             symbolTable[s].i = 0;
             if(identity)
                 symbolTable[s].zString = sstack.back().syn.zString;
             else
                symbolTable[s].zString = sstack.back().syn.zString + "+" + "vec2("+ std::to_string(rrr) + "," + std::to_string(iii) + ")";
          }

      }
      else
      {
          Comp_lex ccc;
          if(sstack.back().syn.zString == "")
          {
            
             ccc.r = rrr;
             ccc.i = iii;
             ccc.zString = sstack.back().syn.zString;
          }
          else
          {
             ccc.r = 1; ccc.i = 0;
             if(identity)
                 ccc.zString = sstack.back().syn.zString;
             else
                ccc.zString = sstack.back().syn.zString + "+" + "vec2("+std::to_string(rrr) + "," + std::to_string(iii) + ")";
          }
          std::pair<std::string, Comp_lex> v(s,ccc);
          symbolTable.insert(v);
      }
         
      variable.clear();
 }

}

void Parser::fX0()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node a(sub);
        Node b(E);
        sstack.back().processed = true;
        sstack.back().prodno = 1;
        sstack.push_back(b);
        sstack.push_back(a);
    }
    else
    {
       sstack[_top - 1].syn.r = -1 * sstack.back().syn.r;
       sstack[_top - 1].syn.i = -1 * sstack.back().syn.i;
       sstack[_top - 1].syn.zString ="-1*(" +sstack.back().syn.zString+")";
    }   
}

void Parser::fX1()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node b(E);
        sstack.back().processed = true;
        sstack.back().prodno = 2;
        sstack.push_back(b);
    }
    else
    {       
      sstack[_top - 1].syn.r = sstack.back().syn.r;
      sstack[_top - 1].syn.i = sstack.back().syn.i;
      sstack[_top - 1].syn.zString = sstack.back().syn.zString;        
   }
}

void Parser::fE()
{
    int _top = sstack.size() -1;
    if(!sstack.back().processed)
    {
        Node a(T);
        Node b(E_);
        if(sstack.back().inside)
        {
            sstack.back().inh.zString = sstack.back().syn.zString;
            a.inside = true;
            b.inside = true;
        }
        sstack.back().processed = true;
        sstack.back().prodno = 3;
        sstack.push_back(b);
        sstack.push_back(a);
    }
    else
    {
        int next_ = 1;
        if(sstack.back().inside)
            next_ = 2;
      sstack[_top - next_].syn.r = sstack.back().syn.r;
      sstack[_top - next_].syn.i = sstack.back().syn.i;
      sstack[_top - next_].syn.zString = sstack.back().syn.zString;
    }
}

void Parser::fE_0()
{
    int _top = sstack.size() -1;
    if(!sstack.back().processed)
    {
        Node a(add);
        Node b(T);
     //   if(sstack.back().inside)
     //       b.inside = true;
        b.inh.r = sstack.back().syn.r;
        b.inh.i = sstack.back().syn.i;
        sstack.back().inh.zString = sstack.back().syn.zString;
        b.o_p = add;
        Node c(E_);
        sstack.back().processed = true;
        sstack.back().prodno = 4;
        sstack.push_back(c);
        sstack.push_back(b);
        sstack.push_back(a);
    }
    else
    {
      sstack[_top - 1].syn.r = sstack.back().syn.r;
      sstack[_top - 1].syn.i = sstack.back().syn.i;
      if(sstack.back().syn.zString == "")
      {
          sstack[_top - 1].syn.zString = sstack.back().inh.zString;
      }
      else
      {
            sstack[_top-1].syn.zString = sstack.back().inh.zString + "+" + sstack.back().syn.zString;
      }
    }
}

void Parser::fE_1()
{
    int _top = sstack.size() -1;
    if(!sstack.back().processed)
    {
        Node a(sub);
        Node b(T);
        Node c(E_);
 
        b.inh.r = sstack.back().syn.r;
        b.inh.i = sstack.back().syn.i;
        sstack.back().inh.zString = sstack.back().syn.zString;
        b.o_p = sub;
        sstack.back().processed = true;
        sstack.back().prodno = 5;
        sstack.push_back(c);
        sstack.push_back(b);
        sstack.push_back(a);
    }
    else
    {
       sstack[_top - 1].syn.r = sstack.back().syn.r;
       sstack[_top - 1].syn.i = sstack.back().syn.i;
       if(sstack.back().syn.zString == "")
       { sstack[_top - 1].syn.zString = sstack.back().inh.zString;}
       else
       { 
           sstack[_top -1].syn.zString = sstack.back().inh.zString + "-" + sstack.back().syn.zString;
       }
    }
}

void Parser::fE_2()
{
    int _top = sstack.size() - 1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 6;
    }
    else
    {

        sstack[_top-1].syn.r = sstack.back().syn.r;
        sstack[_top-1].syn.i = sstack.back().syn.i;
        sstack[_top-1].syn.zString = sstack.back().syn.zString;
        //if(sstack.back().inside == false)
          //  variable.clear();
    }
}

void Parser::fT()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {

        Node a(F); Node b(T_);
        if(sstack.back().inside)
            b.inside = true;
        sstack.back().processed = true;
        sstack.back().prodno = 7;
        sstack.push_back(b); sstack.push_back(a);
        
    }
    else
    {
        if(sstack.back().o_p == add)
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r + sstack.back().inh.r;
            sstack[_top - 1].syn.i = sstack.back().syn.i + sstack.back().inh.i;
        }
        else if(sstack.back().o_p == sub)
        {
            sstack[_top - 1].syn.r = sstack.back().inh.r - sstack.back().syn.r;
            sstack[_top - 1].syn.i = sstack.back().inh.i - sstack.back().syn.i; 
        }
        else
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r;
            sstack[_top - 1].syn.i = sstack.back().syn.i;
        }

        sstack[_top -1].syn.zString = sstack.back().syn.zString;
    }
}

void Parser::fT_0()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node a(mul); Node b(F); Node c(T_);
        if(sstack.back().inside)
            c.inside = true;
        b.o_p = mul;
        b.inh.r = sstack.back().syn.r;
        b.inh.i = sstack.back().syn.i;
        b.inh.zString = sstack.back().syn.zString;
        sstack.back().processed = true;
        sstack.back().prodno = 8;
        sstack.push_back(c); sstack.push_back(b); sstack.push_back(a);
    }
    else
    {
       sstack[_top - 1].syn.r = sstack.back().syn.r;
       sstack[_top - 1].syn.i = sstack.back().syn.i;
       sstack[_top - 1].syn.zString = sstack.back().syn.zString;          
    }
}

void Parser::fT_1()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node a(div_); Node b(F); Node c(T_);
        b.o_p = div_;
        b.inh.r = sstack.back().syn.r;
        b.inh.i = sstack.back().syn.i;
        if(sstack.back().inside)
            c.inside  = true;
        b.inh.zString = sstack.back().syn.zString;
        sstack.back().processed = true;
        sstack.back().prodno = 9;
        sstack.push_back(c); sstack.push_back(b); sstack.push_back(a);
    }
    else
    {
       sstack[_top - 1].syn.r = sstack.back().syn.r;
       sstack[_top - 1].syn.i = sstack.back().syn.i;
       sstack[_top - 1].syn.zString = sstack.back().syn.zString;          
    }
}

void Parser::fT_2()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        // i could have done it directly , but need to generalize the stack
        sstack.back().prodno = 10;
    }
    else
    {      
      if(sstack.back().syn.zString == "")
      {
        sstack[_top - 1].syn.r = sstack.back().syn.r;
        sstack[_top - 1].syn.i = sstack.back().syn.i;
        sstack[_top - 1].syn.zString = sstack.back().syn.zString;
      }
      else
      {
        int x=0;
          std::string divORmul = sstack.back().syn.zString;
          int outside = variable.size() - divORmul.size();
          float rr = sstack.back().syn.r;
        float ii = sstack.back().syn.i;
        std::string convert = "vec2(" + std::to_string(rr) + "," + std::to_string(ii) + ")";
        if(rr == 1 && ii == 0)
            convert = "";
      
        sstack[_top - 1].syn.r = 0;  sstack[_top - 1].syn.i = 0;
        
        if(sstack.back().inside)
        {  
            sstack[_top -1].syn.r = 1;
        }
        
        for(int r=outside; r<divORmul.size()+outside; r++)
        {  
            if(!searchForString(variable[r]))
            {
                return;
            }
            std::string oneMoreTime = symbolTable[variable[r]].zString;
            if(oneMoreTime == "null" &&  variable[r] != finalZ)
            {
                std::cerr << "Error "<<variable[r]<<" is not defined \n";
                return;
            }

            if(divORmul[x] == '*')
            {
                if(variable[r] == finalZ)
                {
                    if(convert == "")
                        convert = finalZ;
                    else
                        convert = "multiply(" + convert + "," + finalZ + ")";
                }
                else
                {
                    if(convert == "")
                        convert = oneMoreTime;
                    else
                        convert = "multiply(" + convert + "," + oneMoreTime + ")";
                }
            }
            else if(divORmul[x] == '/')
            {
                if(variable[r] == finalZ)
                {
                    if(convert == "")
                        convert = finalZ;
                    else
                        convert = "divide(" + convert + "," + finalZ + ")";
                }
                else
                {
                    if(convert == "")
                        convert = oneMoreTime;
                    else
                        convert = "divide(" + convert + "," + oneMoreTime + ")";
                }
            }

           else
            {
                std::cerr << " divORmul mein Yeh kya ?! Yeh kya !? Yeh kya ?! "<<divORmul[r]<<std::endl;
             //   return;
            }
            x++;
        }
     
        if(outside <= 0)
            variable.clear();

        sstack[_top - 1].syn.zString = convert;
      }

    }
}

void Parser::fF0()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 11;
        Node a(id);
		float rr=1, ii=0;
		std::string sss="";
        Token_id* dd = (Token_id*)(lex->tokens.front());
        if(dd->getLex() == finalZ)
        {
           variable.push_back(finalZ);
           sstack.back().isZ = true;
        }
        else if(searchForString(dd->getLex()))
		{
            sss = symbolTable[dd->getLex()].zString;
        
            if(sss == "null" || sss == "")
            {
			    rr = symbolTable[dd->getLex()].r;
			    ii = symbolTable[dd->getLex()].i;
            }
            else
            {
                sstack.back().isZ = true;
                variable.push_back(dd->getLex());
            }
        }
		else
		{
       
		    rr = 0;
            ii = 0;
			Comp_lex x;
			std::pair<std::string, Comp_lex> xxx(dd->getLex(), x);
			symbolTable.insert(xxx); 
		}
        sstack.back().syn.r = rr;
        sstack.back().syn.i = ii;
        sstack.back().syn.zString = sss;
        sstack.push_back(a);
    }
    else
    {
        if(sstack.back().o_p == mul)
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r * sstack.back().inh.r - sstack.back().inh.i*sstack.back().syn.i;
            sstack[_top - 1].syn.i = sstack.back().syn.i*sstack.back().inh.r + sstack.back().syn.r*sstack.back().inh.i;
                     
           if(sstack.back().isZ)
           {
               sstack[_top-1].syn.zString = sstack.back().inh.zString + "*";
           }
           else
           {
               sstack[_top-1].syn.zString = sstack.back().inh.zString;
           }
                        
        }
        else if(sstack.back().o_p == div_)
        {
            float aa = sstack.back().syn.r,  bb = sstack.back().syn.i;
            float r2 = aa * aa + bb * bb;
            sstack[_top - 1].syn.r = (sstack.back().inh.r * aa + sstack.back().inh.i * bb)/r2;
            sstack[_top -1].syn.i = (sstack.back().inh.i * aa - sstack.back().inh.r * bb)/r2;
            if(sstack.back().isZ)
            {
                sstack[_top-1].syn.zString = sstack.back().inh.zString + "/";
            }
            else
            {
                sstack[_top-1].syn.zString = sstack.back().inh.zString;
            }
        }
        else
        {
            sstack[_top-1].syn.r = sstack.back().syn.r;
            sstack[_top-1].syn.i = sstack.back().syn.i;
            if(sstack.back().isZ)
            {
                sstack[_top-1].syn.zString = "*";
            }
            else
            {
                sstack[_top-1].syn.zString = sstack.back().syn.zString;
            }
        }
    }   
}

void Parser::fF1()
{
    int _top = sstack.size()-1;

    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 12;
        Node a(real_); 
        Token_real* dd = (Token_real*)(lex->tokens.front());
		sstack.back().syn.r = dd->getVal();
		sstack.back().syn.i = 0;
		sstack.back().syn.zString = "";
        sstack.push_back(a);
	}
    else
    {
        if(sstack.back().o_p == mul)
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r * sstack.back().inh.r - sstack.back().inh.i*sstack.back().syn.i;
            sstack[_top - 1].syn.i = sstack.back().syn.i*sstack.back().inh.r + sstack.back().syn.r*sstack.back().inh.i;   
        }
        else if(sstack.back().o_p == div_)
        {
            float aa = sstack.back().syn.r,  bb = sstack.back().syn.i;
            float r2 = aa * aa + bb * bb;
            sstack[_top - 1].syn.r = (sstack.back().inh.r * aa + sstack.back().inh.i * bb)/r2;
            sstack[_top -1].syn.i = (sstack.back().inh.i * aa - sstack.back().inh.r * bb)/r2;
            // do something for zString here
        }
        else
        {
            sstack[_top-1].syn.r = sstack.back().syn.r;
            sstack[_top-1].syn.i = sstack.back().syn.i;

        }
            sstack[_top-1].syn.zString = sstack.back().syn.zString;
    }
}

void Parser::fF2()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().prodno = 13;
        sstack.back().processed = true;
        Node a(img);
        Token_img* dd = (Token_img*)(lex->tokens.front());
		sstack.back().syn.r = 0;
		sstack.back().syn.i = dd->getVal();
        sstack.push_back(a);
    }
    else
    {
        if(sstack.back().o_p == mul)
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r * sstack.back().inh.r - sstack.back().inh.i*sstack.back().syn.i;
            sstack[_top - 1].syn.i = sstack.back().syn.i*sstack.back().inh.r + sstack.back().syn.r*sstack.back().inh.i;
         //   sstack[_top - 1].syn.zString = sstack.back().syn.zString + "*(" + sstack.back().inh.zString + ")";            
        }
        else if(sstack.back().o_p == div_)
        {
            float aa = sstack.back().syn.r,  bb = sstack.back().syn.i;
            float r2 = aa * aa + bb * bb;
            sstack[_top - 1].syn.r = (sstack.back().inh.r * aa + sstack.back().inh.i * bb)/r2;
            sstack[_top -1].syn.i = (sstack.back().inh.i * aa - sstack.back().inh.r * bb)/r2;
            // do something for zString here
        }
        else
        {
            sstack[_top-1].syn.r = sstack.back().syn.r;
            sstack[_top-1].syn.i = sstack.back().syn.i;
        }
        sstack[_top-1].syn.zString = sstack.back().syn.zString;
        
    }
}

void Parser::fF3()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node a(bracky_l); Node b(Y);
        sstack.back().processed = true;
        sstack.back().prodno = 14;
     //   sstack.back().inh.zString = sstack.back().syn.zStrig;
        sstack.push_back(b); sstack.push_back(a);
        //dont synthesise here
    }
    else
    {
        if(sstack.back().o_p == mul)
        {
            sstack[_top - 1].syn.r = sstack.back().syn.r * sstack.back().inh.r - sstack.back().inh.i*sstack.back().syn.i;
            sstack[_top - 1].syn.i = sstack.back().syn.i*sstack.back().inh.r + sstack.back().syn.r*sstack.back().inh.i;
            sstack[_top - 1].syn.zString = sstack.back().inh.zString + "*";            
        }
        else if(sstack.back().o_p == div_)
        {
            float aa = sstack.back().syn.r,  bb = sstack.back().syn.i;
            float r2 = aa * aa + bb * bb;
            sstack[_top - 1].syn.r = (sstack.back().inh.r * aa + sstack.back().inh.i * bb)/r2;
            sstack[_top -1].syn.i = (sstack.back().inh.i * aa - sstack.back().inh.r * bb)/r2;
            sstack[_top - 1].syn.zString = sstack.back().inh.zString + "/";
        }

        else
        {
            sstack[_top-1].syn.r = sstack.back().syn.r;
            sstack[_top-1].syn.i = sstack.back().syn.i;
            sstack[_top-1].syn.zString = sstack.back().syn.zString;
        }

    }
}

void Parser::fY0()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        Node a(E);
        Node b(bracky_r);
        a.inside = true; 
        sstack.back().processed = true;
        sstack.back().prodno = 15;
        sstack.back().inh.r = variable.size();
        brackySize.push_back(variable.size());
        sstack.push_back(b); sstack.push_back(a);
    }
    else
    {
      sstack[_top - 1].syn.r = sstack.back().syn.r;
      sstack[_top - 1].syn.i = sstack.back().syn.i;
      if(sstack.back().syn.zString == "")
         sstack[_top - 1].syn.zString = sstack.back().syn.zString; 
      else
      {
        
             for(int j=variable.size(); j>sstack.back().inh.r; j--)
               variable.pop_back();

            brackySize.pop_back();

    
          Comp_lex c;
          c.r = 1;  c.i = 0;
          c.zString = "("+sstack.back().syn.zString+")";

          std::string newbrr = tempVariables();
          std::pair<std::string, Comp_lex> vuv(newbrr,c);
          symbolTable.insert(vuv);
          variable.push_back(newbrr);
          sstack[_top - 1].syn.zString = "*";

      }

    }
}

void Parser::fY1()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 16;
        Node a(sub); Node b(H); Node c(bracky_r);
        sstack.push_back(c); sstack.push_back(b); sstack.push_back(a);
    }
    else
    {
       sstack[_top - 1].syn.r = sstack.back().syn.r;
      sstack[_top - 1].syn.i = sstack.back().syn.i;
      sstack[_top - 1].syn.zString = sstack.back().syn.zString;        
    }
}

void Parser::fH0()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 17;
        Node a(real_); 
        Token_real* dd = (Token_real*)(lex->tokens.front());
        sstack.back().syn.r = dd->getVal();
		sstack.back().syn.i = 0;	
        sstack.push_back(a);
    }
    else
    {
       sstack[_top - 2].syn.r = -1*sstack.back().syn.r;
      sstack[_top - 2].syn.i = -1*sstack.back().syn.i;
   //   sstack[_top - 2].syn.zString = "-1*("+sstack.back().syn.zString+")";               
    }
}

void Parser::fH1()
{
    int _top = sstack.size()-1;
    if(!sstack.back().processed)
    {
        sstack.back().processed = true;
        sstack.back().prodno = 18;
        Node a(img); 
		sstack.back().syn.r = 0;
        Token_img* dd = (Token_img*)(lex->tokens.front());
        sstack.back().syn.i = dd->getVal();
//		sstack.back().syn.zString = "";
        sstack.push_back(a);
    }
    else
    {
      sstack[_top - 2].syn.r = -1*sstack.back().syn.r;
      sstack[_top - 2].syn.i = -1*sstack.back().syn.i;
  //    sstack[_top - 2].syn.zString = "-1*("+sstack.back().syn.zString+")";
    }
}

void Parser::execute()
{ 
    bool run = true;
    int prodno = -100;
    int linecnt = 0;

    // XXXXXXXXXX  this should be changed for more than 1 line hence more than 1 $ XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    // XXXXXXXXXXX  First Implement it in lexer too, as lexer can pass only 1 line currently XXXXXXXXXXXXXXXXXXXXXXX
    while(run)
    {
        
        if(lex->tokens.size() == 0)
            run = false;
        if(lex->tokens.front()->getType() == 1 && sstack.back().type == 1)
        {
            linecnt++;

            if(lex->tokens.size() <= 1)
                run = false;
            else
            {
                sstack.pop_back();
                lex->tokens.erase(lex->tokens.begin());
                Node m(M);
                Node e($);
                sstack.push_back(e);
                sstack.push_back(m);
            }
            
        }
        else if(sstack.back().type > 10 )
        {
            if(!sstack.back().processed)
            {
               
                int a = lex->tokens.front()->getType();
                int b = sstack.back().type - 11;
                prodno = table[b][a];
                if(prodno == -100)
                {
                    std::cerr << " Parsing error in line "<<linecnt<<std::endl;
                    run = false;
                }
                (*this.*prod[prodno])();
            }           
            if(sstack.back().processed)
            {
                (*this.*prod[sstack.back().prodno])();
                sstack.pop_back();
            }
       }
        else if(sstack.back().type <= 10)
        {
            lex->tokens.erase(lex->tokens.begin());
            sstack.pop_back();
        }
    }

    answer = symbolTable[finalZ].zString;
}

bool Parser::searchForString(std::string s)
{
    for(std::map<std::string, Comp_lex>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it)
    {
        if(it->first == s)
            return true;
    }
    return false;
}

void Parser::theMaker()
{
    for(int a=0; a<9; a++)
    {
        for(int b=0; b<11; b++)
        {
            table[a][b] = -100;
        }
    }

    table[0][0] = 0;
    table[1][5] = 1; table[1][0] = 2;  table[1][9] = 2; table[1][3] =2; table[1][2] = 2;
    table[2][9] = 3; table[2][0] = 3;  table[2][3] = 3;  table[2][2] = 3;
    table[3][4] = 4; table[3][5] = 5;  table[3][10] = 6; table[3][1] = 6;
    table[4][9] = 7; table[4][0] = 7;  table[4][3] = 7;   table[4][2] = 7;
    table[5][4] = 10; table[5][5] = 10; table[5][10] = 10; table[5][1] = 10; table[5][6] =8; table[5][7] = 9;
    table[6][9] = 14; table[6][0]=11;  table[6][3] = 12; table[6][2] = 13;
    table[7][5] = 16; table[7][9] = 15; table[7][0]=15;  table[7][3] =15; table[7][2]=15;
    table[8][3] = 17; table[8][2] = 18;
}

std::string Parser::tempVariables()
{
    std::string alphaIsThe = "AnDhER_RaAjAAjajaja_cHoPaAt_naAgrrRiIIi";
    int numIsThe = 79000;
    bool found = false;
    std::string alphaNum = "";
    while(!found)
    {
        alphaNum = alphaIsThe + std::to_string(numIsThe);
        if(searchForString(alphaNum))
        {
            numIsThe++;
        }
        else
        {
            found = true;
        }
    }

        return alphaNum;

}

std::string Parser::getans()
{
    return answer;
}
