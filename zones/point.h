#ifndef zonepoint_h_
#define zonepoint_h_

#include "zonebase.h"

/// Defines a single point at a absolute position.
/// _name zone:point
/// _param <x> x position of the point as floating point
/// _param <y> y position of the point as floating point

namespace coresystem {

//# --- point ---
class zonePoint : public zonebase {
public:
  zonePoint (float x, float y)
  {
    m_point = sf::Vector2f (x,y);
  }

  virtual sf::Vector2f getPoint ()
  {
    return m_point;
  }

  virtual bool contains (float x, float y)
  {
	  return (sf::Vector2f(x,y) == m_point);
  }

protected:
    sf::Vector2f  m_point;
};
}

#endif
