/* 
 * File:   TitleScreen.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 04:38
 */

#include "TitleScreen.hpp"
#include "Factory.hpp"
#include "Button.hpp"
using namespace engine;

TitleScreen::TitleScreen(engine::Game* game) : Scene::Scene(game) {
    std::cout << "A" << std::endl;
    Button* b = engine::Factory::create<Button>("assets/config/ui_titlescreen.json", this);
    if (b){
        m_ui.AddNode(b);
        std::cout << "S(" << b->GetGlobalPosition().x << ", " << b->GetGlobalPosition().y << std::endl;
    }
}

TitleScreen::~TitleScreen() {
}
