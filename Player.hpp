/* 
 * File:   Player.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 11:04
 */

#ifndef PLAYER_HPP
#define	PLAYER_HPP
#include "SpriteNode.hpp"

class PlayerContactListener : public b2ContactListener {
protected:
    b2Fixture* m_fixture;
    size_t m_contactCount;
public:

    PlayerContactListener(b2Fixture* fixture);
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    size_t GetContactCount() const;
    void SetFixture(b2Fixture* fixture);
};

class Player : public engine::SpriteNode {
protected:
    sf::Vector2f m_maxVelocity;
    sf::Vector2f m_velocityIncrease;
    b2Fixture* m_fixtureRect;
    b2Fixture* m_fixtureCircle;
    PlayerContactListener m_contactListener;
    float m_jumpCooldown;
public:
    Player(engine::Scene* scene);
    virtual ~Player();
    virtual void OnUpdate(sf::Time interval);
    virtual bool initialize(Json::Value& root);

};

#endif	/* PLAYER_HPP */

