#include "stdafx.h"
#include "QLog.hpp"



namespace QLog {



namespace {

std::ostream * s_logStream(&std::cout);

}



void log(std::ostream & s_logStream_) {
	s_logStream = &s_logStream_;
}

std::ostream & log() {
	return *s_logStream;
}



}