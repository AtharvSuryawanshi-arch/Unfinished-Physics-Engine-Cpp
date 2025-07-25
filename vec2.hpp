#pragma once
#include <math.h>

class vec2 //working as intended* 
{
public:
    float x;
    float y;

    vec2 operator+(vec2 vec);
    vec2 operator-(vec2 vec);
    vec2 operator*(float scalar);
    vec2 operator+=(vec2 vec);
    vec2 operator-=(vec2 vec);
    
    inline vec2 conjugate();
    inline vec2 rotated(float angle);
    inline vec2 rotated_about(float angle, vec2 vec);
    
    inline float argument();
    inline float slope();       
    inline float dot(vec2 vec); 
    inline float mod();         
    
    inline void print_vec();
    inline void rotate_this_origin(float angle);
    inline void rotate_this_about( float angle, vec2 vec);
};

class line //working as intended
{
public:
    vec2 point1;
    vec2 point2;
    
    float compare(vec2 vec);
    inline float compare(line line);
    inline float argument();
    inline float slope();
    inline bool within(vec2 vec);

    inline bool check_internal_y(vec2 vec);
    inline float equivalent_x(vec2 vec);

    inline void print();

};

typedef vec2 complex;

inline void line::print(){
    printf("Line data : (%f,%f), (%f,%f)\n",point1.x,point1.y,point2.x,point2.y);
}

inline float line::slope()
{
    return (point2-point1).slope();
}

vec2 vec2::operator+(vec2 vec)
{
    vec2 res = {x,y};
    res.x += vec.x;
    res.y += vec.y;
    return res;
}

vec2 vec2::operator-(vec2 vec)
{
    vec2 res = {x,y};
    res.x -= vec.x;
    res.y -= vec.y;
    return res;
}

inline vec2 vec2::operator*(float scalar)
{
    return vec2{x*scalar, y*scalar};
}

inline vec2 vec2::operator+=(vec2 vec)
{
    return (*this + vec);
}

inline vec2 vec2::operator-=(vec2 vec)
{
    return (*this - vec);
}

inline float vec2::dot(vec2 vec)
{
    return x*vec.x + y*vec.y;
}

inline float vec2::mod()
{
    return sqrt(x*x + y*y);
}

inline vec2 vec2::conjugate()
{
    return vec2{x, -y};
}

inline vec2 vec2::rotated(float angle)
{
    vec2 temp = *this;
    temp.rotate_this_origin( angle );
    return temp;
}

inline vec2 vec2::rotated_about(float angle, vec2 vec)
{
    vec2 temp = *this;
    temp.rotate_this_about( angle, vec );
    return temp;
}

inline void vec2::print_vec()
{
    printf("vector : %f %f\n", x, y);
}

inline void vec2::rotate_this_origin(float angle)
{
    x = x*cos(angle) - y*sin(angle);
    y = x*sin(angle) + y*cos(angle);
}

inline void vec2::rotate_this_about(float angle, vec2 vec)
{
    vec2 temp = vec2{x,y} - vec;
    temp.rotate_this_origin(angle);

    *this = *this + temp;
}

inline bool line::within(vec2 vec)
{
    bool x;
    float res = (vec-point1).dot(point2 - point1)*(vec-point2).dot(point2 - point1);
    if (res <= 0)
        x = true;
    else 
        x= false;
    return x;
}

inline bool line::check_internal_y(vec2 vec)
{
    float x = (point2.y - vec.y)*(point1.y - vec.y);
    if (x <= 0)
        return true;
    else
        return false;
}

inline float line::equivalent_x(vec2 vec)
{
    return (point1.x*(point2.y-vec.y) + point2.x*(vec.y-point1.y))/(point2.y-point1.y);
}

float line::compare(vec2 vec)
{
    return ((point2.x-point1.x)*vec.y - (point2.y - point1.y)*vec.x + point1.x*point2.y - point1.y*point2.x)/(point2-point1).mod();
}

inline float line::compare( line line)
{
    return compare(line.point1);
}

inline float line::argument()
{
    return atan(slope());
}

inline float vec2::argument()
{
    return atan2(y,x);
}

inline float vec2::slope()
{
    return y/x;
}
