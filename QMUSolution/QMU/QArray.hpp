#pragma once

namespace qmu {


template <typename T>
class Array {

	public:

	const long long n;
	T * const p;

	Array(long long n, T * p) :
		m_n(n),
		m_p(p)
	{}

	Array(const Array<T> & arr) :
		m_n(arr.n),
		m_p(arr.p)
	{}

	Array<T> & operator=(const Array<T> & arr) = delete;

	T & operator[](long long i) {
		return m_p[i];
	}

	T & operator*() {
		return *m_p;
	}

	T * operator->() {
		return m_p;
	}

};


}
