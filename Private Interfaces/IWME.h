//
//  IWME.h
//  CppRete
//
//  Created by Cory Slep on 10/5/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IWME_h
#define CppRete_IWME_h

#include "Namespaces.h"
#include "ITupleTraversee.h"

NAMESPACE_RETE_BEGIN
class IAlphaMemory;
NAMESPACE_RETE_END


NAMESPACE_TUPLE_BEGIN

class ITuple;
class IToken;

class IWME : public NAMESPACE_ALG::ITupleTraversee
{
public:
    virtual ~IWME() {}
    
    virtual bool SetTuple(const ITuple* tuple) = 0;
    //virtual const ITuple* const GetTuple() const = 0;
    virtual bool AddReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent) = 0;
    virtual bool RemoveReteMemoryContainer(NAMESPACE_RETE::IAlphaMemory* parent) = 0;
    virtual bool AddTokenContainer(IToken* parent) = 0;
    virtual bool RemoveTokenContainer(IToken* parent) = 0;
    virtual bool ContainsMemoryParent(NAMESPACE_RETE::IAlphaMemory* pParent) = 0;
    virtual bool ContainsTokenParent(IToken* pParent) = 0;
    virtual long GetIdentifier() const = 0;
    virtual long GetAttribute(long attrIndex) const = 0;
    virtual long GetValue(long attrIndex) const = 0;
    virtual long GetNumAttributes() const = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IWME& rhs) const = 0;
    virtual bool Equals(const ITuple& rhs) const = 0;
};

NAMESPACE_TUPLE_END

inline bool operator==(const NAMESPACE_TUPLE::IWME& lhs, const NAMESPACE_TUPLE::IWME& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_TUPLE::IWME& lhs, const NAMESPACE_TUPLE::IWME& rhs) {return !lhs.Equals(rhs);}
inline bool operator==(const NAMESPACE_TUPLE::IWME& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_TUPLE::IWME& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return !lhs.Equals(rhs);}

#endif
