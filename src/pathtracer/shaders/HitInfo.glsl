#ifndef HITINFO_GLSL
#define HITINFO_GLSL

// Info required to process a hit
struct HitInfo {
    bool  front_face;   // Front face hit?
    uint  mat_id;       // Material id of hitted surface
    float ray_t;        // Ray t parameter
    vec3  point;        // Geometric point where the hit occurred
    vec3  normal;       // Normal vector of hitted surface
};

// Compute face normal
void hit_set_face_normal(in Ray ray, inout HitInfo hit) {
    hit.front_face = dot(ray.dir, hit.normal) < 0.0f;
    hit.normal = hit.front_face ? hit.normal : -hit.normal;
}

#endif // HITINFO_GLSL

