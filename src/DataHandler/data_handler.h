/*
 * Modulo responsavel por ler o arquivo de entrada e instanciar os objetos
 * Autor: Francisco Sergio de Freitas Filho
*/

#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "HypothesesGenerator/hypotheses_generator.h"
#include "Learners/learner.h"
#include "Teachers/teacher.h"

using namespace std;

//Esta classe e responsavel por ler o arquivo de entrada e instanciar os objetos
class DataHandler{
private:
    std::string output_path;
    std::string output_folder;
    std::string configPath;
    std::vector<std::string> teachersLine;
    std::vector<std::string> learnersLine;
    std::vector<std::string> hypothesesLine;
    int numExamples, numHypotheses, teacherRepetitions, learnerRepetitions;

    std::vector<HypothesesGenerator*> getSimpleRandomHypotheses(vector<string> &hypothesis);
    std::vector<Learner*> getRandomLearners(vector<HypothesesGenerator*> hypotheses);
    std::vector<Learner*> getAdversaryLearners(vector<HypothesesGenerator*> hypotheses);
    std::vector<Teacher*> getPacTeacher();
    std::vector<Teacher*> getWeightsTheoreticalFoundedTeacher();
    std::vector<std::string> getList(std::string line);
    void setSolutionPath(std::string line);

public:
    DataHandler(string configPath);
    const std::vector<std::string> split(const std::string& s, const char& c);

    std::vector<std::string> getHypothesesLine() const;
    int getNumExamples() const;
    int getNumHypotheses() const;
    int getTeacherRepetitions() const;
    int getLearnerRepetitions() const;
    std::vector<std::string> getLearnersLine() const;
    std::vector<std::string> getTeachersLine() const;
    std::string getOutput_path() const;
    std::string getOutput_folder() const;
    void generateGraphic();

    // Funcao que cria, inicializa e retorna os conjuntos de  hipoteses
    std::vector<HypothesesGenerator*> getHypotheses();

    // funcao que cria, inicializa e retorna os learners
    std::vector<Learner*> getLearners(vector<HypothesesGenerator *> hypotheses);

    // funcao que cria, inicializa e retorna os teachers
    std::vector<Teacher *> getTeachers();

};

#endif // DATA_HANDLER_H
