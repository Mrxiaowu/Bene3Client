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

#endif /* _UART_PROTOCOL_PARSER_H_ */
