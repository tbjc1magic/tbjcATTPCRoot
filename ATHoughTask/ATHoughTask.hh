#ifndef ATHOUGHTASK_H
#define ATHOUGHTASK_H

// FAIRROOT classes
#include "FairTask.h"
#include "FairLogger.h"

#include "ATHoughSpace.hh"
// ATTPCROOT classes
class ATEvent;
class ATProtoEvent;
class ATDigiPar;
class tbjcArray;

// ROOT classes
#include "TClonesArray.h"

class ATHoughTask : public FairTask {
  public:
    ATHoughTask();
    ~ATHoughTask();

    void SetPersistence(Bool_t value = kTRUE);
    void SetThreshold(Double_t threshold);
    void SetLinearHough();
    void SetCircularHough();
    void SetPhiReco(); //Hough Space is calculated for the prototype after sorting the hits by quadrant. Phi Reconstruction is
    // needed prior to this mode of the task
    void SetRadiusThreshold(Float_t value);
    void SetHoughThreshold(Double_t value);

    virtual InitStatus Init();
    virtual void SetParContainers();
    virtual void Exec(Option_t *opt);
    //virtual void FinishEvent();

  private:
    FairLogger *fLogger;

    ATDigiPar *fPar;

    tbjcArray *fEventHArray;
    tbjcArray *fProtoEventHArray;
    tbjcArray *fHoughArray;

    ATHoughSpace *fHoughSpace;
    ATEvent *fEvent;
    ATProtoEvent *fProtoevent;

    Bool_t fIsPersistence;
    Bool_t fIsLinear;
    Bool_t fIsCircular;
    Bool_t fIsPhiReco; //Hough Space applied after Phi Reconstruction to divide hits in quadrants

    Double_t fThreshold;
    Double_t fRadThreshold;
    Double_t fHoughThreshold;

    Int_t fInternalID;

};

#endif
