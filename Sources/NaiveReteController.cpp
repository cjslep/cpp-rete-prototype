//
//  NaiveReteController.cpp
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveReteController.h"
#include "NaiveActivationVisitor.h"
#include "NaiveAlphaHashNetwork.h"
#include "NaiveBetaMemory.h"
#include "NaiveTokenFactory.h"
#include "NaiveAlphaNetworkFactory.h"
#include "NaiveCondition.h"
#include "NaiveProductionModifier.h"
#include "NaiveProductionNode.h"
#include "NaiveWME.h"
#include "Triple.h"
#include <iostream>

NaiveReteController::NaiveReteController() :
    m_lCurrentProdID(0)
{
    m_pTokenFactory = new NAMESPACE_TUPLE_OVRHD::NaiveTokenFactory();
    m_pAlphaNetFactory = new NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory();
    m_pAlgVisitor = new NAMESPACE_RETE_ALG::NaiveActivationVisitor(m_pTokenFactory);
    m_pHeadHash = new NAMESPACE_RETE_ALG::NaiveAlphaHashNetwork(m_pAlgVisitor, m_pAlphaNetFactory);
    m_pDummyTop = new NAMESPACE_RETE::NaiveBetaMemory();
    m_pProductionModifier = new NAMESPACE_RETE_ALG::NaiveProductionModifier();
}

NaiveReteController::~NaiveReteController()
{
    delete m_pDummyTop;
    delete m_pHeadHash;
    delete m_pAlgVisitor;
    delete m_pAlphaNetFactory;
    delete m_pTokenFactory;
}

void NaiveReteController::StageNewProduction()
{
    for(std::list<NAMESPACE_RETE_ALG::ICondition*>::iterator iterConds = m_listConditions.begin();
        m_listConditions.end() != iterConds;
        /* Updated below when erasing*/)
    {
        NAMESPACE_RETE_ALG::ICondition* pTemp = *iterConds;
        iterConds = m_listConditions.erase(iterConds);
        
        delete pTemp;
        pTemp = NULL;
    }
}

bool NaiveReteController::PrepareCondition(long valID, long valAttrType, long valAttrVal)
{
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, valID, valAttrType, valAttrVal);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

bool NaiveReteController::PrepareCondition(const char* varID, long varIDLength, long valAttrType, long valAttrVal)
{
    std::string variableID(varID, varIDLength);
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, variableID, valAttrType, valAttrVal);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

bool NaiveReteController::PrepareCondition(const char* varID, long varIDLength, long valAttrType, const char* varAttrVal, long varAttrValLength)
{
    std::string variableID(varID, varIDLength);
    std::string variableValue(varAttrVal, varAttrValLength);
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, variableID, valAttrType, variableValue);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

bool NaiveReteController::PrepareCondition(const char* varID, long varIDLength, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength)
{
    std::string variableID(varID, varIDLength);
    std::string variableAttr(varAttrType, varAttrTypeLength);
    std::string variableValue(varAttrVal, varAttrValLength);
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, variableID, variableAttr, variableValue);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

bool NaiveReteController::PrepareCondition(long valID, const char* varAttrType, long varAttrTypeLength, const char* varAttrVal, long varAttrValLength)
{
    std::string variableAttr(varAttrType, varAttrTypeLength);
    std::string variableValue(varAttrVal, varAttrValLength);
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, valID, variableAttr, variableValue);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

bool NaiveReteController::PrepareCondition(long valID, long valAttrType, const char* varAttrVal, long varAttrValLength)
{
    std::string variableValue(varAttrVal, varAttrValLength);
    NAMESPACE_RETE_ALG::ICondition* pCond = new NAMESPACE_RETE_ALG::NaiveCondition(m_pAlphaNetFactory, valID, valAttrType, variableValue);
    if (m_listConditions.end() == FindConditionByValue(pCond))
    {
        m_listConditions.push_back(pCond);
        return true;
    }
    else
    {
        delete pCond;
        return false;
    }
}

long NaiveReteController::PublishProduction()
{
    NAMESPACE_RETE::NaiveProductionNode* pProductionNode = new NAMESPACE_RETE::NaiveProductionNode(m_lCurrentProdID);
    m_mapIDtoProduction[m_lCurrentProdID] = pProductionNode;
    m_pProductionModifier->AddProduction(m_pAlgVisitor, pProductionNode, m_pHeadHash, &m_listConditions, &m_listIWMEs, m_pDummyTop);
    ++m_lCurrentProdID;
    this->StageNewProduction();
    return m_lCurrentProdID - 1;
}

bool NaiveReteController::RemoveData(long valID, long valAttrType, long valAttrVal)
{
    NAMESPACE_TUPLE::IWME* pWME = new NAMESPACE_TUPLE::NaiveWME(new NAMESPACE_TUPLE::Triple(valID, valAttrType, valAttrVal));
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterWME = FindWMEByValue(pWME);
    if (m_listIWMEs.end() != iterWME)
    {
        m_pHeadHash->RemoveWME(*iterWME);
        delete pWME;
        delete *iterWME;
        m_listIWMEs.erase(iterWME);
        return true;
    }
    else
    {
        delete pWME;
        return false;
    }
}

