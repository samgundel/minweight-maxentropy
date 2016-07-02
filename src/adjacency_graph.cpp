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

#include <adjacency_graph.hpp>

#include <cmath>

#include <string>

namespace n1graph {

AdjacencyGraph::AdjacencyGraph() :
		graph_type_(GraphType::UNDIRECTED) {

}

AdjacencyGraph::AdjacencyGraph(int n, GraphType directed, float default_value) {
	Initialize(n, directed, default_value);
}

void AdjacencyGraph::AddEdge(int source, int target) {
	CHECK_LT(source, location_.size());
	CHECK_LT(target, location_.size());
	adjacency_(source, target) = 1;
	if (graph_type_ == UNDIRECTED)
		adjacency_(target, source) = 1;
}

void AdjacencyGraph::AddWeightedEdge(int source, int target, float weight) {
	CHECK_LT(source, location_.size());
	CHECK_LT(target, location_.size());
	adjacency_(source, target) = weight;
	if (graph_type_ == UNDIRECTED)
		adjacency_(target, source) = weight;
}

void AdjacencyGraph::AddEuclideanWeightedEdge(int source, int target) {
	CHECK_LT(source, location_.size());
	CHECK_LT(target, location_.size());
	adjacency_(source, target) = (location_[source] - location_[target]).Norm();
	if (graph_type_ == UNDIRECTED)
		adjacency_(target, source) = adjacency_(source, target);
}

void AdjacencyGraph::SetLocation(int node, const Vector<float>& location) {
	CHECK_LT(node, location_.size());
	location_[node] = location;
}

std::string AdjacencyGraph::ToString() const {
	std::string output;
	// Adding the number of Nodes.
	output.append(std::to_string(location_.size()));
	output.append(",");
	// Adding the if graph is directed.
	if (graph_type_ == GraphType::DIRECTED)
		output.append("1");
	else
		output.append("0");
	output.append("\n");
	// Adding location information.
	for (const Vector<float>& location : location_) {
		output.append(std::to_string(location[0]));
		output.append(",");
		output.append(std::to_string(location[1]));
		output.append("\n");
	}
	// Adding edge weights.
	for (int i = 0; i < adjacency_.rows(); ++i) {
		for (int j = 0; j < adjacency_.cols(); ++j) {
			if (graph_type_ == GraphType::UNDIRECTED && j <= i)
				continue;
			float weight = adjacency_(i, j);
			if (weight > 0 and weight < INFINITY) {
				output.append(std::to_string(i));
				output.append(",");
				output.append(std::to_string(j));
				output.append(",");
				output.append(std::to_string(weight));
				output.append("\n");
			}
		}
	}
	return output;
}

void AdjacencyGraph::Initialize(int n, GraphType direction,
		float default_value) {
	CHECK_GT(n, 0);
	graph_type_ = direction;
	adjacency_.Allocate(n, n, 1, default_value);
	for (int i = 0; i < n; ++i) {
		location_.push_back(Vector<float>(0, 0));
	}

}

std::string AdjacencyGraph::ToTikz() const {
	std::string tex;
	float scale = 1.8f;
	std::string node_class = "vertex";
	std::string edge_class = "edge";
	tex += "\\begin{tikzpicture}[scale="+std::to_string(scale)+", auto,swap]\n";

	for ( uint i = 0 ; i < location_.size() ; ++i ) {
		const Vector<float>& location = location_[i];
		std::string x = std::to_string(location[0]);
		std::string y = std::to_string(location[1]);
		std::string index = std::to_string(i+1);
		tex += "\t\\node["+node_class+"] ("+index+") at ("+x+","+y+") {};\n";
	}

	// Adding edge weights.
	for (int i = 0; i < adjacency_.rows(); ++i) {
		std::string source = std::to_string(i+1);
		for (int j = 0; j < adjacency_.cols(); ++j) {
			std::string target = std::to_string(j+1);
			if (graph_type_ == GraphType::UNDIRECTED && j <= i)
				continue;
			float weight = adjacency_(i, j);
			if (weight > 0 and weight < INFINITY) {
				tex += "\t\\path["+edge_class+"] ("+source+") -- ("+target+");\n";
			}
		}
	}
	tex += "\\end{tikzpicture}\n";
	return tex;
}

AdjacencyGraph::~AdjacencyGraph() {
}

} /* namespace n1graph */
