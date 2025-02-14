#include "mouse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "byteorder.h"
#include "cdn_log.h"
#include "cdn_errno.h"

//static CH9_UsbSpeed sMaxSpeed = CH9_USB_SPEED_UNKNOWN;
static CH9_UsbSpeed sDevSpeed = CH9_USB_SPEED_UNKNOWN;

static uint8_t cusbdss_epCfgMode = CH9_USB_EP_INTERRUPT;

// function return unicode string for english version
static void get_unicode_string(char * target, const char * src) {

    size_t src_len = strlen(src) * 2;
    int i;

    *target++ = src_len + 2;
    *target++ = CH9_USB_DT_STRING;

    if (src_len > 100) {
        src_len = 100;
    }
    for (i = 0; i < src_len; i += 2) {
        *target++ = *src++;
        *target++ = 0;
    }
}


//------------------- descriptor set--------------------------------------------
// device descriptor for SuperSpeed mode
static CH9_UsbDeviceDescriptor devSsDesc = {
    .bLength = CH9_USB_DS_DEVICE,
    .bDescriptorType = CH9_USB_DT_DEVICE,
    .bcdUSB = cpuToLe16(BCD_USB_SS),
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 9,
    .idVendor = cpuToLe16(ID_VENDOR),
    .idProduct = cpuToLe16(ID_PRODUCT),
    .bcdDevice = cpuToLe16(BCD_DEVICE_SS),
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1
};

struct usb_hid_interface_descriptor {
    uint8_t bLength; /**< Descriptor size */
    uint8_t bDescriptorType; /**< INTERFACE: 8 bit DESCR_TYPE value */
    uint16_t bcdHID; /**< HID Class specification release */
    uint8_t bCountryCode; /**< Country code of the localized hardware */
    uint8_t bNumDescriptors; /**< Number of class descriptors count */
    uint8_t bDescriptorType2; /**< Type of class descriptor */
    uint16_t wDescriptorLength; /**< Size of the Report descriptor */
} __attribute__((packed));

// device descriptor for HighSpeed mode
static CH9_UsbDeviceDescriptor devHsDesc = {
    .bLength = CH9_USB_DS_DEVICE,
    .bDescriptorType = CH9_USB_DT_DEVICE,
    .bcdUSB = cpuToLe16(BCD_USB_HS),
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = cpuToLe16(ID_VENDOR),
    .idProduct = cpuToLe16(ID_PRODUCT),
    .bcdDevice = cpuToLe16(BCD_DEVICE_HS),
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1
};
//------------- Start of Super Speed configuration descriptors -----------------
// configuration descriptors for SuperSpeed mode
static CH9_UsbConfigurationDescriptor confSsDesc = {
    .bLength = CH9_USB_DS_CONFIGURATION,
    .bDescriptorType = CH9_USB_DT_CONFIGURATION,
    .wTotalLength = cpuToLe16(
    CH9_USB_DS_CONFIGURATION
    + CH9_USB_DS_INTERFACE
    + CH9_USB_DS_ENDPOINT
    + CH9_USB_DS_SS_USB_EP_COMPANION
    + sizeof (struct usb_hid_interface_descriptor)),
    .bNumInterfaces = 1,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = CH9_USB_CONFIG_RESERVED | CH9_USB_CONFIG_SELF_POWERED,
    .bMaxPower = 1
};

//0x09, 0x04, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00,
static CH9_UsbInterfaceDescriptor interfaceDesc = {
    .bLength = CH9_USB_DS_INTERFACE,
    .bDescriptorType = CH9_USB_DT_INTERFACE,
    .bInterfaceNumber = 0,
    .bAlternateSetting = 0,
    .bNumEndpoints = 1,
    .bInterfaceClass = CH9_USB_CLASS_HID,
    .bInterfaceSubClass = 0,
    .bInterfaceProtocol = 0,
    .iInterface = 0
};

//0x09, 0x21, 0x01, 0x01, 0x00, 0x01, 0x22, 50, 0x00,
static struct usb_hid_interface_descriptor hidInterfaceDesc = {
    .bLength = 0x09,
    .bDescriptorType = 0x21,
    .bcdHID = cpuToLe16(0x0101),
    .bCountryCode = 0x00,
    .bNumDescriptors = 0x01,
    .bDescriptorType2 = 0x22,
    .wDescriptorLength = cpuToLe16(50)
};


