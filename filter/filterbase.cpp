/*
 *  filterbase.cpp
 *  corengine
 *
 *  Created by Daniel Kagemann on 30.11.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */

#include "filterbase.h"
#include "../helper/helper.h"

#include "blur.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
filterbase::filterbase ()
{}
/*-------------------------------------------------------------------*/
filterbase::~filterbase () {}
/*-------------------------------------------------------------------*/
filterbase* filterbase::factory (std::string settings)
{
  std::vector<std::string>    argv;
  
  //# blur
  if (settings.substr (0,4)=="blur") {
    return new filterBlur ();
  }

  throw helper::errormessage("unknown filter command: %s",settings.c_str());
  return NULL;
}
/*-------------------------------------------------------------------*/
void filterbase::perform (sf::RenderWindow& wnd) 
{
	//# nothing do to here
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
