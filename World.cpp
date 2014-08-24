/* 
 * File:   World.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 09:25
 */

#include "World.hpp"
#include "LD30Game.hpp"
#include "Factory.hpp"
using namespace engine;

EscHandler::EscHandler(World* world) : m_world(world) {

}

void EscHandler::handle(const sf::Event::KeyEvent& key) {
    if (m_world->GetGame()->GetScene() != m_world) {
        return;
    }
    if (key.code == sf::Keyboard::Escape) {
        m_world->TogglePause();
    }
}

void ChainMouse::handle(const sf::Event::MouseButtonEvent& e) {
    auto m = m_world->GetGame()->GetMousePosition();
    if (e.button == sf::Mouse::Left && m_current) {
        m_current->SetPosition((int)m.x, (int)m.y);
    }else if (e.button == sf::Mouse::Right) {
        if (m_current) {
            m_root["children"][m_root["children"].size()]= Json::objectValue;;
            m_root["children"][m_root["children"].size() - 1]["childData"] = m_config;
            m_root["children"][m_root["children"].size() - 1]["position"][0u] = m_current->GetPosition().x;
            m_root["children"][m_root["children"].size() - 1]["position"][1u] = m_current->GetPosition().y;
        }
        m_current = Factory::CreateChildFromFile(m_config, m_world);
        if (m_current) {
            m_current->SetPosition((int)m.x, (int)m.y);
            m_world->AddNode(m_current);
        }else{
        }
    }else if (e.button == sf::Mouse::Middle){
        m_current->Delete();
        m_current = nullptr;
    }
}

World::World(LD30Game* game) : engine::Scene::Scene(game), m_paused(false), m_escHandler(this), m_cm(this) {
    m_game->OnKeyDown.AddHandler(&m_escHandler);
    //m_game->OnMouseClick.AddHandler(&m_cm);
    m_pauseMenu = Factory::create<PauseMenu>("assets/config/pausemenu.json", this);
    m_portal = Factory::create<SpriteNode>("assets/config/world1/portal.json", this);
    if (m_portal){
        AddNode(m_portal);
    }
}

World::~World() {
    m_game->OnKeyDown.RemoveHandler(&m_escHandler);
    m_game->OnMouseClick.RemoveHandler(&m_cm);
    delete m_pauseMenu;
}

void World::update(sf::Time interval) {
    if (!m_paused && !m_scene->GetGame()->IsFocus()) {
        m_paused = true;
    }
    if (!m_paused) {
        Scene::update(interval);
    } else {
        m_pauseMenu->update(interval);
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
    Scene::draw(target, states, m_paused ? 0 : delta); // Prevent animations from playing
    if (m_paused) {
        // Keep UI in the screen
        auto view = m_scene->GetGame()->GetWindow()->getView();
        m_pauseMenu->setPosition(view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2));
        m_pauseMenu->draw(target, states, delta);
    }
}

Node* World::GetPortal() const {
    return m_portal;
}

void World::TogglePause() {
    m_paused = !m_paused;
}