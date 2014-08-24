/* 
 * File:   Projectile.hpp
 * Author: iMer
 *
 * Created on 24. August 2014, 13:36
 */

#ifndef PROJECTILE_HPP
#define	PROJECTILE_HPP
#include "SpriteNode.hpp"
#include "util/Event.hpp"
class Projectile;
class ProjectileContactListener : public engine::util::EventHandler<b2Contact*, bool> {
protected:
    Projectile* m_projectile;
public:
    ProjectileContactListener(Projectile* p);
    virtual void handle(b2Contact* c, bool begin);
};

class Projectile : public engine::SpriteNode {
protected:  
    ProjectileContactListener m_contactListener;
    bool m_killed;
    bool m_autoDestroy;
    bool m_harmEnemies;
public:
    Projectile(engine::Scene*);
    virtual ~Projectile();

    virtual void OnUpdate(sf::Time interval);
    void Kill();

    virtual bool initialize(Json::Value& root);
    void SetHarmEnemies(bool harmEnemies);
    bool IsHarmEnemies() const;


};

#endif	/* PROJECTILE_HPP */

