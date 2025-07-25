#pragma once
#include <vector>
#include <stdio.h>
#include "vec2.hpp"

int counter = 1;

class vertex
{
public:
    vec2 position;
    //add properties to the vertex if needed
};

class object //working as intended
{
public:

    std::vector<vertex>     vertices;
    std::vector<object*>    object_storage;
    vec2                    velocity_com;
    vec2                    position_com;
    float                   angular_velocity; //anticlockwise

    inline line edge(size_t n);

    inline bool check_edge( vec2, size_t );
    inline bool is_colliding_with( vec2 vec );
    inline bool is_colliding_with_object( object* obj );

    inline vec2 velocity_of_vertex( size_t n );
};

inline line object::edge(size_t n)
{
    if( n >= vertices.size()-1)
        return line{ vertices.at(n).position, vertices.at(0).position};
    else
       return line{ vertices.at(n).position, vertices.at(n+1).position}; 
}

inline bool object::check_edge(vec2 vec, size_t n)
{
    line l = edge( n );
    
    return l.check_internal_y(vec);
}

inline bool object::is_colliding_with(vec2 vec)
{
    uint gauss = 0;

    for( int i = 0; i < vertices.size(); ++i)
    {
        line l = edge( i );
        printf("check edge %i : %i \n",i, check_edge(vec,i));
        if( check_edge(vec, i))
        {
            if( l.equivalent_x(vec) > vec.x)
            {
                gauss++;
            }
        }
        l.print();
    }

    //optimization : use : 
    //return (gauss%2);
    printf("gause for vertex %i : %i\n" , counter++, gauss);
    if( gauss %2 == 1){
        return true;
    }else{
        return false;
    }
}

inline bool object::is_colliding_with_object(object *obj)
{
    size_t n = obj->vertices.size();

    for( size_t i = 0; i < n ; ++i )
    {
        if( is_colliding_with(obj->vertices.at(i).position))
            goto label_exit;
    }
    return false;

    label_exit:
    return true;
}

inline vec2 object::velocity_of_vertex(size_t n)
{
    //M_PI_2f32 = PI/2
    return (velocity_com + (vertices.at(n).position - position_com).rotated(M_PI_2f32)*angular_velocity);
}
