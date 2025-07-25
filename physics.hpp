#pragma once
#include "object.hpp"

class physics
{
    vec2 gravity;
    std::vector<object*> object_all;
    
    const float frequency; //Hz
    const float delta; //in s (float)
    // please put delta = 1/frequency

    void update_velocity();
    void update_position(); //includes rotation too
    
    void set_object_order();
};

void physics::update_velocity()
{
    for(int i = 0; i < object_all.size(); ++i)
    {
        object_all.at(i)->velocity_com = object_all.at(i)->velocity_com + gravity*delta;
    }
}

void physics::update_position()
{
    for( int i = 0; i < object_all.size(); ++i )
    {
        for( int j = 0; j < object_all.at(i)->vertices.size(); ++j)
        {
            object_all.at(i)->vertices.at(j).position += object_all.at(i)->velocity_of_vertex(j)*delta;
        }
    }
}

void physics::set_object_order()
{

}
