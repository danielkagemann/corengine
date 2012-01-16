#ifndef randompos_h_
#define randompos_h_

#include "actionbase.h"

/*
group: action
desc: adds a random position for both directions
file: action:randompos=<xval-min>,<xval-max>,<yval-min>,<yval-max>
*/

namespace coresystem {
  class randompos : public actionbase {
  public:
    
    randompos ()
    {
   m_offsetx[0] = 0.f;m_offsetx[1]=0.f;
   m_offsety[0] = 0.f;m_offsety[1]=0.f;
    }    
    randompos (float xi,float xa,float yi, float ya)
    {
   m_offsetx[0] = xi;m_offsetx[1]=xa;
   m_offsety[0] = yi;m_offsety[1]=ya;
    }
    
    virtual void update (emitter* em, particle* p, float dt)
	  {
  	 if (p->isDead == false) {
     
    	 if (zoneimpact(p->position)==false) {
      	 return;
	     }
     
       p->position.x += sf::Randomizer::Random (m_offsetx[0], m_offsetx[1]);
       p->position.y += sf::Randomizer::Random (m_offsety[0], m_offsety[1]);
	   }
    }
    
  protected:
    float    m_offsetx[2];
    float    m_offsety[2];
  };
}

#endif
