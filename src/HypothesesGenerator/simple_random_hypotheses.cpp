/*
 * Modulo responsavel por gerar o conjunto de hipoteses
 * Autor: Francisco Sergio de Freitas Filho
*/

#include "simple_random_hypotheses.h"

SimpleRandomHypotheses::SimpleRandomHypotheses(int n, int m, vector<double> accList, double hardSamples, double hardFrac, int seed){
    this->name = "SimpleRandomHypotheses";
    this->n = n;
    this->m = m;
    this->accList = vector<double>(accList);
    this->hardSamples = hardSamples;
    this->hardFrac = hardFrac;
    this->seed = seed;
    this->randomState = Random(this->seed);
    this->cover = vector<vector<int>>(this->m, vector<int>());
    this->hasPerfect = true; //futuramente pode fazer sentido nao ter a hipotese perfeita
    this->c=0;
    this->sum = vector<int>(this->n, 0);
    this->acc = vector<double>(this->n, 0);
    this->sorted = vector<bool>(this->n, false);
    this->generateH();
}


int SimpleRandomHypotheses::getM() const
{
    return m;
}

//funcao que gera conjunto de hipoteses
void SimpleRandomHypotheses::generateH(){
    int k = this->hasPerfect ? 1:0;
    while (this->c<(this->n-k)) {
        vector<int> h = this->get_h();
        bool insert = true;
        for(unsigned int i=0; i<this->H.size(); i++){
            if ( (this->sum[this->c] == this->sum[i]) &&
                 (h.size() == this->H[i].size()) ){
                if(!this->sorted[this->c]){                    
                    sort(h.begin(), h.end());
                    this->sorted[this->c] = true;
                }
                if(!this->sorted[i]){
                    this->sortH(i);
                }
                if(h == this->H[i]){
                    insert = false;
                    this->sorted[this->c] = false;
                    break;
                }
            }
        }
        if (insert){
            this->H.push_back(h);
            for(int x: h){
                this->cover[x].push_back(this->c);
            }
            this->c++;
        }
    }
    if(this->hasPerfect){
        this->H.push_back(vector<int>());
        this->acc.back() = 1.0;
        this->sorted[this->n] = true;
    }

}


//funcao que gera uma hipotese obedecendo as proporcoes definidas em simple_random_hypotheses.h
vector<int> SimpleRandomHypotheses::get_h(){
    double e = 1.0 - this->accList[this->randomState.randInt(0,this->accList.size())];
    int k = round(this->m*e);
    int n_hard_samples = (int) k*this->hardFrac;

    vector<int> hardH = randomState.choice((int) this->m*this->hardSamples, n_hard_samples);

    vector<int> candidates;
    for(int i=((int) this->m * this->hardSamples); i<this->m; i++)
        candidates.push_back(i);
    vector<int> easyH = randomState.choice(candidates, k-n_hard_samples);

    easyH.insert(easyH.end(), hardH.begin(), hardH.end());
    int s = 0;
    for (unsigned int i=0;i<easyH.size(); i++)
        s += easyH[i];
    this->sum[this->c] = s;
    this->acc[this->c] = 1.0 - (((double) easyH.size())/ ((double) this->m));

    return easyH;

}

