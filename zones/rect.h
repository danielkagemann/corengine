#ifndef zonerect_h_
#define zonerect_h_

#include "zonebase.h"

namespace coresystem {

/// Defines a rectangular zone.
/// _name zone:rect
/// _param <left> left position as integer
/// _param <top> top position as integer
/// _param <right> right position as integer
/// _param <bottom> bottom position as integer

//# --- rectangle ---
class zoneRect : public zonebase {
public:
  zoneRect (float left, float top, float right, float bottom)
  {
    m_rect = sf::FloatRect (left,top,right,bottom);
  }

  virtual sf::Vector2f getPoint ()
  {
    return sf::Vector2f (sf::Randomizer::Random (m_rect.Left,m_rect.Right), sf::Randomizer::Random (m_rect.Top,m_rect.Bottom));
  }

  virtual bool contains (float x, float y)
  {
	  return m_rect.Contains (x,y);
  }

  virtual void render (sf::RenderWindow& wnd)
  {
    sf::Shape   rc = sf::Shape::Rectangle (m_rect.Left,m_rect.Top,m_rect.Right,m_rect.Bottom,ZONECOLOR,1.f,ZONECOLOR);
    rc.EnableFill(true);
    wnd.Draw (rc);
  }


protected:
  sf::FloatRect   m_rect;
};

}
#endif
