<table border="0">
  <tr>
    <td align="left" valign="middle">
    <h1>NFC Application Examples</h1>
  </td>
  <td align="left" valign="middle">
    <a href="https://www.silabs.com/products/wireless">
      <img src="http://pages.silabs.com/rs/634-SLU-379/images/WGX-transparent.png"  title="Silicon Labs Gecko and Wireless Gecko MCUs" alt="EFM32 32-bit Microcontrollers" width="250"/>
    </a>
  </td>
  </tr>
</table>

This fold contains NFC application examples, which demonstrates how to use NFC library and NFC IC drivers. 


## Examples

### [nt3h2x11_field_detection](nt3h2x11_field_detection)

Demonstrates NT3H2x11 Field Detection (FD) functionality, which can be used for NFC wake up.

### [nt3h2x11_format_t2t](nt3h2x11_format_t2t)

Formats NT3H2x11 to be T2T compatible. Factory state NT3H2x11 needs to set its capability container (CC) to certain value before being able to be read/wrtien by certain NFC reader devices such as smart phones.

### [nt3h2x11_i2c_read_tag](nt3h2x11_i2c_read_tag)

Read NT3H2x11 memory content via I2C and dump it to a serial terminal. This example can be modified to retrive data external NFC device writes to NT3H2x11.

### [nt3h2x11_i2c_write_tag_ndef](nt3h2x11_i2c_write_tag_ndef)

This example demonstrates how to form a NDEF message with [NFC library](../nfc_library) and write it to NT3H2x11 via I2C interface.


## Reporting Bugs/Issues and Posting Questions and Comments

To report bugs in the Application Examples projects, please create a new "Issue" in the "Issues" section of this repo. Please reference the board, project, and source files associated with the bug, and reference line numbers. If you are proposing a fix, also include information on the proposed fix. Since these examples are provided as-is, there is no guarantee that these examples will be updated to fix these issues.

Questions and comments related to these examples should be made by creating a new "Issue" in the "Issues" section of this repo.

## Disclaimer

The Gecko SDK suite supports development with Silicon Labs IoT SoC and module devices. Unless otherwise specified in the specific directory, all examples are considered to be EXPERIMENTAL QUALITY which implies that the code provided in the repos has not been formally tested and is provided as-is.  It is not suitable for production environments.  In addition, this code will not be maintained and there may be no bug maintenance planned for these resources. Silicon Labs may update projects from time to time.
