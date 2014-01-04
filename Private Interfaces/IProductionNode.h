//
//  IProductionNode.h
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IProductionNode_h
#define CppRete_IProductionNode_h

#include "Namespaces.h"
#include "IBetaMemory.h"

class IProductionSubscriber;

NAMESPACE_TUPLE_BEGIN
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class IActivationVisitee;
NAMESPACE_RETE_ALG_END

NAMESPACE_RETE_BEGIN

class IProductionNode : public IBetaMemory
{
public:
    virtual ~IProductionNode() {}
    
    virtual long GetId() const = 0;
    virtual void ClearTokenList() = 0;
    virtual bool AddSubscriber(IProductionSubscriber* pSubscriber) = 0;
    virtual bool RemoveSubscriber(IProductionSubscriber* pSubscriber) = 0;
};

NAMESPACE_RETE_END

#endif