//0x07, 0x05, MOUSE_EP_ADDRES_IN, 0x03, 0x03, 0x00, 0x07,
static CH9_UsbEndpointDescriptor endpointDesc = {
    .bLength = CH9_USB_DS_ENDPOINT,
    .bDescriptorType = CH9_USB_DT_ENDPOINT,
    .bEndpointAddress = MOUSE_EP_ADDRES_IN,
    .bmAttributes = CH9_USB_EP_INTERRUPT,
    .wMaxPacketSize = cpuToLe16(64),
    .bInterval = 1
};

//0x06, 0x30, 0x00, 0x00, 0x00, 0x00
static CH9_UsbSSEndpointCompanionDescriptor compDesc = {
    .bLength = CH9_USB_DS_SS_USB_EP_COMPANION,
    .bDescriptorType = CH9_USB_DT_SS_USB_EP_COMPANION,
    .bMaxBurst = 0,
    .bmAttributes = 0,
    .wBytesPerInterval = cpuToLe16(0)
};
//------------------- End of Super Speed configuration -------------------------

//------------- Start of High Speed configuration descriptors -----------------
// configuration descriptors for HighSpeed mode
static CH9_UsbConfigurationDescriptor confHsDesc = {
    .bLength = CH9_USB_DS_CONFIGURATION,
    .bDescriptorType = CH9_USB_DT_CONFIGURATION,
    .wTotalLength = cpuToLe16(
    CH9_USB_DS_CONFIGURATION
    + CH9_USB_DS_INTERFACE
    + CH9_USB_DS_ENDPOINT
    + CH9_USB_DS_OTG
    + sizeof (struct usb_hid_interface_descriptor)),
    .bNumInterfaces = 1,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = CH9_USB_CONFIG_RESERVED | CH9_USB_CONFIG_SELF_POWERED,
    .bMaxPower = 0
};

static CH9_UsbOtgDescriptor otgDesc =  {
    .bLength = CH9_USB_DS_OTG,
    .bDescriptorType = CH9_USB_DT_OTG,
    .bmAttributes = /*CH9_USB_OTG_ADP_MASK | CH9_USB_OTG_HNP_MASK | */ CH9_USB_OTG_SRP_MASK, // Modified by Chirag after mail from Pawel dated Appril 11,2018
	//.bmAttributes = /*CH9_USB_OTG_ADP_MASK |*/ CH9_USB_OTG_HNP_MASK |  CH9_USB_OTG_SRP_MASK,
    .bcdOTG = cpuToLe16(0x0200)
} ;

// language descriptor for english
static uint8_t languageDesc[] = {
    4, CH9_USB_DT_STRING, 0x09, 0x04
};

// string will be filled then in initializing section
static char vendorDesc[sizeof (USB_MANUFACTURER_STRING)*2 + 2];
static char productDesc[sizeof (USB_PRODUCT_STRING)*2 + 2];
static char serialDesc[sizeof (USB_SERIAL_NUMBER_STRING)*2 + 2];

//-------------- BOS descriptor set start --------------------------------------

static CH9_UsbBosDescriptor bosDesc = {
    .bLength = CH9_USB_DS_BOS,
    .bDescriptorType = CH9_USB_DT_BOS,
    .wTotalLength = cpuToLe16(CH9_USB_DS_BOS + CH9_USB_DS_DEVICE_CAPABILITY_30 + CH9_USB_DS_DEVICE_CAPABILITY_20),
    .bNumDeviceCaps = 2
};

static CH9_UsbSSDeviceCapabilityDescriptor capabilitySsDesc = {
    .bLength = CH9_USB_DS_DEVICE_CAPABILITY_30,
    .bDescriptorType = CH9_USB_DT_DEVICE_CAPABILITY,
    .bDevCapabilityType = CH9_USB_DCT_SS_USB,
    .bmAttributes = 0, // LTM not supported
    .wSpeedSupported = cpuToLe16(CH9_USB_SS_CAP_SUPPORT_SS | CH9_USB_SS_CAP_SUPPORT_HS | CH9_USB_SS_CAP_SUPPORT_FS),
    .vFunctionalitySupport = 1, //<----what's that????????????????????, look in spec
    .bU1DevExitLat = 4, // 4 us
    .bU2DevExitLat = cpuToLe16(512) // 512 us
};

