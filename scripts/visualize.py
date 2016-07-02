import igraph
import sys
from math import log

if __name__ == '__main__':
	if len(sys.argv) < 2:
		print '\ncall:\n\tpython visualize.py graph1.csv graph2.csv\n'
		exit(1)
	graph_1 = open(sys.argv[1],'r').readlines()
	graph_2 = open(sys.argv[2],'r').readlines()
	n,directed_1 = map(int,graph_1[0].split(','))
	n,directed_2 = map(int,graph_2[0].split(','))
	nodes_1 = [map(float,i[:-1].split(',')) for i in graph_1[1:1+n]]
	nodes_2 = [map(float,i[:-1].split(',')) for i in graph_2[1:1+n]]
	edges_1 = [map(float,i[:-1].split(',')) for i in graph_1[n+1:]]
	edges_2 = [map(float,i[:-1].split(',')) for i in graph_2[n+1:]]
	w = []
	pts_1, pts_2 = [],[]
	g1 = igraph.Graph()
	if ( directed_1 ):
		g1.to_directed()
	gap = max([i[0] for i in nodes_1])
	for i in range(1,n):
		g1.add_vertex(i)
		g1.add_vertex(n+i)
		pts_1.append(tuple([nodes_1[i][0],-nodes_1[i][1]]))
		pts_2.append(tuple([gap+nodes_2[i][0],-nodes_2[i][1]]))
	for i in range(1,n):
		g1.add_edge(pts_1.index(i),n+pts_2.index(i))
	pts_1.extend(pts_2)
	style = {}
	style["layout"] = pts_1
	style["bbox"] = (200*log(n),200*log(n))
	style["vertex_color"] = [p.get(i) for i in measure]
	igraph.plot(g1,**style)
		


