#pragma once
#include "object.hpp"

struct twin_object{
    object* object1;
    object* object2;
};

class physics{
public:
    const float frequency;
    const float delta;
    std::vector<object*> object_collection;
    
    long int frame = 0;

    physics( float frequency, std::vector<object*> &object_collection);
    std::vector<twin_object> check_collisions();
     
    void collide_objects( twin_object obj );
};

physics::physics( float frequency, std::vector<object*> &object_collection )
: object_collection(object_collection), frequency( frequency ), delta( 1 / frequency )
{
    debug(printf("Physics Engine Initiated\n"));
}

std::vector<twin_object> physics::check_collisions()
{
    std::vector<twin_object> temp = {};
    size_t i_size = object_collection.size() - 1;
    size_t j_size = object_collection.size();
    for( size_t i = 0; i < i_size; ++i)
    {
        for( size_t j = i; j < j_size; ++j)
        {
            if( object_collection.at(i)->is_colliding_with_object(*object_collection.at(j)).comparison)
            {
                temp.push_back({object_collection.at(i),object_collection.at(j)});
            }
        }
    }
    return temp;
}

inline void physics::collide_objects(twin_object obj)
{
    float avg_e = (obj.object1->e + obj.object2->e)/2;

    float m1 = obj.object1->density * obj.object1->area;
    float m2 = obj.object2->density * obj.object2->area;

    vec2 pos_rel = (obj.object2->position_com - obj.object1->position_com).normalized();

    vec2 v_bar = (obj.object1->velocity_com*m1 + obj.object2->velocity_com*m2)/(m1 + m2);

    obj.object1->velocity_com += v_bar + ( v_bar - obj.object1->velocity_com)*avg_e - pos_rel*(obj.object1->velocity_com.dot(pos_rel));
    obj.object2->velocity_com += v_bar + ( v_bar - obj.object2->velocity_com)*avg_e - pos_rel*(obj.object2->velocity_com.dot(pos_rel));
}
