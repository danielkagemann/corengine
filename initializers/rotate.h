#ifndef initrotate_h_
#define initrotate_h_

#include "initbase.h"

namespace coresystem {

/// Defines the rotation of new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:rotate
/// _param <min> minimum factor as floating point
/// _param <max> maximum factor as floating point

//# ---- rotate ----
class initRotate : public initbase {
public:
  initRotate (float mi, float ma) 
  {
    m_val[0] = mi;
    m_val[1] = ma;
    if (mi > ma) {
      throw ("rotate minimum is greater maximum");
    }
  }

  virtual void init (emitter* em, particle* p)
  {
    p->angle = sf::Randomizer::Random (m_val[0],m_val[1]);
  }
protected:
  float m_val[2];
};

}


#endif