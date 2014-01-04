//
//  NaiveToken.cpp
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveToken.h"
#include "IWME.h"
#include "IBetaMemory.h"
#include "ITupleTraverser.h"
#include <algorithm>

NAMESPACE_TUPLE::NaiveToken::NaiveToken(IWME* pIWME) :
    m_pIWME(pIWME),
    m_pParentMemory(NULL),
    m_pParentToken(NULL)
{
    m_pIWME->AddTokenContainer(this);
}

NAMESPACE_TUPLE::NaiveToken::NaiveToken(IWME* pIWME, NAMESPACE_RETE::IBetaMemory* pParentMemory) :
    m_pIWME(pIWME),
    m_pParentMemory(pParentMemory),
    m_pParentToken(NULL)
{
    m_pIWME->AddTokenContainer(this);
}

NAMESPACE_TUPLE::NaiveToken::NaiveToken(IWME* pIWME, NAMESPACE_RETE::IBetaMemory* pParentMemory, IToken* pParentToken) :
    m_pIWME(pIWME),
    m_pParentMemory(pParentMemory),
    m_pParentToken(pParentToken)
{
    m_pIWME->AddTokenContainer(this);
}

NAMESPACE_TUPLE::NaiveToken::~NaiveToken()
{
    m_pIWME->RemoveTokenContainer(this);
    m_pIWME = NULL;
    if (NULL != m_pParentMemory)
    {
        m_pParentMemory->RemoveFromTokenList(this);
        m_pParentMemory = NULL;
    }
    if (NULL != m_pParentToken)
    {
        m_pParentToken->RemoveTokenChild(this);
        m_pParentToken = NULL;
    }
    for (std::list<IToken*>::iterator iterToken = m_listChildTokens.begin();
         m_listChildTokens.end() != iterToken;
         /* Updated below from erase */)
    {
        IToken* pToken = *iterToken;
        iterToken = m_listChildTokens.erase(iterToken);
        delete pToken;
    }
}

const NAMESPACE_TUPLE::IToken* const NAMESPACE_TUPLE::NaiveToken::GetParentToken() const
{
    return m_pParentToken;
}

bool NAMESPACE_TUPLE::NaiveToken::SetParentToken(IToken* pParent)
{
    std::list<IToken*>::iterator iterParent = std::find(m_listChildTokens.begin(), m_listChildTokens.end(), pParent);
    if (iterParent == m_listChildTokens.end())
    {
        m_pParentToken = pParent;
        return true;
    }
    return false;
}

const NAMESPACE_RETE::IBetaMemory* const NAMESPACE_TUPLE::NaiveToken::GetParentMemory() const
{
    return m_pParentMemory;
}

void NAMESPACE_TUPLE::NaiveToken::SetParentMemory(NAMESPACE_RETE::IBetaMemory* pParent)
{
    m_pParentMemory = pParent;
}

const NAMESPACE_TUPLE::IWME* const NAMESPACE_TUPLE::NaiveToken::GetWME() const
{
    return m_pIWME;
}

long NAMESPACE_TUPLE::NaiveToken::GetNumTokenChildren() const
{
    return m_listChildTokens.size();
}

bool NAMESPACE_TUPLE::NaiveToken::AddTokenChild(IToken* child)
{
    if (NULL == child || m_pParentToken == child || this == child)
    {
        return false;
    }
    std::list<IToken*>::iterator iterChild = std::find(m_listChildTokens.begin(), m_listChildTokens.end(), child);
    if (iterChild == m_listChildTokens.end())
    {
        m_listChildTokens.push_back(child);
        child->SetParentToken(this);
        return true;
    }
    return false;
}

bool NAMESPACE_TUPLE::NaiveToken::RemoveTokenChild(IToken* child)
{
    if (NULL == child)
    {
        return false;
    }
    std::list<IToken*>::iterator iterChild = std::find(m_listChildTokens.begin(), m_listChildTokens.end(), child);
    if (iterChild != m_listChildTokens.end())
    {
        m_listChildTokens.erase(iterChild);
        child->SetParentToken(NULL);
        return true;
    }
    return false;
}

bool NAMESPACE_TUPLE::NaiveToken::Equals(const IToken& rhs) const
{
    return *m_pIWME == *rhs.GetWME() && m_pParentToken == rhs.GetParentToken();
}

void NAMESPACE_TUPLE::NaiveToken::TraversedBy(NAMESPACE_ALG::ITupleTraverser* visitor)
{
    for (std::list<IToken*>::iterator iterChildren = m_listChildTokens.begin();
         iterChildren != m_listChildTokens.end();
         ++iterChildren)
    {
        IToken* temp = *iterChildren;
        visitor->RemoveTokenAndDescendants(temp);
    }
    
    m_pParentMemory->RemoveFromTokenList(this);
    m_pParentMemory = NULL;
    m_pParentToken->RemoveTokenChild(this);
    m_pParentToken = NULL;
    m_pIWME->RemoveTokenContainer(this);
    m_pIWME = NULL;
}