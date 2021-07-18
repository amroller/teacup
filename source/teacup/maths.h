// MIT License
//
// Copyright (c) 2021 Aaron M. Roller
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef TC_MATHS_HEADER_GUARD
#define TC_MATHS_HEADER_GUARD

#include <teacup/types.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// Math primitives

union Vec4 {
    struct {
        F32 x, y, z, w;
    };
    F32 raw[4];
};

union Vec3 {
    struct {
        F32 x, y, z;
    };
    F32 raw[3];
};

union Vec2 {
    struct {
        F32 x, y;
    };
    F32 raw[2];
};

union Mat4 {
    struct {
        F32 m0,  m1,  m2,  m3;
        F32 m4,  m5,  m6,  m7;
        F32 m8,  m9,  m10, m11;
        F32 m12, m13, m14, m15;
    };
    F32 raw[4][4];
};

union Quat {
    struct {
        F32 x, y, z, w;
    };
    F32 raw[4];
};

struct Box3 {
    Vec3 min, max;
};

struct Box2 {
    Vec2 min, max;
};

////////////////////////////////////////////////////////////////////////////////
// Base functions

inline F32 Cos(F32 a) {
    return cosf(a);
}

inline F32 Sin(F32 a) {
    return sinf(a);
}

inline F32 Tan(F32 a) {
    return tanf(a);
}

inline F32 ACos(F32 a) {
    return acosf(a);
}

inline F32 ASin(F32 a) {
    return asinf(a);
}

inline F32 ATan(F32 a) {
    return atanf(a);
}

inline F32 ATan2(F32 a, F32 b) {
    return atan2f(a, b);
}

inline F32 LogBaseE(F32 a) {
    return logf(a);
}

inline F32 LogBase2(F32 a) {
    return log2f(a);
}

inline F32 LogBase10(F32 a) {
    return log10f(a);
}

inline F32 Pow(F32 a, F32 b) {
    return powf(a, b);
}

inline F32 Sqrt(F32 a) {
    return sqrtf(a);
}

inline F32 Min(F32 a, F32 b) {
    return TC_MIN(a, b);
}

inline F32 Max(F32 a, F32 b) {
    return TC_MAX(a, b);
}

inline F32 Floor(F32 a) {
    return floorf(a);
}

inline F32 Ceil(F32 a) {
    return ceilf(a);
}

inline F32 Abs(F32 a) {
    return fabsf(a);
}

////////////////////////////////////////////////////////////////////////////////
// Vector 4D functions

inline Vec4 operator-(Vec4 a) {
    return {-a.x, -a.y, -a.z, -a.w};
}

