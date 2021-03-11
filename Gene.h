#ifndef GENE_H
#define GENE_H
#include <limits.h>


class Gene
{
    public:
        Gene(double * gene);
        ~Gene();

        double geneticSequence[15];
        double score=1.0001;
        double percentTime=1;
        double percentTargets=1;



        double* getGeneticSequence();

};

#endif // GENE_H
