#include <nds.h>

/* some stupid math utilities */
typedef struct
{
    float32 x;
    float32 y;
} vector2;

static inline vector2 vector2_add(vector2 a, vector2 b) {
    vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

static inline vector2 vector2_scalar(vector2 v, float32 s) {
    vector2 result;
    result.x = v.x * s;
    result.y = v.y * s;
    return result;
}