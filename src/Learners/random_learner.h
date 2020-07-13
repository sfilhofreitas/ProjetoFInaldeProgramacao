/*
 * Modulo responsavel por definir um Learner aleatorio
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef OPTIMAL_NO_PERFECT_H
#define OPTIMAL_NO_PERFECT_H
#include<iostream>
#include "../HypothesesGenerator/hypotheses_generator.h"
#include "learner.h"
using namespace std;
/*
 * Este Learner retorna uma hipotese de forma aleatoria
 * que respeita todos os exemplos recebidos ate entao
 * Porem, a hipotese perfeita, se houver, so e mandada em ultimo caso
*/
class RandomLearner: public Learner{
private:
    //numero de hipoteses
    int n;

    //lista de hipoteses embaralhada de acordo com a semente do Learner
    //A hipotese perfeita, se houver, e a ultima
    vector<int> index;

    //lista em que e computado o numero de erros de cada hipotese para os exemplos recebidos
    vector<int> errors_h;

    // ponteiro para a posicao da proxima hipotese a ser considerada:
    //esse learner assume que o conjunto de exemplos atual contem o conjunto da iteracao passada
    int index_start;

    //retorna o menor indice considerando a ordem da lista index cuja hipotese ainda nao e coberta pelos exemplos recebidos
    int getIndexMinElement();

public:
    RandomLearner(HypothesesGenerator *hypGenerator, int seed);
    //recebe um conjunto de exemplos e retorna uma hipotese que respeita todos os exemplos recebidos
    vector<int> get_h(const vector<int> &samples);
    void restart();
};

#endif // OPTIMAL_NO_PERFECT_H
