#pragma once

#include <iostream>
#include <netinet/in.h>

struct Ipv4Header 
{
    uint8_t versionAndHeaderLength;  // version(4) + headerLength(4)
    uint8_t typeOfService;
    uint16_t totalLength;
    uint16_t identification;
    uint16_t flagsAndFragmentOffset; // flags(3) + framgmentOffset(13);
    uint8_t timeToLive;
    uint8_t protocol;
    uint16_t headerCheckSum;
    in_addr source;
    in_addr destination;
};

struct TcpHeader
{
    uint16_t sourcePort;
    uint16_t destinationPort;
    uint32_t sequenceNumber;
    uint32_t acknowledgeNumber;
    uint16_t dataOffsetAndFlags;  // data offset(4) + reserved(6) + flags(6)
    uint16_t windowSize;
    uint16_t checkSum;
    uint16_t urgentPointer;
};