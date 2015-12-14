/*
 * node.cc
 *
 *  Created on: 05-Nov-2013
 *      Author: PARITOSH
 */
#include <stdio.h>
#include <string.h>

#include <omnetpp.h>
#include "h/node.h"
#include "h/bs.h"
#include "cgate.h"

#include "ClusterMessage_m.h"
#include "Status2BSMessage_m.h"
#include "ClusterHeadMessage_m.h"
#include "TDMAMessage_m.h"
#include "DataToCHMessage_m.h"
#include "Data2BSMessage_m.h"

Define_Module(Node);

void Node::initialize()
{
    int i;
    cMessage *cm;
    cMessage *cm2;
    cModule *parent = getParentModule();

    this->initStats();
    this->myId = par("id");
    this->xpos = par("xpos");
    this->ypos = par("ypos");
    this->nrGates = (int) parent->par("numNodes") + 3;
    this->energy = (double) par("energy");
    this->myCluster = 0;
    this->nrNodes = (int) parent->par("numNodes");
    this->nrFrames = (int) parent->par("frames");
    this->nrRounds = (int) parent->par("rounds");
    this->solarOn = (int) parent->par("solarOn");
    this->sunDuration = (int) parent->par("sunDuration");
    this->sunStart = par("sunstart");
    this->sunNodes = (int) parent->par("sunNodes");

    this->myData = 0;
    this->curFrame = 0;
    this->sentBS = 0;
    this->wasHead = 0;
    this->headSun = 0;
    this->headBatt = 0;

    // default, set black
    this->myStatus = STATUS_BATT;
    this->setDisplayString("p=$xpos,$ypos;o=black;i=device/device");

    // schedule SUN
    if (this->solarOn)
    {
        cm = new cMessage();
        cm2 = new cMessage();

        cm->setKind(SMSG_CHANGESTATUS);
        cm2->setKind(SMSG_CHANGESTATUS);

        int max = this->nrRounds * (this->nrFrames * 30);
        int endSun = this->sunStart + this->sunDuration;

        this->repeatTime = (this->nrNodes / this->sunNodes) * this->sunDuration;
        this->expectedEndTime = (30 * this->nrFrames) * nrRounds;
        ev << "repeatTime " << this->repeatTime << " expected end " << this->
            expectedEndTime << "\n";

        if (endSun > max)
            endSun = max - 100;

        scheduleAt(simTime() + this->sunStart, cm); // XXXXXXXX
        scheduleAt(simTime() + endSun, cm2); // XXXXXXXX
    }

    ev << this->myId << " energy: " << energy << "status " << this->myStatus << "\n";

    {
        cMessage *cmsg = new cMessage();
        cmsg->setKind(SMSG_INIT);
        scheduleAt(simTime() + INIT_WAIT, cmsg);
    }

}

