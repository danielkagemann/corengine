#ifndef morph_h_
#define morph_h_

#include "actionbase.h"
#include "../zones/zonebase.h"

/// Morph particles from one zone to another (e.g. action:morph=@<zonenumber>,<steps>)
/// _name action:morph
/// _param <zonenumber> number of the zone to use as source
/// _param <steps> number of movement steps to use as integer

namespace coresystem {
  class morph : public actionbase {

  public:
    struct data {
      sf::Vector2f    diff;
      int             steps;
    };
  public:
    morph (zonebase* z, int steps)
    {
      m_destination = z;
      m_steps = steps;
      if (z==NULL) {
        throw ("morph has invalid target zone specified");
      }
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      //# check if particle within dictionary
      if (m_dict.find(p) != m_dict.end()) {
        if (m_dict[p].steps > 0) {
          m_dict[p].steps--;
          //# existing. move on
          p->position.x += m_dict[p].diff.x;
          p->position.y += m_dict[p].diff.y;
        }
      }
      else {
        struct data dt;
        //# get a point from the destination zone
        dt.diff = m_destination->getPoint ();
        dt.diff.x = (dt.diff.x - p->position.x) / m_steps;
        dt.diff.y = (dt.diff.y - p->position.y) / m_steps;
        dt.steps = m_steps;
        //# put into dictionary
        m_dict[p] = dt;
      }
    }

  protected:
    zonebase* m_destination;
    int       m_steps;

    std::map<particle*, struct data>   m_dict;    
  };
}

#endif
