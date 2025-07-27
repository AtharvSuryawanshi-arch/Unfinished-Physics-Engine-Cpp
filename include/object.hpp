#pragma once
#include "vec2.hpp"
#include <stdio.h>
#include <vector>

uint OBJECT_ID = 0;

struct object_compare
{
    bool   comparison;
};

class object
{
public:
    std::vector<vec2>   vertices;

    vec2                position_com;
    vec2                velocity_com;
    
    float               angular_velocity;
    float               e; //coeficient of restitution
    float               density;
    float               area; // TO-DO Later

    inline line edge( size_t n );
    
    object( std::vector<vec2> &vert );

    object_compare is_colliding_with( vec2 vert );
    object_compare is_colliding_with_object( object obj );

    vec2 vertex_velocity( size_t n );
private:
    inline vec2 edge_normal( size_t n );
};

inline object_compare object::is_colliding_with(vec2 vec)
{

    float edge_distance = 0.0f;
    size_t const_edge = 0;
    object_compare temp;
    uint gauss = 0;
    for( uint i = 0; i < vertices.size(); ++i )
    {
        line l = edge( i );
        
        if( l.check_internal_y(vec) )
        {
            if(l.equivalent_x(vec) > vec.x)
            {
                gauss++;
            }
        }
    }
    
    if( gauss % 2 == 0 ){
        return object_compare{false};
    }
    temp.comparison = true;
    debug(printf("vertex compare : %i \n", true ));
    return temp;
}

inline object_compare object::is_colliding_with_object(object obj)
{
    for( uint i = 0; i < obj.vertices.size(); ++i)
    {
        if( is_colliding_with( obj.vertices.at(i)).comparison )
        {
            return {true};
        }
    }
    return {false};
}

inline vec2 object::vertex_velocity(size_t n)
{
    return velocity_com + (vertices.at(n) - position_com).rotated(M_PI/2).normalized()*angular_velocity;
}

object::object(std::vector<vec2> &vert) : vertices(vert)
{
    vec2 position_com = vec2{0.0f,0.0f};
    debug(printf("Object Initiated : Object ID : %i\n", OBJECT_ID++));
    for( uint i = 0; i < vertices.size(); ++i){
        position_com += vertices.at( i );
    }
    position_com.x /= vertices.size();
    position_com.y /= vertices.size();
}

inline vec2 object::edge_normal(size_t n)
{
    line t = edge( n );
    return (t.point2 - t.point1).rotated( M_PI / 2 ).normalized();
}

inline line object::edge( size_t n )
{
    if( n >= vertices.size()-1)
        return line{ vertices.at(n), vertices.at(0)};
    else
       return line{ vertices.at(n), vertices.at(n+1)}; 
} 
