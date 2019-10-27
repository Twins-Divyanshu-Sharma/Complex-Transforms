#include "Win.h"

Win::Win(int height, int width)
{
    this->width = width;
    this->height = height;
}

Win::~Win()
{
}

void Win::createWindow()
{
   if(!glfwInit())
   {
        std::cerr<<"unable to initialize window"<<std::endl;
        glfwTerminate();
        return;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindow = glfwCreateWindow(width,height,"Argand Plane",NULL,NULL);
   if(!glfwWindow)
   {
       std::cerr<<"unable to make window"<<std::endl;
       glfwTerminate();
       return;
   }
   glfwDefaultWindowHints();
   glfwMakeContextCurrent(glfwWindow);
   glViewport(0,0,width, height);

}

void Win::resize(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

bool Win::isClosed()
{
    if(glfwWindowShouldClose(glfwWindow))
        return true;
    else
        return false;
}

void Win::pollEvents()
{
    glfwPollEvents();
}

void Win::forceClose()
{
    glfwSetWindowShouldClose(glfwWindow,true);
}

void Win::swapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

void Win::terminate()
{
    glfwTerminate();
}

bool Win::keyPressed(int keyCode)
{
    return glfwGetKey(glfwWindow, keyCode) == GLFW_PRESS;
}

bool Win::keyReleased(int keyCode)
{
    return glfwGetKey(glfwWindow, keyCode) == GLFW_RELEASE;
}

float Win::getAspectRatio()
{
    return (float)width/(float)height;
}
