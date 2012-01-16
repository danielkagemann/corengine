#ifndef move_h_
#define move_h_

#include "actionbase.h"

/// Set new position with use of velocity. 
/// _name action:move


namespace coresystem {
  class move : public actionbase {
  public:

    move ()
    {}

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
        p->position.x += p->velocity.x * dt;
        p->position.y += p->velocity.y * dt;
      }
    }
  };
}

#endif