static CH9_UsbCapabilityDescriptor capabilityExtDesc = {
    .bLength = CH9_USB_DS_DEVICE_CAPABILITY_20,
    .bDescriptorType = CH9_USB_DT_DEVICE_CAPABILITY,
    .bDevCapabilityType = CH9_USB_DCT_USB20_EXTENSION,
    .bmAttributes = cpuToLe32(CH9_USB_USB20_EXT_LPM_SUPPORT | CH9_USB_USB20_EXT_BESL_ALT_HIRD)
};
//-------------- BOS descriptor set end ----------------------------------------
uint8_t hidReportDesc[] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x02, // USAGE (Mouse)
    0xa1, 0x01, // COLLECTION (Application)
    0x09, 0x01, //   USAGE (Pointer)
    0xa1, 0x00, //   COLLECTION (Physical)
    0x05, 0x09, //     USAGE_PAGE (Button)
    0x19, 0x01, //     USAGE_MINIMUM (Button 1)
    0x29, 0x03, //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x95, 0x03, //     REPORT_COUNT (3)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    0x95, 0x01, //     REPORT_COUNT (1)
    0x75, 0x05, //     REPORT_SIZE (5)
    0x81, 0x03, //     INPUT (Cnst,Var,Abs)
    0x05, 0x01, //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30, //     USAGE (X)
    0x09, 0x31, //     USAGE (Y)
    0x15, 0x81, //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x02, //     REPORT_COUNT (2)
    0x81, 0x06, //     INPUT (Data,Var,Rel)
    0xc0, //   END_COLLECTION
    0xc0 // END_COLLECTION
};


static CH9_UsbDeviceQualifierDescriptor qualifierDesc = {
    .bLength = CH9_USB_DS_DEVICE_QUALIFIER,
    .bDescriptorType = CH9_USB_DT_DEVICE_QUALIFIER,
    .bcdUSB = cpuToLe16(0x0200),
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = 64,
    .bNumConfigurations = 0x01,
    .bReserved = 0x00
};

static CH9_UsbEndpointDescriptor* endpointEpInDesc = &endpointDesc;

void hid_devcfg_setMaxSpeed(CH9_UsbSpeed maxSpeed) {

    if (maxSpeed == CH9_USB_SPEED_HIGH || maxSpeed == CH9_USB_SPEED_FULL) {
        bosDesc.wTotalLength = cpuToLe16(CH9_USB_DS_BOS + CH9_USB_DS_DEVICE_CAPABILITY_20);
        bosDesc.bNumDeviceCaps = 1;
        devHsDesc.bcdUSB = cpuToLe16(BCD_USB_HS_ONLY);
    }
}

CH9_UsbSpeed hid_devcfg_updateSpeed(CH9_UsbSpeed devSpeed) {
    CH9_UsbSpeed oldSpeed = sDevSpeed;
    if (devSpeed != oldSpeed) {
        vDbgMsg(DBG_GEN_MSG, 1, "Updating speed oldSpeed(%d) newSpeed(%d)  \n",
                oldSpeed, devSpeed);
    }
    sDevSpeed = devSpeed;
    return oldSpeed;
}

CH9_UsbConfigurationDescriptor *hid_devcfg_getConfigDesc(CH9_UsbSpeed devSpeed) {
    CH9_UsbConfigurationDescriptor *configDesc = NULL;

    // select descriptors according to actual speed
    switch (devSpeed) {

        case CH9_USB_SPEED_FULL:
            configDesc = &confHsDesc;
            break;

        case CH9_USB_SPEED_HIGH:
            configDesc = &confHsDesc;
            break;

        case CH9_USB_SPEED_SUPER:
        case CH9_USB_SPEED_SUPER_PLUS:
            configDesc = &confSsDesc;
            break;

        default:
            vDbgMsg(DBG_GEN_MSG, 1, "Unknown speed %d: \n", devSpeed);
            break;
    }
    return configDesc;
}

CH9_UsbDeviceDescriptor *hid_devcfg_getDeviceDesc(CH9_UsbSpeed devSpeed) {

    CH9_UsbDeviceDescriptor * devDesc = NULL;

    // select descriptors according to actual speed
    switch (devSpeed) {

        case CH9_USB_SPEED_FULL:
            devDesc = &devHsDesc;
            break;

        case CH9_USB_SPEED_HIGH:
            devDesc = &devHsDesc;
            break;

        case CH9_USB_SPEED_SUPER:
        case CH9_USB_SPEED_SUPER_PLUS:
            devDesc = &devSsDesc;
            break;

        default:
            vDbgMsg(DBG_GEN_MSG, 1, "Unknown speed %d: \n", devSpeed);
            break;
    }
    return devDesc;
}

char* hid_dev_getLanguageDesc() {
    return (char *) &languageDesc[0];
}

