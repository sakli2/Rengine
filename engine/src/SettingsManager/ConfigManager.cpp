#include <Rengine/SettingsManager/ConfigManager.h>
#include <Rengine/Utilities/FileManager.h>
#include <Rengine/Utilities/LOG.h>

namespace RENGINE 
{
    void ConfigManager::loadConfig(const std::string& filePath) 
    {
        if(s_filePath() == filePath)
            return;

        std::get<floatHolder>(s_Configs()).clear();
        std::get<stringHolder>(s_Configs()).clear();

        s_filePath() = filePath;
        FileManager::FileReader fileM(filePath);
        std::string text = fileM.read();

        while(text.size() > 0) {
            auto begin = text.find_first_of("<[");
            auto end = text.find_first_of("]>");
            std::string inside_name = text.substr(begin + 2, end - begin - 2);
            text = text.substr(end + 2, text.size() - end - 2);
            std::string title =  getBracketInside(inside_name);

            begin = text.find_first_of("{");
            end = text.find_first_of("}");
            std::string before_bracket = text.substr(0, begin);
            for (auto& ch : before_bracket)
            {
                if(ch != '\n' && ch != ' ') {
                    throw_error("Invalid syntax, missing bracket after " + Utilities::quotate(title + before_bracket));
                    break;
                }
            }
            if(begin == std::string::npos || end == std::string::npos)
                throw_error("Config file " + Utilities::quotate(s_filePath()) + " has missmatched brackets on resource " + Utilities::quotate(title));
            std::string inside_bracket = text.substr(begin + 1, end - begin - 1);
            text = text.substr(end + 1, text.size() - end - 1);

            std::string line;
            size_t line_end = inside_bracket.find_first_of("\n");;
            while(line_end != std::string::npos)
            {
                line = inside_bracket.substr(0, line_end);
                inside_bracket = inside_bracket.substr(line_end + 1, inside_bracket.size() - line_end - 1);

                auto equal_pos = line.find("=");
                if(equal_pos == std::string::npos)
                {
                    for (auto& ch : line)
                    {
                        if(ch != ' ')
                        {
                            throw_error("Invalid syntax " + Utilities::quotate(line));
                            break;
                        }
                    }
                    line_end = inside_bracket.find_first_of("\n");
                    continue;
                }
                std::string var_string = line.substr(0, equal_pos);
                std::string value_string = line.substr(equal_pos + 1, line.size() - equal_pos - 1);
                

                auto var_bracket_start_pos = var_string.find_first_of("[");
                auto var_bracket_end_pos = var_string.find_last_of("]");
                
                if(var_bracket_end_pos == std::string::npos || var_bracket_start_pos == std::string::npos)
                    throw_error("Missmatched brackets[] left side in " + Utilities::quotate(line));

                std::string var_before = var_string.substr(0, var_bracket_start_pos);
                std::string var_after = var_string.substr(var_bracket_end_pos + 1, var_string.size() - var_bracket_end_pos - 1);
                
                for (auto& ch : var_before)
                {
                    if(ch != ' ')
                    {
                        throw_error("Invalid syntax " + Utilities::quotate(line));
                        break;
                    }
                }
                for (auto& ch : var_after)
                {
                    if(ch != ' ')
                    {
                        throw_error("Invalid syntax " + Utilities::quotate(line));
                        break;
                    }
                }
                std::string var_name = var_string.substr(var_bracket_start_pos + 1, var_bracket_end_pos - var_bracket_start_pos - 1);
                std::string var_title = getBracketInside(var_name);
                line_end = inside_bracket.find_first_of("\n");
                

                //check value
                value_string = value_string.substr(value_string.find_first_not_of(" "), value_string.find_last_not_of(" "));
                if((value_string.at(0) == '\'' && value_string.at(value_string.size() - 1) == '\'') ||
                (value_string.at(0) == '\"' && value_string.at(value_string.size() - 1) == '\"'))
                {
                    //is string
                    std::string value = value_string.substr(1, value_string.size() - 2);
                    std::get<stringHolder>(s_Configs())[title][var_title] = value;
                }
                else
                {
                    //is float
                    try{
                        float value = std::stof(value_string);
                        std::get<floatHolder>(s_Configs())[title][var_title] = value;
                    }
                    catch(std::invalid_argument error)
                    {
                        throw_error("invalid value type" + Utilities::quotate(line));
                    }
                }
            } 
        }

    }

    std::string ConfigManager::getBracketInside(const std::string& inside)
    {
        std::array<std::string, 2> quotations = {"\'", "\""};
        for (const std::string& character : quotations)
        {
           auto name_begin = inside.find_first_of(character);
           auto name_end = inside.find_last_of(character);
           if(name_begin != std::string::npos && name_end != std::string::npos && name_begin != name_end)
                return inside.substr(name_begin + 1, name_end - name_begin - 1);
        }
        throw_error("Config file " + Utilities::quotate(s_filePath()) + " has missmatched quotations on " + Utilities::quotate(inside));
        return "";
    }
}