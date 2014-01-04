//
//  IJoinNode.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IJoinNode_h
#define CppRete_IJoinNode_h

#include "Namespaces.h"
#include "IActivationVisitee.h"
#include <list>

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
class IJoinNodeTest;
class IBetaMemory;
class IProductionNode;

class IJoinNode : public IActivationVisitee {
public:
    virtual ~IJoinNode() {}
    
    virtual IBetaMemory* GetBetaParent() = 0;
    virtual IAlphaMemory* GetAlphaParent() = 0;
    virtual bool AddJoinNodeTest(IJoinNodeTest* addTest) = 0;
    virtual bool RemoveJoinNodeTest(IJoinNodeTest* removeTest) = 0;
    virtual IBetaMemory* GetChildMemory() const = 0;
    virtual void SetChildMemory(IBetaMemory* pChild) = 0;
    virtual std::list<IJoinNodeTest*>* GetJoinTests() const = 0;
    virtual std::list<IProductionNode*>* GetChildProductions() const = 0;
    virtual bool AddProduction(IProductionNode* childProduction) = 0;
    virtual bool RemoveProduction(IProductionNode* childProduction) = 0;
    virtual void ClearProductions() = 0;
    virtual bool HasSameJoinTests(std::list<IJoinNodeTest*>* pListJoinTests) = 0;
    virtual bool HasChildMemory() = 0;
    
    // Clients use operators instead of the following functions
    //virtual bool Equals(const IJoinNode& rhs) const = 0;
    //virtual bool LessThan(const IJoinNode& rhs) const = 0;
};

NAMESPACE_RETE_END

/*inline bool operator==(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return !lhs.Equals(rhs);}
inline bool operator<(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return lhs.LessThan(rhs);}
inline bool operator>(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return rhs.LessThan(lhs);}
inline bool operator<=(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return !rhs.LessThan(lhs);}
inline bool operator>=(const NAMESPACE_RETE::IJoinNode& lhs, const NAMESPACE_RETE::IJoinNode& rhs) {return !lhs.LessThan(rhs);}*/

#endif
