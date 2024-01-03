/*
 * Copyright (C) 2024 Algoltek, Inc.
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#include "config.h"

#include <fwupdplugin.h>

#include "fu-algoltek-usb-common.h"
#include "fu-algoltek-usb-firmware.h"
#include "fu-algoltek-usb-struct.h"

struct _FuAlgoltekUsbFirmware {
	FuFirmware parent_instance;
};

G_DEFINE_TYPE(FuAlgoltekUsbFirmware, fu_algoltek_usb_firmware, FU_TYPE_FIRMWARE)

static gboolean
<<<<<<< HEAD
fu_algoltek_usb_firmware_validate(FuFirmware *firmware, GBytes *fw, gsize offset, GError **error)
{
	return fu_struct_algoltek_product_identity_validate_bytes(fw, offset, error);
=======
fu_algoltek_usb_firmware_validate(FuFirmware *firmware,
				  GInputStream *stream,
				  gsize offset,
				  GError **error)
{
	return fu_struct_algoltek_product_identity_validate_stream(stream, offset, error);
>>>>>>> upstream/main
}

static gboolean
fu_algoltek_usb_firmware_parse(FuFirmware *firmware,
<<<<<<< HEAD
			       GBytes *fw,
=======
			       GInputStream *stream,
>>>>>>> upstream/main
			       gsize offset,
			       FwupdInstallFlags flags,
			       GError **error)
{
<<<<<<< HEAD
	gchar *version;
	g_autoptr(FuFirmware) img_isp = fu_firmware_new();
	g_autoptr(FuFirmware) img_payload = fu_firmware_new();
	g_autoptr(GBytes) blob_isp = NULL;
	g_autoptr(GBytes) blob_payload = NULL;
	g_autoptr(GByteArray) header_array = g_byte_array_new();
	g_autoptr(GBytes) blob_header = NULL;

	blob_header =
	    fu_bytes_new_offset(fw, offset, FU_STRUCT_ALGOLTEK_PRODUCT_IDENTITY_SIZE, error);
	fu_byte_array_append_bytes(header_array, blob_header);

	version = fu_struct_algoltek_product_identity_get_version(header_array);

	offset += FU_STRUCT_ALGOLTEK_PRODUCT_IDENTITY_SIZE;

	blob_isp = fu_bytes_new_offset(fw, offset, AG_ISP_SIZE, error);
	if (blob_isp == NULL)
		return FALSE;
	fu_firmware_set_bytes(img_isp, blob_isp);
	fu_firmware_set_id(img_isp, "isp");
	fu_firmware_add_image(firmware, img_isp);
	offset += g_bytes_get_size(blob_isp);

	blob_payload = fu_bytes_new_offset(fw, offset, AG_FIRMWARE_SIZE, error);
	if (blob_payload == NULL)
		return FALSE;

	fu_firmware_set_version(img_payload, version);
	fu_firmware_set_bytes(img_payload, blob_payload);
	fu_firmware_set_id(img_payload, FU_FIRMWARE_ID_PAYLOAD);
	fu_firmware_add_image(firmware, img_payload);
=======
	const gchar *version;
	g_autoptr(FuFirmware) img_isp = fu_firmware_new();
	g_autoptr(FuFirmware) img_payload = fu_firmware_new();
	g_autoptr(GByteArray) st = NULL;
	g_autoptr(GInputStream) stream_isp = NULL;
	g_autoptr(GInputStream) stream_payload = NULL;

	/* identity */
	st = fu_struct_algoltek_product_identity_parse_stream(stream, offset, error);
	if (st == NULL)
		return FALSE;
	version = fu_struct_algoltek_product_identity_get_version(st);
	offset += FU_STRUCT_ALGOLTEK_PRODUCT_IDENTITY_SIZE;

	/* ISP */
	stream_isp = fu_partial_input_stream_new(stream, offset, AG_ISP_SIZE);
	if (!fu_firmware_parse_stream(img_isp, stream_isp, 0x0, flags, error))
		return FALSE;
	fu_firmware_set_id(img_isp, "isp");
	fu_firmware_add_image(firmware, img_isp);
	offset += AG_ISP_SIZE;

	/* payload */
	stream_payload = fu_partial_input_stream_new(stream, offset, AG_FIRMWARE_SIZE);
	if (!fu_firmware_parse_stream(img_payload, stream_payload, 0x0, flags, error))
		return FALSE;
	fu_firmware_set_version(img_payload, version);
	fu_firmware_set_id(img_payload, FU_FIRMWARE_ID_PAYLOAD);
	fu_firmware_add_image(firmware, img_payload);

	/* success */
>>>>>>> upstream/main
	return TRUE;
}

static GByteArray *
fu_algoltek_usb_firmware_write(FuFirmware *firmware, GError **error)
{
	g_autoptr(GByteArray) buf = g_byte_array_new();
	g_autoptr(GBytes) blob_isp = NULL;
	g_autoptr(GBytes) blob_payload = NULL;

	blob_isp = fu_firmware_get_image_by_id_bytes(firmware, "isp", error);
	if (blob_isp == NULL)
		return NULL;
	fu_byte_array_append_bytes(buf, blob_isp);

	blob_payload = fu_firmware_get_image_by_id_bytes(firmware, FU_FIRMWARE_ID_PAYLOAD, error);
	if (blob_payload == NULL)
		return NULL;
	fu_byte_array_append_bytes(buf, blob_payload);

	return g_steal_pointer(&buf);
}

static void
fu_algoltek_usb_firmware_init(FuAlgoltekUsbFirmware *self)
{
}

static void
fu_algoltek_usb_firmware_class_init(FuAlgoltekUsbFirmwareClass *klass)
{
	FuFirmwareClass *klass_firmware = FU_FIRMWARE_CLASS(klass);
	klass_firmware->validate = fu_algoltek_usb_firmware_validate;
	klass_firmware->parse = fu_algoltek_usb_firmware_parse;
	klass_firmware->write = fu_algoltek_usb_firmware_write;
}
