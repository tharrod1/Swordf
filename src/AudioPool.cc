#include <vector>
#include <SFML/Audio.hpp>
#include "AudioPool.h"

unsigned int AudioPool::addMusic(char *path){
  sf::Music mus;
  if(!mus.openFromFile(path)) return -1;
  mpool.push_back(&mus);
  return mpool.size();
}

unsigned int AudioPool::addSound(char *path){
  sf::SoundBuffer buf;
  sf::Sound snd;
    
  if(!buf.loadFromFile(path)) return -1;

  snd.setBuffer(buf);
  spool.push_back(&snd);
  return spool.size();
}

AudioPool::~AudioPool(){
  unsigned int sizes = mpool.size();
  for(unsigned int i = 0; i < sizes; i++) removeMusic(i);
  sizes = spool.size();
  for(unsigned int i = 0; i < sizes; i++) removeSound(i);
}

sf::Music* AudioPool::getMusic(int id){
  return mpool[id];
}
  
sf::Sound* AudioPool::getSound(int id){
  return spool[id];
}
  
void AudioPool::removeMusic(int id){
  delete mpool[id];
  mpool.erase(mpool.begin()+id);
}

void AudioPool::removeSound(int id){
  delete spool[id];
  spool.erase(spool.begin()+id);
}
