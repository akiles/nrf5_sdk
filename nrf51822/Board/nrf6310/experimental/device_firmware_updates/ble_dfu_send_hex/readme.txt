Testing the DFU:

Pre-requisite:
- Install Nordic nRF51 SDK v6.0.0 (This SDK)
- Install IronPython which can be found at http://ironpython.net

Program initial SoftDevice
1. Make sure the device is cleared (nrfjprog --eraseall)
2. Program s110_nrf51822_7.0.0_softdevice.hex (nrfjprog --program s110_nrf51822_7.0.0_softdevice.hex)
3. Confirm the data at location 0x00003000: FFFFFF10 51B1E5DB 00016000 FFFF004E  (nrfjprog --memrd 0x3000 --w 4 --n 16)

Program Bootloader with SoftDevice update support
4. Go to <Install Folder>\Nordic\nrf51822\Board\nrf6310\experimental\device_firmware_updates\bootloader\arm\
5. Open bootloader.uvproj, compile and download.

Perform SoftDevice / Bootloader DFU
6. Using the script enclosed in this folder it is possible to transfer a new SoftDevice, Bootloader, or Application
   a. Open Master Control Panel, find the device advertising as: 'DfuTarg'
   b. Go to the  <Install Folder>\Nordic\nrf51822\Board\nrf6310\experimental\device_firmware_updates\ble_dfu_send_hex\dfu
   c. Execute the DFU Update script from Command line:
      c:\...path-to...\dfu> ipy main.py --file ..\test_images_update\<image_file.hex> --address <target address>
      where:
        <image_file.hex> can be:
        dfu_test_softdevice_b.hex               : For a SoftDevice update.
        dfu_test_softdevice_w_bootloader_b.hex  : For a SoftDevice and Bootloader update.
        dfu_test_bootloader_b.hex               : For a Bootloader update.
        <target address> is the address of the device advertising 'DfuTarg' found in a)

7. Confirm the data transfer:
   a. The SoftDevice update can be verified as:
        Data at location 0x00003000: FFFFFF10 51B1E5DB 00016000 FFFFFFFE to verify that the new softdevice is in place (nrfjprog --memrd 0x3000 --w 4 --n 16)i
        Notice the change in the last four hex digits (004E -> FFFE).
   a. The Bootloader update can be verified as:
        Open Master Control Panel, verify that the device is now advertising as: 'DfuTest' istead of 'DfuTarg'
         
Perform Application DFU:
8. Port your application to SoftDevice 7.0 specifications. Refer to release notes for details.
   Important: The application must be compiled to execute from address 0x16000 and size adjusted accordingly.
9. Use DFU to upload this ported application. Follow steps 6, supply your application instead of the SoftDevice.
   

Note: 
1. DFU mode can be entered, when an application is present, by holding button 7 on the nRF6310 motherboard when resetting the nRF51822 device.
2. Be aware that if an application is present when updating the SoftDevice, it will be deleted during SoftDevice update.
3. Application needs to be uploaded using DFU if Bootloader is present.
4. It is also possible to compile another Bootloader and transfer with the SoftDevice.
   In order to transfer another own compiled Bootloader with SoftDevice using the provided script then it is neccesary to merge the hex files.
   This can be done manually or using the mergehex.exe provided with nrfjprog (Part of SDK installer), default install folder: c:\Program Files (x86)\Nordic Semiconductor\nrf51\bin\
     c:\...path-to...\test_images_update> mergehex.exe -m dfu_test_softdevice_b.hex <new_bootloader>.hex -o dfu_test_softdevice_<new_bootloader>.hex
   It might be neccesary to provide the full path to the mergehex.exe in case the tool is not included in the PATH environment.
5. If the error '[EXCEPTION] Access to the port 'COMxx' is denied.' is presented when executing the update script then make sure MasterControlPanel is closed.
6. At current moment the bootloader supports only update to SoftDevices of identical size.

