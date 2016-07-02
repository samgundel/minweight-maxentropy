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

#ifndef ADJACENCY_GRAPH_HPP_
#define ADJACENCY_GRAPH_HPP_

#include <matrix.hpp>
#include <vector.hpp>
#include <types.hpp>

namespace n1graph {

struct Edge {
	int source_;
	int target_;
	float weight_;
	Edge(int source, int target, float weight) :
			source_(source), target_(target), weight_(weight) {
	}
};

class AdjacencyGraph {
public:
	AdjacencyGraph();

	AdjacencyGraph(int n, GraphType directed = GraphType::DIRECTED,
			float default_value = 0);

	void Initialize(int n, GraphType directed = GraphType::DIRECTED,
			float default_value = 0);

	void SetLocation(int node, const Vector<float>& location);

	virtual void AddEdge(int source, int target);

	virtual void AddWeightedEdge(int source, int target, float weight);

	virtual void AddEuclideanWeightedEdge(int source, int target);

	virtual std::string ToString() const;

	virtual std::string ToTikz() const;

	virtual size_t NumberOfNodes() const {
		return adjacency_.rows();
	}

	virtual ~AdjacencyGraph();

	GraphType graph_type() const {
		return graph_type_;
	}

	const std::vector<Vector<float> >& location() const {
		return location_;
	}

	const Vector<float>& location(int node) const {
		CHECK_LT(node, location_.size());
		return location_[node];
	}

	std::vector<Vector<float> >* mutable_location() {
		return &location_;
	}

	std::vector<Edge> edges() const {
		std::vector<Edge> edges;
		for (int i = 0; i < adjacency_.rows(); ++i) {
			for (int j = 0; j < adjacency_.cols(); ++j) {
				if (graph_type_ == GraphType::UNDIRECTED && j <= i)
					continue;
				float weight = adjacency_(i, j);
				if (weight > 0) {
					edges.push_back(Edge(i, j, weight));
				}
			}
		}
		return edges;
	}

	const Matrix<float>& adjacency() const {
		return adjacency_;
	}

	Matrix<float>* mutable_adjacency() {
		return &adjacency_;
	}

private:
	GraphType graph_type_;
	std::vector<Vector<float>> location_;
	Matrix<float> adjacency_;
};

} /* namespace n1graph */
#endif /* ADJACENCY_GRAPH_HPP_ */
