#ifndef randomdrift_h_
#define randomdrift_h_

#include "actionbase.h"

/// Set drift for both directions
/// _name action:randomdrift
/// _param <x> x value to be used as floating point
/// _param <y> y value to be used as floating point

namespace coresystem {
  class randomdrift : public actionbase {
  public:

    randomdrift ()
    {
      m_drift = sf::Vector2f (0.f,0.f);
    }

    randomdrift (float x, float y)
    {
      m_drift = sf::Vector2f(x,y);
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        if (zoneimpact(p->position)==false) {
          return;
        }

        p->velocity.x += sf::Randomizer::Random (-0.5f,0.5f) * m_drift.x * dt;
        p->velocity.y += sf::Randomizer::Random (-0.5f,0.5f) * m_drift.y * dt;
      }
    }

  protected:
    sf::Vector2f    m_drift;
  };
}

#endif
