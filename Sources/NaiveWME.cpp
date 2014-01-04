//
//  NaiveWME.cpp
//  CppRete
//
//  Created by Cory Slep on 10/28/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveWME.h"
#include "IAlphaMemory.h"
#include "ITuple.h"
#include "IToken.h"
#include "ITupleTraverser.h"
#include <algorithm>

NAMESPACE_TUPLE::NaiveWME::NaiveWME(const ITuple* pTuple) :
    m_pTuple(pTuple)
{
    
}

NAMESPACE_TUPLE::NaiveWME::~NaiveWME()
{
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterTokens = m_listParentTokens.begin();
         m_listParentTokens.end() != iterTokens;
         /* Updated when erasing */)
    {
        NAMESPACE_TUPLE::IToken* pTemp = *iterTokens;
        iterTokens = m_listParentTokens.erase(iterTokens);
        
        delete pTemp;
        pTemp = NULL;
    }
    delete m_pTuple;
}

bool NAMESPACE_TUPLE::NaiveWME::SetTuple(const ITuple* tuple)
{
    if (NULL == m_pTuple)
    {
        m_pTuple = tuple;
        return true;
    }
    return false;
}

const NAMESPACE_TUPLE::ITuple* const NAMESPACE_TUPLE::NaiveWME::GetTuple() const
{
    return m_pTuple;
}

bool NAMESPACE_TUPLE::NaiveWME::AddReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent)
{
    std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator iterLoc = FindParentMemory(parent);
    if (iterLoc != m_listParentMemories.end())
    {
        return false;
    }
    m_listParentMemories.push_back(parent);
    return true;
}

bool NAMESPACE_TUPLE::NaiveWME::RemoveReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent)
{
    std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator iterLoc = FindParentMemory(parent);
    if (iterLoc == m_listParentMemories.end())
    {
        return false;
    }
    m_listParentMemories.erase(iterLoc);
    return true;
}

bool NAMESPACE_TUPLE::NaiveWME::AddTokenContainer(IToken* parent)
{
    std::list<IToken*>::iterator iterLoc = std::find(m_listParentTokens.begin(), m_listParentTokens.end(), parent);
    if (iterLoc != m_listParentTokens.end())
    {
        return false;
    }
    m_listParentTokens.push_back(parent);
    return true;
}

bool NAMESPACE_TUPLE::NaiveWME::RemoveTokenContainer(IToken* parent)
{
    std::list<IToken*>::iterator iterLoc = std::find(m_listParentTokens.begin(), m_listParentTokens.end(), parent);
    if (iterLoc == m_listParentTokens.end())
    {
        return false;
    }
    m_listParentTokens.erase(iterLoc);
    return true;
}

bool NAMESPACE_TUPLE::NaiveWME::Equals(const IWME& rhs) const
{
    if (GetIdentifier() == rhs.GetIdentifier() && GetNumAttributes() == rhs.GetNumAttributes())
    {
        for (int myIndex = 0; myIndex < GetNumAttributes(); ++myIndex)
        {
            bool bFound = false;
            int otherIndex = 0;
            for (int otherIndex = 0; otherIndex < rhs.GetNumAttributes(); ++otherIndex)
            {
                if (GetAttribute(myIndex) == rhs.GetAttribute(otherIndex))
                {
                    bFound = true;
                    break;
                }
            }
            if (!bFound || GetValue(myIndex) != rhs.GetValue(otherIndex))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool NAMESPACE_TUPLE::NaiveWME::Equals(const ITuple& rhs) const
{
    if (GetNumAttributes() == rhs.GetNumAttributes())
    {
        for (int myIndex = 0; myIndex < GetNumAttributes(); ++myIndex)
        {
            bool bFound = false;
            int otherIndex = 0;
            for (int otherIndex = 0; otherIndex < rhs.GetNumAttributes(); ++otherIndex)
            {
                if (GetAttribute(myIndex) == rhs.GetAttribute(otherIndex))
                {
                    bFound = true;
                    break;
                }
            }
            if (!bFound || GetValue(myIndex) != rhs.GetValue(otherIndex))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator NAMESPACE_TUPLE::NaiveWME::FindParentMemory(NAMESPACE_RETE::IAlphaMemory* pMemory)
{
    std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator iterChildren = m_listParentMemories.begin();
    for (; iterChildren != m_listParentMemories.end();
         ++iterChildren)
    {
        NAMESPACE_RETE::IAlphaMemory* temp = *iterChildren;
        if (*temp == *pMemory)
        {
            break;
        }
    }
    return iterChildren;
}

void NAMESPACE_TUPLE::NaiveWME::TraversedBy(NAMESPACE_ALG::ITupleTraverser* visitor)
{
    for (std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator iterParent = m_listParentMemories.begin();
         iterParent != m_listParentMemories.end();
         ++iterParent)
    {
        NAMESPACE_RETE::IAlphaMemory* temp = *iterParent;
        temp->RemoveWMESuccessor(this);
    }
    
    for (std::list<IToken*>::iterator iterParent = m_listParentTokens.begin();
         iterParent != m_listParentTokens.end();
         iterParent = m_listParentTokens.begin())
    {
        IToken* temp = *iterParent;
        visitor->RemoveTokenAndDescendants(temp);
    }
    
    m_listParentMemories.clear();
    m_listParentTokens.clear();
}

bool NAMESPACE_TUPLE::NaiveWME::ContainsMemoryParent(NAMESPACE_RETE::IAlphaMemory* pParent)
{
    return m_listParentMemories.end() != FindParentMemory(pParent);
}

bool NAMESPACE_TUPLE::NaiveWME::ContainsTokenParent(IToken* pParent)
{
    return m_listParentTokens.end() != std::find(m_listParentTokens.begin(), m_listParentTokens.end(), pParent);
}

long NAMESPACE_TUPLE::NaiveWME::GetIdentifier() const
{
    return m_pTuple->GetIdentifier();
}

long NAMESPACE_TUPLE::NaiveWME::GetAttribute(long attrIndex) const
{
    return m_pTuple->GetAttribute(attrIndex);
}

long NAMESPACE_TUPLE::NaiveWME::GetValue(long attrIndex) const
{
    return m_pTuple->GetValue(attrIndex);
}

long NAMESPACE_TUPLE::NaiveWME::GetNumAttributes() const
{
    return m_pTuple->GetNumAttributes();
}