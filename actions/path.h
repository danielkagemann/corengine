#ifndef path_h_
#define path_h_

#include "actionbase.h"

/// simulate a path instead of linear movement
/// _name action:path
/// _param <type> The following is allowed. sinus for both directions. sinus-x for x direction. sinus-y for y direction.
/// _param <amplitude> the amplitude of the wave
/// _param <interval> increment interval to be used

namespace coresystem {
  class path : public actionbase {

  protected:
    enum {
      type_sinus = 0,
      type_sinx,
      type_siny,
    };
  public:

    path ()
    {
      m_amplitude = 1;
      m_interval  = 1;
      m_type      = type_sinus;
    }

    path (std::string type, float am, float inc)
    {
      m_amplitude = am;
      m_interval  = inc;

      if (type.compare ("sinus") == 0) {
        m_type = type_sinus;
      }
      else if (type.compare ("sinus-x") == 0) {
        m_type = type_sinx;
      }
      else if (type.compare ("sinus-y") == 0) {
        m_type = type_siny;
      }
      else {
        throw ("type is wrong");
      }
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false && p->usepath == true) {

        if (zoneimpact(p->position)==false) {
          return;
        }

        float   valx = m_amplitude * sin (p->pathvalue.x);
        float   valy = m_amplitude * sin (p->pathvalue.y);

        switch (m_type) {
        case type_sinus:
          p->position.x += valx;
          p->position.y += valy;
          p->pathvalue.x+=m_interval;
          p->pathvalue.y+=m_interval;
          break;
        case type_sinx:
          p->position.x += valx;
          p->pathvalue.x+=m_interval;
          break;
        case type_siny:
          p->position.y += valy;
          p->pathvalue.y+=m_interval;
          break;
        }
      }
    }

  protected:
    float             m_amplitude;
    float             m_interval;
    int               m_type;
  };
}

#endif
