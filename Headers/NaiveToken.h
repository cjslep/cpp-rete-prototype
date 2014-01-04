//
//  NaiveToken.h
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveToken__
#define __CppRete__NaiveToken__

#include <list>
#include "Namespaces.h"
#include "IToken.h"

NAMESPACE_RETE_BEGIN
class IBetaMemory;
NAMESPACE_RETE_END

NAMESPACE_TUPLE_BEGIN
class IWME;

class NaiveToken : public IToken {
public:
    NaiveToken(IWME* pIWME);
    NaiveToken(IWME* pIWME, NAMESPACE_RETE::IBetaMemory* pParentMemory);
    NaiveToken(IWME* pIWME, NAMESPACE_RETE::IBetaMemory* pParentMemory, IToken* pParentToken);
    virtual ~NaiveToken();
    
    // Inherited from IToken
    virtual const IToken* const GetParentToken() const;
    virtual bool SetParentToken(IToken* parent);
    virtual const NAMESPACE_RETE::IBetaMemory* const GetParentMemory() const;
    virtual void SetParentMemory(NAMESPACE_RETE::IBetaMemory* parent);
    virtual const IWME* const GetWME() const;
    virtual long GetNumTokenChildren() const;
    virtual bool AddTokenChild(IToken* child);
    virtual bool RemoveTokenChild(IToken* child);
    
    // Inherited from ITupleTraversee
    virtual void TraversedBy(NAMESPACE_ALG::ITupleTraverser* visitor);
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IToken& rhs) const;
    
protected:
    std::list<IToken*> m_listChildTokens;
    NAMESPACE_RETE::IBetaMemory* m_pParentMemory;
    IToken* m_pParentToken;
    IWME* m_pIWME;
    
private:
    // Disallow copying
    NaiveToken& operator=(const NaiveToken&);
    NaiveToken(const NaiveToken&);
};

NAMESPACE_TUPLE_END

#endif /* defined(__CppRete__NaiveToken__) */
