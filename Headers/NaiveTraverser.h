//
//  NaiveTraverser.h
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveTraverser__
#define __CppRete__NaiveTraverser__

#include "Namespaces.h"
#include "ITupleTraverser.h"

NAMESPACE_TUPLE_BEGIN
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_TUPLE_ALG_BEGIN

class NaiveTraverser : public ITupleTraverser
{
public:
    NaiveTraverser();
    virtual ~NaiveTraverser();
    
    // Inherited from ITupleTraverser
    virtual void RemoveWMEInToken(NAMESPACE_TUPLE::IToken* pToken) = 0;
    virtual void RemoveTokenAndDescendants(NAMESPACE_TUPLE::IToken* pToken) = 0;
    
private:
    // Disallow copying
    NaiveTraverser& operator=(const NaiveTraverser&);
    NaiveTraverser(const NaiveTraverser&);
};

NAMESPACE_TUPLE_ALG_END

#endif /* defined(__CppRete__NaiveTraverser__) */
