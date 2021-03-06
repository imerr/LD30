/* 
 * File:   LD30Game.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 04:37
 */

#ifndef LD30GAME_HPP
#define	LD30GAME_HPP
#include "Game.hpp"
#include "TitleScreen.hpp"
#include "World.hpp"
class LD30Game : public engine::Game {
protected:
    TitleScreen* m_sceneTitleScreen;
    World* m_sceneWorld1;
    World* m_sceneWorld2;
    World* m_sceneWorld3;
    World* m_sceneWorld4;
    bool m_next;
    bool m_nextDel;
public:
    LD30Game();
    virtual ~LD30Game();
    void Start();
    void NextWorld();
    virtual void OnUpdate();
};

#endif	/* LD30GAME_HPP */

