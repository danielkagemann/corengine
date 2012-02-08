#ifndef measuretime_h_
#define measuretime_h_

#include <time.h>
#include <string.h>   //# linux requirement

#ifndef TRACE
   #define TRACE printf
#endif

//# ---- inline implementation of mtime ----
//# usage of mtime
//# create mtime object with or without functionname in the context you want
//# to measure. the destructor automatically generates the traceoutput
class mtime {
public:
  //# constructor with functionname
  mtime (const char* lpszFunction)
  {Construct(lpszFunction);}
  
  //# default constructor without functionname
  mtime ()
  {Construct(NULL);}

  //# destructor with auto trace
  ~mtime ()
  {
    double  duration = (double)(clock() - m_start) / CLOCKS_PER_SEC;

    TRACE ("(%s)=%.04f sec\n", m_function, duration);
  }

protected:
  //# helper method for different constructors
  void Construct (const char* lpszFunction)
  {
    if (lpszFunction == NULL) {
      strcpy (m_function, "");
    }
    else {
      strcpy (m_function, lpszFunction);
    }
    m_start=clock();
  }
  
protected:
  clock_t     m_start;
  char        m_function[300];
};

#endif