char* hid_dev_getVendorDesc() {
    get_unicode_string(vendorDesc, USB_MANUFACTURER_STRING);
    return vendorDesc;
}

char* hid_dev_getProductDesc() {
    get_unicode_string(productDesc, USB_PRODUCT_STRING);
    return productDesc;
}

char* hid_dev_getSerialDesc() {
    get_unicode_string(serialDesc, USB_SERIAL_NUMBER_STRING);
    return serialDesc;
}

CH9_UsbDeviceQualifierDescriptor* hid_dev_getQualifierDesc() {
    return &qualifierDesc;
}
 
int hid_dev_getOtgDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed) {
    int length = 0;
    
    length = otgDesc.bLength;
    memmove(ep0Buff, &otgDesc, length);
    return length;
}

int hid_dev_getHidDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed) {
    int length = 0;

    length = sizeof (hidReportDesc);
    memmove(ep0Buff, &hidReportDesc, length);
    return length;
}

int hid_dev_getHidIntDesc(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed) {
    int length = 0;
    
    length = sizeof (struct usb_hid_interface_descriptor);
    memmove(ep0Buff, &hidInterfaceDesc, length);
    return length;
}
                                
int hid_dev_getSpeedConfiguration(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed) {
    CH9_UsbConfigurationDescriptor *configDesc = hid_devcfg_getConfigDesc(devSpeed);
    int offset = 0;
    int length = 0;
                    
    length = le16ToCpu(configDesc->wTotalLength);
    memmove(&ep0Buff[offset], configDesc, CH9_USB_DS_CONFIGURATION);
    ep0Buff[1] = CH9_USB_DS_OTHER_SPEED_CFG;
    offset += CH9_USB_DS_CONFIGURATION;

    memmove(&ep0Buff[offset], &interfaceDesc, CH9_USB_DS_INTERFACE);
    offset += CH9_USB_DS_INTERFACE;

    memmove(&ep0Buff[offset], &hidInterfaceDesc, sizeof (struct usb_hid_interface_descriptor));
    offset += sizeof (struct usb_hid_interface_descriptor);

    memmove(&ep0Buff[offset], &endpointDesc, CH9_USB_DS_ENDPOINT);
    offset += CH9_USB_DS_ENDPOINT;

    //memmove(&ep0Buff[offset], &compDesc, CH9_USB_DS_SS_USB_EP_COMPANION);

    //only for OTG devices
    memmove(&ep0Buff[offset], &otgDesc, CH9_USB_DS_OTG);
    offset += CH9_USB_DS_OTG;

    return length;
    
}

int hid_dev_getOtherSpeedCfg(uint8_t* ep0Buffer, CH9_UsbSpeed devSpeed) {
    int offset = 0;

    if (devSpeed == CH9_USB_SPEED_HIGH) {
        CH9_UsbConfigurationDescriptor *configDesc = hid_devcfg_getConfigDesc(CH9_USB_SPEED_FULL);
        uint8_t numEndpoints = 0;
        CH9_UsbSpeed currentDevSpeed = sDevSpeed;

        /* patch descriptor type */
        configDesc->bDescriptorType = CH9_USB_DT_OTHER_SPEED_CFG;

        /* patch speed */
        hid_devcfg_updateSpeed(CH9_USB_SPEED_FULL);

        // select descriptors according to actual speed
        // dummy write - will be overwritten at the end with correct length 
        memmove(&ep0Buffer[offset], configDesc, CH9_USB_DS_CONFIGURATION);
        offset += CH9_USB_DS_CONFIGURATION;

        memmove(&ep0Buffer[offset], &interfaceDesc, CH9_USB_DS_INTERFACE);
        offset += CH9_USB_DS_INTERFACE;
        memmove(&ep0Buffer[offset], &hidInterfaceDesc, sizeof (struct usb_hid_interface_descriptor));
        offset += sizeof (struct usb_hid_interface_descriptor);

        if (endpointEpInDesc != NULL) {
            memmove(&ep0Buffer[offset], endpointEpInDesc, CH9_USB_DS_ENDPOINT);
            offset += CH9_USB_DS_ENDPOINT;
            numEndpoints++;
        }

        /* fix config descriptor length */
        configDesc->wTotalLength = cpuToLe16(offset);
        memmove(&ep0Buffer[0], configDesc, CH9_USB_DS_CONFIGURATION);

        /* revert descriptor type */
        configDesc->bDescriptorType = CH9_USB_DT_CONFIGURATION;
        
        /* revert speed */
        hid_devcfg_updateSpeed(currentDevSpeed);
        
        /* fix number of endpoints */
        interfaceDesc.bNumEndpoints = numEndpoints;
        memmove(&ep0Buffer[CH9_USB_DS_CONFIGURATION], &interfaceDesc, CH9_USB_DS_INTERFACE);
    }
    return (int)(offset);
}

