//
//  IAlphaNode.h
//  CppRete
//
//  Created by Cory Slep on 9/23/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IAlphaMemory_h
#define CppRete_IAlphaMemory_h

#include "Namespaces.h"
#include "IReteMemory.h"

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END


NAMESPACE_RETE_BEGIN

class IAlphaMemory : public IReteMemory
{
public:
    virtual ~IAlphaMemory() {}
    
    virtual std::list<NAMESPACE_TUPLE::IWME*>* GetWMESuccessors() const = 0;
    virtual bool AddWMESuccessor(NAMESPACE_TUPLE::IWME* successor) = 0;
    virtual NAMESPACE_TUPLE::IWME* RemoveWMESuccessor(NAMESPACE_TUPLE::IWME* successor) = 0;
};

NAMESPACE_RETE_END

#endif