// making the gates on the fly
void Node::initNodes()
{
    int i;
    cModule *parent = getParentModule();
    cModule *mod;
    cModule *myMod;             // this is my Module
    int numNodes;
    int trRange;
    int delx, dely;
    int ritems;

    numNodes = (int) parent->par("numNodes");
    ev << "numNodes is: " << numNodes << " energy: " << energy << "\n";

    for (i = 1; i <= simulation.getLastModuleId(); i++)
    {
        int x, y, id;

        //scan the simulation module vector
        mod = (cModule *) simulation.getModule(i);

        // check for nodes in transmission range
        if ((strcmp(mod->getName(), "node") == 0) || (strcmp(mod->getName(), "bs") == 0))
        {
            if (strcmp(mod->getName(), "node") == 0)
            {
                id = ((Node *) mod)->myId;
                x = ((Node *) mod)->xpos;
                y = ((Node *) mod)->ypos;
                nodePtr[id] = ((Node *) mod);
            }
            if (strcmp(mod->getName(), "bs") == 0)
            {
                id = ((BS *) mod)->myId;
                this->bsId = id;
                x = ((BS *) mod)->xpos;
                y = ((BS *) mod)->ypos;
                this->bsDist =
                    (x / 10 - this->xpos / 10) * (x / 10 - this->xpos / 10) + (y / 10 -
                                                                               this->ypos / 10) *
                    (y / 10 - this->ypos / 10);
            }
            if (id != this->myId && id == this->bsId)
            {
                cGate *g;
                char gName1[32],gName2[32];
                int items;

                // ev << this->myId << "(" << this->xpos << "," << this->ypos <<") found node with id " << id << " xpos: " <<  x << " ypos: " << y<< "\n";

                if ((((this->ypos - ypos) * (this->ypos - ypos)) +
                     ((this->xpos - xpos) * (this->xpos - xpos))) < 2500 || id == this->bsId)
                {

                    items = this->descvSize;
                    ritems = mod->gateCount();

                    // make new gate here
                    sprintf(gName1, "O_%d", id);
                   // g = new cGate(gName, 'O');
                    //this->gatev.addAt(items, g); // position, element
                   // g->setOwnerModule((cModule *) this, items);
                    //g=this->getOrCreateFirstUnconnectedGate(gName1,0,false,true);
                    if(!this->hasGate(gName1))
                        this->addGate(gName1,cGate::OUTPUT,false);
                    // make new gate at other side
                    sprintf(gName2, "I_%d", this->myId);
                    //g = new cGate(gName, 'I');
                    //mod->gatev.addAt(ritems, g); // position, element
                    //g->setOwnerModule((cModule *) mod, ritems);
                   // mod->getOrCreateFirstUnconnectedGate(gName2,0,false,true);
                    if(!mod->hasGate(gName2))
                        mod->addGate(gName2,cGate::INPUT,false);
                    //CHANNEL
                    cIdealChannel *ch = NULL;
                    if((this->gate(gName1)->isConnected())){
                        this->gate(gName1)->disconnect();
                    }
                    if(mod->gate(gName2)->isConnected()){
                                       mod->gate(gName2)->disconnect();
                                   }
                          this->gate(gName1)->connectTo(mod->gate(gName2),ch);
                   // cLinkType *etere = findLink("etere");
                    //connect((cModule *) this, items, (cLinkType *) etere, (cModule *) mod, ritems);
                    //draw the link
                    g = this->gate(gName1);
                    g->setDisplayString( g->getDisplayString());
                }
            }
        }
    }
    // send energy and solar status to BS
    ev << "call send2BS\n";
    send2BS(this->myId, this->bsId, this->energy, this->myStatus, this->myCluster, this->xpos,
            this->ypos);
}

