/*
 *  particlesystem.cpp
 *  corengine
 *
 *  Created by Daniel Kagemann on 15.09.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */

#include "particlesystem.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
particlesystem::particlesystem()
{
	m_emitters.clear ();
}
/*-------------------------------------------------------------------*/
particlesystem::~particlesystem()
{
	int	i;
  for (i = static_cast<int>(m_emitters.size()-1); i >=0; i--) {
  	delete m_emitters[i];
    m_emitters[i] = NULL;
  }
  m_emitters.clear();
}
/*-------------------------------------------------------------------*/
void particlesystem::addEmitter (emitter* obj)
{
	m_emitters.push_back(obj);
}
/*-------------------------------------------------------------------*/
void particlesystem::removeEmitter (emitter* obj)
{
  for (int i = static_cast<int> (m_emitters.size()-1); i>=0; i--) {
	  if (m_emitters[i] == obj) {
	    delete m_emitters[i];
      m_emitters.erase (m_emitters.begin()+i);
      break;
    }
  }
}
/*-------------------------------------------------------------------*/
void particlesystem::render (sf::RenderWindow& wnd,bool zonedisplay)
{
	int	i;
  for (i = 0; i < static_cast<int> (m_emitters.size()); m_emitters[i]->render(wnd,zonedisplay), i++);
}
/*-------------------------------------------------------------------*/
int particlesystem::numberOfEmitter ()
{
	return static_cast<int> (m_emitters.size());
}
/*-------------------------------------------------------------------*/
int particlesystem::numberOfParticles ()
{
  int count = 0;
  for (int i = 0; i < numberOfEmitter(); i++) {
    count+=static_cast<int> (m_emitters[i]->getParticles().size());
  }
  return count;
}
/*-------------------------------------------------------------------*/
