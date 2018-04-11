
#ifndef _GRAPH_VIEWER_H_
#define _GRAPH_VIEWER_H_

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef __WIN32__
#include <winsock2.h>
#include <Windows.h>
#endif

#include <stdlib.h>
#include <signal.h>
#include <string>

#include "connection.h"

#define BLUE "BLUE"
#define RED "RED"
#define PINK "PINK"
#define BLACK "BLACK"
#define WHITE "WHITE"
#define ORANGE "ORANGE"
#define YELLOW "YELLOW"
#define GREEN "GREEN"
#define CYAN "CYAN"
#define GRAY "GRAY"
#define DARK_GRAY "DARK_GRAY"
#define LIGHT_GRAY "LIGHT_GRAY"
#define MAGENTA "MAGENTA"

/**
 * Classe que guarda o grafo e o representa. Todas as suas fun��es retornam um booleano a indicar
 * se a sua execu��o decorreu ou n�o com sucesso.
 */
class GraphViewer {
public:
	/**
	 * Vari�vel que guarda a pr�xima porta que o programa vai usar. O valor inicial � 7772.
	 */
	static short port;

	/**
	 * Construtor que cria um novo grafo e atribui automaticamente a porta.
	 * Exemplo: GraphViewer *gv = new GraphViewer(600, 600, true); instancia um grafo
	 * 600x600, onde a posi��o dos n�s � determinada automaticamente.
	 *
	 * @param width long longeiro que representa a lagura da �rea do grafo.
	 * @param height long longeiro que representa a altura da �rea do grafo.
	 * @param dynamic Booleano que determina se a localiza��o dos n�s � automaticamente.
	 * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
	 */
	GraphViewer(int width, int height, bool dynamic);

	/**
	 * Construtor que cria um novo grafo, utilizando uma porta especificada pelo utilizador para a liga��o.
	 *
	 * Exemplo: GraphViewer *gv = new GraphViewer(600, 600, false, 3000); instancia um grafo
	 * 600x600, onde a posi��o dos n�s � determinada pelo utilizador
	 * (usando a vers�o de addNode onde se pode especificar as coordenadas), sendo que a porta
	 * a usar para a comunica��o � a 3000.
	 *
	 * @param width inteiro que representa a lagura da �rea do grafo.
	 * @param height inteiro que representa a altura da �rea do grafo.
	 * @param dynamic Booleano que determina se a localiza��o dos n�s � automaticamente.
	 * determinado pelo programa (true) ou se deve ser determinado pelo utilizador (false).
	 * @param port_n inteiro que determina a porta a utilizar. Deve-se ter cuidado para n�o utilizar uma porta
	 * j� usada por outro programa ou pelo sistema.
	 */
	GraphViewer(int width, int height, bool dynamic, int port_n);

	/**
	 * Fun��o que cria a janela para visualiza��o.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->createWindow(600, 600); abre uma janela 600x600 onde mostra o grafo.
	 *
	 *
	 * @param width Largura da janela a criar.
	 * @param height Altura da janela a criar.
	 */
	bool createWindow(int width, int height);

	/**
	 * Fecha a janela a ser utilizada para visualiza��o.
	 */
	bool closeWindow();

	/**
	 * Acrescenta um n� � representa��o do grafo, numa posi��o espec�fica, irrelevante se o grafo
	 * for din�mico.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer com isDynamic = false:
	 * gv->addNode(0, 1, 2); adiciona um n� com ID 0 na posi��o (x, y) = (1, 2)
	 *
	 * @param id Identificador �nico do n�.
	 * @param x Posi��o horizontal do n�.
	 * @param y Posi��o vertical do n�.
	 */
	bool addNode(long long id, long long x, long long y);

