#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <ctime>

enum class LevelLog
{
	ERROR = 0,
	WARNING = 1,
	INFO = 2
};
class Logger
{
public:
	Logger(const std::string& filename, LevelLog level = LevelLog::INFO);
	~Logger();

	void Log(const std::string& massage, LevelLog level);
	void SetLevelLog(LevelLog level);
private:
	std::mutex logMutex;
	std::ofstream logfile;
	LevelLog currentLevel;

	std::string GetTimeCurrent();
	std::string LevelString(LevelLog level);

};

