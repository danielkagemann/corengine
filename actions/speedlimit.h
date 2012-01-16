#ifndef speedlimit_h_
#define speedlimit_h_

#include "actionbase.h"

/// Set the maximum speed for both directions.
/// _name action:speedlimit
/// _param <x> Maximum x-velocity as floating point
/// _param <y> Maximum y-velocity as floating point

namespace coresystem {
  class speedlimit : public actionbase {
  public:

    speedlimit ()
    {
      m_limits = sf::Vector2f(0.f,0.f);
    }

    speedlimit (float x, float y)
    {
      m_limits = sf::Vector2f(x,y);
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      //# dt not needed
      if (p->isDead == false) {
        if (p->velocity.x > m_limits.x) {
          p->velocity.x = m_limits.x;
        }
        if (p->velocity.y > m_limits.y) {
          p->velocity.y = m_limits.y;
        }
      }
    }

  protected:
    sf::Vector2f    m_limits;
  };
}

#endif
