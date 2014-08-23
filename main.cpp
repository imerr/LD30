/* 
 * File:   main.cpp
 * Author: iMer
 *
 * Created on 23. August 2014, 03:03
 */

#include "LD30Game.hpp"
#include "Factory.hpp"
#include "Player.hpp"

int main(int argc, char** argv) {
    engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
    LD30Game game;
    game.run();
    return 0;
}

