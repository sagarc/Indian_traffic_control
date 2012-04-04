/****************************************************************************/
/// @file    MSLane.cpp
/// @author  Christian Roessel
/// @date    Mon, 05 Mar 2001
/// @version $Id: MSLane.cpp 8785 2010-05-26 17:09:58Z behrisch $
///
// Representation of a lane in the micro simulation
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright 2001-2010 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <utils/common/UtilExceptions.h>
#include <utils/common/StdDefs.h>
#include "MSVehicle.h"
#include "MSVehicleType.h"
#include "MSEdge.h"
#include "MSJunction.h"
#include "MSLogicJunction.h"
#include "MSLink.h"
#include "MSStrip.h"
#include "MSLane.h"
#include "MSVehicleTransfer.h"
#include "MSGlobals.h"
#include "MSVehicleControl.h"
#include <cmath>
#include <bitset>
#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>
#include <iterator>
#include <exception>
#include <climits>
#include <set>
#include <utils/common/MsgHandler.h>
#include <utils/common/ToString.h>
#include <utils/options/OptionsCont.h>
#include <utils/common/HelpersHarmonoise.h>

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// static member definitions
// ===========================================================================
MSLane::DictType MSLane::myDict;


// ===========================================================================
// member method definitions
// ===========================================================================
MSLane::MSLane(const std::string &id, SUMOReal maxSpeed, SUMOReal length, 
               size_t stripWidth, MSEdge * const edge,
               unsigned int numericalID, const Position2DVector &shape,
               const std::vector<SUMOVehicleClass> &allowed,
               const std::vector<SUMOVehicleClass> &disallowed) throw()
        : myShape(shape), myID(id), myNumericalID(numericalID),
	myStrips(), //TODO: refactor out myVehicles
        myVehicles(), myLength(length), myEdge(edge), myMaxSpeed(maxSpeed),
        myAllowedClasses(allowed), myNotAllowedClasses(disallowed),
        myVehicleLengthSum(0), myInlappingVehicleEnd(10000), myInlappingVehicle(0) {
    //std::cerr << "StripWidth is:" << stripWidth << " for lane:" << id << std::endl;
    for (unsigned int stripNumId=0; stripNumId < stripWidth; ++stripNumId) {
        myStrips.push_back (new MSStrip("strip"+toString<int>(stripNumId)+"_"+id, length, edge, this, stripNumId));
    }
    
    myWidth = myStrips.size();
}


MSLane::~MSLane() throw() {
    for (MSLinkCont::iterator i=myLinks.begin(); i!=myLinks.end(); ++i) {
        delete *i;
    }
}


void
MSLane::initialize(MSLinkCont* links) {
    myLinks = *links;
    delete links;
}


// ------ interaction with MSMoveReminder ------
void
MSLane::addMoveReminder(MSMoveReminder* rem) throw() {
    myMoveReminders.push_back(rem);
}



// ------ Vehicle emission ------
bool
MSLane::freeEmit(MSVehicle& veh, SUMOReal mspeed) throw() {

	 size_t stripId = getEmptyStartStripID(veh.getWidth());

	bool adaptableSpeed = true;
    if (getVehicleNumber()==0) {
        if (isEmissionSuccess(&veh, mspeed, 0, adaptableSpeed,stripId)) {
            return true;
        }
    } else {
        // check whether the vehicle can be put behind the last one if there is such
        MSVehicle *leader = getLastVehicle(veh.getStrips());
        
        if (leader != 0) {
            SUMOReal leaderPos = leader->getPositionOnLane() - leader->getVehicleType().getLength();
            SUMOReal speed = mspeed;
            if (adaptableSpeed) {
                speed = leader->getSpeed();
            }
            SUMOReal frontGapNeeded = veh.getCarFollowModel().getSecureGap(speed, leader->getCarFollowModel().getSpeedAfterMaxDecel(leader->getSpeed()));
            if (leaderPos-frontGapNeeded>=0) {
                SUMOReal tspeed = MIN2(veh.getCarFollowModel().ffeV(&veh, mspeed, frontGapNeeded, leader->getSpeed()), mspeed);
                // check whether we can emit in behind the last vehicle on the lane
                if (isEmissionSuccess(&veh, tspeed, 0, adaptableSpeed, stripId)) {
                    return true;
                }
                else std::cerr << "not successful emission 1" ;
            }
        } else {
            if (isEmissionSuccess(&veh, mspeed, 0, adaptableSpeed, stripId)) {
                    return true;
            }
            else std::cerr << "not successful emission 2" ;
        }
    }
    /* ashu
      StripCont strips =getMyStrips();

     for (StripContConstIter it=strips.begin(); it != strips.end(); ++it)
     {if ((*it)->freeEmitCheck(veh, mspeed))
    	return true;}


//TODO: Uncomment and fix


    // go through the lane, look for free positions (starting after the last vehicle)
    MSLane::VehCont::iterator predIt = myVehicles.begin();
    while (predIt!=myVehicles.end()) {
        // get leader (may be zero) and follower
        const MSVehicle *leader = predIt!=myVehicles.end()-1 ? *(predIt+1) : getPartialOccupator();
        const MSVehicle *follower = *predIt;

        // patch speed if allowed
        SUMOReal speed = mspeed;
        if (adaptableSpeed&&leader!=0) {
            speed = MIN2(leader->getSpeed(), mspeed);
        }

        // compute the space needed to not collide with leader
        SUMOReal frontMax = getLength();
        if (leader!=0) {
            SUMOReal leaderRearPos = leader->getPositionOnLane() - leader->getVehicleType().getLength();
            if (leader == getPartialOccupator()) {
                leaderRearPos = getPartialOccupatorEnd();
            }
            frontMax = leaderRearPos - veh.getCarFollowModel().getSecureGap(speed, leader->getCarFollowModel().getSpeedAfterMaxDecel(leader->getSpeed()));
        }
        // compute the space needed to not let the follower collide
        const SUMOReal followPos = follower->getPositionOnLane();
        const SUMOReal backGapNeeded = follower->getCarFollowModel().getSecureGap(follower->getSpeed(), veh.getCarFollowModel().getSpeedAfterMaxDecel(speed));
        const SUMOReal backMin = followPos + backGapNeeded + veh.getVehicleType().getLength();

        // check whether there is enough room (given some extra space for rounding errors)
        if (frontMax>0 && backMin+POSITION_EPS<frontMax) {
            // try emit vehicle (should be always ok)
            if (isEmissionSuccess(&veh, speed, backMin+POSITION_EPS, adaptableSpeed)) {
            	std::cerr << "FIX working" ;
            	return true;
            }
        }
        ++predIt;
    }



  */
    //TODO:  Recheck01 ___AB oct 2011

    StripCont strips =getMyStrips();
   for (StripContConstIter it=strips.begin(); it != strips.end(); ++it)
   {
    // go through the lane, look for free positions (starting after the last vehicle)
    MSLane::VehCont::iterator predIt = (*it)->myVehicles.begin();
    while (predIt!=(*it)->myVehicles.end()) {
        // get leader (may be zero) and follower
        const MSVehicle *leader = predIt!=(*it)->myVehicles.end()-1 ? *(predIt+1) : (*it)->getPartialOccupator();
        const MSVehicle *follower = *predIt;

        // patch speed if allowed
        SUMOReal speed = mspeed;
        if (adaptableSpeed&&leader!=0) {
            speed = MIN2(leader->getSpeed(), mspeed);
        }

        // compute the space needed to not collide with leader
        SUMOReal frontMax = getLength();
        if (leader!=0) {
            SUMOReal leaderRearPos = leader->getPositionOnLane() - leader->getVehicleType().getLength();
            if (leader == (*it)->getPartialOccupator()) {
                leaderRearPos = (*it)->getPartialOccupatorEnd();
            }
            frontMax = leaderRearPos - veh.getCarFollowModel().getSecureGap(speed, leader->getCarFollowModel().getSpeedAfterMaxDecel(leader->getSpeed()));
        }
        // compute the space needed to not let the follower collide
        const SUMOReal followPos = follower->getPositionOnLane();
        const SUMOReal backGapNeeded = follower->getCarFollowModel().getSecureGap(follower->getSpeed(), veh.getCarFollowModel().getSpeedAfterMaxDecel(speed));
        const SUMOReal backMin = followPos + backGapNeeded + veh.getVehicleType().getLength();

        // check whether there is enough room (given some extra space for rounding errors)
        if (frontMax>0 && backMin+POSITION_EPS<frontMax) {
            // try emit vehicle (should be always ok)
            if (isEmissionSuccess(&veh, speed, backMin+POSITION_EPS, adaptableSpeed, stripId)) {
            	std::cerr << "FIX working" ;
            	return true;
            }
        }
        ++predIt;
    }
   }//for
    // first check at lane's begin
   std::cerr << "not successful emission last" ;
    return false;
}


