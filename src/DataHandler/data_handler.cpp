/*
 * Modulo responsavel por ler o arquivo de entrada e instanciar os objetos
 * Autor: Francisco Sergio de Freitas Filho
*/

#include "data_handler.h"

#include "HypothesesGenerator/simple_random_hypotheses.h"
#include "Learners/random_learner.h"
#include "Teachers/pac_teacher.h"
#include "Teachers/weights_theoretical_founded.h"
#include "Learners/adversary_learner.h"

//funcao para remover espacos desnecessarios
std::string removeExtraSpaces(std::string str){
    int n = str.length();
    std::string newStr = "";
    int i=0;
    int j=n-1;
    for(i=0; i<n; i++)
        if(str[i] != ' ') break;
    for(j=n-1; j>0; j--)
        if(str[j] != ' ') break;

    int k=0;
    while(i<=j){
        if(str[i]!='\r' && ((str[i] != ' ') || (newStr[k-1] != ' '))){
            newStr += str[i];
            k++;
        }
        i++;
    }
    return newStr;
}
//Lendo arquivo de configuracao
DataHandler::DataHandler(string configPath){
    this->configPath = configPath;
    std::string line = "";
    std::ifstream config(this->configPath);

    if (config.is_open()){
       getline (config,line);
       this->setSolutionPath(line);
       getline (config,line);
       teachersLine = this->getList(line);
       getline (config,line);
       learnersLine = this->getList(line);
       getline (config,line);
       hypothesesLine = this->getList(line);
       getline (config,line);
       numExamples = stoi(this->getList(line)[0]);
       getline (config,line);
       numHypotheses = stoi(this->getList(line)[0]);
       getline (config,line);
       teacherRepetitions = stoi(this->getList(line)[0]);
       getline (config,line);
       learnerRepetitions = stoi(this->getList(line)[0]);
       config.close();
     }
     else{
        std::string message = "\nErro ao tentar ler o arquivo de configuracao. "
                        "O arquivo deve estar no mesmo diretorio do executavel"
                        " ou seu caminho deve ser explicitado ao executar!\n";
        std::cout << message;
        exit(-1);
     }

}

std::string current_datetime(){
    time_t timer;
    struct tm *horarioLocal;

    time(&timer); // Obtem informações de data e hora
    horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

    string dia = std::to_string(horarioLocal->tm_mday);
    dia = dia.size() == 1 ? "0"+dia : dia;
    string mes = std::to_string(horarioLocal->tm_mon + 1);
    mes = mes.size() == 1 ? "0"+mes : mes;
    string ano = std::to_string(horarioLocal->tm_year + 1900);

    string hora = std::to_string(horarioLocal->tm_hour);
    hora = hora.size() == 1 ? "0"+hora : hora;
    string min  = std::to_string(horarioLocal->tm_min);
    min = min.size() == 1 ? "0"+min : min;
    string sec  = std::to_string(horarioLocal->tm_sec);
    sec = sec.size() == 1 ? "0"+sec : sec;

    return ano+mes+dia+hora+min+sec;
}

void DataHandler::setSolutionPath(std::string line){
    line = split(line, ':')[1];
    line = removeExtraSpaces(line);
    if(line[line.size()-1]=='/')
        line.erase(line.size()-1, line.size()-1);
    string timeNow = current_datetime();
    line += "_"+timeNow;
    this->output_folder = line+"/";
    this->output_path = line + "/"+timeNow + ".csv";
    if(system(("mkdir "+this->output_folder).c_str()) != 0){
        cout << "Erro ao criar o diretorio de saida!";
        exit(-1);
    }
    if(system(("cp "+this->configPath+" "+this->output_folder).c_str())){
        cout << "Erro ao copiar o arquivo de configuracao para o diretorio de saida!";
        exit(-1);
    }

}