	/**
	 * Acrescenta um n� � representa��o do grafo, numa posi��o ao crit�rio do programa.
	 * S� pode ser usado se o grafo for din�mico, ou seja, se as posi��es de todos
	 * os n�s forem atribu�das automaticamente. Caso contr�rio, n�o adiciona o n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer com isDynamic = true:
	 * gv->addNode(0); adiciona um n� com ID 0
	 *
	 * @param id Identificador �nico do n�.
	 */
	bool addNode(long long id);

	/**
	 * Acrescenta uma aresta � representa��o do grafo.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->addEdge(0, 1, 2, EdgeType::UNDIRECTED); adiciona uma aresta n�o-dirigida com ID 0
	 * que liga os n�s com os IDs 1 e 2
	 *
	 * @param id Identificador �nico da aresta.
	 * @param v1 Identificador �nico do n� de origem da aresta.
	 * @param v2 Identificador �nico do n� de destino da aresta.
	 * @param edgeType EdgeType.DIRECTED caso a aresta seja unidirecional
	 * ou EdgeType.UNDIRECTED caso a aresta seja bidirecional.
	 */
	bool addEdge(long long id, long long v1, long long v2, long long edgeType);

	/**
	 * Remove um n� da representa��o do grafo e todas as arestas ligadas a este.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->removeNode(0) remove o n� com ID 0
	 *
	 * @param id Identificador �nico do n� a a remover.
	 */
	bool removeNode(long long id);

	/**
	 * Remove uma aresta da representa��o do grafo.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->removeEdge(0) remove a aresta com ID 0
	 *
	 * @param id Identificador �nico da aresta a remover.
	 */
	bool removeEdge(long long id);

	/**
	 * Fun��o que define o texto de um n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setVertexLabel(0, "Isto � um n�"); adiciona o texto "Isto � um n�" ao n� com ID 0
	 *
	 * @param id Identificador �nico do n� com o texto a alterar.
	 * @param label Novo texto do n�.
	 */
	bool setVertexLabel(long long id, string label);

	/**
	 * Fun��o que define o texto de uma aresta.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeLabel(0, "Isto � uma aresta"); adiciona o texto "Isto � uma aresta" � aresta com ID 0
	 *
	 * @param id Identificador �nico da aresta com o texto a alterar.
	 * @param label Novo texto da aresta.
	 */
	bool setEdgeLabel(long long id, string label);

	/**
	 * Fun��o que define a cor de uma aresta.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeColor(0, BLUE); modifica a cor da aresta com ID 0 para azul
	 *
	 * @param id Identificador �nico da aresta com a cor a alterar.
	 * @param color Nova cor da aresta, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool setEdgeColor(long long id, string color);

	/**
	 * Fun��o que define se uma aresta � desenhada, ou n�o, a tracejado.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeDashed(0, false); faz com que a aresta com ID 0 seja desenhada a tra�o cont�nuo
	 *
	 * @param id Identificador �nico da aresta com a cor a alterar.
	 * @param dashed Nova cor da aresta, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool setEdgeDashed(long long id, bool dashed);

	/**
	 * Fun��o que define a cor de um n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setVertexColor(0, GREEN); modifica a cor do n� com ID 0 para verde
	 *
	 * @param id Identificador �nico do n� com a cor a alterar.
	 * @param color Nova cor do n�, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool setVertexColor(long long id, string color);

	/**
	 * Fun��o que define o tamanho de um n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setVertexSize(0, 10); modifica o tamanho do n� com ID 0 para 40
	 *
	 * @param id Identificador �nico do n� com o tamanho a alterar.
	 * @param size Novo tamanho do n�.
	 */
	bool setVertexSize(int id, int size);

	/**
	 * Fun��o que define um �cone para um n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setVertexIcon(0, "icon.png"); faz com que o n�, quando desenhado, n�o seja um c�rculo, mas sim a imagem icon.png
	 *
	 * @param id Identificador �nico do n� com o �cone a alterar.
	 * @param filepath Caminho do ficheiro a utilizar como novo �cone do n�.
	 */
	bool setVertexIcon(int id, string filepath);

