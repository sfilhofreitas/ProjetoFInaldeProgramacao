/*
 * Modulo responsavel por gerar o conjunto de hipoteses
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef HYPOTHESES_GENERATOR_H
#define HYPOTHESES_GENERATOR_H
#include "../Utils/util_random.h"
//#include "../Utils/heuristics.h"
#include <bits/stdc++.h>
#include<vector>

using namespace std;

class HypothesesGenerator{
    protected:
        //nome do gerador de hipoteses
        string name;

        //classe que gerencia a aleatoriedade do Learner
        Random randomState = NULL;

        //semente de aleatoriedade
        int seed;

        //quantidade de hipoteses distintas que devem ser geradas
        int n;

        //quantidade de exemplos do conjunto de dados
        int m;

        //flag que indica se o conjunto de hipoteses contem a hipotese perfeita
        //no momento é assumido que isso é sempre verdade
        bool hasPerfect=true;

        //lista de hipoteses que cada exemplo cobre
        vector<vector<int>> cover;

        //conjunto de hipoteses: so é armazenado os indices dos exemplos errados de cada hipotese
        vector<vector<int>> H;

        //acuracia de cada hipotese
        vector<double> acc;

        //bool diz se a lista de indices errados esta ordenada
        vector<bool> sorted;

        //metodo que gera o conjunto de hipoteses
        virtual void generateH() = 0;

    public:
        //metodos getters e setters
        string getName() const{return name;}
        int getSeed() const{return seed;}
        int getN() const{return n;}
        bool getHasPerfect() const{return hasPerfect;}
        vector<int> getCover(int i) const{return cover[i];}
        vector<int> getH(int i) const{return H[i];}
        int getM() const{return m;}
        double getAcc(int i) {return acc[i];}
        vector<double> const & getAcc(){return acc;}
        bool getSorted(int i) {return sorted[i];}
        void setSorted(int i, bool value){this->sorted[i]=value;}
        void sortH(int i){
            sort(this->H[i].begin(), this->H[i].end());
            this->sorted[i] = true;
        }
};

#endif // HYPOTHESES_GENERATOR_H

