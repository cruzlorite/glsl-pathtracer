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

#ifndef VOXFRACTURER_OPENGL_SHADERPROGRAM_H_
#define VOXFRACTURER_OPENGL_SHADERPROGRAM_H_

#include <vector>
#include <string>

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include "ShaderObject.h"

namespace opengl {

    /***
     * OpenGL Shader Program wrapper class
     * @see https://www.khronos.org/opengl/wiki/GLSL_Object#Program_objects
     */
    class ShaderProgram : public opengl::Object {
    public:

        /**
         * ShaderProgram constructor
         */
        ShaderProgram();

        /**
         * Construct the OpenGL object and reserve resources
         */
        virtual void create();

        /**
         * Destroy object and free resources
         */
        virtual void destroy();

        /**
         * Link the shaders program
         * @see https://www.khronos.org/opengl/wiki/Shader_Compilation
         */
        void link();

        /**
         * Use the shaders program
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
         */
        void use() const;

        /**
         * Attach a shaders object to the shaders program
         * @param[in][in] shader    ShaderObject to be attached to this ShaderProgram
         */
        void attach(const ShaderObject& shader) const;

        /**
         * Detach a shaders object from the shaders program
         * @param[in][in] shader    ShaderObject to be detached from this ShaderProgram
         */
        void detach(const ShaderObject& shader) const;

        /**
         * The link status, GL_TRUE or GL_FALSE
         * @return Shader program linking status
         */
        GLint getLinkStatus() const;

        /**
         * Get linking log message
         * @return Linking log message
         */
        const std::string& getLinkLog() const;

        /**
         * Set shaders uniform
         * @note No sanity checks are done on this methods
         * @param[in] name  Uniform in shaders name
         * @param[in] value Value we want to set
         * @return True if the uniform was set correctly, false if not
         */
        ///@{
        bool uniform(std::string const& name, GLfloat value) const;
        bool uniform(std::string const& name, GLint   value) const;
        bool uniform(std::string const& name, GLuint  value) const;
        bool uniform(std::string const& name, glm::vec2 const& value) const;
        bool uniform(std::string const& name, glm::vec3 const& value) const;
        bool uniform(std::string const& name, glm::uvec3 const& value) const;
        bool uniform(std::string const& name, glm::vec4 const& value) const;
        bool uniform(std::string const& name, glm::mat3 const& value) const;
        bool uniform(std::string const& name, glm::mat4 const& value) const;
        ///@}

        /**
         * Set glm::vec3 array uniform
         * @param[in] name  Uniform name
         * @param[in] size  Array size
         * @param[in] data  Pointer to data
         * @return True if the uniform was set correctly, false if not
         */
        bool uniform(std::string const& name, GLsizei size, const GLuint* pointer) const;

    private:

        GLint       linkStatus; //!< Is the shaders program linked?
        std::string linkLog;    //!< link log message
    };

};

#endif //VOXFRACTURER_OPENGL_SHADERPROGRAM_H_
