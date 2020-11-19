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

#ifndef VOXFRACTURER_OPENGL_SHADEROBJECT_H_
#define VOXFRACTURER_OPENGL_SHADEROBJECT_H_

#include <string>

#include <glad/glad.h>

#include "OpenGLError.h"
#include "Object.h"

namespace opengl {

    /**
     * OpenGL Shader Object wrapper class
     * @see https://www.khronos.org/opengl/wiki/Shader
     */
    class ShaderObject : public opengl::Object {
    public:

        /**
         * Shader object construction
         * @param[in] type The shaders type GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, etc...
         */
        ShaderObject(GLenum type);

        /**
         * Shader object construction
         * @param[in] type      GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, etc...
         * @param[in] source    The shaders source code
         */
        ShaderObject(GLenum type, std::string const& source);

        /**
         * Construct the OpenGL object and reserve resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
         */
        void create();

        /**
         * Destroy object and free resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
         */
        void destroy();

        /**
         * Compile shaders
         * @see https://www.khronos.org/opengl/wiki/Shader_Compilation
         */
        void compile();

        /**
         * Appends source code
         * @param[in] source More shaders code
         */
        void addSource(const std::string& source);

        /**
         * Appends source code
         * @param[in] source Shader source code
         */
        void setSource(const std::string& source);

        /**
         * Get shaders type
         * @return The shaders type
         */
        GLenum getType() const;

        /**
         * Get shaders source code
         * @return The shaders source code
         */
        std::string const& getSource() const;

        /**
         * Get shaders compilation status
         * @return The compilation status: GL_TRUE or GL_FALSE
         */
        GLint getCompileStatus() const;

        /**
         * Get (if available) shaders compilation los message
         * @return The compilation log message
         */
        const std::string& getCompileLog() const;

        /**
         * Get OpenGL Object handler
         * @Return The OpenGL shaders object handler
         */
         GLint getHandler() const;

    private:

        GLenum      _type;            //!< ShaderObject type
        std::string _source;          //!< The shaders source code

        GLint       _compileStatus;   //!< Compilation status
        std::string _compileLog;      //!< Compilation log message
    };

};

#endif //OPENGL_SHADEROBJECT_H
