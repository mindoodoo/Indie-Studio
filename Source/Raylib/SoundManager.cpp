/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** SoundManager
*/

#include "SoundManager.hpp"

RL::SoundManager::SoundManager()
{
    InitAudioDevice();
    loadMusic("./Source/Assets/audio_assets/Music");
    loadAudioEffects("./Source/Assets/audio_assets/Effects");
    this->_currentSongPlaying = -1;
    this->_musicPaused = false;
    this->_songTimePlayed = 0.0f;
    this->_shuffleEnabled = false;
    this->_musicVolume = 0.1f;
    this->_soundEffectVolume = 0.1f;
}

RL::SoundManager::~SoundManager()
{
    for (std::size_t i = 0; i < this->_songs.size(); ++i) {
        UnloadMusicStream(this->_songs[i]._song);
    }

    for (std::size_t i = 0; i < this->_soundfx.size(); ++i) {
        UnloadSound(this->_soundfx[i]._soundEffect);
    }
    StopSoundMulti();

    CloseAudioDevice();    
}


void RL::SoundManager::loadMusic(std::string folderPath)
{
    std::ifstream fin;
    std::string  filepath;
    std::string songName;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    musicFile_t thisSong;

    dp = opendir( folderPath.c_str() );
    if (dp == NULL)
        std::cout << "Error(" << errno << ") opening " << folderPath << std::endl;

    while ((dirp = readdir( dp ))) {
        filepath = folderPath + "/" + dirp->d_name;
        songName = dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it 
        if (stat( filepath.c_str(), &filestat ))
            continue;
        if (S_ISDIR( filestat.st_mode ))
            continue;

        thisSong._song = LoadMusicStream(filepath.c_str());
        std::cout << filepath.erase(filepath.find_last_of("."), std::string::npos) << std::endl;

        thisSong._name = songName.erase(songName.find_last_of("."), std::string::npos);

        this->_songs.push_back(thisSong);
    }
    closedir(dp);
}

void RL::SoundManager::loadAudioEffects(std::string folderPath)
{
    std::ifstream fin;
    std::string  filepath;
    std::string EffectName;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    soundEffectFile_t thisEffect;

    dp = opendir( folderPath.c_str() );
    if (dp == NULL)
        std::cout << "Error(" << errno << ") opening " << folderPath << std::endl;

    while ((dirp = readdir( dp ))) {
        filepath = folderPath + "/" + dirp->d_name;
        EffectName = dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it 
        if (stat( filepath.c_str(), &filestat ))
            continue;
        if (S_ISDIR( filestat.st_mode ))
            continue;

        thisEffect._soundEffect = LoadSound(filepath.c_str());
        std::cout << filepath.erase(filepath.find_last_of("."), std::string::npos) << std::endl;

        thisEffect._name = EffectName.erase(EffectName.find_last_of("."), std::string::npos);

        this->_soundfx.push_back(thisEffect);
    }
    closedir(dp);
}

void RL::SoundManager::enableDisableShuffle()
{
    this->_shuffleEnabled = !_shuffleEnabled;
    if (_shuffleEnabled)
        std::cout << "Shuffle is now enabled" << std::endl;
    if (!_shuffleEnabled)
        std::cout << "Shuffle is now disabled" << std::endl;
}

void RL::SoundManager::updateMusicStream()
{
    if (this->_currentSongPlaying == -1) {
        if (!this->_shuffleEnabled)
            return;
        else
            playRandomMusic();
    }
    
    UpdateMusicStream(this->_songs[_currentSongPlaying]._song);
    this->_songTimePlayed = GetMusicTimePlayed(this->_songs[_currentSongPlaying]._song) /
    GetMusicTimeLength(this->_songs[_currentSongPlaying]._song) * 400;
    SetMusicVolume(this->_songs[_currentSongPlaying]._song, this->_musicVolume);
    if (this->_songTimePlayed > 399) {
        StopMusicStream(this->_songs[_currentSongPlaying]._song);
        this->_currentSongPlaying = -1;
    }
}

