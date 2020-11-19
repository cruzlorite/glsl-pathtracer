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

#ifndef VOXFRACTURER_OPENGL_VERTEXARRAYOBJECT_H_
#define VOXFRACTURER_OPENGL_VERTEXARRAYOBJECT_H_

#include "BufferObject.h"

namespace opengl {

    /**
     * OpenGL Vertex Array Object wrapper class
     * @see https://www.khronos.org/opengl/wiki/Vertex_Specification
     */
    class VertexArrayObject : public opengl::Object {
    public:

        /**
         * Construct the OpenGL object and reserve resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
         */
        virtual void create();

        /**
         * Destroy object and free resources
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml
         */
        virtual void destroy();

        /**
         * Bind vertex array object
         * @note If the Object is not bound other methods won't work properly
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
         */
        void bind() const;

        /**
         * Unbind
         * @note If the Object is not bound other methods won't work properly
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
         */
        void unbind() const;

        /**
         * Bind a buffer to a vertex buffer bind point
         * @param[in] bindingindex  The index of the vertex buffer binding point to which to bind the buffer
         * @param[in] buffer        The buffer to bind to the vertex buffer binding point
         * @param[in] offset        The offset of the first element of the buffer
         * @param[in] stride        The distance between elements within the buffer
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexBuffer.xhtml
         */
        void bindBuffer(
                GLuint bindingindex,
                const BufferObject& buffer,
                GLintptr offset,
                GLsizei stride) const;

        /**
         * Modify the rate at which generic vertex attributes advance
         * @param[in] bindingindex  The index of the vertex buffer binding point
         * @param[in] divisor       The new value for the instance step rate to apply
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexBindingDivisor.xhtml
         */
        void setBindingDivisor(
                GLuint bindingindex,
                GLuint divisor) const;

        /**
         * Enable generic vertex attribute
         * @param[in] attribindex   The index of generic vertex attribute
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
         */
        void enableAttrib(GLuint attribindex) const;

        /**
         * Disable generic vertex attribute
         * @param[in] attribindex   The index of the generic vertex attribute
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
         */
        void disableAttrib(GLuint attribindex) const;

        /**
         * Specify generic vertex attribute format
         * @param[in] attribindex   The generic vertex attribute array being described
         * @param[in] size          The number of values per vertex that are stored in the array
         * @param[in] type          The type of the data stored in the array
         * @param[in] normalized    GL_TRUE if the param[in][in]eter represents a normalized integer. GL_FALSE otherwise
         * @param[in] offset        The offset of the first element
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribFormat.xhtml
         */
         void attribFormat(
                 GLuint     attribindex,
                 GLint      size,
                 GLenum     type,
                 GLboolean  normalized,
                 GLuint     offset) const;

        /**
         * Associate a vertex attribute and a vertex buffer binding for this vertex array object
         * @param[in] attribindex   The index of the attribute to associate with a BufferObject.
         * @param[in] bindingindex  The index of the vertex buffer binding
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribBinding.xhtml
         */
        void attribBinding(GLuint attribindex,  GLuint bindingindex) const;

        /**
         * Render primitives from VertexArrayObject using indices (glDrawElements)
         * @pre This Object is correctly bound
         * @param[in] ibo   BufferObject with drawing indices
         * @param[in] mode  Drawing primitive: GL_POINTS, GL_TRIANGLES, etc...
         * @param[in] count Specifies the number of elements to be rendered
         * @param[in] type  Indices type: GL_UNSIGNED_INT, GL_UNSIGNED _SHORT, etc...
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawElements.xhtml
         */
        void drawElements(
                const BufferObject& ibo,
                GLenum mode,
                GLuint size,
                GLenum type) const;

        /**
         * Render primitives from VertexArrayObject (glDrawArrays)
         * @param[in] mode  Drawing primitive: GL_POINTS, GL_TRIANGLES, etc...
         * @param[in] first Specifies the starting index in the enabled arrays
         * @param[in] count Specifies the number of indices to be rendered
         * @see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
         */
        void drawArrays(
                GLenum  mode,
                GLuint  first,
                GLsizei count) const;
    };

}

#endif //VOXFRACTURER_OPENGL_VERTEXARRAYOBJECT_H_
