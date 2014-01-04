//
//  IToken.h
//  CppRete
//
//  Created by Cory Slep on 10/5/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IToken_h
#define CppRete_IToken_h

#include "Namespaces.h"
#include "ITupleTraversee.h"

NAMESPACE_RETE_BEGIN
class IBetaMemory;
NAMESPACE_RETE_END

NAMESPACE_TUPLE_BEGIN
class IWME;

class IToken : public NAMESPACE_ALG::ITupleTraversee
{
public:
    virtual ~IToken() {}
    
    virtual const IToken* const GetParentToken() const = 0;
    virtual bool SetParentToken(IToken* parent) = 0; // Don't call this directly usually (Add/RemoveTokenChild handles it)
    virtual const IWME* const GetWME() const = 0;
    virtual long GetNumTokenChildren() const = 0;
    virtual bool AddTokenChild(IToken* child) = 0;
    virtual bool RemoveTokenChild(IToken* child) = 0;
    virtual const NAMESPACE_RETE::IBetaMemory* const GetParentMemory() const = 0;
    virtual void SetParentMemory(NAMESPACE_RETE::IBetaMemory* parent) = 0; // Don't call this directly (IBetaMemory Add/RemoveToTokenList handles it)
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IToken& rhs) const = 0;
};

NAMESPACE_TUPLE_END

inline bool operator==(const NAMESPACE_TUPLE::IToken& lhs, const NAMESPACE_TUPLE::IToken& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_TUPLE::IToken& lhs, const NAMESPACE_TUPLE::IToken& rhs) {return !lhs.Equals(rhs);}

#endif
