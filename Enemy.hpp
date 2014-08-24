/* 
 * File:   Enemy.hpp
 * Author: iMer
 *
 * Created on 24. August 2014, 09:08
 */

#ifndef ENEMY_HPP
#define	ENEMY_HPP
#include "SpriteNode.hpp"

class Enemy : public engine::SpriteNode {
protected:
    bool m_killed;
    SpriteNode* m_explosion;
public:
    Enemy(engine::Scene* world);
    virtual ~Enemy();
    virtual uint8_t GetType() const;
    void Kill();
    virtual void OnUpdate(sf::Time interval);

    virtual bool initialize(Json::Value& root);

private:

};

#endif	/* ENEMY_HPP */