bool
MSLane::emit(MSVehicle& veh) throw(ProcessError) {
    SUMOReal pos = 0;
    SUMOReal speed = 0;
    bool patchSpeed = true; // whether the speed shall be adapted to infrastructure/traffic in front

    // determine the speed
    const SUMOVehicleParameter &pars = veh.getParameter();
    size_t stripId = getEmptyStartStripID(veh.getWidth());
    switch (pars.departSpeedProcedure) {
    case DEPART_SPEED_GIVEN:
        speed = pars.departSpeed;
        patchSpeed = false;
        break;
    case DEPART_SPEED_RANDOM:
        speed = RandHelper::rand(MIN2(veh.getMaxSpeed(), getMaxSpeed()));
        patchSpeed = true; // !!!(?)
        break;
    case DEPART_SPEED_MAX:
        speed = MIN2(veh.getMaxSpeed(), getMaxSpeed());
        patchSpeed = true; // !!!(?)
        break;
    case DEPART_SPEED_DEFAULT:
    default:
        // speed = 0 was set before
        patchSpeed = false; // !!!(?)
        break;
    }

    // determine the position
    switch (pars.departPosProcedure) {
    case DEPART_POS_GIVEN:
        if (pars.departPos >= 0.) {
            pos = pars.departPos;
        } else {
            pos = pars.departPos + getLength();
        }
        break;
    case DEPART_POS_RANDOM:
        pos = RandHelper::rand(getLength());
        break;
    case DEPART_POS_RANDOM_FREE: {
        for (unsigned int i=0; i < 10; i++) {
            // we will try some random positions ...
            pos = RandHelper::rand(getLength());
            if (isEmissionSuccess(&veh, speed, pos, patchSpeed, stripId)) {
                return true;
            }
        }
        // ... and if that doesn't work, we put the vehicle to the free position
        return freeEmit(veh, speed);
    }
    break;
    case DEPART_POS_FREE:
        return freeEmit(veh, speed);
    case DEPART_POS_DEFAULT:
    default:
        // pos = 0 was set before
        break;
    }

    // try to emit
    return isEmissionSuccess(&veh, speed, pos, patchSpeed, stripId);
}


