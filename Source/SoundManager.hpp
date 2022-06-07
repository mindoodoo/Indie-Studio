/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** SoundManager
*/

#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <raylib.h>

typedef struct
    {
        Music _song;
        std::string _name;
    } musicFile_t;

typedef struct
    {
        Sound _soundEffect;
        std::string _name;
    } soundEffectFile_t;

namespace RL {

    class SoundManager {
        public:
            SoundManager();
            ~SoundManager();

            //getters
            std::vector<musicFile_t> getSongList();
            musicFile_t getSong(std::string);

            //loading methods
            void loadMusic(std::string folderPath);
            void loadAudioEffects(std::string folderPath);

            //update method to keep stream updated ! must be called at every frame
            void updateMusicStream();

            //playing methods
            void playRandomMusic();
            void playSpecificMusic(std::string songName);
            void playSpecificSoundFx(std::string EffectName);
            void pauseOrPlayMusic();

            void enableDisableShuffle();

        private:
            std::vector<musicFile_t> _songs;
            std::vector<int> _playedSongs;
            std::vector<soundEffectFile_t> _soundfx;
            int _currentSongPlaying;
            bool _musicPaused;
            float _songTimePlayed;
            bool _shuffleEnabled;
    };
}
