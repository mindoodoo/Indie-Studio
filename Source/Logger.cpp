//
// Created by mindoo on 26.05.22.
//

#include "Logger.hpp"

Logger::Logger(const std::string &sectionName, bool standardOutput)
        : _sectionName(sectionName), _standardOutput(standardOutput) {}

void Logger::log(std::string msg) const
{
    if (this->_standardOutput)
        std::cout << "\033[1;33m" << this->_sectionName << ": " << "\033[0m" << msg << std::endl;
    else
        std::cerr << "\033[1;33m" << this->_sectionName << ": " << "\033[0m" << msg << std::endl;
}

const std::string &Logger::getSectionName() const {
    return _sectionName;
}

void Logger::setSectionName(const std::string &sectionName) {
    _sectionName = sectionName;
}