inline Vec4 operator+(Vec4 a, Vec4 b) {
    return {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
}

inline Vec4 operator-(Vec4 a, Vec4 b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
}

inline Vec4 operator*(Vec4 a, F32 b) {
    return {a.x*b, a.y*b, a.z*b, a.w*b};
}

inline Vec4 operator*(F32 a, Vec4 b) {
    return {a*b.x, a*b.y, a*b.z, a*b.w};
}

inline Vec4 operator/(Vec4 a, F32 b) {
    F32 inv = 1.0f / b;
    return {a.x*inv, a.y*inv, a.z*inv, a.w*inv};
}

inline Vec4 operator/(F32 a, Vec4 b) {
    return {a/b.x, a/b.y, a/b.z, a/b.w};
}

////////////////////////////////////////////////////////////////////////////////
// Vector 3D functions

inline Vec3 operator-(Vec3 a) {
    return {-a.x, -a.y, -a.z};
}

inline Vec3 operator+(Vec3 a, Vec3 b) {
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline Vec3 operator-(Vec3 a, Vec3 b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline Vec3 operator*(Vec3 a, F32 b) {
    return {a.x*b, a.y*b, a.z*b};
}

inline Vec3 operator*(F32 a, Vec3 b) {
    return {a*b.x, a*b.y, a*b.z};
}

inline Vec3 operator/(Vec3 a, F32 b) {
    F32 inv = 1.0f / b;
    return {a.x*inv, a.y*inv, a.z*inv};
}

inline Vec3 operator/(F32 a, Vec3 b) {
    return {a/b.x, a/b.y, a/b.z};
}

inline F32 Dot(Vec3 a, Vec3 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vec3 Cross(Vec3 a, Vec3 b) {
    F32 x = a.y*b.z - a.z*b.y;
    F32 y = a.z*b.x - a.x*b.z;
    F32 z = a.x*b.y - a.y*b.x;
    return {x, y, z};
}

inline F32 LengthSquared(Vec3 a) {
    return Dot(a, a);
}

inline F32 Length(Vec3 a) {
    return Sqrt(LengthSquared(a));
}

inline Vec3 Normalize(Vec3 a) {
    return a * (1.0f / Length(a));
}

inline Vec3 Lerp(Vec3 a, Vec3 b, F32 t) {
    return (1.0f-t)*a + t*b;
}

inline Vec3 Min(Vec3 a, Vec3 b) {
    F32 x = Min(a.x, b.x);
    F32 y = Min(a.y, b.y);
    F32 z = Min(a.z, b.z);
    return {x, y, z};
}

inline Vec3 Max(Vec3 a, Vec3 b) {
    F32 x = Max(a.x, b.x);
    F32 y = Max(a.y, b.y);
    F32 z = Max(a.z, b.z);
    return {x, y, z};
}

////////////////////////////////////////////////////////////////////////////////
// Vector 2D functions

inline Vec2 operator-(Vec2 a) {
    return {-a.x, -a.y};
}

inline Vec2 operator+(Vec2 a, Vec2 b) {
    return {a.x+b.x, a.y+b.y};
}

inline Vec2 operator-(Vec2 a, Vec2 b) {
    return {a.x-b.x, a.y-b.y};
}

inline Vec2 operator*(Vec2 a, F32 b) {
    return {a.x*b, a.y*b};
}

inline Vec2 operator*(F32 a, Vec2 b) {
    return {a*b.x, a*b.y};
}

inline Vec2 operator/(Vec2 a, F32 b) {
    F32 inv = 1.0f / b;
    return {a.x*inv, a.y*inv};
}

inline Vec2 operator/(F32 a, Vec2 b) {
    return {a/b.x, a/b.y};
}

inline F32 Dot(Vec2 a, Vec2 b) {
    return a.x*b.x + a.y*b.y;
}

inline F32 Cross(Vec2 a, Vec2 b) {
    return a.x*b.y - a.y*b.x;
}

inline F32 LengthSquared(Vec2 a) {
    return Dot(a, a);
}

inline F32 Length(Vec2 a) {
    return Sqrt(LengthSquared(a));
}

inline Vec2 Normalize(Vec2 a) {
    return a * (1.0f / Length(a));
}

inline Vec2 Lerp(Vec2 a, Vec2 b, F32 t) {
    return (1.0f-t)*a + t*b;
}

inline Vec2 Min(Vec2 a, Vec2 b) {
    F32 x = Min(a.x, b.x);
    F32 y = Min(a.y, b.y);
    return {x, y};
}

inline Vec2 Max(Vec2 a, Vec2 b) {
    F32 x = Max(a.x, b.x);
    F32 y = Max(a.y, b.y);
    return {x, y};
}

////////////////////////////////////////////////////////////////////////////////
// Matrix 4x4 functions

inline Mat4 Mat4Identity() {
    Mat4 mat = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return mat;
}

inline Mat4 operator+(Mat4 a, Mat4 b) {
    Mat4 mat = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat.raw[r][c] = a.raw[r][c] + b.raw[r][c];
        }
    }
    return mat;
}

inline Mat4 operator-(Mat4 a, Mat4 b) {
    Mat4 mat = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat.raw[r][c] = a.raw[r][c] - b.raw[r][c];
        }
    }
    return mat;
}

inline Mat4 operator*(Mat4 a, Mat4 b) {
    Mat4 mat = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat.raw[r][c] = a.raw[r][0] * b.raw[0][c] + a.raw[r][1] * b.raw[1][c] + a.raw[r][2] * b.raw[2][c] + a.raw[r][3] * b.raw[3][c];
        }
    }
    return mat;
}

inline Mat4 operator*(Mat4 a, F32 b) {
    Mat4 mat = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat.raw[r][c] = a.raw[r][c] * b;
        }
    }
    return mat;
}

inline Mat4 operator*(F32 a, Mat4 b) {
    Mat4 mat = {};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            mat.raw[r][c] = a * b.raw[r][c];
        }
    }
    return mat;
}

inline Mat4 Transpose(Mat4 a) {
    Mat4 mat = {
        a.raw[0][0], a.raw[1][0], a.raw[2][0], a.raw[3][0],
        a.raw[0][1], a.raw[1][1], a.raw[2][1], a.raw[3][1],
        a.raw[0][2], a.raw[1][2], a.raw[2][2], a.raw[3][2],
        a.raw[0][3], a.raw[1][3], a.raw[2][3], a.raw[3][3]
    };
    return mat;
}

inline Vec4 Diagonal(Mat4 a) {
    return {a.raw[0][0], a.raw[1][1], a.raw[2][2], a.raw[3][3]};
}

Mat4 Inverse(Mat4 a);

