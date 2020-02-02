#include "Audio.hpp"
#include "core.h"

#include "SDL_mixer.h"

using namespace Shiro;
using namespace std;

Music::Music() : volume(0), data(nullptr) {}

Music::~Music() {
    if(data) {
        Mix_FreeMusic(data);
    }
}

bool Music::load(string filenameNoExt) {
    data = nullptr;
    volume = MIX_MAX_VOLUME;

    string path = filenameNoExt + ".ogg";
    data = Mix_LoadMUS(path.c_str());
    if(data) {
        return true;
    }

    path = filenameNoExt + ".wav";
    data = Mix_LoadMUS(path.c_str());

    return data != nullptr;
}

bool Music::play(coreState* cs) {
    if (!data) {
        return false;
    }

    Mix_VolumeMusic((volume * ((cs->mus_volume * cs->master_volume) / 100)) / MIX_MAX_VOLUME);
    Mix_PlayMusic(data, -1);

    return true;
}

Sfx::Sfx() : volume(0), data(nullptr) {}

Sfx::~Sfx() {
    if (data) {
        Mix_FreeChunk(data);
    }
}

bool Sfx::load(string filenameNoExt) {
    data = nullptr;
    volume = MIX_MAX_VOLUME;

    string path = filenameNoExt + ".wav";
    data = Mix_LoadWAV(path.c_str());
    filename = path;

    return data != nullptr;
}

bool Sfx::play() {
    if(!data) {
        return false;
    }

    // Mix_VolumeChunk(data, printf(((float)(nz->settings->sfx_volume) / 100.0) * 128.0));
    Mix_VolumeChunk(data, volume);
    if(Mix_PlayChannel(-1, data, 0) < 0) {
        printf("Mix_PlayChannel() error: %s\n", Mix_GetError());
    }

    return true;
}