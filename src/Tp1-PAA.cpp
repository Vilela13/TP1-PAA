#include <iostream>     // Biblioteca padrão de c++
#include <istream>      // Biblioteca padrão de c++
#include <list>         // Biblioteca que contem a estrutura listas
#include <string>       // Biblioteca que contem a estrutura string ( vetor de caracteres)
#include <fstream>      // Biblioteca que contem a estrutura para acessar arquivos txt
#include <vector>       // Biblioteca que contem a estrutura Vector

#include <stdio.h>      // Biblioteca padão de C, principalmente a operações de entrada e saída
#include <stdlib.h>     // Biblioteca padão de C, possui funções envolvendo alocação de memória, controle de processos, conversões e outras.

#include<sstream>

#define MaxDouble 1.8e+307  // Define o maior valor para a variavel Double


using namespace std; // utilizar o espaço de nomes em C++


class Algoritmo{        // Classe principal do programa

public:
    Algoritmo();                                    // construtora da classe
    void EscreveTXT();                              // Escreve uma instancia para o problema
    int NumNos;                                     // Contem o numero de nos do grafo
    int NoOrigem, NoDestino, Amizade, Distancia;    // Garda as informações lidas no Input
    double LowerBound, UpperBound, Intermediario;   // Variaveis que guarada o Upper bound , o lower bound e o valor intermediario necessario para realizar a busca binaria
    double Razao;                                   // A razão pedida, que é a solução do problema

    vector<vector<vector<int> > > MatrizGrafo;      // São 3 matrizes NumNos por NumNos, a primeira é da conectividade dos nos, a segunda referente a amizade entre os nos, e a terceira a distancia deles
    vector<char> NosDFS;                            // Vetor com o estados dos Nos apos a busca em profundidade (DFS)

    void ImprimeEstruturasCriadas();                // Imprime a MatrizGrafo referente a incidancia dos arcos e o vetor com os estados dos nos
    void ImprimeDadosLidos();                       // Imprime a matriz de incidencia, a da amizade e a de distancia
    void ImprimeEstadosNosAposDFS( );               // Imprime os estados dos nos no vetor dos NosDFS

    void DFS(int);                                  // Busca em profundidade apartir do no passado
    int VerificaGrafoConexo();                      // Verifica se o grafo é conexo ao ver se tem no com o estado 'b' no vetor de estados NosDFS

    void CalculoUpperLowerBound( );                 // Calcula o valor do Upper Bound e Lower Bound iniciais para a busca binaria
    void ImprimeUpperLower();                       // Imprime os valores de Upper Bound e Lower Bound

    vector<vector<double> > MatrizNovosPesos;                       // Matriz que contem os novos pessos unitarios das arestas
    vector<vector<int> > MatrixArvoreGeradoraMaisArcosPositivo;     // Matriz de incidencia da arvore geradora maxima mais os arcos com valor positivo restantes
    double SomaArcosArvoreGeradoraMaisArcosPositivo;                // Valor do somatorio dos arcos da arvore geradora maxima mais os arcos com valor positivo restantes

    void ReponderacaoDePesos( double );             // Realiza a reponderação dos pesos baseado no valor passado como referencia
    void ImprimeNovosPesos();                       // Imprime os novos pesos unitarios tidos

    /* Inicio Algoritmo Prim */

    vector<int> Predecessor;        // Variavel de predecessores utilizada no algoritmo Prim e que ira fornecer a arvora geradora minima
    vector<int> Q;                  // Vector utilizado como se fosse uma lista para saber os nos ja analisados pelo algoritmo Prim
    vector<double> Key;             // Valor da distancia do no anterior a ele na arvore geradora minima ao longo da execução

    void Prim();                    // Algoritmo Prim de fato

    /*   Fim Algoritmo Prim */

    void ImprimePredecessores();    // Imprime o vetor de predecessores dos nos
    void ImprimeKey();              // Imprime o valor das Key dos nos

    void PreencheMatrixComArvoreGeradora();                 // Preenche a MatrixArvoreGeradoraMaisArcosPositivo com a Arvore geradora maxima encontrada
    void ImprimeMatrixArvoreGeradoraMaisArcosPositivo();    // Imprime a MatrixArvoreGeradoraMaisArcosPositivo
    void PreencheMatrixComArcosPositivosRestantes();        // Preenche a MatrixArvoreGeradoraMaisArcosPositivo com os arcos positivos restantes
    void SomaArcosMatrixComArcosPositivosRestantes();       // Realiza a soma dos arcos da arvore geradora maxima mais os arcos positivos restantes

