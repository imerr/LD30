/* 
 * File:   LD30Game.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 04:37
 */

#include "LD30Game.hpp"
#include "Factory.hpp"

LD30Game::LD30Game() : m_next(false), m_nextDel(false) {
    m_sceneTitleScreen = engine::Factory::create<TitleScreen>("assets/config/titlescreen.json", this);
    m_sceneWorld1 = engine::Factory::create<World>("assets/config/world_1.json", this);
    m_sceneWorld2 = engine::Factory::create<World>("assets/config/world_2.json", this);
    m_sceneWorld3 = engine::Factory::create<World>("assets/config/world_3.json", this);
    m_sceneWorld4 = engine::Factory::create<World>("assets/config/world_4.json", this);
    m_scene = m_sceneTitleScreen;
}

LD30Game::~LD30Game() {
    delete m_sceneTitleScreen;
    delete m_sceneWorld1;
    delete m_sceneWorld2;
    delete m_sceneWorld3;
    delete m_sceneWorld4;
}

void LD30Game::Start() {
    m_scene = m_sceneWorld3;
}

void LD30Game::OnUpdate() {
    if (m_next) {
        if (m_scene == m_sceneWorld1) {
            m_scene = m_sceneWorld2;
        } else if (m_scene == m_sceneWorld2) {
            m_scene = m_sceneWorld3;
        } else if (m_scene == m_sceneWorld3) {
            m_scene = m_sceneWorld4;
        }
        m_next = false;
    }
}

void LD30Game::NextWorld() {
    m_next = true;
}