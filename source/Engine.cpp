#include "Engine.h"

double Engine::fps = 400.0;
double Engine::millisecPerUpdate = 1000/fps;

Engine::Engine(int width, int height, int scale)
{
    windows = new Win(width, height);
    this->scale = scale;
    parser.initialize("z", &lex);
    updateTheCode("z");
    gameloopThread = new std::thread(&Engine::gameloop, this);
    commandLine();
    gameloopThread->join();
}

Engine::~Engine()
{
    delete gameloopThread;
    delete windows;
}

void Engine::initialize()
{    
    windows->createWindow();
    worldRenderer = new Renderer();
    worldRenderer->setOrthogonalProjection(-orthoMag,orthoMag,-orthoMag,orthoMag,-orthoMag,orthoMag);
    grid = new Grid(scale);
    glClearColor(0, 0, 0, 1);
}

void Engine::commandLine()
{
    bool dhavti = true;
    while(dhavti)
    {
        getline(std::cin, line);
        if(line == "!")
        {
            lex.pass(cmd);
                parser.execute();
                updateTheCode(parser.getans());
                resetShader = true;
            line = "";
            cmd = "";
        }
        else if(line == "end")
        {
            windows->forceClose();
            dhavti = false;
        }
        else
        {
            cmd += line + " $ ";
          //  std::cout << cmd << std::endl << parser.getans() << std::endl;
        }
    }

}

void Engine::gameloop()
{
    initialize();
    clock_t previous = clock();
    double elapsed = 0;
    clock_t current = clock();
    double lag = 0;

    while(!windows->isClosed())
    {
        elapsed = (double)(current - previous)*1000/CLOCKS_PER_SEC;
        lag += elapsed;
        previous = clock();

        input();

        while(lag >= millisecPerUpdate)
        {
            update();
            lag -= millisecPerUpdate;
        }

        render(lag/millisecPerUpdate);
        current = clock();
    }

    windows->terminate();
}

void Engine::input()
{
    if(windows->keyPressed(GLFW_KEY_Z) && !windows->keyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        orthoMag -= 0.5f;
        worldRenderer->setOrthogonalProjection(-orthoMag,orthoMag,-orthoMag,orthoMag,-orthoMag,orthoMag);
    }

    if(windows->keyPressed(GLFW_KEY_Z) && windows->keyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        orthoMag += 0.5f;
        worldRenderer->setOrthogonalProjection(-orthoMag,orthoMag,-orthoMag,orthoMag,-orthoMag,orthoMag);
    }


    if(orthoMag <= 0)
        orthoMag = 0.1f;

    if(windows->keyPressed(GLFW_KEY_R))
        it = 0;

    windows->pollEvents();
}

void Engine::update()
{
    if(it < noOfInterpolates+1)
        worldRenderer->setNext((it++)/noOfInterpolates);

    if(resetShader)
    {
        worldRenderer->reload();
        resetShader = false;
    }

}

void Engine::render(double extraPolateVelocity)
{
    glClear(GL_COLOR_BUFFER_BIT);
    worldRenderer->render(*grid);
    windows->swapBuffers();
}
