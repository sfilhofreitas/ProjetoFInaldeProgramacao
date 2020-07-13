/*
 * Modulo responsavel por realizar testes unitarios
 * Autor: Francisco Sergio de Freitas Filho
*/
#include "unittests.h"

UnitTests::UnitTests(){
    std::pair<bool, std::string> testResult;

    testResult = this->testget_h();
    std::cout << testResult.second<<endl;

    testResult = this->testTeachingPacTeacher();
    std::cout << testResult.second<<endl;

    testResult = this->testGetExamplesWTF();
    std::cout << testResult.second<<endl;

    testResult = this->testTeachingWTF();
    std::cout << testResult.second<<endl;

    testResult = this->testChoice();
    std::cout << testResult.second<<endl;

}

std::pair<bool, string> UnitTests::testget_h() const{
    std::vector<double> accList;
    accList.push_back(0.9);
    accList.push_back(0.95);
    int n=10001, m=100;

    //embora a funcao Hypotheses.get_h() nao esteja sendo chamada explicitamente
    //cada elemento Hypotheses.getH(i) representa uma chamada da funcao em questao
    SimpleRandomHypotheses Hypotheses(n, m, accList, 0.05, 0.5, 0);

    //testando se existe hipotese perfeita como ultimo elemento do conjunto: TESTE 1
    if(Hypotheses.getH(n-1).size() != 0)
        return std::pair<bool, std::string> (false, "Falha no metodo get_h(): TESTE 1");


    //testando se acuracias das hipoteses estao uniformente distribuidas: TESTE 2
    int count1=0, count2=0;
    for (int i=0; i<n-1; i++){
        if(Hypotheses.getH(i).size() == 10){ count1 ++;}
        else if (Hypotheses.getH(i).size() == 5){ count2 ++;}
    }
    double ratio = double(count1)/double(count2);
    if ((ratio < 0.97) || (ratio > 1.03) || (count1+count2 != n-1)) // usando um epsilon de 0.03
       return std::pair<bool, std::string> (false, "Falha no metodo get_h(): TESTE 2");



    //testando se a proporcao de exemplos dificeis e esta sendo respeitada: TESTE 3
    int countExampleZero = 0; //a faixa de exemplos dificeis comeca do exemplo 0
    for (int i=0; i<n-1; i++){
       for (int example : Hypotheses.getH(i)){
           if(example == 0){
               countExampleZero ++;
               break;
           }
        }
    }
    double expectedValueZero = ((n-1)/2.0)*(1+2/5.0);
    ratio = countExampleZero/expectedValueZero;
    if ((ratio < 0.97) || (ratio > 1.03))// usando um epsilon de 0.03
        return std::pair<bool, std::string> (false, "Falha no metodo get_h(): TESTE 3");


    return std::pair<bool, std::string> (true, "Metodo get_h() testado com sucesso");
}



std::pair<bool, string> UnitTests::testTeachingPacTeacher() const{
    int n=1000, m=100, seed=0;
    std::vector<double> accList;
    accList.push_back(0.9);
    accList.push_back(0.95);
    HypothesesGenerator* Hypotheses = new SimpleRandomHypotheses(n, m, accList, 0.05, 0.5, 0);
    PacTeacher pacTeacher(m, seed);
    RandomLearner randomLearner(Hypotheses,seed);
    AdversaryLearner adversaryLearner(Hypotheses, seed);
    pair<vector<int>, string> solution1 = pacTeacher.teaching(randomLearner);
    pair<vector<int>, string> solution2 = pacTeacher.teaching(adversaryLearner);

    //testando se o PacTeacher ta ignorando os learners e escolhendo aleatoriamente: TESTE 1
    if (solution1.first != solution2.first)
        return std::pair<bool, std::string> (false, "Falha no metodo teaching() do PacTeacher: TESTE 1");

    //testando se todos os elementos do teaching set sao distintos: TESTE 2
    std::vector<int>::iterator it;
    it = std::unique (solution1.first.begin(), solution1.first.end());
    solution1.first.resize( std::distance(solution1.first.begin(),it) );
    if (solution1.first != solution2.first)
        return std::pair<bool, std::string> (false, "Falha no metodo teaching() do PacTeacher: TESTE 2");


    return std::pair<bool, std::string> (true, "Metodo teaching() do PacTeacher testado com sucesso");


}

