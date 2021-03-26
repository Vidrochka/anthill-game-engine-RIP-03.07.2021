#include "../Include/ATLogger.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <stdexcept>

namespace at::utils::logger
{
    std::map<std::string, inner::LoggerInfo *> ATLogger::_log_buffer_map{};
    std::mutex *ATLogger::_add_new_section_mutex = new std::mutex{};

    std::string _get_datetime_prefix();

    void ATLogger::_log(inner::LoggerInfo *log_section, std::string msg)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        log_section->buffer << msg;
    }

    void ATLogger::_log(std::string log_section, std::string msg)
    {
        _log(_log_buffer_map[log_section], msg);
    }

    void ATLogger::_flush_all()
    {
        for (auto log_info : _log_buffer_map)
            _flush(log_info.second);
    }

    void ATLogger::_flush(inner::LoggerInfo *log_section)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);

        std::ofstream out(log_section->fpath, std::ios::app);

        if (out.is_open())
        {
            out << log_section->buffer.str();
            log_section->buffer.str(std::string());
        }
        else
        {
            throw std::string("Невозможно открыть файл для записи в лог");
        }

        out.close();
    }

    void ATLogger::_flush(std::string log_section)
    {
        _flush(_log_buffer_map[log_section]);
    }

    void ATLogger::_set_new_log_path(inner::LoggerInfo *log_section, std::string fpath)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        log_section->fpath = fpath;
    }

    void ATLogger::_set_new_log_path(std::string log_section, std::string fpath)
    {
        _set_new_log_path(_log_buffer_map[log_section], fpath);
    }

    ATLogger::ATLogger(std::string log_section)
    {
        _logger_section = _log_buffer_map[log_section];
    }

    ATLogger::ATLogger()
    {
        _logger_section = _log_buffer_map[""];
    }

    ATLogger::~ATLogger()
    {
        flush();
    }

    void ATLogger::b_set_new_log_path(std::string fpath)
    {
        _set_new_log_path("", fpath);
    }

    void ATLogger::set_new_log_path(std::string log_section, std::string fpath)
    {
        _set_new_log_path(log_section, fpath);
    }

    void ATLogger::set_new_log_path(std::string fpath)
    {
        _set_new_log_path(_logger_section, fpath);
    }

    void ATLogger::b_log_info(std::string msg)
    {
        _log("", _get_datetime_prefix() + " <Info> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::b_log_debug(std::string msg)
    {
        _log("", _get_datetime_prefix() + " <Debug> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::b_log_error(std::string msg)
    {
        _log("", _get_datetime_prefix() + " <Error> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::b_log_fatal(std::string msg, int exit_code)
    {
        _log("", _get_datetime_prefix() + " <Fatal> { exit_code: " + std::to_string(exit_code) + ", msg: \"" + msg + "\" }\n");
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_log_args(std::string args, int count)
    {
        _log("", _get_datetime_prefix() + " <ARGS> { count: " + std::to_string(count) + ", args: [" + args + "] }\n");
    }

    void ATLogger::log_info(std::string msg)
    {
        _log(_logger_section, _get_datetime_prefix() + " <Info> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::log_debug(std::string msg)
    {
        _log(_logger_section, _get_datetime_prefix() + " <Debug> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::log_error(std::string msg)
    {
        _log(_logger_section, _get_datetime_prefix() + " <Error> { msg: \"" + msg + "\" }\n");
    }

    void ATLogger::log_fatal(std::string msg, int exit_code)
    {
        _log(_logger_section, _get_datetime_prefix() + " <Fatal> { exit_code: " + std::to_string(exit_code) + ", msg: \"" + msg + "\" }\n");
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_flush()
    {
        _flush("");
    }

    void ATLogger::flush(std::string log_section)
    {
        _flush(log_section);
    }

    void ATLogger::flush()
    {
        _flush(_logger_section);
    }

    void ATLogger::init_base_logger(int buffer_size, std::string fpath, bool throw_if_exist)
    {
        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _log_buffer_map[""] = new inner::LoggerInfo(fpath, buffer_size);
    }

    bool ATLogger::is_section_exist(std::string log_section, bool need_create_if_not_exist, std::string fpath, int buffer_size)
    {
        if (_log_buffer_map.count(log_section) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        if (need_create_if_not_exist)
            _log_buffer_map[""] = new inner::LoggerInfo(fpath, buffer_size);

        return false;
    }

    void ATLogger::create_section(std::string log_section, std::string fpath, int buffer_size, bool throw_if_exist)
    {
        if (_log_buffer_map.count(log_section) > 0 && throw_if_exist)
            throw std::string("Log section already exist");

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _log_buffer_map[log_section] = new inner::LoggerInfo(fpath, buffer_size);
    }

    std::string _get_datetime_prefix()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        std::string s_dt = std::string(dt);
        return "[" + s_dt.substr(0, s_dt.length() - 1) + "]";
    }
}