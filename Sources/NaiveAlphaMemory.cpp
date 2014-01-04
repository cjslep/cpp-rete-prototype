//
//  NaiveAlphaMemory.cpp
//  CppRete
//
//  Created by Cory Slep on 10/7/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveAlphaMemory.h"
#include "IActivationVisitor.h"
#include "IJoinNode.h"
#include "IWME.h"
#include "IReteMemory.h"
#include <algorithm>

NAMESPACE_RETE::NaiveAlphaMemory::NaiveAlphaMemory()
{
    
}

NAMESPACE_RETE::NaiveAlphaMemory::~NaiveAlphaMemory()
{
    
}

std::list<NAMESPACE_TUPLE::IWME*>* NAMESPACE_RETE::NaiveAlphaMemory::GetWMESuccessors() const
{
    return const_cast<std::list<NAMESPACE_TUPLE::IWME*>*>(&m_wmeItems);
}

bool NAMESPACE_RETE::NaiveAlphaMemory::AddWMESuccessor(NAMESPACE_TUPLE::IWME* successor)
{
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterLoc = FindSuccessorIndex(successor);
    if (iterLoc != m_wmeItems.end())
    {
        return false;
    }
    m_wmeItems.push_back(successor);
    successor->AddReteMemoryContainer(this);
    return true;
}

NAMESPACE_TUPLE::IWME* NAMESPACE_RETE::NaiveAlphaMemory::RemoveWMESuccessor(NAMESPACE_TUPLE::IWME* successor)
{
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterLoc = FindSuccessorIndex(successor);
    if (iterLoc == m_wmeItems.end())
    {
        return NULL;
    }
    m_wmeItems.erase(iterLoc);
    NAMESPACE_TUPLE::IWME* pMyWME = *iterLoc;
    pMyWME->RemoveReteMemoryContainer(this);
    return pMyWME;
}

void NAMESPACE_RETE::NaiveAlphaMemory::VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft)
{
    // Alpha memories don't have a "left" nor "right" activation
    visitor->AlphaActivate(&m_listSuccessors, &m_wmeItems);
}

std::list<NAMESPACE_RETE::IJoinNode*>* NAMESPACE_RETE::NaiveAlphaMemory::GetChildrenList() const
{
    return const_cast<std::list<IJoinNode*>*>(&m_listSuccessors);
}

bool NAMESPACE_RETE::NaiveAlphaMemory::AddChild(IJoinNode* child)
{
    std::list<NAMESPACE_RETE::IJoinNode*>::iterator iterLoc = std::find(m_listSuccessors.begin(), m_listSuccessors.end(), child);
    if (iterLoc != m_listSuccessors.end())
    {
        return false;
    }
    m_listSuccessors.push_back(child);
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaMemory::RemoveChild(IJoinNode* child)
{
    std::list<NAMESPACE_RETE::IJoinNode*>::iterator iterLoc = std::find(m_listSuccessors.begin(), m_listSuccessors.end(), child);
    if (iterLoc == m_listSuccessors.end())
    {
        return false;
    }
    m_listSuccessors.erase(iterLoc);
    return true;
}

std::list<NAMESPACE_TUPLE::IWME*>::iterator NAMESPACE_RETE::NaiveAlphaMemory::FindSuccessorIndex(NAMESPACE_TUPLE::IWME* child)
{
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterChildren = m_wmeItems.begin();
    for (; iterChildren != m_wmeItems.end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IWME* temp = *iterChildren;
        if (*temp == *child)
        {
            break;
        }
    }
    return iterChildren;
}

bool NAMESPACE_RETE::NaiveAlphaMemory::Equals(const IReteMemory& rhs) const
{
    const IAlphaMemory* pAlpha = dynamic_cast<IAlphaMemory*>(const_cast<IReteMemory*>(&rhs));
    if (NULL == pAlpha)
    {
        return false;
    }
    
    std::list<IJoinNode*>* pList = pAlpha->GetChildrenList();
    std::list<NAMESPACE_TUPLE::IWME*>* pOtherWMEList = pAlpha->GetWMESuccessors();
    if (NULL != pList ^ m_listSuccessors.size() == 0 || NULL != pOtherWMEList ^ m_wmeItems.size() == 0 ||
        pList->size() != m_listSuccessors.size() || pOtherWMEList->size() != m_wmeItems.size())
    {
        return false;
    }
    
    if (NULL != pList)
    {
        
        std::list<IJoinNode*>::const_iterator iterChildren = m_listSuccessors.begin();
        std::list<IJoinNode*>::const_iterator iterOtherChildren = pList->begin();
        for (;
             iterOtherChildren != pList->end() && iterChildren != m_listSuccessors.end();
             ++iterOtherChildren, ++iterChildren)
        {
            if (*iterOtherChildren != *iterChildren)
            {
                return false;
            }
        }
    }
    
    if (NULL != pOtherWMEList)
    {
        std::list<NAMESPACE_TUPLE::IWME*>::const_iterator iterWME = m_wmeItems.begin();
        std::list<NAMESPACE_TUPLE::IWME*>::const_iterator iterOtherWME = pOtherWMEList->begin();
        for (;
             iterWME != m_wmeItems.end() && iterOtherWME != pOtherWMEList->end();
             ++iterWME, ++iterOtherWME)
        {
            if (*iterWME != *iterOtherWME)
            {
                return false;
            }
        }
    }
    return true;
    
}

bool NAMESPACE_RETE::NaiveAlphaMemory::HasParent() const
{
    return false;
}