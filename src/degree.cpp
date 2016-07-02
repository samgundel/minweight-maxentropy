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

#include <degree.hpp>

#include <cmath>
#include <set>
#include <vector>

#include <glog/logging.h>

namespace n1graph {

template <class T>
std::vector<int> Degree<T>::DegreeVector(const Matrix<T>& adjacency) {
	CHECK_EQ(adjacency.cols(), adjacency.rows());
	std::vector<int> values(adjacency.cols());
	for (int i = 0; i < adjacency.rows(); ++i) {
		for (int j = 0; j < adjacency.cols(); ++j) {
			float weight = adjacency(i, j);
			if (weight > 0 && weight < INFINITY) {
				values[i] += 1;
			}
		}
	}
	return values;
}

template <class T>
Vector<int> Degree<T>::DegreeLength(const Matrix<T>& adjacency,
		const std::vector<bool>& mask) {
	CHECK_EQ(adjacency.rows(), adjacency.cols());
	CHECK_EQ(adjacency.rows(), mask.size());
	std::vector<int> degree_vector = Degree<T>::DegreeVector(adjacency);
	std::set<int> unique_elements;
	for (int i = 0; i < mask.size(); ++i) {
		if ( mask[i] )
			unique_elements.insert(degree_vector[i]);
	}
	return unique_elements.size();
}

template class Degree<bool>;
template class Degree<int>;
template class Degree<long>;
template class Degree<float>;
template class Degree<double>;

} /* namespace n1graph */

