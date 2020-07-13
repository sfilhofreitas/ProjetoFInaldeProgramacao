/*
 * Modulo responsavel por definir funcoes aleatorias
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H
#include<random>
#include<vector>
#include<iostream>
#define MAX_INT 2147483647
using namespace std;

//Classe que fornece funcoes aleatorias para os objetos em funcao de uma seed
//Exceto quando explicitado o contrario, as funcoes seguem uma distribuicao uniforme
class Random{
mt19937 rng;
default_random_engine generator;
uniform_real_distribution<double> real_distribution;//(0.0,1.0);
uniform_int_distribution<int> int_distribution;

int seed;
public:
    Random(int seed);

    //Esta funcao retorna um numero aleatorio entre 0 e 1
    double random();

    //Esta funcao retorna um vector de numeros aleatorios entre 0 e 1
    vector<double> random(int n);

    //Esta funcao retorna um numero inteiro aleatorio entre min e max
    int randInt(int min, int max);

    //Esta funcao retorna k numeros disjuntos de 0 a n-1 cuja probabilidade
    //de sortear cada elemento e dada pela distribuicao p
    vector<int> choice(int n, int k, vector<double> p);

    //Esta funcao retorna k numeros disjuntos de 0 a n-1
    vector<int> choice(int n, int k);

    //Esta funcao retorna k elementos disjuntos de v
    vector<int> choice(vector<int> v, int k);

    //Esta funcao retorna k elementos disjuntos de v cuja probabilidade
    //de sortear cada elemento e dada pela distribuicao p
    vector<int> choice(vector<int> v, int k, vector<double> p);

    //esta funcao embaralha um vetor v
    void shuffle(vector<int> &v);

    void reset();
};

#endif // UTIL_RANDOM_H
