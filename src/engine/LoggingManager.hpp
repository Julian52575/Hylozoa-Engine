#ifndef ENGINE_LOGGINGMANAGER_HPP
    #define ENGINE_LOGGINGMANAGER_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>

namespace Engine {
    class LoggingManager {
        public:
            LoggingManager()
            {
                if (!std::filesystem::is_directory("logs") || !std::filesystem::exists("logs")) {
                    std::filesystem::create_directory("logs");
                }
                this->getUniqueFileName(this->_filename);
                this->_filename = "logs/" + this->_filename;
                this->_file.open(this->_filename, std::ios::out);
                if (!this->_file) {
                    throw std::runtime_error("Error on log constructor");
                }
                this->_file << "Created" << std::endl;
            }
            ~LoggingManager()
            {
                if (this->_buffer.size() > 0) {
                    this->_file << this->_buffer;
                }
                this->_file << std::endl;
                this->_file.close();
            };
            friend LoggingManager& operator<<(LoggingManager& log, const std::string& msg)
            {
                log._buffer = log._buffer + msg;
                if (msg.find("\n") != std::string::npos) {
                    log._file << log._buffer << std::endl;
                    log._buffer.clear();
                }
                return log;
            }
            void flush()
            {
                this->_file << this->_buffer << std::endl;
                this->_buffer.clear();
            }

        private:
            inline void getUniqueFileName(std::string& out)
            {
                time_t timestamp = time(&timestamp);
                struct tm datetime = *localtime(&timestamp);

                out = std::to_string(datetime.tm_mday)
                    + "-" + std::to_string(datetime.tm_mon)
                    + "_" + std::to_string(datetime.tm_hour)
                    + ":" + std::to_string(datetime.tm_min)
                    + ":" + std::to_string(datetime.tm_sec)
                    + ".txt";
            }

        private:
            std::ofstream _file;
            std::string _filename;
            std::string _buffer;
    };
}  // Engine


#endif  // ENGINE_LOGGINGMANAGER_HPP
