#ifndef initrotatevelocity_h_
#define initrotatevelocity_h_

#include "initbase.h"

namespace coresystem {

/// Defines the rotation speed of new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:rotatevelocity
/// _param <min> minimum factor as floating point
/// _param <max> maximum factor as floating point

//# ---- rotateVelocity ----
class initRotateVelocity : public initbase {
public:
  initRotateVelocity (float mi, float ma) 
  {
    m_val[0] = mi;
    m_val[1] = ma;
    if (mi > ma) {
      throw ("rotateVelocity minimum is greater maximum");
    }
  }

  virtual void init (emitter* em, particle* p)
  {
    p->angleVelo = sf::Randomizer::Random (m_val[0],m_val[1]);
  }
protected:
  float m_val[2];
};

}


#endif