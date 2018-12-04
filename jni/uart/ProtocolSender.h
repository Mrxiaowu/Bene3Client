//Bene3

#ifndef _UART_PROTOCOL_SENDER_H_
#define _UART_PROTOCOL_SENDER_H_

#include "CommDef.h"
#include "../include/utils/Log.h"

//bool sendProtocol(const UINT16 cmdID,const BYTE *pData, BYTE len);

bool sendProtocol( const BYTE *pData, BYTE len);

#endif /* _UART_PROTOCOL_SENDER_H_ */
