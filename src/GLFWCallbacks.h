//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of voxfracturer.
//
//    voxfracturer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    voxfracturer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with voxfracturer.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOXFRACTURER_GLFWCALLBACKS_H_
#define VOXFRACTURER_GLFWCALLBACKS_H_

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "pathtracer/PathTracer.h"

/**
 * Debug GLFW error
 * @param[in] error         error code
 * @param[in] description   error description
 */
void errorCallback(int error, const char *description);

/**
 * Update viewport
 * @param window[in]    The window that received the event
 * @param width[in]     New viewport width
 * @param height[in]    New viewport height
 */
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

/**
 * @param[in]	window      The window that received the event
 * @param[in]	key         The keyboard key that was pressed or released
 * @param[in]	scancode	The system-specific scancode of the key
 * @param[in]	action      GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT. Future releases may add more actions
 * @param[in]	mods        Bit field describing which modifier keys were held down
 */
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

/**
 * Orbit scened based on callback xpos and ypos
 * @param window    The window that received the event
 * @param xpos      New cursor x position
 * @param ypos      New cursor y position
 */
void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);

/**
 * Store what mouse button is pressed
 * @param [in]	window	The window that received the event
 * @param[in]	button	The mouse button that was pressed or released
 * @param[in]	action	One of GLFW_PRESS or GLFW_RELEASE. Future releases may add more actions
 * @param[in]	mods	Bit field describing which modifier keys were held down
 */
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

/**
 * Perform zoomIn/zoomOut
 * @param[in]	window	The window that received the event
 * @param[in]	xoffset	The scroll offset along the x-axis
 * @param[in]	yoffset	The scroll offset along the y-axis
 */
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif  //VOXFRACTURER_GLFWCALLBACKS_H_
