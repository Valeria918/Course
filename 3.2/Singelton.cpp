#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class Logger {
public:
    enum LogLevel { info = 0, warning = 1, error = 2 };

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Meyers singleton: thread-safe по C++11, деструктор вызывается при завершении программы
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }

    void Log(const std::string& message, LogLevel level) {
        std::string levelStr;
        switch (level) {
            case info:    levelStr = "I"; break;
            case warning: levelStr = "W"; break;
            case error:   levelStr = "E"; break;
        }

        // форматируем время до захвата мьютекса — не держим лок дольше нужного
        std::string timeStr = getFormattedCurrentTime();

        std::lock_guard<std::mutex> lock(mtx);
        if (file.is_open()) {
            file << timeStr << " [" << levelStr << "] " << message << "\n";
        }
    }

private:
    std::ofstream file;
    std::mutex mtx;

    Logger() {
        file.open("log.txt", std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            file << "Файл создан инициализацией класса.\n";
        }
    }

    ~Logger() {
        if (file.is_open()) {
            file.close();
        }
    }

    std::string getFormattedCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        struct tm parts{};
#ifdef _WIN32
        localtime_s(&parts, &now_c);  // thread-safe на Windows
#else
        localtime_r(&now_c, &parts);  // thread-safe на POSIX
#endif

        std::ostringstream oss;
        oss << std::setfill('0') << "["
            << std::setw(2) << parts.tm_hour << ":"
            << std::setw(2) << parts.tm_min  << ":"
            << std::setw(2) << parts.tm_sec  << "."
            << std::setw(3) << now_ms.count()
            << "]";
        return oss.str();
    }
};

int main() {
    Logger& l1 = Logger::GetInstance();
    l1.Log("This is an info message.", Logger::info);
    Logger& l2 = Logger::GetInstance();
    l2.Log("This is a warning message.", Logger::warning);
    l2.Log("This is an error message.", Logger::error);

    return 0;
}