////////////////////////////////////////////////////////////////////////////////
// Quaternion functions

inline Quat QuatIdentity() {
    Quat quat = {0, 0, 0, 1};
    return quat;
}

inline Quat operator+(Quat a, Quat b) {
    return {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
}

inline Quat operator-(Quat a, Quat b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
}

inline Quat operator*(Quat a, Quat b) {
    F32 x = a.x*b.w + a.w*b.x + a.y*b.w - a.z*b.y;
    F32 y = a.y*b.w + a.w*b.y + a.z*b.x - a.x*b.z;
    F32 z = a.z*b.w + a.w*b.z + a.x*b.y - a.y*b.x;
    F32 w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
    return {x, y, z, w};
}

inline Quat operator*(Quat a, F32 b) {
    return {a.x*b, a.y*b, a.z*b, a.w*b};
}

inline Quat operator*(F32 a, Quat b) {
    return {a*b.x, a*b.y, a*b.z, a*b.w};
}

inline Quat operator/(Quat a, F32 b) {
    F32 inv = 1.0f / b;
    return {a.x*inv, a.y*inv, a.z*inv, a.w*inv};
}

inline Quat operator/(F32 a, Quat b) {
    return {a/b.x, a/b.y, a/b.z, a/b.w};
}

inline F32 Dot(Quat a, Quat b) {
     return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

inline F32 LengthSquared(Quat a) {
    return Dot(a, a);
}

inline F32 Length(Quat a) {
    return Sqrt(LengthSquared(a));
}

inline Quat Normalize(Quat a) {
    return a * (1.0f / Length(a));
}

inline Quat Conjugate(Quat a) {
    return {-a.x, -a.y, -a.z, a.w};
}

inline Quat Inverse(Quat a) {
    return Conjugate(a) / Dot(a, a);
}

inline Quat Lerp(Quat a, Quat b, F32 t) {
    return (1.0f-t)*a + t*b;
}

////////////////////////////////////////////////////////////////////////////////
// Box 3D functions

inline Box3 Union(Box3 a, Vec3 b) {
    Box3 box = {};
    box.min = Min(a.min, b);
    box.max = Max(a.max, b);
    return box;
}

inline Box3 Union(Box3 a, Box3 b) {
    Box3 box = {};
    box.min = Min(a.min, b.min);
    box.max = Max(a.max, b.max);
    return box;
}

inline Box3 Intersect(Box3 a, Box3 b) {
    Box3 box = {};
    box.min = Max(a.min, b.min);
    box.max = Min(a.max, b.max);
    return box;
}

inline bool Overlaps(Box3 a, Box3 b) {
    bool x = (a.max.x >= b.min.x) && (a.min.x <= b.max.x);
    bool y = (a.max.y >= b.min.y) && (a.min.y <= b.max.y);
    bool z = (a.max.z >= b.min.z) && (a.min.z <= b.max.z);
    return x && y && z;
}

inline bool Inside(Box3 a, Vec3 b) {
    return b.x >= a.min.x && b.x <= a.max.x && b.y >= a.min.y && b.y <= a.max.y && b.z >= a.min.z && b.z <= a.max.z;
}

inline bool InsideExclusive(Box3 a, Vec3 b) {
     return b.x >= a.min.x && b.x < a.max.x && b.y >= a.min.y && b.y < a.max.y && b.z >= a.min.z && b.z < a.max.z;
}

////////////////////////////////////////////////////////////////////////////////
// Box 2D functions

inline Box2 Union(Box2 a, Vec2 b) {
    Box2 box = {};
    box.min = Min(a.min, b);
    box.max = Max(a.max, b);
    return box;
}

inline Box2 Union(Box2 a, Box2 b) {
    Box2 box = {};
    box.min = Min(a.min, b.min);
    box.max = Max(a.max, b.max);
    return box;
}

inline Box2 Intersect(Box2 a, Box2 b) {
    Box2 box = {};
    box.min = Max(a.min, b.min);
    box.max = Min(a.max, b.max);
    return box;
}

inline bool Overlaps(Box2 a, Box2 b) {
    bool x = (a.max.x >= b.min.x) && (a.min.x <= b.max.x);
    bool y = (a.max.y >= b.min.y) && (a.min.y <= b.max.y);
    return x && y;
}

inline bool Inside(Box2 a, Vec2 b) {
    return b.x >= a.min.x && b.x <= a.max.x && b.y >= a.min.y && b.y <= a.max.y;
}

inline bool InsideExclusive(Box2 a, Vec2 b) {
     return b.x >= a.min.x && b.x < a.max.x && b.y >= a.min.y && b.y < a.max.y;
}

#endif // TC_MATHS_HEADER_GUARD
