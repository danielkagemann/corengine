#ifndef color_h_
#define color_h_

#include "actionbase.h"

/// Reduce color values R,G,B with given values. Values will be decremented
/// _name action:color
/// _param <rval> value to decrement the red value by
/// _param <gval> value to decrement the green value by
/// _param <bval> value to decrement the blue value by

namespace coresystem {
  class color : public actionbase {
  public:

    color ()
    {
      m_rgb[0] = 0;
      m_rgb[1] = 0;
      m_rgb[2] = 0;
    }

    color (int r, int g, int b)
    {
      m_rgb[0] = r;
      m_rgb[1] = g;
      m_rgb[2] = b;
    }

#define CALC(val,id)  val = (((int)val - m_rgb[id]) < 0) ? 0 : (((int)val - m_rgb[id]) > 255) ? 255 : (val-m_rgb[id])

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
      
         if (zoneimpact(p->position)==false) {
            return;
         }
         CALC(p->color.r, 0);
         CALC(p->color.g, 1);
         CALC(p->color.b, 2);
          
         //# in case of a shape we have to set the color there
         if (p->shape.GetImage() != NULL) {
            p->shape.SetColor (p->color);
         }          
      }
    }
protected:
    int   m_rgb[3];
  };
}

#endif
