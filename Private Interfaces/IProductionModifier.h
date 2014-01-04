//
//  IProductionModifier.h
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IProductionModifier_h
#define CppRete_IProductionModifier_h

#include "Namespaces.h"
#include <list>

NAMESPACE_RETE_BEGIN
class IJoinNode;
class IBetaMemory;
class IAlphaMemory;
class IJoinNodeTest;
class IAlphaNodeTest;
class IProductionNode;
class IReteMemory;
class IProductionNode;
NAMESPACE_RETE_END

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class IActivationVisitor;
class ICondition;
class IAlphaHashNetwork;

class IProductionModifier
{
public:
    virtual ~IProductionModifier() {};
    
    // For use by clients
    virtual bool AddProduction(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IAlphaHashNetwork* pHeadAlphaNetwork, std::list<ICondition*>* pListOfConditions, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs, IBetaMemory* pDummyTopNode) = 0;
    virtual void RemoveProduction(IProductionNode* pProduction, IAlphaHashNetwork* pHeadAlphaNetwork) = 0;
    
    // Helper methods only
    virtual IBetaMemory* ConstructOrShareBetaMemory(IActivationVisitor* pVisitor, IJoinNode* pParent) = 0;
    virtual IJoinNode* ConstructOrShareJoinNode(IBetaMemory* pParent, IAlphaMemory* pAlphaMem, std::list<IJoinNodeTest*>* pListJoinTests) = 0;
    virtual std::list<IJoinNodeTest*>* ConstructJoinNodeTestsList(ICondition* pCondition, std::list<ICondition*>* pPrevConditions) = 0;
    virtual IAlphaMemory* ConstructOrShareAlphaMemory(IActivationVisitor* pVisitor, IAlphaHashNetwork* pAlphaNetwork, ICondition* pCondition, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs) = 0;
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IBetaMemory* pParent) = 0;
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IBetaMemory* pNewNode) = 0;
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IProductionNode* pNewNode) = 0;
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IBetaMemory* pParent) = 0;
    virtual void DeleteNodeAndAnyUnusedAncestors(IJoinNode* pNode, IAlphaHashNetwork* pHeadHash) = 0;
    virtual void DeleteNodeAndAnyUnusedAncestors(IBetaMemory* pNode, IAlphaHashNetwork* pHeadHash) = 0;
    virtual void DeleteNodeAndAnyUnusedAncestors(IProductionNode* pNode, IAlphaHashNetwork* pHeadHash) = 0;
};

NAMESPACE_RETE_ALG_END

#endif
