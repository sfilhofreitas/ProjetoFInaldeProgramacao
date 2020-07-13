/*
 * Modulo responsavel por definir um Learner adversario
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef HARD_OPTIMAL_NO_PERFECT_H
#define HARD_OPTIMAL_NO_PERFECT_H
#include<iostream>
#include<algorithm>
#include "../HypothesesGenerator/hypotheses_generator.h"
#include "learner.h"
using namespace std;

/*
 * Este Learner retorna a hipotese de pior acuracia
 * que respeita todos os exemplos recebidos ate entao
*/
class AdversaryLearner: public Learner{
private:
    //numero de hipoteses
    int n;
    //lista de hipoteses embaralhada de acordo com a semente do Learner
    //apos embaralhados, as hipoteses sao ordenados por ordem crescente de acuracia
    vector<int> index;

    //lista em que e computado o numero de erros de cada hipotese para os exemplos recebidos
    vector<int> errors_h;

    // ponteiro para a posicao da proxima hipotese a ser considerada:
    //esse learner assume que o conjunto de exemplos atual contem o conjunto da iteracao passada
    int index_start;

    //retorna o menor indice considerando a ordem da lista index cuja hipotese ainda nao e coberta pelos exemplos recebidos
    int getIndexMinElement();

public:
    AdversaryLearner(HypothesesGenerator *hypGenerator, int seed);
    //recebe um conjunto de exemplos e retorna uma hipotese que respeita todos os exemplos recebidos
    vector<int> get_h(const vector<int> &samples);
    void restart();
};

#endif // HARD_OPTIMAL_NO_PERFECT_H
