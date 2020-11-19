#ifndef MATERIAL_GLSL
#define MATERIAL_GLSL

#define LAMBERT     0
#define METAL       1
#define DIELECTRIC  2

struct Material {
    bool isEmisive;
    uint type;
    float fuzz;
    float ref_idx; // refract index
    vec3 albedo;
};

#endif // MATERIAL_GLSL