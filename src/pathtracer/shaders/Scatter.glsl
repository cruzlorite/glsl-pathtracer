#ifndef SCATTER_GLSL
#define SCATTER_GLSL

#include "Ray.glsl"
#include "HitInfo.glsl"
#include "MaterialLibrary.glsl"
#include "Random.glsl"

// Scatter 
bool lambert_scatter(in Ray ray_in, in HitInfo hit, out vec3 att, out Ray ray_out) {
    vec3 scatter_direction = hit.normal + rand_unit_vector();
    ray_out = Ray(hit.point, scatter_direction);
    att = get_material_by_id(hit.mat_id).albedo;
    return true;
}

bool metal_scatter(in Ray ray_in, in HitInfo hit, out vec3 att, out Ray ray_out) {
    vec3 reflected = reflect(normalize(ray_in.dir), hit.normal);
    Material mat = get_material_by_id(hit.mat_id);
    ray_out = Ray(hit.point, reflected + mat.fuzz * rand_unit_vector());
    att = mat.albedo;
    return dot(ray_out.dir, hit.normal) > 0.0f;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1.0f - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
}

// Dielectric 
bool dielectric_scatter(in Ray ray_in, in HitInfo hit, out vec3 att, out Ray ray_out) {
    Material mat = get_material_by_id(hit.mat_id);
    att = vec3(1.0f);
    float eta = hit.front_face ? (1.0f / mat.ref_idx) :  mat.ref_idx; 

    vec3 unitdir = normalize(ray_in.dir);
    float cos_theta = min(dot(-unitdir, hit.normal), 1.0f);
    float sin_theta = sqrt(1.0f - (cos_theta * cos_theta));
    if (eta * sin_theta > 1.0f) {
        vec3 reflected = reflect(unitdir, hit.normal);
        ray_out = Ray(hit.point, reflected);
        return true;
    }

    float reflect_prob = schlick(cos_theta, eta);
    if (randf() < reflect_prob) {
        vec3 reflected = reflect(unitdir, hit.normal);
        ray_out = Ray(hit.point, reflected);
        return true;
    }

    vec3 refracted = refract(unitdir, hit.normal, eta);
    ray_out = Ray(hit.point, refracted);
    return true;
}

// Check material type and use the corresponding function
bool scatter(in Ray ray_in, in HitInfo hit, out vec3 att, out Ray ray_out) {
    Material mat = get_material_by_id(hit.mat_id);
    
    switch(mat.type) {
        case LAMBERT:
            return lambert_scatter(ray_in, hit, att, ray_out);
        case METAL:
            return metal_scatter(ray_in, hit, att, ray_out);
        default:
            return dielectric_scatter(ray_in, hit, att, ray_out);
    }
}

#endif // SCATTER_GLSL