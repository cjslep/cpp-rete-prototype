//
//  NaiveProductionNode.cpp
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveProductionNode.h"
#include "IToken.h"
#include "IWME.h"
#include "IActivationVisitor.h"
#include "IJoinNode.h"
#include "IReteMemory.h"
#include "IProductionSubscriber.h"
#include <algorithm>

NAMESPACE_RETE::NaiveProductionNode::NaiveProductionNode(long id) :
    m_pParent(NULL),
    m_lId(id)
{
    
}

NAMESPACE_RETE::NaiveProductionNode::NaiveProductionNode(long id, IJoinNode* pParent) :
    m_pParent(pParent),
    m_lId(id)
{
    
}

NAMESPACE_RETE::NaiveProductionNode::~NaiveProductionNode()
{
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterTokens = m_vecTokenList.begin();
         m_vecTokenList.end() != iterTokens;
         /* Updated while erasing */)
    {
        NAMESPACE_TUPLE::IToken* pTemp = *iterTokens;
        iterTokens = m_vecTokenList.erase(iterTokens);
        
        delete pTemp;
        pTemp = NULL;
    }
}

NAMESPACE_RETE::IJoinNode* NAMESPACE_RETE::NaiveProductionNode::GetParent() const
{
    return m_pParent;
}

void NAMESPACE_RETE::NaiveProductionNode::SetParent(IJoinNode* parent)
{
    m_pParent = parent;
}

std::list<NAMESPACE_TUPLE::IToken*>* NAMESPACE_RETE::NaiveProductionNode::GetTokenList() const
{
    return const_cast<std::list<NAMESPACE_TUPLE::IToken*>*>(&m_vecTokenList);
}

void NAMESPACE_RETE::NaiveProductionNode::ClearTokenList()
{
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterTokens = m_vecTokenList.begin();
         m_vecTokenList.end() != iterTokens;
         /* Updated while erasing */)
    {
        NAMESPACE_TUPLE::IToken* pTemp = *iterTokens;
        iterTokens = m_vecTokenList.erase(iterTokens);
        
        delete pTemp;
        pTemp = NULL;
    }
}

bool NAMESPACE_RETE::NaiveProductionNode::AddToTokenList(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterToken = std::find(m_vecTokenList.begin(), m_vecTokenList.end(), member);
    if (iterToken != m_vecTokenList.end())
    {
        return false;
    }
    m_vecTokenList.push_back(member);
    member->SetParentMemory(this);
    NotifySubscribers(member);
    return true;
}

bool NAMESPACE_RETE::NaiveProductionNode::RemoveFromTokenList(NAMESPACE_TUPLE::IToken* member)
{
    std::list<NAMESPACE_TUPLE::IToken*>::iterator iterToken = std::find(m_vecTokenList.begin(), m_vecTokenList.end(), member);
    if (iterToken == m_vecTokenList.end())
    {
        return false;
    }
    m_vecTokenList.erase(iterToken);
    member->SetParentMemory(NULL);
    return true;
}

bool NAMESPACE_RETE::NaiveProductionNode::HasParent() const
{
    return NULL != GetParent();
}

std::list<NAMESPACE_RETE::IJoinNode*>* NAMESPACE_RETE::NaiveProductionNode::GetChildrenList() const
{
    return NULL;
}

bool NAMESPACE_RETE::NaiveProductionNode::AddChild(IJoinNode* child)
{
    return false;
}

bool NAMESPACE_RETE::NaiveProductionNode::RemoveChild(IJoinNode* child)
{
    return false;
}

bool NAMESPACE_RETE::NaiveProductionNode::Equals(const NAMESPACE_RETE::IReteMemory& rhs) const
{
    const IProductionNode* pProd = dynamic_cast<IProductionNode*>(const_cast<IReteMemory*>(&rhs));
    if (NULL == pProd)
    {
        return false;
    }
    
    // TODO: Compare other distinguishing factors!
    
    return GetId() == pProd->GetId();
}

void NAMESPACE_RETE::NaiveProductionNode::VisitBy(NAMESPACE_RETE_ALG::IActivationVisitor* visitor, bool isLeft)
{
    // TODO: Possibly notify something else?
    visitor->ProductionActivated(this);
}

long NAMESPACE_RETE::NaiveProductionNode::GetId() const
{
    return m_lId;
}

bool NAMESPACE_RETE::NaiveProductionNode::AddSubscriber(IProductionSubscriber* pSubscriber)
{
    std::list<IProductionSubscriber*>::iterator iterSub = std::find(m_listSubs.begin(), m_listSubs.end(), pSubscriber);
    if (iterSub != m_listSubs.end())
    {
        return false;
    }
    m_listSubs.push_back(pSubscriber);
    return true;
}

bool NAMESPACE_RETE::NaiveProductionNode::RemoveSubscriber(IProductionSubscriber* pSubscriber)
{
    std::list<IProductionSubscriber*>::iterator iterSub = std::find(m_listSubs.begin(), m_listSubs.end(), pSubscriber);
    if (iterSub == m_listSubs.end())
    {
        return false;
    }
    m_listSubs.erase(iterSub);
    return true;
}

void NAMESPACE_RETE::NaiveProductionNode::NotifySubscribers(NAMESPACE_TUPLE::IToken* newToken)
{
    const NAMESPACE_TUPLE::IToken* pTokenCount = newToken->GetParentToken();
    long lCount = 1;
    while (NULL != pTokenCount)
    {
        ++lCount;
        pTokenCount = pTokenCount->GetParentToken();
    }
    
    // This is NOT multiple-attribute friendly
    long** tempData = new long*[lCount];
    long* numTableColsAtRow = new long[lCount];
    long index = 0;
    for (const NAMESPACE_TUPLE::IToken* pTokenIter = newToken;
         NULL != pTokenIter;
         pTokenIter = pTokenIter->GetParentToken()) {
        tempData[index] = new long[3];
        numTableColsAtRow[index] = 3;
        
        tempData[index][0] = pTokenIter->GetWME()->GetIdentifier();
        tempData[index][1] = pTokenIter->GetWME()->GetAttribute(0);
        tempData[index][2] = pTokenIter->GetWME()->GetValue(0);
        
        ++index;
    }
    for (std::list<IProductionSubscriber*>::iterator iterSub = m_listSubs.begin();
         m_listSubs.end() != iterSub;
         ++iterSub)
    {
        IProductionSubscriber* pSub = *iterSub;
        pSub->ProductionExecuted(m_lId, tempData, numTableColsAtRow, lCount);
    }
    
    index = 0;
    delete numTableColsAtRow;
    for (const NAMESPACE_TUPLE::IToken* pTokenIter = newToken;
         NULL != pTokenIter;
         pTokenIter = pTokenIter->GetParentToken()) {
        
        delete tempData[index];
        
        ++index;
    }
    delete tempData;
}