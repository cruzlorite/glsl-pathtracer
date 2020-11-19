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

#include "ShaderProgram.h"

namespace opengl {

    ShaderProgram::ShaderProgram()
        : Object()
        , linkStatus(GL_FALSE)
        , linkLog() {

    }

    void ShaderProgram::create() {
        // Create shaders program and check errors
        handler = glCreateProgram();
        checkOpenGLError(glCreateProgram);

        // The Object was correctly created
        setAsCreated();
    }

    void ShaderProgram::destroy() {
        glDeleteProgram(handler);
        linkStatus = GL_FALSE;
        linkLog    = "";

        // Object correctly destroyed
        setAsDestroyed();
    }

    GLint ShaderProgram::getLinkStatus() const {
        return linkStatus;
    }

    std::string const& ShaderProgram::getLinkLog() const {
        return linkLog;
    }

    void ShaderProgram::link() {
        // Link and check errors
        glLinkProgram(handler);

        // Get linking status
        glGetProgramiv(handler, GL_LINK_STATUS, &linkStatus);

        // Check if linking went wrong
        if (linkStatus  == GL_FALSE) {
            // Get log message length
            GLint logLen = 0;
            glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logLen);

            // Get log message
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetProgramInfoLog(handler, logLen, &written, cLogString);
                linkLog.assign(cLogString);
                delete[] cLogString;
            }
        }
    }

    void ShaderProgram::use() const {
        glUseProgram(handler);
    }

    void ShaderProgram::attach(const ShaderObject& shader) const {
        glAttachShader(handler, shader.getHandler());
    }

    void ShaderProgram::detach(const ShaderObject& shader) const {
        glDetachShader(handler, shader.getHandler());
    }

    bool ShaderProgram::uniform(std::string const& name, GLint value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform1i(location, value);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, GLuint value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform1ui(location, value);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, GLfloat value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform1f(location, value);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, glm::vec3 const& value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform3fv(location, 1, &value[0]);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, glm::uvec3 const& value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform3uiv(location, 1, &value[0]);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, glm::vec4 const& value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform4fv(location, 1, &value[0]);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, glm::mat4 const& value) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
            return true;
        }
        else return false;
    }

    bool ShaderProgram::uniform(std::string const& name, GLsizei size, const GLuint* pointer) const {
        GLint location = glGetUniformLocation(handler, name.c_str());
        if (location >= 0) {
            glUniform1uiv(location, size, pointer);
            return true;
        }
        else return false;
    }

};