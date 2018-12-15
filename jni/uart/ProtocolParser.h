//Bene3
#ifndef _UART_PROTOCOL_PARSER_H_
#define _UART_PROTOCOL_PARSER_H_

#include "ProtocolData.h"
#include "uart/ProtocolParser.h"
#include "uart/ProtocolSender.h"
#include "include/entry/EasyUIContext.h"

typedef void (*OnProtocolDataUpdateFun)(const SProtocolData &data);

void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener);
void unregisterProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener);

SProtocolData& getProtocolData();

void hex_to_str(char *ptr,unsigned char *buf,int len);

void BYTEToString();

#endif /* _UART_PROTOCOL_PARSER_H_ */
