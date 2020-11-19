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

#ifndef VOXFRACTURER_OPENGL_BUFFEROBJECT_H_
#define VOXFRACTURER_OPENGL_BUFFEROBJECT_H_

#include <vector>

#include <glad/glad.h>

#include "OpenGLError.h"
#include "Object.h"

namespace opengl {

    /**
     * OpenGL buffer object wrapper class
     * @see https://www.khronos.org/opengl/wiki/Buffer_Object
     */
    class BufferObject : public Object {
    public:

        /**
         * BufferObject constructor
         * @param[in] target GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER, etc...
         */
        BufferObject(GLenum target);

        /**
         * Construct the OpenGL object and reserve resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
         */
        virtual void create();

        /**
         * Destroy object and free resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml
         */
        virtual void destroy();

        /**
         * Set Buffer Object binding target
         * @param[in] target    Buffer target enum: GL_ARRAY_BUFFER, GL_ELEMENT_BUFFER, etc...
         * @return Buffer size in bytes
         */
        void setTarget(GLenum target);

        /**
         * Get Buffer Object binding target
         * @return Buffer Object binding target
         */
        GLenum getTarget() const;

        /**
         * Bind the buffer to the target
         * @note If the Object is not bound other methods my not work properly
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
         */
        void bind() const;

        /**
         * Unbind buffer to the target
         * @note If the Object is not bound other methods my not work properly
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
         */
        void unbind() const;

        /**
         * Set buffer data
         * @pre This Object is correctly bound
         * @param[in] data  pointer where it's the data
         * @param[in] size  Number of bytes we want to write
         * @param[in] usage Buffer usage enum: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, etc...
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
         */
        void setData(void const* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

        /**
         * Set buffer partial data
         * @pre This Object is correctly bound
         * @param[in] data      Pointer to the data
         * @param[in] size      Number of bytes we want to write
         * @param[in] offset    Buffer write offset in bytes
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferSubData.xhtml
         */
        void setSubData(void const* data, GLsizeiptr size, GLintptr offset);

        /**
         * Set buffer data from std::vector
         * @pre This Object is correctly bound
         * @param[in] data  std::vector with data
         * @param[in] usage Buffer usage enum: GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, etc...
         */
        template <typename T>
        void setData(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW);

        /**
         * Set buffer partial data form std::vector
         * @pre This Object is correctly bound
         * @param[in] data      std::vector with data
         * @param[in] offset    Buffer write offset in bytes
         */
        template <typename T>
        void setSubData(const std::vector<T>& data, GLintptr offset);

    protected:

        GLenum target;  //!< Buffer binding target
    };

    template <typename T>
    void BufferObject::setData(const std::vector<T>& data, GLenum usage) {
        setData(data.data(), sizeof(T) * data.size(), usage);
    }

    template <typename T>
    void BufferObject::setSubData(const std::vector<T>& data, GLintptr offset) {
        setSubData(data.data(), sizeof(T) * data.size(), offset);
    }

}

#endif //VOXFRACTURER_OPENGL_BUFFEROBJECT_H_
