//
//  ITupleTraverser.h
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ITupleTraverser_h
#define CppRete_ITupleTraverser_h

#include "Namespaces.h"

NAMESPACE_TUPLE_BEGIN
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_TUPLE_ALG_BEGIN

class ITupleTraverser
{
public:
    virtual ~ITupleTraverser() {}
    
    // Used by clients
    virtual void RemoveWMEInToken(NAMESPACE_TUPLE::IToken* pToken) = 0;
    
    // Callback
    virtual void RemoveTokenAndDescendants(NAMESPACE_TUPLE::IToken* pToken) = 0;
};

NAMESPACE_TUPLE_ALG_END

#endif
