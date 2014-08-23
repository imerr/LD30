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
using namespace engine;

PlayerContactListener::PlayerContactListener(b2Fixture* fixture) : m_contactCount(0), m_fixture(fixture) {

}

void PlayerContactListener::BeginContact(b2Contact* contact) {
    if (contact->GetFixtureA() == m_fixture || contact->GetFixtureB() == m_fixture) {
        m_contactCount++;
    }
}

void PlayerContactListener::EndContact(b2Contact* contact) {
    if (contact->GetFixtureA() == m_fixture || contact->GetFixtureB() == m_fixture) {
        m_contactCount--;
    }
}

size_t PlayerContactListener::GetContactCount() const {
    return m_contactCount;
}

void PlayerContactListener::SetFixture(b2Fixture* fixture) {
    m_fixture = fixture;
}

Player::Player(Scene* scene) : SpriteNode(scene), m_maxVelocity(8, 1), m_velocityIncrease(3, 5), m_contactListener(nullptr), m_jumpCooldown(0) {
    m_scene->GetWorld()->SetContactListener(&m_contactListener);
}

Player::~Player() {
    if (m_scene->GetWorld()) {
        m_scene->GetWorld()->SetContactListener(nullptr);
    }
}

void Player::OnUpdate(sf::Time interval) {
    auto window = m_scene->GetGame()->GetWindow();
    sf::View v = window->getView();
    v.setCenter(util::minmax(v.getSize().x / 2, m_body->GetPosition().x * m_scene->GetPixelMeterRatio(), m_scene->GetSize().x - v.getSize().x / 2), util::minmax(v.getSize().y / 2, m_body->GetPosition().y * m_scene->GetPixelMeterRatio(), m_scene->GetSize().y - v.getSize().y / 2));
    window->setView(v);
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && m_body->GetLinearVelocity().x < m_maxVelocity.x) {
        m_body->ApplyLinearImpulse(b2Vec2(m_velocityIncrease.x * interval.asSeconds(), 0), m_body->GetWorldCenter(), true);
        if (m_flipped) {
            m_flipped = false;
            UpdateTexCoords();
        }
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && m_body->GetLinearVelocity().x > -m_maxVelocity.x) {
        m_body->ApplyLinearImpulse(b2Vec2(-m_velocityIncrease.x * interval.asSeconds(), 0), m_body->GetWorldCenter(), true);
        if (!m_flipped) {
            m_flipped = true;
            UpdateTexCoords();
        }
    }
    /*if (m_contactListener.GetContactCount()) {
        m_fixtureCircle->SetFriction(100);
        m_fixtureRect->SetFriction(100);
    } else {
        m_fixtureCircle->SetFriction(0);
        m_fixtureRect->SetFriction(0);
    }*/
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
    return true;
}