//
//  NaiveAlphaHashNetwork.cpp
//  CppRete
//
//  Created by Cory Slep on 11/3/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveAlphaHashNetwork.h"
#include "IAlphaNetworkFactory.h"
#include "IActivationVisitor.h"
#include "IAlphaNodeTest.h"
#include "ICondition.h"
#include "IAlphaMemory.h"
#include "NaiveAlphaNodeTest.h"
#include "IWME.h"

NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::NaiveAlphaHashNetwork(IActivationVisitor* pVisitor, IAlphaNetworkFactory* pFactory) :
    m_pVisitor(pVisitor),
    m_pFactory(pFactory)
{
    
}

NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::~NaiveAlphaHashNetwork()
{
    for (std::list<NAMESPACE_RETE::IAlphaNodeTest*>::iterator iterMemTests = m_memoryTests.begin();
         m_memoryTests.end() != iterMemTests;
         ++iterMemTests)
    {
        NAMESPACE_RETE::IAlphaNodeTest* pTemp = *iterMemTests;
        NAMESPACE_RETE::IAlphaMemory* pTempMemory = m_memoryMap.at(pTemp);
        delete pTempMemory;
        pTempMemory = NULL;
        delete pTemp;
        pTemp = NULL;
    }
    m_memoryTests.clear();
    m_memoryMap.clear();
    for (std::list<NAMESPACE_RETE::IAlphaNodeTest*>::iterator iterNextTests = m_nextHashTests.begin();
         m_nextHashTests.end() != iterNextTests;
         ++iterNextTests)
    {
        NAMESPACE_RETE::IAlphaNodeTest* pTemp = *iterNextTests;
        NAMESPACE_RETE_ALG::IAlphaHashNetwork* pTempNetwork = m_nextHashMap.at(pTemp);
        delete pTempNetwork;
        pTempNetwork = NULL;
        delete pTemp;
        pTemp = NULL;
    }
    m_nextHashTests.clear();
    m_nextHashMap.clear();
    
}

bool NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::AddAlphaNodeTestAndNetwork(IAlphaNodeTest* pAlphaNodeTest, IAlphaHashNetwork* pNextNetwork)
{
    IAlphaHashNetwork* pNext = m_nextHashMap[pAlphaNodeTest];
    if (NULL != pNext)
    {
        return false;
    }
    m_nextHashMap[pAlphaNodeTest] = pNextNetwork;
    m_nextHashTests.push_back(pAlphaNodeTest);
    return true;
}

bool NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::AddAlphaNodeTestAndMemory(IAlphaNodeTest* pAlphaNodeTest, IAlphaMemory* pAlphaMemory)
{
    IAlphaMemory* pNext = m_memoryMap[pAlphaNodeTest];
    if (NULL != pNext)
    {
        return false;
    }
    m_memoryMap[pAlphaNodeTest] = pAlphaMemory;
    m_memoryTests.push_back(pAlphaNodeTest);
    return true;
}

NAMESPACE_RETE::IAlphaMemory* NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::GetCondition(ICondition* pCondition) const
{
    for (std::list<IAlphaNodeTest*>::const_iterator iterMemTests = m_memoryTests.begin();
         m_memoryTests.end() != iterMemTests;
         ++iterMemTests)
    {
        IAlphaNodeTest* pTempTest = *iterMemTests;
        if ((NULL != pCondition && pTempTest->HasEquivalentConditions(*pCondition)) ||
            (NULL == pCondition && pTempTest->IsUnconditionallyAccepting()))
        {
            return m_memoryMap.at(*iterMemTests);
        }
    }
    
    if (0 < m_nextHashTests.size())
    {
        for (std::list<IAlphaNodeTest*>::const_iterator iterMemTests = m_nextHashTests.begin();
             m_nextHashTests.end() != iterMemTests;
             ++iterMemTests)
        {
            IAlphaNodeTest* pTest = *iterMemTests;
            if ((NULL != pCondition && pTest->HasEquivalentConditions(*pCondition)) ||
                (NULL == pCondition && pTest->IsUnconditionallyAccepting()))
            {
                IAlphaMemory* pMemory = m_nextHashMap.at(pTest)->GetCondition(pCondition);
                if (NULL != pMemory)
                {
                    return pMemory;
                }
            }
        }
    }
    return NULL;
}

void NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::AddWME(NAMESPACE_TUPLE::IWME* pIWME)
{
    for (std::list<IAlphaNodeTest*>::const_iterator iterMems = m_memoryTests.begin();
         iterMems != m_memoryTests.end();
         ++iterMems)
    {
        IAlphaNodeTest* pTempTest = *iterMems;
        if (pTempTest->Test(*pIWME))
        {
            m_pVisitor->BeginAlphaActivate(m_memoryMap[pTempTest], pIWME);
        }
    }
    
    for (std::list<IAlphaNodeTest*>::const_iterator iterMems = m_nextHashTests.begin();
         iterMems != m_nextHashTests.end();
         ++iterMems)
    {
        IAlphaNodeTest* pTempTest = *iterMems;
        if (pTempTest->Test(*pIWME))
        {
            m_nextHashMap[pTempTest]->AddWME(pIWME);
        }
    }
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::AddConditionAndMemory(ICondition* pCondition, IAlphaMemory* pAlphaMem, bool addSubHashes)
{
    if (NULL == pCondition)
    {
        IAlphaNodeTest* pAlphaTest = m_pFactory->GetNewAlphaNodeTest();
        AddAlphaNodeTestAndMemory(pAlphaTest, pAlphaMem);
        return pAlphaTest;
    }
    
    for (std::list<IAlphaNodeTest*>::const_iterator iterMems = m_nextHashTests.begin();
         iterMems != m_nextHashTests.end();
         ++iterMems)
    {
        IAlphaNodeTest* pTempTest = *iterMems;
        if (pTempTest->HasSameAttributeTypeTest(*pCondition))
        {
            return m_nextHashMap[pTempTest]->AddConditionAndMemory(pCondition, pAlphaMem, false);
        }
    }
    // TODO: Not safe for multiple tuples more than three
    if (pCondition->HasAtLeastOneConstantAttributeType() && addSubHashes)
    {
        IAlphaNodeTest* pNewTest = pCondition->GetAlphaTestAttributeTypeNode();
        if (m_nextHashMap.end() == m_nextHashMap.find(pNewTest))
        {
            AddAlphaNodeTestAndNetwork(pNewTest, m_pFactory->GetNewAlphaHashNetwork(m_pVisitor));
        }
        else
        {
            delete pNewTest;
            pNewTest = NULL;
        }
        return m_nextHashMap[pNewTest]->AddConditionAndMemory(pCondition, pAlphaMem, false);
    }
    else
    {
        // Add it here
        IAlphaNodeTest* pNewTest = pCondition->GetAlphaTestNode();
        AddAlphaNodeTestAndMemory(pNewTest, pAlphaMem);
        return pNewTest;
    }
}

bool NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::PruneUnusedAlphaMemories()
{
    bool deletedSome = false;
    for (std::list<IAlphaNodeTest*>::iterator iterMems = m_memoryTests.begin();
         iterMems != m_memoryTests.end();
         /* Update depends on whether things were erased, below */)
    {
        IAlphaNodeTest* pAlphaTest = *iterMems;
        IAlphaMemory* pAlphaMemory = m_memoryMap.at(pAlphaTest);
        if (0 == pAlphaMemory->GetChildrenList()->size())
        {
            delete pAlphaMemory;
            pAlphaMemory = NULL;
            m_memoryMap.erase(pAlphaTest);
            
            delete pAlphaTest;
            pAlphaTest = NULL;
            iterMems = m_memoryTests.erase(iterMems);
            
            deletedSome = true;
        }
        else
        {
            ++iterMems;
        }
    }
    
    for (std::list<IAlphaNodeTest*>::const_iterator iterMems = m_nextHashTests.begin();
         iterMems != m_nextHashTests.end();
         /* Update depends on whether things were erased, below */)
    {
        IAlphaNodeTest* pAlphaTest = *iterMems;
        IAlphaHashNetwork* pNetwork = m_nextHashMap.at(pAlphaTest);
        deletedSome |= pNetwork->PruneUnusedAlphaMemories();
        if (!pNetwork->HasTests())
        {
            delete pNetwork;
            pNetwork = NULL;
            m_memoryMap.erase(pAlphaTest);
            
            delete pAlphaTest;
            pAlphaTest = NULL;
            iterMems = m_nextHashTests.erase(iterMems);
            
            deletedSome = true;
        }
        else
        {
            ++iterMems;
        }
    }
    
    return deletedSome;
}

bool NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::HasTests()
{
    return m_memoryTests.size() > 0 || m_nextHashTests.size() > 0;
}

void NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork::RemoveWME(NAMESPACE_TUPLE::IWME* pIWME)
{
    for (std::list<IAlphaNodeTest*>::iterator iterMems = m_memoryTests.begin();
         iterMems != m_memoryTests.end();
         ++iterMems)
    {
        NAMESPACE_TUPLE::IWME* pTemp = m_memoryMap.at(*iterMems)->RemoveWMESuccessor(pIWME);
        if (pTemp != pIWME)
        {
            delete pTemp;
            pTemp = NULL;
        }
    }
    
    for (std::list<IAlphaNodeTest*>::const_iterator iterMems = m_nextHashTests.begin();
         iterMems != m_nextHashTests.end();
         ++iterMems)
    {
        m_nextHashMap.at(*iterMems)->RemoveWME(pIWME);
    }
}