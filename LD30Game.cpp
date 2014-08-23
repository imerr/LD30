/* 
 * File:   LD30Game.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 04:37
 */

#include "LD30Game.hpp"
#include "Factory.hpp"
LD30Game::LD30Game() {
    m_sceneTitleScreen = engine::Factory::create<TitleScreen>("assets/config/titlescreen.json", this);
    m_sceneWorld = engine::Factory::create<World>("assets/config/world_1.json", this);
    m_scene = m_sceneTitleScreen;
}

LD30Game::~LD30Game() {
    delete m_sceneTitleScreen;
    delete m_sceneWorld;
}

void LD30Game::Start(){
    m_scene = m_sceneWorld;
}