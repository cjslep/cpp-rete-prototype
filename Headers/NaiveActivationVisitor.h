//
//  NaiveActivationVisitor.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveActivationVisitor__
#define __CppRete__NaiveActivationVisitor__

#include "Namespaces.h"
#include "IActivationVisitor.h"
#include <list>

NAMESPACE_TUPLE_OVRHD_BEGIN
class ITokenFactory;
NAMESPACE_TUPLE_OVRHD_END
NAMESPACE_TUPLE_BEGIN
class IWME;
class IToken;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
class IJoinNode;
class IJoinNodeTest;
class IBetaMemory;
class IProductionNode;
NAMESPACE_RETE_END

NAMESPACE_RETE_ALG_BEGIN

class NaiveActivationVisitor : public IActivationVisitor
{
public:
    NaiveActivationVisitor(const NAMESPACE_TUPLE_OVRHD::ITokenFactory* factory);
    virtual ~NaiveActivationVisitor();
    
    // Inherited from IActivationVisitor
    virtual void AlphaActivate(std::list<IJoinNode*>* listSuccessors, std::list<NAMESPACE_TUPLE::IWME*>* wmeItems);
    virtual void LeftBetaActivate(IBetaMemory* pBetaMem, std::list<IJoinNode*>* listChildren);
    virtual void LeftJoinActivate(IAlphaMemory* pAlphaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren);
    virtual void RightJoinActivate(IBetaMemory* pBetaParent, const std::list<IJoinNodeTest*>& vecTests, IBetaMemory* pChildMem, std::list<IProductionNode*>* pVecChildren);
    virtual void LeftBetaActivateForProduction(IBetaMemory* pParent, IProductionNode* pChildProd);
    virtual void LeftBetaActivateForNewInsertion(IJoinNode* pBetaParent);
    virtual void RightJoinActivateForProduction(IJoinNode* pJoinNode, NAMESPACE_TUPLE::IWME* pWME);
    virtual void ProductionActivated(IProductionNode* pProduction);
    
    virtual void SetWME(NAMESPACE_TUPLE::IWME* pWME);
    
    // For beginning the chain calling
    virtual void BeginAlphaActivate(IAlphaMemory* alphaMemory, NAMESPACE_TUPLE::IWME* wme);
    
protected:
    // Helper functions
    bool DoesPassJoinTests(const std::list<IJoinNodeTest*>& vecTests, NAMESPACE_TUPLE::IToken* pToken, NAMESPACE_TUPLE::IWME* pWME);
    
    // Member variables
    const NAMESPACE_TUPLE_OVRHD::ITokenFactory* m_pFactory;
    NAMESPACE_TUPLE::IWME* m_pWme;
    NAMESPACE_TUPLE::IToken* m_pToken;
    
private:
    // Disallow copying
    NaiveActivationVisitor& operator=(const NaiveActivationVisitor&);
    NaiveActivationVisitor(const NaiveActivationVisitor&);
};

NAMESPACE_RETE_ALG_END

#endif /* defined(__CppRete__NaiveActivationVisitor__) */
