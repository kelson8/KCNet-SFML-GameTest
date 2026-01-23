#include "ini_handler.h"

#include "defines.h"

#include <iostream>
#include <filesystem>
#include <stdexcept>  // For std::runtime_error

#include <fmt/core.h>

#include "logger.h"

// TODO Add a reload option for this ini handler, so the game doesn't have to be restarted.

IniHandler::IniHandler()
{
    SI_Error rc = iniFile.LoadFile(Defines::iniFile);

    // Load the INI file

    // Make sure rc is correct, assert test
    // assert(rc < 0);

    if (rc < 0)
    {
        fmt::println("Error: failed to load INI file {}! Error code: {}", Defines::iniFile, rc);
    }
    // else
    // {
    // fmt::println("Ini file {} loaded.", Config::GetIniFile().c_str());
    // }
}

/**
 * @brief Strip the quotes from the INI value.
 * @param str 
 * @return The ini value without quotes.
 */
std::string trimQuotes(const std::string& str) {
    if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.size() - 2);
    }
    return str;
}

//---------
// Public functions
//---------

/**
 * Get an ini key value, mostly for strings.
 *
 * @param section The section in the ini file to check.
 * @param key The key in the ini file to check
 * @return The value from the ini file if it exists.
 */
const char* IniHandler::GetValue(const std::string& section, const std::string& key)
{
    const char* value = iniFile.GetValue(section.c_str(), key.c_str());

    if (value == nullptr)
    {
        std::string errorText = fmt::format("Key '{}' not found in section '{}'", key, section);
        fmt::println("{}", errorText);
        //SPDLOG_ERROR(errorText);
        //spdlog::error(errorText);
        return nullptr; // Return nullptr if not found
    }

    // Convert to std::string for manipulation
    std::string valueStr(value);

    // Trim quotes from the value
    valueStr = trimQuotes(valueStr);

    return strdup(valueStr.c_str());
}

/**
 * @brief Get a int from the ini file.
 * 
 * @param section The section in the ini file to check.
 * @param key The key in the ini file to check
 * @return The int from the ini file if it exists.
 */
int IniHandler::GetInt(const std::string& section, const std::string& key)
{
    // This should be an int anyways, so I'll just static cast the value to int.
    int value = static_cast<int>(iniFile.GetDoubleValue(section.c_str(), key.c_str()));

    // Come up with a better way for this
    //if (value != 0)
    if (iniFile.GetValue(section.c_str(), key.c_str()) == nullptr)
    {
        fmt::println("Key '{}' not found in section '{}'", key, section);
    }

    return value;
}

/**
 * @brief Get a double from the ini file
 *
 * @param section The section in the ini file to check.
 * @param key The key in the ini file to check
 * @return The double from the ini file if it exists.
 */
double IniHandler::GetDouble(const std::string& section, const std::string& key)
{
    double value = iniFile.GetDoubleValue(section.c_str(), key.c_str());

    if (iniFile.GetValue(section.c_str(), key.c_str()) == nullptr)
    {
        fmt::println("Key '{}' not found in section '{}'. Returning NaN.\n", key, section);
        return std::numeric_limits<double>::quiet_NaN();
    }

    return value;
}

/**
 * @brief Get a boolean value in the ini
 *
 * @param section The section in the ini file to check.
 * @param key The key in the ini file to check
 * @return The boolean from the ini file if it exists.
 */
bool IniHandler::GetBool(const std::string &section, const std::string &key)
//std::optional<bool> IniHandler::GetBool(const std::string& section, const std::string& key)
{

    const char* value = iniFile.GetValue(section.c_str(), key.c_str());
    //if (value == nullptr)
    if (iniFile.GetValue(section.c_str(), key.c_str()) == nullptr)
    {
        fmt::println("Key '{}' not found in section '{}'.", key, section);
        // throw std::runtime_error("Key does not exist");
        return false;
    }

    bool boolValue = iniFile.GetBoolValue(section.c_str(), key.c_str());
    return boolValue;
}

/**
 * @brief Set an ini boolean
 * 
 * @param section The section in the ini file to set.
 * @param key The key in the ini file to set
 * @param comment The comment to set for the ini value
 * @param forceReplace If this forces the replacement of the value.
 * @param value 
 */
void IniHandler::SetBool(const std::string& section, const std::string& key, bool value, std::string comment, bool forceReplace)
{
    if (iniFile.GetValue(section.c_str(), key.c_str()) == nullptr)
    {
        fmt::println("Key '{}' not found in section '{}'.", key, section);
        return;
    }

    // https://stackoverflow.com/questions/43056169/writing-to-ini-file-simpleini-setvalue-not-doing-anything-despite-appearing
    SI_Error rc = iniFile.SetBoolValue(section.c_str(), key.c_str(), value, comment.c_str(), forceReplace);
    if (rc < 0)
    {
        fmt::println("Error, could not write boolean to ini file");
        return;
    }

    // Save the ini file.
    iniFile.SaveFile(Defines::iniFile);

    fmt::println("Ini file updated successfully.");
}
