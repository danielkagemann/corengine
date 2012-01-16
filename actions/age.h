#ifndef age_h_
#define age_h_

#include "actionbase.h"

/// Decrements the lifetime of a particle by one each frame. If lifetime is zero the particle dies.
/// _name action:age

namespace coresystem {
  class age : public actionbase {
  public:

    age ()
    {}

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
        p->lifetime--;
        if (p->lifetime <= 0) {
          p->isDead = true;
        }
      }
    }
  };
}

#endif