int hid_dev_getConfiguration(uint8_t* ep0Buff, CH9_UsbSpeed devSpeed) {
    CH9_UsbConfigurationDescriptor *configDesc = hid_devcfg_getConfigDesc(devSpeed);
    int offset = 0;
    
    // select descriptors according to actual speed
    // dummy write - will be overwritten at the end with correct length 
    memmove(&ep0Buff[offset], configDesc, CH9_USB_DS_CONFIGURATION);
    offset += CH9_USB_DS_CONFIGURATION;

    memmove(&ep0Buff[offset], &interfaceDesc, CH9_USB_DS_INTERFACE);
    offset += CH9_USB_DS_INTERFACE;
    memmove(&ep0Buff[offset], &hidInterfaceDesc, sizeof (struct usb_hid_interface_descriptor));
    offset += sizeof (struct usb_hid_interface_descriptor);

    memmove(&ep0Buff[offset], &endpointDesc, CH9_USB_DS_ENDPOINT);
    offset += CH9_USB_DS_ENDPOINT;

    if(devSpeed == CH9_USB_SPEED_SUPER || devSpeed ==  CH9_USB_SPEED_SUPER_PLUS) {
    memmove(&ep0Buff[offset], &compDesc, CH9_USB_DS_SS_USB_EP_COMPANION);
    offset += CH9_USB_DS_SS_USB_EP_COMPANION;
    }
    //only for OTG devices
    memmove(&ep0Buff[offset], &otgDesc, CH9_USB_DS_OTG);
    offset += CH9_USB_DS_OTG;
    
    configDesc->wTotalLength = cpuToLe16(offset);
    memmove(&ep0Buff[0], configDesc, CH9_USB_DS_CONFIGURATION);
    
    interfaceDesc.bNumEndpoints = 1;
    memmove(&ep0Buff[CH9_USB_DS_CONFIGURATION], &interfaceDesc, CH9_USB_DS_INTERFACE);
    
    return (int)(configDesc->wTotalLength);
}

int hid_dev_getBOSDesc(uint8_t* ep0Buff, CH9_UsbSpeed maxSpeed) {
    int offset = 0;
    int length = le16ToCpu(bosDesc.wTotalLength);

    memmove(ep0Buff, &bosDesc, CH9_USB_DS_BOS);
    offset += CH9_USB_DS_BOS;
    if (maxSpeed == CH9_USB_SPEED_SUPER || maxSpeed == CH9_USB_SPEED_SUPER_PLUS) {
        memmove(&ep0Buff[offset], &capabilitySsDesc, CH9_USB_DS_DEVICE_CAPABILITY_30);
        offset += CH9_USB_DS_DEVICE_CAPABILITY_30;
    }

    memmove(&ep0Buff[offset], &capabilityExtDesc, CH9_USB_DS_DEVICE_CAPABILITY_20);

    return length;
}

int hid_dev_getEpDesc(uint8_t* buffer, uint8_t epAddress) {

    int length = 0;
    if (epAddress == endpointDesc.bEndpointAddress) {
        length = CH9_USB_DS_ENDPOINT;
        memmove(buffer, &endpointDesc, CH9_USB_DS_ENDPOINT);
        if (sDevSpeed == CH9_USB_SPEED_SUPER) {
            length += CH9_USB_DS_SS_USB_EP_COMPANION;
            memmove(&buffer[CH9_USB_DS_ENDPOINT], &compDesc, CH9_USB_DS_SS_USB_EP_COMPANION);
        }
    }
    return length;
}

uint8_t hid_dev_getInEpAddress() {
    uint8_t epAddress;
    switch (cusbdss_epCfgMode) {
        case CH9_USB_EP_INTERRUPT:
            epAddress = MOUSE_EP_ADDRES_IN;
            break;

        default:
            epAddress = MOUSE_EP_ADDRES_IN;
            break;
    }
    return epAddress;
}

uint8_t hid_dev_getXferMode() {
    return cusbdss_epCfgMode;
}
 
