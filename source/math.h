#include <nds.h>

/* some stupid math utilities */
typedef struct
{
    s16 x;
    s16 y;
} vector2;

typedef struct
{
    float x;
    float y;
} vector2_float;

static inline vector2 vector2_add(vector2 a, vector2 b)
{
    vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

static inline vector2_float vector2f_add(vector2_float a, vector2_float b)
{
    vector2_float result;
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

static inline u16 vector2_squaremag(vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

static inline vector2 vector2_scalar(vector2 v, float s)
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