/*
 * Modulo responsavel por gerar o conjunto de hipoteses
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef SIMPLE_RANDOM_HYPOTHESES_H
#define SIMPLE_RANDOM_HYPOTHESES_H
#include<vector>
#include<iostream>
#include <bits/stdc++.h>
#include<math.h>
#include "hypotheses_generator.h"

using namespace std;

class SimpleRandomHypotheses: public HypothesesGenerator{
private:
    //lista de acuracias possiveis para cada hipotese
    vector<double> accList;

    //fracao de exemplos entre os m que serao errados com mais frequencia
    double hardSamples;

    //hardFrac dos erros de cada hipotese vem dos exemplos mais dificeis
    double hardFrac;

    //soma dos indices que cada hipotese erra
    //Essa variavel ajuda a evitar ordenar todas as listas de erros
    //A ordenacao ocorre para otimizar o tempo de teste se uma nova hipotese é disjunta
    vector<int> sum;

    //variavel auxiliar: ponteiro de indice
    int c;

    //metodo que cria o conjunto de hipoteses
    void generateH();

    //metodo que cria uma hipotese conforme definida pelos parametros recebidos pela classe
    vector<int> get_h();

public:
    SimpleRandomHypotheses(int n, int m, vector<double> accList, double hardSamples, double hardFrac, int seed);
    int getM() const;

};

#endif // SIMPLE_RANDOM_HYPOTHESES_H
