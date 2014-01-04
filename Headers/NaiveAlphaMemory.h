//
//  NaiveAlphaMemory.h
//  CppRete
//
//  Created by Cory Slep on 10/7/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveAlphaMemory__
#define __CppRete__NaiveAlphaMemory__

#include <list>
#include "Namespaces.h"
#include "IAlphaMemory.h"
#include "IAlphaHashNetwork.h"

NAMESPACE_RETE_BEGIN
class IJoinNode;

class NaiveAlphaMemory : public IAlphaMemory
{
public:
    NaiveAlphaMemory();
    virtual ~NaiveAlphaMemory();
    
    // Inhereted from IAlphaMemory
    virtual std::list<NAMESPACE_TUPLE::IWME*>* GetWMESuccessors() const;
    virtual bool AddWMESuccessor(NAMESPACE_TUPLE::IWME* successor);
    virtual NAMESPACE_TUPLE::IWME* RemoveWMESuccessor(NAMESPACE_TUPLE::IWME* successor);
    
    // Inhereted from IReteMemory
    virtual bool HasParent() const;
    virtual std::list<IJoinNode*>* GetChildrenList() const;
    virtual bool AddChild(IJoinNode* child);
    virtual bool RemoveChild(IJoinNode* child);
    
    virtual bool Equals(const IReteMemory& rhs) const;
    
    // Inhereted from IActivationVisitee
    virtual void VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft);
    
protected:
    // Helper finders
    std::list<NAMESPACE_TUPLE::IWME*>::iterator FindSuccessorIndex(NAMESPACE_TUPLE::IWME* child);
    
    // Member variables
    std::list<IJoinNode*> m_listSuccessors;
    std::list<NAMESPACE_TUPLE::IWME*> m_wmeItems;
    
private:
    // Disallow copying
    NaiveAlphaMemory& operator=(const NaiveAlphaMemory&);
    NaiveAlphaMemory(const NaiveAlphaMemory&);
    
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveAlphaMemory__) */
