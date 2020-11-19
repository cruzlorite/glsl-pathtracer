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

#include "BufferObject.h"

namespace opengl {

    BufferObject::BufferObject(GLenum target)
        : Object()
        , target(target) {

    }

    void BufferObject::create() {
        // Generate Buffer object and check errors
        glGenBuffers(1, &handler);

        // Object correctly created
        setAsCreated();
    }


    void BufferObject::destroy() {
        // Free resources
        glDeleteBuffers(1, &handler);

        // Sanity clean
        target  = 0;

        // Object correctly destroyed
        setAsDestroyed();
    }

    void BufferObject::setTarget(GLenum target) {
        this->target = target;
    }

    GLenum BufferObject::getTarget() const {
        return target;
    }

    void BufferObject::bind() const {
        glBindBuffer(target, handler);
    }

    void BufferObject::unbind() const {
        glBindBuffer(target, 0);
    }

    void BufferObject::setData(void const* data, GLsizeiptr size, GLenum usage) {
        // Set data and check errors
        glBufferData(target, size, data, usage);
    }

    void BufferObject::setSubData(void const* data, GLsizeiptr size, GLintptr offset) {
        // Set data and check errors
        glBufferSubData(target, offset, size, data);
    }

}