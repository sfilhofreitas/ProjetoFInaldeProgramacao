/*
 * Modulo responsavel por definir um Teacher totalmente aleatorio
 * Esse teacher ignora o feedback do Learner
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef PAC_TEACHER_H
#define PAC_TEACHER_H
#include<string>
#include<vector>
#include<iostream>
#include "../Learners/learner.h"
#include "teacher.h"

using namespace std;

/*
 * Este teacher envia exemplos aleatoriamente sem se importar com o feedback do learner
 * Podendo, inclusive, mandar exemplos que o learner ja acerta
 */
class PacTeacher: public Teacher{
    //numero de exemplos
    int m;

    //lista de exemplos embaralhados
    vector<int> index;

    //ponteiro que aponta para o ultimo exemplo enviado da lista index
    int lastIndex;

    //Funcao na qual o teacher escolhe que exemplo enviar.
    //Nesse caso, o exemplo lastIndex+1 da lista index
    int get_example();

    public:
        PacTeacher(int m, int seed);

        //funcao onde ocorre onde o teacher interage com o learner e define o teaching set
        pair<vector<int>, string> teaching(Learner &learner);
};

#endif // PAC_TEACHER_H
