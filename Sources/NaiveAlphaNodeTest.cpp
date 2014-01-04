//
//  NaiveAlphaNodeTest.cpp
//  CppRete
//
//  Created by Cory Slep on 11/10/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveAlphaNodeTest.h"
#include "ICondition.h"
#include "IWME.h"
#include <algorithm>

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest() :
    m_HasIDValue(false),
    m_HasAttributeTypes(false),
    m_HasAttributeValues(false),
    m_idValue(-1),
    m_attributeTypes(),
    m_attributeValueFromType()
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest(long idValue) :
    m_HasIDValue(true),
    m_HasAttributeTypes(false),
    m_HasAttributeValues(false),
    m_idValue(idValue),
    m_attributeTypes(),
    m_attributeValueFromType()
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest(long idValue, const std::list<long>& attrTypes) :
    m_HasIDValue(true),
    m_HasAttributeTypes(true),
    m_HasAttributeValues(false),
    m_idValue(idValue),
    m_attributeTypes(attrTypes),
    m_attributeValueFromType()
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest(long idValue, const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues) :
    m_HasIDValue(true),
    m_HasAttributeTypes(true),
    m_HasAttributeValues(true),
    m_idValue(idValue),
    m_attributeTypes(attrTypes),
    m_attributeValueFromType(attrValues)
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest(const std::list<long>& attrTypes) :
    m_HasIDValue(false),
    m_HasAttributeTypes(true),
    m_HasAttributeValues(false),
    m_idValue(-1),
    m_attributeTypes(attrTypes),
    m_attributeValueFromType()
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::NaiveAlphaNodeTest(const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues) :
    m_HasIDValue(false),
    m_HasAttributeTypes(true),
    m_HasAttributeValues(true),
    m_idValue(-1),
    m_attributeTypes(attrTypes),
    m_attributeValueFromType(attrValues)
{
    
}

