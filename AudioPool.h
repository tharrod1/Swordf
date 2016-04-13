#pragma once
#include <vector>
#include <SFML/Audio.hpp>

class AudioPool {
 private:
  std::vector<sf::Music*> mpool;
  std::vector<sf::Sound*> spool;
 public:
  unsigned int addMusic(char *path){
    sf::Music mus;
    if(!mus.openFromFile(path)) return -1;
    mpool.push_back(&mus);
    return mpool.size();
  }

  unsigned int addSound(char *path){
    sf::SoundBuffer buf;
    sf::Sound snd;
    
    if(!buf.loadFromFile(path)) return -1;

    snd.setBuffer(buf);
    spool.push_back(&snd);
    return spool.size();
  }

  sf::Music* getMusic(int id){
    return mpool[id];
  }
  
  sf::Sound* getSound(int id){
    return spool[id];
  }
  
  void removeMusic(int id){
    mpool.erase(mpool.begin()+id);
  }

  void removeSound(int id){
    spool.erase(spool.begin()+id);
  }

  ~AudioPool(){
    mpool.clear();
    spool.clear();
  }
};
