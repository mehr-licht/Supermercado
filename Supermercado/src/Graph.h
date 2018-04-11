
#ifndef GRAPH_H_
#define GRAPH_H_

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <list>
#include <limits.h>
#include <stack>
#include <math.h>
#include "Client.h"
#include "Menu.h"
using namespace std;

template<class T> class Edge;
template<class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template<class T>
class Vertex {
	T info;

	bool visited;
	bool processing;
	int indegree;
	double dist;

public:


	vector<Edge<T> > adj;
	Vertex(T in);
	friend class Graph<T> ;

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	//bool operator<(const Vertex<T> vertex);
	int getNumEdges();
	Vertex* path;

	vector<Edge<T> > getAdj();
};


template<class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}
template<class T>
int Vertex<T>::getNumEdges() {
	return adj.size();
}
;

template<class T>
Vertex<T>::Vertex(T in) :
		info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest, w);
	adj.push_back(edgeD);
}

//--
template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
int Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template<class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template<class T>
vector<Edge<T> > Vertex<T>::getAdj() {
	return adj;
}
/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template<class T>
class Edge {
	Vertex<T> * dest;

public:
	double weight;
	Edge(Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;
	double getWeight();
	Vertex<T>* getNode();
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

template<class T>
double Edge<T>::getWeight() {
	return this->weight;
}

template<class T>
Vertex<T>* Edge<T>::getNode() {
	return this->dest;
}
/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	Graph getInvertedGraph();
	bool isStronglyConnected();

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s, double &total);

	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);

	//added for project
	//long long getWeight(const T &source, const T &dest);

	vector<long long> getOurRoute(long long firstNode, vector<long long> stops,
			long long endNode, double &total);
};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template<class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template<class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj = v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	long long found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vD->indegree++;
	vS->addEdge(vD, w);

	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	long long found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}

template<class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			//cout << "ok ";
			dfs(it->dest, res);
		}
}

template<class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<long long> level;
	long long maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		long long l = level.front();
		level.pop();
		l++;
		long long nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}

template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector<Vertex<T>*> buffer;
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->indegree == 0)
			buffer.push_back(vertexSet[i]);
	}
	return buffer;
}

template<class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true)
			numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	vector<T> res;

	//verificar se � um DAG
	if (getNumCycles() > 0) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!q.empty()) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if (v->adj[i].dest->indegree == 0)
				q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexSet.size()) {
		while (!res.empty())
			res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) {

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	buffer.push_front(v->info);
	while (v->path != NULL && v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if (v->path != NULL)
		buffer.push_front(v->path->info);

	vector<T> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest) {

	int originIndex = -1, destinationIndex = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == origin)
			originIndex = i;
		if (vertexSet[i]->info == dest)
			destinationIndex = i;

		if (originIndex != -1 && destinationIndex != -1)
			break;
	}

	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1) {
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}
	res.push_back(vertexSet[destinationIndex]->info);
	return res;
}

template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2,
		vector<T> & res) {
	if (P[index1][index2] != -1) {
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2], index2, res);
	}
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue<Vertex<T>*> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (w->dist == INT_INFINITY) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue<Vertex<T>*> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &s, double &total) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;

	vector<Vertex<T>*> pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());

	while (!pq.empty()) {
		//write(STDOUT_FILENO,".",2);//progress bar
		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for (unsigned int i = 0; i < v->adj.size(); i++) {

			Vertex<T>* w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se j� estiver na lista, apenas a actualiza
				if (!w->processing) {

					w->processing = true;
					pq.push_back(w);
					total += v->dist / pow(10, 3);

				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());

			}
		}
	}

}



