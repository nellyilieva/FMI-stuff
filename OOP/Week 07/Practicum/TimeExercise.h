#pragma once
#include <iostream>
#include <fstream>

namespace Time {

	class Duration {
	private:
		unsigned seconds;

	public:
		static const Duration Seconds;
		static const Duration Minutes;
		static const Duration Hours;

		Duration();
		Duration(unsigned _seconds);
		unsigned getSeconds() const;

		//prefix
		Duration& operator++();
		Duration& operator--();

		//syfix
		Duration& operator++(int);
		Duration& operator--(int);

		Duration& operator+=(const Duration& other);
		Duration& operator-=(const Duration& other);
		Duration& operator*=(unsigned factor);

		/*friend std::istream& operator>>(std::istream& is, Time::Duration& d);
		friend std::ostream& operator<<(std::ostream& os, Time::Duration& d);*/
	};
}

Time::Duration operator+(const Time::Duration& lhs, const Time::Duration& rhs);
Time::Duration operator-(const Time::Duration& lhs, const Time::Duration& rhs);


bool operator==(const Time::Duration& lhs, const Time::Duration& rhs);
bool operator!=(const Time::Duration& lhs, const Time::Duration& rhs);
bool operator<(const Time::Duration& lhs, const Time::Duration& rhs);
bool operator>(const Time::Duration& lhs, const Time::Duration& rhs);
bool operator<=(const Time::Duration& lhs, const Time::Duration& rhs);
bool operator>=(const Time::Duration& lhs, const Time::Duration& rhs);

