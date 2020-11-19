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

#include "ScreenQuad.h"

namespace pathtracer {

    const GLfloat ScreenQuad::QUAD_VERTICES[12] = {
        -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f
    };

    ScreenQuad::ScreenQuad()
        : opengl::VertexArrayObject()
        , vbo(GL_ARRAY_BUFFER) {

    }

    void ScreenQuad::create() {
        // Init VAO
        opengl::VertexArrayObject::create();
        opengl::VertexArrayObject::bind();

        // Create vbo with vertices
        vbo.create();
        vbo.bind();
        vbo.setData(QUAD_VERTICES, sizeof(QUAD_VERTICES), GL_STATIC_DRAW);

        // Specify attrib 0
        attribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);
        attribBinding(0, 0);
        glBindVertexBuffer(0, vbo.getHandler(), 0, sizeof(GLfloat) * 2); // 2 GLfloat per vertex

        // Unbind
        vbo.unbind();
        opengl::VertexArrayObject::unbind();
    }

    void ScreenQuad::destroy() {
        vbo.destroy();
        opengl::VertexArrayObject::destroy();
    }

    void ScreenQuad::render() const {
        opengl::VertexArrayObject::bind();
        opengl::VertexArrayObject::drawArrays(GL_TRIANGLES, 0, 6);
        opengl::VertexArrayObject::unbind();
    }
}