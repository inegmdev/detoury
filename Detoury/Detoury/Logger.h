#pragma once
#include "spdlog/spdlog.h"
#include <string>

class Logger {
private:
	std::shared_ptr<spdlog::logger> m_logger;
	std::string m_log_file_name;
public:
	Logger();
	void init();
	void write();
};
