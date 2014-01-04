//
//  IActivationVisitor.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IActivationVisitor_h
#define CppRete_IActivationVisitor_h

#include "Namespaces.h"
#include <list>

NAMESPACE_TUPLE_BEGIN
class IWME;
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_BEGIN
class IJoinNode;
class IReteMemory;
class IBetaMemory;
class IAlphaMemory;
class IJoinNodeTest;
class IProductionNode;
NAMESPACE_RETE_END

NAMESPACE_RETE_ALG_BEGIN

class IActivationVisitor
{
public:
    virtual ~IActivationVisitor() {}
    
    // Initiators (Clients use these)
    virtual void BeginAlphaActivate(IAlphaMemory* alphaMemory, NAMESPACE_TUPLE::IWME* wme) = 0;
    
    // Callbacks within data structures
    virtual void AlphaActivate(std::list<IJoinNode*>* listSuccessors, std::list<NAMESPACE_TUPLE::IWME*>* wmeItems) = 0;
    virtual void LeftBetaActivate(IBetaMemory* pBetaMem, std::list<IJoinNode*>* listChildren) = 0;
    virtual void LeftJoinActivate(IAlphaMemory* pAlphaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren) = 0;
    virtual void RightJoinActivate(IBetaMemory* pBetaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren) = 0;
    virtual void LeftBetaActivateForProduction(IBetaMemory* pParent, IProductionNode* pChildProd) = 0;
    virtual void RightJoinActivateForProduction(IJoinNode* pJoinNode, NAMESPACE_TUPLE::IWME* pWME) = 0;
    virtual void LeftBetaActivateForNewInsertion(IJoinNode* pBetaParent) = 0;
    virtual void ProductionActivated(IProductionNode* pProduction) = 0;
    
    virtual void SetWME(NAMESPACE_TUPLE::IWME* pWME) = 0;
};

NAMESPACE_RETE_ALG_END

#endif
