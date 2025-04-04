#ifndef DATA_STRUCTURES_ADJACENCYMAP_H
#define DATA_STRUCTURES_ADJACENCYMAP_H

#include "../General Graph/GraphAbstract.h"

namespace Graph {

    template<typename V, typename E>
    class AdjacencyMap final : public GraphAbstract<V, E> {
        
        // STARTING POINT

        GraphAbstract<V, E> &print(std::ostream &ostream) override;

    public:
        std::vector<V> vertices() const override;

        std::vector<E> edges() const override;

        std::pmr::vector<std::pair<V, V>> endVertices(const E &edge) override;

        std::vector<E> outgoingEdges(const V &vertex) override;

        std::vector<E> incomingEdges(const V &vertex) override;

        E getEdge(const V &vertex1, const V &vertex2) override;

        std::vector<V> opposite(const V &vertex) override;

        GraphAbstract<V, E> &addVertex(const V &vertex) override;

        GraphAbstract<V, E> &addEdge(const E &edge, const V &vertex1, const V &vertex2) override;

        GraphAbstract<V, E> &removeVertex(const V &vertex) override;

        GraphAbstract<V, E> &removeEdge(const E &edge) override;

        bool containEdge(const E &edge) const override;

        bool containVertex(const V &vertex) const override;

        size_t numVertices() override;

        size_t numEdges() override;

        size_t outDegree(const V &vertex) override;

        size_t inDegree(const V &vertex) override;
    };
}

#include "AdjacencyMap.cpp"

#endif //DATA_STRUCTURES_ADJACENCYMAP_H
