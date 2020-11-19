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

#ifndef RENDERER_H_
#define RENDERER_H_

#include <glad/glad.h>

#include "scene/OrbitCamera.h"


/**
 * Renderer interface.
 */
class Renderer : public scene::OrbitCamera {
public:

    // Prevent unwanted constructions and destructions
    Renderer() = default;
    virtual ~Renderer() = default;

    /**
     * Initialize shaders, load objects and set OpenGL configuration.
     * After calling create(), you must set a viewport in order
     * to visualize the scene correctly.
     */
    virtual void init() = 0;

    /** Free all resources */
    virtual void destroy() = 0;

    /** Render the scene */
    virtual void render() = 0;

    /**
     * Set the viewport.
     * @param[in] width Width of the viewport
     * @param[in] height Height of the viewport
     */
    virtual void setViewport(GLsizei x, GLsizei y, GLsizei width, GLsizei height) = 0;

    /**
     * Set projection matrix.
     * @param[in] fovy      Camera field of view angle on y axis
     * @param[in] aspect    Camera aspect ratio
     * @param[in] zNer      Z near plane distance
     * @param[in] zFar      Z far plane distance
     */
    virtual void setPerspective(float fovy, float aspect, float zNear, float zFar) = 0;

    /** Export render image to file */
    virtual void readFrameBuffer(uint8_t* image, size_t w, size_t h) const = 0;
};

#endif  //PATH_TRACER_PATHTRACER_H_
