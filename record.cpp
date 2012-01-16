#include "record.h"

Record::Record ()
{
  m_each_n_frame = 0;
  m_current_frame = 0;
  m_isRecording = false;
}

Record::~Record ()
{}

void Record::Start (int each)
{
  Stop ();
  m_each_n_frame = each;
  m_isRecording = true;
}

void Record::Stop ()
{
  //# iterate through images and save to disk
  //# delete the images
  char  filename[300];
  for (int i = static_cast<int> (m_images.size()) - 1; i >= 0; i--) {
    sprintf (filename, "records/record_%05d.jpg",i);
    m_images[i]->SaveToFile (filename);
    delete m_images[i];

    printf ("Saving %s...(%d remaining)\n", filename, i);
  }
  m_images.clear();
  m_isRecording=false;
}

void Record::Snapshot (sf::RenderWindow& wnd)
{
  if (m_isRecording==false) {
    return;
  }

  if (++m_current_frame >= m_each_n_frame) {
    sf::Image *pImg = new sf::Image();
    pImg->CopyScreen (wnd,sf::IntRect (0,0,640,480));
    m_images.push_back (pImg);
    m_current_frame=0;
  }
}

bool Record::IsRecording ()
{
  return m_isRecording;
}