void Node::handleMessage(cMessage * msg)
{
    if (!msg->isSelfMessage())
    {
        //
        // BS announces head with this message
        // broadcasted to all nodes by BS
        //
        if (((ClusterMessage *) msg)->getProto() == CL_TOHEAD)
        {
            int head;           // cluster head of the cluster

            // reduce energy for packet reception of header
            energyReceive(25 * 8);

            head = ((ClusterHeadMessage *) msg)->getCHead(this->myId);
            ev << this->myId << " my head is " << head << "\n";
            if (head != this->myId)
            {
                // setup connection to host
                cGate *g;
                char gName1[32],gName2[32];
                int items;
                int xpos, ypos;
                cModule *mod;
                int ritems;
                ;
                this->cHead = 0;
                this->headId = head;
                if (myStatus == STATUS_SUN)
                    this->setDisplayString("p=$xpos,$ypos;o=yellow;i=device/device");
                else
                    this->setDisplayString("p=$xpos,$ypos;o=black;i=device/device");

                xpos = nodePtr[head]->xpos;
                ypos = nodePtr[head]->ypos;
                mod = (Node *) nodePtr[head];

                items = this->descvSize;
                ritems = mod->gateCount();

                // make new gate here
                sprintf(gName1, "O_%d", head);
                /*g = new cGate(gName, 'O');
                this->gatev.addAt(items, g); // position, element
                g->setOwnerModule((cModule *) this, items);*/
                //g=this->getOrCreateFirstUnconnectedGate(gName1,0,false,true);
                if(!this->hasGate(gName1))
                    this->addGate(gName1,cGate::OUTPUT,false);

                // make new gate at other side
                sprintf(gName2, "I_%d", this->myId);
               /* g = new cGate(gName, 'I');
                mod->gatev.addAt(ritems, g); // position, element
                g->setOwnerModule((cModule *) mod, ritems);*/
                //mod->getOrCreateFirstUnconnectedGate(gName2,0,false,true);
                if(!mod->hasGate(gName2))
                    mod->addGate(gName2,cGate::INPUT,false);
                //CHANNEL
                cIdealChannel *ch = NULL;
                if((this->gate(gName1)->isConnected())){
                    this->gate(gName1)->disconnect();
                }
                if(mod->gate(gName2)->isConnected()){
                                   mod->gate(gName2)->disconnect();
                               }
                    this->gate(gName1)->connectTo(mod->gate(gName2),ch);
                //cLinkType *etere = findLink("etere");
                //connect((cModule *) this, items, (cLinkType *) etere, (cModule *) mod, ritems);
                //draw the link
                g = this->gate(gName1);
                g->setDisplayString( g->getDisplayString());

            }
            else
            {
                // now this node is cluster head
                this->cHead = 1;
                this->headId = head;
                this->wasHead++;
                if (this->myStatus == STATUS_BATT)
                    this->headBatt++;
                else
                    this->headSun++;
                this->setDisplayString("p=$xpos,$ypos;o=red;i=device/device");

                // want to create TDMA in next step
                {
                    cMessage *cmsg = new cMessage();
                    cmsg->setKind(SMSG_MAKETDMA);
                    scheduleAt(simTime() + INIT_WAIT, cmsg);
                }

                // must stay awake and receive data packets from other nodes
                // reset number of packets received in this frame
                this->nrDataPackets = 0;
                // must collect data and send it to BS

            }
        }
        //
        // cluster head announces its TDMA scheme with this message
        // received by nodes in cluster
        //
        if (((ClusterMessage *) msg)->getProto() == CL_TDMA)
        {
            int i, s;
            int sTime;

            // reset data and counters
            this->myData = 0;   // reset myData
            this->curFrame = 0;

            // reduce energy for packet reception of header
            energyReceive(25 * 8);

            this->nrFrames = ((TDMAMessage *) msg)->getFrames();
            this->frameTime = ((TDMAMessage *) msg)->getFrameTime();
            this->headId = ((TDMAMessage *) msg)->getSrcAddress();
            ev << this->myId << ": received TDMA  frameTime " << this->frameTime << "\n";

            // find slot for this node
            for (i = 0; this->frameTime; i++)
            {
                if (((TDMAMessage *) msg)->getTdma(i) == this->myId &&
                    ((TDMAMessage *) msg)->getTdma(i) != 0)
                {
                    ev << this->myId << ": found slot time " << i + 1 << "\n";
                    sTime = i + 1;
                    this->mySlot = i + 1;
                    break;
                }
            }
            ev << "loop done\n";
            // sleep until slot time, then wake up and send data
            {
                cMessage *cmsg = new cMessage();
                cmsg->setKind(SMSG_SENDDATA);
                scheduleAt(simTime() + sTime, cmsg);
            }
            ev << "tdma " << this->myId << "done\n";
        }
        //
        // cluster head receives data
        //
        if (((ClusterMessage *) msg)->getProto() == CL_CHDATA)
        {
            int newHead = 0;    // XXX update in case someone

            // reduce energy for packet reception of data
            energyReceive(500 * 8);

            // cluster head received data
            this->nrDataPackets++;
            // check if all packets
            if (this->nrDataPackets == this->clusterNodes) // XXX
            {
                this->nrDataPackets = 0;
                // if new cluster head (due to SUN reason)
                if (newHead)
                {
                    // inform this node that it is the new head

                    // one "seconds" until processed data is sent to BS
                }
                else
                {
                    // two "seconds" until processed data is sent to BS
                    cMessage *cmsg = new cMessage();
                    cmsg->setKind(SMSG_DATA2BS);
                    scheduleAt(simTime() + 2, cmsg);
                }
            }
        }
    }
    else
    {                           // self message
        if (msg->getKind() == SMSG_CHANGESTATUS) //we update the status
        {
            int receiver;

            if (this->myStatus != STATUS_DEAD)
            {

                if (myStatus == STATUS_SUN)
                {
                    cMessage *cm;
                    cMessage *cm2;

                    myStatus = STATUS_BATT;
                    this->setDisplayString("p=$xpos,$ypos;o=black;i=device/device");

                    if (simTime() + this->repeatTime < this->expectedEndTime)
                    {
                        cm = new cMessage();
                        cm2 = new cMessage();
                        cm->setKind(SMSG_CHANGESTATUS);
                        cm2->setKind(SMSG_CHANGESTATUS);

                        scheduleAt(simTime() + this->repeatTime - this->sunDuration, cm);
                        scheduleAt(simTime() + this->repeatTime, cm2);
                    }

                }
                else
                {
                    myStatus = STATUS_SUN;
                    this->setDisplayString("p=$xpos,$ypos;o=yellow;i=device/device");
                }
            }
            ev << "new status " << this->myStatus << "\n";
        }
        else if (msg->getKind() == SMSG_INIT)
        {
            this->initNodes();
        }
        else if (msg->getKind() == SMSG_SENDDATA)
        {
            int newSun = 0;     // set to 1 if you want to take over as clusterhead

            // node has been woken up to transmit data to clusterhead
            //ev << this->myId << "to send data to clusterhead\n";
            sendDataToCHead(newSun);
            this->curFrame++;
            if (this->curFrame < this->nrFrames)
            {
                // sleep until slot time, then wake up and send data
                cMessage *cmsg = new cMessage();
                cmsg->setKind(SMSG_SENDDATA);
                scheduleAt(simTime() + this->frameTime, cmsg);
            }
            else
            {
                // XXX must wake up to send new status to BS, so new cluster head can be chosen
                cMessage *cmsg = new cMessage();
                cmsg->setKind(SMSG_STATUS2BS);
                scheduleAt(simTime() + (this->frameTime - this->mySlot), cmsg);
            }
        }
        else if (msg->getKind() == SMSG_DATA2BS)
        {
            // cluster head sends data to BS
            sendData2BS(this->myId);
        }
        else if (msg->getKind() == SMSG_MAKETDMA)
        {
            // reset some values
            this->curFrame = 0;

            // cluster head sends data to BS
            this->sendTDMA();
        }
        else if (msg->getKind() == SMSG_STATUS2BS)
        {
            if (this->myId == 25)
                ev << this->myId << ": send STATUS to BS with EL " << this->
                    energy << " head:" << this->cHead << "\n";
            this->cHead = 0;
            send2BS(this->myId, this->bsId, this->energy, this->myStatus, this->myCluster,
                    this->xpos, this->ypos);
            this->sentBS++;
        }
        else
        {
            ev << "got strange self-message!!\n";
        }
    }
    delete(msg);
}

