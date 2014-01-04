//
//  IReteAlgorithm.h
//  CppRete
//
//  Created by Cory Slep on 9/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IReteController_h
#define CppRete_IReteController_h

#include "IProductionSubscriber.h"

struct IReteController
{
public:
    virtual ~IReteController() {};
    // Prepares for a new production, clears any preexisting staging material
    virtual void StageNewProduction() = 0;
    virtual bool PrepareCondition(long valID, long valAttrType, long valAttrVal) = 0;
    virtual bool PrepareCondition(const char* varID, long varIDLength, long valAttrType, long valAttrVal) = 0;
    virtual bool PrepareCondition(const char* varID, long varIDLength, long valAttrType, const char* varAttrVal, long varAttrValLength) = 0;
    virtual bool PrepareCondition(const char* varID, long varIDLength, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength) = 0;
    virtual bool PrepareCondition(long valID, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength) = 0;
    virtual bool PrepareCondition(long valID, long valAttrType, const char* varAttrVal, long varAttrValLength) = 0;
    virtual long PublishProduction() = 0;
    virtual bool RemoveData(long valID, long valAttrType, long valAttrVal) = 0;
    virtual bool RemoveData(long valID, long valAttrType) = 0;
    virtual bool AddData(long valID, long valAttrType, long valAttrVal) = 0;
    virtual bool HasIDAttrData(long valID, long valAttrType) = 0;
    virtual bool RemoveProduction(long productionID) = 0;
    virtual bool AddSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber) = 0;
    virtual bool RemoveSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber) = 0;
};

extern "C" IReteController* NewReteController(void);
typedef IReteController* ReteController_Constructor(void);
extern "C" void DeleteReteController(IReteController* pController);
typedef void ReteController_Destructor(IReteController*);

#endif
