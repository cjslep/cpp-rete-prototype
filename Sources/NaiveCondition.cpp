//
//  NaiveCondition.cpp
//  CppRete
//
//  Created by Cory Slep on 11/18/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveCondition.h"
#include "NaiveAlphaNodeTest.h"
#include "IAlphaNodeTest.h"
#include "IAlphaNetworkFactory.h"
#include <algorithm>

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, long valAttrType, long valAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(false),
    m_bHasVariableAttrType(false),
    m_bHasVariableAttrValue(false),
    m_varID(""),
    m_lValID(valID),
    m_varAttrType(""),
    m_lValAttrType(valAttrType),
    m_varAttrValue(""),
    m_lValAttrValue(valAttrVal)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, long valAttrType, long valAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(true),
    m_bHasVariableAttrType(false),
    m_bHasVariableAttrValue(false),
    m_varID(varID),
    m_lValID(-1),
    m_varAttrType(""),
    m_lValAttrType(valAttrType),
    m_varAttrValue(""),
    m_lValAttrValue(valAttrVal)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, long valAttrType, std::string varAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(true),
    m_bHasVariableAttrType(false),
    m_bHasVariableAttrValue(true),
    m_varID(varID),
    m_lValID(-1),
    m_varAttrType(""),
    m_lValAttrType(valAttrType),
    m_varAttrValue(varAttrVal),
    m_lValAttrValue(-1)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, std::string varAttrType, std::string varAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(true),
    m_bHasVariableAttrType(true),
    m_bHasVariableAttrValue(true),
    m_varID(varID),
    m_lValID(-1),
    m_varAttrType(varAttrType),
    m_lValAttrType(-1),
    m_varAttrValue(varAttrVal),
    m_lValAttrValue(-1)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, std::string varAttrType, std::string varAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(false),
    m_bHasVariableAttrType(true),
    m_bHasVariableAttrValue(true),
    m_varID(""),
    m_lValID(valID),
    m_varAttrType(varAttrType),
    m_lValAttrType(-1),
    m_varAttrValue(varAttrVal),
    m_lValAttrValue(-1)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, long valAttrType, std::string varAttrVal) :
    m_pFactory(pFactory),
    m_bHasVariableID(false),
    m_bHasVariableAttrType(false),
    m_bHasVariableAttrValue(true),
    m_varID(""),
    m_lValID(valID),
    m_varAttrType(""),
    m_lValAttrType(valAttrType),
    m_varAttrValue(varAttrVal),
    m_lValAttrValue(-1)
{
    
}

