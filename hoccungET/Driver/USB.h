#ifndef __USB_H
#define __USB_H
#include <stdint.h>
//------------------------TYPEDEF---------------------------------------------
#define __IO   volatile
typedef enum{
	RESET = 0,
	SET = !RESET
}FlagStatus;

typedef struct {
    union {
        __IO uint32_t WORD;
        struct {
            __IO uint32_t EA         : 4;
            __IO uint32_t STAT_TX    : 2;
            __IO uint32_t DTOG_TX    : 1;
            __IO uint32_t CTR_TX     : 1;
            __IO uint32_t EP_KIND    : 1;
            __IO uint32_t EPTYPE     : 2;
            __IO uint32_t SETUP      : 1;
            __IO uint32_t STAT_RX    : 2;
            __IO uint32_t DTOG_RX    : 1;
            __IO uint32_t CTR_RX     : 1;
        } BITS;
    } EPnRp[8];

    uint32_t                    : 32;   /* 0x20 */
    uint32_t                    : 32;   /* 0x24 */
    uint32_t                    : 32;   /* 0x28 */
    uint32_t                    : 32;   /* 0x2C */
    uint32_t                    : 32;   /* 0x30 */
    uint32_t                    : 32;   /* 0x34 */
    uint32_t                    : 32;   /* 0x38 */
    uint32_t                    : 32;   /* 0x3C */

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t FRES       : 1;
            __IO uint32_t PDWN       : 1;
            __IO uint32_t LPMODE     : 1;
            __IO uint32_t FSUSP      : 1;
            __IO uint32_t RESUME     : 1;
            __IO uint32_t            : 3;
            __IO uint32_t ESOFM      : 1;
            __IO uint32_t SOFM       : 1;
            __IO uint32_t RESETM     : 1;
            __IO uint32_t SUSPM      : 1;
            __IO uint32_t WKUPM      : 1;
            __IO uint32_t ERRM       : 1;
            __IO uint32_t PMAOVRM    : 1;
            __IO uint32_t CTRM       : 1;
        } BITS;
    } CNTR;

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t EP_ID      : 4;
            __IO uint32_t DIR        : 1;
            __IO uint32_t            : 3;
            __IO uint32_t ESOF       : 1;
            __IO uint32_t SOF        : 1;
            __IO uint32_t RESET      : 1;
            __IO uint32_t SUSP       : 1;
            __IO uint32_t WKUP       : 1;
            __IO uint32_t ERR        : 1;
            __IO uint32_t PMAOVR     : 1;
            __IO uint32_t CTR        : 1;
        } BITS;
    } ISTR;

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t FN         : 11;
            __IO uint32_t LSOF       : 2;
            __IO uint32_t LCK        : 1;
            __IO uint32_t RXDM       : 1;
            __IO uint32_t RXDP       : 1;
        } BITS;
    } FNR;

    union {
        __IO uint32_t WORD;

        struct
        {
            __IO uint32_t ADD        : 7;
            __IO uint32_t EF         : 1;
        } BITS;
    } DADDR;

    __IO uint32_t BTABLE;
} USB_Typedef;

typedef struct {
    union
    {
        uint8_t byte;

        struct {
            uint8_t recipient   : 5;    /* 0 = Device
                                           1 = Interface
                                           2 = Endpoint
                                           3 = Other
                                           4...31 = Reserved */

            uint8_t type        : 2;    /* 0 = Standard
                                           1 = Class
                                           2 = Vendor
                                           3 = Reserved */

            uint8_t dir         : 1;    /* 0 = Host-to-device
                                           1 = Device-to-hos */
        } bits;
    } bmRequestType;

    uint8_t     bRequest;
    uint16_t    wValue;
    uint16_t    wIndex;
    uint16_t    wLength;
} USB_RequestTypedef;




#define USB_SET_TYPE_TRANSFER(USBx, EP, TYPE)                       \
     do {                                                           \
         register uint16_t wValReg = 0;                             \
         wValReg = (USBx->EPnRp[EP].WORD & 0x8F8F) | ((TYPE) << 9); \
         USBx->EPnRp[EP].WORD = wValReg;                            \
     } while (0)                                                    \


#define USB_SET_ENDPOINT_ADDRESS(USBx, EP)                          \
     do {                                                           \
         register uint16_t wValReg = 0;                             \
         wValReg = (USBx->EPnRp[EP].WORD & 0x8F8F) | (EP);          \
         USBx->EPnRp[EP].WORD = wValReg;                            \
     } while (0)                                                    \