static void displayEndpointInfo(CUSBD_Ep * ep) {
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "-------Endpoint INFO------------- %c\n", ' ');
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "address: %02X\n", ep->address);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "epList: %08X\n", (uintptr_t) & ep->epList);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "name: %s\n", ep->name);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "ops: %c\n", ' ');
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "maxPacket: %d\n", ep->maxPacket);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "maxStreams: %d\n", ep->maxStreams);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "mult: %d\n", ep->mult);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "maxburst: %d\n", ep->maxburst);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "desc: %08X\n", (uintptr_t) ep->desc);
    vDbgMsg(DBG_GEN_MSG, DBG_FYI, "compDesc: %08X\n", (uintptr_t) ep->compDesc);
}

static void configureDev(USB_Handler *usb_handler, CUSBD_PrivateData *pD, uint8_t ctrlValue) {
    //static uint8_t configValue = 0;
    static uint8_t epDescBuffer[64];    
    CUSBD_Ep * ep;
    LIST_ListHead *list;
    CUSBD_Dev * dev;
    CUSBD_OBJ *drv = usb_handler->dprofile->drv;
    drv->getDevInstance(pD, &dev);
    
    //configValue = ctrlValue;    
    for (list = dev->epList.next; list != &dev->epList; list = list->next) {
        endpointDesc.bEndpointAddress = 0x1;
        memcpy(epDescBuffer, &endpointDesc, sizeof(endpointDesc));
        ep = (CUSBD_Ep *) list;
        ep->ops->epEnable(pD, ep, epDescBuffer);
        displayEndpointInfo(ep);
        break;
    }

    dev->state = CH9_USB_STATE_CONFIGURED; 
   
}

static void unConfigureDev(USB_Handler *usb_handler, CUSBD_PrivateData *pD) {
    CUSBD_Dev * dev;
    CUSBD_Ep * ep;
    LIST_ListHead *list;
    //uint8_t configValue = 0;
    CUSBD_OBJ *drv = usb_handler->dprofile->drv;
    drv->getDevInstance(pD, &dev);

    for (list = dev->epList.next; list != &dev->epList; list = list->next) {
        ep = (CUSBD_Ep *) list;
        if (ep->address == MOUSE_EP_ADDRES_IN) {
            ep->ops->epDisable(pD, ep);
        }
    }  
    
    dev->state = CH9_USB_STATE_ADDRESS;
      
}

