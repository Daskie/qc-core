#pragma once

#include <iostream>
#include <string>

namespace qc::log {

    inline void error_break() {}

    inline void warning_break() {}

    inline void exception_break() {}

}

#define QC_ERROR(msg) do { \
    std::cout << "ERROR" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::log::error_break(); \
} while (false)

#define QC_WARNING(msg) do { \
    std::cout << "WARNING" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::log::warning_break(); \
} while (false)

#define QC_LOG(msg) do { \
    std::cout << msg << std::endl; \
} while (false)

#define QC_EXCEPTION(msg, exception) do { \
    std::cout << "EXCEPTION" << std::endl; \
    std::cout << "\t" << msg << std::endl; \
    std::cout << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qc::log::exception_break(); \
    throw exception; \
} while (false)
