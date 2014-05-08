#include "Util.h"
#include "State.h"
void Log(std::string LogMessage)
{
	filelog.open(LOG_FILE, std::ios::out | std::ios::app);
	if(filelog.is_open())
	{
		filelog << GAME_NAME + std::string(": ") + LogMessage + std::string(".\n");
	}
	filelog.close();
}