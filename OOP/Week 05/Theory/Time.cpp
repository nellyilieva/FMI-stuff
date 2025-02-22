#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)
#include "Time.h"

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier) {
	if (newValue >= lowerBound && newValue <= upperBound) {
		(secondsFromMidnight -= (oldValue * multiplier)) += (newValue * multiplier);
		return true;
	}
	else {
		return false;
	}
}

Time::Time(unsigned hours, unsigned minutes, unsigned seconds) {
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

unsigned Time::getHours() const {
	return secondsFromMidnight / SECONDS_IN_HOURS;
}

unsigned Time::getMinutes() const {
	return (secondsFromMidnight / SECONDS_IN_MINUTE) % 60;
}

unsigned Time::getSeconds() const {
	return secondsFromMidnight % 60;
}

bool Time::setHours(unsigned hours) {
	return validateAndSet(0, 24, hours, getHours(), SECONDS_IN_HOURS);
}

bool Time::setMinutes(unsigned minutes) {
	return validateAndSet(0, 59, minutes, getMinutes(), SECONDS_IN_MINUTE);
}

bool Time::setSeconds(unsigned seconds) {
	return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

void Time::tick() {
	++secondsFromMidnight %= DAY_SECONDS;
}

void Time::serialize(std::ostream& os) const {
	os << std::setw(2) << std::setfill('0') << getHours() << ":"
		<< std::setw(2) << std::setfill('0') << getMinutes() << ":"
		<< std::setw(2) << std::setfill('0') << getSeconds() << std::endl;
}

int compareTimes(const Time& lhs, const Time& rhs) {
	if (lhs.getHours() == rhs.getHours()) {
		if (lhs.getMinutes() == rhs.getMinutes()) {
			return lhs.getSeconds() - rhs.getSeconds();
		}
		else {
			return lhs.getMinutes() - rhs.getMinutes();
		}
	}
	else {
		return lhs.getHours() - rhs.getHours();
	}
}

int main (){
	
}
