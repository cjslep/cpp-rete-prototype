//
//  ExportedFunctions.h
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_ExportedFunctions_h
#define CppRete_ExportedFunctions_h

/*
 
 Included in NaiveReteController.h
 
 */

#include "Namespaces.h"

EXPORT
IReteController* NewReteController()
{
    return new NaiveReteController();
}

EXPORT
void DeleteReteController(IReteController* pController)
{
    delete pController;
}

#endif
