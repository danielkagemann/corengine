#ifndef lineardrag_h_
#define lineardrag_h_

#include "actionbase.h"

/// Set a factor for linear drift in both directions
/// _name action:lineardrag
/// _param <factor> This factor is used as kind of multiplicator (1-<factor>)for both velocity directions.

namespace coresystem {
  class lineardrag : public actionbase {
  public:

    lineardrag (float drag = 0)
    {
      m_drag = drag;
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        if (zoneimpact(p->position)==false) {
          return;
        }

        float   scale = 1-m_drag*dt / 1.f; //# 1.f is particle mass
        if (scale<0) {
          p->velocity.x = 0.f;
          p->velocity.y = 0.f;
        }
        else {
          p->velocity.x*=scale;
          p->velocity.y*=scale;
        }
      }
    }

  protected:
      float m_drag;
  };
}

#endif