bool
MSLane::isEmissionSuccess(MSVehicle* aVehicle,
                          SUMOReal speed, SUMOReal pos,
                          bool patchSpeed, size_t startStripId) throw(ProcessError) {
    //  and the speed is not too high (vehicle should decelerate)
    // try to get a leader on consecutive lanes
    //  we have to do this even if we have found a leader on our lane because it may
    //  be driving into another direction
    //std::cerr<<"EMISSION speed:"<<speed<<std::endl;
	std::cerr<<"EMISSION vehicle:"<<aVehicle->getID()<<std::endl;
    size_t endStripId = startStripId + aVehicle->getWidth() - 1;
    assert(startStripId >=0 && endStripId < myStrips.size());
    aVehicle->getBestLanes(true, this);
    const MSCFModel &cfModel = aVehicle->getCarFollowModel();
    const std::vector<MSLane*> &bestLaneConts = aVehicle->getBestLanesContinuation(this);
    std::vector<MSLane*>::const_iterator ri = bestLaneConts.begin();
    SUMOReal seen = getLength() - pos;
    SUMOReal dist = cfModel.brakeGap(speed);
    const MSRoute &r = aVehicle->getRoute();
    MSRouteIterator ce = r.begin();
    MSLane *currentLane = this;
    MSLane *nextLane = this;
    while (seen<dist&&ri!=bestLaneConts.end()&&nextLane!=0/*&&ce!=r.end()*/) {
        // get the next link used...
        MSLinkCont::const_iterator link = currentLane->succLinkSec(*aVehicle, 1, *currentLane, bestLaneConts);
        // ...and the next used lane (including internal)
        if (!currentLane->isLinkEnd(link) && (*link)->havePriority() && (*link)->getState()!=MSLink::LINKSTATE_TL_RED) { // red may have priority?
#ifdef HAVE_INTERNAL_LANES
            bool nextInternal = false;
            nextLane = (*link)->getViaLane();
            if (nextLane==0) {
                nextLane = (*link)->getLane();
            } else {
                nextInternal = true;
            }
#else
            nextLane = (*link)->getLane();
#endif
        } else {
            nextLane = 0;
        }
        // check how next lane effects the journey
        if (nextLane!=0) {
            SUMOReal gap = 0;
            //TODO: fix get & set partial occupator to strip level
            MSVehicle * leader = 0;//currentLane->getPartialOccupator();
            if (leader!=0) {
                gap = getPartialOccupatorEnd();
            } else {
                // check leader on next lane
                leader = nextLane->getLastVehicle(aVehicle->getStrips());
                if (leader!=0) {
                    gap = seen+leader->getPositionOnLane()-leader->getVehicleType().getLength();
                }
            }
            if (leader!=0) {
                SUMOReal nspeed = gap>=0 ? cfModel.ffeV(aVehicle, speed, gap, leader->getSpeed()) : 0;
                if (nspeed<speed) {
                    if (patchSpeed) {
                        speed = MIN2(nspeed, speed);
                        dist = cfModel.brakeGap(speed);
                    } else {
                        // we may not drive with the given velocity - we crash into the leader
                        return false;
                    }
                }
            }
            // check next lane's maximum velocity
            SUMOReal nspeed = nextLane->getMaxSpeed();
            if (nspeed<speed) {
                // patch speed if needed
                if (patchSpeed) {
                    speed = MIN2(cfModel.ffeV(aVehicle, speed, seen, nspeed), speed);
                    dist = cfModel.brakeGap(speed);
                } else {
                    // we may not drive with the given velocity - we would be too fast on the next lane
                    return false;
                }
            }
            // check traffic on next junctions
            const SUMOTime arrivalTime = MSNet::getInstance()->getCurrentTimeStep() + TIME2STEPS(seen / speed);
#ifdef HAVE_INTERNAL_LANES
            const SUMOTime leaveTime = (*link)->getViaLane()==0 ? arrivalTime + TIME2STEPS((*link)->getLength() * speed) : arrivalTime + TIME2STEPS((*link)->getViaLane()->getLength() * speed);
#else
            const SUMOTime leaveTime = arrivalTime + TIME2STEPS((*link)->getLength() * speed);
#endif
            if ((*link)->hasApproachingFoe(arrivalTime, leaveTime)) {
                SUMOReal nspeed = cfModel.ffeV(aVehicle, speed, seen, 0);
                if (nspeed<speed) {
                    if (patchSpeed) {
                        speed = MIN2(nspeed, speed);
                        dist = cfModel.brakeGap(speed);
                    } else {
                        // we may not drive with the given velocity - we crash into the leader
                        return false;
                    }
                }
            } else {
                // we can only drive to the end of the current lane...
                SUMOReal nspeed = cfModel.ffeV(aVehicle, speed, seen, 0);
                if (nspeed<speed) {
                    if (patchSpeed) {
                        speed = MIN2(nspeed, speed);
                        dist = cfModel.brakeGap(speed);
                    } else {
                        // we may not drive with the given velocity - we crash into the leader
                        return false;
                    }
                }
            }
            seen += nextLane->getLength();
            ++ce;
            ++ri;
            currentLane = nextLane;
        }
    }
    if (seen<dist) {
        SUMOReal nspeed = cfModel.ffeV(aVehicle, speed, seen, 0);
        if (nspeed<speed) {
            if (patchSpeed) {
                speed = MIN2(nspeed, speed);
                dist = cfModel.brakeGap(speed);
            } else {
                // we may not drive with the given velocity - we crash into the leader
                MsgHandler::getErrorInstance()->inform("Vehicle '" + aVehicle->getID() + "' will not be able to emit using given velocity!");
                // !!! we probably should do something else...
                return false;
            }
        }
    }

    // get the pointer to the vehicle next in front of the given position
    MSVehicle *pred;
    std::vector<MSVehicle *> predCont;
    std::vector<MSVehicle *>::iterator predIt, it;
    for (unsigned int i=startStripId; i<=endStripId; ++i) {
        predCont.push_back(myStrips.at(i)->getPredAtPos(pos));
    }
    predIt = predCont.begin();
    SUMOReal currMin = -1;
    if (*predIt != 0) {
        currMin = (*predIt)->getPositionOnLane();
    } else {
        // signals no leader in front
        predIt = predCont.end();
    }
    for (it = predCont.begin(); it != predCont.end(); ++it) {
        if (*it == 0) continue;
        if ((*it)->getPositionOnLane() < currMin) {
            predIt = it;
            currMin = (*it)->getPositionOnLane();
        }
    }
    
    if (predIt != predCont.end()) {
        // ok, there is one (a leader)
        MSVehicle* leader = *predIt;
        SUMOReal frontGapNeeded = aVehicle->getCarFollowModel().getSecureGap(speed, leader->getCarFollowModel().getSpeedAfterMaxDecel(leader->getSpeed()));
        SUMOReal gap = MSVehicle::gap(leader->getPositionOnLane(), leader->getVehicleType().getLength(), pos);
        if (gap<frontGapNeeded) {
            // too close to the leader on this lane
            return false;
        }
    }

    // FIXME: implement look back
    // check back vehicle
    if (false/*predIt!=myVehicles.begin()*/) {
        // there is direct follower on this lane
        MSVehicle *follower = *(predIt-1);
        SUMOReal backGapNeeded = follower->getCarFollowModel().getSecureGap(follower->getSpeed(), aVehicle->getCarFollowModel().getSpeedAfterMaxDecel(speed));
        SUMOReal gap = MSVehicle::gap(pos, aVehicle->getVehicleType().getLength(), follower->getPositionOnLane());
        if (gap<backGapNeeded) {
            // too close to the follower on this lane
            return false;
        }
    } else if (false) {
        // check approaching vehicle (consecutive follower)
        SUMOReal lspeed = getMaxSpeed();
        // in order to look back, we'd need the minimum braking ability of vehicles in the net...
        //  we'll assume it to be 4m/s^2
        //   !!!revisit
        SUMOReal dist = lspeed * lspeed * SUMOReal(1./2.*4.) + SPEED2DIST(lspeed);
        std::pair<const MSVehicle * const, SUMOReal> approaching = getFollowerOnConsecutive(dist, 0, speed, pos - aVehicle->getVehicleType().getLength());
        if (approaching.first!=0) {
            const MSVehicle *const follower = approaching.first;
            SUMOReal backGapNeeded = follower->getCarFollowModel().getSecureGap(follower->getSpeed(), aVehicle->getCarFollowModel().getSpeedAfterMaxDecel(speed));
            SUMOReal gap = approaching.second - pos - aVehicle->getVehicleType().getLength();
            if (gap<backGapNeeded) {
                // too close to the consecutive follower
                return false;
            }
        }
        // check for in-lapping vehicle
        MSVehicle* leader = getPartialOccupator();
        if (leader!=0) {
            SUMOReal frontGapNeeded = aVehicle->getCarFollowModel().getSecureGap(speed, leader->getCarFollowModel().getSpeedAfterMaxDecel(leader->getSpeed()));
            SUMOReal gap = getPartialOccupatorEnd() - pos;
            if (gap<=frontGapNeeded) {
                // too close to the leader on this lane
                return false;
            }
        }
    }

    // may got negative while adaptation
    if (speed<0) {
        return false;
    }
    // enter
    //XXX: later change to enterStripAtEmit()?
    //if (speed < 0.0001) speed += 10.0;
    StripCont strips;
    strips.resize(aVehicle->getWidth());
    StripCont::iterator start = myStrips.begin() + startStripId;
    std::copy(start, start + aVehicle->getWidth(), strips.begin());
    aVehicle->enterLaneAtEmit(this, pos, speed, strips);
    bool wasInactive = getVehicleNumber()==0;
    if (true/*predIt==myVehicles.end()*/) {
        // vehicle will be the first on the lane
        //std::cerr<<"startStripId:"<<startStripId<<", NumStrips:"<<strips.size()<<", VehWidth:"<<aVehicle->getWidth()<<std::endl;
        for (size_t i=startStripId; i<startStripId+strips.size(); ++i) {
                this->getStrip(i)->pushIntoStrip(aVehicle);
                this->getStrip(i)->setVehLenSum(this->getStrip(i)->getVehLenSum() + 
                                                        aVehicle->getVehicleType().getLength());
        }
        aVehicle->printDebugMsg("Emitting");
        printDebugMsg();
    } else {
        //this->getStrip(0).insert(0, aVehicle);
    }
    //myVehicleLengthSum += aVehicle->getVehicleType().getLength();
    if (wasInactive) {
        MSNet::getInstance()->getEdgeControl().gotActive(this);
    }
    return true;
}


