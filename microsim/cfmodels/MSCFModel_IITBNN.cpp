
// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <microsim/MSVehicle.h>
#include <microsim/MSLane.h>
#include "MSCFModel_IITBNN.h"
#include <microsim/MSAbstractLaneChangeModel.h>
#include <utils/common/RandHelper.h>


#include<iostream>
extern MSCFModel_IITBNN::UT Units[14]; 

float Weights[] =  {
	-0.143580, 0.201710, 
	-0.435920, 1.811630, 
	-0.018860, -0.903730, 
	0.490110, -2.272230, 
	-2.654690, 0.155780, 
	0.167580, 0.458600, 
	-0.489070, 0.140120, 
	1.922750, 0.186400, 
	6.487300, -1.187110, 
	1.286700, -2.376440, 
	-0.167980, 1.874670, -0.755620, -2.110800, -1.562800, 0.388300, 0.228530, 1.012770, 4.334710, -2.079650 
    };

MSCFModel_IITBNN::UT* Sources[] =  {
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 1, Units + 2, 
        Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12 
    };

MSCFModel_IITBNN::UT Units[] = 
{
	{ 0.0, 0.0, 0, 0, 0},
	{ /* unit 1 (Old: 1) */
		0.0, 1.000000, 0,
		&Sources[0] , 
		&Weights[0] , 
	},
	{ /* unit 2 (Old: 2) */
		0.0, 0.998030, 0,
		&Sources[0] , 
		&Weights[0] , 
	},
	{ /* unit 3 (Old: 3) */
		0.0, 0.554370, 2,
		&Sources[0] , 
		&Weights[0] , 
	},
	{ /* unit 4 (Old: 4) */
		0.0, -1.292860, 2,
		&Sources[2] , 
		&Weights[2] , 
	},
	{ /* unit 5 (Old: 5) */
		0.0, -0.241650, 2,
		&Sources[4] , 
		&Weights[4] , 
	},
	{ /* unit 6 (Old: 6) */
		0.0, 0.668520, 2,
		&Sources[6] , 
		&Weights[6] , 
	},
	{ /* unit 7 (Old: 7) */
		0.0, -0.427730, 2,
		&Sources[8] , 
		&Weights[8] , 
	},
	{ /* unit 8 (Old: 8) */
		0.0, 0.152550, 2,
		&Sources[10] , 
		&Weights[10] , 
	},
	{ /* unit 9 (Old: 9) */
		0.0, -1.159520, 2,
		&Sources[12] , 
		&Weights[12] , 
	},
	{ /* unit 10 (Old: 10) */
		0.0, -0.509900, 2,
		&Sources[14] , 
		&Weights[14] , 
	},
	{ /* unit 11 (Old: 11) */
		0.0, -1.450040, 2,
		&Sources[16] , 
		&Weights[16] , 
	},
	{ /* unit 12 (Old: 12) */
		0.0, 0.018010, 2,
		&Sources[18] , 
		&Weights[18] , 
	},
	{ /* unit 13 (Old: 13) */
		0.0, -1.762410, 10,
		&Sources[20] , 
		&Weights[20] , 
	}
};


// ===========================================================================
// method definitions
// ===========================================================================
MSCFModel_IITBNN::MSCFModel_IITBNN(const MSVehicleType* vtype,  SUMOReal accel, SUMOReal decel,
                                   SUMOReal dawdle, SUMOReal tau) throw()
        : MSCFModel(vtype, decel), myAccel(accel), myDawdle(dawdle), myTau(tau) {

    myTauDecel = decel * myTau;
    std::cout<<"IITBNN LOADED"<<std::endl;
}


MSCFModel_IITBNN::~MSCFModel_IITBNN() throw() {}


SUMOReal
MSCFModel_IITBNN::moveHelper(MSVehicle * const veh, const MSLane * const lane, SUMOReal vPos) const throw() {
    SUMOReal oldV = veh->getSpeed(); // save old v for optional acceleration computation
    SUMOReal vSafe = MIN2(vPos, veh->processNextStop(vPos)); // process stops
    // we need the acceleration for emission computation;
    //  in this case, we neglect dawdling, nonetheless, using
    //  vSafe does not incorporate speed reduction due to interaction
    //  on lane changing
    veh->setPreDawdleAcceleration(SPEED2ACCEL(vSafe-oldV));
    //
    SUMOReal vNext = dawdle(MIN3(lane->getMaxSpeed(), maxNextSpeed(oldV), vSafe));
    vNext =
        veh->getLaneChangeModel().patchSpeed(
            MAX2((SUMOReal) 0, oldV-(SUMOReal)ACCEL2SPEED(myDecel)), //!!! reverify
            vNext,
            MIN3(vSafe, veh->getLane().getMaxSpeed(), maxNextSpeed(oldV)),//vaccel(myState.mySpeed, myLane->maxSpeed())),
            vSafe);
    return MIN4(vNext, vSafe, veh->getLane().getMaxSpeed(), maxNextSpeed(oldV));
}


