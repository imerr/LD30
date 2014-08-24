/* 
 * File:   Upgrade.hpp
 * Author: iMer
 *
 * Created on 24. August 2014, 21:16
 */

#ifndef UPGRADE_HPP
#define	UPGRADE_HPP
#include "SpriteNode.hpp"
class Upgrade : public engine::SpriteNode {
protected:

    uint8_t m_upgradeType;
public:

    enum Types {
        UPGRADE_BUBBLE
    };
    
    Upgrade(engine::Scene*);
    virtual ~Upgrade();

    virtual uint8_t GetType() const;
    virtual bool initialize(Json::Value& root);
    void SetUpgradeType(uint8_t upgradeType);
    uint8_t GetUpgradeType() const;


private:

};

#endif	/* UPGRADE_HPP */