// ------ Handling vehicles lapping into lanes ------
SUMOReal
MSLane::setPartialOccupation(MSVehicle *v, SUMOReal leftVehicleLength) throw() {
    myInlappingVehicle = v;
    if (leftVehicleLength>myLength) {
        myInlappingVehicleEnd = 0;
    } else {
        myInlappingVehicleEnd = myLength-leftVehicleLength;
    }
    return myLength;
    assert (v != 0);
    MSVehicle::StripCont strips = v->getStrips();
    MSVehicle::StripCont::iterator it = strips.begin();
    for (; it != strips.end(); ++it) {
        (*it)->setPartialOccupation(v, leftVehicleLength);
    }
    
}


void
MSLane::resetPartialOccupation(MSVehicle *v) throw() {
    if (v==myInlappingVehicle) {
        myInlappingVehicleEnd = 10000;
    }
    myInlappingVehicle = 0;
    /*
    assert (v != 0);
    MSVehicle::StripCont strips = v->getStrips();
    MSVehicle::StripCont::iterator it = strips.begin();
    for (; it != strips.end(); ++it) {
        (*it)->resetPartialOccupation(v);
    }
    */
}


std::pair<MSVehicle*, SUMOReal>
MSLane::getLastVehicleInformation() const throw() {
    //TODO: make efficient
    std::vector< std::pair<MSVehicle*, SUMOReal> > lastVehCont;
    std::vector< std::pair<MSVehicle*, SUMOReal> >::iterator lastVehContIt;
    for (StripCont::const_iterator it = myStrips.begin(); it != myStrips.end(); ++it) {
        //MSVehicle *last = *((*it)->myVehicles.begin());
        lastVehCont.push_back((*it)->getLastVehicleInformation());
    }
    std::unique(lastVehCont.begin(), lastVehCont.end(), VehInfoEqComparator());
    lastVehContIt = std::min_element(lastVehCont.begin(), lastVehCont.end(), VehInfoLessComparator() );
    return std::make_pair(lastVehContIt->first, lastVehContIt->second);
}


// ------  ------
bool
MSLane::moveCritical(SUMOTime t) {
    StripContIter it = myStrips.begin();
    bool res = true;
    for (it; it != myStrips.end(); ++it) {
        // returns false if there is atleast one vehicle in lane
        bool empty = (*it)->moveCritical(t);
        res = res && empty;
    }
    return res;
    // return getVehicleNumber()==0;
}


