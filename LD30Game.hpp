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

class LD30Game : public engine::Game {
protected:
    TitleScreen* m_sceneTitleScreen;
public:
    LD30Game();
    virtual ~LD30Game();

};

#endif	/* LD30GAME_HPP */

