//
//  NaiveReteController.h
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveReteController__
#define __CppRete__NaiveReteController__

#include "Namespaces.h"
#include "IReteController.h"
#include "IActivationVisitor.h"
#include "IAlphaHashNetwork.h"
#include "IProductionNode.h"
#include "ITokenFactory.h"
#include "IAlphaNetworkFactory.h"
#include "IProductionModifier.h"
#include <list>
#include <unordered_map>

class NaiveReteController : public IReteController
{
public:
    NaiveReteController();
    virtual ~NaiveReteController();
    
    virtual void StageNewProduction();
    virtual bool PrepareCondition(long valID, long valAttrType, long valAttrVal);
    virtual bool PrepareCondition(const char* varID, long varIDLength, long valAttrType, long valAttrVal);
    virtual bool PrepareCondition(const char* varID, long varIDLength, long valAttrType, const char* varAttrVal, long varAttrValLength);
    virtual bool PrepareCondition(const char* varID, long varIDLength, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength);
    virtual bool PrepareCondition(long valID, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength);
    virtual bool PrepareCondition(long valID, long valAttrType, const char* varAttrVal, long varAttrValLength);
    virtual long PublishProduction();
    virtual bool RemoveData(long valID, long valAttrType, long valAttrVal);
    virtual bool RemoveData(long valID, long valAttrType);
    virtual bool AddData(long valID, long valAttrType, long valAttrVal);
    virtual bool HasIDAttrData(long valID, long valAttrType);
    virtual bool RemoveProduction(long productionID);
    virtual bool AddSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber);
    virtual bool RemoveSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber);
    
protected:
    // Helper finders
    std::list<NAMESPACE_RETE_ALG::ICondition*>::iterator FindConditionByValue(NAMESPACE_RETE_ALG::ICondition* member);
    std::list<NAMESPACE_TUPLE::IWME*>::iterator FindWMEByIDAndAttributeType(NAMESPACE_TUPLE::IWME* member);
    std::list<NAMESPACE_TUPLE::IWME*>::iterator FindWMEByValue(NAMESPACE_TUPLE::IWME* member);
    
    long m_lCurrentProdID;
    NAMESPACE_TUPLE_OVRHD::ITokenFactory* m_pTokenFactory;
    NAMESPACE_RETE_ALG::IAlphaNetworkFactory* m_pAlphaNetFactory;
    
    NAMESPACE_RETE_ALG::IActivationVisitor* m_pAlgVisitor;
    NAMESPACE_RETE_ALG::IAlphaHashNetwork* m_pHeadHash;
    NAMESPACE_RETE::IBetaMemory* m_pDummyTop;
    NAMESPACE_RETE_ALG::IProductionModifier* m_pProductionModifier;
    std::list<NAMESPACE_TUPLE::IWME*> m_listIWMEs;
    std::unordered_map<long, NAMESPACE_RETE::IProductionNode*> m_mapIDtoProduction;
    
    std::list<NAMESPACE_RETE_ALG::ICondition*> m_listConditions;
};


#include "ExportedFunctions.h"

#endif /* defined(__CppRete__NaiveReteController__) */