bool NaiveReteController::RemoveData(long valID, long valAttrType)
{
    NAMESPACE_TUPLE::IWME* pWME = new NAMESPACE_TUPLE::NaiveWME(new NAMESPACE_TUPLE::Triple(valID, valAttrType, 0));
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterWME = FindWMEByIDAndAttributeType(pWME);
    bool foundDelete = false;
    while (m_listIWMEs.end() != iterWME)
    {
        m_pHeadHash->RemoveWME(*iterWME);
        delete *iterWME;
        m_listIWMEs.erase(iterWME);
        foundDelete = true;
        
        iterWME = FindWMEByIDAndAttributeType(pWME);
    }
    delete pWME;
    return foundDelete;
}

bool NaiveReteController::AddData(long valID, long valAttrType, long valAttrVal)
{
    NAMESPACE_TUPLE::IWME* pWME = new NAMESPACE_TUPLE::NaiveWME(new NAMESPACE_TUPLE::Triple(valID, valAttrType, valAttrVal));
    if (m_listIWMEs.end() == FindWMEByValue(pWME))
    {
        m_listIWMEs.push_back(pWME);
        m_pHeadHash->AddWME(pWME);
        return true;
    }
    else
    {
        delete pWME;
        return false;
    }
}

bool NaiveReteController::HasIDAttrData(long valID, long valAttrType)
{
    NAMESPACE_TUPLE::IWME* pWME = new NAMESPACE_TUPLE::NaiveWME(new NAMESPACE_TUPLE::Triple(valID, valAttrType, 0));
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterWME = FindWMEByIDAndAttributeType(pWME);
    delete pWME;
    pWME = NULL;
    return m_listIWMEs.end() != iterWME;
}

bool NaiveReteController::RemoveProduction(long productionID)
{
    std::unordered_map<long, NAMESPACE_RETE::IProductionNode*>::iterator iterProdID = m_mapIDtoProduction.find(productionID);
    if (m_mapIDtoProduction.end() != iterProdID)
    {
        m_pProductionModifier->RemoveProduction(iterProdID->second, m_pHeadHash);
        return true;
    }
    else
    {
        return false;
    }
}

std::list<NAMESPACE_RETE_ALG::ICondition*>::iterator NaiveReteController::FindConditionByValue(NAMESPACE_RETE_ALG::ICondition* member)
{
    std::list<NAMESPACE_RETE_ALG::ICondition*>::iterator iterCond = m_listConditions.begin();
    for (; iterCond != m_listConditions.end();
         ++iterCond)
    {
        NAMESPACE_RETE_ALG::ICondition* temp = *iterCond;
        if (*temp == *member)
        {
            break;
        }
    }
    return iterCond;
}

std::list<NAMESPACE_TUPLE::IWME*>::iterator NaiveReteController::FindWMEByIDAndAttributeType(NAMESPACE_TUPLE::IWME* member)
{
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterWME = m_listIWMEs.begin();
    for (; iterWME != m_listIWMEs.end();
         ++iterWME)
    {
        NAMESPACE_TUPLE::IWME* temp = *iterWME;
        if (temp->GetNumAttributes() == member->GetNumAttributes() &&
            temp->GetIdentifier() == member->GetIdentifier() &&
            temp->GetAttribute(0) == member->GetAttribute(0))
        {
            break;
        }
    }
    return iterWME;
}

std::list<NAMESPACE_TUPLE::IWME*>::iterator NaiveReteController::FindWMEByValue(NAMESPACE_TUPLE::IWME* member)
{
    std::list<NAMESPACE_TUPLE::IWME*>::iterator iterWME = m_listIWMEs.begin();
    for (; iterWME != m_listIWMEs.end();
         ++iterWME)
    {
        NAMESPACE_TUPLE::IWME* temp = *iterWME;
        if (*temp == *member)
        {
            break;
        }
    }
    return iterWME;
}

bool NaiveReteController::AddSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber)
{
    std::unordered_map<long, NAMESPACE_RETE::IProductionNode*>::iterator iter = m_mapIDtoProduction.find(productionID);
    if (m_mapIDtoProduction.end() != iter)
    {
        NAMESPACE_RETE::IProductionNode* pProdNode = iter->second;
        return pProdNode->AddSubscriber(pSubscriber);
    }
    return false;
}

bool NaiveReteController::RemoveSubscriberToProduction(long productionID, IProductionSubscriber* pSubscriber)
{
    std::unordered_map<long, NAMESPACE_RETE::IProductionNode*>::iterator iter = m_mapIDtoProduction.find(productionID);
    if (m_mapIDtoProduction.end() != iter)
    {
        NAMESPACE_RETE::IProductionNode* pProdNode = iter->second;
        return pProdNode->RemoveSubscriber(pSubscriber);
    }
    return false;
}