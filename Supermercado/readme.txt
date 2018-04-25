linux
gcc version 5.4.0 20160609
g++ -O0 -g3 -Wall -c -fmessage-length=0

depois de compilar: correr, nesta pasta, o comando ./Debug/Supermercado

(ou então correr nesta pasta a versão release (./Supermercado)


os dados da análise foram obtidos repondendo 0 ao numero de nós, ao número de clientes e ao número de supermercados.
isto implica as configurações default de 22 clientes, 11 supermercados e 4 camioes (1 de cada 1 de 4 supermercados) 
num mapa de 649 nós e 696 arestas

se se escolher outros numeros de clientes estes serão criados a partir dos nós disponiveis, 
acontecendo o mesmo com os supermercados e os camiões (numero introduzido corresponde ao número de camioes por supermercado, 
indo depois a aplicação distribuir os clientes criados pelos supermercados e pelos seus camioes)
