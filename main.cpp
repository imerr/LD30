/* 
 * File:   main.cpp
 * Author: iMer
 *
 * Created on 23. August 2014, 03:03
 */

#include "LD30Game.hpp"
#include "Factory.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Upgrade.hpp"

int main(int argc, char** argv) {
    engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
    engine::Factory::RegisterType("enemy", engine::Factory::CreateChildNode<Enemy>);
    engine::Factory::RegisterType("projectile", engine::Factory::CreateChildNode<Projectile>);
    engine::Factory::RegisterType("upgrade", engine::Factory::CreateChildNode<Upgrade>);
    LD30Game game;
    game.run();
    return 0;
}

