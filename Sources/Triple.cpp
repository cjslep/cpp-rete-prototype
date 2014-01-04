//
//  Triple.cpp
//  CppRete
//
//  Created by Cory Slep on 9/23/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "Triple.h"

NAMESPACE_TUPLE::Triple::Triple(long tupleID) :
    m_attribute(-1), 
    m_value(-1)
{
    m_identifier = tupleID;
}

NAMESPACE_TUPLE::Triple::Triple(long tupleID, long attr, long value)
{
    m_identifier = tupleID;
    m_attribute = attr;
    m_value = value;
}

NAMESPACE_TUPLE::Triple::~Triple()
{
    
}

long NAMESPACE_TUPLE::Triple::GetIdentifier() const
{
    return m_identifier;
}

long NAMESPACE_TUPLE::Triple::GetAttribute(long attrId) const
{
    return attrId == 0 ? m_attribute : k_InvalidTIndex;
}

long NAMESPACE_TUPLE::Triple::GetValue(long attrId) const
{
    return attrId == 0 ? m_value : k_InvalidTIndex;
}

void NAMESPACE_TUPLE::Triple::SetID(long tupleID)
{
    m_identifier = tupleID;
}

bool NAMESPACE_TUPLE::Triple::SetAttr(long attr, long attrIndex)
{
    if (attrIndex > 0 && attrIndex < GetNumAttributes())
    {
        m_attribute = attr;
        return true;
    }
    return false;
}

bool NAMESPACE_TUPLE::Triple::SetValue(long value, long attrIndex)
{
    if (attrIndex > 0 && attrIndex < GetNumAttributes())
    {
        m_value = value;
        return true;
    }
    return false;
}

long NAMESPACE_TUPLE::Triple::GetNumAttributes() const
{
    return 1;
}

bool NAMESPACE_TUPLE::Triple::Equals(const ITuple& rhs) const
{
    return rhs.GetNumAttributes() == GetNumAttributes() &&
        rhs.GetIdentifier() == GetIdentifier() &&
        rhs.GetAttribute(0) == GetAttribute(0) &&
        rhs.GetValue(0) == GetValue(0);
}

bool NAMESPACE_TUPLE::Triple::LessThan(const ITuple& rhs) const
{
    long otherIdentifier = rhs.GetIdentifier();
    if (otherIdentifier != m_identifier)
    {
        return GetIdentifier() < otherIdentifier;
    }
    long otherAttrType = rhs.GetAttribute(0);
    if (otherAttrType != m_attribute)
    {
        return GetAttribute(0) < otherAttrType;
    }
    return GetValue(0) < rhs.GetValue(0);
}