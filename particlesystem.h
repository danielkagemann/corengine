/*
 *  particlesystem.h
 *  corengine
 *
 *  Created by Daniel Kagemann on 15.09.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */

#ifndef particlesystem_h_
#define particlesystem_h_

#include "emitters/emitter.h"
#include <vector>

namespace coresystem
{
  class particlesystem {
  public:
    particlesystem();
    ~particlesystem();
    
    void addEmitter (emitter* obj);
    void removeEmitter (emitter* obj);
    
    int numberOfEmitter ();

    int numberOfParticles ();

    void render (sf::RenderWindow& wnd);
    
  protected:
    std::vector<emitter*>		m_emitters;
  };
}

#endif
