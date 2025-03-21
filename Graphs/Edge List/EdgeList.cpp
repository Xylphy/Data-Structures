#include "EdgeList.h"

#include <functional>
#include <set>

namespace Graph
{

	template <typename V, typename E>

	template <typename V, typename E>
	std::vector<E> *EdgeList<V, E>::edges() const
	{
		auto *edges = new std::vector<E>;

		std::transform(_edges->begin(), _edges->end(), std::back_inserter(*edges),
					   [](const Edge &edge) -> E { return edge.edgeName; });

		return edges;
	}

	template <typename V, typename E>
	std::vector<std::pair<V, V>> *EdgeList<V, E>::endVertices(const E &edge) const
	{
		auto *vertices = new std::vector<std::pair<V, V>>;

		std::for_each(_edges->begin(), _edges->end(),
					  [&vertices, &edge](const Edge &e) -> void
					  {
						  if (edge == e.edgeName)
							  vertices->emplace_back(e.vertex1, e.vertex2);
					  });

		return vertices;
	}

	template <typename V, typename E>
	std::vector<E> *EdgeList<V, E>::outgoingEdges(const V &vertex) const
	{
		auto *outgoingEdges = new std::vector<E>();

		std::for_each(_edges->begin(), _edges->end(),
					  [&outgoingEdges, &vertex](const Edge &e) -> void
					  {
						  if (e.vertex1 == vertex)
							  outgoingEdges->emplace_back(e.edgeName);
					  });

		return outgoingEdges;
	}

	template <typename V, typename E>
	std::vector<E> *EdgeList<V, E>::incomingEdges(const V &vertex) const
	{
		auto *incomingEdges = new std::vector<E>();

		std::for_each(_edges->begin(), _edges->end(),
					  [&incomingEdges, &vertex](const Edge &e) -> void
					  {
						  if (e.vertex2 == vertex)
							  incomingEdges->emplace_back(e.edgeName);
					  });

		return incomingEdges;
	}

	template <typename V, typename E>
	E EdgeList<V, E>::getEdge(const V &vertex1, const V &vertex2) const
	{
		for (const Edge &edges : *_edges)
			if (edges.vertex1 == vertex1 && edges.vertex2 == vertex2)
				return edges.edgeName;

		return {};
	}

	template <typename V, typename E>
	std::vector<E> *EdgeList<V, E>::unique_edge() const
	{
		std::set<E> edgeSet;
		auto *unique_edges = new std::vector<E>();

		std::for_each(_edges->begin(), _edges->end(),
					  [&unique_edges, &edgeSet](const Edge &edges) -> void
					  {
						  if (edgeSet.find(edges.edgeName) == edgeSet.end())
						  {
							  unique_edges->emplace_back(edges.edgeName);
							  edgeSet.insert(edges.edgeName);
						  }
					  });

		return unique_edges;
	}

	template <typename V, typename E>
	std::vector<V> *EdgeList<V, E>::opposite(const V &vertex) const
	{
		auto *oppositeVertices = new std::vector<V>();

		std::for_each(_edges->begin(), _edges->end(),
					  [&oppositeVertices, &vertex](const Edge &edge) -> void
					  {
						  if (edge.vertex1 == vertex)
							  oppositeVertices->emplace_back(edge.vertex2);
					  });

		return oppositeVertices;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::addVertex(const V &vertex)
	{
		if (std::find(_vertices->begin(), _vertices->end(), vertex) != _vertices->end())
			throw std::logic_error(vertex + " vertex already exists\n");

		_vertices->emplace_back(vertex);

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::add_directed_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{

		std::function<bool(V)> lambda = [&vertex1, &vertex2](const V &vertex) -> bool
		{ return vertex1 == vertex || vertex2 == vertex; };

		typename std::list<V>::iterator _vertices_iterator = std::find_if(_vertices->begin(), _vertices->end(), lambda);

		if (std::find_if(_vertices_iterator, _vertices->end(), lambda) == _vertices->end())
			throw std::logic_error("vertex doesn't exists\n");

		_edges->emplace_back(edge, vertex1, vertex2);

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::add_bidirected_Edge(const E &edge, const V &vertex1, const V &vertex2)
	{

		std::function<bool(V)> lambda = [&vertex1, &vertex2](const V &vertex) -> bool
		{ return vertex1 == vertex || vertex2 == vertex; };

		typename std::list<V>::iterator _vertices_iterator = std::find_if(_vertices->begin(), _vertices->end(), lambda);

		if (std::find_if(_vertices_iterator, _vertices->end(), lambda) == _vertices->end())
			throw std::logic_error("vertex doesn't exists\n");

		_edges->emplace_back(edge, vertex1, vertex2);
		_edges->emplace_back(edge, vertex2, vertex1);

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::removeVertex(const V &vertex)
	{
		typename std::list<E>::iterator iterator = std::find(_vertices->begin(), _vertices->end(), vertex);

		if (iterator == _vertices->end())
			return *this;

		_vertices->erase(iterator);

		_edges->remove_if([&vertex](const Edge &edge) -> bool
						  { return edge.vertex1 == vertex || edge.vertex2 == vertex; });

		return *this;
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::removeEdge(const E &edge)
	{

		_edges->remove_if([&edge](const Edge &_edge) -> bool { return _edge.edgeName == edge; });

		return *this;
	}

	template <typename V, typename E>
	size_t EdgeList<V, E>::numVertices() const
	{
		return _vertices->size();
	}

	template <typename V, typename E>
	size_t EdgeList<V, E>::numEdges() const
	{
		return _edges->size();
	}

	template <typename V, typename E>
	size_t EdgeList<V, E>::outDegree(const V &vertex) const
	{
		if (!containVertex(vertex))
			throw std::logic_error(vertex + " vertex doesn't exist\n");

		std::vector<E> *outEdges = outgoingEdges(vertex);
		const size_t outDegree = outEdges->size();
		delete outEdges;
		return outDegree;
	}

	template <typename V, typename E>
	size_t EdgeList<V, E>::inDegree(const V &vertex) const
	{
		if (!containVertex(vertex))
			throw std::logic_error(vertex + " vertex doesn't exist\n");

		std::vector<E> *inEdges = incomingEdges(vertex);
		const size_t inDegree = inEdges->size();
		delete inEdges;
		return inDegree;
	}

	template <typename V, typename E>
	bool EdgeList<V, E>::containEdge(const E &edge) const
	{
		return std::find_if(_edges->begin(), _edges->end(),
							[&edge](const Edge &e) -> bool { return edge == e.edgeName; }) != _edges->end();
	}

	template <typename V, typename E>
	bool EdgeList<V, E>::containVertex(const V &vertex) const
	{
		return std::find_if(_vertices->begin(), _vertices->end(),
							[&vertex](const V &v) -> bool { return vertex == v; }) != _vertices->end();
	}

	template <typename V, typename E>
	GraphAbstract<V, E> &EdgeList<V, E>::print(std::ostream &ostream)
	{
		ostream << "Vertices:";
		for (const V &s : *_vertices)
			ostream << " " << s;
		ostream << "\nEdges:\n";
		for (const Edge &edge : *_edges)
			ostream << "Name: " << edge.edgeName << " <" << edge.vertex1 << ", " << edge.vertex2 << ">\n";

		return *this;
	}

	template <typename V, typename E>
	EdgeList<V, E>::~EdgeList()
	{
		delete _vertices;
		delete _edges;
	}


} // namespace Graph
