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

#include "VertexArrayObject.h"

namespace opengl {

    void VertexArrayObject::create() {
        // Generate VertexArrayObject and check errors
        glGenVertexArrays(1, &handler);
        checkOpenGLError(glGenVertexArrays);

        // Object correctly created
        setAsCreated();
    }

    void VertexArrayObject::destroy() {
        // Free resources
        glDeleteVertexArrays(1, &handler);

        // Object correctly destroyed
        setAsDestroyed();
    }

    void VertexArrayObject::bind() const {
        glBindVertexArray(handler);
    }

    void VertexArrayObject::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArrayObject::enableAttrib(GLuint attribindex) const {
        glEnableVertexArrayAttrib(handler, attribindex);
    }

    void VertexArrayObject::disableAttrib(GLuint attribindex) const {
        glDisableVertexArrayAttrib(handler, attribindex);
    }

    void VertexArrayObject::bindBuffer(GLuint bindingindex, const BufferObject& buffer, GLintptr offset,
            GLsizei stride) const {
        glVertexArrayVertexBuffer(handler, bindingindex, buffer.getHandler(), offset, stride);
    }

    void VertexArrayObject::setBindingDivisor(GLuint bindingindex, GLuint divisor) const {
        glVertexArrayBindingDivisor(handler, bindingindex, divisor);
    }

    void VertexArrayObject::attribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized,
            GLuint offset) const {
        enableAttrib(attribindex);
        glVertexArrayAttribFormat(handler, attribindex, size, type, normalized, offset);
    }

    void VertexArrayObject::attribBinding(GLuint attribindex, GLuint bindingindex) const {
        glVertexArrayAttribBinding(handler, attribindex, bindingindex);
    }

    void VertexArrayObject::drawElements(const BufferObject& ibo, GLenum mode, GLuint count, GLenum type) const {
        // Bind buffer object
        ibo.bind();

        glDrawElements(mode, count, type, nullptr);

        // Bind to zero
        ibo.unbind();
    }

    void VertexArrayObject::drawArrays(GLenum  mode, GLuint  first, GLsizei count) const {
        glDrawArrays(mode, first, count);
    }

}