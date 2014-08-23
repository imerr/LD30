/* 
 * File:   PauseMenu.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 18:09
 */

#ifndef PAUSEMENU_HPP
#define	PAUSEMENU_HPP
#include "Node.hpp"
class World;
class PauseMenu: public engine::Node {
protected:
    
public:
    PauseMenu(World* scene);
    virtual ~PauseMenu();
};

#endif	/* PAUSEMENU_HPP */

