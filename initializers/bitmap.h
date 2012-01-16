#ifndef initbitmap_h_
#define initbitmap_h_

#include "initbase.h"
#include "../emitters/emitter.h"

/// Defines the bitmap file as shape for new particles. Scale-values are used as bounds for random. <min> must be greater than <max>, otherwise an error is thrown.
/// _name init:bitmap
/// _param <file> filename with path information and extension for the bitmap to use
/// _param <scale-min> minimum factor as floating point
/// _param <scale-max> maximum factor as floating point

namespace coresystem {
//# ---- bitmap ----
class initBitmap : public initbase {
public:
  initBitmap (const char* lpFile, float scalei, float scalea)
  {
    m_shapename  = lpFile;
    m_scale[0]   = scalei;
    m_scale[1]   = scalea;
    if (scalei > scalea) {
      throw ("scale minimum is greater maximum");
    }
  }

  virtual void init (emitter* em, particle* p)
  {
    sf::Image& img = em->getResource ().Image (m_shapename.c_str());

    p->shape.SetImage (img);
    p->shape.SetCenter(img.GetWidth()/2.f, img.GetHeight()/2.f);
    float     scale = sf::Randomizer::Random (m_scale[0],m_scale[1]);
    p->shape.Resize (img.GetWidth ()*scale,img.GetHeight()*scale);
  }

protected:
  float       m_scale[2];
  std::string m_shapename;
};

}


#endif