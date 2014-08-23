/* 
 * File:   World.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 09:25
 */

#ifndef WORLD_HPP
#define	WORLD_HPP
#include "Scene.hpp"

class LD30Game;

class World: public engine::Scene {
public:
    World(LD30Game* game);
    virtual ~World();

};

#endif	/* WORLD_HPP */