#define USB_SET_STAT_RX(USBx, EP, STS)                          \
    do                                                          \
    {                                                           \
        register uint16_t _wRegVal = 0;                         \
        _wRegVal = (USBx->EPnRp[EP].BITS.STAT_RX ^ STS) << 12;  \
        _wRegVal = _wRegVal | (USBx->EPnRp[EP].WORD & 0x8F8F);  \
        USBx->EPnRp[EP].WORD = _wRegVal;                        \
    } while (0)                                                 \

//
#define USB_DATA_TGL_RX(USBx, EP, TGL)                          \
    do                                                          \
    {                                                           \
        register uint16_t _wRegVal = 0;                         \
        _wRegVal = (USBx->EPnRp[EP].BITS.DTOG_RX ^ TGL) << 14;  \
        _wRegVal = _wRegVal | (USBx->EPnRp[EP].WORD & 0x8F8F);  \
        USBx->EPnRp[EP].WORD = _wRegVal;                        \
    } while (0)                                                 \


#define USB_SET_STAT_TX(USBx, EP, STS)                          \
    do                                                          \
    {                                                           \
        register uint16_t _wRegVal = 0;                         \
        _wRegVal = (USBx->EPnRp[EP].BITS.STAT_TX ^ STS) << 4;   \
        _wRegVal = _wRegVal | (USBx->EPnRp[EP].WORD & 0x8F8F);  \
        USBx->EPnRp[EP].WORD = _wRegVal;                        \
    } while (0)                                                 \

#define USB_DATA_TGL_TX(USBx, EP, TGL)                          \
    do                                                          \
    {                                                           \
        register uint16_t _wRegVal = 0;                         \
        _wRegVal = (USBx->EPnRp[EP].BITS.DTOG_TX ^ TGL) << 6;   \
        _wRegVal = _wRegVal | (USBx->EPnRp[EP].WORD & 0x8F8F);  \
        USBx->EPnRp[EP].WORD = _wRegVal;                        \
    } while (0)                                                 \


#define CLEAR_TRANSFER_TX_FLAG(USBx, EP)                            \
     do {                                                           \
         register uint16_t wValReg = 0;                             \
         wValReg = (USBx->EPnRp[EP].WORD & 0x8F8F) & ~(1 << 7);     \
         USBx->EPnRp[EP].WORD = wValReg;                            \
     } while (0)                                                    \

#define CLEAR_TRANSFER_RX_FLAG(USBx, EP)                            \
     do {                                                           \
         register uint16_t wValReg = 0;                             \
         wValReg = (USBx->EPnRp[EP].WORD & 0x8F8F) & ~(1 << 15);    \
         USBx->EPnRp[EP].WORD = wValReg;                            \
     } while (0)





//-------------------------------------MACRO---------------------------------------------	 

#define USB_ADDR_TX(ep)                    (*(uint16_t*)(((ep*8)*2) + 0x40006000))
#define USB_COUNT_TX(ep)                   (*(uint16_t*)((((ep*8U) + 2U)*2) + 0x40006000))
#define USB_ADDR_RX(ep)                    (*(uint16_t*)((((ep*8) + 4U)*2) + 0x40006000))
#define USB_COUNT_RX(ep)                   (*(uint16_t*)((((ep*8U) + 6U)*2) + 0x40006000))	


#define USB_ADDR0_TX                            (USB_ADDR_TX(0))
#define USB_COUNT0_TX                           (USB_COUNT_TX(0))
#define USB_ADDR0_RX                            (USB_ADDR_RX(0))
#define USB_COUNT0_RX                           (USB_COUNT_RX(0))
		 
		 
#define HIBYTE(x)                               ((uint8_t)((x & 0xFF00) >>8))
#define LOBYTE(x)                               ((uint8_t)(x & 0x00FF))

		 
		 
//-------------------------DEFINE------------------------
//Transminssion status
#define STATUS_TX_DISABLE		0x00
#define STATUS_TX_STALL		  0x01
#define STATUS_TX_NAK		    0x02
#define STATUS_TX_VALID		  0x03
		
//Reception status
#define STATUS_RX_DISABLE		0x00
#define STATUS_RX_STALL		  0x01
#define STATUS_RX_NAK		    0x02
#define STATUS_RX_VALID		  0x03

//Data toggle 
#define DATA_TGL_0				0x00
#define DATA_TGL_1				0x01

//EP type
#define ENDPOINT_TYPE_BULK                      0x00
#define ENDPOINT_TYPE_CONTROL                   0x01
#define ENDPOINT_TYPE_ISO                       0x02
#define ENDPOINT_TYPE_INTERRUPT                 0x03
		 
#define USB_MAX_EP_PACKET_SIZE									0x40

