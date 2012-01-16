#ifndef sharedimage_h__
#define sharedimage_h__

#include <map>

using namespace std;

typedef map<string, sf::Image>		TObjectMap;

class sharedimage {
public:
  sharedimage()
	{}

	virtual ~sharedimage()
  {}

  bool existImage (const char* lpName) 
  {
    return (mBitmaps.find(lpName) == mBitmaps.end()) ? false : true;
  }
  
  sf::Image& addImage (const char* lpName, sf::Image img)
  {
		img.SetSmooth (true);
	  mBitmaps[lpName] = img;
	  return mBitmaps[lpName];
  }
	
	sf::Image& Image (const char* lpName)
	{
    if (mBitmaps.find(lpName) == mBitmaps.end()) {
      sf::Image   img;
      if (img.LoadFromFile(lpName)==false) {
        throw ("error loading image");
      }
      img.SetSmooth (true);
      mBitmaps[lpName] = img;
    }
    return mBitmaps[lpName];
	}
	
protected:
	TObjectMap		mBitmaps;
};

#endif