void Node::send2BS(int src, int rec, int energy, int status, int cluster, int xpos, int ypos)
{

    // send out a TOCLUSTER message
    Status2BSMessage *cmsg = new Status2BSMessage(); // create new status2BS message
    cmsg->setProto(CL_TOBS);
    cmsg->setSrcAddress(this->myId); // XXX node id
    cmsg->setDestAddress(rec);
    cmsg->setStatus(status);
    cmsg->setEnergy(energy);
    cmsg->setCluster(cluster);
    cmsg->setYpos(ypos);
    cmsg->setXpos(xpos);

    ev << "in send2BS:" << this->myId << "\n";
    {
        char str[32];

        sprintf(str, "O_%d", rec);
        if (findGate(str) > 1)
        {
            cGate *g = gate(str);
            if (g->isConnected())
            {
                ev << this->myId << ": sToCluster to" << rec << "\n";
                send((Status2BSMessage *) cmsg, str);
                // reduce energy for header
                this->energyTransmit(25 * 8, this->bsDist);
            }
        }
    }
}

void Node::sendTDMA()
{
    int n;
    int nrPeers = 0;            // number of nodes in my cluster
    char str[32];
    int i, j;
    TDMAMessage *tmsg;
    int items, ritems;
    cGate *g;
    char gName1[32],gName2[32];

    // create new Message including TDMA slots
    tmsg = new TDMAMessage();
    tmsg->setProto(CL_TDMA);
    tmsg->setSrcAddress(this->myId);
    tmsg->setDestAddress(BROADCAST);

    // compute number of nodes in cluster and update cluster head
    for (n = 2; n < this->nrNodes + 2; n++)
    {
        if (n != this->myId && nodePtr[n]->headId == this->myId)
        {
            // set TDMA slot
            tmsg->setTdma(nrPeers, n);
            ev << "tdma " << nrPeers << ": " << n << "\n";
            // make a connection to this node

            items = this->descvSize;
            ritems = nodePtr[n]->descvSize;

            // make new gate here
            sprintf(gName1, "O_%d", nodePtr[n]->myId);
            /*g = new cGate(gName, 'O');
            this->gatev.addAt(items, g); // position, element
            g->setOwnerModule((cModule *) this, items);*/
            //g=this->getOrCreateFirstUnconnectedGate(gName1,0,false,true);
            if(!this->hasGate(gName1))
                this->addGate(gName1,cGate::OUTPUT,false);
            // make new gate at other side
            sprintf(gName2, "I_%d", this->myId);
            /*g = new cGate(gName, 'I');
            nodePtr[n]->gatev.addAt(ritems, g); // position, element
            g->setOwnerModule(nodePtr[n], ritems);*/
            //nodePtr[n]->getOrCreateFirstUnconnectedGate(gName2,0,false,true);
            if(!nodePtr[n]->hasGate(gName2))
                nodePtr[n]->addGate(gName2,cGate::INPUT,false);
            //CHANNEL
            cIdealChannel *ch = NULL;
            if((this->gate(gName1)->isConnected())){
                this->gate(gName1)->disconnect();
            }
            if(nodePtr[n]->gate(gName2)->isConnected()){
                               nodePtr[n]->gate(gName2)->disconnect();
             }

            this->gate(gName1)->connectTo(nodePtr[n]->gate(gName2),ch);
            //cLinkType *etere = findLink("etere");
            //connect((cModule *) this, items, (cLinkType *) etere, nodePtr[n], ritems);
            //draw the link
            g = this->gate(gName1);
            g->setDisplayString(g->getDisplayString());

            // compute distance as well
            nodePtr[n]->headDist =
                (((nodePtr[n])->xpos / 10 - this->xpos / 10) * ((nodePtr[n])->xpos / 10 -
                                                                this->xpos / 10)) +
                (((nodePtr[n])->ypos / 10 - this->ypos / 10) * ((nodePtr[n])->ypos / 10 -
                                                                this->ypos / 10));
            ev << "dist: " << nodePtr[n]->headDist << "\n";
            nrPeers++;
        }
    }
    ev << "clusterhead " << this->myId << ": have peers " << nrPeers << "\n";

    tmsg->setFrames(this->nrFrames); // XXX nr Frames ???
    tmsg->setFrameTime(nrPeers + 2); // XXX frame length?

    this->clusterNodes = nrPeers;
    // give two slots to cluster head at the end of each round
    tmsg->setTdma(nrPeers, this->myId);
    tmsg->setTdma(nrPeers + 1, this->myId);

    for (i = 0; i < nrPeers; i++)
    {
        int rec = tmsg->getTdma(i);
        sprintf(str, "O_%d", rec);
        if (findGate(str) > 1)
        {
            cGate *g = gate(str);
            if (g->isConnected())
            {
                ev << this->myId << ": sTDMA to" << rec << "\n";
                send((TDMAMessage *) tmsg->dup(), str);
                // reduce energy for header
                this->energyTransmit(25 * 8, nodePtr[rec]->headDist);
            }
        }
        else
            ev << "no gate\n";
    }

    // if we have 0 peers we do not do anything, so we can send our new status
    // to BS
    if (nrPeers == 0)
    {
        ev << "call send2BS\n";
        send2BS(this->myId, this->bsId, this->energy, this->myStatus, this->myCluster, this->xpos,
                this->ypos);
    }
}

