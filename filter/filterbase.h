/*
 *  filterbase.h
 *  corengine
 *
 *  Created by Daniel Kagemann on 30.11.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */
#ifndef filterbase_h_
#define filterbase_h_

#include <SFML/Graphics.hpp>

namespace coresystem {
  
  class filterbase {
public:
	filterbase();
  virtual ~filterbase();
  
  virtual void perform (sf::RenderWindow& wnd);
  
  static filterbase* factory (std::string settings);
};

}

#endif

