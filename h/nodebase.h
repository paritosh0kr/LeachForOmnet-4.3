/*
 * nodebase.h
 *
 *  Created on: 09-Nov-2013
 *      Author: PARITOSH
 */
#ifndef NODEBASE_H
#define NODEBASE_H

#include <omnetpp.h>
#include "solar.h"

/**
 * Base class for Node and BS.
 */
class NodeBase : public cSimpleModule
{

  protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage * msg) = 0;
    virtual void finish();
    void updateStats();
    void initStats();

  public:  //XXX
    cArray nHosts;              // XXX IT neighbouring hosts
    int myId;

    int myStatus;
    // SUNNY STUFF for stats
    int nrAllMsgBatt;
    int nrAllMsgSun;
    int nrDataBatt;
    int nrDataSun;
    int nrExplBatt;
    int sinkFromTwo;
    int sinkFromThree;

    // how many gates
    int nrGates;
    int nrNodes;
};

extern void updateStats();

#endif



