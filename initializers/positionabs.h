#ifndef initpositionabs_h_
#define initpositionabs_h_

#include "initbase.h"
#include "../zones/zonebase.h"

/// Defines a rectangle zone where new particles are created.
/// _name init:positionabs=rect=<parameter><br/> init:positionabs=@<zonenumber>
/// _param <left> left position as integer
/// _param <top> top position as integer
/// _param <right> right position as integer
/// _param <bottom> bottom position as integer
/// _param <zonenumber> Reference to a valid zone: definition

namespace coresystem {
//# ---- absoluteposition ----
class initPositionAbs : public initbase {
public:
  initPositionAbs (zonebase*  z)
  {
    m_zone = z;
    if (z==NULL) {
      throw ("no zone specified");
    }
  }

  virtual void init (emitter* em, particle* p)
  {
    p->position = m_zone->getPoint();
  }

protected:
  zonebase*  m_zone;
};

}


#endif