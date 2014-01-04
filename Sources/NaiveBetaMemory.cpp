//
//  NaiveBetaMemory.cpp
//  CppRete
//
//  Created by Cory Slep on 10/21/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveBetaMemory.h"
#include "IToken.h"
#include "IActivationVisitor.h"
#include "IJoinNode.h"
#include "IReteMemory.h"
#include <algorithm>

NAMESPACE_RETE::NaiveBetaMemory::NaiveBetaMemory() :
    m_pParent(NULL)
{
    
}

NAMESPACE_RETE::NaiveBetaMemory::~NaiveBetaMemory()
{
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterTokens = m_vecTokenList.begin();
         m_vecTokenList.end() != iterTokens;
         /* Updated when erasing */)
    {
        NAMESPACE_TUPLE::IToken* pTemp = *iterTokens;
        iterTokens = m_vecTokenList.erase(iterTokens);
        
        delete pTemp;
        pTemp = NULL;
    }
}

void NAMESPACE_RETE::NaiveBetaMemory::VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft)
{
    if (isLeft)
    {
        // Owner of tokens placed in m_vecTokenList
        visitor->LeftBetaActivate(this, &m_listChildren);
    }
    else
    {
        throw -1;
    }
}

std::list<NAMESPACE_TUPLE::IToken*>* NAMESPACE_RETE::NaiveBetaMemory::GetTokenList() const
{
    return const_cast<std::list<NAMESPACE_TUPLE::IToken*>*>(&m_vecTokenList);
}

bool NAMESPACE_RETE::NaiveBetaMemory::AddToTokenList(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterToken = FindTokenIteratorByValue(member);
    if (iterToken != m_vecTokenList.end())
    {
        return false;
    }
    m_vecTokenList.push_back(member);
    member->SetParentMemory(this);
    return true;
}

bool NAMESPACE_RETE::NaiveBetaMemory::RemoveFromTokenList(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterToken = FindTokenIteratorByPointer(member);
    if (iterToken == m_vecTokenList.end())
    {
        return false;
    }
    m_vecTokenList.erase(iterToken);
    member->SetParentMemory(NULL);
    return true;
}


NAMESPACE_RETE::IJoinNode* NAMESPACE_RETE::NaiveBetaMemory::GetParent() const
{
    return m_pParent;
}

void NAMESPACE_RETE::NaiveBetaMemory::SetParent(IJoinNode* parent)
{
    m_pParent = parent;
}

std::list<NAMESPACE_RETE::IJoinNode*>* NAMESPACE_RETE::NaiveBetaMemory::GetChildrenList() const
{
    return const_cast<std::list<NAMESPACE_RETE::IJoinNode*>*>(&m_listChildren);
}

bool NAMESPACE_RETE::NaiveBetaMemory::AddChild(IJoinNode* child)
{
    std::list<IJoinNode*>::iterator iterLoc = std::find(m_listChildren.begin(), m_listChildren.end(), child);
    if (iterLoc != m_listChildren.end())
    {
        return false;
    }
    m_listChildren.push_back(child);
    return true;
}

bool NAMESPACE_RETE::NaiveBetaMemory::RemoveChild(IJoinNode* child)
{
    std::list<IJoinNode*>::iterator iterLoc = std::find(m_listChildren.begin(), m_listChildren.end(), child);
    if (iterLoc == m_listChildren.end())
    {
        return false;
    }
    m_listChildren.erase(iterLoc);
    return true;
}

std::list<NAMESPACE_TUPLE::IToken*>::iterator NAMESPACE_RETE::NaiveBetaMemory::FindTokenIteratorByValue(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterChildren = m_vecTokenList.begin();
    for (; iterChildren != m_vecTokenList.end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IToken* temp = *iterChildren;
        if (*temp == *member)
        {
            break;
        }
    }
    return iterChildren;
}

std::list<NAMESPACE_TUPLE::IToken*>::iterator NAMESPACE_RETE::NaiveBetaMemory::FindTokenIteratorByPointer(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterChildren = m_vecTokenList.begin();
    for (; iterChildren != m_vecTokenList.end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IToken* temp = *iterChildren;
        if (temp == member)
        {
            break;
        }
    }
    return iterChildren;
}

bool NAMESPACE_RETE::NaiveBetaMemory::Equals(const IReteMemory& rhs) const
{
    const IBetaMemory* pBeta = dynamic_cast<IBetaMemory*>(const_cast<IReteMemory*>(&rhs));
    if (NULL == pBeta)
    {
        return false;
    }
    
    std::list<IJoinNode*>* pList = pBeta->GetChildrenList();
    if (pList->size() != m_listChildren.size())
    {
        return false;
    }
    std::list<IJoinNode*>::const_iterator iterChildren = m_listChildren.begin();
    std::list<IJoinNode*>::const_iterator iterOtherChildren = pList->begin();
    for (;
         iterOtherChildren != pList->end() && iterChildren != m_listChildren.end();
         ++iterOtherChildren, ++iterChildren)
    {
        if (*iterOtherChildren != *iterChildren)
        {
            return false;
        }
    }
    return NULL != m_pParent ? (rhs.HasParent() ? m_pParent == pBeta->GetParent() : false) : !rhs.HasParent();
}

bool NAMESPACE_RETE::NaiveBetaMemory::HasParent() const
{
    return NULL != GetParent();
}