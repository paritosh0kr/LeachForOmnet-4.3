/*
 * bs.cc
 *
 *  Created on: 05-Nov-2013
 *      Author: PARITOSH
 */
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "h/node.h"
#include "h/bs.h"
#include "h/solar.h"

#include "ClusterMessage_m.h"
#include "Status2BSMessage_m.h"
#include "ClusterHeadMessage_m.h"

#define EXPL_TIME 5

Define_Module(BS);

void BS::initialize()
{
    int xpos, ypos, i;
    cModule *parent = getParentModule();

    this->myId = par("id");
    this->nrGates = (int) parent->par("numNodes") + 2;
    this->xpos = par("xpos");
    this->ypos = par("ypos");
    this->nrNodes = (int) parent->par("numNodes");
    this->xMax = (int) parent->par("xMax");
    this->yMax = (int) parent->par("yMax");
    this->resetStatus();
    this->roundEnergyLoss = 80001.0;
    this->roundsDone = 0;
    this->nrRounds = (int) parent->par("rounds");
    this->firstDead = 0;
    this->calledEnd = 0;
    this->solarOn = (int) parent->par("solarOn");
    this->sunNodes = (int) parent->par("sunNodes");
    this->sunDuration = (int) parent->par("sunDuration");
    this->sunnyCtr = 0;
    this->halfDead = 0;
    this->halfDeadCtr = 0;
    this->deadNodes = 0;
    this->oldDeadNodes = 0;

    for (i = 0; i < 104; i++)
    {
        advInfo[i].id = 0;
        advInfo[i].energy = 0;
        advInfo[i].status = 0;
    }

    for (i = 0; i < this->nrRounds; i++)
    {
        this->roundTimes[i] = 0;
        this->sunnyNodes[i] = 0;
    }

    // schedule first sending
   this->setDisplayString("p=$xpos,$ypos;o=blue;i=device/antennatower");

    ev << "BS: id " << this->myId << " nrGates: " << this->nrGates << " x,y " << this->
        xpos << this->ypos << "\n";

    {
        cMessage *cmsg = new cMessage();
        cmsg->setKind(SMSG_INIT);
        scheduleAt(simTime(), cmsg);
    }
}

// making the gates on the fly
void BS::initNodes()
{
    int i;
    cModule *parent = getParentModule();
    cModule *mod;
    cModule *myMod;             // this is my Module
    int numNodes;
    int trRange;
    int delx, dely;
    int ritems;

    // new stuff
    numNodes = (int) parent->par("numNodes");
    ev << "BS numNodes is: " << numNodes << "\n";
    // new stuff
    trRange = (int) parent->par("trRange");
    ev << "BS trRange is: " << trRange << "\n";

    for (i = 1; i <= simulation.getLastModuleId(); i++)
    {
        int x, y, id;

        //scan the simulation module vector
        mod = (cModule *) simulation.getModule(i);

        if (strcmp(mod->getName(), "node") == 0)
        {
            id = ((Node *) mod)->myId;
            x = ((Node *) mod)->xpos;
            y = ((Node *) mod)->ypos;
            nodePtr[id] = ((Node *) mod);

            if (id != this->myId)
            {
                cGate *g;
                char gName1[32],gName2[32];
                int items;

                ev << "BS: " << this->myId << "(" << this->xpos << "," << this->
                    ypos << ") found node with id " << id << " xpos: " << x << " ypos: " << y <<
                    "\n";

                items = this->descvSize;
                ritems = mod->gateCount();

                ev << "items " << items << "\n";

                // make new gate here
                sprintf(gName1, "O_%d", id);
               /* g = new cGate(gName,cGate::OUTPUT,false);
                this->gatev.addAt(items, g); // position, element
                g->setOwnerModule((cModule *) this, items);*/
                //g=this->getOrCreateFirstUnconnectedGate(gName1,0,false,true);

                if(this->hasGate(gName1)){
                    this->gate(gName1)->disconnect();
                    this->deleteGate(gName1);
                }
                    this->addGate(gName1,cGate::OUTPUT,false);

                // make new gate at other side
                sprintf(gName2, "I_%d", this->myId);
                /*g = new cGate(gName, 'I');
                mod->gatev.addAt(ritems, g); // position, element
                g->setOwnerModule((cModule *) mod, ritems);*/
                //mod->getOrCreateFirstUnconnectedGate(gName2,0,false,true);
                if(mod->hasGate(gName2)){
                    mod->gate(gName2)->disconnect();
                    mod->deleteGate(gName2);
                }
                    mod->addGate(gName2,cGate::INPUT,false);
                //CHANNEL
                cIdealChannel *ch = NULL;
                /*if((this->gate(gName1)->isConnected())){
                    this->gate(gName1)->disconnect();
                }
                if(mod->gate(gName2)->isConnected()){
                    mod->gate(gName2)->disconnect();
                }*/
                    this->gate(gName1)->connectTo(mod->gate(gName2),ch);
                //mod->gate(gName2)->connectTo(this->gate(gName1),ch);
                //cLinkType *etere = findLink("etere");
                //connect((cModule *) this, items, (cLinkType *) etere, (cModule *) mod, ritems);
                //draw the link
                g = this->gate(gName1);
               g->setDisplayString(g->getDisplayString());

            }
        }
    }
}

