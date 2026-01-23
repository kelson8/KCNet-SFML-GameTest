#include "defines.h"
#include "util/ini_handler.h"

Defines::Defines()
{
	IniHandler iniHandler;
	pewSound = iniHandler.GetValue("Sounds", "PewSound");
	popSound = iniHandler.GetValue("Sounds", "PopSound");
	winSound = iniHandler.GetValue("Sounds", "WinSound");

	shipHitSound = iniHandler.GetValue("Sounds", "ShipHitSound");
	enemyHitSound = iniHandler.GetValue("Sounds", "EnemyHitSound");

	musicSound = iniHandler.GetValue("Sounds", "MusicFile");
	musicEnabled = iniHandler.GetBool("SoundToggles", "MusicEnabled");
	soundEffectsEnabled = iniHandler.GetValue("SoundToggles", "SoundEffectsEnabled");
}

const std::string Defines::loggerPrefix = "KCNet-Game";

const std::string Defines::logFileName = "game.log";

const std::string Defines::gameName = "KCNet SFML GameTest";

const char* Defines::iniFile = "game-settings.ini";