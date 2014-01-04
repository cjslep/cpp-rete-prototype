//
//  NaiveJoinNode.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveJoinNode__
#define __CppRete__NaiveJoinNode__

#include "Namespaces.h"
#include <list>
#include "IJoinNode.h"

NAMESPACE_RETE_OVRHD_BEGIN
class IJoinNodeAncestryManager;
NAMESPACE_RETE_OVRHD_END

NAMESPACE_RETE_BEGIN
class IJoinNodeTest;
class IBetaMemory;
class IAlphaMemory;
class IProductionNode;

class NaiveJoinNode : public IJoinNode
{
public:
    NaiveJoinNode(IAlphaMemory* parentAlpha, IBetaMemory* parentBeta);
    virtual ~NaiveJoinNode();
    
    // Inhereted from IJoinNode
    virtual IBetaMemory* GetBetaParent();
    virtual IAlphaMemory* GetAlphaParent();
    virtual bool AddJoinNodeTest(IJoinNodeTest* addTest);
    virtual bool RemoveJoinNodeTest(IJoinNodeTest* removeTest);
    virtual IBetaMemory* GetChildMemory() const;
    virtual void SetChildMemory(IBetaMemory* pChild);
    virtual std::list<IJoinNodeTest*>* GetJoinTests() const;
    virtual std::list<IProductionNode*>* GetChildProductions() const;
    virtual bool AddProduction(IProductionNode* childProduction);
    virtual bool RemoveProduction(IProductionNode* childProduction);
    virtual void ClearProductions();
    virtual bool HasSameJoinTests(std::list<IJoinNodeTest*>* pListJoinTests);
    virtual bool HasChildMemory();
    
    // Inhereted from IActivationVisitee
    
    virtual void VisitBy(NAMESPACE_ALG::IActivationVisitor* visitor, bool isLeft);
    
protected:
    // Helper functions
    std::list<IProductionNode*>::iterator FindChildProduction(IProductionNode* queryNode);
    std::list<IJoinNodeTest*>::iterator FindTest(IJoinNodeTest* test);
    
    // Member variables
    std::list<IJoinNodeTest*> m_joinTests;
    std::list<IProductionNode*> m_childProductions;
    IBetaMemory* m_pChild;
    IBetaMemory* m_pParentBeta;
    IAlphaMemory* m_pParentAlpha;
    
private:
    // Disallow copying
    NaiveJoinNode& operator=(const NaiveJoinNode&);
    NaiveJoinNode(const NaiveJoinNode&);
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveJoinNode__) */
