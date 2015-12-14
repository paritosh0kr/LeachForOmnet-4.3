/*
 * nodebase.cc
 *
 *  Created on: 09-Nov-2013
 *      Author: PARITOSH
 */
#include <stdio.h>
#include <string.h>

#include <omnetpp.h>
#include "nodebase.h"

void NodeBase::updateStats()
{
    if (this->myStatus == STATUS_SUN)
        this->nrAllMsgSun++;
    else
        this->nrAllMsgBatt++;
}

void NodeBase::initStats()
{
    this->nrAllMsgBatt = 0;
    this->nrAllMsgSun = 0;
    this->nrDataBatt = 0;
    this->nrDataSun = 0;
}

void NodeBase::finish()
{
#if 0
    ev << "finished node id: ";
    ev << this->myId;
    ev << " nrAllMsgBatt: ";
    ev << this->nrAllMsgBatt;
    ev << " nrAllMsgSun ";
    ev << this->nrAllMsgSun;
    ev << "    nrDataBatt ";
    ev << this->nrDataBatt;
    ev << " nrDataSun ";
    ev << this->nrDataSun;
    ev << "\n";
#endif

#if 0
    recordScalar(" nrAllMsgBatt", this->nrAllMsgBatt);
    recordScalar("nrAllMsgSun", this->nrAllMsgSun);
    recordScalar("nrDataBatt ", this->nrDataBatt);
    recordScalar("nrDataSun ", this->nrDataSun);
    recordScalar("nrExplBatt", this->nrExplBatt);
#endif
}



