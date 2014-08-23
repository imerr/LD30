/* 
 * File:   World.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 09:25
 */

#ifndef WORLD_HPP
#define	WORLD_HPP
#include "Scene.hpp"
#include "util/Event.hpp"
#include "SFML/Window.hpp"
#include "PauseMenu.hpp"
#include <fstream>
#include <iostream>
class LD30Game;
class World;

class EscHandler : public engine::util::EventHandler<const sf::Event::KeyEvent&> {
private:
    World* m_world;
public:
    EscHandler(World* world);
    virtual void handle(const sf::Event::KeyEvent&);

};

class ChainMouse : public engine::util::EventHandler<const sf::Event::MouseButtonEvent&> {
private:
    World* m_world;
    engine::Node* m_current;
    Json::Value m_root;
    std::string m_config;
public:

    ChainMouse(World* world) {
        m_config = "assets/config/world1/mushroom_red.json";
        m_world = world;
        m_root["children"] = Json::arrayValue;
        m_current = nullptr;

    }

    virtual ~ChainMouse() {
        std::cout << "Writing" << std::endl;
        std::ofstream d;
        d.open("out.json");
        if (!d.good()) {
            std::cerr << "Could not open config file: " << strerror(errno) << std::endl;
        } else {
            Json::StyledWriter w;
            d << w.write(m_root) << std::endl;
        }
    }
    virtual void handle(const sf::Event::MouseButtonEvent&);

};

class World : public engine::Scene {
protected:
    bool m_paused;
    EscHandler m_escHandler;
    ChainMouse m_cm;
    PauseMenu* m_pauseMenu;
public:
    World(LD30Game* game);
    virtual ~World();
    virtual void update(sf::Time interval);
    void TogglePause();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states, float delta);


};

#endif	/* WORLD_HPP */

