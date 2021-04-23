#include "anthill-game-engine.hpp"

auto get_unhandled_exception_log()->std::shared_ptr<ILogger>;

int main(int argc, char* argv[])
{
	try
	{
		setlocale(LC_ALL, "en_US.UTF-8");
		auto core = at::core::engine_core::get_engine_core();
		core->run();
	}
	catch (std::exception ex)
	{
		auto logger = get_unhandled_exception_log();
		logger->log_fatal("Unhandled exception: "u8at + ex.what(), -1);
		return -1;
	}

	return 0;
}

auto get_unhandled_exception_log() -> std::shared_ptr<ILogger> {
	auto logger_manager = std::shared_ptr<ILoggerManager>(new LoggerManager());
	logger_manager->create_logger("unhandled_exception"u8at, std::shared_ptr<ILogStrategy>(new FileLogStrategy("unhandled_exception.log"u8at, 0)));
	auto logger = logger_manager->get_logger("unhandled_exception"u8at);
	logger->add_strategy(std::shared_ptr<ILogStrategy>(new ConsoleLogStrategy(0)));
	return logger;
}
