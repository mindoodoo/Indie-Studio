/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>
#include <chrono>

class Timer {
    public:
        Timer() {};
        ~Timer() {};
        void startTimer() {
            _pauseTime = 0;
            _bombTime = 0;
            _start = std::chrono::system_clock::now();
        };

        float returnTime() {
            _currentTime = std::chrono::system_clock::now();
            std::chrono::duration<float> diff = _currentTime - _start;
            // std::chrono::duration<float> diff = std::chrono::duration_cast<std::chrono::seconds>(_currentTime - _start);

            float elapsedTime = diff.count() - _pauseTime;

            return elapsedTime;
        };
        float returnBombTime() {
            _currentTime = std::chrono::system_clock::now();
            std::chrono::duration<float> diff = _currentTime - _start;
            // std::chrono::duration<float> diff = std::chrono::duration_cast<std::chrono::seconds>(_currentTime - _start);
            float elapsedTime = diff.count() - _pauseTime - _bombTime;
            return elapsedTime;
        };

        void setBombtime(float time) {
            _bombTime = time;
        };

        void restartTimer() {
            _pauseTime = 0;
            _bombTime = 0;
            _start = std::chrono::system_clock::now();
        };

        void startPause() {
            _pauseStart = std::chrono::system_clock::now();
        };
        void stopPause() {
            _pauseEnd = std::chrono::system_clock::now();
            std::chrono::duration<float> diff = _pauseEnd - _pauseStart;
            _pauseTime += diff.count();
        };

    private:
        std::chrono::system_clock::time_point _start;
        std::chrono::system_clock::time_point _currentTime;
        std::chrono::system_clock::time_point _pauseStart;
        std::chrono::system_clock::time_point _pauseEnd;
        float _pauseTime;
        float _bombTime;
};

#endif /* !TIMER_HPP_ */