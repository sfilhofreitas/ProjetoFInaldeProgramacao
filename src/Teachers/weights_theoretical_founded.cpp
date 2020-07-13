/*
 * Modulo responsavel por definir um Teacher que
 * atribui um peso para cada exemplo e seleciona
 * os exemplos baseado na variacao de pesos da
 * iteracao passada
 * Autor: Francisco Sergio de Freitas Filho
*/

#include "weights_theoretical_founded.h"

//funcao que seleciona os exemplos
vector<int> WeightsTheoreticalFounded::getExamples(vector<int> &Examples, vector<double> delta_w){
    vector<double> randomNumbers = randomState.random(this->n);
    sort(randomNumbers.begin(), randomNumbers.end());
    unsigned int i = 0;
    int j = 0;
    double aux = 0.0;
    bool flag = true;
    vector<int> S;
    while(j<this->n && i<Examples.size()){
        if (flag)
            aux += delta_w[i];
        flag = false;
        if(randomNumbers[j] <= aux){
            if(randomNumbers[j] > (aux-delta_w[i])){
                S.push_back(Examples[i]); //selecionando exemplo i
                flag = true;
                i++;
            }
            j++;
        }
        else{
            i++;
            flag = true;
        }
    }

    return S;

}

WeightsTheoreticalFounded::WeightsTheoreticalFounded(int m, int seed){
    this->name = "WeightsTheoreticalFounded";
    this->m = m;
    this->seed = seed;
    this->randomState = Random(this->seed);
    this->weights = vector<double>(this->m, 1.0/(2.0*this->m));
    this->n = 1;
}

pair<vector<int>, string> WeightsTheoreticalFounded::teaching(Learner &learner){
    learner.restart();
    this->randomState = Random(this->seed);
    fill(this->weights.begin(), this->weights.end(), 1.0/(2.0*this->m));
    this->n = 1;
    string log = "";
    vector<int> S;
    int i=0;
    bool flag = true;
    vector<int> samples;
    while(true){
        vector<int> delta_h = learner.get_h(S);

        double accS = this->getAccS(delta_h, S);
        double acc = 1.0 - ((double) delta_h.size()/(double) this->m);
        if(flag)
            log += to_string(i)+","+this->name+","+learner.getName()+","+learner.getHypGenerator()->getName()+","+
                   to_string(this->seed)+","+to_string(learner.getSeed())+","+to_string(learner.getHypGenerator()->getSeed())+
                   ","+to_string(samples.size())+","+to_string(S.size())+","+to_string(accS)+","+to_string(acc)+"\n";

        if(delta_h.size() == 0)
            break;

        double sum = 0.0;
        for(int x: delta_h)
           sum += this->weights[x];

        if(sum >= 1.0){//algoritmo falhou
            this->n *= 2; //dobrando a estimativa do tamanho do conjunto de hipoteses
            fill(this->weights.begin(), this->weights.end(), 1.0/(2.0*this->m));//resetando pesos
            sum = (1.0/(2.0*this->m)) * delta_h.size();
        }

        int k = 1;
        while(sum*k < 1.0)
            k *= 2;

        vector<double> delta_w(delta_h.size());
        double old_w;
        for(unsigned int j=0; j<delta_h.size(); j++){
            old_w = this->weights[delta_h[j]];
            this->weights[delta_h[j]] *= k;//incremento de peso
            delta_w[j] = (this->weights[delta_h[j]] - old_w)/2.0;//variacao de pesos dos exemplos
        }
        samples = this->getExamples(delta_h, delta_w);
        if(samples.size() != 0){
            S.insert(S.end(), samples.begin(), samples.end());
            flag = true;
            i++;
        }else{//algoritmo falhou
            flag = false;
            this->n *= 2; // aumentar estimativa
        }

    }
    return make_pair(S, log);
}