NAMESPACE_RETE::NaiveAlphaNodeTest::~NaiveAlphaNodeTest()
{
    
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::Test(const NAMESPACE_TUPLE::IWME& aWME) const
{
    if (HasIDValue() && aWME.GetIdentifier() != GetIdValue())
    {
        return false;
    }
    if (HasAttrTypes())
    {
        if (aWME.GetNumAttributes() != m_attributeTypes.size())
        {
            return false;
        }
        
        for (int i = 0; i < aWME.GetNumAttributes(); ++i)
        {
            if (m_attributeTypes.end() == std::find(m_attributeTypes.begin(), m_attributeTypes.end(), aWME.GetAttribute(i)))
            {
                return false;
            }
        }
    }
    if (HasAttrValues())
    {
        for (int i = 0; i < aWME.GetNumAttributes(); ++i)
        {
            std::unordered_map<long, long>::const_iterator iterVal = m_attributeValueFromType.find(aWME.GetAttribute(i));
            if (m_attributeValueFromType.end() == iterVal || aWME.GetValue(i) != iterVal->second)
            {
                return false;
            }
        }
    }
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasEquivalentConditions(const NAMESPACE_RETE_ALG::ICondition& otherCond) const
{
    bool hasDifferentIds = m_HasIDValue ^ !otherCond.HasVariableIdentifier();
    bool hasDifferentAttributeTypes = m_HasAttributeTypes ^ otherCond.HasAtLeastOneConstantAttributeType();
    bool hasDifferentAttributeValues = m_HasAttributeValues ^ otherCond.HasAtLeastOneConstantAttributeValue();
    
    if (hasDifferentIds || hasDifferentAttributeTypes || hasDifferentAttributeValues)
    {
        return false;
    }
    
    if (m_HasIDValue)
    {
        if (m_idValue != otherCond.GetConstantIdentifierValue())
        {
            return false;
        }
    }
    
    if (m_HasAttributeTypes && !m_HasAttributeValues)
    {
        std::list<long> otherAttTypes;
        otherCond.GetAllConstantAttrTypes(otherAttTypes);
        if (m_attributeTypes.size() != otherAttTypes.size())
        {
            return false;
        }
        
        std::list<long>::const_iterator iterMyAttTypes;
        std::list<long>::const_iterator iterOtherAttTypes;
        for (iterMyAttTypes = m_attributeTypes.begin(), iterOtherAttTypes = otherAttTypes.begin();
             m_attributeTypes.end() != iterMyAttTypes && otherAttTypes.end() != iterOtherAttTypes;
             ++iterMyAttTypes, ++iterOtherAttTypes)
        {
            if (*iterMyAttTypes != *iterOtherAttTypes)
            {
                return false;
            }
        }
    }
    
    if (m_HasAttributeValues)
    {
        std::list<long> otherAttTypes;
        std::unordered_map<long, long> otherAttVals;
        otherCond.GetAllConstantAttrValues(otherAttTypes, otherAttVals);
        if (m_attributeTypes.size() != otherAttTypes.size() ||
            m_attributeValueFromType.size() != otherAttVals.size())
        {
            return false;
        }
        
        for (std::list<long>::const_iterator iterMyAttTypes = m_attributeTypes.begin(),
             iterOtherAttTypes = otherAttTypes.begin();
             m_attributeTypes.end() != iterMyAttTypes && otherAttTypes.end() != iterOtherAttTypes;
             ++iterMyAttTypes,
             ++iterOtherAttTypes)
        {
            if (*iterMyAttTypes != *iterOtherAttTypes ||
                m_attributeValueFromType.at(*iterMyAttTypes) != otherAttVals.at(*iterOtherAttTypes))
            {
                return false;
            }
        }
    }
    
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasSameAttributeTypeTest(const NAMESPACE_RETE_ALG::ICondition& otherCond) const
{
    if (m_HasAttributeTypes && !m_HasAttributeValues)
    {
        std::list<long> otherAttTypes;
        otherCond.GetAllConstantAttrTypes(otherAttTypes);
        if (m_attributeTypes.size() != otherAttTypes.size())
        {
            return false;
        }
        
        for (std::list<long>::const_iterator iterMyAttTypes = m_attributeTypes.begin(),
             iterOtherAttTypes = otherAttTypes.begin();
             m_attributeTypes.end() != iterMyAttTypes && otherAttTypes.end() != iterOtherAttTypes;
             ++iterMyAttTypes,
             ++iterOtherAttTypes)
        {
            if (*iterMyAttTypes != *iterOtherAttTypes)
            {
                return false;
            }
        }
    }
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasIDValue() const
{
    return m_HasIDValue;
}

long NAMESPACE_RETE::NaiveAlphaNodeTest::GetIdValue() const
{
    return m_idValue;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasAttrTypes() const
{
    return m_HasAttributeTypes;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasExactlyAttrTypes(const std::list<long>& vecAttrs) const
{
    if (!HasAttrTypes() || vecAttrs.size() != m_attributeTypes.size())
    {
        return false;
    }
    for (std::list<long>::const_iterator iterAttrs = vecAttrs.begin();
         vecAttrs.end() != iterAttrs;
         ++iterAttrs)
    {
        if (m_attributeTypes.end() == std::find(m_attributeTypes.begin(), m_attributeTypes.end(), *iterAttrs))
        {
            return false;
        }
    }
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasAttrValues() const
{
    return m_HasAttributeValues;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::HasExactlyAttrValues(const std::list<long>& vecAttrs, const std::unordered_map<long, long>& attributeValueFromType) const
{
    if (!HasAttrValues())
    {
        return false;
    }
    if (!HasExactlyAttrTypes(vecAttrs))
    {
        return false;
    }
    for (std::list<long>::const_iterator iterAttrs = vecAttrs.begin();
         vecAttrs.end() != iterAttrs;
         ++iterAttrs)
    {
        if (attributeValueFromType.at(*iterAttrs) != m_attributeValueFromType.at(*iterAttrs))
        {
            return false;
        }
    }
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::Equals(const IAlphaNodeTest& rhs) const
{
    if ((HasIDValue() != rhs.HasIDValue() || HasAttrTypes() != rhs.HasAttrTypes() || HasAttrValues() != rhs.HasAttrValues()) ||
        (HasIDValue() && GetIdValue() != rhs.GetIdValue()) ||
        (HasAttrTypes() && !HasAttrValues() && !rhs.HasExactlyAttrTypes(m_attributeTypes)) ||
        (HasAttrTypes() && HasAttrValues() && !rhs.HasExactlyAttrValues(m_attributeTypes, m_attributeValueFromType)))
    {
        return false;
    }
    return true;
}

bool NAMESPACE_RETE::NaiveAlphaNodeTest::IsUnconditionallyAccepting() const
{
    return !m_HasIDValue && !m_HasAttributeTypes && !m_HasAttributeValues;
}