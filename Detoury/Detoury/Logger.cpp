#include <iostream>
#include <Windows.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "Logger.h"

Logger::Logger() {

}

void Logger::init() {
	try {
		// Create basic file logger (not rotated)
		m_logger = spdlog::basic_logger_mt(
			"basic_logger", "C:/logs/basic-log.txt"
		);
		MessageBoxA(HWND_DESKTOP, "Success", "Success", MB_OK);
	}
	catch (const spdlog::spdlog_ex &ex) {
		MessageBoxA(HWND_DESKTOP, "Failed to init the log file", "Detoury::Log", MB_OK);
		MessageBoxA(HWND_DESKTOP, ex.what(), "Detoury::Log", MB_OK);
	}
}
void Logger::write() {
	m_logger->info("Hello world");
}