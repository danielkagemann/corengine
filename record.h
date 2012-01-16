#ifndef record_h_
#define record_h_

#include <SFML/Graphics.hpp>
#include <vector>


//# create animation with imagemagick
//# mogrify *.jpg -flip -crop 400x200+120+0 +repage -resize 250x
//# iconvert -dispose None *.jpg -loop 0 animation.gif

class Record {
public:
  Record ();
  ~Record();

  void Start (int each);
  void Stop ();
  void Snapshot (sf::RenderWindow& wnd);
  bool IsRecording ();

protected:
  int                     m_each_n_frame;
  int                     m_current_frame;
  std::vector<sf::Image*> m_images;
  bool                    m_isRecording;
};

#endif
