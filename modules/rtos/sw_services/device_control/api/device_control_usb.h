// Copyright (c) 2021 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#ifndef USB_DEVICE_CONTROL_H_
#define USB_DEVICE_CONTROL_H_

#if USE_TINYUSB

#include "tusb.h"
#include "device/usbd_pvt.h"
#include "device_control.h"

#define TUD_XMOS_DEVICE_CONTROL_DESC_LEN 9

#define TUD_XMOS_DEVICE_CONTROL_DESCRIPTOR(_itfnum, _stridx) \
  /* Interface */\
  9, TUSB_DESC_INTERFACE, _itfnum, 0, 0, TUSB_CLASS_VENDOR_SPECIFIC, 0x00, 0x00, _stridx

/*
 * To be returned to TinyUSB by the application via the
 * usbd_app_driver_get_cb() callback, if device control
 * over USB is to be used.
 */
extern const usbd_class_driver_t usb_device_control_app_driver;

/*
 * Must be called by tud_vendor_control_xfer_cb() if
 * device control over USB is to be used.
 */
bool usb_device_control_xfer(uint8_t rhport, uint8_t stage, tusb_control_request_t const *request);

/*
 * Application callback that provides the USB device control driver
 * with the device control context to use.
 */
__attribute__ ((weak))
device_control_t *tud_device_control_get_ctrl_ctx_cb(void);

#endif

#endif /* USB_DEVICE_CONTROL_H_ */
