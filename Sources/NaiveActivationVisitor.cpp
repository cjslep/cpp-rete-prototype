//
//  NaiveActivationVisitor.cpp
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveActivationVisitor.h"
#include "ITokenFactory.h"
#include "IAlphaMemory.h"
#include "IToken.h"
#include "IJoinNode.h"
#include "IJoinNodeTest.h"
#include "IBetaMemory.h"
#include "IWME.h"
#include "IProductionNode.h"

NAMESPACE_RETE_ALG::NaiveActivationVisitor::NaiveActivationVisitor(const NAMESPACE_TUPLE_OVRHD::ITokenFactory* factory) :
    m_pFactory(factory),
    m_pWme(NULL),
    m_pToken(NULL)
{
    
}

NAMESPACE_RETE_ALG::NaiveActivationVisitor::~NaiveActivationVisitor()
{
    
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::BeginAlphaActivate(IAlphaMemory* alphaMemory, NAMESPACE_TUPLE::IWME* wme)
{
    m_pWme = wme;
    m_pWme->AddReteMemoryContainer(alphaMemory);
    alphaMemory->VisitBy(this, false); // Recursive for this particular WME
    m_pWme = NULL;
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::AlphaActivate(std::list<IJoinNode*>* listSuccessors, std::list<NAMESPACE_TUPLE::IWME*>* wmeItems)
{
    wmeItems->push_back(m_pWme);
    for (std::list<IJoinNode*>::iterator iterSuccessors = listSuccessors->begin();
         iterSuccessors != listSuccessors->end();
         ++iterSuccessors)
    {
        IJoinNode* temp = *iterSuccessors;
        temp->VisitBy(this, false); // Recursive using the WME set by BeginAlphaActivate
    }
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::LeftBetaActivate(IBetaMemory* pBetaMem, std::list<IJoinNode*>* listChildren)
{
    // Save previous token for recursive calling
    NAMESPACE_TUPLE::IToken* prevToken = m_pToken;
    
    NAMESPACE_TUPLE::IToken* newToken = m_pFactory->CreateNewTokenFromWME(*m_pWme); // Using WME set by BeginAlphaActivate to create new token
    if (NULL != prevToken)
    {
        prevToken->AddTokenChild(newToken);
    }
    // pBetaMem now owns this token
    pBetaMem->AddToTokenList(newToken);
    m_pToken = newToken; // Use the new token as the next "parent token"
    for (std::list<IJoinNode*>::iterator iterChildren = listChildren->begin();
         iterChildren != listChildren->end();
         ++iterChildren)
    {
        IJoinNode* temp = *iterChildren;
        temp->VisitBy(this, true); // Recursive using the WME set by BeginAlphaActivate
    }
    
    // Restore previous token for recursive calling
    m_pToken = prevToken;
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::LeftJoinActivate(IAlphaMemory* pAlphaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren)
{
    // Activated from beta, so look through alpha
    std::list<NAMESPACE_TUPLE::IWME*>* pList = pAlphaParent->GetWMESuccessors();
    for (std::list<NAMESPACE_TUPLE::IWME*>::iterator iterChildren = pList->begin();
         iterChildren != pList->end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IWME* pWME = *iterChildren;
        if (DoesPassJoinTests(vecTests, m_pToken, pWME)) // Using the Token set by LeftBetaActivate
        {
            NAMESPACE_TUPLE::IWME* pTemp = m_pWme;
            m_pWme = pWME;
            if (NULL != pChildMem)
            {
                pChildMem->VisitBy(this, true);
            }
            
            for (std::list<IProductionNode*>::iterator iterChildren = pVecChildren->begin();
                 iterChildren != pVecChildren->end();
                 ++iterChildren)
            {
                IProductionNode* temp = *iterChildren;
                temp->VisitBy(this, true);
            }
            m_pWme = pTemp;
        }
    }
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::RightJoinActivate(IBetaMemory* pBetaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren)
{
    // Activated from alpha, so look through beta
    std::list<NAMESPACE_TUPLE::IToken*>* pList = pBetaParent->GetTokenList();
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterChildren = pList->begin();
         iterChildren != pList->end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IToken* pToken = *iterChildren;
        if (DoesPassJoinTests(vecTests, pToken, m_pWme)) // Using the WME set by BeginAlphaActivate
        {
            m_pToken = pToken;
            
            if (NULL != pChildMem)
            {
                pChildMem->VisitBy(this, true);
            }
            
            for (std::list<IProductionNode*>::iterator iterChildren = pVecChildren->begin();
                 iterChildren != pVecChildren->end();
                 ++iterChildren)
            {
                IProductionNode* temp = *iterChildren;
                temp->VisitBy(this, true);
            }
            
            m_pToken = NULL;
        }
    }
    
    // Special case: If no join tests and beta's parent is null, assume beta is a "dummy node" and pass through
    if (0 == vecTests.size() && NULL == pBetaParent->GetParent())
    {
        if (NULL != pChildMem)
        {
            pChildMem->VisitBy(this, true);
        }
        
        for (std::list<IProductionNode*>::iterator iterChildren = pVecChildren->begin();
             iterChildren != pVecChildren->end();
             ++iterChildren)
        {
            IProductionNode* temp = *iterChildren;
            temp->VisitBy(this, true);
        }
    }
}


bool NAMESPACE_RETE_ALG::NaiveActivationVisitor::DoesPassJoinTests(const std::list<IJoinNodeTest*>& vecTests, NAMESPACE_TUPLE::IToken* pToken, NAMESPACE_TUPLE::IWME* pWME)
{
    for (std::list<IJoinNodeTest*>::const_iterator iterTests = vecTests.begin();
         iterTests != vecTests.end();
         ++iterTests)
    {
        const IJoinNodeTest* temp = *iterTests;
        if (!temp->Test(*pToken, *pWME)) {
            return false;
        }
    }
    return true;
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::LeftBetaActivateForProduction(IBetaMemory* pParent, IProductionNode* pChildProd)
{
    std::list<NAMESPACE_TUPLE::IToken*>* tokenList = pParent->GetTokenList();
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterTokens = tokenList->begin();
         tokenList->end() != iterTokens;
         ++iterTokens)
    {
        pChildProd->VisitBy(this, *iterTokens);
    }
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::LeftBetaActivateForNewInsertion(IJoinNode* pBetaParent)
{
    IBetaMemory* pTempMem = pBetaParent->GetChildMemory();
    pBetaParent->SetChildMemory(NULL);
    std::list<IProductionNode*>* pTempList = pBetaParent->GetChildProductions();
    pBetaParent->ClearProductions();
    IAlphaMemory* pAlpha = pBetaParent->GetAlphaParent();
    std::list<NAMESPACE_TUPLE::IWME *>* wmeList = pAlpha->GetWMESuccessors();
    for (std::list<NAMESPACE_TUPLE::IWME *>::iterator iterWME = wmeList->begin();
         wmeList->end() != iterWME;
         ++iterWME)
    {
        this->RightJoinActivateForProduction(pBetaParent, *iterWME);
    }
    for (std::list<IProductionNode *>::iterator iterPrevChildren = pTempList->begin();
         pTempList->end() != iterPrevChildren;
         ++iterPrevChildren)
    {
        pBetaParent->AddProduction(*iterPrevChildren);
    }
    pBetaParent->SetChildMemory(pTempMem);
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::RightJoinActivateForProduction(IJoinNode* pJoinNode, NAMESPACE_TUPLE::IWME* pWME)
{
    IBetaMemory* pBetaParent = pJoinNode->GetBetaParent();
    std::list<NAMESPACE_TUPLE::IToken*>* pList = pBetaParent->GetTokenList();
    IBetaMemory* pBetaChild = pJoinNode->GetChildMemory();
    std::list<IJoinNodeTest*>* pTestList = pJoinNode->GetJoinTests();
    std::list<IProductionNode*>* pListProductions = pJoinNode->GetChildProductions();
    for (std::list<NAMESPACE_TUPLE::IToken*>::iterator iterChildren = pList->begin();
         iterChildren != pList->end();
         ++iterChildren)
    {
        NAMESPACE_TUPLE::IToken* pToken = *iterChildren;
        if (DoesPassJoinTests(*pTestList, pToken, pWME))
        {
            m_pToken = pToken;
            this->SetWME(pWME);
            
            if (NULL != pBetaChild)
            {
                pBetaChild->VisitBy(this, true);
            }
            
            for (std::list<IProductionNode*>::iterator iterProdNode = pListProductions->begin();
                 pListProductions->end() != iterProdNode;
                 ++iterProdNode) {
                IProductionNode* pProd = *iterProdNode;
                pProd->VisitBy(this, false);
            }
            
            this->SetWME(NULL);
            m_pToken = NULL;
        }
    }
    
    // Special case: If no join tests and beta's parent is null, assume beta is a "dummy node" and pass through
    if (0 == pTestList->size() && NULL == pBetaParent->GetParent())
    {
        this->SetWME(pWME);
        if (NULL != pBetaChild)
        {
            pBetaChild->VisitBy(this, true);
        }
        
        for (std::list<IProductionNode*>::iterator iterChildren = pListProductions->begin();
             iterChildren != pListProductions->end();
             ++iterChildren)
        {
            IProductionNode* temp = *iterChildren;
            temp->VisitBy(this, true);
        }
        this->SetWME(NULL);
    }
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::SetWME(NAMESPACE_TUPLE::IWME* pWME)
{
    m_pWme = pWME;
}

void NAMESPACE_RETE_ALG::NaiveActivationVisitor::ProductionActivated(IProductionNode* pProduction)
{
    NAMESPACE_TUPLE::IToken* newToken = m_pFactory->CreateNewTokenFromWME(*m_pWme); // Using WME set by BeginAlphaActivate to create new token
    if (NULL != m_pToken)
    {
        m_pToken->AddTokenChild(newToken);
    }
    pProduction->AddToTokenList(newToken);
}
