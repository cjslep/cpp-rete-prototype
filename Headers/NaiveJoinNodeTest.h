//
//  NaiveJoinNodeTest.h
//  CppRete
//
//  Created by Cory Slep on 11/10/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveJoinNodeTest__
#define __CppRete__NaiveJoinNodeTest__

#include "IJoinNodeTest.h"

NAMESPACE_RETE_BEGIN

class NaiveJoinNodeTest : public IJoinNodeTest
{
public:
    NaiveJoinNodeTest(long fieldWMEfromToken, long fieldWME, long tokenIndex);
    virtual ~NaiveJoinNodeTest();
    
    virtual bool Test(const NAMESPACE_TUPLE::IToken& aToken, const NAMESPACE_TUPLE::IWME& aWME) const;
    
    virtual long GetTokenIndex() const;
    virtual long GetAttributeIndexWME() const;
    virtual long GetAttributeIndexToken() const;
    
    virtual bool Equals(const IJoinNodeTest& rhs) const;
protected:
    long m_tokenIndex;
    long m_fieldWME;
    long m_fieldWMEfromToken;
    
private:
    // Disallow copying
    NaiveJoinNodeTest& operator=(const NaiveJoinNodeTest&);
    NaiveJoinNodeTest(const NaiveJoinNodeTest&);
};

NAMESPACE_RETE_END

#endif /* defined(__CppRete__NaiveJoinNodeTest__) */
