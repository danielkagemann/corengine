/*
 * coresystem
 * 
 * Author: Daniel Kagemann
 * Copyright (c) Daniel Kagemann 2010
 * http://coreapps.de
 * 
 * Licence Agreement
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "particlesystem.h"
#include "record.h"

#include "actions/accelerate.h"
#include "actions/speedlimit.h"
#include "actions/move.h"
#include "actions/death.h"
#include "actions/randomdrift.h"
#include "actions/age.h"
#include "actions/fade.h"
#include "actions/scale.h"
#include "actions/lineardrag.h"

#include "initializers/initbase.h"
#include "initializers/age.h"
#include "initializers/alpha.h"
#include "initializers/bitmap.h"
#include "initializers/color.h"
#include "initializers/dot.h"
#include "initializers/positionabs.h"
#include "initializers/scale.h"
#include "initializers/velocity.h"

#include "zones/zonebase.h"
#include "zones/point.h"
#include "zones/rect.h"
#include "zones/point.h"
#include "zones/bitmap.h"

#define FG_COLOR    sf::Color (255,255,255)
#define BG_COLOR    sf::Color (0,0,0)

int main(int argc, char* argv[])
{
 	 std::string		msg;

   try {
    if (argc!=2) {
      throw ("number of arguments mismatch");
    }
    sf::RenderWindow App(sf::VideoMode(640, 480), "corengine");

    App.SetFramerateLimit(30);

    //# create system
    coresystem::particlesystem system;

    //# get from file
    coresystem::emitter *emi = new coresystem::emitter (argv[1]);
    system.addEmitter (emi);
    emi->init();

    bool    quit = false;
    char    infoText[300];

    sf::Color     foreColor = FG_COLOR;
    sf::Color     backColor = BG_COLOR;
    
    //# autoreload feature
    FileInfo			fileinfo (argv[1]);
    Record    		recording;

    // Start game loop
    while (App.IsOpened() && quit==false) {
      // Process events
      sf::Event Event;
      while (App.GetEvent(Event)) {
        // Close window : exit
        if (Event.Type == sf::Event::Closed) {
          quit = true;
          continue;
        }
        
        //# user interaction
        if (Event.Type == sf::Event::KeyPressed) {
          switch (Event.Key.Code) {
            case sf::Key::A:
              recording.Start (1);
              break;
            
            case sf::Key::S:
              recording.Stop ();
              break;
            case sf::Key::I:
              if (backColor == BG_COLOR) {
                backColor = FG_COLOR;
                foreColor = BG_COLOR;
              }
              else {
                backColor = BG_COLOR;
                foreColor = FG_COLOR;
              }
              break;
            }
        }
      }
      // Clear screen
      App.Clear(backColor);
      
      //# draw text only if not recording
      if (recording.IsRecording ()==false) {

        //# 'A' for recording 
        sf::String help ("[A] start recording - [S] stop recording - [I] invert colors", sf::Font::GetDefaultFont (), 13);
        help.SetColor(foreColor);
        help.SetPosition (2,5);
        App.Draw (help);

        //# draw number of current particles in the info area
        sprintf (infoText,"%d particles in system", system.numberOfParticles());
        help.SetText (infoText);
        help.SetPosition (2,25);
        App.Draw (help);
      }
      
      //# message ?
      if (msg.size() > 0) {
      	sf::String m (msg.c_str(),sf::Font::GetDefaultFont(),13);
        m.SetPosition (10,450);
        m.SetColor(foreColor);
        App.Draw (m);
      }

      //# draw particle system
      system.render (App);
      // Finally, display the rendered frame on screen
      App.Display();

      //# take snapshot
      recording.Snapshot (App);

			//# check for modified file
      if (fileinfo.isModified ()==true) {
      	OUTPUT ("reloading emitter\n");
        //# delete emitter
        system.removeEmitter(emi);

				//# embed reload emitter to display error messages here        
        try {
        	emi = new coresystem::emitter (argv[1]);
	        system.addEmitter (emi);
  	      emi->init();
          msg="";
        }
        catch (const char* lpEmbed) {
	        msg = lpEmbed;
        }
      }
    }

    //# remove from system
    system.removeEmitter (emi);
    App.Close();

  }
  catch (const char* errorstring) {
    OUTPUT ("!: corengine throws an error: %s\n",errorstring);
  }

  return EXIT_SUCCESS;
}
