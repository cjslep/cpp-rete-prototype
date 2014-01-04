//
//  NaiveCondition.h
//  CppRete
//
//  Created by Cory Slep on 11/18/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveCondition__
#define __CppRete__NaiveCondition__

#include "Namespaces.h"
#include "ICondition.h"
#include <string>

NAMESPACE_RETE_BEGIN
class IAlphaNodeTest;
NAMESPACE_RETE_END

NAMESPACE_RETE_ALG_BEGIN
class IAlphaNetworkFactory;

class NaiveCondition : public ICondition
{
public:
    NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, long valAttrType, long valAttrVal);
    NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, long valAttrType, long valAttrVal);
    NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, long valAttrType, std::string varAttrVal);
    NaiveCondition(IAlphaNetworkFactory* pFactory, std::string varID, std::string varAttrType, std::string varAttrVal);
    NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, std::string varAttrType, std::string varAttrVal);
    NaiveCondition(IAlphaNetworkFactory* pFactory, long valID, long valAttrType, std::string varAttrVal);
    
    virtual ~NaiveCondition();
    
    // Inherited from ICondition
    virtual NAMESPACE_RETE::IAlphaNodeTest* GetAlphaTestNode() const;
    virtual NAMESPACE_RETE::IAlphaNodeTest* GetAlphaTestAttributeTypeNode() const;
    virtual void GetAllVariables(std::list<std::string>& vecVariables) const;
    
    virtual bool HasVariableIdentifierOf(const std::string& varName) const;
    virtual bool HasVariableIdentifier() const;
    virtual long GetConstantIdentifierValue() const;
    
    virtual bool HasAtLeastOneConstantAttributeType() const;
    virtual bool HasConstantAttributeType(long attrType) const;
    virtual void GetAllConstantAttrTypes(std::list<long>& vecAttrTypeIDs) const;
    
    virtual bool HasAtLeastOneConstantAttributeValue() const;
    virtual bool HasConstantAttributeValue(long attrType) const;
    virtual void GetAllConstantAttrValues(std::list<long>& vecAttrTypeIDs, std::unordered_map<long, long>& mapAttrValuesForTypes) const;
    
    virtual bool HasAttributeTypeWithVariableName(const std::string& varName) const;
    virtual long GetAttributeIndexWithVariableName(const std::string& varName) const;
    
    virtual long GetValueIndexWithVariableName(const std::string& varName) const;
    
    virtual long GetNumAttributes() const;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const ICondition& rhs) const;
    
protected:
    IAlphaNetworkFactory* m_pFactory;
    bool m_bHasVariableID;
    bool m_bHasVariableAttrType;
    bool m_bHasVariableAttrValue;
    std::string m_varID;
    long m_lValID;
    std::string m_varAttrType;
    long m_lValAttrType;
    std::string m_varAttrValue;
    long m_lValAttrValue;
    
private:
    // Disallow copying
    NaiveCondition& operator=(const NaiveCondition&);
    NaiveCondition(const NaiveCondition&);
};
NAMESPACE_RETE_ALG_END

#endif /* defined(__CppRete__NaiveCondition__) */
