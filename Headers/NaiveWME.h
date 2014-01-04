//
//  NaiveWME.h
//  CppRete
//
//  Created by Cory Slep on 10/28/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveWME__
#define __CppRete__NaiveWME__

#include "Namespaces.h"
#include "IWME.h"
#include <list>

NAMESPACE_TUPLE_BEGIN
class ITuple;
class IToken;

class NaiveWME : public IWME
{
public:
    NaiveWME(const ITuple* pTuple);
    virtual ~NaiveWME();
    
    // Inherited from IWME
    virtual bool SetTuple(const ITuple* tuple);
    virtual const ITuple* const GetTuple() const;
    virtual bool AddReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent);
    virtual bool RemoveReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent);
    virtual bool AddTokenContainer(IToken* parent);
    virtual bool RemoveTokenContainer(IToken* parent);
    virtual bool ContainsMemoryParent(NAMESPACE_RETE::IAlphaMemory* pParent);
    virtual bool ContainsTokenParent(IToken* pParent);
    virtual long GetIdentifier() const;
    virtual long GetAttribute(long attrIndex) const;
    virtual long GetValue(long attrIndex) const;
    virtual long GetNumAttributes() const;
    
    // Inherited from ITupleTraversee
    virtual void TraversedBy(NAMESPACE_ALG::ITupleTraverser* visitor);
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IWME& rhs) const;
    virtual bool Equals(const ITuple& rhs) const;
    
protected:
    std::list<NAMESPACE_RETE::IAlphaMemory*>::iterator FindParentMemory(NAMESPACE_RETE::IAlphaMemory* pMemory);
    
    std::list<NAMESPACE_RETE::IAlphaMemory*> m_listParentMemories;
    std::list<IToken*> m_listParentTokens;
    const ITuple* m_pTuple;
    
private:
    // Disallow copying
    NaiveWME& operator=(const NaiveWME&);
    NaiveWME(const NaiveWME&);
    
};

NAMESPACE_TUPLE_END


#endif /* defined(__CppRete__NaiveWME__) */
