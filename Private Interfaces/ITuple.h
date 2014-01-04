//
//  ITuple.h
//  CppRete
//
//  Created by Cory Slep on 9/22/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ITuple_h
#define CppRete_ITuple_h

#include "Namespaces.h"


NAMESPACE_TUPLE_BEGIN

static const long k_InvalidTIndex = -1;

class Identifier
{
public:
    Identifier (long id) : m_lId(id) {}
    long GetValue() const {return m_lId;}
private:
    long m_lId;
};

class Attribute
{
public:
    Attribute (long type, long value) : m_lType(type), m_lValue(value) {}
    long GetValue() const {return m_lValue;}
    long GetType() const {return m_lType;}
private:
    long m_lType;
    long m_lValue;
};

class ITuple
{
public:
    virtual ~ITuple() {}
    
    virtual long GetIdentifier() const = 0;
    virtual long GetAttribute(long attrIndex) const = 0;
    virtual long GetValue(long attrIndex) const = 0;
    virtual long GetNumAttributes() const = 0;
    
    virtual void SetID(long tupleID) = 0;
    virtual bool SetAttr(long attr, long attrIndex) = 0;
    virtual bool SetValue(long value, long attrIndex) = 0;
    
    // Clients use operators instead of the following functions
    virtual bool Equals(const ITuple& rhs) const = 0;
    virtual bool LessThan(const ITuple& rhs) const = 0;
};

NAMESPACE_TUPLE_END

inline bool operator==(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return lhs.Equals(rhs);}
inline bool operator!=(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return !lhs.Equals(rhs);}
inline bool operator<(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return lhs.LessThan(rhs);}
inline bool operator>(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return rhs.LessThan(lhs);}
inline bool operator<=(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return !rhs.LessThan(lhs);}
inline bool operator>=(const NAMESPACE_TUPLE::ITuple& lhs, const NAMESPACE_TUPLE::ITuple& rhs) {return !lhs.LessThan(rhs);}


#endif
