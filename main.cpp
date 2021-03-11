#include <iostream>
#include "vehicle.h"
#include <vector>
#include <fstream>
#include "Gene.h"
#include "geneticFunctions.h"
#include <cstdlib>
#include <ctime>



using namespace std;

int main()
{
    srand(time(NULL));
    int numDrones;
    int numObstacles;
    int numTargets;


    vector <vehicle> swarm;
    vector <target> targets;
    vector <obstacle> obstacles;


    cout<<"Enter numDrones numObstacles numTargets "<<endl;
    cin>>numDrones>>numObstacles>>numTargets;

    //information concerning each swarm member is taken

    for (int i=0;i<numDrones;i++){
        double weight;
        cout<<"Enter weight of drone"<<endl;
        cin>>weight;

        int maxForce;
        cout<<"enter the max force drone can apply"<<endl;
        cin>>maxForce;

        double maxVel;
        cout<<"Enter the max velocity drone can sustain"<<endl;
        cin>>maxVel;

        double position[3];
        cout<<"Enter Drone position in space separated triads"<<endl;
        cin>>position[0]>>position[1]>>position[2];

        double velocity[3];
        cout<<"Enter Drone current velocity in space separated triads"<<endl;
        cin>>velocity[0]>>velocity[1]>>velocity[2];

        double direction[3];
        cout<<"Enter the current direction in which velocity is present"<<endl;
        cin>> direction[0]>>direction[1]>>direction[2];


        swarm.push_back(vehicle(false, weight,maxForce, maxVel, position, velocity, direction ));
    }



    ofstream obstaclefile("obstacles.dat", ios::app);


    //information concerning each obstacle is taken

    for (int i=0;i<numObstacles;i++){
        double position[3];
        cout<<"Enter Obstacle position in space separated triads"<<endl;
        cin>>position[0]>>position[1]>>position[2];
        obstaclefile<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;


        double tolerance;
        cout<<"Enter the tolerance that the obstacle has"<<endl;
        cin>>tolerance;

        obstacles.push_back(obstacle(position , tolerance));

    }

    obstaclefile.close();

    //information concerning each target is taken

    ofstream targetfile("targets.dat", ios::app);

    for (int i=0;i<numTargets;i++){
        double position[3];
        cout<<"Enter target position in space separated triads"<<endl;
        cin>>position[0]>>position[1]>>position[2];
        targetfile<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;

        double tolerance;
        cout<<"Enter the tolerance that the target has"<<endl;
        cin>>tolerance;

        targets.push_back(target( position, tolerance));
    }



    targetfile.close();


    cout<<"Enter the boundary values simulation"<<endl;
    int boundary[3];
    for (int i=0;i<3;i++){
        cin>>boundary[i];
    }

    double frameTime;
    cout<<"Enter the frame time you want to simulate the drone environment"<<endl;
    cin>>frameTime;




    double duration;
    cout<<"Enter the duration you want to simulate"<<endl;
    cin>>duration;

    //removed from here


     vector <Gene> fittestSurvivers;

    for (int j=0;j<1;j++){

        vector <Gene> Generation;


        for (int i=0;i<20;i++){
            double randGene[15];
            createRandomGene(randGene);
            Generation.push_back(Gene(randGene));
        }

        for (int i=0;i<2;i++){
            cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Generation "<<i<<" Earth " <<j<<endl;
            vector <Gene> Offsprings;
            cout<<Generation.size()<<"intitial gen"<<endl;
            generateScore(Generation, targets, duration, swarm ,  obstacles, frameTime, boundary);
            performanceOfGenes(Generation, 1 , 0.0001);
            reorderOnScore(Generation);
            mateGenes(Generation, Offsprings);
            cout<<Offsprings.size()<<"initial off"<<endl;
            //generateScore(Offsprings, targets, duration, swarm ,  obstacles, frameTime, boundary);
            //performanceOfGenes(Offsprings, 1 , 0.0001);
            //reorderOnScore(Offsprings);
            eliminateGenes(Generation);
            //eliminateGenes(Offsprings);

            cout<<Generation.size()<<"final gen"<<endl;
            cout<<Offsprings.size()<<"final off"<<endl;
            regeneratePopulation(Generation, Offsprings);
            //reorderOnScore(Generation);
//            for(int m=0;m<20;m++){
//
//                printGene(Generation[m].getGeneticSequence());
//                cout<<Generation[m].score<<endl;
//            }
        }

        reorderOnScore(Generation);
        fittestSurvivers.push_back(Generation[0]);


    }






        //reorderOnScore(Generation);
            //performanceOfGenes(fittestSurvivers, 1 , 0.0001);
            reorderOnScore(fittestSurvivers);



    cout<<endl<<endl<<"--------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<fittestSurvivers.size();i++){
        printGene(fittestSurvivers[i].getGeneticSequence());
        cout<<fittestSurvivers[i].score<<endl;
    }





    cout<<"thank you"<<endl;


    return 0;
}
