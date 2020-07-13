/*
 * Modulo responsavel por definir um Teacher totalmente aleatorio
 * Esse teacher ignora o feedback do Learner
 * Autor: Francisco Sergio de Freitas Filho
*/
#include "pac_teacher.h"

//funcao que seleciona exemplo: simplesmente pega o proximo
//de uma ordem aleatoria predefinida
int PacTeacher::get_example(){
    this->lastIndex++;
    return this->index[this->lastIndex-1];
}

PacTeacher::PacTeacher(int m, int seed){
    this->name = "PacTeacher";
    this->m = m;
    this->seed = seed;
    this->randomState = Random(this->seed);
    for(int i=0; i<this->m; i++)
        this->index.push_back(i);
    this->randomState.shuffle(index);
    this->lastIndex = 0;
}


//funcao que o teacher guia o learner para a hipotese alvo
pair<vector<int>, string> PacTeacher::teaching(Learner &learner){
    learner.restart();
    this->randomState = Random(this->seed);
    string log = "";
    vector<int> S;
    this->lastIndex = 0;
    int i=0;
    while(true){
        vector<int> delta_h = learner.get_h(S);
        double accS = this->getAccS(delta_h, S);
        double acc = 1.0 - ((double) delta_h.size()/(double) this->m);
        log += to_string(i)+","+this->name+","+learner.getName()+","+learner.getHypGenerator()->getName()+","+
               to_string(this->seed)+","+to_string(learner.getSeed())+","+to_string(learner.getHypGenerator()->getSeed())+
               ",1,"+to_string(S.size())+","+to_string(accS)+","+to_string(acc)+"\n";

        if(delta_h.size() == 0)
            break;

        S.push_back(this->get_example());
        i+=1;

    }
    return make_pair(S, log);

}
