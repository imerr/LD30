/* 
 * File:   Player.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 11:04
 */

#include "Player.hpp"
#include "SFML/Window.hpp"
#include <cmath>
#include "Scene.hpp"
#include "Game.hpp"
#include "util/misc.hpp"
#include <iostream>
#include "ExtraNodeTypes.hpp"
#include "Factory.hpp"
#include "Projectile.hpp"
#include "util/math.hpp"
#include <cmath>
#include "World.hpp"
#include "LD30Game.hpp"
using namespace engine;

PlayerContactListener::PlayerContactListener(Player* p, b2Fixture* fixture) : m_contactCount(0), m_fixture(fixture), m_player(p) {

}

void PlayerContactListener::handle(b2Contact* contact, bool begin) {
    if (begin) {
        if (contact->GetFixtureA() == m_fixture || contact->GetFixtureB() == m_fixture) {
            m_contactCount++;
        }
        void* udA = contact->GetFixtureA()->GetBody()->GetUserData();
        void* udB = contact->GetFixtureB()->GetBody()->GetUserData();
        Node* n = nullptr;
        if (udA == m_player && udB) {
            n = static_cast<Node*> (udB);
        } else if (udB == m_player && udA) {
            n = static_cast<Node*> (udA);
        }
        if (n) {
            if (n->GetType() == NT_ENEMY) {
                m_player->Kill();
            }else if (n->GetType() == NT_UPGRADE) {
                m_player->EnableBubble();
                n->Delete();
            }else if (n->GetIndentifier() == "portal"){
               dynamic_cast<LD30Game*>(m_player->GetScene()->GetGame())->NextWorld();
            }
        }
    } else {
        if (contact->GetFixtureA() == m_fixture || contact->GetFixtureB() == m_fixture) {
            m_contactCount--;
        }
    }
}

size_t PlayerContactListener::GetContactCount() const {
    return m_contactCount;
}

void PlayerContactListener::SetFixture(b2Fixture* fixture) {
    m_fixture = fixture;
}

Player::Player(engine::Scene* scene) : SpriteNode(scene), m_maxVelocity(8, 1), m_velocityIncrease(3, 5), m_contactListener(this, nullptr), m_jumpCooldown(0), m_killed(false), m_respawnTimer(3), m_explosion(nullptr), m_shootTimer(1),
m_bubble(false) {
    m_scene->OnContact.AddHandler(&m_contactListener);
}

Player::~Player() {
    m_scene->OnContact.RemoveHandler(&m_contactListener);
    if (m_scene->GetWorld()) {
        m_scene->GetWorld()->SetContactListener(nullptr);
    }
}

void Player::OnUpdate(sf::Time interval) {
    if (m_killed) {
        if (m_respawnTimer > 0) {
            m_respawnTimer -= interval.asSeconds();
        } else {
            SetPosition(m_spawnPosition.x, m_spawnPosition.y);
            for (auto it = m_children.begin(); it != m_children.end(); it++) {
                if (*it == m_explosion) continue;
                (*it)->SetActive(true);
            }
            m_killed = false;
            m_respawnTimer = 3;
        }
        return;
    }
    auto window = m_scene->GetGame()->GetWindow();
    sf::View v = window->getView();
    v.setCenter(util::minmax(v.getSize().x / 2, m_body->GetPosition().x * m_scene->GetPixelMeterRatio(), m_scene->GetSize().x - v.getSize().x / 2), (util::minmax(v.getSize().y / 2, m_body->GetPosition().y * m_scene->GetPixelMeterRatio(), m_scene->GetSize().y - v.getSize().y / 2)));
    window->setView(v);
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_body->GetLinearVelocity().x < m_maxVelocity.x) {
        m_body->ApplyLinearImpulse(b2Vec2(m_velocityIncrease.x * interval.asSeconds(), 0), m_body->GetWorldCenter(), true);
        if (m_flipped) {
            m_flipped = false;
            UpdateTexCoords();
        }
    }
    if (m_shootTimer < 0) {
        if (m_bubble && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_shootTimer < 0) {
            Projectile* p = Factory::create<Projectile>("assets/config/projectile_bubble.json", m_scene);
            auto mpos = m_scene->GetGame()->GetMousePosition();
            float angle = atan2(mpos.x - GetPosition().x, mpos.y - (GetPosition().y - m_size.y / 3));
            if (angle < 0) {
                p->SetFlipped(true);
            }
            p->GetBody()->SetTransform(b2Vec2((GetPosition().x + (angle < 0 ? -m_size.x : +m_size.x)*.8) / m_scene->GetPixelMeterRatio(), (GetPosition().y - m_size.y / 3) / m_scene->GetPixelMeterRatio()), angle > 0 ? -(fabs(angle) - util::fPI / 2) : (fabs(angle) - util::fPI / 2));
            p->GetBody()->SetLinearVelocity(b2Vec2(p->GetBody()->GetLinearVelocity().x * sinf(angle), p->GetBody()->GetLinearVelocity().x * cosf(angle)));
            m_scene->AddNode(p);
            m_shootTimer = 1;
        }
    } else {
        m_shootTimer -= interval.asSeconds();
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_body->GetLinearVelocity().x > -m_maxVelocity.x) {
        m_body->ApplyLinearImpulse(b2Vec2(-m_velocityIncrease.x * interval.asSeconds(), 0), m_body->GetWorldCenter(), true);
        if (!m_flipped) {
            m_flipped = true;
            UpdateTexCoords();
        }
    }
    if (m_jumpCooldown > 0) {
        m_jumpCooldown -= interval.asSeconds();
    } else if (m_contactListener.GetContactCount() && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        m_body->ApplyLinearImpulse(b2Vec2(0, -m_velocityIncrease.y), m_body->GetWorldCenter(), true);
        m_jumpCooldown = 1;
    }

    if (!m_contactListener.GetContactCount()) {
        if (m_currentAnimation != "jumping") {
            PlayAnimation("jumping");
        }
    } else if (abs(m_body->GetLinearVelocity().x) > 0.02) {
        if (m_currentAnimation != "running") {
            PlayAnimation("running");
        }
    } else {
        if (m_currentAnimation != "default") {
            PlayAnimation("default");
        }
    }
}

bool Player::initialize(Json::Value& root) {
    if (!SpriteNode::initialize(root)) {
        return false;
    }
    b2Fixture* f = m_body->GetFixtureList();
    for (size_t i = 0; i < 2; i++) {
        if (f->GetShape()->GetType() == b2Shape::e_circle) {
            m_fixtureCircle = f;
            m_contactListener.SetFixture(f);
        } else {
            m_fixtureRect = f;
        }
        f = f->GetNext();
    }
    m_spawnPosition = GetPosition();
    m_explosion = Factory::create<SpriteNode>("assets/config/explosion.json", m_scene);
    AddNode(m_explosion);
    m_explosion->SetPosition(m_explosion->GetSize().x / 6, 0);
    return true;
}

void Player::Kill() {
    if (!m_killed) {
        m_killed = true;
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            if (*it == m_explosion) continue;
            (*it)->SetActive(false);
        }
        m_explosion->PlayAnimation("explode");
        PlayAnimation("death");
    }

}

uint8_t Player::GetType() const {
    return NT_PLAYER;
}

void Player::EnableBubble() {
    m_bubble = true;
}