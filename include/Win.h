#ifndef khidki
#define khidki

#include <GLFW/glfw3.h>
#include <iostream>

class Win
{
    public:
        Win(int,int);
        ~Win();
        void createWindow();
        bool isClosed();
        void pollEvents();
        void swapBuffers();
        void terminate();
        bool keyPressed(int);
        bool keyReleased(int);
        float getAspectRatio();
        void forceClose();
    private:
        int width = 1366;
        int height = 786;
        GLFWwindow* glfwWindow;

        static void resize(GLFWwindow*, int, int);

};

#endif