    double Resposta();                 // Realiza a busca binaria para encontrar a resposta

    int LeImput(char *);       // Realiza a leitura dos dados passados, calcula a resposta que se quer e escreve as respostas em um arquivo de saida

    ~Algoritmo();       // Destridora
};



Algoritmo::Algoritmo(){
}

void Algoritmo::EscreveTXT(){

    ofstream SaidaNos;
    SaidaNos.open("InstanciaA.in");

    int NumNos;
    int NoOrigem, NoDestino, Amizade, Distancia;

    NumNos = 4;
    SaidaNos << NumNos << endl;
    NoOrigem = 1; NoDestino = 2; Amizade = 6; Distancia = 5;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 2; NoDestino = 3; Amizade = 3; Distancia = 4;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 3; NoDestino = 4; Amizade = 5; Distancia = 2;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 4; NoDestino = 1; Amizade = 3; Distancia = 3;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;

    SaidaNos << endl;

    NumNos = 5;
    SaidaNos << NumNos << endl;
    NoOrigem = 1; NoDestino = 2; Amizade = 6; Distancia = 5;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 2; NoDestino = 3; Amizade = 3; Distancia = 4;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 3; NoDestino = 4; Amizade = 5; Distancia = 2;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 4; NoDestino = 1; Amizade = 3; Distancia = 3;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;

    SaidaNos << endl;

    NumNos = 4;
    SaidaNos << NumNos << endl;
    NoOrigem = 1; NoDestino = 2; Amizade = 1; Distancia = 10;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 2; NoDestino = 3; Amizade = 3; Distancia = 3;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 2; NoDestino = 4; Amizade = 3; Distancia = 2;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
    NoOrigem = 3; NoDestino = 4; Amizade = 3; Distancia = 1;
    SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;

    SaidaNos.close();
}

void  Algoritmo::ImprimeEstruturasCriadas(){
          cout << " Matrix de incidencia Inicial" << endl;

          for (int i = 0; i < NumNos; i++){
            cout << " L" << i+1 << "  ";
            for (int j = 0; j < NumNos; j++){
                cout << MatrizGrafo[i][j][0] << " ";
            }
            cout << endl;
          }

          cout << endl << endl;

          cout << " Vetor de estado dos Nos"<< endl;

          for (int i = 0; i < NumNos; i++){
            cout << " " << i+1 << " [" << NosDFS[i] << "]";
        }
        cout << endl;
}

void Algoritmo::ImprimeDadosLidos(){

    cout << " Matrix de incidencia " << endl;

    for (int i = 0; i < NumNos; i++){
        cout << " L" << i+1 << "  ";
        for (int j = 0; j < NumNos; j++){
            cout << MatrizGrafo[i][j][0] << " ";
        }
        cout << endl;
      }

      cout << endl << endl;

      cout << " Matrix de amizade " << endl;

    for (int i = 0; i < NumNos; i++){
        cout << " L" << i+1 << "  ";
        for (int j = 0; j < NumNos; j++){
            cout << MatrizGrafo[i][j][1] << " ";
        }
        cout << endl;
      }

      cout << endl << endl;

      cout << " Matrix de distancia " << endl;

    for (int i = 0; i < NumNos; i++){
        cout << " L" << i+1 << "  ";
        for (int j = 0; j < NumNos; j++){
            cout << MatrizGrafo[i][j][2] << " ";
        }
        cout << endl;
      }

      cout << endl << endl;


}

void Algoritmo::ImprimeEstadosNosAposDFS(){
    cout << endl << endl << " Vetor de estado dos Nos Apos DFS"<< endl;

    for (int i = 0; i < NumNos; i++){
        cout << " " << i+1 << " [" << NosDFS[i] << "]";
    }
    cout << endl;
}

int Algoritmo::VerificaGrafoConexo(){  // Retorna 1 se grafo conexo, caso contrario retorna 0
    for (int i = 0; i < NumNos; i++){
        if( NosDFS[i] == 'b'){
            return 0;
        }
    }
    return 1;
}

void Algoritmo::DFS(int u){
    NosDFS[u] = 'c';
    int aux;
    for (int j = 0; j < NumNos; j++){
        aux = j;
        if( MatrizGrafo[u][aux][0] == 1 ){
                if( NosDFS[aux] == 'b'){
                    //cout << endl << "  Entrou no BFS = " << j;
                    DFS(aux );
                }
        }
    }
    NosDFS[u] = 'p';
}

