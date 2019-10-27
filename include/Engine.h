#ifndef ENGINE_H
#define ENGINE_H

#include "Win.h"
#include <time.h>
#include <thread>
#include "Renderer.h"
#include "Lexer.h"
#include "Parser.h"

class Engine
{
    public:
            Engine(int,int,int);
            ~Engine();

    private:
            Win* windows;
            std::thread* gameloopThread;
            static double fps;
            static double millisecPerUpdate;
            Renderer* worldRenderer;
            Grid* grid;
            int scale;
            float it = 0;
            int noOfInterpolates = 20;
            float orthoMag = 20;
            bool resetShader = false;
            std::string cmd, line;
            Lexer lex;
            Parser parser;
            
            void initialize();
            void gameloop();
            void input();
            void update();
            void render(double);

            void commandLine();
};

#endif
