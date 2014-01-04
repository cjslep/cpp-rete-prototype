//
//  IReteMemory.h
//  CppRete
//
//  Created by Cory Slep on 10/5/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IReteMemory_h
#define CppRete_IReteMemory_h

#include "Namespaces.h"
#include "IActivationVisitee.h"
#include <list>

NAMESPACE_RETE_BEGIN
class IJoinNode;

class IReteMemory : public IActivationVisitee
{
public:
    virtual ~IReteMemory() {}
    
    virtual bool HasParent() const = 0;
    virtual std::list<IJoinNode*>* GetChildrenList() const = 0;
    virtual bool AddChild(IJoinNode* child) = 0;
    virtual bool RemoveChild(IJoinNode* child) = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IReteMemory& rhs) const = 0;
};

NAMESPACE_RETE_END

inline bool operator==(const NAMESPACE_RETE::IReteMemory& lhs, const NAMESPACE_RETE::IReteMemory& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_RETE::IReteMemory& lhs, const NAMESPACE_RETE::IReteMemory& rhs) {return !lhs.Equals(rhs);}



#endif
