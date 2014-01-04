//
//  NaiveProductionModifier.cpp
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveProductionModifier.h"
#include "IJoinNode.h"
#include "IAlphaMemory.h"
#include "IJoinNodeTest.h"
#include "ICondition.h"
#include "IAlphaHashNetwork.h"
#include "NaiveBetaMemory.h"
#include "NaiveJoinNode.h"
#include "NaiveJoinNodeTest.h"
#include "NaiveAlphaMemory.h"
#include "IActivationVisitor.h"
#include "IProductionNode.h"
#include "IAlphaNodeTest.h"

NAMESPACE_RETE_ALG::NaiveProductionModifier::NaiveProductionModifier()
{
    
}

NAMESPACE_RETE_ALG::NaiveProductionModifier::~NaiveProductionModifier()
{
    
}

bool NAMESPACE_RETE_ALG::NaiveProductionModifier::AddProduction(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IAlphaHashNetwork* pAlphaNetwork, std::list<ICondition*>* pListOfConditions, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs, IBetaMemory* pDummyTopBeta)
{
    if (NULL == pDummyTopBeta)
    {
        return false;
    }
    IBetaMemory* pCurrentBetaMem = pDummyTopBeta;
    // Most recent tests first (add to front!)
    std::list<ICondition*> pPreviousConditions;
    std::list<ICondition*>::iterator iterTests = pListOfConditions->begin();
    std::list<NAMESPACE_RETE::IJoinNodeTest*>* pJoinTestList = ConstructJoinNodeTestsList(*iterTests, &pPreviousConditions);
    IAlphaMemory* pAlphaMem = ConstructOrShareAlphaMemory(pVisitor, pAlphaNetwork, *iterTests, pAllWMEs);
    IJoinNode* pCurrentJoinNode = ConstructOrShareJoinNode(pCurrentBetaMem, pAlphaMem, pJoinTestList);
    pPreviousConditions.push_front(*iterTests);
    for (++iterTests;
         pListOfConditions->end() != iterTests;
         ++iterTests)
    {
        pCurrentBetaMem = ConstructOrShareBetaMemory(pVisitor, pCurrentJoinNode);
        delete pJoinTestList;
        pJoinTestList = ConstructJoinNodeTestsList(*iterTests, &pPreviousConditions);
        pAlphaMem = ConstructOrShareAlphaMemory(pVisitor, pAlphaNetwork, *iterTests, pAllWMEs);
        pCurrentJoinNode = ConstructOrShareJoinNode(pCurrentBetaMem, pAlphaMem, pJoinTestList);
        pPreviousConditions.push_front(*iterTests);
    }
    delete pJoinTestList;
    pCurrentJoinNode->AddProduction(pProdNode);
    UpdateNewNodeWithPreviousMatches(pVisitor, pCurrentJoinNode, pProdNode);
    return true;
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::RemoveProduction(IProductionNode* pProduction, IAlphaHashNetwork* pHeadAlphaNetwork)
{
    this->DeleteNodeAndAnyUnusedAncestors(pProduction, pHeadAlphaNetwork);
}

NAMESPACE_RETE::IBetaMemory* NAMESPACE_RETE_ALG::NaiveProductionModifier::ConstructOrShareBetaMemory(IActivationVisitor* pVisitor, IJoinNode* pParent)
{
    IBetaMemory* pChildList = pParent->GetChildMemory();
    if (NULL != pChildList)
    {
        return pChildList;
    }
    IBetaMemory* pNewMem = new NaiveBetaMemory();
    //pNewMem->SetParent(pParent);
    pParent->SetChildMemory(pNewMem);
    UpdateNewNodeWithPreviousMatches(pVisitor, pParent, pNewMem);
    return pNewMem;
}

NAMESPACE_RETE::IJoinNode* NAMESPACE_RETE_ALG::NaiveProductionModifier::ConstructOrShareJoinNode(IBetaMemory* pParent, IAlphaMemory* pAlphaMem, std::list<IJoinNodeTest*>* pListJoinTests)
{
    std::list<IJoinNode *>* childList = pParent->GetChildrenList();
    for (std::list<IJoinNode *>::iterator iterChild = childList->begin();
            iterChild != childList->end();
            ++iterChild)
    {
        IJoinNode* pTempJoin = *iterChild;
        IAlphaMemory *pTempAlpha = pTempJoin->GetAlphaParent();
        if (*pTempAlpha == *pAlphaMem && pTempJoin->HasSameJoinTests(pListJoinTests))
        {
            return pTempJoin;
        }
    }
    IJoinNode* pNewJoin = new NaiveJoinNode(pAlphaMem, pParent);
    for (std::list<IJoinNodeTest*>::iterator iterTests = pListJoinTests->begin();
         pListJoinTests->end() != iterTests;
         ++iterTests)
    {
        pNewJoin->AddJoinNodeTest(*iterTests);
    }
    return pNewJoin;
}

//Most recent conditions first!
std::list<NAMESPACE_RETE::IJoinNodeTest*>* NAMESPACE_RETE_ALG::NaiveProductionModifier::ConstructJoinNodeTestsList(ICondition* pCondition, std::list<ICondition*>* pPrevConditions)
{
    std::list<IJoinNodeTest*>* pNewTestList = new std::list<IJoinNodeTest*>();
    if (NULL == pCondition)
    {
        return pNewTestList;
    }
    
    std::list<std::string> vecVars;
    pCondition->GetAllVariables(vecVars);
    for (std::list<std::string>::iterator iterVar = vecVars.begin();
         iterVar != vecVars.end();
         ++iterVar)
    {
        long relIndex = 0;
        for (std::list<ICondition*>::iterator iterPrevConds = pPrevConditions->begin();
             pPrevConditions->end() != iterPrevConds;
             ++iterPrevConds)
        {
            ICondition* pPrevCond = *iterPrevConds;
            if (pPrevCond->HasVariableIdentifierOf(*iterVar) ||
                pPrevCond->HasAttributeTypeWithVariableName(*iterVar))
            {
                long newCondField = pCondition->HasVariableIdentifierOf(*iterVar) ? -1 : -2;
                if (-1 != pCondition->GetAttributeIndexWithVariableName(*iterVar))
                {
                    newCondField = pCondition->GetAttributeIndexWithVariableName(*iterVar);
                }
                else if (-1 != pCondition->GetValueIndexWithVariableName(*iterVar))
                {
                    newCondField = pCondition->GetValueIndexWithVariableName(*iterVar);
                }
                
                long prevCondField = pPrevCond->HasVariableIdentifierOf(*iterVar) ? -1 : -2;
                if (-1 != pPrevCond->GetAttributeIndexWithVariableName(*iterVar))
                {
                    prevCondField = pPrevCond->GetAttributeIndexWithVariableName(*iterVar);
                }
                else if (-1 != pPrevCond->GetValueIndexWithVariableName(*iterVar))
                {
                    prevCondField = pPrevCond->GetValueIndexWithVariableName(*iterVar);
                }
                pNewTestList->push_back(new NaiveJoinNodeTest(prevCondField, newCondField, relIndex));
                break; // Break out of prev conditions loop
            }
            ++relIndex;
        }
    }
    return pNewTestList;
}

NAMESPACE_RETE::IAlphaMemory* NAMESPACE_RETE_ALG::NaiveProductionModifier::ConstructOrShareAlphaMemory(IActivationVisitor* pVisitor, IAlphaHashNetwork* pAlphaNetwork, ICondition* pCondition, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs)
{
    IAlphaMemory* pAlphaMem = pAlphaNetwork->GetCondition(pCondition);
    if (NULL != pAlphaMem)
    {
        return pAlphaMem;
    }
    pAlphaMem = new NaiveAlphaMemory();
    IAlphaNodeTest* pNewTest = pAlphaNetwork->AddConditionAndMemory(pCondition, pAlphaMem, true);
    for (std::list<NAMESPACE_TUPLE::IWME *>::iterator iterWME = pAllWMEs->begin();
         pAllWMEs->end() != iterWME;
         ++iterWME)
    {
        const NAMESPACE_TUPLE::IWME* pIWME = *iterWME;
        if (pNewTest->Test(*pIWME))
        {
            pVisitor->SetWME(const_cast<NAMESPACE_TUPLE::IWME*>(pIWME));
            pAlphaMem->VisitBy(pVisitor, false);
            pVisitor->SetWME(NULL);
        }
    }
    return pAlphaMem;
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IBetaMemory* pParent)
{
    pVisitor->LeftBetaActivateForProduction(pParent, pProdNode);
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IBetaMemory* pBetaNode)
{
    pVisitor->LeftBetaActivateForNewInsertion(pBetaNode->GetParent());
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IProductionNode* pNewNode)
{
    std::list<IProductionNode*> tempList = *(pParent->GetChildProductions());
    pParent->ClearProductions();
    pParent->AddProduction(pNewNode);
    
    IBetaMemory* pTempBeta = pParent->GetChildMemory();
    pParent->SetChildMemory(NULL);
    
    IAlphaMemory* pAlpha = pParent->GetAlphaParent();
    std::list<NAMESPACE_TUPLE::IWME *>* wmeList = pAlpha->GetWMESuccessors();
    for (std::list<NAMESPACE_TUPLE::IWME *>::iterator iterWME = wmeList->begin();
         wmeList->end() != iterWME;
         ++iterWME)
    {
        pVisitor->RightJoinActivateForProduction(pParent, *iterWME);
    }
    
    pParent->ClearProductions();
    for (std::list<IProductionNode *>::iterator iterPrevChildren = tempList.begin();
         tempList.end() != iterPrevChildren;
         ++iterPrevChildren)
    {
        pParent->AddProduction(*iterPrevChildren);
    }
    pParent->SetChildMemory(pTempBeta);
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IBetaMemory* pNewNode)
{
    std::list<IProductionNode*> tempList = *(pParent->GetChildProductions());
    pParent->ClearProductions();
    
    IBetaMemory* pTempBeta = pParent->GetChildMemory();
    pParent->SetChildMemory(pNewNode);
    
    IAlphaMemory* pAlpha = pParent->GetAlphaParent();
    std::list<NAMESPACE_TUPLE::IWME *>* wmeList = pAlpha->GetWMESuccessors();
    for (std::list<NAMESPACE_TUPLE::IWME *>::iterator iterWME = wmeList->begin();
         wmeList->end() != iterWME;
         ++iterWME)
    {
        pVisitor->RightJoinActivateForProduction(pParent, *iterWME);
    }
    
    for (std::list<IProductionNode *>::iterator iterPrevChildren = tempList.begin();
         tempList.end() != iterPrevChildren;
         ++iterPrevChildren)
    {
        pParent->AddProduction(*iterPrevChildren);
    }
    pParent->SetChildMemory(pTempBeta);
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::DeleteNodeAndAnyUnusedAncestors(IJoinNode* pNode, IAlphaHashNetwork* pHeadHash)
{
    IAlphaMemory* pAlphaParent = pNode->GetAlphaParent();
    pAlphaParent->RemoveChild(pNode);
    pHeadHash->PruneUnusedAlphaMemories();
    
    IBetaMemory* pBetaParent = pNode->GetBetaParent();
    pBetaParent->RemoveChild(pNode);
    if (0 == pBetaParent->GetChildrenList()->size() && NULL != pBetaParent->GetParent()) // Don't delete top level dummy beta
    {
        this->DeleteNodeAndAnyUnusedAncestors(pBetaParent, pHeadHash);
    }
    delete pNode;
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::DeleteNodeAndAnyUnusedAncestors(IBetaMemory* pNode, IAlphaHashNetwork* pHeadHash)
{
    IJoinNode* pJoin = pNode->GetParent();
    pJoin->SetChildMemory(NULL);
    if (!pJoin->HasChildMemory())
    {
        this->DeleteNodeAndAnyUnusedAncestors(pJoin, pHeadHash);
    }
    delete pNode;
}

void NAMESPACE_RETE_ALG::NaiveProductionModifier::DeleteNodeAndAnyUnusedAncestors(IProductionNode* pNode, IAlphaHashNetwork* pHeadHash)
{
    IJoinNode* pJoin = pNode->GetParent();
    pJoin->RemoveProduction(pNode);
    if (!pJoin->HasChildMemory())
    {
        this->DeleteNodeAndAnyUnusedAncestors(pJoin, pHeadHash);
    }
    pNode->ClearTokenList();
}