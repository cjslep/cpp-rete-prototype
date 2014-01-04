//
//  IProductionSubscriber.h
//  CppRete
//
//  Created by Cory Slep on 12/8/13.
//  Copyright (c) 2013 Cory Slep. All rights reserved.
//

#ifndef CppRete_IProductionSubscriber_h
#define CppRete_IProductionSubscriber_h

struct IProductionSubscriber
{
public:
    virtual ~IProductionSubscriber() {};
    /*
     2D array.
      
     +-+-+-+
     | | | | numTableColsAtRow[0]
     +-+-+-+-+-+-+-+
     | | | | | | | | numTableColsAtRow[1]
     +-+-+-+-+-+-+-+
     | | | | | | numTableColsAtRow[2]
     +-+-+-+-+-+
     numTableRows
     
     In general each row will be in the format:
     | ID |[ ATTR TYPE | VAL TYPE ]
     where multiple attribute/value pairs can exist in a row
     */
    virtual void ProductionExecuted(long prodNumber, long** pDataTable, long* numTableColsAtRow, long numTableRows) = 0;
};

class ProductionSubscriber : public IProductionSubscriber
{
public:
    ProductionSubscriber() {}
    virtual ~ProductionSubscriber() {}
    virtual void ProductionExecuted(long prodNumber, long** pDataTable, long* numTableColsAtRow, long numTableRows) {}
};

#endif
