/* SPDX-License-Identifier: MIT */

#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/usb/class/usb_hid.h>

LOG_MODULE_REGISTER(sakoa_hid_probe, LOG_LEVEL_INF);

static struct hid_ops probe_ops;
static hid_int_ready_callback original_in_ready;
static uint32_t write_count;
static uint32_t complete_count;

void __real_usb_hid_register_device(const struct device *dev, const uint8_t *desc, size_t size,
                                    const struct hid_ops *op);
int __real_hid_int_ep_write(const struct device *dev, const uint8_t *data, uint32_t data_len,
                            uint32_t *bytes_ret);

static void probe_in_ready(const struct device *dev) {
    complete_count++;
    LOG_INF("HID_PROBE COMPLETE count=%u", complete_count);

    if (original_in_ready != NULL) {
        original_in_ready(dev);
    }
}

void __wrap_usb_hid_register_device(const struct device *dev, const uint8_t *desc, size_t size,
                                    const struct hid_ops *op) {
    probe_ops = *op;
    original_in_ready = op->int_in_ready;
    probe_ops.int_in_ready = probe_in_ready;

    LOG_INF("HID_PROBE REGISTER desc_len=%u", (unsigned int)size);
    __real_usb_hid_register_device(dev, desc, size, &probe_ops);
}

int __wrap_hid_int_ep_write(const struct device *dev, const uint8_t *data, uint32_t data_len,
                            uint32_t *bytes_ret) {
    uint32_t written = 0;
    int err = __real_hid_int_ep_write(dev, data, data_len, &written);

    if (bytes_ret != NULL) {
        *bytes_ret = written;
    }

    write_count++;
    LOG_INF("HID_PROBE WRITE count=%u err=%d len=%u written=%u data=%02x %02x %02x %02x "
            "%02x %02x %02x %02x %02x",
            write_count, err, data_len, written, data_len > 0 ? data[0] : 0,
            data_len > 1 ? data[1] : 0, data_len > 2 ? data[2] : 0,
            data_len > 3 ? data[3] : 0, data_len > 4 ? data[4] : 0,
            data_len > 5 ? data[5] : 0, data_len > 6 ? data[6] : 0,
            data_len > 7 ? data[7] : 0, data_len > 8 ? data[8] : 0);

    return err;
}
