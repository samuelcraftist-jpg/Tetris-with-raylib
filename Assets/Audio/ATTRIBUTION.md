# Audio Assets Attribution

All audio files in this folder are CC0 / public domain and may be used freely,
including in commercial games, with no attribution required. Credits below are
given voluntarily.

## Sound effects (.wav)

Files: move.wav, rotate.wav, soft_drop.wav, hard_drop.wav, lock.wav,
line_clear.wav, level_up.wav, game_over.wav, restart.wav

- Source: OpenGameArt.org — "IgnisForge Free SFX Sampler - 43 Synthesized Retro Sound Effects"
- Author: IgnisForge
- License: CC0 (public domain)
- Source URL: https://opengameart.org/content/ignisforge-free-sfx-sampler-43-synthesized-retro-sound-effects
- Author page: https://ignisforge.itch.io
- Note: Credit "IgnisForge" with a link to https://ignisforge.itch.io is
  appreciated but not required (per the asset's CC0 terms).
- These were taken from the sampler pack `ignisforge-oga-sampler-cc0.zip`
  (1.2 Mb) and renamed to match the sound each one plays in-game.

## Background music (.mp3)

File: music.mp3

- Source: OpenGameArt.org — "Puzzled"
- Author: iamoneabe
- License: CC0 (public domain)
- Source URL: https://opengameart.org/content/puzzled-0
- Note: "Happy happy joy joy something something.. Longplay D# Major 56BPM"

## Notes

- raylib loads `music.mp3` as a streaming music file. If you replace it with a
  different file, keep the filename `music.mp3` (or update the path in
  `audio.cpp`).
- All sounds are loaded once at startup and unloaded when the game exits
  (`Audio::~Audio()`), per raylib's audio cleanup requirements.
- If any audio file is missing, the game still runs silently for that sound
  (a console message reports which file is missing).