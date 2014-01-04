//
//  IActivationVisitee.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IActivationVisitee_h
#define CppRete_IActivationVisitee_h

#include "Namespaces.h"

NAMESPACE_RETE_ALG_BEGIN
class IActivationVisitor;
NAMESPACE_RETE_ALG_END

NAMESPACE_RETE_BEGIN

class IActivationVisitee
{
public:
    virtual ~IActivationVisitee() {}
    
    virtual void VisitBy(NAMESPACE_RETE_ALG::IActivationVisitor* visitor, bool isLeft) = 0;
};

NAMESPACE_RETE_END

#endif
