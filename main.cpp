#include <iostream>
#include <thread>
#include <atomic>
#include "logger.h"
#include "ThreadQueue.h"

struct LogMessage {
    std::string text;
    LevelLog level;
};

ThreadQueue<LogMessage> queue;
std::atomic<bool> running(true);

void loggerThread(Logger& logger) {
    while (running) {
        LogMessage msg = queue.pop();
        if (!msg.text.empty()) {
            logger.Log(msg.text, msg.level);
        }
    }
}

LevelLog parseLevel(const std::string& str) {
    if (str == "ERROR") return LevelLog::ERROR;
    if (str == "WARNING") return LevelLog::WARNING;
    return LevelLog::INFO;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./ThreadQueue <logfile> <default_level>\n"
        		  << "Arguments:\n"
        		  << "	<logfile> Path to the log file.\n"
        		  << "	<default_level> Importance level of the message\n";
        return 1;
    }

    std::string filename = argv[1];
    LevelLog defaultLevel = parseLevel(argv[2]);
	try{
    	Logger Logger(filename, defaultLevel);
    	std::thread worker(loggerThread, std::ref(Logger));
	
    	std::string input;
    	while (true) {
        	std::cout << "Enter message (or 'exit'): ";
        	std::getline(std::cin, input);
        	if (input == "exit") break;
	
        	std::cout << "Enter level (INFO/WARNING/ERROR) or leave blank: ";
        	std::string levelStr;
        	std::getline(std::cin, levelStr);
	
        	LevelLog level = levelStr.empty() ? defaultLevel : parseLevel(levelStr);
        	queue.push({input, level});
    	}
	
    	running = false;
    	queue.push({"", defaultLevel});
    	worker.join();
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
       }
    return 0;
}


