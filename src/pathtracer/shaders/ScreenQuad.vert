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

// Draw a texture ScreenQuad. Used to draw to framebuffer a image2D generated 
// via Compute Shader.

R"(#version 450

layout (location = 0) in vec2 position;

out vec2 textCoords;

void main() {
    textCoords = (position + 1.0f) / 2.0f;
    gl_Position = vec4(position, 0.0f, 1.0f);
}
)"
