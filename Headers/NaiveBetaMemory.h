//
//  NaiveBetaMemory.h
//  CppRete
//
//  Created by Cory Slep on 10/21/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveBetaMemory__
#define __CppRete__NaiveBetaMemory__

#include <list>
#include "Namespaces.h"
#include "IBetaMemory.h"

NAMESPACE_TUPLE_BEGIN
class ITokenFactory;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_BEGIN
class IJoinNode;

class NaiveBetaMemory : public IBetaMemory
{
public:
    NaiveBetaMemory();
    virtual ~NaiveBetaMemory();
    
    // Inherited from IBetaMemory
    virtual std::list<NAMESPACE_TUPLE::IToken*>* GetTokenList() const;
    virtual bool AddToTokenList(NAMESPACE_TUPLE::IToken* member);
    virtual bool RemoveFromTokenList(NAMESPACE_TUPLE::IToken* member);
    virtual IJoinNode* GetParent() const;
    virtual void SetParent(IJoinNode* parent);
    
    // Inherited from IReteMemory
    virtual bool HasParent() const;
    virtual std::list<IJoinNode*>* GetChildrenList() const;
    virtual bool AddChild(IJoinNode* child);
    virtual bool RemoveChild(IJoinNode* child);
    
    virtual bool Equals(const IReteMemory& rhs) const;
    
    // Inhereted from IActivationVisitee
    virtual void VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft);
    
protected:
    // Helper finders
    std::list<NAMESPACE_TUPLE::IToken*>::iterator FindTokenIteratorByValue(NAMESPACE_TUPLE::IToken* member);
    std::list<NAMESPACE_TUPLE::IToken*>::iterator FindTokenIteratorByPointer(NAMESPACE_TUPLE::IToken* member);
    
    // Member Variables
    IJoinNode* m_pParent;
    std::list<IJoinNode*> m_listChildren;
    std::list<NAMESPACE_TUPLE::IToken*> m_vecTokenList;
    
private:
    // Disallow copying
    NaiveBetaMemory& operator=(const NaiveBetaMemory&);
    NaiveBetaMemory(const NaiveBetaMemory&);
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveBetaMemory__) */
