//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of Pathtracer.
//
//    Pathtracer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Pathtracer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Pathtracer.  If not, see <https://www.gnu.org/licenses/>..

#include "GLFWCallbacks.h"

static struct {
    bool mouseLeft;
    bool mouseRight;
} shared;   //!< Store information to be shared between GLFW callbacks

// Get pathtracer instance
pathtracer::PathTracer& pt = pathtracer::PathTracer::instance();

void errorCallback(int error, const char *description) {
    std::cerr << __func__ << ": (error=" << error << ", description=" << description << ")" << std::endl;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    pt.setViewport(0, 0, width, height);
    pt.setPerspective(glm::radians(90.0f), (float) width / (float) height, 0.5f, 100.0f);
    pt.restart();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    static double xprev = xpos;
    static double yprev = ypos;

    double xoffset = xprev - xpos;
    double yoffset = yprev - ypos;

    if (shared.mouseLeft && !ImGui::IsMouseHoveringAnyWindow()) {
        pt.setTheta(pt.getTheta() - float(glm::radians(xoffset / 2.0f)));
        pt.setPhi(pt.getPhi()     - float(glm::radians(yoffset / 2.0f)));
        pt.restart();
    }

    xprev = xpos;
    yprev = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (!ImGui::IsMouseHoveringAnyWindow())
                shared.mouseLeft = action;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (!ImGui::IsMouseHoveringAnyWindow())
                shared.mouseRight = action;
            break;
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    float distance = pt.getDistance() - float(yoffset) / 2.0f;

    if (!ImGui::IsMouseHoveringAnyWindow()) {
        pt.setDistance(distance);
        pt.restart();
    } 
}
