/*
 * solar.h
 *
 *  Created on: 09-Nov-2013
 *      Author: PARITOSH
 */
#ifndef SOLAR_H
#define SOLAR_H

// define if we want to use NOSUN or not
//#define NOSUN 1
#undef NOSUN

#define NANO 0.001
#define PICO 0.000001

// NEW: CLUSTER_STUFF
#define NR_CLUSTERS      1      // XXX update
#define BS_ID            1      // ID of base station
#define CH_MIN_ENERGY    30     // XXX want to change this!!
#define CLUSTER_SIZE     100
#define FRAME_TIME       CLUSTER_SIZE+1 // how long is one frame (how many slots)

// messagetypes for clusters
#define CL_TOBS          1
#define CL_TOHEAD        2
#define CL_TDMA          3
#define CL_CHDATA        4

// self message types
#define SMSG_SENDDATA     11
#define SMSG_CHANGESTATUS 12
#define SMSG_DATA2BS      13    // cluster head sends data to BS
#define SMSG_STATUS2BS    14    // nodes send their new status to BS
#define SMSG_SINKSTART    15
#define SMSG_SEQUPDATE    16    // nodes update seq number for expl messages
#define SMSG_INIT         17    // init updates
#define SMSG_MAKETDMA     18

#define BROADCAST     0

#define STATUS_SUN  1            // status: running with solar energy
#define STATUS_BATT     2       // status: running on battery
#define STATUS_DEAD     3       // this node is dead

struct _node
{
    int id;
    int status;
    int outgate;
    int hops;
    int bcount;
    int scount;
    int seqNumber;              // per node
};

struct _adv
{
    int id;
    int energy;
    int status;
    int rating;
    int xpos;
    int ypos;
};

struct _peerInfo
{
    int id;
    int xpos;
    int ypos;
};

// status for myGrad
#define GS_INIT     0
#define GS_ACTIVE   1

// define some events and times
#define INIT_WAIT               1 // wait to init nodes
#define SINK_WAIT               2 // sink waits until start
#define EVENT_SENSORDATA    1
#define EVENT_BC            2
#define BC_TIME             1
#define EVENT_CHANGESTATUS  3
#define EVENT_PRINTSTATS    4
//#define END_TIME   1250
#define END_TIME            900
//#define END_TIME   1100
//#define END_TIME   1750
#define CHANGE2_1                       200
#define CHANGE2_2                       400
#define CHANGE3_1                       100
#define CHANGE3_2                       450

#define EXPL_PERIOD                     300
#define DATA_PERIOD                     40

#define MAX_NEIGHBOURS                  5 /* for hop counter */
#define MAX_DOWNS                       2 /* how many downs */

#endif



