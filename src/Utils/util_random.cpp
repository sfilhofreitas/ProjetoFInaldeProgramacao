#include "util_random.h"
#include<random>

Random::Random(int seed){
    this->seed = seed;
    this->rng = mt19937(this->seed);
    this->generator = default_random_engine(this->seed);
    this->real_distribution = uniform_real_distribution<double>(0.0, 1.0);
    this->int_distribution = uniform_int_distribution<int> (0,MAX_INT);
}

double Random::random(){
    return ((double) this->rng() / (rng.max()));
    //return this->real_distribution(this->generator);

}

vector<double> Random::random(int n){
    vector<double> randomNumbers;
    for(int i=0; i<n; i++)
        randomNumbers.push_back(this->random());
    return randomNumbers;
}

int Random::randInt(int min, int max){
    return min + (this->rng() % (max-min));
    //return min + (this->int_distribution(this->generator) % (max-min));
}

vector<int> Random::choice(int n, int k, vector<double> p){
    vector<int> selected(k);
    int v[n];
    for(int i=0; i<n; i++)
        v[i] = i;
    double sumSelected = 0.0;
    for(int i=0; i<k; i++){
        double ac = 0.0;
        double x = this->random();
        for (int j=i; j<n; j++){
            ac += p[j]/(1.0-sumSelected);
            if (x<ac){
                selected[i] = v[j];
                sumSelected += p[j];
                swap(p[i], p[j]);
                swap(v[i], v[j]);
                break;
            }
        }
    }
    return selected;
}


vector<int> Random::choice(int n, int k){
    vector<int> selected(k);
    int v[n];
    for(int i=0; i<n; i++)
        v[i] = i;
    int x;
    for(int i=0; i<k; i++){
        x = this->randInt(i, n);
        selected[i] = v[x];
        swap(v[i], v[x]);
    }

    return selected;

}


vector<int> Random::choice(vector<int> v, int k){
    vector<int> index = this->choice(v.size(), k);
    vector<int> selected;
    for(int i: index)
        selected.push_back(v[i]);
    return selected;
}

vector<int> Random::choice(vector<int> v, int k, vector<double> p){
    vector<int> index = this->choice(v.size(), k, p);
    vector<int> selected;
    for(int i: index)
        selected.push_back(v[i]);
    return selected;
}

void Random::shuffle(vector<int> &v){
    for(unsigned int i = 0; i<v.size()-1; i++){
        int id = this->randInt(i, v.size());
        swap(v[i], v[id]);
    }

}

void Random::reset(){
    //this->rng = mt19937(this->seed);
}
