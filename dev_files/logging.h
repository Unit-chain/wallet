#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <iomanip>

// Define logging levels
enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

// Define a logging class
class Logger {
public:
    Logger(const std::string& level = "Info", const std::string& min_level = "Info") : 
        m_level(stringToLevel(level)), 
        m_min_level(stringToLevel(min_level))
    {}

    virtual ~Logger() = default;

    // Set the logging level
    void setLogLevel(const std::string& level) {
        m_level = stringToLevel(level);
    }

    // Set the minimum logging level
    void setMinLogLevel(const std::string& level) {
        m_min_level = stringToLevel(level);
    }

    // Log a message at the specified level and return a function object with a new logging level
    std::function<Logger&(const std::string&)> log(LogLevel level) {
        return [this, level](const std::string& message) -> Logger& {
            if (level >= m_level && level >= m_min_level) {
                std::time_t now = std::time(nullptr);
                std::tm timeinfo = *std::localtime(&now);
                std::cout << "[" << levelToString(level) << "] " << std::put_time(&timeinfo, "%c")
                          << " [DEBUG " << levelToString(m_level) << "] " << message << std::endl;
            }
            return *this;
        };
    }

    // Convert a logging level to a string
    static std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Debug:
                return "DEBUG";
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Warning:
                return "WARNING";
            case LogLevel::Error:
                return "ERROR";
            default:
                return "UNKNOWN";
        }
    }

private:
    LogLevel m_level;
    LogLevel m_min_level;

	// Convert a string to a logging level
	LogLevel stringToLevel(const std::string& level) {
	    std::string lowercase_level = level;
	    std::transform(lowercase_level.begin(), lowercase_level.end(), lowercase_level.begin(),
			   [](unsigned char c) { return std::tolower(c); });
	    if (lowercase_level == "debug") {
		return LogLevel::Debug;
	    } else if (lowercase_level == "info") {
		return LogLevel::Info;
	    } else if (lowercase_level == "warning") {
		return LogLevel::Warning;
	    } else if (lowercase_level == "error") {
		return LogLevel::Error;
	    } else {
		return LogLevel::Info;
	    }
	} 
};


