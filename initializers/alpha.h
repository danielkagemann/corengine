#ifndef initalpha_h_
#define initalpha_h_

#include "initbase.h"
#include "../helper/helper.h"

/// Defines the alpha value of new particles. Values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:alpha
/// _param <min> minimum alpha as integer
/// _param <max> maximum alpha as integer

namespace coresystem {
//# ---- alpha ----
class initAlpha : public initbase{
  public:
    initAlpha (int mi, int ma)
    {
      m_range.set(mi,ma);

      if (m_range.getLower() < 0) {
        throw ("minimum below 0");
      }
      if (m_range.getUpper() > 255) {
        throw ("maximum greater 255");
      }
    }

    virtual void init (emitter* em, particle* p)
    {
      if (m_range.equal()==true) {
        p->color.a = m_range.getLower();
      }
      else {
        p->color.a = m_range.getRandom();
      }

      //# in case of a shape we have to set the color there
      if (p->shape.GetImage() != NULL) {
        p->shape.SetColor (p->color);
      }
    }

protected:
  TRangeInt   m_range;
};
}


#endif