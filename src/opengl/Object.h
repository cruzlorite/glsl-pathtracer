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

#ifndef VOXFRACTURER_OPENGL_OBJECT_H_
#define VOXFRACTURER_OPENGL_OBJECT_H_

#include <stdexcept>

#include <glad/glad.h>

#include "OpenGLError.h"

namespace opengl {

    /**
     * Abtract class for OpenGL wrapper classes
     * @see https://www.khronos.org/opengl/wiki/OpenGL_Object#Object_Creation_and_Destruction
     */
    class Object {
    public:

        // It has no sense to copy a OpenGL object
        Object(const Object&)               = delete;
        Object(Object&&)                    = delete;
        Object& operator=(const Object&)    = delete;
        Object& operator=(Object&&)         = delete;

        /** Object constructor. Real `constructions` is performed on create() */
         Object();

        /**
         * Construct the OpenGL object and reserve resources
         * @throws OpenGLError if some OpenGL error is detected during creation (This Object is not usable)
         * @see https://www.khronos.org/opengl/wiki/OpenGL_Object#Object_Creation_and_Destruction
         */
        virtual void create() = 0;

        /**
         * Destroy object and free resources
         * @see https://www.khronos.org/opengl/wiki/OpenGL_Object#Object_Creation_and_Destruction
         */
        virtual void destroy() = 0;

        /**
         * Returns whether or not is the object created
         * @return True if the object has been created, false if not
         */
        bool isCreated() const;

        /**
         * Get object handler
         * @return The OpenGL object handler
         * @see https://www.khronos.org/opengl/wiki/OpenGL_Object#Object_Usage
         */
        GLuint getHandler() const;

    protected:

        /** Set the Object as created */
        void setAsCreated();

        /** Set the Object as destroyed */
        void setAsDestroyed();

        GLuint handler; //!< OpenGL Object handler

    private:

        bool created; //!< Is this Object created?
    };

};

#endif //VOXFRACTURER_OPENGL_OBJECT_H_
