#pragma once

#include "QMU.h"

#include <iostream>



namespace qmu {

QMU_API void log(std::ostream & logStream);
QMU_API std::ostream & log();

inline void error_break() {}
inline void warning_break() {}
inline void exception_break() {}

}



#define Q_ERROR(msg) do { \
	qmu::error_break(); \
	qmu::log() << "ERROR" << std::endl; \
	qmu::log() << "\t" << msg << std::endl; \
	qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_WARNING(msg) do { \
	qmu::warning_break(); \
	qmu::log() << "WARNING" << std::endl; \
	qmu::log() << "\t" << msg << std::endl; \
	qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_LOG(msg) do { \
	qmu::log() << msg << std::endl; \
} while (false)

#define Q_EXCEPTION(msg) do { \
	qmu::exception_break(); \
	qmu::log() << "EXCEPTION" << std::endl; \
	qmu::log() << "\t" << msg << std::endl; \
	qmu::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)