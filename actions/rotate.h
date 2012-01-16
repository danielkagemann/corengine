#ifndef rotate_h_
#define rotate_h_

#include "actionbase.h"

/// Rotate the particle with the given velocity 
/// _name action:rotate


namespace coresystem {
  class rotate : public actionbase {
  public:

    rotate ()
    {}

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
        p->angle += p->angleVelo * dt;
        
        if (p->angle < 0.f) {
          p->angle = 360.f;
        }
        else if (p->angle > 360.f) {
          p->angle = 0.f;
        }
	      if (p->shape.GetImage () != NULL) {
           p->shape.SetRotation (p->angle);
  	    }
      }
    }
  };
}

#endif
