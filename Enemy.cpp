/* 
 * File:   Enemy.cpp
 * Author: iMer
 * 
 * Created on 24. August 2014, 09:08
 */

#include "Enemy.hpp"
#include "ExtraNodeTypes.hpp"
#include "Scene.hpp"
#include "Factory.hpp"
#include <iostream>
using namespace engine;

Enemy::Enemy(Scene* world) : SpriteNode(world), m_killed(false) {

}

Enemy::~Enemy() {
}

uint8_t Enemy::GetType() const {
    return NT_ENEMY;
};

void Enemy::OnUpdate(sf::Time interval) {
    if (m_killed) {
        if (m_body) {
            m_body->SetActive(false);
        }
        if (m_explosion && m_explosion->GetAnimation() && m_explosion->GetAnimation()->IsOver()) {
            Delete();
            return;
        }
    }
}

void Enemy::Kill() {
    if (!m_killed) {
        m_killed = true;
        m_render = false;
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            if (*it == m_explosion) continue;
            (*it)->SetActive(false);
        }
        if (m_explosion) {
            m_explosion->PlayAnimation("explode");
        }
    }
}

bool Enemy::initialize(Json::Value& root) {
    if (!SpriteNode::initialize(root)) {
        return false;
    }
    m_explosion = Factory::create<SpriteNode>("assets/config/explosion.json", m_scene);
    if (m_explosion) {
        AddNode(m_explosion);
        m_explosion->setPosition((m_explosion->GetSize().x / 6)*(m_size.x + 50) / m_explosion->GetSize().x, 0);
        m_explosion->setScale((m_size.x + 50) / m_explosion->GetSize().x, (m_size.x + 50) / m_explosion->GetSize().x);
    }
}