void Algoritmo::CalculoUpperLowerBound( ){
    LowerBound = 0;
    UpperBound = 0;

    for (int i = 0; i < NumNos; i++){
        for (int j = i; j < NumNos; j++){
            UpperBound = UpperBound + MatrizGrafo[i][j][1];
        }
    }

}

void Algoritmo::ImprimeUpperLower(){
    cout<< endl << "  Lower = " << LowerBound << endl;
    cout<< endl << "  Upper = " << UpperBound << endl;
}

void Algoritmo::ReponderacaoDePesos( double R){

    MatrizNovosPesos.resize(NumNos);
    MatrixArvoreGeradoraMaisArcosPositivo.resize(NumNos);
    for (int i = 0; i < NumNos; i++){
        MatrizNovosPesos[i].resize(NumNos);
        MatrixArvoreGeradoraMaisArcosPositivo[i].resize(NumNos);
    }

    for (int i = 0; i < NumNos; i++){
        for (int j = 0; j < NumNos; j++){
            if( MatrizGrafo[i][j][0] == 1){
                MatrizNovosPesos[i][j] = -( MatrizGrafo[i][j][1] - R * MatrizGrafo[i][j][2] );
            }else{
                MatrizNovosPesos[i][j] = 0;
            }
            MatrixArvoreGeradoraMaisArcosPositivo [i][j] = 0;
        }
    }
}

