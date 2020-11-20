//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of Pathtracer.
//
//    Pathtracer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Pathtracer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Pathtracer.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PATHTRACER_SCREENQUAD_H_
#define PATHTRACER_SCREENQUAD_H_

#include <iostream>

#include <glad/glad.h>

#include "../opengl/VertexArrayObject.h"
#include "../opengl/BufferObject.h"

namespace pathtracer {

    /** ScreenQuad: It simply renders a quad where to draw a texture. */
    class ScreenQuad : public opengl::VertexArrayObject {
    public:

        /** Screen Quad vertices */
        static const GLfloat QUAD_VERTICES[12]; // 6 vertices, 12 floats

        /** Default constructor */
        ScreenQuad();

        /** Create the object. */
        void create();

        /** Free resources */
        void destroy();

        /** Render the Screen Quad */
        void render() const;

    private:

        opengl::BufferObject vbo; //!< Vbo for vertices data
    };

}

#endif //PATHTRACER_SCREENQUAD_H_
