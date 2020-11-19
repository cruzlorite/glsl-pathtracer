#ifndef RANDF_GLSL
#define RANDF_GLSL

#include "Constants.glsl"

// Pseudo random number generation in GPU

// Value with random state
uint rng_state;

// Initialize random state
void randf_seed(uint value) {
    // We must setup rng state with unique value for every therad
    rng_state = gl_GlobalInvocationID.x * (gl_NumWorkGroups * gl_WorkGroupSize).y +
        gl_GlobalInvocationID.y;
    rng_state = rng_state * value * 3451031;
}

// @see http://www.reedbeta.com/blog/quick-and-easy-gpu-random-numbers-in-d3d11/
uint rand_xorshift() {
    // Xorshift algorithm from George Marsaglia's paper
    rng_state ^= (rng_state << 13);
    rng_state ^= (rng_state >> 17);
    rng_state ^= (rng_state << 5);
    return rng_state;
}

// Wang hashing fuction
uint wang_hash(uint seed) {
    seed = (seed ^ uint(61)) ^ (seed >> uint(16));
    seed *= uint(9);
    seed = seed ^ (seed >> uint(4));
    seed *= uint(0x27d4eb2d);
    seed = seed ^ (seed >> uint(15));
    return seed;
}

// Combine both to gererate random floats on range [0, 1]
float randf() {
    uint seed = wang_hash(rand_xorshift());
    return float(seed) / 4294967296.0f;
}

// Random unit vector for lambertian reflection
vec3 rand_unit_vector() {
    float a = randf() * 2.0f * PI;
    float z = (randf() * 2.0f) - 1.0f;
    float r = sqrt(1.0f - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

#endif // RANDF_GLSL