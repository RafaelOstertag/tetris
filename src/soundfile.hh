#ifndef __SOUNDFILE_HH
#define __SOUNDFILE_HH

#include "sound.hh"

#include <string>

class SoundFile : public Sound {
  public:
    SoundFile(const std::string& filename);
    virtual ~SoundFile();

    SoundFile(const SoundFile&) = delete;
    SoundFile& operator=(const SoundFile&) = delete;

    SoundFile(SoundFile&& o);
    SoundFile& operator=(SoundFile&& o);

    virtual Mix_Chunk* getMixChunk() const { return chunk; }

  private:
    Mix_Chunk* chunk;

    void destroyChunk();
};

#endif
