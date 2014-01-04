//
//  NaiveJoinNode.cpp
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveJoinNode.h"
#include "IJoinNodeTest.h"
#include "IActivationVisitor.h"
#include "IBetaMemory.h"
#include "IAlphaMemory.h"
#include "IProductionNode.h"

NAMESPACE_RETE::NaiveJoinNode::NaiveJoinNode(IAlphaMemory* parentAlpha, IBetaMemory* parentBeta) :
    m_pParentBeta(parentBeta),
    m_pParentAlpha(parentAlpha),
    m_pChild(NULL)
{
    m_pParentAlpha->AddChild(this);
    m_pParentBeta->AddChild(this);
}

NAMESPACE_RETE::NaiveJoinNode::~NaiveJoinNode()
{
    /* Currently, Alpha Hash Networks handle deletion of Alpha memories.
    if (NULL != m_pParentAlpha)
    {
        m_pParentAlpha->RemoveChild(this);
    }*/
    if (NULL != m_pParentBeta)
    {
        m_pParentBeta->RemoveChild(this);
    }
    if (NULL != m_pChild)
    {
        m_pChild->SetParent(NULL);
    }
}


NAMESPACE_RETE::IBetaMemory* NAMESPACE_RETE::NaiveJoinNode::GetBetaParent()
{
    return m_pParentBeta;
}

NAMESPACE_RETE::IAlphaMemory* NAMESPACE_RETE::NaiveJoinNode::GetAlphaParent()
{
    return m_pParentAlpha;
}

bool NAMESPACE_RETE::NaiveJoinNode::AddJoinNodeTest(IJoinNodeTest* addTest)
{
    if (m_joinTests.end() != FindTest(addTest))
    {
        return false;
    }
    m_joinTests.push_back(addTest);
    return true;
}

bool NAMESPACE_RETE::NaiveJoinNode::RemoveJoinNodeTest(IJoinNodeTest* removeTest)
{
    std::list<NAMESPACE_RETE::IJoinNodeTest*>::iterator iterTest = FindTest(removeTest);
    if (iterTest != m_joinTests.end())
    {
        m_joinTests.erase(iterTest);
        return true;
    }
    return false;
}

void NAMESPACE_RETE::NaiveJoinNode::VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft)
{
    if (isLeft)
    {
        // Do join node left activation - activated from beta memory
        visitor->LeftJoinActivate(m_pParentAlpha, m_joinTests, m_pChild, &m_childProductions);
    }
    else
    {
        // Do join node right activation - activated from alpha memory
        visitor->RightJoinActivate(m_pParentBeta, m_joinTests, m_pChild, &m_childProductions);
    }
}

std::list<NAMESPACE_RETE::IProductionNode*>* NAMESPACE_RETE::NaiveJoinNode::GetChildProductions() const
{
    return const_cast<std::list<IProductionNode*>*>(&m_childProductions);
}

NAMESPACE_RETE::IBetaMemory* NAMESPACE_RETE::NaiveJoinNode::GetChildMemory() const
{
    return m_pChild;
}

void NAMESPACE_RETE::NaiveJoinNode::SetChildMemory(IBetaMemory* pChild)
{
    if (NULL != m_pChild)
    {
        m_pChild->SetParent(NULL);
    }
    m_pChild = pChild;
    if (NULL != m_pChild)
    {
        m_pChild->SetParent(this);
    }
}

bool NAMESPACE_RETE::NaiveJoinNode::AddProduction(IProductionNode* childProduction)
{
    if (m_childProductions.end() != FindChildProduction(childProduction))
    {
        return false;
    }
    m_childProductions.push_back(childProduction);
    childProduction->SetParent(this);
    return true;
}

bool NAMESPACE_RETE::NaiveJoinNode::RemoveProduction(IProductionNode* childProduction)
{
    std::list<NAMESPACE_RETE::IProductionNode*>::iterator iterChild = FindChildProduction(childProduction);
    if (iterChild != m_childProductions.end())
    {
        NAMESPACE_RETE::IProductionNode* temp = *iterChild;
        temp->SetParent(NULL);
        m_childProductions.erase(iterChild);
        return true;
    }
    return false;
}

std::list<NAMESPACE_RETE::IJoinNodeTest*>::iterator NAMESPACE_RETE::NaiveJoinNode::FindTest(IJoinNodeTest* test)
{
    for (std::list<IJoinNodeTest*>::iterator iterTests = m_joinTests.begin();
         iterTests != m_joinTests.end();
         ++iterTests)
    {
        IJoinNodeTest* temp = *iterTests;
        if (*test == *temp)
        {
            return iterTests;
        }
    }
    return m_joinTests.end();
}

std::list<NAMESPACE_RETE::IProductionNode*>::iterator NAMESPACE_RETE::NaiveJoinNode::FindChildProduction(IProductionNode* queryNode)
{
    for (std::list<IProductionNode*>::iterator iterProds = m_childProductions.begin();
         iterProds != m_childProductions.end();
         ++iterProds)
    {
        IProductionNode* temp = *iterProds;
        if (*temp == *queryNode)
        {
            return iterProds;
        }
    }
    return m_childProductions.end();
}

std::list<NAMESPACE_RETE::IJoinNodeTest*>* NAMESPACE_RETE::NaiveJoinNode::GetJoinTests() const
{
    return const_cast<std::list<IJoinNodeTest*>*>(&m_joinTests);
}

void NAMESPACE_RETE::NaiveJoinNode::ClearProductions()
{
    for (std::list<IProductionNode*>::iterator iterProds = m_childProductions.begin();
         iterProds != m_childProductions.end();
         ++iterProds)
    {
        NAMESPACE_RETE::IProductionNode* temp = *iterProds;
        temp->SetParent(NULL);
    }
    m_childProductions.clear();
}

bool NAMESPACE_RETE::NaiveJoinNode::HasSameJoinTests(std::list<IJoinNodeTest*>* pListJoinTests)
{
    if (m_joinTests.size() != pListJoinTests->size())
    {
        return false;
    }
    
    for (std::list<IJoinNodeTest*>::iterator iterMyTests = m_joinTests.begin(), iterOtherTests = pListJoinTests->begin();
         m_joinTests.end() != iterMyTests && pListJoinTests->end() != iterOtherTests;
         ++iterMyTests, ++iterOtherTests)
    {
        IJoinNodeTest* pMyTest = *iterMyTests;
        IJoinNodeTest* pOtherTest = *iterOtherTests;
        if (*pMyTest != *pOtherTest)
        {
            return false;
        }
    }
    return true;
}

bool NAMESPACE_RETE::NaiveJoinNode::HasChildMemory()
{
    return NULL != m_pChild || m_childProductions.size() > 0;
}