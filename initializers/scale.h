#ifndef initscale_h_
#define initscale_h_

#include "initbase.h"

/// Defines the scalefactor of new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:scale
/// _param <min> minimum factor as floating point
/// _param <max> maximum factor as floating point

namespace coresystem {
  //# ---- scale ----
  class initScale : public initbase {
  public:
    initScale (float mi, float ma) 
    {
      m_val[0] = mi;
      m_val[1] = ma;
      if (mi > ma) {
        throw ("size minimum is greater maximum");
      }
    }

    virtual void init (emitter* em, particle* p)
    {
      p->scalefactor = sf::Randomizer::Random (m_val[0],m_val[1]);
      
      if (p->shape.GetImage () != NULL) {
        p->shape.Resize(p->shape.GetImage()->GetWidth()*p->scalefactor, p->shape.GetImage()->GetHeight()*p->scalefactor);	//# use static value
      }
    }
  protected:
    float m_val[2];
  };
}


#endif