void Node::sendDataToCHead(int newSun)
{
    int rec = this->headId;     // this data is sent to the cluster head

    //ev << this->myId << " send data to " << rec << "\n";
    // send out a TOCLUSTER message
    DataToCHMessage *dmsg = new DataToCHMessage();
    dmsg->setProto(CL_CHDATA);
    dmsg->setSrcAddress(this->myId); // XXX node id
    dmsg->setDestAddress(rec);
    dmsg->setData(this->myData);
    this->myData++;
    dmsg->setNewSun(newSun);

    {
        char str[32];

        sprintf(str, "O_%d", rec);
        if (findGate(str) > 1)
        {
            cGate *g = gate(str);
            if (g->isConnected())
            {
                //ev << this->myId << ": sDataCH to" << rec << "\n";
                send((DataToCHMessage *) dmsg, str);
                // reduce energy for data packet
                this->energyTransmit(500 * 8, this->headDist);
            }
        }
    }
}

void Node::sendData2BS(int data)
{
    int rec = this->bsId;       // this data is sent to the cluster head

    ev << this->myId << "send data to BBBBBSSSS\n\n\n";
    // send out a TOCLUSTER message
    Data2BSMessage *dmsg = new Data2BSMessage(); // create new toCenter message
    dmsg->setProto(CL_CHDATA);
    dmsg->setSrcAddress(this->myId); // XXX node id
    dmsg->setDestAddress(rec);
    dmsg->setData(this->myData);
    this->myData++;

    {
        char str[32];

        sprintf(str, "O_%d", rec);
        if (findGate(str) > 1)
        {
            cGate *g = gate(str);
            if (g->isConnected())
            {
                //ev << this->myId << ": sDataCH to" << rec << "\n";
                send((Data2BSMessage *) dmsg, str);
                // reduce energy for data packet to BS
                this->energyTransmit(500 * 8, this->bsDist);
            }
        }
    }

    // reduce energy for data aggregation
    energyDataAggr(this->clusterNodes);

    // now done with this round
    this->curFrame++;
    if (this->curFrame == this->nrFrames)
    {
        ev << "cHead: round done\n";
        // reset from being a cluster head
        //this->cHead = 0;
        {
            // XXX must wake up to send new status to BS, so new cluster head can be chosen
            cMessage *cmsg = new cMessage();
            cmsg->setKind(SMSG_STATUS2BS);
            scheduleAt(simTime(), cmsg); // XXX constant
        }
        this->curFrame = 0;
    }
}