void RL::SoundManager::playRandomMusic()
{
    bool isAlreadyPlayed = true;

    std::srand(std::time(nullptr));
    int randomIndex = std::rand() % this->_songs.size();

    while (isAlreadyPlayed && this->_playedSongs.size() != 0) {
        for (std::size_t i = 0; i < this->_playedSongs.size(); ++i) {
            if (randomIndex == this->_playedSongs[i]) {
                randomIndex = std::rand() % this->_songs.size();
                isAlreadyPlayed = true;
            }
            else {
                isAlreadyPlayed = false;
            }
        }        
    }

    this->_playedSongs.push_back(randomIndex);
    playSpecificMusic(this->_songs[randomIndex]._name);
    this->_currentSongPlaying = randomIndex;
    if (this->_playedSongs.size() == this->_songs.size())
        this->_playedSongs.clear();
}

void RL::SoundManager::playSpecificMusic(std::string songName)
{
    if (this->_currentSongPlaying != -1)
        StopMusicStream(this->_songs[_currentSongPlaying]._song);

    for (std::size_t i = 0; i < this->_songs.size(); ++i) {
        if (this->_songs[i]._name == songName) {
            PlayMusicStream(this->_songs[i]._song);
            this->_currentSongPlaying = i;
            SetMusicVolume(this->_songs[_currentSongPlaying]._song, this->_musicVolume);
            return;
        }
    }
}

void RL::SoundManager::playSpecificSoundFx(std::string EffectName)
{
    // if (this->_currentSongPlaying != -1)
    //     StopMusicStream(this->_songs[_currentSongPlaying]._song);

    for (std::size_t i = 0; i < this->_soundfx.size(); ++i) {
        if (this->_soundfx[i]._name == EffectName) {
            SetSoundVolume(this->_soundfx[i]._soundEffect, this->_soundEffectVolume);
            PlaySoundMulti(this->_soundfx[i]._soundEffect);
            //this->_currentSongPlaying = i;
            return;
        }
    }
}

void RL::SoundManager::pauseOrPlayMusic()
{
    if (this->_currentSongPlaying != -1) {
        if (!this->_musicPaused) {
            PauseMusicStream(this->_songs[_currentSongPlaying]._song);
            this->_musicPaused = true;
            std::cout << "PAUSING " << this->_songs[_currentSongPlaying]._name << std::endl;
        }
        else {
            ResumeMusicStream(this->_songs[_currentSongPlaying]._song);
            this->_musicPaused = false;
            std::cout << "RESUMING " << this->_songs[_currentSongPlaying]._name << std::endl;
        }
    }
}

void RL::SoundManager::increaseMusicVolume()
{
    if (this->_musicVolume >= 1.0f)
        return;
    this->_musicVolume += 0.1f;
    SetMusicVolume(this->_songs[_currentSongPlaying]._song, this->_musicVolume);
    std::cout << "Music Volume: " << this->_musicVolume << std::endl;
}

void RL::SoundManager::decreaseMusicVolume()
{
    if (this->_musicVolume <= 0.0f)
        return;
    this->_musicVolume -= 0.1f;
    SetMusicVolume(this->_songs[_currentSongPlaying]._song, this->_musicVolume);
    std::cout << "Music Volume: " << this->_musicVolume << std::endl;
}

void RL::SoundManager::increaseSoundEffectVolume()
{
    if (this->_soundEffectVolume >= 1.0f)
        return;
    this->_soundEffectVolume += 0.1f;
    std::cout << "Sound Volume: " << this->_soundEffectVolume << std::endl;

}

void RL::SoundManager::decreaseSoundEffectVolume()
{
    if (this->_soundEffectVolume <= 0)
        return;
    this->_soundEffectVolume -= 0.1f;
    std::cout << "Sound Volume: " << this->_soundEffectVolume << std::endl;

}

//getters
std::vector<musicFile_t> RL::SoundManager::getSongList()
{
    return this->_songs;
}

musicFile_t RL::SoundManager::getSong(std::string songName)
{
    for (std::size_t i = 0; i < this->_songs.size(); ++i) {
        if (this->_songs[i]._name == songName) {
            return this->_songs[i];
        }
    }
    //add an special song in first place of the list to make sue we can play this song
    return this->_songs[0];    
}

float RL::SoundManager::getMusicVolume()
{
    return this->_musicVolume;
}

float RL::SoundManager::getSoundEffectVolume()
{
    return this->_soundEffectVolume;
}

void RL::SoundManager::muteGame()
{
    if (_soundEffectVolume == 0 || _musicVolume == 0) {
        _soundEffectVolume = 0.5f;
        _musicVolume = 0.5f;
    } else {
        _soundEffectVolume = 0;
        _musicVolume = 0;
    }
}