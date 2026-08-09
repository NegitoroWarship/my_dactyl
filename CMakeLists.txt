# SPDX-License-Identifier: MIT

if(CONFIG_SAKOA_USB_HID_PROBE)
  zephyr_library()
  zephyr_library_sources(src/usb_hid_probe.c)
  zephyr_ld_options(
    -Wl,--wrap=usb_hid_register_device
    -Wl,--wrap=hid_int_ep_write
  )
endif()
