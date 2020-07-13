/*
 * Modulo responsavel por definir um Teacher que
 * atribui um peso para cada exemplo e seleciona
 * os exemplos baseado na variacao de pesos da
 * iteracao passada
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef WEIGHTS_THEORETICAL_FOUNDED_H
#define WEIGHTS_THEORETICAL_FOUNDED_H
#include<string>
#include<vector>
#include<iostream>
#include <bits/stdc++.h>
#include "Learners/learner.h"
#include "../Learners/random_learner.h"
#include "teacher.h"

using namespace std;


class WeightsTheoreticalFounded: public Teacher{
    //numero de exemplos
    int m;

    //peso de cada exemplo
    vector<double> weights;

    //estimativa do tamanho do conjunto de hipoteses do Learner
    int n;

public:    
    WeightsTheoreticalFounded(int m, int seed);

    //funcao onde ocorre onde o teacher interage com o learner e define o teaching set
    pair<vector<int>, string> teaching(Learner &learner);

    //Funcao na qual o teacher escolhe quais exemplos enviar considerando a variacao delta_w dos pesos
    vector<int> getExamples(vector<int>& Examples, vector<double> delta_w);
};

#endif // WEIGHTS_THEORETICAL_FOUNDED_H
