#ifndef initOffsetpos_h_
#define initOffsetpos_h_

#include "initbase.h"

/// Add offset to each particles position<br/> Note: this initializer should be sorted after positionabs
/// _name init:offsetpos
/// _param <x> Offset as integer for x position offset as floating point
/// _param <y> Offset as integer for y position offset as floating point

namespace coresystem {

//# ---- age ----
class initOffsetpos : public initbase {
public:
  initOffsetpos (float x, float y) 
  {
    m_pos = sf::Vector2f(x,y);
  }

  virtual void init (emitter* em, particle* p)
  {
    p->position.x += m_pos.x;
    p->position.y += m_pos.y;
  }
protected:
  sf::Vector2f      m_pos;
};

}


#endif