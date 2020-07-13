/*
 * Modulo responsavel por realizar testes unitarios
 * Autor: Francisco Sergio de Freitas Filho
*/
#ifndef UNITTESTS_H
#define UNITTESTS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HypothesesGenerator/simple_random_hypotheses.h"
#include "Teachers/pac_teacher.h"
#include "Teachers/weights_theoretical_founded.h"
#include "Learners/random_learner.h"
#include "Learners/adversary_learner.h"
#include "Utils/util_random.h"


class UnitTests
{
public:
    UnitTests();
    //testa a funcao get_h() que gera hipóteses
    std::pair<bool, std::string> testget_h() const;

    //testa a funcao Teaching do PacTeacher
    std::pair<bool, std::string> testTeachingPacTeacher() const;

    //testa a funcao getExample do WTF
    std::pair<bool, std::string> testGetExamplesWTF() const;

    //testa a funcao teaching do WTF
    std::pair<bool, std::string> testTeachingWTF() const;

    //testa as funcoes choices de Random
    std::pair<bool, std::string> testChoice() const;




};

#endif // UNITTESTS_H
