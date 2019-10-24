# How to see hardware info

there is a command *dmidecode*,his syntax is

	dmidecode --type 17

after --type is a number,0~42,means different hardware component,for 17,it is
*memory*,here is a full list

	Type   Information
	────────────────────────────────────────────
	  0   BIOS
	  1   System
	  2   Baseboard
	  3   Chassis
	  4   Processor
	  5   Memory Controller
	  6   Memory Module
	  7   Cache
	  8   Port Connector
	  9   System Slots
	 10   On Board Devices
	 11   OEM Strings
	 12   System Configuration Options
	 13   BIOS Language
	 14   Group Associations
	 15   System Event Log
	 16   Physical Memory Array
	 17   Memory Device
	 18   32-bit Memory Error
	 19   Memory Array Mapped Address
	 20   Memory Device Mapped Address
	 21   Built-in Pointing Device
	 22   Portable Battery
	 23   System Reset
	 24   Hardware Security
	 25   System Power Controls
	 26   Voltage Probe
	 27   Cooling Device
	 28   Temperature Probe
	 29   Electrical Current Probe
	 30   Out-of-band Remote Access
	 31   Boot Integrity Services
	 32   System Boot
	 33   64-bit Memory Error
	 34   Management Device
	 35   Management Device Component
	 36   Management Device Threshold Data
	 37   Memory Channel
	 38   IPMI Device
	 39   Power Supply
	 40   Additional Information
	 41   Onboard Devices Extended Information
	 42   Management Controller Host Interface

you can also use keyword instead of number,a keyword is a combine of numbers,
here is their mapping
*
	Keyword     Types
    ──────────────────────────────
    bios        0, 13
    system      1, 12, 15, 23, 32
    baseboard   2, 10, 41
    chassis     3
    processor   4
    memory      5, 6, 16, 17
    cache       7
    connector   8
    slot        9

