//
//  Triple.h
//  CppRete
//
//  Created by Cory Slep on 9/23/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__Triple__
#define __CppRete__Triple__

#include "Namespaces.h"
#include "ITuple.h"

NAMESPACE_TUPLE_BEGIN

class Triple : public ITuple
{
public:
    Triple(long tupleID);
    Triple(long tupleID, long attr, long value);
    virtual ~Triple();
    
    virtual long GetIdentifier() const;
    virtual long GetAttribute(long attrIndex) const;
    virtual long GetValue(long attrIndex) const;
    virtual long GetNumAttributes() const;
    
    virtual void SetID(long tupleID);
    virtual bool SetAttr(long attr, long attrIndex);
    virtual bool SetValue(long value, long attrIndex);
    
    virtual bool Equals(const ITuple& rhs) const;
    virtual bool LessThan(const ITuple& rhs) const;
protected:
    long m_identifier;
    long m_attribute;
    long m_value;
private:
    // Disallow copying
    Triple& operator=(const Triple&);
    Triple(const Triple&);
};

NAMESPACE_TUPLE_END

#endif /* defined(__CppRete__Triple__) */
