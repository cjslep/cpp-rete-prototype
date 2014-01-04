//
//  NaiveProductionNode.h
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveProductionNode__
#define __CppRete__NaiveProductionNode__

#include "Namespaces.h"
#include "IProductionNode.h"
#include <list>

NAMESPACE_TUPLE_BEGIN
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class IActivationVisitor;
NAMESPACE_RETE_ALG_END

NAMESPACE_RETE_BEGIN
class IJoinNode;
class IReteMemory;

class NaiveProductionNode : public IProductionNode
{
public:
    NaiveProductionNode(long id);
    NaiveProductionNode(long id, IJoinNode* pParent);
    virtual ~NaiveProductionNode();
    
    // Inherited from IProductionNode
    virtual long GetId() const;
    virtual void ClearTokenList();
    virtual bool AddSubscriber(IProductionSubscriber* pSubscriber);
    virtual bool RemoveSubscriber(IProductionSubscriber* pSubscriber);
    
    // Inherited from IBetaMemory
    virtual IJoinNode* GetParent() const;
    virtual void SetParent(IJoinNode* parent);
    virtual std::list<NAMESPACE_TUPLE::IToken*>* GetTokenList() const;
    virtual bool AddToTokenList(NAMESPACE_TUPLE::IToken* member);
    virtual bool RemoveFromTokenList(NAMESPACE_TUPLE::IToken* member);
    
    // Inherited from IReteMemory
    virtual bool HasParent() const;
    virtual std::list<IJoinNode*>* GetChildrenList() const;
    virtual bool AddChild(IJoinNode* child);
    virtual bool RemoveChild(IJoinNode* child);
    // Clients use operators instead of the following function
    virtual bool Equals(const IReteMemory& rhs) const;
    
    // Inherited from IActivationVisitee
    virtual void VisitBy(NAMESPACE_RETE_ALG::IActivationVisitor* visitor, bool isLeft);
    
protected:
    // Helpers
    void NotifySubscribers(NAMESPACE_TUPLE::IToken* newToken);
    
    // Members
    long m_lId;
    IJoinNode* m_pParent;
    std::list<NAMESPACE_TUPLE::IToken*> m_vecTokenList;
    std::list<IProductionSubscriber*> m_listSubs;
    
private:
    // Disallow copying
    NaiveProductionNode& operator=(const NaiveProductionNode&);
    NaiveProductionNode(const NaiveProductionNode&);
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveProductionNode__) */
