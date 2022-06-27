#pragma once
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/fmt.h"

class Logger {
private:
	std::shared_ptr<spdlog::logger> m_logger;
	std::string m_log_file_name;
public:
	Logger();
	void init();

	template<typename... Args>
	void write(fmt::format_string<Args...> fmt, Args &&... args) {
		m_logger->info(fmt, std::forward<Args>(args)...);
	}
};
