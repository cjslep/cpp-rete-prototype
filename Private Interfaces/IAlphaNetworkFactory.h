//
//  IAlphaNetworkFactory.h
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IAlphaNetworkFactory_h
#define CppRete_IAlphaNetworkFactory_h

#include "Namespaces.h"
#include <unordered_map>
#include <list>

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
class IAlphaNodeTest;
NAMESPACE_RETE_END

NAMESPACE_RETE_ALG_BEGIN
class IAlphaHashNetwork;
class IActivationVisitor;

class IAlphaNetworkFactory
{
public:
    virtual ~IAlphaNetworkFactory() {};
    
    virtual IAlphaHashNetwork* GetNewAlphaHashNetwork(IActivationVisitor* pVisitor) = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest() = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue) = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes) = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues) = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(const std::list<long>& attrTypes) = 0;
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues) = 0;
    virtual IAlphaMemory* GetNewAlphaMemory() = 0;
};

NAMESPACE_RETE_ALG_END

#endif
