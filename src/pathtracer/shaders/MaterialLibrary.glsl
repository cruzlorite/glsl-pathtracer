#ifndef MATERIALLIBRARY_GLSL
#define MATERIALLIBRARY_GLSL

#include "Material.glsl"

#define NUM_MATERIALS 9

// List of materials
const Material materials[] = { 
    Material(false, LAMBERT, 0.0f, 0.0f, vec3(0.1f, 0.1f, 1.0f)),
    Material(false, METAL, 0.5f, 0.0f, vec3(0.7f, 0.7f, 0.7f)),
    Material(false, METAL, 0.0f, 0.0f, vec3(1.0f, 1.0f, 1.0f)),
    Material(false, DIELECTRIC, 0.9f, 1.5f, vec3(1.0f, 1.0f, 1.0f)),
    Material(false, METAL, 0.5f, 0.0f, vec3(0.1f, 1.0f, 0.1f)),
    Material(false, METAL, 0.0f, 0.5f, vec3(1.0f, 0.3f, 0.3f)),
    Material(false, METAL, 9.0f, 0.5f, vec3(1.0f, 0.3f, 0.3f)),
    Material(false, LAMBERT, 9.0f, 0.5f, vec3(0.8f, 0.3f, 0.8f)),
    Material(false, LAMBERT, 9.0f, 0.5f, vec3(0.35f, 0.9f, 0.35f))
};

// Find material on material list
#define get_material_by_id(id) materials[id]

#endif // MATERIALLIBRARY_GLSL
