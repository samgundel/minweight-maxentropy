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

#include <cmath>

#include <gflags/gflags.h>
#include <glog/logging.h>

#include <adjacency_graph.hpp>
#include <csv_reader.hpp>
#include <matching.hpp>
#include <n1graph.hpp>
#include <text_writer.hpp>
#include <vector.hpp>

using n1graph::AdjacencyGraph;
using n1graph::CSVReader;
using n1graph::GraphType;
using n1graph::Matching;
using n1graph::N1Graph;
using n1graph::TextWriter;
using n1graph::Vector;

AdjacencyGraph CreateRegularGraph(int n) {
	/***********
	 * 4 Nodes *
	 ***********/
	AdjacencyGraph adj(n, GraphType::UNDIRECTED, 0.f);

	float radius = 1.f;
	float angle = 360.f / n;
	for (int i = 0; i < n; ++i) {
		float radian_angle = i * angle * M_PI / 180;
		float x = radius * cos(radian_angle);
		float y = radius * sin(radian_angle);
		adj.SetLocation(i, Vector<float>(x, y));
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			adj.AddEuclideanWeightedEdge(i, j);
		}
	}
	return adj;
}

AdjacencyGraph CreateGraph(std::vector<Vector<float> > points) {
	AdjacencyGraph adj(points.size(), GraphType::UNDIRECTED, 0.f);
	for (int i = 0; i < points.size(); ++i) {
		adj.SetLocation(i, points[i]);
	}
	for (int i = 0; i < points.size(); ++i) {
		for (int j = i + 1; j < points.size(); ++j) {
			adj.AddEuclideanWeightedEdge(i, j);
		}
	}
	return adj;
}

int main(int argc, char **argv) {
	google::InitGoogleLogging(argv[0]);
	if (argc < 3) {
		LOG(WARNING) << "We expect two points sets to be informed.";
		return -1;
	}
	std::string result_location1 = "graph_result1.csv";
	std::string result_location2 = "graph_result2.csv";
	std::string tikz_location = "graph_result.tex";
	AdjacencyGraph graph_a, graph_b;
	N1Graph g_a, g_b;
	LOG(INFO)<< "Building Graph.";
	if (argc > 2) {
		graph_a = CreateGraph(CSVReader::ReadCSV(argv[1], ','));
		graph_b = CreateGraph(CSVReader::ReadCSV(argv[2], ','));
		LOG(INFO)<< "Minimizing Cost Function.";
		g_a.Minimize(graph_a);
		g_b.Minimize(graph_b);
		Matching matching;
		matching.Register(g_a,g_b);
		Vector<float> gap(25, 0);
		LOG(INFO)<< "Writing Results.";
		TextWriter::Write(result_location1, g_a.result().ToString());
		TextWriter::Write(result_location2, g_b.result().ToString());
        TextWriter::Write(tikz_location, matching.ToTikz(g_a, g_b, gap, 1));
		LOG(INFO)<< "Run Visualization.";
	} else {
		graph_a = CreateRegularGraph(std::atoi(argv[1]));
		g_a.Minimize(graph_a);
		TextWriter::Write(tikz_location, g_a.result().ToTikz());
	}
	system("python visualize.py graph_result1.csv graph_result2.csv");
	return 0;
}
