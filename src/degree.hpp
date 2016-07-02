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


#ifndef DEGREE_HPP_
#define DEGREE_HPP_

#include <vector>

#include <adjacency_graph.hpp>

namespace n1graph {

/**
 * A class which calculates the degree of a given graph as well as how many
 * unique node degrees exist in the graph.
 */
template<class T>
class Degree {
private:
	Degree() {
	}
public:
	/**
	 * Given an adjacency matrix, we retrieve a vector corresponding to the
	 * degree of nodes.
	 *
	 * Time Complexity: O(V)
	 *
	 * @param adjacency The adjacency matrix of a graph.
	 * @return the vector containing the degree values.
	 */
	static std::vector<int> DegreeVector(const Matrix<T>& adjacency);

	/**
	 * Given an adjacency matrix, we retrieve the number of unique node degrees.
	 *
	 * Time Complexity: O(V)
	 *
	 * @param adjacency The adjacency matrix of a graph.
	 * @return the number of different degree values.
	 */
	static Vector<int> DegreeLength(const Matrix<T>& adjacency,
			const std::vector<bool>& mask);
};

} /* namespace n1graph */
#endif /* DEGREE_HPP_ */
