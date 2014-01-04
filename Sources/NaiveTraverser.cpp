//
//  NaiveTraverser.cpp
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#include "NaiveTraverser.h"
#include "IToken.h"
#include <stdio.h>

NAMESPACE_TUPLE_ALG::NaiveTraverser::NaiveTraverser()
{
    
}

NAMESPACE_TUPLE_ALG::NaiveTraverser::~NaiveTraverser()
{
    
}

void NAMESPACE_TUPLE_ALG::NaiveTraverser::RemoveWMEInToken(NAMESPACE_TUPLE::IToken* pToken)
{
    pToken->TraversedBy(this);
}

void NAMESPACE_TUPLE_ALG::NaiveTraverser::RemoveTokenAndDescendants(NAMESPACE_TUPLE::IToken* pToken)
{
    pToken->TraversedBy(this);
    delete pToken;
    pToken = NULL;
}