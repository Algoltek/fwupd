if libusb.found()
cargs = ['-DG_LOG_DOMAIN="FuPluginDfuCsr"']
plugins += {meson.current_source_dir().split('/')[-1]: true}

plugin_quirks += files('dfu-csr.quirk')
plugin_builtins += static_library('fu_plugin_dfu_csr',
  rustgen.process('fu-dfu-csr.rs'),
  sources: [
    dfu_rs[1], # header
    'fu-dfu-csr-device.c',
    'fu-dfu-csr-firmware.c',
    'fu-dfu-csr-plugin.c',
  ],
  include_directories: [
    root_incdir,
    fwupd_incdir,
    fwupdplugin_incdir,
    plugindfu_incdir,
  ],
  c_args: cargs,
  dependencies: plugin_deps,
  link_with: [
    fwupdplugin,
    plugin_builtin_dfu,
  ],
)
endif
