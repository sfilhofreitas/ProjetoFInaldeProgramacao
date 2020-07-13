/*
 * Modulo responsavel por definir um Learner adversario
 * Autor: Francisco Sergio de Freitas Filho
*/

#include "adversary_learner.h"

//funcao que busca a hipotese com menor erro no conjunto de hipoteses
//seguindo uma ordem aleatoria predefinida
int AdversaryLearner::getIndexMinElement(){
    int min_id = index[0];
    int min_elem = errors_h[index[0]];
    if(min_elem == 0) return index[0];
    for(unsigned int i=1; i<errors_h.size(); i++){
        if(errors_h[index[i]]<min_elem){
            if(min_elem == 0) break;
            min_id = index[i];
            min_elem = errors_h[index[i]];
        }
    }
    return min_id;
    }


AdversaryLearner::AdversaryLearner(HypothesesGenerator *hipGenerator, int seed){
    this->name = "AdversaryLearner";
    this->hypGenerator = hipGenerator;
    this->n = hipGenerator->getN();
    this->seed = seed;
    this->randomState = Random(this->seed);

    int k = this->n - (this->hypGenerator->getHasPerfect() ? 1:0);
    for(int i=0; i<k; i++)
        this->index.push_back(i);
    this->randomState.shuffle(this->index);
    if(this->hypGenerator->getHasPerfect())
        this->index.push_back(this->n - 1);
    stable_sort(this->index.begin(), this->index.end(), [this] (int i, int j) {return this->hypGenerator->getAcc(i) < this->hypGenerator->getAcc(j);});//this->comp);

    this->errors_h = vector<int>(this->n, 0);
    this->index_start = 0;

    }


//funcao que seleciona qual hipotese retornar para o teacher
vector<int> AdversaryLearner::get_h(const vector<int> &samples){
    for(unsigned int i=this->index_start; i<samples.size(); i++){
        vector<int> const &v = this->hypGenerator->getCover(samples[i]);
        for(unsigned int j=0; j<v.size(); j++)
            errors_h[v[j]] += 1;
    }
    this->index_start = samples.size();

    int min_index = getIndexMinElement();
    return this->hypGenerator->getH(min_index);
}

//funcao para resetar o Learner
void AdversaryLearner::restart(){
    this->index_start = 0;
    fill(this->errors_h.begin(), this->errors_h.end(), 0);
}
