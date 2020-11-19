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

#include "ShaderObject.h"

namespace opengl {

    ShaderObject::ShaderObject(GLenum type)
            : Object()
            , _type(type)
            , _source()
            , _compileStatus(GL_FALSE)
            , _compileLog() {

    }

    ShaderObject::ShaderObject(GLenum type, std::string const& source)
        : ShaderObject(type) {
        addSource(source);
    }

    void ShaderObject::create() {
        // Create OpenGL shaders object
        handler = glCreateShader(_type);
        checkOpenGLError(glCreateProgram);

        // The Shader object has been correctly created
        setAsCreated();
    }

    void ShaderObject::destroy() {
        // Release resources
        glDeleteShader(handler);

        // Sanity
        handler         = 0;
        _compileStatus  = GL_FALSE;
        _compileLog     = "";

        // The Shader object has been correctly destroyed
        setAsDestroyed();
    }

   void ShaderObject::compile() {
        // Set source code and compile it
        const char* cstr = _source.c_str();
        glShaderSource(handler, 1, &cstr, NULL);
        glCompileShader(handler);

        // Get compilation status
        glGetShaderiv(handler, GL_COMPILE_STATUS, &_compileStatus);

        // Check if compilation ran well
        if (_compileStatus == GL_FALSE) {
            // Get message length
            GLint logLen = 0;
            glGetShaderiv(handler, GL_INFO_LOG_LENGTH, &logLen);

            // Get log messages
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(handler, logLen, &written, cLogString);
                _compileLog.assign(cLogString);
                delete[] cLogString;
            }
        }
    }

    void ShaderObject::addSource(const std::string& source) {
        _source += source;
    }

    void ShaderObject::setSource(const std::string &source) {
        _source = source;
    }

    const std::string& ShaderObject::getSource() const {
        return _source;
    }

    GLenum ShaderObject::getType() const {
        return _type;
    }

    GLint ShaderObject::getCompileStatus() const {
        return _compileStatus;
    }

    std::string const& ShaderObject::getCompileLog() const {
        return _compileLog;
    }

    GLint ShaderObject::getHandler() const {
        return handler;
    }

};