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

#include "Object.h"

namespace opengl {

    Object::Object()
        : handler(0)
        , created(false) {

    }

    bool Object::isCreated() const {
        return created;
    }

    void Object::setAsCreated() {
        created = true;
    }

    void Object::setAsDestroyed() {
        created = false;
        handler = 0;
    }

    GLuint Object::getHandler() const {
        return handler;
    }
}
