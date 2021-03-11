#include "geneticfunctions.h"
#include"Gene.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>




bool compareScore( Gene &a,Gene &b ){
    return (a.score < b.score);
}


void printGene(double* gene){
    for (int i=0;i<15;i++){
        cout<<gene[i]<<" ";
    }
}

void createRandomGene(double* randGene){

  for (int i=0;i<3;i++){
    randGene[i]=(((double) rand()/RAND_MAX)*10);
  }


  for (int i=3;i<15;i++){
    randGene[i]=((double) rand()/RAND_MAX);
  }


  //ensuring w1>w2 for target

  if(randGene[3]<randGene[4]){
    randGene[4]= (((double) rand()/RAND_MAX)*randGene[3]);
  }

  //ensuring a1<a2 for target

  if(randGene[10]<randGene[9]){
    randGene[9]=(((double) rand()/RAND_MAX)*randGene[10]);
  }

  //ensure obstacle goes from -ve desire to positive when near i.e a2!<a1 and w1!>w2

  if(randGene[11]>randGene[12] && randGene[5]>randGene[6]){
    randGene[5]=(((double) rand()/RAND_MAX)*randGene[6]);
  }

  //ensure drones interaction goes from -ve desire to positive when near i.e a2!<a1 and w1!>w2

  if(randGene[11]>randGene[12] && randGene[7]>randGene[8]){
    randGene[7]=(((double) rand()/RAND_MAX)*randGene[8]);
  }



}

void reorderOnScore(vector <Gene> &geneCandidates){
    sort(geneCandidates.begin(),geneCandidates.end(), compareScore);
}


void performanceOfGenes(vector <Gene> &geneCandidates, double w1 , double w2){
    for (int i=0;i<geneCandidates.size();i++){
        double score;
        //cost fn (w1*A+w2)*Tm
        //both w1 and w2 are percentages and hence <1 && >0
        score = w1*geneCandidates[i].percentTargets + w2;
        score*=geneCandidates[i].percentTime;
        //cout<<score<<" "<<geneCandidates[i].percentTargets<<" "<<geneCandidates[i].percentTime<<endl;
        geneCandidates[i].score=score;
    }
}


void mateGenes(vector <Gene> &parentGenes , vector <Gene> &OffspringGenes){

    for (int j=0;j<2;j++){
        double gene1[15];
        double gene2[15];
        for (int i=0;i<15;i++){
            double randomNum1=((double) rand()/RAND_MAX);
            double randomNum2=((double) rand()/RAND_MAX);
            gene1[i]=randomNum1*parentGenes[j].geneticSequence[i]+(1-randomNum1)*parentGenes[j+1].geneticSequence[i];
            gene2[i]=randomNum2*parentGenes[j].geneticSequence[i]+(1-randomNum2)*parentGenes[j+1].geneticSequence[i];
        }
        OffspringGenes.push_back(Gene(gene1));
        OffspringGenes.push_back(Gene(gene2));
    }

}


void eliminateGenes(vector <Gene> &geneCandidates){

    for (int i=geneCandidates.size()-1;i>3;i--){
        geneCandidates.erase(geneCandidates.begin()+i);
    }
}


void regeneratePopulation(vector <Gene> &geneCandidates, vector <Gene> &OffspringGenes){
    geneCandidates.insert(geneCandidates.end(), OffspringGenes.begin(), OffspringGenes.end());

    for (int i=8;i<20;i++){
        double randGene[15];
        createRandomGene(randGene);
        geneCandidates.push_back(Gene(randGene));
    }
}


void generateScore(vector <Gene> &Generation , vector <target>  &targets, double duration, vector <vehicle> &swarm,  vector <obstacle> &obstacles, double frameTime , int * boundary){
        vector <target> defaultInitialTargets = targets;
        vector <vehicle> defaultIntialSwarm = swarm;
        vector <thread> lifeOfMembers(Generation.size());

        for (int j=0;j<Generation.size();j++){
            targets=defaultInitialTargets;
            swarm=defaultIntialSwarm;
            if(Generation[j].score != 1.0001){
                cout<<"found already calculated"<<endl;
                continue;
            }

            for (int i=0;i<swarm.size();i++){
                swarm[i].hit=false;
            }
            //singleDroneSim((Generation[j]),(targets),duration,(swarm),(obstacles),frameTime,boundary);
            lifeOfMembers[j]=thread(singleDroneSim, std::ref(Generation[j]),std::ref(targets),duration,std::ref(swarm),std::ref(obstacles),frameTime,boundary);
        }

        for (int i=0;i<lifeOfMembers.size();i++){
            if(lifeOfMembers[i].joinable()){
                cout<<"Life "<<lifeOfMembers[i].get_id()<<endl;
                lifeOfMembers[i].join();
            }else{
                cout<<"not feasible"<<endl;
            }
        }

        targets=defaultInitialTargets;
        swarm=defaultIntialSwarm;
}

void singleDroneSim(Gene &gene, vector <target>  &targets, double duration, vector <vehicle> &swarm,  vector <obstacle> &obstacles, double frameTime , int * boundary){
    cout<<"my thread "<<this_thread::get_id<<endl;
    //while(1){};
    double currTime=0.0;
    int totalTargets = targets.size();
    while(currTime<duration){

                if(targets.size()==0){
                    cout<<"all targets mapped"<<endl;
                    break;
                }


                for (int i=0;i<swarm.size();i++){
                    if(swarm[i].hit){
                        continue;
                    }
                    swarm[i].Aim(swarm,targets,obstacles,gene.getGeneticSequence());
                }
                for (int i=0;i<swarm.size();i++){
                    if(swarm[i].hit){
                        continue;
                    }
                    swarm[i].Action( duration, frameTime, boundary);
                }
                currTime+=frameTime;
            }

    gene.percentTime=currTime/duration;
    gene.percentTargets=targets.size()/totalTargets;
}