// Standard Device Requests
#define GET_STATUS                              0x00
#define CLEAR_FEATURE                           0x01
#define SET_FEATURE                             0x03
#define SET_ADDRESS                             0x05
#define GET_DESCRIPTOR                          0x06
#define SET_DESCRIPTOR                          0x07
#define GET_CONFIGURATION                       0x08
#define SET_CONFIGURATION                       0x09
#define GET_INTERFACE                           0x0A
#define SET_INTERFACE                           0x0B
#define SYNCH_FRAME                             0x0C

// Descriptor Types
#define DEVICE_TYPE                             0x01
#define CONFIGURATION_TYPE                      0x02
#define STRING_TYPE                             0x03
#define INTERFACE_TYPE                          0x04
#define ENDPOINT_TYPE                           0x05
#define DEVICE_QUALIFIER_TYPE                   0x06
#define OTHER_SPEED_CONFIGURATION_TYPE          0X07
#define INTERFACE_POWER                         0x08

// Device Descriptor
#define MAX_SIZE_DEVICE_DESCRIPTOR              0x12
#define USB_MAX_EP0_SIZE                        0x40
#define USB_DEVICE_CLASS                        0x02
#define USB_DEVICE_SUB_CLASS                    0x00
#define USB_DEVICE_PROTOCOL                     0x00
#define USBD_VID                                0x1234
#define USBD_PID_FS                             0x5678
#define USBD_MAX_NUM_CONFIGURATION              1

// String Index
#define USBD_MAX_STR_DESC_SIZ                   512
#define USBD_IDX_LANGID_STR                     0x00 
#define USB_LEN_LANGID_STR_DESC                 0x04
#define USBD_LANGID_STRING                      1033
#define USBD_IDX_MFC_STR                        0x01 
#define USBD_MANUFACTURER_STRING                "STMicroelectronics"
#define USBD_IDX_PRODUCT_STR                    0x02
#define USBD_PRODUCT_STRING_FS                  "Logan"
#define USBD_IDX_SERIAL_STR                     0x03 
#define USBD_SERIALNUMBER_STRING_FS             "00000000001A"
#define USBD_IDX_CONFIG_STR                     0x04 
#define USBD_CONFIGURATION_STRING_FS            "CDC Config"
#define USBD_IDX_INTERFACE_STR                  0x05
#define USBD_INTERFACE_STRING_FS                "CDC Interface"

// Configuration Descriptor
#define MAX_SIZE_CONFIG_DESCRIPTOR              0x09
#define USB_CONFIG_DESC_LEN                     0x20

#define USB_MAX_EP_PACKET_SIZE                  0x40

// Recipient type
#define USB_REQ_RECIP_DEVICE                    0x00
#define USB_REQ_RECIP_INTERACE                  0x01
#define USB_REQ_RECIP_ENDP                      0x02

//---------------------------------------------DEFINE FOR CDC-------------------------------
		 
typedef struct _CDC_LINE_CODING_TYPE {
    uint32_t baudrate;              // baud rate
    uint8_t  stopbits;              // number of stopbits (0:1bit,1:1.5bits,2:2bits)
    uint8_t  parity;                // parity (0:none,1:odd,2:even,3:mark,4:space)
    uint8_t  databits;              // number of data bits (5,6,7,8 or 16)
} CDC_LINE_CODING_TYPE;
		 
#define CDC_IN_EP                               0x81  /* EP1 for data IN */
#define CDC_OUT_EP                              0x01  /* EP1 for data OUT */
#define CDC_CMD_EP                              0x82  /* EP2 for CDC commands */
#define CDC_CMD_PACKET_SIZE                     0x08  /* Control Endpoint Packet size */
#define CDC_DATA_FS_MAX_PACKET_SIZE             0x40  /* Endpoint IN & OUT Packet size */
#define MAX_SIZE_COM_CONFIG                     0x07
#define CDC_DATA_FS_IN_PACKET_SIZE              CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_DATA_FS_OUT_PACKET_SIZE             CDC_DATA_FS_MAX_PACKET_SIZE
#define CDC_GET_LINE_CODING                     0x21
#define CDC_SET_LINE_CODING                     0x20
#define CDC_SET_LINE_CTLSTE                     0x22
#define CDC_SEND_BREAK                          0x23
#undef USB_CONFIG_DESC_LEN
#define USB_CONFIG_DESC_LEN                     67

// Request type
#define USB_REQ_TYP_STANDARD                    0x00
#define USB_REQ_TYP_CLASS                       0x01
#define USB_REQ_TYP_VENDOR                      0x02
		 
//--------------------------VAR--------------------------

#define USB_ADD_BASE        0x40005C00
#define USB                 ((USB_Typedef*)(USB_ADD_BASE))


void USB_Init(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void USB_TransactionCallBack(void);
void USB_ResetCallBack(void);
void CDC_Transmit(uint8_t* data, uint8_t length);
uint16_t CDC_Receive(uint8_t* data);
#endif
