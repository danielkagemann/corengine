/*
 *  blur.h
 *  corengine
 *
 *  Created by Daniel Kagemann on 30.11.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */

#ifndef blur_h_
#define blur_h_

/// Defines blur filter
/// _name filter:blur

#include "filterbase.h"

using namespace coresystem;

class filterBlur : public filterbase {
public:
	filterBlur()
  {
  	m_fx.LoadFromMemory (
     "texture framebuffer\n"
     "float offset\n"
     "\n"
     "effect\n"
     "{\n"
     "vec2 offx = vec2(offset, 0.0);\n"
     "vec2 offy = vec2(0.0, offset);\n"
     " \n"
     "vec4 c0 = framebuffer(_in);\n"
     "vec4 c1 = framebuffer(_in - offy);\n"
     "vec4 c2 = framebuffer(_in + offy);\n"
     "vec4 c3 = framebuffer(_in - offx);\n"
     "vec4 c4 = framebuffer(_in + offx);\n"
     " \n"
     "_out = c0 * 0.2 + c1 * 0.2 + c2 * 0.2 + c3 * 0.2 + c4 * 0.2;\n"
     "}\n"
    );
    m_fx.SetTexture("framebuffer", NULL);
    m_fx.SetParameter("offset", 2.f);
  }
  
  void perform (sf::RenderWindow& wnd) 
  {
     if (sf::PostFX::CanUsePostFX() == false) {
      return;
     }
     wnd.Draw(m_fx);

  
  /*
   if (p->shape.GetImage() == NULL) {
      throw ("cannot use blur filter. no shape defined");
    }
    //# for better access
   const sf::Image    *source = p->shape.GetImage();
    sf::Image         blurred;
    blurred.Create (source->GetWidth(),source->GetHeight());

    //# blur code taken from processing library
    float v = 1.f/9.f;
    float kernel[3][3] = { { v, v, v },
                           { v, v, v },
                           { v, v, v } };

    // Loop through every pixel in the image.
    for (int y = 1; y < static_cast<int> (source->GetHeight()-1); y++) { // Skip top and bottom edges
      for (int x = 1; x < static_cast<int> (source->GetWidth()-1); x++) { // Skip left and right edges

        float sum = 0.f; // Kernel sum for this pixel
        for (int ky = -1; ky <= 1; ky++) {
          for (int kx = -1; kx <= 1; kx++) {
            
            // Image is grayscale, red/green/blue are identical
            float val = source->GetPixel (x+kx,y+ky).r;
            
            // Multiply adjacent pixels based on the kernel values
            sum += kernel[ky+1][kx+1] * val;
          }
        }
        // For this pixel in the new image, set the gray value
        // based on the sum from the kernel
        blurred.SetPixel (x,y, sf::Color(static_cast<int>(sum),static_cast<int>(sum),static_cast<int>(sum)));
      }
    }
    sf::Sprite    sprite (blurred);
    sprite.SetPosition (p->position);
    sprite.Resize(source->GetWidth()*p->scalefactor, source->GetHeight()*p->scalefactor);	//# use static value
    wnd.Draw (sprite);
    */
  }
protected:
	sf::PostFX  m_fx;  
};

#endif
