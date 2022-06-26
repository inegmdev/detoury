#pragma once
#include "spdlog/spdlog.h"

class Logger {
private:
	std::shared_ptr<spdlog::logger> m_logger;
public:
	Logger();
	void init();
	void write();
};
