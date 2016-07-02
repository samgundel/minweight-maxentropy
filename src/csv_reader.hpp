/*
 * Copyright 2014 Samuel de Sousa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CSV_READER_HPP_
#define CSV_READER_HPP_

#include <fstream>
#include <sstream>
#include <vector>
#include <vector.hpp>

namespace n1graph {

class CSVReader {
public:

	static Vector<float> split(const std::string &s, char delim) {
		std::vector<std::string> tokens;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			tokens.push_back(item);
		}
		Vector<float> point;
		point.Resize(tokens.size());
		for (uint i = 0; i < tokens.size(); ++i) {
			point.Set(i, std::stof(tokens[i]));
		}
		return point;
	}

	static std::vector<Vector<float> > ReadCSV(const std::string &filename,
			char delim) {

		std::vector<Vector<float> > values;
		std::ifstream in(filename.c_str());
		if (!in.is_open())
			return values;
		std::string line;
		while (std::getline(in, line)) {
			values.push_back(split(line, delim));
		}

		return values;
	}

};

} /* namespace n1graph */
#endif /* CSV_READER_HPP_ */
