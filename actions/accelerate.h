#ifndef accelerate_h_
#define accelerate_h_

#include "actionbase.h"

/// Accelerate velocity by the given values for each direction.
/// _name action:accelerate
/// _param <x> Increment x-velocity with this value as floating point
/// _param <y> Increment y-velocity with this value as floating point

namespace coresystem {
  class accelerate : public actionbase {
  public:

    accelerate ()
    {
      m_accelerate = sf::Vector2f(0.f,0.f);
    }

    accelerate (float x, float y)
    {
      m_accelerate = sf::Vector2f(x,y);
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        if (zoneimpact(p->position)==false) {
          return;
        }
        p->velocity.x += m_accelerate.x * dt;
        p->velocity.y += m_accelerate.y * dt;
      }
    }

  protected:
    sf::Vector2f    m_accelerate;
  };
}

#endif