NAMESPACE_RETE_ALG::NaiveCondition::~NaiveCondition()
{
    
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveCondition::GetAlphaTestNode() const
{
    std::list<long> types;
    std::unordered_map<long, long> values;
    if (!m_bHasVariableID && !m_bHasVariableAttrType && !m_bHasVariableAttrValue)
    {
        types.push_back(m_lValAttrType);
        values[m_lValAttrType] = m_lValAttrValue;
        return m_pFactory->GetNewAlphaNodeTest(m_lValID, types, values);
    }
    else if (m_bHasVariableID && !m_bHasVariableAttrType && !m_bHasVariableAttrValue)
    {
        types.push_back(m_lValAttrType);
        values[m_lValAttrType] = m_lValAttrValue;
        return m_pFactory->GetNewAlphaNodeTest(types, values);
    }
    else if (m_bHasVariableID && !m_bHasVariableAttrType && m_bHasVariableAttrValue)
    {
        types.push_back(m_lValAttrType);
        return m_pFactory->GetNewAlphaNodeTest(types);
    }
    else if (m_bHasVariableID && m_bHasVariableAttrType && m_bHasVariableAttrValue)
    {
        return m_pFactory->GetNewAlphaNodeTest();
    }
    else if (!m_bHasVariableID && m_bHasVariableAttrType && m_bHasVariableAttrValue)
    {
        return m_pFactory->GetNewAlphaNodeTest(m_lValID);
    }
    else if (!m_bHasVariableID && !m_bHasVariableAttrType && m_bHasVariableAttrValue)
    {
        types.push_back(m_lValAttrType);
        return m_pFactory->GetNewAlphaNodeTest(m_lValID, types);
    }
    else
    {
        return NULL;
    }
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveCondition::GetAlphaTestAttributeTypeNode() const
{
    if (!m_bHasVariableAttrType)
    {
        std::list<long> types;
        types.push_back(m_lValAttrType);
        return m_pFactory->GetNewAlphaNodeTest(types);
    }
    else
    {
        return NULL;
    }
}

void NAMESPACE_RETE_ALG::NaiveCondition::GetAllVariables(std::list<std::string>& vecVariables) const
{
    vecVariables.clear();
    if (m_bHasVariableID && vecVariables.end() == std::find(vecVariables.begin(), vecVariables.end(), m_varID))
    {
        vecVariables.push_back(m_varID);
    }
    if (m_bHasVariableAttrType && vecVariables.end() == std::find(vecVariables.begin(), vecVariables.end(), m_varAttrType))
    {
        vecVariables.push_back(m_varAttrType);
    }
    if (m_bHasVariableAttrValue && vecVariables.end() == std::find(vecVariables.begin(), vecVariables.end(), m_varAttrValue))
    {
        vecVariables.push_back(m_varAttrValue);
    }
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasVariableIdentifierOf(const std::string& varName) const
{
    return m_bHasVariableID && 0 == varName.compare(m_varID);
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasVariableIdentifier() const
{
    return m_bHasVariableID;
}

long NAMESPACE_RETE_ALG::NaiveCondition::GetConstantIdentifierValue() const
{
    return m_lValID;
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasAtLeastOneConstantAttributeType() const
{
    return !m_bHasVariableAttrType;
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasConstantAttributeType(long attrType) const
{
    return !m_bHasVariableAttrType && m_lValAttrType == attrType;
}

void NAMESPACE_RETE_ALG::NaiveCondition::GetAllConstantAttrTypes(std::list<long>& vecAttrTypeIDs) const
{
    vecAttrTypeIDs.clear();
    if (!m_bHasVariableAttrType)
    {
        vecAttrTypeIDs.push_back(m_lValAttrType);
    }
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasAtLeastOneConstantAttributeValue() const
{
    return !m_bHasVariableAttrValue && !m_bHasVariableAttrType;
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasConstantAttributeValue(long attrType) const
{
    return !m_bHasVariableAttrValue && !m_bHasVariableAttrType && m_lValAttrValue == attrType;
}

void NAMESPACE_RETE_ALG::NaiveCondition::GetAllConstantAttrValues(std::list<long>& vecAttrTypeIDs, std::unordered_map<long, long>& mapAttrValuesForTypes) const
{
    vecAttrTypeIDs.clear();
    mapAttrValuesForTypes.clear();
    if (!m_bHasVariableAttrValue && !m_bHasVariableAttrType)
    {
        vecAttrTypeIDs.push_back(m_lValAttrType);
        mapAttrValuesForTypes[m_lValAttrType] = m_lValAttrValue;
    }
}

bool NAMESPACE_RETE_ALG::NaiveCondition::HasAttributeTypeWithVariableName(const std::string& varName) const
{
    return (m_bHasVariableAttrType && 0 == varName.compare(m_varAttrType)) ||
        (m_bHasVariableAttrValue && 0 == varName.compare(m_varAttrValue));
}

long NAMESPACE_RETE_ALG::NaiveCondition::GetAttributeIndexWithVariableName(const std::string& varName) const
{
    return m_bHasVariableAttrType && 0 == varName.compare(m_varAttrType) ? 0 : -1;
}

long NAMESPACE_RETE_ALG::NaiveCondition::GetValueIndexWithVariableName(const std::string& varName) const
{
    return m_bHasVariableAttrValue && 0 == varName.compare(m_varAttrValue) ? 1 : -1;
}

long NAMESPACE_RETE_ALG::NaiveCondition::GetNumAttributes() const
{
    return 1;
}

bool NAMESPACE_RETE_ALG::NaiveCondition::Equals(const ICondition& rhs) const
{
    if (HasVariableIdentifier() ^ rhs.HasVariableIdentifier())
    {
        return false;
    }
    else if (HasVariableIdentifier() && !rhs.HasVariableIdentifierOf(m_varID))
    {
        return false;
    }
    else if (!HasVariableIdentifier() && rhs.GetConstantIdentifierValue() != m_lValID)
    {
        return false;
    }
    
    if (GetNumAttributes() ^ rhs.GetNumAttributes())
    {
        return false;
    }
    
    std::list<long> tempList;
    std::unordered_map<long, long> tempMap;
    if (HasConstantAttributeType(0) ^ HasConstantAttributeType(0))
    {
        return false;
    }
    else if (!HasConstantAttributeType(0) && !rhs.HasAttributeTypeWithVariableName(m_varAttrType))
    {
        return false;
    }
    else if (HasConstantAttributeType(0))
    {
        rhs.GetAllConstantAttrTypes(tempList);
        if (tempList.front() != m_lValAttrType)
        {
            return false;
        }
        tempList.clear();
    }
    
    if (HasConstantAttributeValue(0) ^ HasConstantAttributeValue(0))
    {
        return false;
    }
    else if (!HasConstantAttributeValue(0) && -1 == rhs.GetValueIndexWithVariableName(m_varAttrValue))
    {
        return false;
    }
    else if (HasConstantAttributeValue(0))
    {
        rhs.GetAllConstantAttrValues(tempList, tempMap);
        if (tempMap[tempList.front()] != m_lValAttrValue)
        {
            return false;
        }
    }
    
    return true;
}