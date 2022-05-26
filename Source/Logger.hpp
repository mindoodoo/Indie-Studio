//
// Created by mindoo on 26.05.22.
//

#ifndef BOMBERMAN_LOGGER_HPP
#define BOMBERMAN_LOGGER_HPP

#include <string>
#include <iostream>

class Logger {
public:
    Logger(const std::string &sectionName, bool standardOutput = true);

    void log(std::string msg) const;

private:
    std::string _sectionName;
    bool _standardOutput;
};


#endif //BOMBERMAN_LOGGER_HPP
