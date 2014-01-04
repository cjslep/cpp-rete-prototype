//
//  NaiveAlphaNetworkFactory.cpp
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveAlphaNetworkFactory.h"
#include "NaiveAlphaHashNetwork.h"
#include "NaiveAlphaNodeTest.h"
#include "NaiveAlphaMemory.h"

NAMESPACE_RETE_ALG::IAlphaHashNetwork* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaHashNetwork(IActivationVisitor* pVisitor)
{
    return new NaiveAlphaHashNetwork(pVisitor, this);
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest()
{
    return new NaiveAlphaNodeTest();
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest(long idValue)
{
    return new NaiveAlphaNodeTest(idValue);
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes)
{
    return new NaiveAlphaNodeTest(idValue, attrTypes);
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues)
{
    return new NaiveAlphaNodeTest(idValue, attrTypes, attrValues);
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest(const std::list<long>& attrTypes)
{
    return new NaiveAlphaNodeTest(attrTypes);
}

NAMESPACE_RETE::IAlphaNodeTest* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaNodeTest(const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues)
{
    return new NaiveAlphaNodeTest(attrTypes, attrValues);
}

NAMESPACE_RETE::IAlphaMemory* NAMESPACE_RETE_ALG::NaiveAlphaNetworkFactory::GetNewAlphaMemory()
{
    return new NaiveAlphaMemory();
}