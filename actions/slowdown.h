#ifndef slowdown_h_
#define slowdown_h_

#include "actionbase.h"

/// Set a factor for slowing down in both directions
/// _name action:slowdown
/// _param <factor> This factor is used as kind of multiplicator for both velocity directions.

namespace coresystem {
  class slowdown : public actionbase {
  public:

    slowdown (float sl)
    {
      m_sl = sl;
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        if (zoneimpact(p->position)==false) {
          return;
        }

        float len = p->velocity.x * p->velocity.x + p->velocity.y * p->velocity.y;
        if (len == 0) {
          return;
        }
        float scale = m_sl / sqrt (len);
        if (scale < 0) {
          p->velocity = sf::Vector2f (0.f,0.f);
        }
        else {
          p->velocity.x *=scale;
          p->velocity.y *=scale;
        }
      }
    }

  protected:
    float m_sl;
  };
}

#endif
