#ifndef boundingbox_h_
#define boundingbox_h_

#include "actionbase.h"

/// Definition of a rectangular bounding zone where each particle will bounce back.
/// _name action:boundingbox
/// _name <left> Defines left position for rectangle as integer
/// _name <top> Defines top position for rectangle as integer
/// _name <right> Defines right position for rectangle as integer
/// _name <bottom> Defines bottom position for rectangle as integer
/// _name <bounce> Defines how to bounce back used for velocity calculation. Default is 1

namespace coresystem {
  class boundingbox : public actionbase {
  public:

    boundingbox (int left, int top, int right, int bottom, float bounce=1.f)
    {
      m_rect   = sf::IntRect(left,top,right,bottom);
      m_bounce = bounce;
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
        float radius = 1.f;

        //# right
        if (p->velocity.x > 0 && (p->position.x + radius >= m_rect.Right)) {
          p->velocity.x = -p->velocity.x * m_bounce;
          p->position.x += 2*(m_rect.Right - (p->position.x + radius));
        }
        //# left
			  else if ( p->velocity.x < 0 &&  (p->position.x - radius  <= m_rect.Left)) {
				  p->velocity.x = -p->velocity.x * m_bounce;
				  p->position.x += 2 * ( m_rect.Left - (p->position.x - radius) );
			  }
        //# bottom
			  if ( p->velocity.y > 0 && (p->position.y + radius >= m_rect.Bottom)) {
				  p->velocity.y = -p->velocity.y * m_bounce;
				  p->position.y += 2 * ( m_rect.Bottom - (p->position.y + radius) );
			  }
        //# top
        else if ( p->velocity.y < 0 && (p->position.y - radius <= m_rect.Top)) {
				  p->velocity.y = -p->velocity.y * m_bounce;
				  p->position.y += 2 * ( m_rect.Top - (p->position.y - radius) );
			  }
      }
    }

  protected:
    sf::IntRect       m_rect;
    float             m_bounce;
  };
}

#endif