void
MSLane::detectCollisions(SUMOTime timestep) {
    for (StripContIter strip = myStrips.begin(); strip != myStrips.end(); ++strip) {
        (*strip)->detectCollisions(timestep);
    }
}


SUMOReal
getMaxSpeedRegardingNextLanes(MSVehicle& veh, SUMOReal speed, SUMOReal pos) {
    MSRouteIterator next = veh.getRoute().begin();
    const MSCFModel &cfModel = veh.getCarFollowModel();
    MSLane *currentLane = (*next)->getLanes()[0];
    SUMOReal seen = currentLane->getLength() - pos;
    SUMOReal dist = SPEED2DIST(speed) + cfModel.brakeGap(speed);
    SUMOReal tspeed = speed;
    while (seen<dist&&next!=veh.getRoute().end()-1) {
        ++next;
        MSLane *nextLane = (*next)->getLanes()[0];
        tspeed = MIN2(cfModel.ffeV(&veh, tspeed, seen, nextLane->getMaxSpeed()), nextLane->getMaxSpeed());
        dist = SPEED2DIST(tspeed) + cfModel.brakeGap(tspeed);
        seen += nextLane->getMaxSpeed();
    }
    return tspeed;
}


bool
MSLane::setCritical(SUMOTime t, std::vector<MSLane*> &into) {
    // move critical vehicles
    StripCont::iterator i;
    for (i=myStrips.begin(); i!=myStrips.end(); ++i) {
        (*i)->setCritical(t, into);
    }
    return getVehicleNumber()==0;
}


bool
MSLane::dictionary(std::string id, MSLane* ptr) {
    DictType::iterator it = myDict.find(id);
    if (it == myDict.end()) {
        // id not in myDict.
        myDict.insert(DictType::value_type(id, ptr));
        return true;
    }
    return false;
}


MSLane*
MSLane::dictionary(std::string id) {
    DictType::iterator it = myDict.find(id);
    if (it == myDict.end()) {
        // id not in myDict.
        return 0;
    }
    return it->second;
}


void
MSLane::clear() {
    for (DictType::iterator i=myDict.begin(); i!=myDict.end(); ++i) {
        delete(*i).second;
    }
    myDict.clear();
}


void
MSLane::insertIDs(std::vector<std::string> &into) throw() {
    for (DictType::iterator i=myDict.begin(); i!=myDict.end(); ++i) {
        into.push_back((*i).first);
    }
}


bool
MSLane::push(MSVehicle* veh, const std::vector<int> &stripID, bool hasMainStrip) {
    //assert (veh->getStrips().size() != 0);
    
    MSVehicle::StripCont strips;
    // Insert vehicle only if it's destination isn't reached.
    //  and it does not collide with previous
    // check whether the vehicle has ended his route
    // Add to mean data (edge/lane state dump)
    if (! veh->moveRoutePointer(myEdge)) {     // adjusts vehicles routeIterator
        for (int i=0; i<stripID.size(); ++i) {
            MSStrip *strip = getStrip(stripID[i]);
            strip->push(veh);
            strips.push_back(strip);
        }
        veh->enterLaneAtMove(this, SPEED2DIST(veh->getSpeed()) - veh->getPositionOnLane(), strips, hasMainStrip);
        SUMOReal pspeed = veh->getSpeed();
        SUMOReal oldPos = veh->getPositionOnLane() - SPEED2DIST(veh->getSpeed());
        veh->workOnMoveReminders(oldPos, veh->getPositionOnLane(), pspeed);
        return false;
    } else {
        if (hasMainStrip) {
            veh->enterLaneAtMove(this, SPEED2DIST(veh->getSpeed()) - veh->getPositionOnLane(), strips, hasMainStrip);
            veh->onRemovalFromNet(false);
            MSNet::getInstance()->getVehicleControl().scheduleVehicleRemoval(veh);
        }
        return true;
    }
}

//TODO: refactor out? only called by setCritical for getting the leader (last veh of lane)
MSVehicle*
MSLane::pop(SUMOTime) {
    assert(! myVehicles.empty());
    MSVehicle* first = myVehicles.back();
    first->leaveLaneAtMove(SPEED2DIST(first->getSpeed())/* - first->pos()*/);
    myVehicles.pop_back();
    myVehicleLengthSum -= first->getVehicleType().getLength();
    return first;
}


bool
MSLane::appropriate(const MSVehicle *veh) {
    if (myEdge->getPurpose()==MSEdge::EDGEFUNCTION_INTERNAL) {
        return true;
    }
    MSLinkCont::const_iterator link = succLinkSec(*veh, 1, *this, veh->getBestLanesContinuation());
    return (link != myLinks.end());
}


bool
MSLane::integrateNewVehicle(SUMOTime t) {
    bool wasInactive = getVehicleNumber()==0;
    bool hasActivity = false;
    for (StripContIter strip = myStrips.begin(); strip != myStrips.end(); ++strip) {
        bool res = (*strip)->integrateNewVehicle(t);
        hasActivity = hasActivity || res;
    }
    return wasInactive&&hasActivity;
}


bool
MSLane::isLinkEnd(MSLinkCont::const_iterator &i) const {
    return i==myLinks.end();
}


bool
MSLane::isLinkEnd(MSLinkCont::iterator &i) {
    return i==myLinks.end();
}


MSVehicle * const
MSLane::getLastVehicle(const MSVehicle::StripCont &strips) const {
    MSVehicle::StripContConstIter strip = strips.begin();
    MSVehicle *last = 0;
    
    while (strip != strips.end()) {
        last = (*strip)->getLastVehicle();
        if (last != 0) break;
        strip++;
    }
    if (last == 0) return last;
    
    for (MSVehicle::StripContConstIter it=strip+1; it != strips.end(); ++it) {
        MSVehicle *curr = (*it)->getLastVehicle();
        if (!curr) continue;
        
        if (last->getPositionOnLane()-last->getVehicleType().getLength() 
                > 
                curr->getPositionOnLane()-curr->getVehicleType().getLength())
            last = curr;
    }
    //DEBUG
    ///*
    std::pair<MSVehicle*, SUMOReal> lvInfo = getLastVehicleInformation();
    if (last != lvInfo.first)
        MsgHandler::getWarningInstance()->inform("LastVEH_ERR::Lane=" + this->getID() + 
                ", time=" + time2string(MSNet::getInstance()->getCurrentTimeStep()) + ".");
    //*/
    return last;
}


