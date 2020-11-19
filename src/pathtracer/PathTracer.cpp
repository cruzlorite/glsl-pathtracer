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

#include "PathTracer.h"

namespace pathtracer {

    PathTracer::PathTracer()
            : Renderer()
            , ssaa(false)
            , fbWidth(0)
            , fbHeight(0)
            , fbText(0)
            , numSamples(0)
            , clearColor(0.0f)
            , projMat(1.0f)
            , isActive(true)
            , maxBounces(10)
            , screenQuad()
            , screenQuadProgram()
            , pathTracerProgram() {

    }

    void PathTracer::init() {
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_ONE, GL_ONE);

        // Initialize opengl objects
        screenQuad.create();
        initShaders();

        // Prepare camera
        setDistance(5.0f);
        setLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    void PathTracer::destroy() {

    }

    void PathTracer::render() {
                         // force at least one sample
        if (!isActive && numSamples > 0) return; // Don't sample when inactive

        // Increase amount of samples
        numSamples++;

        // Compute modelViewProj matrix
        glm::mat4 vp = projMat * viewMat();
        glm::mat4 ivp = glm::inverse(vp);
        glm::vec4 eye = glm::vec4(getEye(), 0.0f);

        // Generate the 4 camera rays
        glm::vec4 ray00 = ivp * glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
        glm::vec4 ray10 = ivp * glm::vec4(1.0f,  -1.0f, 0.0f, 1.0f);
        glm::vec4 ray01 = ivp * glm::vec4(-1.0f, 1.0f,  0.0f, 1.0f);
        glm::vec4 ray11 = ivp * glm::vec4(1.0f,  1.0f,  0.0f, 1.0f);

        ray00 = (ray00 / ray00.w) - eye;
        ray10 = (ray10 / ray10.w) - eye;
        ray01 = (ray01 / ray01.w) - eye;
        ray11 = (ray11 / ray11.w) - eye;

        // Path trace the scene
        pathTracerProgram.use();
        pathTracerProgram.uniform("eye",   getEye());
        pathTracerProgram.uniform("ray00", glm::vec3(ray00));
        pathTracerProgram.uniform("ray10", glm::vec3(ray10));
        pathTracerProgram.uniform("ray01", glm::vec3(ray01));
        pathTracerProgram.uniform("ray11", glm::vec3(ray11));
        pathTracerProgram.uniform("maxBounces", GLuint(maxBounces));
        pathTracerProgram.uniform("numSamples", numSamples);

        // Bind framebuffer texture
        glBindImageTexture(0, fbText, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

        // Compute dispatch number of groups
        GLuint workGroupsX = GLuint(std::ceil(fbWidth / WORKGROUP_SIZE_X));
        GLuint workGroupsY = GLuint(std::ceil(fbHeight / WORKGROUP_SIZE_Y));

        // Dispatch compute shader
        glDispatchCompute(workGroupsX, workGroupsY, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }

    void PathTracer::renderToQuad() {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render to Screen Quad
        screenQuadProgram.use();

        // Bind framebuffer texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbText);
        screenQuadProgram.uniform("textSampler", 0);
        screenQuadProgram.uniform("numSamples", numSamples);

        screenQuad.bind();
        screenQuad.render();

        glUseProgram(0);
    }

    void PathTracer::renderGui() {       
        if (ImGui::Begin("PathTracer configuration", NULL, ImVec2(0, 0), 0.3f,
                ImGuiWindowFlags_NoSavedSettings    |
                ImGuiWindowFlags_AlwaysAutoResize
                )) {

            if (ImGui::Button(isActive ? " Stop " : " Run  ")) {
                isActive = !isActive;
            }
            ImGui::SameLine();
            std::string text = "Total of " + std::to_string(numSamples) + " samples done.";
            ImGui::Text(text.c_str());
            ImGui::SameLine();
            if (ImGui::Button("Restart")) {
                restart();
            }

            ImGui::SliderInt("maxBounces", &maxBounces, 1, 32);
        }
        
        ImGui::End();
        ImGui::Render();
    }

    void PathTracer::setViewport(GLsizei x, GLsizei y, GLsizei width, GLsizei height) {
        // Update viewport
        glViewport(0, 0, width, height);

        GLsizei scale = ssaa ? 2 : 1; // Antialiasing?
        fbWidth = width * scale;
        fbHeight = height * scale;

        // Create new framebuffer texture
        createFrameBufferTexture(fbWidth, fbHeight);
    }

    void PathTracer::setClearColor(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
        clearColor = glm::vec4(r, g, b, 1.0f);
    }

    void PathTracer::restart() {
        // Clear framebuffer texture
        glClearTexImage(fbText, 0, GL_RGBA, GL_FLOAT, &clearColor.r);
        numSamples = 0;
    }

    void PathTracer::readFrameBuffer(uint8_t* image, size_t w, size_t h) const {
        glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
    }

    void PathTracer::createFrameBufferTexture(GLsizei width, GLsizei height) {
        // Destroy existing framebuffer texture
        glDeleteTextures(1, &fbText);

        // Create new framebuffer texture
        glGenTextures(1, &fbText);

        // Initialize framebuffer texture
        glBindTexture(GL_TEXTURE_2D, fbText);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width, height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    /** Helper method to create shaders */
    void createShaderProgram(opengl::ShaderProgram &program,
            const std::string vertex, const std::string frag) {
        opengl::ShaderObject vertexObject(GL_VERTEX_SHADER, vertex);
        vertexObject.create();
        vertexObject.compile();

        std::cout << "vert: " << vertexObject.getCompileLog() << std::endl;

        opengl::ShaderObject fragObject(GL_FRAGMENT_SHADER, frag);
        fragObject.create();
        fragObject.compile();

        std::cout << "frag: " << fragObject.getCompileLog() << std::endl;

        program.create();
        program.attach(vertexObject);
        program.attach(fragObject);
        program.link();

        std::cout << "link: " << program.getLinkLog() << std::endl;

        // Free resources
        vertexObject.destroy();
        fragObject.destroy();
    }

    /** Helper function to initialize compute shaders */
    void createComputeShaderProgram(opengl::ShaderProgram& program, const std::string& shaderSource) {
        // Create the shader object
        opengl::ShaderObject shaderObject(GL_COMPUTE_SHADER, shaderSource);
        shaderObject.create();
        shaderObject.compile();

        std::cout << "comp: " << shaderObject.getCompileLog() << std::endl;

        // Create shaders program
        program.create();
        program.attach(shaderObject);
        program.link();

        std::cout << "link: " << program.getLinkLog() << std::endl;

        // Free resources
        shaderObject.destroy();
    }

    void PathTracer::initShaders() {
        createShaderProgram(screenQuadProgram,
            // Just a simple way of loading shader sources
            #include "shaders/ScreenQuad.vert"
                    ,
            #include "shaders/ScreenQuad.frag"
        );
        createComputeShaderProgram(pathTracerProgram,
            #include "PathTracer.comp"
        );
    }

    void PathTracer::setPerspective(float fovy, float aspect, float zNear, float zFar) {
        projMat = glm::perspective(fovy, aspect, zNear, zFar);
    }

    void PathTracer::setMaxBounces(unsigned int maxBounces) {
        this->maxBounces = maxBounces;
    }

    void PathTracer::setActive(bool active) {
        this->isActive = active;
    }

    void PathTracer::setSSAA(bool ssaa) {
        this->ssaa = ssaa;
    }
}
