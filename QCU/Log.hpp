#pragma once

#ifdef QCU_EXPORTS
#define QCU_API __declspec(dllexport)
#else
#define QCU_API __declspec(dllimport)
#endif



#include <iostream>

#include "Core.hpp"



namespace qcu {

QCU_API void log(std::ostream & logStream);
QCU_API std::ostream & log();

inline void error_break() {}
inline void warning_break() {}
inline void exception_break() {}

}



#define Q_ERROR(msg) do { \
    qcu::log() << "ERROR" << std::endl; \
    qcu::log() << "\t" << msg << std::endl; \
    qcu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qcu::error_break(); \
} while (false)

#define Q_WARNING(msg) do { \
    qcu::log() << "WARNING" << std::endl; \
    qcu::log() << "\t" << msg << std::endl; \
    qcu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qcu::warning_break(); \
} while (false)

#define Q_LOG(msg) do { \
    qcu::log() << msg << std::endl; \
} while (false)

#define Q_EXCEPTION(msg, exception) do { \
    qcu::log() << "EXCEPTION" << std::endl; \
    qcu::log() << "\t" << msg << std::endl; \
    qcu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    qcu::exception_break(); \
    throw exception; \
} while (false)