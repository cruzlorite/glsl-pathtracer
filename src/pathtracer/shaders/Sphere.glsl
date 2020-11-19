#ifndef SPHERE_GLSL
#define SPHERE_GLSL

#include "Ray.glsl"
#include "HitInfo.glsl"

// Sphere shape structure
struct Sphere {
    uint    mat_id; // Index of material in material list
    float   radius; // Sphere radius
    vec3    center; // Sphere geometric center
};

// Intersect Ray-Sphere test
bool hit_sphere(Sphere sphere, Ray ray, float min, float max, inout HitInfo hit) {
    vec3 oc = ray.origin - sphere.center;
    float a = dot(ray.dir, ray.dir);
    float half_b = dot(oc, ray.dir);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant > 0.0f) {
        float root = sqrt(discriminant);

        float t1 = (-half_b - root) / a;
        if (t1 < max && t1 > min) {
            hit.ray_t  = t1;
            hit.point  = ray_at(ray, t1);
            hit.normal = (hit.point - sphere.center) / sphere.radius;
            hit.mat_id = sphere.mat_id;
            hit_set_face_normal(ray, hit);
            return true;
        }

        float t2 = (-half_b + root) / a;
        if (t2 < max && t2 > min) {
            hit.ray_t  = t2;
            hit.point  = ray_at(ray, t2);
            hit.normal = (hit.point - sphere.center) / sphere.radius;
            hit.mat_id = sphere.mat_id;
            hit_set_face_normal(ray, hit);
            return true;
        }
    } 

    return false;
}

#endif // SPHERE_GLSL

