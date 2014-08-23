/* 
 * File:   TitleScreen.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 04:38
 */

#ifndef TITLESCREEN_HPP
#define	TITLESCREEN_HPP
#include "Scene.hpp"
#include "Game.hpp"
class TitleScreen: public engine::Scene {
public:
    TitleScreen(engine::Game* game);
    virtual ~TitleScreen();
private:

};

#endif	/* TITLESCREEN_HPP */

