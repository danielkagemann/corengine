#ifndef scale_h_
#define scale_h_

#include <SFML/Graphics.hpp>
#include "actionbase.h"

/// Scale the particle by this value.
/// _name action:scale
/// _param <value> Modify scalefactor with this value as floating point

namespace coresystem {

  class scale : public actionbase  { 
    public:
      scale (float factor)
      {
        m_value = factor;
      }

      virtual void update (emitter* em, particle* p, float dt)
      {
        if (p->isDead == false) {

          if (zoneimpact(p->position)==false) {
            return;
          }

          p->scalefactor += m_value;
					//# scale factor towards zero ?
          if (p->scalefactor <=0.f) {
          	p->isDead=true;
            return;
          }
        }
        
	      if (p->shape.GetImage () != NULL) {
           p->shape.Resize(p->shape.GetImage()->GetWidth()*p->scalefactor, p->shape.GetImage()->GetHeight()*p->scalefactor);	//# use static value
  	    }
      }

  protected:
    float   m_value;
  };
}

#endif
