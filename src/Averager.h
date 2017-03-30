/*
 * Averager.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Tim Helland
 */
#include <queue>

#ifndef SRC_Averager_H_
#define SRC_Averager_H_

class Averager {
	std::queue<float> _data;
	unsigned int _mincount;
	unsigned int _maxcount;
	float _defaultvalue;
	float _sum;
public:
	Averager(unsigned int min_count, unsigned int max_count, float defaultvalue);
	void addValue(float datapoint);
	void resetAll();
	float getCurrentAverage();
};

#endif /* SRC_Averager_H_ */
