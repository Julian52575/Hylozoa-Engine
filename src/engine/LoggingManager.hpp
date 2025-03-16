#ifndef ENGINE_LOGGINGMANAGER_HPP
    #define ENGINE_LOGGINGMANAGER_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Engine {
    class LoggingManager {
        public:
            LoggingManager()
            {
                this->getUniqueFileName(this->_filename);
                this->_file.open(this->_filename, std::ios::out);
                if (!this->_file) {
                    throw std::runtime_error("Error on log constructor");
                }
            }
            ~LoggingManager()
            {
                this->_file.close();
            };
            friend LoggingManager& operator<<(LoggingManager& log, const std::string& msg)
            {
                log._file << msg;
                return log;
            }
            void endl()
            {
                this->_file << std::endl;
            }

        private:
            inline void getUniqueFileName(std::string& out)
            {
                time_t timestamp = time(&timestamp);
                struct tm datetime = *localtime(&timestamp);

                out = "log" + std::to_string(datetime.tm_mday)
                    + "-" + std::to_string(datetime.tm_mon)
                    + "_" + std::to_string(datetime.tm_hour)
                    + ":" + std::to_string(datetime.tm_min)
                    + ":" + std::to_string(datetime.tm_sec);
            }

        private:
            std::ofstream _file;
            std::string _filename;
    };
}  // Engine


#endif  // ENGINE_LOGGINGMANAGER_HPP
