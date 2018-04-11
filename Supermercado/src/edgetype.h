/*
 * edgetype.h
 *
 *  Created on: 08/04/2017
 *      Author: ricar
 */


#ifndef _EDGETYPE_
#define _EDGETYPE_

/**
 * Classe que enumera os tipos de arestas. Usar EdgeType.UNDIRECTED para uma aresta sem direc��o, ou
 * EdgeType.DIRECTED para uma aresta dirigida.
 */
class EdgeType {
 public:
  const static long long UNDIRECTED = 0;
  const static long long DIRECTED = 1;
};

#endif


