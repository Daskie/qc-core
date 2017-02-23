#pragma once

#ifdef QMU_EXPORTS
#define QMU_API __declspec(dllexport)
#else
#define QMU_API __declspec(dllimport)
#endif



#include <iostream>

#include "QMU.hpp"



namespace qmu {

QMU_API void log(std::ostream & logStream);
QMU_API std::ostream & log();

inline void error_break() {}
inline void warning_break() {}
inline void exception_break() {}

}



#define Q_ERROR(msg) do { \
	error_break(); \
	log() << "ERROR" << std::endl; \
	log() << "\t" << msg << std::endl; \
	log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_WARNING(msg) do { \
	warning_break(); \
	log() << "WARNING" << std::endl; \
	log() << "\t" << msg << std::endl; \
	log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)

#define Q_LOG(msg) do { \
	log() << msg << std::endl; \
} while (false)

#define Q_EXCEPTION(msg) do { \
	exception_break(); \
	log() << "EXCEPTION" << std::endl; \
	log() << "\t" << msg << std::endl; \
	log() << "\t" << __func__ << " (" << __FILE__ << "(" << __LINE__ << "))" << std::endl; \
} while (false)