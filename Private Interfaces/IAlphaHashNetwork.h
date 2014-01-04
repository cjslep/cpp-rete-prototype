//
//  IAlphaHashNetwork.h
//  CppRete
//
//  Created by Cory Slep on 11/3/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IAlphaHashNetwork_h
#define CppRete_IAlphaHashNetwork_h

#include "Namespaces.h"

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
class IAlphaNodeTest;
NAMESPACE_RETE_END

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class ICondition;

class IAlphaHashNetwork
{
public:
    virtual ~IAlphaHashNetwork() {}
    
    virtual bool AddAlphaNodeTestAndNetwork(IAlphaNodeTest* pAlphaNodeTest, IAlphaHashNetwork* pNextNetwork) = 0;
    virtual bool AddAlphaNodeTestAndMemory(IAlphaNodeTest* pAlphaNodeTest, IAlphaMemory* pAlphaMemory) = 0;
    virtual void AddWME(NAMESPACE_TUPLE::IWME* pIWME) = 0;
    virtual void RemoveWME(NAMESPACE_TUPLE::IWME* pIWME) = 0;
    virtual IAlphaMemory* GetCondition(ICondition* pCondition) const = 0;
    virtual IAlphaNodeTest* AddConditionAndMemory(ICondition* pCondition, IAlphaMemory* pAlphaMem, bool addSubHashes) = 0;
    virtual bool PruneUnusedAlphaMemories() = 0;
    virtual bool HasTests() = 0;
};

NAMESPACE_RETE_ALG_END

#endif
