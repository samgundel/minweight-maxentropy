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

#include "matching.hpp"

#include <cstdlib>
#include <cstring>

namespace n1graph {

Matching::Matching() :
		number_of_points(0) {

}

void Matching::Register(const N1Graph& g1, const N1Graph& g2) {
	LOG(INFO) << "Registering Point sets";
	CHECK_GT(g1.result().NumberOfNodes(), 2);
	CHECK_EQ(g1.result().NumberOfNodes(), g2.result().NumberOfNodes());
	number_of_points = g1.result().NumberOfNodes();
	g1_mapping.reset(new int[number_of_points]);
	g2_mapping.reset(new int[number_of_points]);
	g1_reverse_mapping.reset(new int[number_of_points]);
	g2_reverse_mapping.reset(new int[number_of_points]);

	memset(g1_mapping.get(), 0, number_of_points * sizeof(int));
	memset(g2_mapping.get(), 0, number_of_points * sizeof(int));
	memset(g1_reverse_mapping.get(), 0, number_of_points * sizeof(int));
	memset(g2_reverse_mapping.get(), 0, number_of_points * sizeof(int));

	// If we have an isolated node.
	bool isolated = g1.result().NumberOfNodes() & 1;
	LOG(INFO) << "Registering Point sets";
	for (int i = 0; i < g1.result().NumberOfNodes(); ++i) {
		int degree_1 = (int) g1.result().adjacency().row_sum(i);
		int degree_2 = (int) g2.result().adjacency().row_sum(i);
		LOG(INFO) << i << " "<< degree_1 - 1 << " " << degree_2 - 1;
		if (!isolated) {
			g1_mapping[i] = degree_1 - 1;
			g1_reverse_mapping[degree_1 - 1] = i;
			g2_mapping[i] = degree_2 - 1;
			g2_reverse_mapping[degree_2 - 1] = i;
		}
	}
	LOG(INFO) << "Mapping";
	for (int i = 0; i < g1.result().NumberOfNodes(); ++i) {
		LOG(INFO) << i << " "<< g1_mapping[i] << " " << g2_mapping[i];
	}
}

int Matching::Correspondence(int graph, int point) {
	CHECK_GE(graph, 0);
	CHECK_LT(graph, 2);
	CHECK_GE(point, 0);
	CHECK_LT(point, number_of_points);
	CHECK_NOTNULL(g1_mapping.get());
	CHECK_NOTNULL(g2_mapping.get());
	if ( graph == 0 ) {
		int g1_node = g1_mapping[point];
		return g2_reverse_mapping[g1_node];
	}else
		return 0;
}

std::string Matching::ToTikz(const N1Graph& g1, const N1Graph& g2,
		const Vector<float>& gap, float edge_percentage) const {
	LOG(INFO) << "Generating Tex Code";
	CHECK_EQ(g1.result().NumberOfNodes(), g2.result().NumberOfNodes());
	CHECK_GE(edge_percentage, 0);
	CHECK_LE(edge_percentage, 1);
	CHECK_NOTNULL(g1_mapping.get());
	CHECK_NOTNULL(g2_mapping.get());
	std::string tex;
	float scale = 0.8f;
	std::string g1_node_class = "g1";
	std::string g2_node_class = "g2";
	std::string edge_class = "edge";
	std::string node_size = "25";
	// Tikz classes.
	tex += "\\tikzstyle{" + g1_node_class
			+ "}=[circle,draw,fill=red!25,minimum size=" + node_size
			+ "pt,inner sep=0pt]\n";
	tex += "\\tikzstyle{" + g2_node_class
			+ "}=[circle,draw,fill=blue!25,minimum size=" + node_size
			+ "pt,inner sep=0pt]\n";

	tex += "\\tikzstyle{"+edge_class+"} = [draw,thick,-]\n";

	// Beginning the picture.
	tex += "\\begin{tikzpicture}[scale=" + std::to_string(scale)
			+ ", auto,swap]\n";

	for (uint i = 0; i < g1.result().NumberOfNodes(); ++i) {
		const Vector<float>& location_1 = g1.result().location(i);
		const Vector<float>& location_2 = g2.result().location(i);
		std::string x_1 = std::to_string(location_1[0]/10);
		std::string y_1 = std::to_string(location_1[1]/10);
		std::string x_2 = std::to_string(gap[0] + location_2[0]/10);
		std::string y_2 = std::to_string(gap[1] + location_2[1]/10);
		std::string index_1 = std::to_string(g1_mapping[i]) + "a";
		std::string index_2 = std::to_string(g2_mapping[i]) + "b";
		tex += "\t\\node[" + g1_node_class + "] (" + index_1 + ") at (" + x_1
				+ "," + y_1 + ") {};\n";
		tex += "\t\\node[" + g2_node_class + "] (" + index_2 + ") at (" + x_2
				+ "," + y_2 + ") {};\n";
	}

	int edges_to_draw = g1.result().NumberOfNodes() * edge_percentage;

	for (int i = 0; i < edges_to_draw; ++i) {
		if (g1_mapping[i] == g1.result().NumberOfNodes()/2)
			continue;
		std::string source = std::to_string(g1_mapping[i])+"a";
		std::string target = std::to_string(g1_mapping[i])+"b";
		LOG(INFO) <<"Na posicao "<<i<< " tem o grau "<<source << " e o mapped to " << target;
		tex += "\t\\path[" + edge_class + "] (" + source + ") -- (" + target
				+ ");\n";
	}

	tex += "\\end{tikzpicture}\n";
	return tex;
}

Matching::~Matching() {
	// TODO Auto-generated destructor stub
}

} /* namespace n1graph */
