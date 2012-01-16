#ifndef death_h_
#define death_h_

#include <SFML/Graphics.hpp>
#include "actionbase.h"

/// Definition of a rectangular death zone where each particle will die.
/// _name action:death
/// _param <left> Defines left position for rectangle as integer
/// _param <top> Defines top position for rectangle as integer
/// _param <right> Defines right position for rectangle as integer
/// _param <bottom> Defines bottom position for rectangle as integer
/// _param <inside> Defines if the particle dies when it is inside the rectangle or not. Valid values are yes and no

namespace coresystem {

  class death : public actionbase  { 
    public:
      death (float left, float top, float right, float bottom, bool inside)
      {
        m_rect = sf::FloatRect (left,top,right,bottom);
        m_particle_inside = inside;
      }

      virtual void update (emitter* em, particle* p, float dt)
      {
        if (m_rect.Contains (p->position.x,p->position.y) == m_particle_inside) {
          p->isDead = true;
        }
      }

  protected:
    //# defines the zone where to respawn
    sf::FloatRect   m_rect;
    bool            m_particle_inside;
  };
}

#endif
