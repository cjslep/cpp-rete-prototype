//
//  ITupleTraversee.h
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ITupleTraversee_h
#define CppRete_ITupleTraversee_h

#include "Namespaces.h"

NAMESPACE_TUPLE_ALG_BEGIN
class ITupleTraverser;

class ITupleTraversee
{
public:
    virtual ~ITupleTraversee() {}
    
    virtual void TraversedBy(ITupleTraverser* visitor) = 0;
    
};

NAMESPACE_TUPLE_ALG_END

#endif
