#include <iostream>
#include "EdgeList.h"

std::vector<std::string> EdgeList::vertices() const{
    std::vector<std::string> vertices;
    for(const std::string &s: Vertices)
        vertices.push_back(s);
    return vertices;
}

std::vector<std::string> EdgeList::edges() const{
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::pair<std::string, std::string>> &pair: Edges)
        edges.emplace_back(pair.first);
    return edges;
}

std::pair<std::string, std::string> EdgeList::endVertices(const std::string& edge){
    auto it = Edges.find(edge);
    if(it == Edges.end())
        throw std::logic_error(edge + " edge doesn't exist");
    return it->second;
}

std::vector<std::string> EdgeList::outgoingEdges(const std::string& vertex){
    std::vector<std::string> outgoingEdges;
    for(const std::pair<const std::string, std::pair<std::string, std::string>> &pair: Edges)
        if(pair.second.first == vertex || pair.second.second == vertex)
            outgoingEdges.emplace_back(pair.first);
    return outgoingEdges;
}

std::vector<std::string> EdgeList::incomingEdges(const std::string& vertex){
    return outgoingEdges(vertex);
}

std::string EdgeList::getEdge(const std::string& vertex1, const std::string& vertex2){
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges)
        if((pair.second.first == vertex1 || pair.second.first == vertex2) &&
            (pair.second.second == vertex1 || pair.second.second == vertex2))
            return pair.first;
    return "";
}

std::vector<std::string> EdgeList::opposite(const std::string& vertex){
    std::vector<std::string> oppositeVertices;
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges) {
        if (pair.second.first == vertex)
            oppositeVertices.emplace_back(pair.second.second);
        else if(pair.second.second == vertex)
            oppositeVertices.emplace_back(pair.second.first);
    }
    return oppositeVertices;
}

void EdgeList::addVertex(const std::string& name){
    Vertices.insert(name);
}

void EdgeList::addEdge(const std::string& name, const std::string& vertex1, const std::string& vertex2){
    if(Edges.contains(name))
        throw std::logic_error(name + " edge already exists\n");
    else if(!Vertices.contains(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!Vertices.contains(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    else
        Edges.insert({name, {vertex1, vertex2}});
}

void EdgeList::removeVertex(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        Vertices.erase(iterator);
        for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges)
            if(pair.second.first == vertex || pair.second.second == vertex)
                Edges.erase(pair.first);
    }else throw std::logic_error("Vertex doesn't exist\n");
}

void EdgeList::removeEdge(const std::string& edge){
    auto iterator = Edges.find(edge);
    if(iterator != Edges.end())
        Edges.erase(iterator);
    else
        throw std::logic_error("Edge doesn't exist\n") ;
}

int EdgeList::numVertices(){
    return Vertices.size();
}

int EdgeList::numEdges(){
    return Edges.size();
}

int EdgeList::outDegree(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        int numOutDegree = 0;
        for(const std::pair<const std::string,std::pair<std::string, std::string> >& pair: Edges)
            if(pair.second.first == vertex || pair.second.second == vertex)
                numOutDegree++;
        return numOutDegree;
    }
    return -1;
}

int EdgeList::inDegree(const std::string& vertex){
    return outDegree(vertex);
}

bool EdgeList::containEdge(const std::string& edge) const{
    return Edges.contains(edge);
}
bool EdgeList::containVertex(const std::string& vertex) const{
    return Vertices.contains(vertex);
}

std::ostream& operator<<(std::ostream& os, EdgeList* edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList->Vertices)
        os << " " << s;
    os << "\nEdges:\n";
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: edgeList->Edges)
        os << "Name: " << pair.first << "\t" << pair.second << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, EdgeList& edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList.Vertices)
        os << " " << s;
    os << "\nEdges:\n";
    for(const std::pair<const std::string, Edge*>& pair: edgeList.Edges)
        os << "Name: " << pair.first << "\t" << pair.second << '\n';
    return os;
}

EdgeList::~EdgeList(){
    Vertices.clear();
    for(const std::pair<const std::string, Edge*>& pair: Edges)
        delete pair.second;
    Edges.clear();
}