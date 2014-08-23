/* 
 * File:   TitleScreen.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 04:38
 */

#include "TitleScreen.hpp"
#include "Factory.hpp"
#include "Button.hpp"
#include "LD30Game.hpp"
using namespace engine;

TitleScreen::TitleScreen(LD30Game* game) : Scene::Scene(game) {
    Button* b = Factory::create<Button>("assets/config/titlescreen_start.json", this);
    if (b){
        m_ui.AddNode(b);
        b->OnClick = [game](Button* button, sf::Vector2f){
            game->Start();
        };
    }
    SpriteNode* logo = Factory::create<SpriteNode>("assets/config/logo.json", this);
    if (logo){
        m_ui.AddNode(logo);
    }
}

TitleScreen::~TitleScreen() {
}
