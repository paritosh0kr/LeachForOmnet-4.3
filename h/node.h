/*
 * node.h
 *
 *  Created on: 05-Nov-2013
 *      Author: PARITOSH
 */

#ifndef NODE_H
#define NODE_H

#include <omnetpp.h>
#include "solar.h"
#include "nodebase.h"
#include "bs.h"

/**
 * Represents a node in the network
 */
class Node : public NodeBase
{


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage * msg);
    virtual void finish();

    void sendExploratory(int src, int rec, char attr, int value, int data, int scount, int bcount,
                         int hopcount, int seqNumber);
    void sendData(int src, int rec, char attr, int value, int data, int scount, int bcount,
                  int mustShortest);
    void sendReinforcement(int src, int rec, char attr, int value, int bcount, int scount, int hops,
                           int seqNumber, int period, int strategy);

    void send2BS(int src, int rec, int energy, int status, int cluster, int xpos, int ypos);
    void initNodes();
    void sendTDMA();
    void sendDataToCHead(int newSun);
    void sendData2BS(int data);
    void energyReceive(int bits);
    void energyTransmit(int bits, int dist);
    void energyDataAggr(int signals);

  public:  //XXX
    int minhops;                // min hops to sink
    int minBCount;              // min hops with batteryCount

    int xpos;                   // just for simulation
    int ypos;
    int nrRounds;               // number of rounds (each round starts with setups)
    int nrFrames;               // number of "rounds in a round" (called frames)
    int curFrame;
    int frameTime;              // how many slots has one frame
    int myData;
    int mySlot;                 // slot in current frame
    int bsId;                   // ID of base station

    double energy;              // XXX energy in microJoule  XXX nnode.h
    int headDist;               // distance to head
    int bsDist;
    int myCluster;              // to which cluster this node belongs

    Node *nodePtr[103];
    int clusterNodes;

    int cHead;                  // flag denoting if I this node is cluster head
    int headId;                 // id of cluster head (my cluster)

    int nrDataPackets;          // nr of data packets head has received in this frame
    int sentBS;                 // how many status updates sent to BS by this node
    int wasHead;                // ctr denoting how often a node was cluster head
    int headSun;
    int headBatt;

    // variables for solar stuff
    int sunStart;
    int solarOn;
    int sunDuration;
    int repeatTime;
    int sunNodes;
    int expectedEndTime;
};

#endif




