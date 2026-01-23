#pragma once

#include <iostream>

#include <memory>
#include <optional>

// New for Simpleini https://github.com/brofield/simpleini
#include "SimpleIni.h"
//

class IniHandler
{
public:

	//static IniHandler& getInstance()
	//{
	//    static IniHandler instance;
	//    return instance;
	//}
	IniHandler();

	const char* GetValue(const std::string& section, const std::string& key);
	int GetInt(const std::string& section, const std::string& key);
	double GetDouble(const std::string& section, const std::string& key);
	bool GetBool(const std::string& section, const std::string& key);
	//std::optional<bool> GetBool(const std::string& section, const std::string& key);

	void SetBool(const std::string& section, const std::string& key, bool value, std::string comment, bool forceReplace);

private:
	// ~IniHandler(); // Optional deconstructor
	IniHandler(const IniHandler&) = delete;            // Prevent copy-construction
	IniHandler& operator=(const IniHandler&) = delete; // Prevent assignment

	// Ini file
	CSimpleIniA iniFile;
};
