#pragma once
#include <vector>
#include <SFML/Audio.hpp>

class AudioPool {
 private:
  std::vector<sf::Music*> mpool;
  std::vector<sf::Sound*> spool;
 public:
  unsigned int addMusic(char *path);
  unsigned int addSound(char *path);
  sf::Music* getMusic(int id);
  sf::Sound* getSound(int id);
  void removeMusic(int id);
  void removeSound(int id);
  ~AudioPool();
};
