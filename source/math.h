#include <nds.h>

/* some stupid math utilities */
typedef struct
{
    float32 x;
    float32 y;
} vector2;

static inline vector2 vector2_add(vector2 a, vector2 b)
{
    vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

static inline vector2 vector2_subtract(vector2 a, vector2 b)
{
    vector2 result = a;
    result.x = result.x - b.x;
    result.y = result.y - b.y;
    return result;
}

static inline float vector2_magnitude(vector2 v)
{
    return sqrt32(v.x * v.x + v.y * v.y);
}

static inline vector2 vector2_scalar(vector2 v, float32 s)
{
    vector2 result;
    result.x = v.x * s;
    result.y = v.y * s;
    return result;
}

/* some evaluation functions */
static inline int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

static inline float float_max(float a, float b)
{
    if (a > b)
        return a;
    return b;
}