/*
 * PROJECT:     ReactOS Intel PRO/1000 Driver
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     Intel PRO/1000 driver definitions
 * COPYRIGHT:   Copyright 2013 Cameron Gutman (cameron.gutman@reactos.org)
 *              Copyright 2018 Mark Jansen (mark.jansen@reactos.org)
 */

#ifndef _E1000_PCH_
#define _E1000_PCH_

#include <ndis.h>

#include "e1000hw.h"

#define E1000_TAG '001e'

#define MAXIMUM_FRAME_SIZE 1522
#define RECEIVE_BUFFER_SIZE          2048

#define DRIVER_VERSION 1


#define DEFAULT_INTERRUPT_MASK      (E1000_IMS_LSC | E1000_IMS_TXDW | E1000_IMS_RXDMT0 | E1000_IMS_RXT0)

typedef struct _E1000_ADAPTER
{
    NDIS_SPIN_LOCK Lock;
    NDIS_HANDLE AdapterHandle;
    USHORT VendorID;
    USHORT DeviceID;
    USHORT SubsystemID;
    USHORT SubsystemVendorID;

    UCHAR PermanentMacAddress[IEEE_802_ADDR_LENGTH];
    struct {
        UCHAR MacAddress[IEEE_802_ADDR_LENGTH];
    } MulticastList[MAXIMUM_MULTICAST_ADDRESSES];

    ULONG LinkSpeedMbps;
    ULONG MediaState;
    ULONG PacketFilter;

    /* Io Port */
    ULONG IoPortAddress;
    ULONG IoPortLength;
    volatile PUCHAR IoPort;

    /* NIC Memory */
    NDIS_PHYSICAL_ADDRESS IoAddress;
    ULONG IoLength;
    volatile PUCHAR IoBase;

    /* Interrupt */
    ULONG InterruptVector;
    ULONG InterruptLevel;
    BOOLEAN InterruptShared;
    ULONG InterruptFlags;

    NDIS_MINIPORT_INTERRUPT Interrupt;
    BOOLEAN InterruptRegistered;

    ULONG InterruptMask;
    ULONG InterruptPending;


    /* Transmit */
    PE1000_TRANSMIT_DESCRIPTOR TransmitDescriptors;
    NDIS_PHYSICAL_ADDRESS TransmitDescriptorsPa;

    ULONG CurrentTxDesc;
    ULONG LastTxDesc;
    BOOLEAN TxFull;


    /* Receive */
    PE1000_RECEIVE_DESCRIPTOR ReceiveDescriptors;
    NDIS_PHYSICAL_ADDRESS ReceiveDescriptorsPa;

    ULONG CurrentRxDesc;

    E1000_RCVBUF_SIZE ReceiveBufferType;
    volatile PUCHAR ReceiveBuffer;
    NDIS_PHYSICAL_ADDRESS ReceiveBufferPa;
    ULONG ReceiveBufferEntrySize;

} E1000_ADAPTER, *PE1000_ADAPTER;


BOOLEAN
NTAPI
NICRecognizeHardware(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICInitializeAdapterResources(
    IN PE1000_ADAPTER Adapter,
    IN PNDIS_RESOURCE_LIST ResourceList);

NDIS_STATUS
NTAPI
NICAllocateIoResources(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICRegisterInterrupts(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICUnregisterInterrupts(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICReleaseIoResources(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICPowerOn(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICSoftReset(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICEnableTxRx(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICDisableTxRx(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICGetPermanentMacAddress(
    IN PE1000_ADAPTER Adapter,
    OUT PUCHAR MacAddress);

NDIS_STATUS
NTAPI
NICUpdateMulticastList(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICApplyPacketFilter(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICApplyInterruptMask(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICDisableInterrupts(
    IN PE1000_ADAPTER Adapter);

ULONG
NTAPI
NICInterruptRecognized(
    IN PE1000_ADAPTER Adapter,
    OUT PBOOLEAN InterruptRecognized);

VOID
NTAPI
NICUpdateLinkStatus(
    IN PE1000_ADAPTER Adapter);

NDIS_STATUS
NTAPI
NICTransmitPacket(
    IN PE1000_ADAPTER Adapter,
    IN ULONG PhysicalAddress,
    IN ULONG Length);

NDIS_STATUS
NTAPI
MiniportSetInformation(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN NDIS_OID Oid,
    IN PVOID InformationBuffer,
    IN ULONG InformationBufferLength,
    OUT PULONG BytesRead,
    OUT PULONG BytesNeeded);

NDIS_STATUS
NTAPI
MiniportQueryInformation(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN NDIS_OID Oid,
    IN PVOID InformationBuffer,
    IN ULONG InformationBufferLength,
    OUT PULONG BytesWritten,
    OUT PULONG BytesNeeded);

VOID
NTAPI
MiniportISR(
    OUT PBOOLEAN InterruptRecognized,
    OUT PBOOLEAN QueueMiniportHandleInterrupt,
    IN NDIS_HANDLE MiniportAdapterContext);

VOID
NTAPI
MiniportHandleInterrupt(
    IN NDIS_HANDLE MiniportAdapterContext);


VOID
NTAPI
E1000WriteUlong(
    IN PE1000_ADAPTER Adapter,
    IN ULONG Address,
    IN ULONG Value);



#endif /* _E1000_PCH_ */