void BS::handleMessage(cMessage * msg)
{


    if (msg->isSelfMessage())
    {
        ev << "BS: got self message type " << msg->getKind() << "\n";
        if (msg->getKind() == SMSG_INIT)
        {
            ev << "BS: got start message\n";
            this->initNodes();
        }
    }
    else
    {

        // no self message
       if (((ClusterMessage *) msg)->getProto() == CL_TOBS)
        {
            int energy;
            int cluster;
            int status;
            int sender;
            int clHead;
            int curHEnergy;     // energy of current head
            int curHStatus;     // status of current head
            int rating;
            int xpos, ypos;

            sender = ((Status2BSMessage *) msg)->getSrcAddress();
            energy = ((Status2BSMessage *) msg)->getEnergy();
            cluster = ((Status2BSMessage *) msg)->getCluster();
            status = ((Status2BSMessage *) msg)->getStatus();
            xpos = ((Status2BSMessage *) msg)->getXpos();
            ypos = ((Status2BSMessage *) msg)->getYpos();

            if (energy < 0 && this->firstDead == 0)
                this->firstDead = this->roundsDone;

            if (energy < 0 && this->halfDead == 0)
                this->halfDeadCtr++;

            if (this->roundsDone < 300)
                this->roundTimes[roundsDone] = SIMTIME_DBL(simTime());

            advInfo[sender].id = sender;
            advInfo[sender].energy = energy;
            advInfo[sender].status = status;
            advInfo[sender].xpos = xpos;
            advInfo[sender].ypos = ypos;

            if (advInfo[sender].energy < 0)
            {
                if (((Node *) nodePtr[sender])->myStatus != STATUS_DEAD)
                    this->deadNodes++;
                advInfo[sender].status = STATUS_DEAD;
                status = STATUS_DEAD; // XXX debug only
                ((Node *) nodePtr[sender])->myStatus = STATUS_DEAD;
            }

            if (status == STATUS_SUN)
                this->sunnyCtr++;

            // compute rating
            if (this->solarOn)
            {
                if (status == STATUS_SUN)
                    rating = energy - roundEnergyLoss / 2;
                else
                    rating = energy - roundEnergyLoss;
            }
            else
                rating = energy - roundEnergyLoss;

            advInfo[sender].rating = rating;

            ev << "BS received from " << sender << "status " << status << " rating: " << rating <<
                "\n";
            this->nrStatusRec++;
            ev << "BS rec " << this->nrStatusRec << " nrNodes: " << this->nrNodes << "\n";

            // check if done
            if (this->nrStatusRec == this->nrNodes - this->oldDeadNodes)
            {
                this->oldDeadNodes += this->deadNodes;
                ev << "nodes dead " << this->deadNodes << "all dead " << this->oldDeadNodes << "\n";
                this->deadRound[this->roundsDone] = this->deadNodes;

                this->sunnyNodes[this->roundsDone] = this->sunnyCtr;
                if (this->halfDeadCtr > this->nrNodes / 2 && this->halfDead == 0)
                {
                    this->halfDead = roundsDone;
                    ev << " HALF DEAD\n";
                    this->calledEnd = 2;
                    endSimulation();
                }
                this->roundsDone++;
                if (this->roundsDone <= this->nrRounds)
                {
                    ev << "BS call compute best\n";
                    // now compute best  nodes
                    computeBest();
                    resetStatus();
                }

                if (this->roundsDone > this->nrRounds)
                {
                    this->calledEnd = 1;
                    endSimulation();
                }
            }
        }
    }

    delete(msg);
}