void Algoritmo::ImprimeNovosPesos(){

    cout << endl << " Novos pesos " << endl << endl;
    for (int i = 0; i < NumNos; i++){
        cout << "L" << i+1;
        for (int j = 0; j < NumNos; j++){
                cout << "  " << MatrizNovosPesos[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Algoritmo::Prim(){

    //cout << endl << " entrou prin" << endl;
    int u;
    int posicao;

    Predecessor.resize(NumNos);
    Q.resize(NumNos);
    Key.resize(NumNos);
    for (int i = 0; i < NumNos; i++){
        Q[i]=i;
        Predecessor[i] = -5;
        Key[i]= MaxDouble;
    }

    //ImprimePredecessores();
    //ImprimeKey();
    //ImprimeNovosPesos();

    Key[0]= 0;

    while( Q.size() > 0 ){
            u = Q[0];
            posicao = 0;
        for( int i = 0; i < int(Q.size()); i++ ){
            if( Key[u] > Key[ Q[i] ]){
                u = Q[i];
                posicao = i;
            }
        }
        Q.erase (Q.begin()+ posicao);
    //cout << " U = " << u+1 << endl;
        for( int v = 0; v < NumNos; v++){
            if ( MatrizGrafo[u][v][0] == 1){
                for( int i = 0; i < int(Q.size()); i++ ){
                    if( v ==  Q[i]){
                        if( MatrizNovosPesos[u][v] < Key[v]){
                                //cout << "entrou" << endl;
                            //cout << " v = " << v ;
                            Predecessor[v] = u;
                            Key[v] = MatrizNovosPesos[u][v];
                        }
                    }
                }
            }
        }
    }
}

void Algoritmo::ImprimePredecessores(){
    cout << endl << endl << " Predecessores" << endl << endl;
    for (int i = 0; i < NumNos; i++){
        cout << i+1 << " <= " << Predecessor[i]+1 << endl;
    }
    cout << endl;
}

void Algoritmo::ImprimeKey(){
    cout << endl << endl << " Key" << endl << endl;
    for (int i = 0; i < NumNos; i++){
        cout << i+1 << " <= " << Key[i] << endl;
    }
    cout << endl;
}

void Algoritmo::PreencheMatrixComArvoreGeradora(){

    //cout << endl << " Entro preenche matriz" << endl ;
    //ImprimePredecessores();

    for( int i = 1; i < NumNos; i++){
        MatrixArvoreGeradoraMaisArcosPositivo[       i        ][ Predecessor[i] ] = 1;
        MatrixArvoreGeradoraMaisArcosPositivo[ Predecessor[i] ][       i        ] = 1;
         //cout << endl << " p1 = " << i  << "  -> " << MatrixArvoreGeradoraMaisArcosPositivo[       i        ][ Predecessor[i] ] <<  endl ;
         //cout << endl << " p2 = " << i  << "  -> " << MatrixArvoreGeradoraMaisArcosPositivo[ Predecessor[i] ][       i        ] <<  endl ;
    }
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
}

void Algoritmo::ImprimeMatrixArvoreGeradoraMaisArcosPositivo(){

    cout << endl << " Arvore Geradora " << endl << endl;
    for (int i = 0; i < NumNos; i++){
        cout << "L" << i+1;
        for (int j = 0; j < NumNos; j++){
                cout << "  " << MatrixArvoreGeradoraMaisArcosPositivo[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;

}

void Algoritmo::PreencheMatrixComArcosPositivosRestantes(){

    //cout << endl << " Entro preenche matriz com mais arcos" << endl ;

    for (int i = 0; i < NumNos; i++){
        for (int j = i; j < NumNos; j++){
            if( MatrixArvoreGeradoraMaisArcosPositivo[i][j] == 0){
                if( MatrizNovosPesos[i][j] < 0  ){
                    MatrixArvoreGeradoraMaisArcosPositivo[i][j] = 1;
                    //cout << endl << " Arco a mais " << i << " - " << j << endl << endl;
                }
            }
        }
    }
}

void Algoritmo::SomaArcosMatrixComArcosPositivosRestantes(){

    //cout << endl << " Entro soma matrix" << endl ;
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();

    SomaArcosArvoreGeradoraMaisArcosPositivo = 0;

    for (int i = 0; i < NumNos; i++){
        for (int j = i; j < NumNos; j++){
                //cout << "  " << i << " " << j << endl;
            if( MatrixArvoreGeradoraMaisArcosPositivo[i][j] == 1){
                SomaArcosArvoreGeradoraMaisArcosPositivo = SomaArcosArvoreGeradoraMaisArcosPositivo - MatrizNovosPesos[i][j];
                //cout << i << " " << j << endl;
            }
        }
    }
}

double Algoritmo::Resposta(){

    int AtendeSomatorioNulo;

    CalculoUpperLowerBound();
    //ImprimeUpperLower();

/* Calcula somatorio para o LowerBound inicial */

    ReponderacaoDePesos( LowerBound);
    //ImprimeNovosPesos();
    Prim();
    //ImprimePredecessores();
    PreencheMatrixComArvoreGeradora();
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
    PreencheMatrixComArcosPositivosRestantes();
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
    SomaArcosMatrixComArcosPositivosRestantes();
    //cout << endl << endl << " Somatorio 1 = " << SomaArcosArvoreGeradoraMaisArcosPositivo << endl << endl;

    if( (SomaArcosArvoreGeradoraMaisArcosPositivo < 0.00001) and (SomaArcosArvoreGeradoraMaisArcosPositivo > -0.00001) ){
        return LowerBound;
    }

/* Calcula somatorio para o UpperBound inicial */

    ReponderacaoDePesos( UpperBound);
    //ImprimeNovosPesos();
    Prim();
    //ImprimeNovosPesos();
    PreencheMatrixComArvoreGeradora();
    //cout << " prencheu matriz";
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
    PreencheMatrixComArcosPositivosRestantes();
    //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
    SomaArcosMatrixComArcosPositivosRestantes();
    //cout << endl << endl << " Somatorio 2 = " << SomaArcosArvoreGeradoraMaisArcosPositivo << endl << endl;

/* Realiza a busca binaria para encontrar a resposta */

    if( (SomaArcosArvoreGeradoraMaisArcosPositivo < 0.00001) and (SomaArcosArvoreGeradoraMaisArcosPositivo > -0.00001) ){
        return UpperBound;
    }

    AtendeSomatorioNulo = 0;

    while( AtendeSomatorioNulo == 0 ){
        Intermediario = ((UpperBound - LowerBound) / 2 ) + LowerBound;
        //cout << endl << " Upper = " << UpperBound << "  Lower = " <<  LowerBound ;

        ReponderacaoDePesos(Intermediario);
        //ImprimeNovosPesos();
        Prim();
        //ImprimeNovosPesos();
        PreencheMatrixComArvoreGeradora();
        //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
        PreencheMatrixComArcosPositivosRestantes();
        //ImprimeMatrixArvoreGeradoraMaisArcosPositivo();
        SomaArcosMatrixComArcosPositivosRestantes();
        //cout << endl << endl << " Somatorio = " << SomaArcosArvoreGeradoraMaisArcosPositivo << endl << endl;

        if ( SomaArcosArvoreGeradoraMaisArcosPositivo < 0 ){
            UpperBound = Intermediario;
        }
        if ( SomaArcosArvoreGeradoraMaisArcosPositivo > 0 ){
            LowerBound = Intermediario;
        }

        if( (SomaArcosArvoreGeradoraMaisArcosPositivo < 0.00001) and (SomaArcosArvoreGeradoraMaisArcosPositivo > -0.00001) ){
            AtendeSomatorioNulo = 1;
        }
    }
    return Intermediario;

}

int Algoritmo::LeImput( char *InputChar){

    //cout << endl << endl << "  Entra 2 = " << InputChar << " " << OutputChar << endl << endl;
    //EscreveTXT();


   char input[264];
   FILE * Le = fopen(InputChar, "r");

	if(!Le){
		return 0;
	}

	while(!feof(Le)){

		fscanf(Le, "%d\n", &NumNos);
		//printf("\n%d\n", NumNos);

/* Inicializa vector NosDFS com 0 */

		NosDFS.resize(NumNos);

        for (int i = 0; i < NumNos; i++){
            NosDFS[i] = 'b';
        }

/* Inicializa vector MatrizGrafo com 0 */

        MatrizGrafo.resize(NumNos);
        for (int i = 0; i < NumNos; i++){
            MatrizGrafo[i].resize(NumNos);
            for (int j = 0; j < NumNos; j++){
                MatrizGrafo[i][j].resize(3);
            }
        }

        for (int i = 0; i < NumNos; i++){
            for (int j = 0; j < NumNos; j++){
                for (int w = 0; w < 3; w++){
                    MatrizGrafo[i][j][w] = 0;
                }
            }
        }

        //ImprimeEstruturasCriadas();

/* Le arquivo Passados */

		fgets(input, 264, Le);

		while(input[0] != '\n'){
			sscanf(input, "%d %d %d %d\n", &NoOrigem, &NoDestino, &Amizade, &Distancia);
			//printf("%d %d %d %d\n", NoOrigem, NoDestino, Amizade, Distancia);

			MatrizGrafo[NoOrigem-1 ][NoDestino-1][0] = 1;
			MatrizGrafo[NoDestino-1][NoOrigem-1 ][0] = 1;

			MatrizGrafo[NoOrigem-1 ][NoDestino-1][1] = Amizade;
			MatrizGrafo[NoDestino-1][NoOrigem-1 ][1] = Amizade;

			MatrizGrafo[ NoOrigem-1 ][ NoDestino-1][2] = Distancia;
			MatrizGrafo[ NoDestino-1][ NoOrigem-1 ][2] = Distancia;

			if(!fgets(input, 264, Le))
				break;
		}

        //ImprimeDadosLidos();

        /*
        cout << " Matrix de incidencia Inicial" << endl;

          for (int i = 0; i < NumNos; i++){
            cout << " L" << i+1 << "  ";
            for (int j = 0; j < NumNos; j++){
                cout << MatrizGrafo[i][j][0] << " ";
            }
            cout << endl;
          }
          */

/* Realiza Busca em profundidade */

        DFS(0);
        //ImprimeEstadosNosAposDFS(  );

/* Busca Solução desejada atravez primeirmente da verificação se o grafo é conexo, caso for realiza a busca binaria */

        if( VerificaGrafoConexo() == 1){
            //cout << endl << endl << " Conexo! "<< endl;
            Razao = Resposta();
            //cout << endl << " Resposta = " << Razao << endl << endl;
            printf("\n %.3lf",Razao);
        }else{
            //cout << endl << endl << " Disconexo! "<< endl;
            Razao = -1;
            printf("\n %.3lf",Razao);

        }




		// aqui vc já pode chamar a função do seu tp

	}
	printf("\n");

	fclose(Le);
	return 1;

}



Algoritmo::~Algoritmo(){
}



int main(){

    char *input;
    char *output;
    int leu;
    Algoritmo AG;

    int NumNos;
    int NoOrigem, NoDestino, Amizade, Distancia;



    char c[] = "TemporarioX2548.txt";

    ofstream SaidaNos;
    SaidaNos.open("TemporarioX2548.txt");

	string linha;

	int PrimeiraLinha;

	PrimeiraLinha = 1;

	while(getline(cin,linha)){
		istringstream linha2(linha);
		//cout << "leu linha" << endl;
		if(linha2 >> NumNos){
			if( PrimeiraLinha == 1){

                SaidaNos << NumNos << endl;
                PrimeiraLinha = 0;
            }else{
                NoOrigem = NumNos;
                linha2 >> NoDestino;
                linha2 >> Amizade;
                linha2 >> Distancia;

                SaidaNos << NoOrigem << ' ' << NoDestino << ' ' << Amizade << ' ' << Distancia << endl;
            }
        }else{
            PrimeiraLinha = 1;
            SaidaNos << endl;
        }

	}

	SaidaNos.close();

	leu = AG.LeImput(c);

    remove("TemporarioX2548.txt");

    return 1;



}

