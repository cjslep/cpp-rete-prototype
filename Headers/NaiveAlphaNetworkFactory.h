//
//  NaiveAlphaNetworkFactory.h
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveAlphaNetworkFactory__
#define __CppRete__NaiveAlphaNetworkFactory__

#include "IAlphaNetworkFactory.h"

NAMESPACE_RETE_ALG_BEGIN

class NaiveAlphaNetworkFactory : public IAlphaNetworkFactory
{
public:
    NaiveAlphaNetworkFactory() {};
    virtual ~NaiveAlphaNetworkFactory() {};
    
    virtual IAlphaHashNetwork* GetNewAlphaHashNetwork(IActivationVisitor* pVisitor);
    virtual IAlphaNodeTest* GetNewAlphaNodeTest();
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue);
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes);
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(long idValue, const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues);
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(const std::list<long>& attrTypes);
    virtual IAlphaNodeTest* GetNewAlphaNodeTest(const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues);
    virtual IAlphaMemory* GetNewAlphaMemory();
};

NAMESPACE_RETE_ALG_END

#endif /* defined(__CppRete__NaiveAlphaNetworkFactory__) */
