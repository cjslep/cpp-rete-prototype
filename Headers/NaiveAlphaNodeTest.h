//
//  NaiveAlphaNodeTest.h
//  CppRete
//
//  Created by Cory Slep on 11/10/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveAlphaNodeTest__
#define __CppRete__NaiveAlphaNodeTest__

#include "Namespaces.h"
#include "IAlphaNodeTest.h"
#include <list>
#include <unordered_map>

NAMESPACE_RETE_BEGIN

class NaiveAlphaNodeTest : public IAlphaNodeTest
{
public:
    NaiveAlphaNodeTest();
    NaiveAlphaNodeTest(long idValue);
    NaiveAlphaNodeTest(long idValue, const std::list<long>& attrTypes);
    NaiveAlphaNodeTest(long idValue, const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues);
    NaiveAlphaNodeTest(const std::list<long>& attrTypes);
    NaiveAlphaNodeTest(const std::list<long>& attrTypes, const std::unordered_map<long, long>& attrValues);
    
    virtual ~NaiveAlphaNodeTest();
    
    // Inherited from IAlphaNodeTest
    virtual bool Test(const NAMESPACE_TUPLE::IWME& aWME) const;
    virtual bool HasEquivalentConditions(const NAMESPACE_RETE_ALG::ICondition& otherCond) const;
    virtual bool HasSameAttributeTypeTest(const NAMESPACE_RETE_ALG::ICondition& otherCond) const;
    virtual bool HasIDValue() const;
    virtual long GetIdValue() const;
    virtual bool HasAttrTypes() const;
    virtual bool HasExactlyAttrTypes(const std::list<long>& vecAttrs) const;
    virtual bool HasAttrValues() const;
    virtual bool HasExactlyAttrValues(const std::list<long>& vecAttrs, const std::unordered_map<long, long>& attributeValueFromType) const;
    virtual bool IsUnconditionallyAccepting() const;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const IAlphaNodeTest& rhs) const;
    
protected:
    bool m_HasIDValue;
    bool m_HasAttributeTypes;
    bool m_HasAttributeValues;
    long m_idValue;
    std::unordered_map<long, long> m_attributeValueFromType;
    std::list<long> m_attributeTypes;
    
private:
    // Disallow copying
    NaiveAlphaNodeTest& operator=(const NaiveAlphaNodeTest&);
    NaiveAlphaNodeTest(const NaiveAlphaNodeTest&);
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveAlphaNodeTest__) */
