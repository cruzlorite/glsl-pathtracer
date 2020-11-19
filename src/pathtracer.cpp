//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of pathtracer.
//
//    pathtracer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    pathtracer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with pathtracer.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <istream>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "appinfo.h"
#include "GLFWCallbacks.h"

#include "pathtracer/PathTracer.h"


// Handy macro for printing info
#define PRINT_OUT(msg) std::cout << msg << std::endl; 
#define PRINT_ERR(msg) std::cerr << APP_NAME << ": " << msg << std::endl; 

#define OPENGL_MAJOR    4                   // OpenGL major version
#define OPENGL_MINOR    5                   // OpenGL minor version
#define WINDOW_SIZE     720                 // Window size
#define CLEAR_COLOR     0.0f, 0.0f, 0.0f    // OpenGL clear color

int main(int argc, char** argv) {

    // Setup window
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        PRINT_ERR("glfw initialization failed");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    //glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "pathtracer", NULL, NULL);
    if (window == NULL) {
        PRINT_ERR("glfw window creation failed");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Enable vsync

    // Set GLFW callbacks
    //glfwSetWindowRefreshCallback(window,   windowRefreshCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window,             keyCallback);
    glfwSetCursorPosCallback(window,       cursorPositionCallback);
    glfwSetMouseButtonCallback(window,     mouseButtonCallback);
    glfwSetScrollCallback(window,          scrollCallback);

    // Initialize glad.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        PRINT_ERR("glad initialization failed");
        exit(EXIT_FAILURE);
    }
    
    /**********************************************************/
    /*                      Render loop                       */
    /**********************************************************/

    // Setup imgui
    ImGui_ImplGlfwGL3_Init(window, true);

    // Get Renderer instance
    pathtracer::PathTracer& pt = pathtracer::PathTracer::instance();
    pt.init();

    // After initialization setup PathTracer
    pt.setClearColor(CLEAR_COLOR);
    pt.setMaxBounces(10);
    pt.setSSAA(true); // Enable SSAA

    // WE MUST SET VIEWPORT!!!
    framebufferSizeCallback(window, WINDOW_SIZE, WINDOW_SIZE);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        ImGui_ImplGlfwGL3_NewFrame();

        pt.render();
        pt.renderToQuad();
        pt.renderGui();

        glfwSwapBuffers(window);
    }

    // Release resources
    pt.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