void BS::resetStatus()
{
    int i;

    this->nrStatusRec = 0;      // number of received status
    this->sunnyCtr = 0;
    this->deadNodes = 0;
}

//
// Note: this method is far too long, bad programming style!!
//
#define FBEST 8                 // best after first round
#define LBEST 6                 // 6 best are in last round, 5 survive
void BS::computeBest()
{
    struct _adv best[FBEST];
    int i, j;
    int min = 999999999;
    int minPtr = 0;
    int sum = 0;
    int nrSolar = 0;            // nr of solar nodes

    ev << "first 8\n";
    // put FBEST nodes in best, compute min
    for (i = 0; i < FBEST; i++)
    {
        if (this->advInfo[i + 2].rating < min)
        {
            min = this->advInfo[i + 2].rating;
            minPtr = i;
        }
        best[i].id = this->advInfo[i + 2].id;
        best[i].xpos = this->advInfo[i + 2].xpos;
        best[i].ypos = this->advInfo[i + 2].ypos;
        best[i].status = this->advInfo[i + 2].status;
        best[i].rating = this->advInfo[i + 2].rating;
        ev << "Id: " << best[i].id << " rating: " << best[i].rating << "\n";
    }

    for (i = FBEST; i < this->nrNodes; i++)
    {
        //      ev << "i: " << i << "\n";
        // search for the ones larger tha min (smallest in best)
        if (this->advInfo[i + 2].rating > min)
        {
            // replace min
            min = this->advInfo[i + 2].rating;
            best[minPtr].id = this->advInfo[i + 2].id;
            best[minPtr].rating = this->advInfo[i + 2].rating;
            best[minPtr].xpos = this->advInfo[i + 2].xpos;
            best[minPtr].ypos = this->advInfo[i + 2].ypos;
            // recompute min and minPtr
            minPtr = 0;
            min = 9999999;
            for (j = 0; j < FBEST; j++)
            {
                if (best[j].rating < min)
                {
                    min = best[j].rating;
                    minPtr = j;
                }
            }
        }
    }

    // print out FBEST best, count solar nodes
    ev << "computeBest:\n";
    nrSolar = 0;
    for (i = 0; i < FBEST; i++)
    {
        ev << "Id: " << best[i].id << " rating: " << best[i].rating << "\n";
        nodePtr[best[i].id]->setDisplayString("p=$xpos,$ypos;o=green");
        if (best[i].status == STATUS_SUN)
            nrSolar++;
    }

    // now find one node with minimum distance to all other best nodes
    // usually one in the middle will be removed
    // do not through away solar nodes (if not all are solar nodes)
    minPtr = 0;
    min = 99999999;
    for (i = 0; i < FBEST; i++)
    {
        sum = 0;
        for (j = 0; j < FBEST; j++)
        {
            if (j != i)
                sum += ((best[i].xpos - best[j].xpos) * (best[i].xpos - best[j].xpos)) +
                    ((best[i].ypos - best[j].ypos) * (best[i].ypos - best[j].ypos));

        }
        //ev << "distance sum " << sum << " id " << best[i].id << " min " << min << "\n";
        if (sum < min && (nrSolar < 5 && best[i].status == STATUS_BATT))
        {
            minPtr = i;
            min = sum;
        }
    }
    ev << "remove node " << best[minPtr].id << " from cluster \n";
    nodePtr[best[minPtr].id]->setDisplayString("p=$xpos,$ypos;o=red");
    if (minPtr != FBEST - 1)
    {
        best[minPtr].id = best[FBEST - 1].id;
        best[minPtr].xpos = best[FBEST - 1].xpos;
        best[minPtr].ypos = best[FBEST - 1].ypos;
        best[minPtr].rating = best[FBEST - 1].rating;
    }
    // print out FBEST best
    ev << "computeBest now:\n";
    for (i = 0; i < FBEST - 1; i++)
    {
        ev << "Id: " << best[i].id << " rating: " << best[i].rating << "\n";
    }

    // search for node closest to another node, if one of them close to
    // the border, remove the one close to the border
    {
        int n1, n2, tmp;
        int close = 0;

        min = 9999999;
        for (i = 0; i < FBEST - 1; i++)
        {
            for (j = 0; j < FBEST - 1; j++)
            {
                if (j != i)
                {
                    tmp = ((best[i].xpos - best[j].xpos) * (best[i].xpos - best[j].xpos)) +
                        ((best[i].ypos - best[j].ypos) * (best[i].ypos - best[j].ypos));
                    if (tmp < min)
                    {
                        min = tmp;
                        n1 = i;
                        n2 = j;
                    }
                }
            }
        }
        ev << "n1: " << best[n1].id << " n2: " << best[n2].id << "\n";

#define BORDER 180
        // now choose one of the two
        if (best[n1].xpos<BORDER || best[n1].xpos>this->xMax - BORDER ||
            best[n1].ypos<BORDER || best[n1].ypos>this->yMax - BORDER)
            close = n1;
        else
            close = n2;

        // do not remove solar
        if (this->solarOn && best[n1].status == STATUS_SUN && best[n2].status == STATUS_BATT)
            close = n2;
        if (this->solarOn && best[n2].status == STATUS_SUN && best[n1].status == STATUS_BATT)
            close = n1;
        // update array, remove close
        ev << "remove close" << best[close].id << "\n";
        nodePtr[best[close].id]->setDisplayString("p=$xpos,$ypos;o=red");
        if (close != FBEST - 2)
        {
            best[close].id = best[FBEST - 2].id;
            best[close].xpos = best[FBEST - 2].xpos;
            best[close].ypos = best[FBEST - 2].ypos;
            best[close].rating = best[FBEST - 2].rating;
        }
        // print out FBEST best
        ev << "computeBest now:\n";
        for (i = 0; i < FBEST - 2; i++)
        {
            ev << "Id: " << best[i].id << " rating: " << best[i].rating << "\n";
        }
    }

    // now we do a real optimization
    {
        int sumWithout[LBEST];
        int n;
        int tmp;

        for (i = 0; i < LBEST; i++)
        {
            // reset sum
            sum = 0;
            // loop through all nodes to find minimun distance
            for (n = 2; n < this->nrNodes + 2; n++)
            {
                Node *nPtr = (Node *) nodePtr[n];

                if (nPtr->myStatus != STATUS_DEAD)
                {
                    min = 9999999;
                    for (j = 0; j < LBEST; j++)
                    {
                        if (i != j)
                        {
                            tmp = (nPtr->xpos - best[j].xpos) * (nPtr->xpos - best[j].xpos) +
                                (nPtr->ypos - best[j].ypos) * (nPtr->ypos - best[j].ypos);
                            if (tmp < min)
                            {
                                //        ev << "min " << j << "\n";
                                min = tmp;
                            }
                        }
                    }
                    sum += min;
                }
            }
            sumWithout[i] = sum;
            ev << "sumwithout " << best[i].id << ": " << sum << "\n";
        }
        // the one is lowest number gets kicked out
        min = 99999999;
        for (i = 0; i < LBEST; i++)
        {
            if (sumWithout[i] < min)
            {
                min = sumWithout[i];
                n = i;
            }
        }
        ev << "time " << simTime() << " OUT goes " << best[n].id << "\n";
        nodePtr[best[n].id]->setDisplayString("p=$xpos,$ypos;o=red");
        // remove that node
        if (n != LBEST - 1)
        {
            best[n].id = best[LBEST - 1].id;
            best[n].xpos = best[LBEST - 1].xpos;
            best[n].ypos = best[LBEST - 1].ypos;
            best[n].rating = best[LBEST - 1].rating;
        }
        // print out LBEST best
        ev << "computeBest now:\n";
        for (i = 0; i < LBEST - 1; i++)
        {
            ev << "Id: " << best[i].id << " rating: " << best[i].rating << " x,y " << best[i].
                xpos << "," << best[i].ypos << "\n";
        }
    }

    // now we send message to all nodes and announce their cluster head
    {
        int head = 0;
        int tmp;
        char str[32];

        ClusterHeadMessage *cmsg = new ClusterHeadMessage();
        ev << "send messages to nodes announcing cluster heads\n";
        cmsg->setProto(CL_TOHEAD); // XXX new name (to all now)
        cmsg->setSrcAddress(this->myId);
        for (int rec = 2; rec < this->nrNodes + 2; rec++)
        {
            Node *nPtr = (Node *) nodePtr[rec];
            head = 0;
            if (nPtr->myStatus != STATUS_DEAD)
            {
                //ev << "rec: " << rec;
                min = 9999999;
                for (j = 0; j < LBEST - 1; j++)
                {
                    if (rec != best[j].id)
                    {
                        tmp = (nPtr->xpos - best[j].xpos) * (nPtr->xpos - best[j].xpos) +
                            (nPtr->ypos - best[j].ypos) * (nPtr->ypos - best[j].ypos);
                        //ev << " cmp with " << best[j].id << "gives" << tmp << " ";
                        if (tmp < min)
                        {
                            //ev << "new min\n";
                            min = tmp;
                            head = best[j].id;
                        }
                    }
                    else
                    {
                        head = best[j].id;
                        break;
                    }
                }

            }
            ev << " BS: rec " << rec << " x,y " << nPtr->xpos << "," << nPtr->
                ypos << " has head: " << head << "\n";
            cmsg->setCHead(rec, head);
        }
        cmsg->setDestAddress(BROADCAST);
        for (int rec = 2; rec < this->nrNodes + 2; rec++)
        {
            ev << "BS sendHEAD for" << rec << ":" << cmsg->getCHead(rec) << "\n";
            if (cmsg->getCHead(rec) != 0) // no head when dead
            {
                sprintf(str, "O_%d", rec);
                if (findGate(str) > 1)
                {
                    cGate *g = gate(str);
                    if (g->isConnected())
                    {
                        //ev << this->myId << ": sToCHEAD to" << rec << "\n";
                        send((ClusterHeadMessage *) cmsg->dup(), str);

                    }
                }
            }
            else
                ev << "DEAD DEAD " << rec << "\n";
        }
    }
    // here we can reset everything
    this->resetStatus();
}

void BS::finish()
{
    int i;

    //recordScalar("BS BS node id",this->myId);
    recordScalar("solarOn", this->solarOn);
    recordScalar("sunDuration", this->sunDuration);
    recordScalar("roundsDone", this->roundsDone);
    recordScalar("nrRounds", this->nrRounds);
    recordScalar("firstDead", this->firstDead);
    recordScalar("halfDead", this->halfDead);
    recordScalar("sunNodes", this->sunNodes);

#if 0
    recordScalar("calledEnd", this->calledEnd);
    for (i = 0; i < this->roundsDone; i++)
    {
        recordScalar("roundsDone", this->roundTimes[i]);
        recordScalar("sunny nodes", this->sunnyNodes[i]);
    }
#endif

}


