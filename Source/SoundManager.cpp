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
    loadMusic("./audio_assets/Music");
    this->_currentSongPlaying = -1;
    this->_musicPaused = false;
    this->_songTimePlayed = 0.0f;
    this->_shuffleEnabled = false;
}

RL::SoundManager::~SoundManager()
{
    for (std::size_t i = 0; i < this->_songs.size(); ++i) {
        UnloadMusicStream(this->_songs[i]._song);
    }

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
    if (dp == NULL) {
        std::cout << "Error(" << errno << ") opening " << folderPath << std::endl;
    }

    while ((dirp = readdir( dp ))) {
        filepath = folderPath + "/" + dirp->d_name;
        songName = dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it 
        if (stat( filepath.c_str(), &filestat )) continue;
        if (S_ISDIR( filestat.st_mode ))         continue;

         // Endeavor to read a single number from the file and display it
        thisSong._song = LoadMusicStream(filepath.c_str());
        std::cout << filepath.erase(filepath.find_last_of("."), std::string::npos) << std::endl;

        thisSong._name = songName.erase(songName.find_last_of("."), std::string::npos);

        this->_songs.push_back(thisSong);
    }

    closedir( dp );
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

    std::cout << "IM TRYING TO ENTER WHILE LOOP TO SHUFFLE !!!" << std::endl;

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
    if (this->_playedSongs.size() == this->_songs.size()) {
        std::cout << "IVE PLAYED ALL SONGS OF THE REPERTOIRE, GONNA CLEAR AND REPLAY ALL" << std::endl;
        this->_playedSongs.clear();
    }

}

void RL::SoundManager::playSpecificMusic(std::string songName)
{
    std::cout << "Im Gonna play a specific MUSIC!!" << std::endl;
    if (this->_currentSongPlaying != -1)
        StopMusicStream(this->_songs[_currentSongPlaying]._song);

    for (std::size_t i = 0; i < this->_songs.size(); ++i) {
        if (this->_songs[i]._name == songName) {
            std::cout << "Im playing this song : " << this->_songs[i]._name << std::endl;
            PlayMusicStream(this->_songs[i]._song);
            this->_currentSongPlaying = i;
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

