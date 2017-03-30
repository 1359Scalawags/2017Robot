/*
 * Averager.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: Tim Helland
 */

#include "Averager.h"
#include <queue>

Averager::Averager(unsigned int min_count, unsigned int max_count, float default_value) {
	_mincount = min_count;
	_maxcount = max_count;
	_defaultvalue = default_value;
	_sum = 0;
}

void Averager::resetAll() {
	_sum = 0;
}

void Averager::addValue(float datapoint) {
	_data.push(datapoint);
	_sum += datapoint;
	while(_data.size() > _maxcount) {
		float temp = _data.front();
		_data.pop();
		_sum -= temp;
	}
}

float Averager::getCurrentAverage() {
	if(_data.size() < _mincount) {
		return _defaultvalue;
	}
	else {
		return _sum / _data.size();
	}
}