	/**
	 * Fun��o que define a espessura de uma aresta.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeThickness(0, 20); modifica a espessura da aresta com ID 0 para 20
	 *
	 * @param id Identificador �nico da aresta com a espessura a alterar.
	 * @param thickness Nova espessura da aresta, sendo que por base, as
	 * arestas s�o criadas com a espessura de 1.
	 */
	bool setEdgeThickness(long long id, long long thickness);

	/**
	 * Fun��o que define o peso de uma aresta na representa��o do grafo, a ser visualizado
	 * como w: valor_do_peso, seguido de qualquer outro texto associado � aresta.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeWeight(0, 20); modifica o peso da aresta com ID 0 para 20
	 *
	 * @param id Identificador �nico da aresta a modificar.
	 * @param weight Peso associado � aresta.
	 */
	bool setEdgeWeight(int id, int weight);

	/**
	 * Fun��o que define o fluxo de uma aresta na representa��o do grafo, a ser visualizado
	 * como f: valor_do_fluxo, precedido pelo peso e seguido por texto definido pelo utilizador.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setEdgeFlow(0, 20); modifica o fluxo da aresta com ID 0 para 20
	 *
	 * @param id Identificador �nico da aresta a modificar.
	 * @param flow Fluxo associado � aresta.
	 */
	bool setEdgeFlow(int id, int flow);

	/**
	 * Fun��o que define se as arestas do grafo ser�o desenhadas como curvas ou retas.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineEdgeCurved(false); faz com que as arestas sejam desenhadas como retas
	 *
	 * @param curved Booleano que representa se as arestas ser�o curvas (true) ou retas (false), sendo o valor por defeito � true.
	 */
	bool defineEdgeCurved(bool curved);

	/**
	 * Fun��o que define a cor global das arestas.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineEdgeColor(GRAY); modifica a cor por defeito das arestas para cinzento
	 *
	 * @param color Nova cor das arestas, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool defineEdgeColor(string color);

	/**
	 * Fun��o que define globalmente se as arestas s�o desenhadas, ou n�o, a tracejado.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineEdgeDashed(true); faz com que por defeito as arestas sejam desenhadas a tracejado
	 *
	 * @param dashed Booleano que representa se as arestas v�o estar, ou n�o, todas a tracejado (o valor por defeito � false).
	 */
	bool defineEdgeDashed(bool dashed);

	/**
	 * Fun��o que define a cor global dos n�s.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineVertexColor(RED); modifica a cor por defeito dos n�s para vermelho
	 *
	 * @param color Nova cor dos n�s, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool defineVertexColor(string color);

	/**
	 * Fun��o que define o tamanho global dos n�s.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineVertexSize(20); modifica o tamanho por defeito dos n�s para 20
	 *
	 * @param size Nova cor dos n�s, utilizar as constantes definidas no graphviewer.h para conveni�ncia.
	 */
	bool defineVertexSize(int size);

	/**
	 * Fun��o que define um �cone para um n�.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->defineVertexIcon("icon.gif"); faz com que por defeito os n�s, quando desenhados,
	 * n�o sejam um c�rculo, mas sim a imagem icon.gif
	 *
	 * @param filepath Caminho do ficheiro a utilizar como novo �cone do n�.
	 */
	bool defineVertexIcon(string filepath);

	/**
	 * Fun��o que altera a imagem de fundo do grafo.
	 * Exemplo, para um apontador gv onde foi instanciada a classe GraphViewer:
	 * gv->setBackGround("fundo.png"); faz com que o fundo da janela seja a imagem fundo.png,
	 * em vez de cinzento
	 *
	 * @param path Caminho para o ficheiro com a imagem.
	 */
	bool setBackground(string path);

	/**
	 * Fun��o que actualiza a visualiza��o do grafo.
	 */
	bool rearrange();

#ifdef __linux__
	static pid_t procId;
#endif

private:
	int width, height;
	bool isDynamic;

	Connection *con;

	void initialize(int, int, bool, int);
};

#endif
