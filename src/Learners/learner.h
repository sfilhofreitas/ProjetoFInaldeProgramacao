/*
 * Modulo responsavel por definir um Learner
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef LEARNER_H
#define LEARNER_H
#include<iostream>
#include<vector>
#include "../Utils/util_random.h"
#include "../HypothesesGenerator/hypotheses_generator.h"
using namespace std;

class Learner{
protected:
    //nome do learner
    string name;

    //classe que gerencia a aleatoriedade do Learner
    Random randomState = NULL;

    //gerador de hipoteses que o Learner utiliza
    HypothesesGenerator *hypGenerator;

    //semente de aleatoriedade do Learner
    int seed;

public:
    //metodos getters
    string getName() const{return this->name;}
    HypothesesGenerator *getHypGenerator() const{return hypGenerator;}
    int getSeed() const{return this->seed;}

    /*
     * funcao ao qual o Teacher conversa com o Learner.
     * samples é uma lista de exemplos a qual o Learner vai simular seu treinamento
     * e aprender esses exemplos, retornando uma hipótese que respeita tais exemplos
     */
    virtual vector<int> get_h(const vector<int> &samples) = 0;

    //funcao que reinicia o Learner, como por exemplo, a aletoriedade
    virtual void restart() = 0;

};

#endif // LEARNER_H
