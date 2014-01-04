//
//  ITokenFactory.h
//  CppRete
//
//  Created by Cory Slep on 10/21/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ITokenFactory_h
#define CppRete_ITokenFactory_h

#include "Namespaces.h"

NAMESPACE_TUPLE_BEGIN
class IToken;
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_TUPLE_OVRHD_BEGIN

// Possibly also create "complete tuples" -- that is, ITuple, IWME, ITokens
class ITokenFactory
{
public:
    virtual ~ITokenFactory() {}
    
    virtual IToken* CreateNewTokenFromWME(IWME& aWME) const = 0;
};

NAMESPACE_TUPLE_OVRHD_END

#endif
