#include <iostream>
#include <Windows.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "Logger.h"

/* Used for generating timestamped log file */
#include <chrono>
#include <iomanip> // iomanip to manipulate the output
#include <sstream> // the outptut saved in stringstream
#include <ctime>

/* Used for dynamic writing in the log file*/
#include <spdlog/fmt/fmt.h>

Logger::Logger() {
	std::tm bt{};
	// Use static method `now` to return the number of ticks
	auto now = std::chrono::system_clock::now();
	// Convert the time to time_t structure
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	// Reformat the time into string
	std::stringstream time;
	localtime_s(&bt, &in_time_t);
	time << std::put_time(&bt, "%Y_%m_%d-%H_%M_%S");
	// Save the filename in 
	m_log_file_name = time.str() + "__Detoury_log.txt";
}

void Logger::init() {
	try {
		// Create basic file logger (not rotated)
		std::string path_of_file = "C:/logs/" + m_log_file_name;
		m_logger = spdlog::basic_logger_mt(
			"basic_logger", path_of_file
		);
		m_logger->set_pattern("{ 'timestamp': '%E.%f', 'timestampReadable': '%T.%f' , 'processId': '%P', 'threadId': '%t' , 'event': %v }");
		MessageBoxA(HWND_DESKTOP, path_of_file.c_str(), "Detoury - Success", MB_OK);
	}
	catch (const spdlog::spdlog_ex &ex) {
		MessageBoxA(HWND_DESKTOP, "Failed to init the log file", "Detoury::Log", MB_OK);
		MessageBoxA(HWND_DESKTOP, ex.what(), "Detoury::Log", MB_OK);
	}
}

