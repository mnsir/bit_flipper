#pragma once

// Modern C++ ONLY!!!

#include <bitset>

// TODO
// Добавить все фундаментальные типы

// bool

// signed short int;
// unsigned short int;
// signed int;
// unsigned int;
// signed long int;
// unsigned long int;
// signed long long int;
// unsigned long long int;

// signed char;
// unsigned char;
// wchar_t;
// char8_t // C++20
// char16_t;
// char32_t;

// float;
// double;
// long double;


class BitSwitcher
{
public:
	void SetBit(size_t pos, bool value) {
		data.set(pos, value);
	}

	double GetDouble() const {
		Conv conv(data.to_ullong());
		return conv._double[0];
	}

	float GetFloat0() const {
		Conv conv(data.to_ullong());
		return conv._float[0];
	}

	float GetFloat1() const {
		Conv conv(data.to_ullong());
		return conv._float[1];
	}

	auto DebugInfo() const { return data.to_string(); }

private:
	std::bitset<64U> data;

	union Conv {
		Conv(uint64_t value) : _uint{ value }
		{
		}

		uint64_t _uint[1];
		double _double[1];
		float _float[2];
	};
};

