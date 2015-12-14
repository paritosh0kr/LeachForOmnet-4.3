/*

 * bs.h
 *
 *  Created on: 05-Nov-2013
 *      Author: PARITOSH
 */




#ifndef BS_H
#define BS_H

#include <omnetpp.h>
#include "solar.h"
#include "node.h"
#include "nodebase.h"

/**
 * Implements the base station
 */
class BS : public NodeBase
{

    // this is a macro; it expands to constructor definition etc.
    // 0 says that we use MessageHandlers, not activity()
public:
    void initNodes();
    virtual void initialize(void);
    virtual void handleMessage(cMessage * msg);
    void resetStatus();
    void computeBest();
    void finish();

    int xpos;                   // just for simulation
    int ypos;

    int nrStatusRec;            // number of received status
    //  struct _adv advInfo[NR_CLUSTERS];
    struct _adv advInfo[104];   // XXX

    cModule *nodePtr[104];

    int roundEnergyLoss;
    int xMax;
    int yMax;
    int roundsDone;
    int nrRounds;
    int firstDead;

    int roundTimes[400];        // XXX times when round starts
    int sunnyNodes[400];
    int deadRound[400];
    int sunnyCtr;
    int calledEnd;
    int solarOn;
    int halfDead;
    int halfDeadCtr;
    int oldDeadNodes;
    int deadNodes;
    int sunNodes;
    int sunDuration;
};

#endif
