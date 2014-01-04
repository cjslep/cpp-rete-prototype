//
//  NaiveTokenFactory.cpp
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveTokenFactory.h"
#include "NaiveToken.h"


NAMESPACE_TUPLE_OVRHD::NaiveTokenFactory::NaiveTokenFactory()
{
    
}

NAMESPACE_TUPLE_OVRHD::NaiveTokenFactory::~NaiveTokenFactory()
{
    
}

NAMESPACE_TUPLE::IToken* NAMESPACE_TUPLE_OVRHD::NaiveTokenFactory::CreateNewTokenFromWME(NAMESPACE_TUPLE::IWME& aWME) const
{
    return new NaiveToken(&aWME);
}