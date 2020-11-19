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

#ifndef VOXFRACTURER_OPENGL_OPENGLERROR_H_
#define VOXFRACTURER_OPENGL_OPENGLERROR_H_

#include <string>
#include <stdexcept>

#include <glad/glad.h>

namespace opengl {

    /** Handy macro for checking OpenGL errors */
    #define checkOpenGLError(func) opengl::OpenGLError::checkError((__FILE__ + SOURCE_PATH_SIZE), __LINE__, #func)

    /**
     * @brief Thrown when an OpenGL error occurs
     */
    class OpenGLError : public std::runtime_error {
    public:
        explicit OpenGLError(const std::string& msg) : std::runtime_error(msg) {  }

        /**
         * Checks OpenGL error.
         * @param[in] file  File name of caller
         * @param[in] line  File line of caller
         * @param[in] func  OpenGL function whe are checking
         * @throws OpenGLError if some OpenGL error is detected
         */
         static void checkError(const std::string& file, int line, const std::string func) {
            const GLenum err = glGetError();
            if (err != GL_NO_ERROR)
                throw OpenGLError("OpenGLError: " + func + ": " + errToStr(err) +
                ": file: " + file + ": line: " + std::to_string(line));
         }

        /**
         * Translate error code to string.
         * @param[in] errCode   Error code returned by glGetError()
         */
        static std::string errToStr(GLenum errCode) {
            switch (errCode) {
                case GL_INVALID_ENUM:       return "GL_INVALID_ENUM";
                case GL_INVALID_VALUE:      return "GL_INVALID_VALUE";
                case GL_INVALID_OPERATION:  return "GL_INVALID_OPERATION";
                case GL_STACK_OVERFLOW:     return "GL_STACK_OVERFLOW";
                case GL_STACK_UNDERFLOW:    return "GL_STACK_UNDERFLOW";
                case GL_OUT_OF_MEMORY:      return "GL_OUT_OF_MEMORY";
                default:                    return "UNKNOWN ERROR";
            }
        }
    };
}

#endif //VOXFRACTURER_OPENGL_OPENGLERROR_H_
