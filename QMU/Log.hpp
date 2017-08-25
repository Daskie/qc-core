#pragma once

#ifdef QMU_EXPORTS
#define QMU_API __declspec(dllexport)
#else
#define QMU_API __declspec(dllimport)
#endif



#include <iostream>

#include "Core.hpp"



namespace qmu {

QMU_API void log(std::ostream & logStream);
QMU_API std::ostream & log();

inline void error_break() {}
inline void warning_break() {}
inline void exception_break() {}

}



#define QERROR(msg) do { \
    qmu::error_break(); \
    qmu::log() << "ERROR" << std::endl; \
    qmu::log() << "\t" << msg << std::endl; \
    qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define QWARNING(msg) do { \
    qmu::warning_break(); \
    qmu::log() << "WARNING" << std::endl; \
    qmu::log() << "\t" << msg << std::endl; \
    qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define QLOG(msg) do { \
    qmu::log() << msg << std::endl; \
} while (false)

#define QEXCEPTION(msg, exception) do { \
    qmu::exception_break(); \
    qmu::log() << "EXCEPTION" << std::endl; \
    qmu::log() << "\t" << msg << std::endl; \
    qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
    throw exception; \
} while (false)