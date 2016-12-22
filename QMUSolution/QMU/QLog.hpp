#pragma once

#include "QMU.h"

#include <iostream>



namespace QLog {



QMU_API void log(std::ostream & logStream);
QMU_API std::ostream & log();



inline void error_break() {}
inline void warning_break() {}
inline void exception_break() {}



#define Q_ERROR(msg) do { \
	QLog::error_break(); \
	QLog::log() << "ERROR" << std::endl; \
	QLog::log() << "\t" << msg << std::endl; \
	QLog::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_WARNING(msg) do { \
	QLog::warning_break(); \
	QLog::log() << "WARNING" << std::endl; \
	QLog::log() << "\t" << msg << std::endl; \
	QLog::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_LOG(msg) do { \
	QLog::log() << msg << std::endl; \
} while (false)

#define Q_EXCEPTION(msg) do { \
	QLog::exception_break(); \
	QLog::log() << "EXCEPTION" << std::endl; \
	QLog::log() << "\t" << msg << std::endl; \
	QLog::log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

}