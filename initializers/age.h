#ifndef initage_h_
#define initage_h_

#include "initbase.h"

namespace coresystem {

/// Defines the lifetime of new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:age
/// _param <min> minimum lifetime as integer
/// _param <max> maximum lifetime as integer

//# ---- age ----
class initAge : public initbase {
public:
  initAge (int mi, int ma) 
  {
    m_val[0] = mi;
    m_val[1] = ma;
    if (mi > ma) {
      throw ("age minimum is greater maximum");
    }
  }

  virtual void init (emitter* em, particle* p)
  {
    p->lifetime = sf::Randomizer::Random (m_val[0],m_val[1]);
  }
protected:
  int m_val[2];
};

}


#endif