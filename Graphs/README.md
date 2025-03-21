# Graph ADT
### Due to costly maintenance, I decided to drop this data structure


* _**addEdge** (name, vertex1, vertex2)_: Add edge with its name and its two vertices


* _**addVertex** (name)_: Add vertex with its name


* _**containEdge** (edge)_: Returns a boolean if an edge is present or not;


* _**containVertex** (vertex)_:Returns a boolean value if a vertex is present or not;


* <i>**numVertices** ( )</i>: Returns the number of vertices of the graph.


* <i>**vertices** ( )</i>: Returns an iteration of all the vertices of the graph.


* <i>**numEdges** ( )</i>: Returns the number of edges of the graph.


* <i>**edges** ( )</i>: Returns an iteration of all the edges of the graph.


* <i>**getEdge** (u, v)</i>: Returns the edge from vertex u to vertex v, if one
exists; otherwise return null. For an undirected graph, there is no
difference between _**getEdge** (u, v)_ and _**getEdge** (v, u)_.


* <i>**endVertices** (e)</i>: Returns an array containing the two endpoint vertices
of edge e. If the graph is directed, the first vertex is the origin and the
second is the destination.


* <i>**opposite** (v, e)</i>: For edge e incident to vertex v, returns the other
vertex of the edge; an error occurs if e is not incident to v.

  
* <i>**outDegree** (v)</i>: Returns the number of outgoing edges from vertex v.


* <i>**inDegree** (v)</i>: Returns the number of incoming edges to vertex v. For
an undirected graph, this returns the same value as does
_**outDegree** (v)._


* _**outgoingEdges** (v)_: Returns an iteration of all outgoing edges from
vertex v.


* _**incomingEdges** (v)_: Returns an iteration of all incoming edges to
vertex v. For an undirected graph, this returns the same collection as
does _**outgoingEdges** (v)_.

TODO:\
~~Implement various templates specified for different data types~~ FIXED