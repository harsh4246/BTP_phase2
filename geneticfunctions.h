#ifndef GENETICFUNCTIONS_H
#define GENETICFUNCTIONS_H

#include "Gene.h"

#include <iostream>
#include <vector>
#include "target.h"
#include "vehicle.h"
using namespace std;


void createRandomGene(double* randGene);
void performanceOfGenes(vector <Gene> &geneCandidates, double w1 , double w2);
void generateScore(vector <Gene> &geneCandidates, vector <target>  &targets, double duration, vector <vehicle> &swarm,  vector <obstacle> &obstacles, double frameTime , int * boundary);
void reorderOnScore(vector <Gene> &geneCandidates);
void mateGenes(vector <Gene> &parentGenes , vector <Gene> &OffspringGenes);
void eliminateGenes(vector <Gene> &geneCandidates);
void regeneratePopulation(vector <Gene> &geneCandidates , vector <Gene> &OffspringGenes);
void printGene(double* gene);
void singleDroneSim(Gene &gene, vector <target>  &targets, double duration, vector <vehicle> &swarm,  vector <obstacle> &obstacles, double frameTime , int * boundary);


#endif // GENETICFUNCTIONS_H
