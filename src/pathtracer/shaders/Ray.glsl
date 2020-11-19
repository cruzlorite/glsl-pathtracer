#ifndef RAY_GLSL
#define RAY_GLSL

// Ray struct
struct Ray {
    vec3 origin;    // Ray origin
    vec3 dir;       // Ray direcction vector
};

// evaluate ray at specified t parameter
vec3 ray_at(in Ray ray, in float t) {
    return ray.origin + (t * ray.dir);
}

#endif // RAY_GLSL