// energy consumption for reception of bits
void Node::energyReceive(int bits)
{
    double en;                  // lost energy

    if (this->myStatus == STATUS_BATT)
    {
        en = (double) bits *50.0 * NANO;
        ev << "REC-energy: " << en << "\n";
        this->energy = this->energy - en;
    }
}

// energy consumption for transmission of bits over distance dist
// node that dist is already the square
void Node::energyTransmit(int bits, int dist)
{
    double en;

    if (this->myStatus == STATUS_BATT)
    {
        en = bits * 10 * PICO * dist + (double) bits *50.0 * NANO;
        if (this->cHead == 1)
            ev << "TR-energy HEAD: " << en << "\n";
        this->energy = this->energy - en;
    }
}

// energy consumption for data aggregation (cluster head only)
void Node::energyDataAggr(int signals)
{
    double en;

    if (this->myStatus == STATUS_BATT)
    {
        en = 5 * NANO * signals;
        ev << "AGG-energy: " << en << "\n";
        this->energy = this->energy - en;
    }
}

void Node::finish()
{
#if 0
    recordScalar("node id", this->myId);
    recordScalar("energy", this->energy);
    recordScalar("xpos  ", this->xpos);
    recordScalar("ypos  ", this->ypos);
    recordScalar("wasHead", this->wasHead);
    recordScalar("sunstart", this->sunStart);
    recordScalar("status", this->myStatus);

    recordScalar("wasHead", this->wasHead);
    recordScalar("headSun", this->headSun);
    recordScalar("headBatt", this->headBatt);
#endif
}



