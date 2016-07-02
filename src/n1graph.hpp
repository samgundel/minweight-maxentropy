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

#ifndef MIN_WEIGHT_N1_HPP_
#define MIN_WEIGHT_N1_HPP_

#include <adjacency_graph.hpp>

namespace n1graph {

class N1Graph {
public:
	N1Graph();

	/**
	 * A Dynamic Programming algorithm to find the MinWeight Max Entropy
	 * of a point-set.
	 *
	 *  - Samuel de Sousa, Walter Kropatsch. Data Graph Formulation as the
	 *	  Minimum-Weight Maximum-Entropy Problem. 10th IAPR-TC15 Workshop
	 * 	  on Graph-based Representations in Pattern Recognition (GbR2015).
	 *
	 * Time Complexity: O(V^3 * E).
	 * Space Complexity: O(V^3).
	 */
	void Minimize(const AdjacencyGraph& input);

	/**
	 * Given the order of nodes to be added into the graphs, build the graph.
	 *
	 * Time Complexity: O(V+E)
	 */
	void BuildGraph(const std::vector<int>& nodes);

	/**
	 * Returns the G_N graph created.
	 */
	const AdjacencyGraph& result() const {
		return result_;
	}

	virtual ~N1Graph();

private:

	/**
	 * Once the Dynamic Programming method has computed the
	 * optimum solution. We need to trace back from the solution
	 * to reconstruct the graph.
	 *
	 * Time Complexity: O(V+E).
	 */
	std::vector<int> TraceBack(const Matrix<float>& dp, int layer);

	int FindOptimalLayer(const Matrix<float>& dp);

	/**
	 * The graph which minimizes the weight and maximizes the divergence of
	 * degree.
	 *
	 * Space Complexity: O(V^2).
	 */
	AdjacencyGraph result_;

};

}  // namespace n1graph
#endif /* MIN_WEIGHT_N1_HPP_ */