const MSVehicle * const
MSLane::getFirstVehicle() const {
    //XXX: partial occupators don't count?
    StripCont::const_iterator it = myStrips.begin();
    const MSVehicle *first = (*it)->getFirstVehicle();
    
    for (; it != myStrips.end(); ++it) {
        MSVehicle *curr = (*it)->getLastVehicle();
        if (curr == 0)
            continue;
        else if (first == 0 && curr != 0)
            first = curr;
        
        if (first->getPositionOnLane() < curr->getPositionOnLane())
            first = curr;
    }
    return first;
}


MSLinkCont::const_iterator
MSLane::succLinkSec(const SUMOVehicle& veh, unsigned int nRouteSuccs,
                    const MSLane& succLinkSource, const std::vector<MSLane*> &conts) const {
    const MSEdge* nRouteEdge = veh.succEdge(nRouteSuccs);
    // check whether the vehicle tried to look beyond its route
    if (nRouteEdge==0) {
        // return end (no succeeding link) if so
        return succLinkSource.myLinks.end();
    }
    // a link may be used if
    //  1) there is a destination lane ((*link)->getLane()!=0)
    //  2) the destination lane belongs to the next edge in route ((*link)->getLane()->myEdge == nRouteEdge)
    //  3) the destination lane allows the vehicle's class ((*link)->getLane()->allowsVehicleClass(veh.getVehicleClass()))

    // at first, we'll assume we have the continuations of our route in "conts" (built in "getBestLanes")
    //  "conts" stores the best continuations of our current lane
    MSLinkCont::const_iterator link;
    if (nRouteSuccs>0&&conts.size()>=nRouteSuccs&&nRouteSuccs>0) {
        // we go through the links in our list and return the matching one
        for (link=succLinkSource.myLinks.begin(); link!=succLinkSource.myLinks.end() ; ++link) {
            if ((*link)->getLane()!=0 && (*link)->getLane()->myEdge == nRouteEdge && (*link)->getLane()->allowsVehicleClass(veh.getVehicleType().getVehicleClass())) {
                // we should use the link if it connects us to the best lane
                if ((*link)->getLane()==conts[nRouteSuccs-1]) {
                    return link;
                }
            }
        }
    }

    // ok, we were not able to use the conts for any reason
    //  we will now collect allowed links, at first
    // collect allowed links
    std::vector<MSLinkCont::const_iterator> valid;
    for (link=succLinkSource.myLinks.begin(); link!=succLinkSource.myLinks.end() ; ++link) {
        if ((*link)->getLane()!=0 && (*link)->getLane()->myEdge == nRouteEdge && (*link)->getLane()->allowsVehicleClass(veh.getVehicleType().getVehicleClass())) {
            valid.push_back(link);
        }
    }
    // if no valid link was found...
    if (valid.size()==0) {
        // ... return end (no succeeding link)
        return succLinkSource.myLinks.end();
    }
    // if there is only one valid link, let's use it...
    if (valid.size()==1) {
        return *(valid.begin());
    }
    // if the next edge is the route end, then we may return an arbitary link
    // also, if there is no allowed lane on the edge following the current one (recheck?)
    const MSEdge* nRouteEdge2 = veh.succEdge(nRouteSuccs+1);
    const std::vector<MSLane*> *next_allowed = nRouteEdge->allowedLanes(*nRouteEdge2, veh.getVehicleType().getVehicleClass());
    if (nRouteEdge2==0||next_allowed==0) {
        return *(valid.begin());
    }
    // now let's determine which link is the best
    // in fact, we do not know it, here...
    for (std::vector<MSLinkCont::const_iterator>::iterator i=valid.begin(); i!=valid.end(); ++i) {
        if (find(next_allowed->begin(), next_allowed->end(), (**i)->getLane())!=next_allowed->end()) {
            return *i;
        }
    }
    return *(valid.begin());
}



const MSLinkCont &
MSLane::getLinkCont() const {
    return myLinks;
}


void
MSLane::swapAfterLaneChange(SUMOTime) {
    myVehicles = myTmpVehicles;
    myTmpVehicles.clear();
}




GUILaneWrapper *
MSLane::buildLaneWrapper(GUIGlObjectStorage &) {
    throw "Only within the gui-version";
}


void
MSLane::init(MSEdgeControl &, std::vector<MSLane*>::const_iterator firstNeigh, std::vector<MSLane*>::const_iterator lastNeigh) {
    myFirstNeigh = firstNeigh;
    myLastNeigh = lastNeigh;
}


MSVehicle *
MSLane::removeFirstVehicle() {
    MSVehicle *veh = *(myVehicles.end()-1);
    veh->leaveLaneAtMove(0);
    myVehicles.erase(myVehicles.end()-1);
    myVehicleLengthSum -= veh->getVehicleType().getLength();
    return veh;
}


MSVehicle *
MSLane::removeVehicle(MSVehicle * remVehicle) {
    for (MSLane::VehCont::iterator it = myVehicles.begin(); it < myVehicles.end(); it++) {
        if (remVehicle->getID() == (*it)->getID()) {
            remVehicle->leaveLane(true);
            myVehicles.erase(it);
            myVehicleLengthSum -= remVehicle->getVehicleType().getLength();
            break;
        }
    }
    return remVehicle;
}


MSLane * const
MSLane::getLeftLane() const {
    return myEdge->leftLane(this);
}


MSLane * const
MSLane::getRightLane() const {
    return myEdge->rightLane(this);
}