template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex) {
	if (vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for (unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++) {
		if (vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int *[vertexSet.size()];
	P = new int *[vertexSet.size()];
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for (unsigned int j = 0; j < vertexSet.size(); j++) {
			W[i][j] = edgeCost(i, j);
			P[i][j] = -1;
		}
	}

	for (unsigned int k = 0; k < vertexSet.size(); k++) {
		if (k % 20 == 0)
			write(STDOUT_FILENO, ".", 2);   //progress bar
		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int j = 0; j < vertexSet.size(); j++) {
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem conv�m considerar essa soma
				if (W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min(W[i][j], W[i][k] + W[k][j]);
				if (val != W[i][j]) {
					W[i][j] = val;
					P[i][j] = k;
				}
			}
	}
}

template<class T>
Graph<T> Graph<T>::getInvertedGraph() {

	Graph<T> invertedGraph;
	for (int i = 0; i < getNumVertex(); i++) {
		for (size_t j = 0; j < vertexSet.at(i)->adj.size(); j++) {
			invertedGraph.addVertex(
					vertexSet.at(i)->getAdj().at(j).getNode()->getInfo());
			invertedGraph.addVertex(vertexSet.at(i)->getInfo());
			invertedGraph.addEdge(vertexSet.at(i)->adj.at(j).dest->info,
					vertexSet.at(i)->info, vertexSet.at(i)->adj.at(j).weight);
		}
	}
	return invertedGraph;
}

template<class T>
bool Graph<T>::isStronglyConnected() {

	vector<T> vetor1 = dfs();

	Graph<T> invertedGraph = getInvertedGraph();

	vector<T> vetor2 = invertedGraph.dfs();

	if ((int) vetor1.size() != getNumVertex()
			|| (int) vetor2.size() != getNumVertex()) {
		return false;
	}

	return true;
}


template<class T>
vector<long long> Graph<T>::getOurRoute(long long firstNode,
		vector<long long> stops, long long endNode, double &total) {
	if (!stops.empty()) {
		Graph<T> invertedGraph = getInvertedGraph();
		stack<long long> returnstack;
		vector<long long> leg;
		double parcial, tmp = 0;
		long long source = firstNode;
		vector<long long> pathOrder;
		long long next, nextreturn, sourcereturn = source;
		double min;
		int k;
		pathOrder.push_back((getVertex(source))->getInfo());
		int iter = 0;

		while (stops.size() > 1) {
			iter++;
			min = INT_INFINITY;
			k = 0;
			next = stops.at(0);
			nextreturn = stops.at(0);
			//	cout << "IMPRIME STOPS" << endl;
			//	for (int st = 0; st < (int) stops.size(); st++) {
			//		cout << "st=" << stops.at(st) << endl;
			//	}

			parcial = 0;
			if (iter % 2 == 1) {

				dijkstraShortestPath(source, parcial);//a partir do inicio desta etapa distancias para tudo

			} else {

				invertedGraph.dijkstraShortestPath(sourcereturn, parcial);
			}

			for (unsigned int i = 0; i < stops.size(); i++) {//ver qual a stop mais perto do inicio da etapa actual
				//	cout << "tmp0" << graph.getVertex(stops.at(i))->getDist() << endl;

				if ((tmp = getVertex(stops.at(i))->getDist()) < min) {
					//		write(STDOUT_FILENO, ".", 1);

					min = tmp;
					k = i;

					if (iter % 2 == 1) {		//caminho ida
						//vai determinar a etapa

						next = stops.at(i);
					} else {			//caminho volta

						nextreturn = stops.at(i);
					}
				}
			}
			total += parcial;

			if (iter % 2 == 1) {

				leg = getPath(source, next);//vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
				pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());
				source = next;	//pŕoxima origem é a proximo da volta (anterior)
			} else {

				leg = getPath(sourcereturn, nextreturn);
				for (unsigned int i = 0; i < leg.size(); i++) {

					returnstack.push(leg.at(i));
				}
				sourcereturn = nextreturn;
			}

//		if (stops.size() > 1) {
//			source = (getVertex(iter%2==1?next:nextreturn))->getInfo(); //actualiza o inicio da proxima etapa
//			//	cout<<"stops.at(k)"<<stops.at(k)<<endl;

			stops.erase(stops.begin() + k);	//erro NAO APAGA O QUE DEVE //apaga a stop do cliente calculado nesta etapa

			//	cout << "passou";
//		} else {
//			source = firstNode;
//			stops.clear();
//			dijkstraShortestPath(source, parcial);
//			total += parcial;
//			leg = getPath(source, next); //vai buscar o caminho da etapa agora calculada e a seguir insere no caminho total
//			pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());
//			break;
//		}

		}

		//one client left
		dijkstraShortestPath(source, parcial);

		leg = getPath(source, firstNode);

		pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());

		dijkstraShortestPath(firstNode, parcial);

		leg = getPath(stops.at(0), firstNode);

		pathOrder.insert(pathOrder.end(), leg.begin(), leg.end());

		stops.clear();

		return pathOrder;
	} else {
		return vector<long long>();
	}
}

#endif /* GRAPH_H_ */
