#pragma once

#include <raylib.h>

// Simple audio for the game.
// Loads every sound once, plays it with small helper functions, and unloads
// everything in the destructor. If an audio file is missing, that sound simply
// stays silent and the game keeps running.
class Audio {
    public:
    Audio();
    ~Audio();

    // call once after InitAudioDevice()
    void Init();
    // call every frame (keeps the background music stream alive)
    void Update();

    void PlayMoveSound();
    void PlayRotateSound();
    void PlaySoftDropSound();
    void PlayHardDropSound();
    void PlayLockSound();
    void PlayLineClearSound();
    void PlayLevelUpSound();
    void PlayGameOverSound();
    void PlayRestartSound();

    void ToggleMusic();
    void ToggleSounds();
    void PauseMusic();
    void ResumeMusic();

    bool MusicEnabled() const { return musicEnabled; }
    bool SoundsEnabled() const { return soundsEnabled; }

    private:
    Sound moveSound = {};
    Sound rotateSound = {};
    Sound softDropSound = {};
    Sound hardDropSound = {};
    Sound lockSound = {};
    Sound lineClearSound = {};
    Sound levelUpSound = {};
    Sound gameOverSound = {};
    Sound restartSound = {};
    Music music = {};

    bool musicEnabled = true;
    bool soundsEnabled = true;
};
