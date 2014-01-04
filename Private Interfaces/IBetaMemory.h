//
//  IBetaMemory.h
//  CppRete
//
//  Created by Cory Slep on 10/7/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IBetaMemory_h
#define CppRete_IBetaMemory_h

#include "Namespaces.h"
#include "IReteMemory.h"

NAMESPACE_TUPLE_BEGIN
class IToken;
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_BEGIN

class IBetaMemory : public IReteMemory
{
public:
    virtual ~IBetaMemory() {}
    
    virtual void SetParent(IJoinNode* parent) = 0;
    virtual IJoinNode* GetParent() const = 0;
    virtual std::list<NAMESPACE_TUPLE::IToken*>* GetTokenList() const = 0;
    virtual bool AddToTokenList(NAMESPACE_TUPLE::IToken* member) = 0;
    virtual bool RemoveFromTokenList(NAMESPACE_TUPLE::IToken* member) = 0;
};

NAMESPACE_RETE_END

#endif
