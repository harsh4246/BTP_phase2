#include "Gene.h"
#include <iostream>

using namespace std;

Gene::Gene(double * gene)
{
    for (int i=0;i<15;i++){
        this->geneticSequence[i]=gene[i];
    }
}

Gene::~Gene()
{
    //cout<<"Hello my score is "<<score<<" signing off"<<endl;
}



double* Gene:: getGeneticSequence(){
    return this->geneticSequence;
}