uint32_t mouse_setup(USB_Handler *usb_handler, CUSBD_PrivateData *pD, CH9_UsbSetup *ctrl) {
  CUSBD_Dev *dev;
  int length = 0;
  CH9_UsbConfigurationDescriptor *configDesc;
  CH9_UsbDeviceDescriptor *devDesc;
  //uint8_t outEpAddress = cusbdss_dev_getOutEpAddress(usb_handler->dprofile);
  //uint8_t inEpAddress = cusbdss_dev_getInEpAddress(usb_handler->dprofile);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "setup\n");
  ctrl->wIndex  = le16ToCpu(ctrl->wIndex);
  ctrl->wLength = le16ToCpu(ctrl->wLength);
  ctrl->wValue  = le16ToCpu(ctrl->wValue);

  usb_handler->dprofile->drv->getDevInstance(pD, &dev);

  configDesc = cusbdss_devcfg_getConfigDesc(dev->speed);
  devDesc    = cusbdss_devcfg_getDeviceDesc(dev->speed);

  if ((configDesc == NULL) || (devDesc == NULL)) {
    return CDN_EINVAL;
  }

  vDbgMsg(DBG_USB_CTRL_MSG, 1, "Speed %d: \n", dev->speed);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "bRequest: %02X\n", ctrl->bRequest);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "bRequestType: %02X\n", ctrl->bmRequestType);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wIndex: %04X\n", ctrl->wIndex);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wValue: %04X\n", ctrl->wValue);
  vDbgMsg(DBG_USB_CTRL_MSG, 1, "wLength: %04X\n", ctrl->wLength);


  usb_handler->dprofile->ep0Req->buf = usb_handler->dprofile->ep0Buff;
  usb_handler->dprofile->ep0Req->dma = (uintptr_t) (usb_handler->dprofile->ep0Buff);
      //(uintptr_t)usb_handler->dprofile->ep0BufferPhyAddr;
  

  switch (ctrl->bmRequestType & CH9_USB_REQ_TYPE_MASK) {
  case CH9_USB_REQ_TYPE_STANDARD:
    switch (ctrl->bRequest) {
    case CH9_USB_REQ_GET_DESCRIPTOR:
        vDbgMsg(DBG_USB_CTRL_MSG, 1, "request get descriptor!\n");
        if ((ctrl->bmRequestType & CH9_REQ_RECIPIENT_MASK) == CH9_USB_REQ_RECIPIENT_INTERFACE) {
            switch (ctrl->wValue >> 8) {
                case 0x22:
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request ctrl->wValue>>8 = 0x22 descriptor!\n");
                    length = sizeof(hidReportDesc);
                    memmove(usb_handler->dprofile->ep0Buff, &hidReportDesc, length);
                    break;
                case 0x21:
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request ctrl->wValue>>8 = 0x21 descriptor!\n");
                    length = sizeof (struct usb_hid_interface_descriptor);
                    memmove(usb_handler->dprofile->ep0Buff, &hidInterfaceDesc, length);
                    break;
                default:
                    return -1;
            }
        }else if ((ctrl->bmRequestType & CH9_REQ_RECIPIENT_MASK) == CH9_USB_REQ_RECIPIENT_DEVICE) {
            switch (ctrl->wValue >> 8) {
                case CH9_USB_DT_DEVICE:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_DEVICE descriptor!\n");
                    int i;
                    length = CH9_USB_DS_DEVICE;
                    memmove(usb_handler->dprofile->ep0Buff, devDesc, 18);
                    #if 1
                    for (i = 0; i < length; i++) {
                        DbgMsg(DBG_GEN_MSG, DBG_FYI, "DevDesc[%d] = 0x%02X \n",i, usb_handler->dprofile->ep0Buff[i]);
                    }
                    #endif
                    break;
                }
                case CH9_USB_DT_CONFIGURATION:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_CONFIGURATION descriptor!\n");
                                                    
                    int i;
                    length = hid_dev_getConfiguration(usb_handler->dprofile->ep0Buff, dev->speed);
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "Total length = %02X\n", length);
                    for (i = 0; i < length; i++) {
                        DbgMsg(DBG_GEN_MSG, DBG_FYI, "%02X ", usb_handler->dprofile->ep0Buff[i]);
                    }
                    break;
                }
                
                case CH9_USB_DT_STRING:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_STRING descriptor!\n");
                    
                    uint8_t descIndex = (uint8_t) (ctrl->wValue & 0xFF);
                    char *strDesc;
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "StringDesc %c\n", ' ');
                    switch (descIndex) {
                        case 0:
                            strDesc = hid_dev_getLanguageDesc();
                            length = strDesc[0];
                            vDbgMsg(DBG_USB_CTRL_MSG, 1, "language %c\n", ' ');
                        
                            break;

                        case 1:
                            strDesc = hid_dev_getVendorDesc();
                            length = strDesc[0];
                            vDbgMsg(DBG_USB_CTRL_MSG, 1, "vendor %c\n", ' ');
                            break;

                        case 2:
                            strDesc = hid_dev_getProductDesc();
                            length = strDesc[0];
                            vDbgMsg(DBG_USB_CTRL_MSG, 1, "product %c\n", ' ');
                            break;

                        case 3:
                            strDesc = hid_dev_getSerialDesc();
                            length = strDesc[0];
                            vDbgMsg(DBG_USB_CTRL_MSG, 1, "serial %c\n", ' ');
                            break;
                            
                        default: return -1;
                    }
                    memmove(usb_handler->dprofile->ep0Buff, strDesc, length);
                    
                    break;
                }

                case CH9_USB_DT_BOS:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_BOS descriptor!\n");
                    
                    int i;
                    length = hid_dev_getBOSDesc(usb_handler->dprofile->ep0Buff, dev->maxSpeed);
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "bosDesc[0] = %02X\n", usb_handler->dprofile->ep0Buff[0]);

                    for (i = 0; i < length; i++) {
                        DbgMsg(DBG_USB_CTRL_MSG, 1, "%02X ", usb_handler->dprofile->ep0Buff[i]);
                    }
                    DbgMsg(DBG_USB_CTRL_MSG, 1, " %c\n", ' ');
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "BosDesc %c\n", ' ');
                    
                    break;
                }

                case CH9_USB_DT_DEVICE_QUALIFIER:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_DEVICE_QUALIFIER descriptor!\n");
                    
                    //Only supported for 2.0 devices 
                    length = CH9_USB_DS_DEVICE_QUALIFIER;
                    memmove(usb_handler->dprofile->ep0Buff, hid_dev_getQualifierDesc(), length);
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "QualifierDesc %c\n", ' ');
                    
                    break;
                }

                case CH9_USB_DT_OTHER_SPEED_CFG:
                {
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_OTHER_SPEED_CFG descriptor!\n");
                    
                    int i;
                    length = hid_dev_getOtherSpeedCfg(usb_handler->dprofile->ep0Buff, dev->speed);
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "Total length = %02X\n", length);

                    for (i = 0; i < length; i++) {
                        DbgMsg(DBG_GEN_MSG, DBG_FYI, "%02X ", usb_handler->dprofile->ep0Buff[i]);
                    }
                    DbgMsg(DBG_GEN_MSG, DBG_FYI, " %c\n", ' ');
                    
                    break;
                }

                case CH9_USB_DT_OTG:{
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request CH9_USB_DT_OTG descriptor!\n");
                    
                    length = hid_dev_getOtgDesc(usb_handler->dprofile->ep0Buff, dev->speed);
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "OtgDesc %c\n", ' ');
                    
                    break;
                }
                default:
                    vDbgMsg(DBG_USB_CTRL_MSG, 1, "Error_1 %c\n", ' ');
                    return -1;

            }//switch
        
        }//if
      break;
    case CH9_USB_REQ_SET_CONFIGURATION:{
        static uint8_t configValue = 0;
        vDbgMsg(DBG_USB_CTRL_MSG, 1, "request set configuration!\n");
        if (ctrl->wValue > 1) {
            return -1; // no such configuration
        }

        // un-configure device
        if (ctrl->wValue == 0) {
            vDbgMsg(DBG_USB_CTRL_MSG, 1, "(%d)\n", le16ToCpu(ctrl->wValue));
            unConfigureDev(usb_handler, pD);
            vDbgMsg(DBG_USB_CTRL_MSG, 1, "DevState = CH9_USB_STATE_ADDRESS (%d)\n", le16ToCpu(ctrl->wValue));
            
            return 0;
        }else if (configValue == 1 && ctrl->wValue == 1) {
            // device already configured
            
            return 0;
        }else {
            // configure device
            configureDev(usb_handler, pD, ctrl->wValue); 
            vDbgMsg(DBG_USB_CTRL_MSG, 1, "CH9_USB_STATE_CONFIGURED (%d)\n", le16ToCpu(ctrl->wValue));
        
            /*Code control  Self powered feature of USB*/
            if (configDesc->bmAttributes & CH9_USB_CONFIG_SELF_POWERED) {
                if (usb_handler->dprofile->drv->dSetSelfpowered) {
                    usb_handler->dprofile->drv->dSetSelfpowered(pD);
                }
            } else {
                if (usb_handler->dprofile->drv->dClearSelfpowered) {
                    usb_handler->dprofile->drv->dSetSelfpowered(pD);
                }
            }
            /* invoke and callback registered */
            
        }
        return 0;
        break;
    }
      
    case CH9_USB_REQ_GET_CONFIGURATION:
      vDbgMsg(DBG_USB_CTRL_MSG, 1, "request get configuration!\n");
      break;
    case CH9_USB_REQ_SET_INTERFACE:{
      vDbgMsg(DBG_USB_CTRL_MSG, 1, "request set interface!\n");
      if ((ctrl->wValue != 0) || (ctrl->wIndex != 0) || (ctrl->wLength != 0))return -1;
                    length = 0;
                    unConfigureDev(usb_handler, pD);
                    configureDev(usb_handler, pD, ctrl->wValue);                     
      break;
    }
    case CH9_USB_REQ_GET_INTERFACE:
      vDbgMsg(DBG_USB_CTRL_MSG, 1, "request get interface!\n");
      break;
    case CH9_USB_REQ_GET_STATUS:
      vDbgMsg(DBG_USB_CTRL_MSG, 1, "request get status!\n");
      break;
    default:
      printf("request does not support!\n");
      return -1;
      break;
    }
    break;
  case CH9_USB_REQ_TYPE_CLASS:
    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request class!\n");
    return -1;
    break;
  }

  if (length > 0) {
    usb_handler->dprofile->ep0Req->length = ctrl->wLength < length ? ctrl->wLength : length;
    dev->ep0->ops->reqQueue(pD, dev->ep0, usb_handler->dprofile->ep0Req);
    vDbgMsg(DBG_USB_CTRL_MSG, 1, "request send\n");
  }

  /*
  usb_device_write(pD, usb_handler->dprofile->ep0Req, usb_handler->dprofile->epIn, (uint8_t *)devDesc, devDesc->bLength, 1);
  */
  return 0;
}
