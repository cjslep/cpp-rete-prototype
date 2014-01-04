//
//  IJoinNodeTest.h
//  CppRete
//
//  Created by Cory Slep on 10/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IJoinNodeTest_h
#define CppRete_IJoinNodeTest_h

#include "Namespaces.h"

NAMESPACE_TUPLE_BEGIN
class IToken;
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class ICondition;
NAMESPACE_RETE_ALG_END

NAMESPACE_RETE_BEGIN

class IJoinNodeTest
{
public:
    virtual ~IJoinNodeTest() {}
    
    virtual bool Test(const NAMESPACE_TUPLE::IToken& aToken, const NAMESPACE_TUPLE::IWME& aWME) const = 0;
    
    virtual long GetTokenIndex() const = 0;
    virtual long GetAttributeIndexWME() const = 0;
    virtual long GetAttributeIndexToken() const = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IJoinNodeTest& rhs) const = 0;
};

NAMESPACE_RETE_END

inline bool operator==(const NAMESPACE_RETE::IJoinNodeTest& lhs, const NAMESPACE_RETE::IJoinNodeTest& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_RETE::IJoinNodeTest& lhs, const NAMESPACE_RETE::IJoinNodeTest& rhs) {return !lhs.Equals(rhs);}

#endif
