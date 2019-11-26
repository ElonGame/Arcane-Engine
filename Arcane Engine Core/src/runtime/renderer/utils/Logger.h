#pragma once

#include "Singleton.h"

#define LOG_FILE_DIR "logged_files\\"

#define ARCANE_WARN(...) arcane::Logger::getInstance().warn(__VA_ARGS__)
#define ARCANE_INFO(...) arcane::Logger::getInstance().info(__VA_ARGS__)
#define ARCANE_TRACE(...) arcane::Logger::getInstance().trace(__VA_ARGS__)
#define ARCANE_ERROR(...) arcane::Logger::getInstance().error(__VA_ARGS__)
#define ARCANE_CRITICAL(...) arcane::Logger::getInstance().critical(__VA_ARGS__)

namespace arcane {

	class Logger : public Singleton {
	private:
		Logger();

	public:
		static Logger& getInstance();

		template<typename T>
		inline void warn(const T& msg) { log->warn(msg); }
		template<typename T>
		inline void info(const T& msg) { log->info(msg); }
		template<typename T>
		inline void trace(const T& msg) { log->trace(msg); }
		template<typename T>
		inline void error(const T& msg) { log->error(msg); }
		template<typename T>
		inline void critical(const T& msg) { log->critical(msg); }

	private:
		std::shared_ptr<spdlog::logger> log;

		/**
		* Logs a message
		*
		* @param priority The level of priority that the message is given (higher = more important)
		* @param module The module the message is assosciated with
		* @param message The message that will be logged
		*/
		//void logMessage(const int &priority, const std::string &module, const std::string &message);

		///**
		//* Clears out the contents all of the different files that have been assigned to
		//*/
		//void clearFileContents();

		///**
		//* Sets the output file
		//*
		//* @param filename The file that you want to set the logger to output to
		//*/
		//void setOutputFile(const std::string &filename);

		//enum {
		//	DEBUG, INFO, WARNING, ERROR
		//};
		//std::vector<std::string> filePaths;

		//std::ofstream filestream;
		//std::string file; // Default value set to: "logged_files/log.txt"
	};
}
