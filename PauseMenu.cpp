/* 
 * File:   PauseMenu.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 18:09
 */

#include "PauseMenu.hpp"
#include "Button.hpp"
#include "Factory.hpp"
#include "World.hpp"
using namespace engine;
PauseMenu::PauseMenu(World* scene): Node(scene) {
    Button* b = Factory::create<Button>("assets/config/pausemenu_resume.json", scene);
    if (b){
        b->OnClick = [scene](Button*, sf::Vector2f){
            scene->TogglePause();
        };
        AddNode(b);
    }
}

PauseMenu::~PauseMenu() {
}

