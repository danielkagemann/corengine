#ifndef fade_h_
#define fade_h_

#include "actionbase.h"

/// Reduce alpha value by given value. If alpha gets zero or 255 the particle dies.
/// _name action:fade
/// _param <value> Modify alpha with this value as integer

namespace coresystem {
  class fade : public actionbase {
  public:
    fade ()
    {
      m_factor = 1;
    }

    fade (int f)
    {
      m_factor = f;
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        if (zoneimpact(p->position)==false) {
          return;
        }

        if (p->color.a > 254) {
          p->color.a  = 255;
        }
        else {
          p->color.a-=m_factor;

          if (p->color.a < m_factor) {
            p->isDead = true;
            p->color.a += m_factor;
          }
          if (p->color.a < 0) {
            p->isDead = true;
          }
        }
        
        if (p->isDead==false && p->shape.GetImage () != NULL) {
        	p->shape.SetColor (p->color);
        }
      }
    }

  protected:
    int m_factor;
  };
}

#endif
