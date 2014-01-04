//
//  ICondition.h
//  CppRete
//
//  Created by Cory Slep on 11/10/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ICondition_h
#define CppRete_ICondition_h

#include "Namespaces.h"
#include "ITuple.h"
#include <string>
#include <list>
#include <unordered_map>

NAMESPACE_RETE_BEGIN
class IAlphaNodeTest;
NAMESPACE_RETE_END

NAMESPACE_RETE_ALG_BEGIN

class ICondition
{
public:
    virtual ~ICondition() {}
    
    virtual NAMESPACE_RETE::IAlphaNodeTest* GetAlphaTestNode() const = 0; // Full testing
    virtual NAMESPACE_RETE::IAlphaNodeTest* GetAlphaTestAttributeTypeNode() const = 0; // Only test based on attribute type
    virtual void GetAllVariables(std::list<std::string>& vecVariables) const = 0; // All variables associated with this condition
    
    virtual bool HasVariableIdentifierOf(const std::string& varName) const = 0;
    virtual bool HasVariableIdentifier() const = 0;
    virtual long GetConstantIdentifierValue() const = 0;
    
    virtual bool HasAtLeastOneConstantAttributeType() const = 0;
    virtual bool HasConstantAttributeType(long attrType) const = 0;
    virtual void GetAllConstantAttrTypes(std::list<long>& vecAttrTypeIDs) const = 0;
    
    virtual bool HasAtLeastOneConstantAttributeValue() const = 0;
    virtual bool HasConstantAttributeValue(long attrType) const = 0;
    virtual void GetAllConstantAttrValues(std::list<long>& vecAttrTypeIDs, std::unordered_map<long, long>& mapAttrValuesForTypes) const = 0;
    
    virtual bool HasAttributeTypeWithVariableName(const std::string& varName) const = 0;
    virtual long GetAttributeIndexWithVariableName(const std::string& varName) const = 0;
    
    virtual long GetValueIndexWithVariableName(const std::string& varName) const = 0;
    
    virtual long GetNumAttributes() const = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const ICondition& rhs) const = 0;
};

NAMESPACE_RETE_ALG_END

inline bool operator==(const NAMESPACE_RETE_ALG::ICondition& lhs, const NAMESPACE_RETE_ALG::ICondition& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_RETE_ALG::ICondition& lhs, const NAMESPACE_RETE_ALG::ICondition& rhs) {return !lhs.Equals(rhs);}


#endif
