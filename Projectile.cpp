/* 
 * File:   Projectile.cpp
 * Author: iMer
 * 
 * Created on 24. August 2014, 13:36
 */

#include "Projectile.hpp"
#include "ExtraNodeTypes.hpp"
#include "Scene.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <iostream>
using namespace engine;

ProjectileContactListener::ProjectileContactListener(Projectile* p) : m_projectile(p) {

}

void ProjectileContactListener::handle(b2Contact* c, bool begin) {
    if (begin) {
        void* udA = c->GetFixtureA()->GetBody()->GetUserData();
        void* udB = c->GetFixtureB()->GetBody()->GetUserData();
        if (udA == m_projectile && udB) {
            m_projectile->Kill();
            if (m_projectile->IsHarmEnemies() && static_cast<Node*> (udB)->GetType() == NT_ENEMY) {
                ((Enemy*) udB)->Kill();
            } else if (static_cast<Node*> (udB)->GetType() == NT_PLAYER) {
                ((Player*) udB)->Kill();
            }
        } else if (udB == m_projectile && udA) {
            m_projectile->Kill();
            if (m_projectile->IsHarmEnemies() && static_cast<Node*> (udA)->GetType() == NT_ENEMY) {
                ((Enemy*) udA)->Kill();
            } else if (static_cast<Node*> (udA)->GetType() == NT_PLAYER) {
                ((Player*) udA)->Kill();
            }
        }
    }
}

Projectile::Projectile(Scene* scene) : SpriteNode(scene), m_killed(false), m_contactListener(this), m_autoDestroy(true), m_harmEnemies(true) {
    m_scene->OnContact.AddHandler(&m_contactListener);
}

Projectile::~Projectile() {
    m_scene->OnContact.RemoveHandler(&m_contactListener);
}

void Projectile::OnUpdate(sf::Time interval) {
    if (m_killed){
        m_body->SetActive(false);
    }
    if ((m_killed || GetPosition().x > m_scene->GetSize().x || GetPosition().y > m_scene->GetSize().y || GetPosition().x < 0 || GetPosition().y < 0) && (m_animations.find("explode") == m_animations.end() || m_animations["explode"]->IsOver())) {
        if (m_autoDestroy) {
            Delete();
        }else{
            SetActive(false);
            m_killed=false;
        }

    }
}

void Projectile::Kill() {
    if (!m_killed) {
        m_killed = true;
        if (m_animations.find("explode") != m_animations.end()) {
            PlayAnimation("explode");
        }
    }
}

bool Projectile::initialize(Json::Value& root) {
    if (!SpriteNode::initialize(root)) {
        return false;
    }
    // For use with particle systems
    m_autoDestroy = root.get("autodestroy", true).asBool();
    // bulb cant murder itself
    m_harmEnemies = root.get("harmenemies", true).asBool();
}

void Projectile::SetHarmEnemies(bool harmEnemies) {
    m_harmEnemies = harmEnemies;
}

bool Projectile::IsHarmEnemies() const {
    return m_harmEnemies;
}