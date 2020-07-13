/*
 * Funcao main
 * Autor: Francisco Sergio de Freitas Filho
*/
#include <iostream>
#include<chrono>
#include<fstream>
#include<algorithm>
#include "HypothesesGenerator/simple_random_hypotheses.h"
#include "Learners/random_learner.h"
#include "Teachers/pac_teacher.h"
#include "Teachers/weights_theoretical_founded.h"
#include <exception>
#include "Learners/adversary_learner.h"
#include "DataHandler/data_handler.h"
#include "Tests/unittests.h"

using namespace std;

int main(int argc, char* argv[]){
    string configPath;
    if(argc==1)
        configPath = "config.txt";
    else if(string(argv[1]) == "--tests"){
        UnitTests();
        return 0;
    }else
        configPath = string(argv[1]);

    DataHandler dh = DataHandler(configPath);
    //auto start = std::chrono::high_resolution_clock::now();
    cout << "Criando hipoteses\n";
    vector<HypothesesGenerator*> hypotheses = dh.getHypotheses();

    cout << "Criando learners\n";
    vector<Learner*> learners = dh.getLearners(hypotheses);

    cout << "Criando teachers\n";
    vector<Teacher*> teachers = dh.getTeachers();

    cout << "Iniciando...\n";
    int tot = learners.size()*teachers.size();
    int i = 1;

    ofstream output_log(dh.getOutput_path());
    ofstream output_runtime(dh.getOutput_folder()+"runtime.txt");
    string logHeader = "ITER,TEACHER,LEARNER,HYPOTHESES GENERATOR,TEACHER SEED,LEARNER SEED,HYP_GENERATOR SEED,EXAMPLES_ITERATION,TEACHING SET SIZE,TEACHING SET ACCURACY,ACCURACY\n";
    output_log << logHeader;

    auto start = std::chrono::high_resolution_clock::now();
    for(auto learner: learners){
        for(auto teacher: teachers){
            cout << "Iter: "<<i << "\\"<<tot<<"\n";
            i++;

            if((learner->getSeed() != 0) && (teacher->getName() == "PacTeacher")) continue;

            pair<vector<int>, string> solution = teacher->teaching((*learner));
            output_log << solution.second;

        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    output_runtime << elapsed.count();
    output_log.close();
    output_runtime.close();
    dh.generateGraphic();
    return 0;
}
