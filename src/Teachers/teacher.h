/*
 * Modulo responsavel por definir um Teacher
 * Autor: Francisco Sergio de Freitas Filho
*/

#ifndef TEACHER_H
#define TEACHER_H
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include "../Utils/util_random.h"
#include "../Learners/learner.h"

using namespace std;


class Teacher{
    protected:
        int seed;
        string name;
        Random randomState = NULL;

    public:
        virtual pair<vector<int>, string> teaching(Learner &learner) = 0;
        string getName() const {return this->name;}
        int getSeed() const {return this->seed;}
        double getAccS(vector<int>& V, vector<int>& S){
            if (S.size() == 0) return 1.000000000;
            double n = 0;
            for (auto x : V){
                if (find (S.begin(), S.end(), x) != S.end())  n += 1.0000000000;
            }
            return 1.000000000000 - (n/(double) S.size());
        }
};

#endif // TEACHER_H

