/*
 *  emitter.h
 *  corengine
 *
 *  Created by Daniel Kagemann on 14.09.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */
#ifndef emitter_h_
#define emitter_h_

#ifdef COREENGINE
  #define OUTPUT      printf
#else
  #define OUTPUT      //
#endif


#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "../particle.h"
#include "../sharedimage.h"
#include "../actions/actionbase.h"
#include "../initializers/initbase.h"
#include "../filter/filterbase.h"

namespace coresystem
{
  class Scene {
  public:
    enum CREATORMODE {
      CreateNothing = 0,
    	CreateAll,
      CreatePulse
    };

    std::vector<actionbase*>  actions;
    std::vector<initbase*>    initializers;
    std::vector<filterbase*>  filter;
    float                     elapsetime;

    //# not for all scenes
    int                       numOfObjects;
    float                     numTimerate;
    CREATORMODE               numMode;

    Scene ()
    {
      elapsetime = 0.f;
      numOfObjects = 0;
      numMode = CreateNothing;
      numTimerate = 0.f;
    }

    Scene (float t)
    {
      elapsetime = t;
      numOfObjects = 0;
      numMode = CreateNothing;
      numTimerate = 0.f;
    }
  };

  class emitter {
  public:
    emitter();
    emitter(const char* lpFile);
    virtual ~emitter();
    bool setnumber ();
    void init ();

    void render (sf::RenderWindow& wnd);

    void addAction (actionbase* a);
    
    void addFilter (filterbase* flt);

    void addInitializer (initbase* i, int scene_id=-1);

    std::vector<particle*>& getParticles ();

    static std::vector<std::string> tokenizer (std::string line, std::string sep);

		bool isInitialized ();

    void removeDeadParticles ();

    sharedimage&  getResource ();

  private: 
    void handleinitializers (particle* p);
    void handleactions      (int pidx);
    void creator            (bool initial=false);

    void removeParticles ();

    void removeScene        ();

  protected:
    std::vector<particle*>            m_particle;
    int           			              m_newobjects;
    sf::Clock                         m_timer;
    float                             m_timerate;
    std::vector<Scene*>               m_scenes;
    bool                              m_initialized;
    sf::Clock                         m_scenetimer;

    sharedimage                       m_resourcehandler;
  };
}

#endif


