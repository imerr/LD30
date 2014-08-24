/* 
 * File:   Player.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 11:04
 */

#ifndef PLAYER_HPP
#define	PLAYER_HPP
#include "SpriteNode.hpp"
#include "util/Event.hpp"
class Player;
class PlayerContactListener : public engine::util::EventHandler<b2Contact*, bool> {
protected:
    b2Fixture* m_fixture;
    size_t m_contactCount;
    Player* m_player;
public:

    PlayerContactListener(Player* player, b2Fixture* fixture);
    virtual void handle(b2Contact* contact, bool begin);
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
    sf::Vector2f m_spawnPosition;
    bool m_killed;
    SpriteNode* m_explosion;
    float m_shootTimer;
    float m_respawnTimer;
    bool m_bubble;
public:
    Player(engine::Scene* scene);
    virtual ~Player();
    virtual void OnUpdate(sf::Time interval);
    virtual bool initialize(Json::Value& root);
    void Kill();
    virtual uint8_t GetType() const;
    void EnableBubble();
};

#endif	/* PLAYER_HPP */

