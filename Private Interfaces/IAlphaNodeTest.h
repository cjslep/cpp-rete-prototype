//
//  IAlphaNodeTest.h
//  CppRete
//
//  Created by Cory Slep on 11/3/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IAlphaNodeTest_h
#define CppRete_IAlphaNodeTest_h

#include "Namespaces.h"
#include <list>
#include <unordered_map>

NAMESPACE_TUPLE_BEGIN
class IWME;
NAMESPACE_TUPLE_END

NAMESPACE_RETE_ALG_BEGIN
class ICondition;
NAMESPACE_RETE_ALG_END

NAMESPACE_RETE_BEGIN

class IAlphaNodeTest
{
public:
    virtual ~IAlphaNodeTest() {}
    
    virtual bool Test(const NAMESPACE_TUPLE::IWME& aWME) const = 0;
    virtual bool HasEquivalentConditions(const NAMESPACE_RETE_ALG::ICondition& otherCond) const = 0;
    virtual bool HasSameAttributeTypeTest(const NAMESPACE_RETE_ALG::ICondition& otherCond) const = 0;
    virtual bool HasIDValue() const = 0;
    virtual long GetIdValue() const = 0;
    virtual bool HasAttrTypes() const = 0;
    virtual bool HasExactlyAttrTypes(const std::list<long>& vecAttrs) const = 0;
    virtual bool HasAttrValues() const = 0;
    virtual bool HasExactlyAttrValues(const std::list<long>& vecAttrs, const std::unordered_map<long, long>& attributeValueFromType) const = 0;
    virtual bool IsUnconditionallyAccepting() const = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IAlphaNodeTest& rhs) const = 0;
};

NAMESPACE_RETE_END

inline bool operator==(const NAMESPACE_RETE::IAlphaNodeTest& lhs, const NAMESPACE_RETE::IAlphaNodeTest& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_RETE::IAlphaNodeTest& lhs, const NAMESPACE_RETE::IAlphaNodeTest& rhs) {return !lhs.Equals(rhs);}

#endif
