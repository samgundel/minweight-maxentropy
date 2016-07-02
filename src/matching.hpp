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


#ifndef MATCHING_HPP_
#define MATCHING_HPP_

#include <memory>
#include <string>

#include <glog/logging.h>

#include <adjacency_graph.hpp>
#include <n1graph.hpp>

namespace n1graph {

class Matching {
public:
	Matching();

	/**
	 * This method performs the registration between Two graphs which fulfill
	 * the NHDD property (defined in the paper as G_N graphs). The ggraphs need
	 * to have the same number of points.
	 *
	 * Time Complexity: O(V+E)
	 * Space Complexity: O(V)
	 *
	 * @param g1: The first graph G_N to be registered.
	 * @param g2: The second graph G_N to be registered.
	 */
	void Register(const N1Graph& g1, const N1Graph& g2);

	/**
	 * This method returns the correspondence of a point in one graph to a point
	 * in the other graph.
	 *
	 * Time Complexity: O(1)
	 *
	 * @param graph: The index of the graph (0 for the first graph, 1 to the
	 * second graph).
	 *
	 * @param point: The index of node.
	 *
	 * @return the corresponding point.
	 */
	int Correspondence(int graph, int point);

	/**
	 * This method generates Tikz code for displaying the graphs.
	 *
	 * @param: g1: The first graph to be rendered.
	 * @param: g2: The first graph to be rendered.
	 * @param: gap: The space between the two graphs allowing one to render
 	 * other graph in a desired relative location to the first graph.
	 * @param: edge_percentage: The percentage of edges to be rendered, e.g.
	 * 0.5 means that 50% of the edges will be randomly selected and drawn.
	 */
	std::string ToTikz(const N1Graph& g1, const N1Graph& g2,
			const Vector<float>& gap, float edge_percentage) const;

	virtual ~Matching();
private:
	int number_of_points;
	std::unique_ptr<int[]> g1_mapping;
	std::unique_ptr<int[]> g1_reverse_mapping;
	std::unique_ptr<int[]> g2_mapping;
	std::unique_ptr<int[]> g2_reverse_mapping;
};

} /* namespace n1graph */
#endif /* MATCHING_HPP_ */
