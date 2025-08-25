#include "logger.h"



Logger::Logger(const std::string& filename, LevelLog defaultLevel) : currentLevel(defaultLevel)
{
	logfile.open(filename, std::ios::app);
}

Logger::~Logger()
{
	if (logfile.is_open())
	{
		logfile.close();
	}
}

void Logger::Log(const std::string& message, LevelLog level)
{
	if (level > currentLevel) return;

	std::lock_guard<std::mutex> lock(logMutex);
	logfile << " " << GetTimeCurrent() << " " << "[" << LevelString(level) << "] " << message << "\n";
}

void Logger::SetLevelLog(LevelLog level)
{
	currentLevel = level;
}

std::string Logger::GetTimeCurrent()
{
	std::time_t now = std::time(nullptr);
	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return buffer;
}

std::string Logger::LevelString(LevelLog level)
{
	switch (level)
	{
	case LevelLog::ERROR: return "ERROR";
	case LevelLog::WARNING: return "WARNING";
	case LevelLog::INFO: return "INFO";

	}
}