bool
MSLane::allowsVehicleClass(SUMOVehicleClass vclass) const {
    if (vclass==SVC_UNKNOWN) {
        return true;
    }
    if (myAllowedClasses.size()==0&&myNotAllowedClasses.size()==0) {
        return true;
    }
    if (find(myAllowedClasses.begin(), myAllowedClasses.end(), vclass)!=myAllowedClasses.end()) {
        return true;
    }
    if (myAllowedClasses.size()!=0) {
        return false;
    }
    if (find(myNotAllowedClasses.begin(), myNotAllowedClasses.end(), vclass)!=myNotAllowedClasses.end()) {
        return false;
    }
    return true;
}


void
MSLane::addIncomingLane(MSLane *lane, MSLink *viaLink) {
    IncomingLaneInfo ili;
    ili.lane = lane;
    ili.viaLink = viaLink;
    ili.length = lane->getLength();
    myIncomingLanes.push_back(ili);
}

class by_second_sorter {
public:
    inline int operator()(const std::pair<const MSVehicle * , SUMOReal> &p1, const std::pair<const MSVehicle * , SUMOReal> &p2) const {
        return p1.second<p2.second;
    }
};

std::pair<MSVehicle * const, SUMOReal>
MSLane::getFollowerOnConsecutive(SUMOReal dist, SUMOReal seen, SUMOReal leaderSpeed, SUMOReal backOffset) const {
    // ok, a vehicle has not noticed the lane about itself;
    //  iterate as long as necessary to search for an approaching one
    std::set<MSLane*> visited;
    std::vector<std::pair<MSVehicle *, SUMOReal> > possible;
    std::vector<MSLane::IncomingLaneInfo> newFound;
    std::vector<MSLane::IncomingLaneInfo> toExamine = myIncomingLanes;
    while (toExamine.size()!=0) {
        for (std::vector<MSLane::IncomingLaneInfo>::iterator i=toExamine.begin(); i!=toExamine.end(); ++i) {
            /*
            if ((*i).viaLink->getState()==MSLink::LINKSTATE_TL_RED) {
                continue;
            }
            */
            MSLane *next = (*i).lane;
            if (next->getFirstVehicle()!=0) {
                MSVehicle * v = (MSVehicle*) next->getFirstVehicle();
                SUMOReal agap = (*i).length - v->getPositionOnLane() + backOffset;
                if (!v->getCarFollowModel().hasSafeGap(v->getCarFollowModel().maxNextSpeed(v->getSpeed()), agap, leaderSpeed, v->getLane().getMaxSpeed())) {
                    possible.push_back(std::make_pair(v, (*i).length-v->getPositionOnLane()+seen));
                }
            } else {
                if ((*i).length+seen<dist) {
                    const std::vector<MSLane::IncomingLaneInfo> &followers = next->getIncomingLanes();
                    for (std::vector<MSLane::IncomingLaneInfo>::const_iterator j=followers.begin(); j!=followers.end(); ++j) {
                        if (visited.find((*j).lane)==visited.end()) {
                            visited.insert((*j).lane);
                            MSLane::IncomingLaneInfo ili;
                            ili.lane = (*j).lane;
                            ili.length = (*j).length + (*i).length;
                            ili.viaLink = (*j).viaLink;
                            newFound.push_back(ili);
                        }
                    }
                }
            }
        }
        toExamine.clear();
        swap(newFound, toExamine);
    }
    if (possible.size()==0) {
        return std::pair<MSVehicle * const, SUMOReal>(0, -1);
    }
    sort(possible.begin(), possible.end(), by_second_sorter());
    return *(possible.begin());
}


std::pair<MSVehicle * const, SUMOReal>
MSLane::getLeaderOnConsecutive(SUMOReal dist, SUMOReal seen, SUMOReal speed, const MSVehicle &veh,
                               const std::vector<MSLane*> &bestLaneConts) const {
    if (seen>dist) {
        return std::pair<MSVehicle * const, SUMOReal>(0, -1);
    }
    unsigned int view = 1;
    // loop over following lanes
    const MSLane * targetLane = this;
    MSVehicle *leader = targetLane->getPartialOccupator();
    if (leader!=0) {
        return std::pair<MSVehicle * const, SUMOReal>(leader, seen-targetLane->getPartialOccupatorEnd());
    }
    const MSLane * nextLane = targetLane;
    while (true) {
        // get the next link used
        MSLinkCont::const_iterator link = targetLane->succLinkSec(veh, view, *nextLane, bestLaneConts);
        if (nextLane->isLinkEnd(link) || !(*link)->havePriority() || (*link)->getState()==MSLink::LINKSTATE_TL_RED) {
            return std::pair<MSVehicle * const, SUMOReal>(0, -1);
        }
#ifdef HAVE_INTERNAL_LANES
        bool nextInternal = false;
        nextLane = (*link)->getViaLane();
        if (nextLane==0) {
            nextLane = (*link)->getLane();
        } else {
            nextInternal = true;
        }
#else
        nextLane = (*link)->getLane();
#endif
        if (nextLane==0) {
            return std::pair<MSVehicle * const, SUMOReal>(0, -1);
        }
        MSVehicle * leader = nextLane->getLastVehicle(veh.getStrips());
        if (leader!=0) {
            return std::pair<MSVehicle * const, SUMOReal>(leader, seen+leader->getPositionOnLane()-leader->getVehicleType().getLength());
        } else {
            leader = nextLane->getPartialOccupator();
            if (leader!=0) {
                return std::pair<MSVehicle * const, SUMOReal>(leader, seen+nextLane->getPartialOccupatorEnd());
            }
        }
        if (nextLane->getMaxSpeed()<speed) {
            dist = veh.getCarFollowModel().brakeGap(nextLane->getMaxSpeed());
        }
        seen += nextLane->getLength();
        if (seen>dist) {
            return std::pair<MSVehicle * const, SUMOReal>(0, -1);
        }
#ifdef HAVE_INTERNAL_LANES
        if (!nextInternal) {
            view++;
        }
#else
        view++;
#endif
    }
}


