#include "pch.h"
#include "Logger.h"

namespace arcane {

	Logger::Logger()
	{
		std::string directory = std::filesystem::current_path().string(); // Get the current directory that the project is in 
		directory += "\\" + std::string(LOG_FILE_DIR); // Add the directory that we want to create the log files in 
		if (!std::filesystem::is_directory(directory))
		{
			std::filesystem::create_directory(directory); // Create the log directory
		}

		std::vector<spdlog::sink_ptr> loggerSinks // Create logger sinks
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(LOG_FILE_DIR) + "log"), // File logger sink
			std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>() // Console logger sink
		};

		log = std::make_shared<spdlog::logger>("Arcane Logs", std::begin(loggerSinks), std::end(loggerSinks)); // Create the logger with multiple sinks	
		log->set_level(spdlog::level::trace); // Set logger level
		log->set_pattern("%^[%n] [%l] [%d-%m-%Y %T]: %v %$"); // Set the logger pattern

		spdlog::register_logger(log); // Register the logger that we are using
	}

	Logger& Logger::getInstance() {
		static Logger logger;
		return logger;
	}

	//void Logger::setOutputFile(const std::string &filename) {
	//	file = filename;

	//	// Add this file if it hasn't been written to yet
	//	if (std::find(filePaths.begin(), filePaths.end(), filename) == filePaths.end()) {
	//		filePaths.push_back(filename);
	//		clearFileContents();
	//	}
	//}

	//// TODO: This function will clear the same file multiple times
	//void Logger::clearFileContents() {
	//	filestream.open(file, std::ofstream::out);
	//	if (!filestream) {
	//		error("logged_files/log.txt", "Logger Dtor", "Could not empty the contents of file: " + file);
	//	}
	//	filestream.close();
	//}
}
