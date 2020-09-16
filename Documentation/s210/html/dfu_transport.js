var dfu_transport =
[
    [ "DFU Transport Layers", "dfu_transport.html#dfu_transport_layer_sec", null ],
    [ "Serial (HCI)", "dfu_transport_serial.html", [
      [ "Packet Format", "dfu_transport_serial.html#ble_sdk_app_bootloader_packet_sec", [
        [ "Prepare Application Flash Area", "dfu_transport_serial.html#ble_sdk_app_bootloader_packet_sub_a", null ],
        [ "Activate Image", "dfu_transport_serial.html#ble_sdk_app_bootloader_packet_sub_c", null ]
      ] ]
    ] ],
    [ "BLE", "dfu_transport_ble.html", [
      [ "Device Firmware Update over BLE", "dfu_transport_ble.html#ota_intro_section", null ],
      [ "Device Firmware Update Profile", "dfu_transport_ble.html#ota_profile_section", [
        [ "Configuration", "dfu_transport_ble.html#ota_profile_conf", [
          [ "Profile Dependencies", "dfu_transport_ble.html#ota_profile_intro", null ],
          [ "Roles", "dfu_transport_ble.html#ota_profile_roles", null ],
          [ "Role/Service Relationships", "dfu_transport_ble.html#ota_profile_role_service", null ]
        ] ],
        [ "DFU Controller Role Requirements", "dfu_transport_ble.html#ota_profile_updater_role_req", [
          [ "General Error Handling.", "dfu_transport_ble.html#ota_profile_dfu_controller_err_handling", null ],
          [ "DFU Image Transfer Procedure", "dfu_transport_ble.html#ota_profile_updater_role_transfering", null ],
          [ "Idle Mode Procedures", "dfu_transport_ble.html#ota_idle_mode_procedure", null ],
          [ "Image Validation Procedure", "dfu_transport_ble.html#ota_image_validation_procedure", null ],
          [ "Idle Connection Procedure", "dfu_transport_ble.html#ota_profile_idle_conn", null ],
          [ "Link Loss Procedure", "dfu_transport_ble.html#ota_profile_ll_behavior", null ],
          [ "Packet Receipt Notification procedure", "dfu_transport_ble.html#ota_profile_pkt_rcpt_notif", null ]
        ] ],
        [ "Security Considerations", "dfu_transport_ble.html#security_considerations", null ],
        [ "DFU Target Security Considerations", "dfu_transport_ble.html#ota_server_sec", null ]
      ] ],
      [ "Device Firmware Update BLE Service", "dfu_transport_ble.html#ota_spec_sec", [
        [ "Overview", "dfu_transport_ble.html#ota_spec_abstract", null ],
        [ "Proprietary Service UUID", "dfu_transport_ble.html#ota_spec_number", null ],
        [ "Service Characteristics", "dfu_transport_ble.html#ota_spec_char", null ],
        [ "DFU Packet", "dfu_transport_ble.html#ota_spec_dfu_packet", null ],
        [ "UUID: 0x1532 over proprietary base.", "dfu_transport_ble.html#ota_spec_dfu_packet_number", null ],
        [ "DFU Control Point", "dfu_transport_ble.html#ota_spec_control_state", null ],
        [ "UUID: 0x1531 over proprietary base.", "dfu_transport_ble.html#ota_spec_control_point_number", null ],
        [ "General Error Handling procedures", "dfu_transport_ble.html#ota_spec_control_point_err_handling", null ]
      ] ]
    ] ]
];