const std::vector<string> DataHandler::split(const string &s, const char &c){
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s){
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

std::vector<std::string> DataHandler::getHypothesesLine() const{
    return hypothesesLine;
}

int DataHandler::getNumExamples() const
{
    return numExamples;
}

int DataHandler::getNumHypotheses() const
{
    return numHypotheses;
}

int DataHandler::getTeacherRepetitions() const
{
    return teacherRepetitions;
}

int DataHandler::getLearnerRepetitions() const
{
    return learnerRepetitions;
}

std::vector<std::string> DataHandler::getLearnersLine() const
{
    return learnersLine;
}

std::vector<std::string> DataHandler::getTeachersLine() const
{
    return teachersLine;
}

std::string DataHandler::getOutput_path() const
{
    return output_path;
}

std::string DataHandler::getOutput_folder() const
{
    return output_folder;
}

void DataHandler::generateGraphic(){
    if(system(("python graphic.py "+this->output_folder+" "+this->output_path).c_str()))
        cout << "\nNao foi possivel gerar a visualizacao grafica. Tente executar o script manualmente!";

}

std::vector<string> DataHandler::getList(string line){
    std::vector<std::string> v;
    line = split(line, ':')[1];
    line = removeExtraSpaces(line);
    v = split(line, ',');
    for (unsigned int i=0; i<v.size(); i++){
        v[i] = removeExtraSpaces(v[i]);
    }
    return v;
}



//std::vector<RandomIterative> DataHandler::getRandomIterativeTeachers(std::string teacherStr){

//}

// **************************************************************************************************
// Implementacao da funcao que cria inicializa e retorna o conjunto de hipoteses aleatorias
vector<HypothesesGenerator*> DataHandler::getSimpleRandomHypotheses(vector<string> &hypothesis){
    vector<HypothesesGenerator*> hypotheses;
    vector<double> accList;
    for(string s: this->split(hypothesis[1], '_'))
        accList.push_back(stod(s));

    double hardSamples = stod(hypothesis[2]);
    double hardSamplesProp = stod(hypothesis[3]);

    for(int i=0; i<stoi(hypothesis[4]); i++)
        hypotheses.push_back(new SimpleRandomHypotheses(this->getNumHypotheses(),
                                 this->getNumExamples(), accList, hardSamples,
                                 hardSamplesProp, i));
    return hypotheses;
}


// Implementacao da funcao que chama a funcao que cria inicializa e retorna o conjunto
//de hipoteses do gerador de hipoteses escolhido
vector<HypothesesGenerator*> DataHandler::getHypotheses(){
    vector<HypothesesGenerator*> hypotheses;
    for(string h: this->getHypothesesLine()){
        vector<string> hypothesis = this->split(h, ' ');
        if(hypothesis[0] == "SimpleRandomHypotheses"){
            vector<HypothesesGenerator*> hyp = getSimpleRandomHypotheses(hypothesis);
            hypotheses.insert(hypotheses.end(), hyp.begin(), hyp.end());
        }else{
            cout << "Problem in creating instances of hypotheses generator, review the config file!";
            exit(-1);

        }
    }

    return hypotheses;
}

// **************************************************************************************************



// **************************************************************************************************
// Implementacao de funcoes que criam inicializam e retornam os learners escolhidos

vector<Learner*> DataHandler::getRandomLearners(vector<HypothesesGenerator*> hypotheses){
    vector<Learner*> learners;
    for(auto hipothesis: hypotheses){
        for(int i=0; i<this->getLearnerRepetitions(); i++){
            learners.push_back(new RandomLearner(hipothesis, i));
        }
    }
    return learners;
}


vector<Learner*> DataHandler::getAdversaryLearners(vector<HypothesesGenerator*> hypotheses){
    vector<Learner*> learners;
    for(auto hipothesis: hypotheses){
        for(int i=0; i<this->getLearnerRepetitions(); i++){
            learners.push_back(new AdversaryLearner(hipothesis, i));
        }
    }
    return learners;
}



// Implementacao da funcao que chama a funcao que cria inicializa e retorna os learners escolhidos
vector<Learner*> DataHandler::getLearners(vector<HypothesesGenerator*> hypotheses){
    vector<Learner*> learners;
    for(string l: this->getLearnersLine()){
        vector<string> learner = this->split(l, ' ');

        if(learner[0] == "RandomLearner"){
            vector<Learner*> learnersTemp = getRandomLearners(hypotheses);
            learners.insert(learners.end(), learnersTemp.begin(), learnersTemp.end());
        }else
        if(learner[0] == "AdversaryLearner"){
            vector<Learner*> learnersTemp = getAdversaryLearners(hypotheses);
            learners.insert(learners.end(), learnersTemp.begin(), learnersTemp.end());
        }else{
            cout << "Problem in creating instances of learners, review the config file!";
            exit(-1);
        }


    }
    return learners;
}

// **************************************************************************************************



// **************************************************************************************************
// Implementacao de funcoes que criam inicializam e retornam os Teachers escolhidos

vector<Teacher*> DataHandler::getPacTeacher(){
    vector<Teacher*> teachers;
    for(int i=0; i<this->getTeacherRepetitions(); i++)
        teachers.push_back(new PacTeacher(this->getNumExamples(), i));
    return teachers;
}


vector<Teacher*> DataHandler::getWeightsTheoreticalFoundedTeacher(){
    vector<Teacher*> teachers;
    for(int i=0; i<this->getTeacherRepetitions(); i++)
        teachers.push_back(new WeightsTheoreticalFounded(this->getNumExamples(), i));
    return teachers;
}

vector<Teacher*> DataHandler::getTeachers(){
    vector<Teacher*> teachers;
    for(string t: this->getTeachersLine()){
        vector<string> teacher = this->split(t, ' ');
        if(teacher[0] == "WeightsTheoreticalFounded"){
            vector<Teacher*> teachersTemp = getWeightsTheoreticalFoundedTeacher();
            teachers.insert(teachers.end(), teachersTemp.begin(), teachersTemp.end());
        }else
        if(teacher[0] == "PacTeacher"){
            vector<Teacher*> teachersTemp = getPacTeacher();
            teachers.insert(teachers.end(), teachersTemp.begin(), teachersTemp.end());
        }else{
            cout << "Problem in creating instances of teachers, review the config file!";
            exit(-1);
        }
    }

    return teachers;
}

// **************************************************************************************************

