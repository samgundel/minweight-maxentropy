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

#include <n1graph.hpp>

#include <algorithm>
#include <tuple>
#include <vector>

#include <adjacency_graph.hpp>

namespace n1graph {

N1Graph::N1Graph() {

}

N1Graph::~N1Graph() {
}

bool edge_sorting(const std::tuple<float, int, int>& first,
		const std::tuple<float, int, int>& second) {
	return std::get < 0 > (first) <= std::get < 0 > (second);
}

float JoinIsolate(const AdjacencyGraph& input, int reference_node,
		int latest_node) {
	return input.adjacency()(reference_node, latest_node);
}

float JoinGraph(const AdjacencyGraph& input, int latest_node,
		int const * used_nodes) {
	float cost = 0;
	for (int i = 0; i < input.NumberOfNodes(); ++i) {
		if (used_nodes[i] == 1) {
			cost += input.adjacency()(latest_node, i);
		}
	}
	return cost;
}

std::vector<int> N1Graph::TraceBack(const Matrix<float>& dp, int layer) {
	Vector<int> location(dp.rows() - 1, dp.cols() - 1, layer);
	// We trace back to add the correct edges and reconstruct the graph.
	std::vector<int> nodes;
	// While we haven't reached the first row.
	while (location[0] > 0) {
		Vector<int> left = location;
		left[1] -= 1;
		// We trace only to the left until the neighbors differ.
		while (left[1] >= 0 && dp(location) == dp(left)) {
			location[1] -= 1;
			left[1] -= 1;
		}
		// Once we found out that the value changed from the right to the left
		// cell. It means we added a node. Move up.
		location[0] -= 1;
		// If we are in the first col, it means that we have to start in the
		// last col of the row up, otherwise, we decrement it.
		if (location[1] > 0) {
			nodes.push_back(location[1]);
			location[1] -= 1;
		} else {
			nodes.push_back(0);
			location[1] = dp.cols() - 1;
		}
	}
	// Finally we add the first node which is the same as the level.
	nodes.push_back(location[2]);
	std::reverse(nodes.begin(), nodes.end());
	std::string nodes_str = "";
	for (int node : nodes) {
		nodes_str += std::to_string(node);
		nodes_str += ",";
	}
	LOG(INFO)<< "[BackTrace] " <<nodes_str;
	return nodes;
}

void N1Graph::BuildGraph(const std::vector<int>& nodes) {
	CHECK_GT(nodes.size(), 2);
	result_.AddEdge(nodes[0], nodes[1]);

	bool join_graph = true;
	int max_iterations = nodes.size() / 2 * 2;
	for (int i = 2; i < (nodes.size()/2)*2; ++i) {
		if (join_graph) {
			// Join.
			for (int j = 0; j < i; ++j) {
				result_.AddEdge(nodes[j], nodes[i]);
			}
		} else {
			// Isolated.
			result_.AddEdge(nodes[i], nodes[i-1]);
		}
		join_graph = !join_graph;
	}
}

int N1Graph::FindOptimalLayer(const Matrix<float>& dp) {
	Vector<int> location(dp.rows() - 1, dp.cols() - 1, dp.channels() - 1);
	float optimum = dp(location);
	while (dp(location) == optimum) {
		// We move one layer up to check when the maximum was obtained.
		location[2] -= 1;
		if (location[2] < 0)
			break;
	}
	// The current layer was the one with higher cost, therefore, the layer
	// immediately below has the optimum solution.
	return location[2] + 1;
}

void N1Graph::Minimize(const AdjacencyGraph& input) {
	size_t n = input.NumberOfNodes();
	result_.Initialize(n, GraphType::UNDIRECTED, 0);
	for (int i = 0; i < input.NumberOfNodes(); ++i) {
		result_.SetLocation(i, input.location(i));
	}

	Matrix<float> dp(n, n, n, 0);
	std::unique_ptr<int[]> used_nodes(new int[n]);

	float best_cost = std::numeric_limits<float>::max();
	std::vector<int> best_nodes;

	// For each initial node being selected.
	for (int i = 0; i < n; ++i) {
		std::vector<int> node_list;
		memset(used_nodes.get(), 0, n * sizeof(int));
		used_nodes[i] = 1;
		// Our algorithm alternates two steps, either join graph or join
		// isolated node.
		bool join_graph = false;
		// Every time a node succeeds to improve the objective function, we
		// record it.
		int latest_node = i;
		// For which number of allowed nodes. In that case, we allow k+1 nodes.
		// The first iteration means the the optimum with 2 nodes are allowed
		// (k+1).
		for (int k = 1; k < n; ++k) {
			node_list.push_back(i);
			// We have to accept the first cost found with the new node.
			bool accept = true;
			// By adding the j node to the graph, we calculate the
			// new cost.
			int candidate_latest = -1;
			for (int j = 0; j < n; ++j) {
				// Updating previous cost.
				//float previous_cost = j > 0 ? dp(k, j - 1, i) : INFINITY;
				float previous_cost = dp(k, std::max(0, j - 1), i);
				// New cost is at least the best cost found in the previous
				// iteration.
				float new_cost = dp(k - 1, n - 1, i);
				// If the node has been used already, nothing to do here.
				if (used_nodes[j] == 1) {
					dp(k, j, i) = previous_cost;
					continue;
				} else {
					// Updating new cost.
					if (join_graph)
						new_cost += JoinGraph(input, j, used_nodes.get());
					else
						new_cost += JoinIsolate(input, j, latest_node);
					// If the accept flag is true, it means We don't have any
					// cost yet with k nodes. We must accept this one and later
					// optimize over the possible alternatives.
					if (accept || new_cost < previous_cost) {
						dp(k, j, i) = new_cost;
						// In case this is true, it means we have already added
						// a candidate there.
						if ( node_list.size() == k + 1)
							node_list.pop_back();
						node_list.push_back(j);
						candidate_latest = j;
						accept = false;
					} else {
						dp(k, j, i) = previous_cost;
					}
				}
			}
			CHECK_GE(candidate_latest, 0);
			latest_node = candidate_latest;
			used_nodes[latest_node] = 1;
			join_graph = !join_graph;
		}
		if ( dp(n - 1, n - 1, i) < best_cost ) {
			best_cost = dp(n - 1, n - 1, i);
			best_nodes = node_list;
		}
		node_list.clear();
		// We push the solution towards the corner of the hypercube. Since the
		// location (n,n) holds the optimum for that layer, we force the next
		// layer to be at least as good as the previous one.
		dp(n - 1, n - 1, i) = std::min(dp(n - 1, n - 1, i),
				dp(n - 1, n - 1, std::max(0, i - 1)));
	}
//	int optimum_layer = FindOptimalLayer(dp);
	CHECK_EQ(best_nodes.size(),input.NumberOfNodes());
	BuildGraph(best_nodes);
}

}  /* namespace n1graph */
