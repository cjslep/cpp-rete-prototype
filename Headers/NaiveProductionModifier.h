//
//  NaiveProductionModifier.h
//  CppRete
//
//  Created by Cory Slep on 11/9/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveProductionModifier__
#define __CppRete__NaiveProductionModifier__

#include "Namespaces.h"
#include "IProductionModifier.h"
#include <list>
#include <vector>

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN

class NaiveProductionModifier : public IProductionModifier
{
public:
    NaiveProductionModifier();
    virtual ~NaiveProductionModifier();
    
    // Inherited from IProductionModifier
    virtual bool AddProduction(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IAlphaHashNetwork* pAlphaNetwork, std::list<ICondition*>* pListOfConditions, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs, IBetaMemory* pDummyTopNode);
    virtual void RemoveProduction(IProductionNode* pProduction, IAlphaHashNetwork* pHeadAlphaNetwork);
    virtual IBetaMemory* ConstructOrShareBetaMemory(IActivationVisitor* pVisitor, IJoinNode* pParent);
    virtual IJoinNode* ConstructOrShareJoinNode(IBetaMemory* pParent, IAlphaMemory* pAlphaMem, std::list<IJoinNodeTest*>* pListJoinTests);
    virtual std::list<IJoinNodeTest*>* ConstructJoinNodeTestsList(ICondition* pCondition, std::list<ICondition*>* pPrevConditions);
    virtual IAlphaMemory* ConstructOrShareAlphaMemory(IActivationVisitor* pVisitor, IAlphaHashNetwork* pAlphaNetwork, ICondition* pCondition, std::list<NAMESPACE_TUPLE::IWME *>* pAllWMEs);
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IProductionNode* pProdNode, IBetaMemory* pParent);
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IBetaMemory* pNewNode);
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IJoinNode* pParent, IProductionNode* pNewNode);
    virtual void UpdateNewNodeWithPreviousMatches(IActivationVisitor* pVisitor, IBetaMemory* pParent);
    virtual void DeleteNodeAndAnyUnusedAncestors(IJoinNode* pNode, IAlphaHashNetwork* pHeadHash);
    virtual void DeleteNodeAndAnyUnusedAncestors(IBetaMemory* pNode, IAlphaHashNetwork* pHeadHash);
    virtual void DeleteNodeAndAnyUnusedAncestors(IProductionNode* pNode, IAlphaHashNetwork* pHeadHash);
    
private:
    // Disallow copying
    NaiveProductionModifier& operator=(const NaiveProductionModifier&);
    NaiveProductionModifier(const NaiveProductionModifier&);
};
NAMESPACE_RETE_ALG_END

#endif /* defined(__CppRete__NaiveProductionModifier__) */
