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

#ifndef PATH_TRACER_PATHTRACER_H_
#define PATH_TRACER_PATHTRACER_H_

#include <iostream>
#include <chrono>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "../opengl/VertexArrayObject.h"
#include "../opengl/ShaderObject.h"
#include "../opengl/ShaderProgram.h"

#include "../util/Singleton.h"

#include "../Renderer.h"

#include "ScreenQuad.h"


namespace pathtracer {
    
    /**
     * OpenGL Renderer which is responsible of drawing the scene.
     * This class follows the singleton design pattern and the user
     * can't create new instances.
     */
    class PathTracer : public util::Singleton<PathTracer>, public Renderer {
    private:

        // Singleton<Renderer> needs access to the constructor and destructor
        friend class util::Singleton<PathTracer>;

        // Prevent unwanted constructions and destructions
        PathTracer();
        virtual ~PathTracer() = default;

    public:

        // ComputeShader work group dimensions
        static constexpr GLfloat WORKGROUP_SIZE_X = 16.0f;
        static constexpr GLfloat WORKGROUP_SIZE_Y = 16.0f;

        /**
         * Initialize shaders, load objects and set OpenGL configuration.
         * After calling create(), you must set a viewport in order
         * to visualize the scene correctly.
         */
        void init();

        /** Free all resources */
        void destroy();

        /** Path trace a ray born from eye going to every image pixel */
        void render();

        /** Draw accumulated image on quad */
        void renderToQuad();

        /** Render Graphics User Interface using ImGui */
        void renderGui();

        /**
         * Set the viewport.
         * @param[in] width Width of the viewport
         * @param[in] height Height of the viewport
         */
        void setViewport(GLsizei x, GLsizei y, GLsizei width, GLsizei height);

        /**
         * Set projection matrix.
         * @param[in] fovy      Camera field of view angle on y axis
         * @param[in] aspect    Camera aspect ratio
         * @param[in] zNer      Z near plane distance
         * @param[in] zFar      Z far plane distance
         */
        void setPerspective(float fovy, float aspect, float zNear, float zFar);

        /** Export render image to file */
        void readFrameBuffer(uint8_t* image, size_t w, size_t h) const;

        /**
         * Change OpenGL clear color.
         * @param[in] r Red component
         * @param[in] g Green component
         * @param[in] b Blue component
         */
        void setClearColor(float r, float g, float b);

        /**
         * Restart sampling the scene.  
         */
        void restart();

        /** Set max number of ray bounces */
        void setMaxBounces(unsigned int maxBounces);

        /** Set if pathtracer is running or stopped */
        void setActive(bool active);

        /**
         * Enable/disable supersampling antialiasing.
         * Changes will not be effective until setViewport is not invoked.
         */
        void setSSAA(bool ssaa);

    private:

        /**
         * Create the texture where to render the scene with given dimensions.
         * @param[in] width Viewport width
         * @param[in] height Viewport height
         */
        void createFrameBufferTexture(GLsizei width, GLsizei height); 

        /** Create, compile and link shaders */
        void initShaders();

        bool        ssaa;       //!< Supersampling antialiasing?
        GLsizei     fbWidth;    //!< Framebuffer width
        GLsizei     fbHeight;   //!< Framebuffer height
        GLuint      fbText;     //!< Texture where to render the scene
        GLuint      numSamples; //!< Path tracing amount of samples
        glm::vec4   clearColor; //!< Clear color
        glm::mat4   projMat;    //!< Projection matrix

        // Simulation configuration
        bool    isActive;   // Is path tracing running or stopped?
        int     maxBounces; // Max number of ray bounces

        ScreenQuad              screenQuad;         //!< ScreenQuad where to draw render texture
        opengl::ShaderProgram   screenQuadProgram;  //!< Draw texture to ScreenQuad
        opengl::ShaderProgram   pathTracerProgram;  //!< Path tracing compute shader
    };

}

#endif  //PATH_TRACER_PATHTRACER_H_
