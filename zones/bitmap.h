#ifndef zonebitmap_h_
#define zonebitmap_h_

#include "zonebase.h"

namespace coresystem {

/// Load the given file and generate a particle for each non-alpha pixel. If file cannot be openened an error is thrown.
/// _name zone:bitmap
/// _param <file> file to load including path and extension

//# ---- bitmap ---
class zoneBitmap : public zonebase {
public:
  zoneBitmap (const char* lpFile, float offx=0.f, float offy=0.f)
  {
    sf::Image   img;
    if (img.LoadFromFile (lpFile)==false) {
      throw ("zone bitmap cannot be loaded");
    }

    unsigned int x,y;
    for (y = 0; y < img.GetHeight(); y++) {
      for (x = 0; x < img.GetWidth(); x++) {
        if (img.GetPixel (x,y).a != 0) {
          m_points.push_back (sf::Vector2f(static_cast<float>(x+offx),static_cast<float>(y+offy)));
        }
      }
    }

    if (m_points.size()==0) {
      throw ("zone bitmap does not contain any opaque pixels");
    }
  }

  virtual bool contains (float x, float y)
  {
	  for (int i = 0; i < static_cast<int> (m_points.size()); i++) {
		  if (m_points[i] == sf::Vector2f(x,y)) {
			  return true;
		  }
	  }
	  return false;
  }

  virtual size_t getCount ()
  {
    return m_points.size();
  }

  virtual sf::Vector2f getPoint ()
  {
    if (m_points.size() == 0) {
      return sf::Vector2f(-1.f,-1.f);
    }

    //# get random point
    int   index = sf::Randomizer::Random (0, static_cast<int> (m_points.size()-1));
    sf::Vector2f  pt = m_points[index];
    m_points.erase (m_points.begin()+index);
    return pt;
  }

protected:
  std::vector<sf::Vector2f>   m_points;
};

}
#endif