std::pair<bool, string> UnitTests::testGetExamplesWTF() const{
    WeightsTheoreticalFounded WTF(100, 0);
    std::vector<int> examples;
    std::vector<double> deltas;
    double sumDeltas = 0.0;
    for(int i=0; i<10; i++){
        examples.push_back(i);

        if(i%2 == 0)
            deltas.push_back(1/10.0);
        else
            deltas.push_back(1/20.0);

        sumDeltas += deltas[i];
    }

    int count = 0;// contador de vezes que nenhum exemplo foi selecionado
    int even = 0; // contador de vezes que um exemplo de indice par foi selecionado
    int odd = 0; // contador de vezes que um exemplo de indice impar foi selecionado

    for(int i=0; i<10000; i++){
        //selecionando um exemplo da lista examples cujas probabilidades dos exemplos sao dadas por delta
        std::vector<int> selectedExamples = WTF.getExamples(examples, deltas);
        if(selectedExamples.size() == 0)
            count++; //incrementando se nenhum exemplo foi selecionado
         else if(selectedExamples[0]%2 == 0)
            even++; //incrementando se o exemplo retornado tem indice par
        else
            odd++; //incrementando se o exemplo retornado tem indice impar
    }
    //testando a probabilidade de nao sortear nenhum exemplo: TESTE 1
    double ratio = count/((1-sumDeltas)*10000);
    if(ratio < 0.97 || ratio > 1.03)
        return std::pair<bool, std::string> (false, "Falha no metodo getExamples() do WTF: TESTE 1");

    //testando a probabilidade de sortear pares e impares: TESTE 2
    ratio = even/(2.0*odd); //e esperado que um numero par tenha duas vezes mais chances de ser sorteado do que um impar
    if(ratio < 0.97 || ratio > 1.03)
        return std::pair<bool, std::string> (false, "Falha no metodo getExamples() do WTF: TESTE 2");

    return std::pair<bool, std::string> (true, "Metodo getExamples() do WeightsTheoreticalFounded testado com sucesso");
}

std::pair<bool, string> UnitTests::testTeachingWTF() const{
    int n=1000, m=100, seed=0;
    std::vector<double> accList;
    accList.push_back(0.9);
    accList.push_back(0.95);
    HypothesesGenerator* Hypotheses = new SimpleRandomHypotheses(n, m, accList, 0.05, 0.5, 0);
    WeightsTheoreticalFounded WTF(m, seed);
    RandomLearner randomLearner(Hypotheses,seed);
    pair<vector<int>, string> solution1 = WTF.teaching(randomLearner);
    pair<vector<int>, string> solution2 = WTF.teaching(randomLearner);

    //testando se o WTF ta mantendo o mesmo resultado para uma mesma semente: TESTE 1
    if (solution1.first != solution2.first)
        return std::pair<bool, std::string> (false, "Falha no metodo teaching() do WTF: TESTE 1");

    //testando se todos os elementos do teaching set sao distintos: TESTE 2
    std::vector<int>::iterator it;
    it = std::unique (solution1.first.begin(), solution1.first.end());
    solution1.first.resize( std::distance(solution1.first.begin(),it) );
    if (solution1.first != solution2.first)
        return std::pair<bool, std::string> (false, "Falha no metodo teaching() do WTF: TESTE 2");


    return std::pair<bool, std::string> (true, "Metodo teaching() do WeightsTheoreticalFounded testado com sucesso");

}

std::pair<bool, string> UnitTests::testChoice() const{
    Random randomObj(0);

    //testando se a funcao choice uniforme bate com o valor esperado: TESTE 1
    int count1=0;
    for(int i=0; i<100000; i++){
        std::vector<int> randomNumbers = randomObj.choice(100, 5);
        for(int j=0; j<5; j++)
            if(randomNumbers[j] == 1)
                count1++;
    }
    double ratio = count1/(0.05*100000);
    if(ratio < 0.97 || ratio > 1.03)
        return std::pair<bool, std::string> (false, "Falha no metodo choice(n, k): TESTE 1");


    //testando se a funcao choice que recebe a distribuicao dos elementos bate com o valor esperado: TESTE 2
    count1=0;
    std::vector<double> probabilities;
    probabilities.push_back(0.1);
    probabilities.push_back(0.6);
    probabilities.push_back(0.1);
    probabilities.push_back(0.1);
    probabilities.push_back(0.1);
    for(int i=0; i<100000; i++){
        std::vector<int> randomNumbers = randomObj.choice(5, 1, probabilities);
        for(int j=0; j<5; j++)
            if(randomNumbers[j] == 1)
                count1++;
    }
    ratio = count1/(0.6*100000);
    if(ratio < 0.97 || ratio > 1.03)
        return std::pair<bool, std::string> (false, "Falha no metodo choice(n, k, dist: TESTE 2");



    return std::pair<bool, std::string> (true, "Metodo choice() testado com sucesso");

}
