/* 
 * File:   Upgrade.cpp
 * Author: iMer
 * 
 * Created on 24. August 2014, 21:16
 */

#include "Upgrade.hpp"
#include "ExtraNodeTypes.hpp"
using namespace engine;
Upgrade::Upgrade(Scene* scene) : SpriteNode(scene) {
}

Upgrade::~Upgrade() {
}

uint8_t Upgrade::GetType() const{
    return NT_UPGRADE;
}
bool Upgrade::initialize(Json::Value& root){
    if (!SpriteNode::initialize(root)){
        return false;
    }
    std::string upgradetype = root.get("upgradeType", "bubble").asString();
    if (upgradetype == "bubble"){
        m_upgradeType = UPGRADE_BUBBLE;
    }
    return true;
}

void Upgrade::SetUpgradeType(uint8_t upgradeType) {
    m_upgradeType = upgradeType;
}

uint8_t Upgrade::GetUpgradeType() const {
    return m_upgradeType;
}