void
MSLane::leftByLaneChange(MSVehicle *v) {
    myVehicleLengthSum -= v->getVehicleType().getLength();
}


void
MSLane::enteredByLaneChange(MSVehicle *v) {
    myVehicleLengthSum += v->getVehicleType().getLength();
}


// ------------ Current state retrieval
SUMOReal
MSLane::getOccupancy() const throw() {
    return myVehicleLengthSum / myLength;
}


SUMOReal
MSLane::getVehLenSum() const throw() {
    return myVehicleLengthSum;
}


SUMOReal
MSLane::getMeanSpeed() const throw() { //ashu modification 16 november
         int temp=0; 
     if (getVehicleNumber()==0) {
        //return myMaxSpeed;
         return 0; 
    }
    SUMOReal v = 0;
    for (StripContConstIter i=myStrips.begin(); i!=myStrips.end(); ++i) {
   
        v += (*i)->getMeanSpeed();
         if ((*i)->getMeanSpeed() == 0)
             {
                temp++;
             }
     }
    SUMOReal ret = v / (SUMOReal) (myStrips.size() - temp);
    releaseVehicles();
    return ret;
}

unsigned int 
MSLane::getVehicleNumber() const throw() {
        unsigned int count = 0;
        for (StripContConstIter it = myStrips.begin(); it != myStrips.end(); ++it) {
            count += (*it)->getVehicleNumber();
        }
        return count;
}

const std::deque< MSVehicle* > & 
MSLane::getVehiclesSecure() const throw() {
    //FIXME: hack, decide what to do about this later (has few usages)
	/*std::deque< MSVehicle* > vehCont ;//?? ACE ??
	std::deque< MSVehicle* > vehBuffer;
	for (StripContConstIter it = myStrips.begin(); it != myStrips.end(); ++it) {//?? ACE ??
		vehCont = (*it)->getVehiclesSecure();//?? ACE ??
		for ( std::deque< MSVehicle* >::const_iterator it = vehCont.begin(); it != vehCont.end(); ++it) {
			vehBuffer.push_back(*it);
		}
	}
	return vehBuffer;//?? ACE ??*/
    StripContConstIter it = myStrips.begin();
    return (*it)->getVehiclesSecure();
	//return veh;//?? ACE ??
}
//?? ACE ?? only for gui
const std::deque< MSVehicle* > &
MSLane::getVehiclesSecure(int i) const throw() {
    return myStrips[i]->getVehiclesSecure();
}
    
SUMOReal
MSLane::getRealLaneWidth() const {
    assert (myStrips.size() == myWidth);
    return myStrips.size() * SUMO_const_stripWidth;
}

size_t
MSLane::getEmptyStartStripID(size_t vehWidth) const {
    StripCont::const_iterator strip = myStrips.begin();
    std::vector<SUMOReal> vehPositions(myStrips.size(), getLength());
    std::vector<SUMOReal>::iterator it, start, end;
    size_t startPos = 0;
    it = vehPositions.begin();
    
    // vehPositions contains position of end of last vehicle of every strip
    // or length of lane if there is no last vehicle
    int i=0;
    for (i=0; strip != myStrips.end(); ++strip, ++i) {
        MSVehicle *veh = (*strip)->getLastVehicle();     
        if (veh != 0)
            vehPositions[i] = veh->getPositionOnLane() - veh->getVehicleType().getLength();
    }
    assert(i==myStrips.size());
    
    // for each possible position of vehicle, find the vehicle closest to current one
    // (in all strips current vehicle occupies)
    std::map<size_t, SUMOReal> possiblePosn;
    std::map<size_t, SUMOReal>::iterator pos;
    for (size_t myStart = 0; myStart <= myStrips.size() - vehWidth; ++myStart) {
        // find min dist among all strips that vehicle may occupy
        start = vehPositions.begin() + myStart;
        end = start + vehWidth;
        it = std::min_element(start, end);
        possiblePosn[myStart] = *it;
    }
    // now find the maximum among the possible start positions
    pos = possiblePosn.begin();
    SUMOReal currMaxPos = pos->second;
    startPos = pos->first;
    for (; pos != possiblePosn.end(); ++pos) {
        if (currMaxPos < pos->second) {
            currMaxPos = pos->second;
            startPos = pos->first;
        }
    }
    //std::cerr << getID() << "::getEmptyStartStrip(" << vehWidth << ") = " << startPos << std::endl;
    return startPos;
}

MSVehicle *
MSLane::getPartialOccupator(unsigned int startStrip, unsigned int endStrip) const throw() {
    if (endStrip == 0) endStrip = myStrips.size()-1;
    assert (startStrip <= endStrip && startStrip >=0 && endStrip < myStrips.size());
    //XXX: what if vehicle is on two lanes at a time
    MSVehicle *last=0;
    SUMOReal min = myStrips.at(startStrip)->getPartialOccupatorEnd();
    for (unsigned int strip=startStrip; strip<=endStrip; ++strip) {
        SUMOReal curr = myStrips.at(strip)->getPartialOccupatorEnd();
        if (curr < min) {
            min = curr;
            last = myStrips.at(strip)->getPartialOccupator();
        }
    }
    //printDebugMsg();
    //std::cerr<<"Partial Occupator b/w "<<startStrip<<" and "<<endStrip<<" is: "<<(last != 0 ? last->getID() : "0");
    //return last;
    return myInlappingVehicle;
}

SUMOReal 
MSLane::getPartialOccupatorEnd(unsigned int startStrip, unsigned int endStrip) const throw() {
        //MSVehicle *partialOcc = getPartialOccupator(startStrip, endStrip);
        //return partialOcc->getMainStrip().getPartialOccupatorEnd();
        return myInlappingVehicleEnd;
}

void
MSLane::printDebugMsg(const std::string &msg) const {
    StripCont::const_iterator it = myStrips.begin();
    std::cerr << "Printing Lane:" << getID() << std::endl;
    for (; it != myStrips.end(); ++it) {
        (*it)->printDebugMsg();
    }
}
/****************************************************************************/
