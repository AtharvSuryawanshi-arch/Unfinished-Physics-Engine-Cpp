#pragma once
#include "object.hpp"

class physics{
public:
    const float frequency;
    const float delta;

    std::vector<object*> object_collection;
    
    physics( float frequency, std::vector<object*> &object_collection);

};

physics::physics( float frequency, std::vector<object*> &object_collection )
: object_collection(object_collection), frequency( frequency ), delta( 1 / frequency )
{
    debug(printf("Physics Engine Initiated\n"));
}