SUMOReal
MSCFModel_IITBNN::ffeV(const MSVehicle * const veh, SUMOReal speed, SUMOReal gap, SUMOReal predSpeed) const throw() {
    return MIN2(_vsafe(gap, predSpeed), maxNextSpeed(speed));
}


SUMOReal
MSCFModel_IITBNN::ffeV(const MSVehicle * const veh, SUMOReal gap, SUMOReal predSpeed) const throw() {
    return MIN2(_vsafe(gap, predSpeed), maxNextSpeed(veh->getSpeed()));
}


SUMOReal
MSCFModel_IITBNN::ffeV(const MSVehicle * const veh, const MSVehicle *pred) const throw() {
    return MIN2(_vsafe(veh->gap2pred(*pred), pred->getSpeed()), maxNextSpeed(veh->getSpeed()));
}


SUMOReal
MSCFModel_IITBNN::ffeS(const MSVehicle * const veh, SUMOReal gap) const throw() {
    return MIN2(_vsafe(gap, 0), maxNextSpeed(veh->getSpeed()));
}


SUMOReal
MSCFModel_IITBNN::interactionGap(const MSVehicle * const veh, SUMOReal vL) const throw() {
    // Resolve the vsafe equation to gap. Assume predecessor has
    // speed != 0 and that vsafe will be the current speed plus acceleration,
    // i.e that with this gap there will be no interaction.
    SUMOReal vNext = MIN2(maxNextSpeed(veh->getSpeed()), veh->getLane().getMaxSpeed());
    SUMOReal gap = (vNext - vL) *
                   ((veh->getSpeed() + vL) * myInverseTwoDecel + myTau) +
                   vL * myTau;
int xxxx = 1;
    // Don't allow timeHeadWay < deltaT situations.
    //return MAX2(gap, SPEED2DIST(vNext));
    return 10000.0;
}


bool
MSCFModel_IITBNN::hasSafeGap(SUMOReal speed, SUMOReal gap, SUMOReal predSpeed, SUMOReal laneMaxSpeed) const throw() {
    if (gap<0) {
        return false;
    }
    SUMOReal vSafe = MIN2(_vsafe(gap, predSpeed), maxNextSpeed(speed));
    SUMOReal vNext = MIN3(maxNextSpeed(speed), laneMaxSpeed, vSafe);
    return (vNext>=getSpeedAfterMaxDecel(speed) && gap>= SPEED2DIST(speed));
}


//TODO: Refactor and remove
SUMOReal
MSCFModel_IITBNN::dawdle(SUMOReal speed) const throw() {
    // generate random number out of [0,1]
    SUMOReal random = RandHelper::rand();
    // Dawdle.
    /*
    if (speed < myAccel) {
        // we should not prevent vehicles from driving just due to dawdling
        //  if someone is starting, he should definitely start
        // (but what about slow-to-start?)!!!
        speed -= ACCEL2SPEED(myDawdle * speed * random);
    } else {
        speed -= ACCEL2SPEED(myDawdle * getMaxAccel(speed) * random);
    }
    */
    return MAX2(SUMOReal(0), speed);
}


/** Returns the SK-vsafe. */
SUMOReal MSCFModel_IITBNN::_vsafe(SUMOReal gap, SUMOReal predSpeed) const throw() {
    if (predSpeed==0&&gap<0.01) {
        return 0;
    }
    SUMOReal vsafe=0.0;
    //Const values of traffic vels seen for this particular model
    const SUMOReal vMax = 8.888889; 
    const SUMOReal vMin = 2.777789;

    int member, source;
    float sum;
    enum{OK, Error, Not_Valid};
    UT* unit;

    float in[2], out[1];
    in[0] = (float)gap;
    float inputVel = (predSpeed - vMin)/(vMax - vMin);
    in[1] = inputVel;

    /* layer definition section (names & member units) */

    //static UT* Input[2] = {Units + 1, Units + 2}; /* members */

    static UT* Hidden[10] = {Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12}; /* members */

    const int outputIndex = 13;
    static UT* Output = &Units[outputIndex]; /* members */


    // Set the input variables
    for(member = 0; member < 2; member++) {
            //Input[member]->act = in[member];
            unit = &Units[member + 1];
            //TODO: Change this for SUMO
            unit->act = in[member];
    }

    // Run the major algo
    for (member = 0; member < 10; member++) {
            unit = Hidden[member];
            sum = 0.0;
            for (source = 0; source < unit->NoOfSources; source++) {
                    sum += unit->sources[source]->act * unit->weights[source];
            }
            unit->act = actLogistic(sum, unit->Bias);
    }

    // Calculate the output
    unit = Output;
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
            sum += unit->sources[source]->act * unit->weights[source];
    }
    unit->act = actLogistic(sum, unit->Bias);

    // Give the output
    // TODO: Change this for SUMO
    out[0] = Units[outputIndex].act;
    SUMOReal outVel = (vMax - vMin) * out[0] + vMin;
    vsafe = outVel;


    assert(vsafe >= 0);
    return vsafe;
}



//void MSCFModel::saveState(std::ostream &os) {}

