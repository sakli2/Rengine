#pragma once
#include <pch.h>

namespace RENGINE
{
    namespace FileManager {
        
        class FileWriter
        {

        };

        class FileReader
        {
        public:
            FileReader(const std::string& filePath);
            ~FileReader();
            void open(const std::string& filePath);
            void close();
            std::string read();
            std::string readLine();
            void skipLine();
        private:
            std::ifstream m_fileManager;
            
        };
    }
}