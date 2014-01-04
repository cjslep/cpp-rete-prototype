//
//  NaiveJoinNodeTest.cpp
//  CppRete
//
//  Created by Cory Slep on 11/10/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveJoinNodeTest.h"
#include "IToken.h"
#include "IWME.h"
#include "ITuple.h"
#include <stdio.h>

NAMESPACE_RETE::NaiveJoinNodeTest::NaiveJoinNodeTest(long fieldWMEfromToken, long fieldWME, long tokenIndex) :
    m_fieldWME(fieldWME),
    m_fieldWMEfromToken(fieldWMEfromToken),
    m_tokenIndex(tokenIndex)
{
    
}

NAMESPACE_RETE::NaiveJoinNodeTest::~NaiveJoinNodeTest()
{
    
}

bool NAMESPACE_RETE::NaiveJoinNodeTest::Test(const NAMESPACE_TUPLE::IToken& aToken, const NAMESPACE_TUPLE::IWME& aWME) const
{
    const NAMESPACE_TUPLE::IToken* pToken = &aToken;
    for (int i = 0; i < m_tokenIndex; ++i) {
        pToken = pToken->GetParentToken();
        if (NULL == pToken)
        {
            return false;
        }
    }
    const NAMESPACE_TUPLE::IWME* pWME = pToken->GetWME();
    long valueToken = -1;
    if (-1 == m_fieldWMEfromToken)
    {
        valueToken = pWME->GetIdentifier();
    }
    else if (m_fieldWMEfromToken % 2 == 0)
    {
        valueToken = pWME->GetAttribute(m_fieldWMEfromToken / 2);
    }
    else
    {
        valueToken = pWME->GetValue(m_fieldWMEfromToken / 2);
    }
    
    long valueWME = -1;
    if (-1 == m_fieldWME)
    {
        valueWME = aWME.GetIdentifier();
    }
    else if (m_fieldWME % 2 == 0)
    {
        valueWME = aWME.GetAttribute(m_fieldWME / 2);
    }
    else
    {
        valueWME = aWME.GetValue(m_fieldWME / 2);
    }
    
    return valueToken == valueWME;
}

long NAMESPACE_RETE::NaiveJoinNodeTest::GetTokenIndex() const
{
    return m_tokenIndex;
}

long NAMESPACE_RETE::NaiveJoinNodeTest::GetAttributeIndexWME() const
{
    return m_fieldWME;
}

long NAMESPACE_RETE::NaiveJoinNodeTest::GetAttributeIndexToken() const
{
    return m_fieldWMEfromToken;
}

bool NAMESPACE_RETE::NaiveJoinNodeTest::Equals(const IJoinNodeTest& rhs) const
{
    return m_tokenIndex == rhs.GetTokenIndex() &&
        m_fieldWME == rhs.GetAttributeIndexWME() &&
        m_fieldWMEfromToken == rhs.GetAttributeIndexToken();
}