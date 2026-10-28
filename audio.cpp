#include "audio.hpp"

#include <iostream>

using std::cout;
using std::endl;

Audio::Audio() {}

Audio::~Audio()
{
    // unload sounds that were actually loaded
    if (moveSound.frameCount > 0) UnloadSound(moveSound);
    if (rotateSound.frameCount > 0) UnloadSound(rotateSound);
    if (softDropSound.frameCount > 0) UnloadSound(softDropSound);
    if (hardDropSound.frameCount > 0) UnloadSound(hardDropSound);
    if (lockSound.frameCount > 0) UnloadSound(lockSound);
    if (lineClearSound.frameCount > 0) UnloadSound(lineClearSound);
    if (levelUpSound.frameCount > 0) UnloadSound(levelUpSound);
    if (gameOverSound.frameCount > 0) UnloadSound(gameOverSound);
    if (restartSound.frameCount > 0) UnloadSound(restartSound);

    if (music.frameCount > 0)
    {
        StopMusicStream(music);
        UnloadMusicStream(music);
    }
}

void Audio::Init()
{
    moveSound = LoadSound("Assets/Audio/move.wav");
    rotateSound = LoadSound("Assets/Audio/rotate.wav");
    softDropSound = LoadSound("Assets/Audio/soft_drop.wav");
    hardDropSound = LoadSound("Assets/Audio/hard_drop.wav");
    lockSound = LoadSound("Assets/Audio/lock.wav");
    lineClearSound = LoadSound("Assets/Audio/line_clear.wav");
    levelUpSound = LoadSound("Assets/Audio/level_up.wav");
    gameOverSound = LoadSound("Assets/Audio/game_over.wav");
    restartSound = LoadSound("Assets/Audio/restart.wav");

    music = LoadMusicStream("Assets/Audio/music.mp3");

    // sensible default volumes: music quieter than sound effects
    SetSoundVolume(moveSound, 0.7f);
    SetSoundVolume(rotateSound, 0.7f);
    SetSoundVolume(softDropSound, 0.6f);
    SetSoundVolume(hardDropSound, 0.7f);
    SetSoundVolume(lockSound, 0.8f);
    SetSoundVolume(lineClearSound, 0.8f);
    SetSoundVolume(levelUpSound, 0.8f);
    SetSoundVolume(gameOverSound, 0.8f);
    SetSoundVolume(restartSound, 0.7f);
    SetMusicVolume(music, 0.25f);

    // report missing files so the developer knows why a sound is silent
    if (moveSound.frameCount == 0) cout << "Audio: missing Assets/Audio/move.wav" << endl;
    if (rotateSound.frameCount == 0) cout << "Audio: missing Assets/Audio/rotate.wav" << endl;
    if (softDropSound.frameCount == 0) cout << "Audio: missing Assets/Audio/soft_drop.wav" << endl;
    if (hardDropSound.frameCount == 0) cout << "Audio: missing Assets/Audio/hard_drop.wav" << endl;
    if (lockSound.frameCount == 0) cout << "Audio: missing Assets/Audio/lock.wav" << endl;
    if (lineClearSound.frameCount == 0) cout << "Audio: missing Assets/Audio/line_clear.wav" << endl;
    if (levelUpSound.frameCount == 0) cout << "Audio: missing Assets/Audio/level_up.wav" << endl;
    if (gameOverSound.frameCount == 0) cout << "Audio: missing Assets/Audio/game_over.wav" << endl;
    if (restartSound.frameCount == 0) cout << "Audio: missing Assets/Audio/restart.wav" << endl;
    if (music.frameCount == 0) cout << "Audio: missing Assets/Audio/music.ogg" << endl;

    // start the looping background music if we have it
    if (music.frameCount > 0)
    {
        PlayMusicStream(music);
    }
}

void Audio::Update()
{
    if (music.frameCount > 0)
    {
        UpdateMusicStream(music);
    }
}

void Audio::PlayMoveSound()
{
    if (soundsEnabled && moveSound.frameCount > 0)
    {
        PlaySound(moveSound);
    }
}

void Audio::PlayRotateSound()
{
    if (soundsEnabled && rotateSound.frameCount > 0)
    {
        PlaySound(rotateSound);
    }
}

void Audio::PlaySoftDropSound()
{
    if (soundsEnabled && softDropSound.frameCount > 0)
    {
        PlaySound(softDropSound);
    }
}

void Audio::PlayHardDropSound()
{
    if (soundsEnabled && hardDropSound.frameCount > 0)
    {
        PlaySound(hardDropSound);
    }
}

void Audio::PlayLockSound()
{
    if (soundsEnabled && lockSound.frameCount > 0)
    {
        PlaySound(lockSound);
    }
}

void Audio::PlayLineClearSound()
{
    if (soundsEnabled && lineClearSound.frameCount > 0)
    {
        PlaySound(lineClearSound);
    }
}

void Audio::PlayLevelUpSound()
{
    if (soundsEnabled && levelUpSound.frameCount > 0)
    {
        PlaySound(levelUpSound);
    }
}

void Audio::PlayGameOverSound()
{
    if (soundsEnabled && gameOverSound.frameCount > 0)
    {
        PlaySound(gameOverSound);
    }
}

void Audio::PlayRestartSound()
{
    if (soundsEnabled && restartSound.frameCount > 0)
    {
        PlaySound(restartSound);
    }
}

void Audio::ToggleMusic()
{
    musicEnabled = !musicEnabled;
    if (music.frameCount == 0)
    {
        return;
    }
    if (musicEnabled)
    {
        ResumeMusicStream(music);
    }
    else
    {
        PauseMusicStream(music);
    }
}

void Audio::ToggleSounds()
{
    soundsEnabled = !soundsEnabled;
}

void Audio::PauseMusic()
{
    if (musicEnabled && music.frameCount > 0)
    {
        PauseMusicStream(music);
    }
}

void Audio::ResumeMusic()
{
    if (musicEnabled && music.frameCount > 0)
    {
        PlayMusicStream(music);
        ResumeMusicStream(music);
    }
}
