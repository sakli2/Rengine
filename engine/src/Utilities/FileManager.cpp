#include "pch.h"
#include <Rengine/Utilities/FileManager.h>
namespace RENGINE 
{
    namespace FileManager 
    {
        FileReader::FileReader(const std::string& filePath)
        {
            m_fileManager.open(filePath);
        }
        
        FileReader::~FileReader()
        {
            m_fileManager.close();
        }

        void FileReader::open(const std::string& filePath)
        {
            m_fileManager.close();
            m_fileManager.open(filePath);
        }

        std::string FileReader::readLine()
        {
            std::string line;
            std::getline(m_fileManager,line);
            return line;
        }

        std::string FileReader::read()
        {
            std::string str;

            m_fileManager.seekg(0, std::ios::end);   
            str.reserve(m_fileManager.tellg());
            m_fileManager.seekg(0, std::ios::beg);

            str.assign((std::istreambuf_iterator<char>(m_fileManager)),
                        std::istreambuf_iterator<char>());
            return str;
        }

        void FileReader::skipLine()
        {
            std::string line;
            std::getline(m_fileManager,line);
        }

        void FileReader::close()
        {
            m_fileManager.close();
        }
    }
}