//
//  NaiveAlphaHashNetwork.h
//  CppRete
//
//  Created by Cory Slep on 11/3/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveAlphaHashNetwork__
#define __CppRete__NaiveAlphaHashNetwork__

#include "Namespaces.h"
#include "IAlphaHashNetwork.h"
#include <unordered_map>
#include <list>

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
class IAlphaNodeTest;
NAMESPACE_RETE_END

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class ICondition;
class IActivationVisitor;
class IAlphaNetworkFactory;

class NaiveAlphaHashNetwork : public IAlphaHashNetwork
{
public:
    NaiveAlphaHashNetwork(IActivationVisitor* pVisitor, IAlphaNetworkFactory* pFactory);
    virtual ~NaiveAlphaHashNetwork();
    
    virtual bool AddAlphaNodeTestAndNetwork(IAlphaNodeTest* pAlphaNodeTest, IAlphaHashNetwork* pNextNetwork);
    virtual bool AddAlphaNodeTestAndMemory(IAlphaNodeTest* pAlphaNodeTest, IAlphaMemory* pAlphaMemory);
    virtual void AddWME(NAMESPACE_TUPLE::IWME* pIWME);
    virtual void RemoveWME(NAMESPACE_TUPLE::IWME* pIWME);
    virtual IAlphaMemory* GetCondition(ICondition* pCondition) const;
    virtual IAlphaNodeTest* AddConditionAndMemory(ICondition* pCondition, IAlphaMemory* pAlphaMem, bool addSubHashes);
    virtual bool PruneUnusedAlphaMemories();
    virtual bool HasTests();
    
protected:
    IActivationVisitor* m_pVisitor;
    IAlphaNetworkFactory* m_pFactory;
    std::unordered_map<IAlphaNodeTest*, IAlphaHashNetwork*> m_nextHashMap;
    std::list<IAlphaNodeTest*> m_nextHashTests;
    std::unordered_map<IAlphaNodeTest*, IAlphaMemory*> m_memoryMap;
    std::list<IAlphaNodeTest*> m_memoryTests;
    
private:
    // Disallow copying
    NaiveAlphaHashNetwork& operator=(const NaiveAlphaHashNetwork&);
    NaiveAlphaHashNetwork(const NaiveAlphaHashNetwork&);
};

NAMESPACE_RETE_ALG_END

#endif /* defined(__CppRete__NaiveAlphaHashNetwork__) */
