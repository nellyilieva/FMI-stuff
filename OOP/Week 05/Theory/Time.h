#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

constexpr unsigned int SECONDS_IN_HOURS = 3600;
constexpr unsigned int SECONDS_IN_MINUTE = 60;
constexpr unsigned int DAY_SECONDS = 24 * 3600;

class Time {
private:
	unsigned secondsFromMidnight = 0;

	bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier);

public:
	Time() = default;
	Time(unsigned hours, unsigned minutes, unsigned seconds);

	unsigned getHours() const;
	unsigned getMinutes() const;
	unsigned getSeconds() const;

	bool setHours(unsigned hours);
	bool setMinutes(unsigned minutes);
	bool setSeconds(unsigned seconds);

	void tick();

	void serialize(std::ostream& os) const;
};

int compareTimes(const Time& lhs, const Time& rhs);