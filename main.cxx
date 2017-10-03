#include <vector>
#include "TObject.h"
#include <string>
#include <iostream>
#include "tbjcArray.h"
#include "tbjcClonesArray.h"
using namespace std;
#include "FairRunAna.h"
#include "FairParSet.h"
#include "FairRuntimeDb.h"

#include "ATDigiPar.hh"
#include "ATDecoder2Task.hh"
#include "ATPSATask.hh"
#include "ATPhiRecoTask.hh"
#include "ATHoughTask.hh"
#include "ATAnalysisTask.hh"
int test5(int argc, char* argv[])
{
    TString dataFile = "runfiles/1.txt";
    TString parameterFile = "pATTPC.ND2015.par";

    TString scriptfile = "LookupProto20150331.xml";
    TString protomapfile = "proto.map";
    TString dir = getenv("VMCWORKDIR");
    TString scriptdir = dir + "/scripts/"+ scriptfile;
    TString protomapdir = dir + "/scripts/"+ protomapfile;
    TString geo = "proto_geo_hires.root";
    TString paraDir = dir + "/parameters/";

    FairRunAna* run = new FairRunAna(argv[1]);

    TString paramterFileWithPath = paraDir + parameterFile;

    FairRuntimeDb* rtdb = run->GetRuntimeDb();

    ATDigiPar * fPar = new ATDigiPar();
    rtdb->addContainer("ATDigiPar",(FairParSet*)fPar);

    // FairTask should not be released manually//
    // when the root task is deleted, all child//
    //  will be released sequentially//

    ATDecoder2Task *decoderTask = new ATDecoder2Task();
    decoderTask ->SetMapOpt(1);

    //decoderTask->AddData("data/75_8.graw");

    for(int i=2; i<argc; i++)
    decoderTask->AddData(argv[i]);

    decoderTask ->SetGeo("map/proto_geo_hires.root");
    decoderTask ->SetProtoMap("map/proto.map");
    decoderTask ->SetMap("map/LookupProto20150331.xml");
    // starting event number
    decoderTask->SetEventID(0);
    run -> AddTask(decoderTask);

    ATPSATask *psaTask = new ATPSATask();
    psaTask -> SetPersistence();
    //psaTask -> SetBackGroundPeakFinder(kFALSE); // Suppress background of each pad for noisy data (Larger computing Time)
    psaTask -> SetBackGroundPeakFinder(kFALSE);
    psaTask -> SetThreshold(20);
    psaTask -> SetPeakFinder(); //Note: For the moment not affecting the prototype PSA Task
    run -> AddTask(psaTask);

    ATPhiRecoTask *phirecoTask = new ATPhiRecoTask();
    phirecoTask -> SetPersistence();
    run -> AddTask(phirecoTask);

    ATHoughTask *HoughTask = new ATHoughTask();
    HoughTask->SetPhiReco();
    HoughTask->SetPersistence();
    HoughTask->SetLinearHough();
    HoughTask->SetRadiusThreshold(3.0); // Truncate Hough Space Calculation
    //HoughTask ->SetCircularHough();
    run ->AddTask(HoughTask);

    ATAnalysisTask *AnaTask = new ATAnalysisTask();
    AnaTask->SetPhiReco();
    AnaTask->SetHoughDist(2.0);
    AnaTask->SetPersistence(kTRUE);
    run->AddTask(AnaTask);

    cout<<"tt"<<run->GetNTasks()<<endl;
    run->Init();
    //run->Run(0,3);
    run -> RunOnTBData();
    //  delete psaTask; TTask
    //  delete decoderTask;
    delete fPar;
    delete run;

    cout<<"thing should be finished"<<endl;
}

int main(int argc, char* argv[])
{

    if(argc<2)
    {
        cout<<"provide the file name please"<<endl;
        exit(1);
    }

    for(int i;i<sizeof(argv)/sizeof(char*);i++)cout<<argv[i]<<endl;

    test5(argc,argv);
    return 1;
}
