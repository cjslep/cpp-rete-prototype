//
//  NaiveTokenFactory.h
//  CppRete
//
//  Created by Cory Slep on 10/30/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef __CppRete__NaiveTokenFactory__
#define __CppRete__NaiveTokenFactory__

#include "Namespaces.h"
#include "ITokenFactory.h"

NAMESPACE_TUPLE_OVRHD_BEGIN

class NaiveTokenFactory : public ITokenFactory
{
public:
    NaiveTokenFactory();
    virtual ~NaiveTokenFactory();
    
    virtual IToken* CreateNewTokenFromWME(IWME& aWME) const;
    
private:
    // Disallow copying
    NaiveTokenFactory& operator=(const NaiveTokenFactory&);
    NaiveTokenFactory(const NaiveTokenFactory&);
};

NAMESPACE_TUPLE_OVRHD_END


#endif /* defined(__CppRete__NaiveTokenFactory__) */
