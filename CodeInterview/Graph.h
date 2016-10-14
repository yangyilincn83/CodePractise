#pragma once

#include <iostream>
#include <cassert>

using namespace std;

namespace DataStructure
{
    namespace AdjacencyMatrixGraph
    {
        const int NOEDGE = -1;
        typedef int* Edge;

        class Graph
        {
        private:
            int mumOfVertices;
            int numOfEdges;
            int* matrix;
            bool* mark;

        public:
            Graph()
            {
                matrix = nullptr;
                mark = nullptr;

                // initialize matrix and mark array
            }

            ~Graph()
            {
                if (mark != nullptr)
                {
                    delete[] mark;
                }

                if (matrix != nullptr)
                {
                    delete[] matrix;
                }
            }

            int n()
            {
                return mumOfVertices;
            }

            int e()
            {
                return numOfEdges;
            }

            int v1(Edge edge)
            {
                assert(edge != nullptr);
                return (edge - matrix) / mumOfVertices;
            }

            int v2(Edge edge)
            {
                assert(edge != nullptr);
                return (edge - matrix) % mumOfVertices;
            }

            bool IsEdge(int v1, int v2)
            {
                return (matrix[v1 * mumOfVertices + v2] != NOEDGE);
            }

            int weight(Edge edge)
            {
                if (*edge == NOEDGE)
                {
                    return INFINITY;
                }
                else
                {
                    return *edge;
                }
            }

            int weight(int v1, int v2)
            {
                if (matrix[v1 * mumOfVertices + v2] != NOEDGE)
                {
                    return matrix[v1 * mumOfVertices + v2];
                }
                else
                {
                    return INFINITY;
                }
            }

            Edge first(int v1)
            {
                for (int i = 0; i < mumOfVertices; i++)
                {
                    if (matrix[v1*mumOfVertices + i] != NOEDGE)
                    {
                        return matrix + v1*mumOfVertices + i;
                    }
                }

                return nullptr;
            }

            Edge next(Edge edge)
            {
                assert(edge != nullptr);
                int v = v1(edge);
                for (int i = v2(edge); i < mumOfVertices; i++)
                {
                    if (matrix[v*mumOfVertices + i] != NOEDGE)
                    {
                        return matrix + v * mumOfVertices + i;
                    }
                }

                return nullptr;
            }
        };
    }

    namespace AdjacentListGraph
    {
        class LinkedEdge
        {
        public:
            int v1;
            int v2;
            int weight;
            LinkedEdge* next;

            LinkedEdge(int v1, int v2, LinkedEdge* next = nullptr)
            {
                this->v1 = v1;
                this->v2 = v2;
                this->next = next;
            }

            LinkedEdge(LinkedEdge* next = nullptr)
            {
                this->next = next;
            }
        };

        typedef LinkedEdge* Edge;

        class Graph
        {
        private:
            Edge* list;
            int numOfVertices;
            int numOfEdges;
            bool* mark;

        public:
            Graph()
            {
                list = nullptr;
                mark = nullptr;

                // initialize list and mark array
            }

            ~Graph()
            {
                if (mark != nullptr)
                {
                    delete[] mark;
                }

                if (list != nullptr)
                {
                    for (int v = 0; v < numOfVertices; v++)
                    {
                        Edge edge = list[v];
                        while (list[v] != nullptr)
                        {
                            Edge temp = list[v];
                            list[v] = list[v]->next;
                            delete temp;
                        }
                    }

                    delete[] list;
                }
            }

            int v1(Edge edge)
            {
                assert(edge != nullptr);
                return edge->v1;
            }

            int v2(Edge edge)
            {
                assert(edge != nullptr);
                return edge->v2;
            }

            int weight(Edge edge)
            {
                assert(edge != nullptr);
                return edge->weight;
            }

            int weight(int v1, int v2)
            {
                for (Edge e = list[v1]; e != nullptr; e = e->next)
                {
                    if (e->v2 == v2)
                    {
                        return e->weight;
                    }
                }

                return INFINITY;
            }

            Edge first(int v1)
            {
                return list[v1];
            }

            Edge next(Edge edge)
            {
                assert(edge != nullptr);
                return edge->next;
            }

            bool IsEdge(int v1, int v2)
            {
                for (Edge e = list[v1]; e != nullptr; e = e->next)
                {
                    if (e->v2 == v2)
                    {
                        return true;
                    }
                }

                return false;
            }

            int n()
            {
                return numOfVertices;
            }

            int e()
            {
                return numOfEdges;
            }
        };
    }
}