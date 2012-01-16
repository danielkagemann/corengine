#ifndef initvelocity_h_
#define initvelocity_h_

#include "initbase.h"

/// Defines velocities for new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:velocity
/// _param <x-min> minimum x-velocity as floating point
/// _param <x-max> maximum x-velocity as floating point
/// _param <y-min> minimum y-velocity as floating point
/// _param <y-max> maximum y-velocity as floating point

namespace coresystem {
//# ---- velocity ----
class initVelocity : public initbase {
public:
  initVelocity (float xi,float xa, float yi, float ya)
  {
     m_x[0] = xi;
     m_x[1] = xa;
     m_y[0] = yi;
     m_y[1] = ya;
     if (xi > xa) {
       throw ("x velocity minimum greater maximum");
     }
     if (yi > ya) {
       throw ("y velocity minimum greater maximum");
     }
  }

  virtual void init (emitter* em, particle* p)
  {
    p->velocity.x = sf::Randomizer::Random (m_x[0],m_x[1]);
    p->velocity.y = sf::Randomizer::Random (m_y[0],m_y[1]);
  }
protected:
  float   m_x[2];
  float   m_y[2];
};

}


#endif