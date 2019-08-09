#pragma once

#include <iostream>
#include <string>

namespace qc {

inline void error_break() {}

inline void warning_break() {}

inline void exception_break() {}

}

#define Q_ERROR(msg) do { \
    std::cout << "ERROR" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::error_break(); \
} while (false)

#define Q_WARNING(msg) do { \
    std::cout << "WARNING" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::warning_break(); \
} while (false)

#define Q_LOG(msg) do { \
    std::cout << msg << std::endl; \
} while (false)

#define Q_EXCEPTION(msg, exception) do { \
    std::cout << "EXCEPTION" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::exception_break(); \
    throw exception; \
} while (false)
