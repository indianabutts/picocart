from core import DataPins, ControlPins

import sys


def main(mocked=False):
    if mocked:
        print("Running in Mock Mode")
    valid_address = -1
    pin_labels = {
        0: "GPIO2",
        1: "GPIO3",
        2: "GPIO4",
        3: "GPIO17",
        4: "GPIO27",
        5: "GPIO22",
        6: "GPIO10",
        7: "GPIO9",
        8: "GPIO11",
        9: "GPIO14",
        10: "GPIO15",
        11: "GPIO18",
        12: "GPIO23",
        13: "GPIO24",
        14: "GPIO25",
        15: "GPIO8",
    }
    data_pins = DataPins(pin_labels, mocked)
    data_pins.set_as_output()
    control_pins = ControlPins(pulse_label="GPIO21", mocked=mocked)
    while True:
        address_string = input("Please Enter a 16-bit address in HEX without 0x:")
        address = int(address_string, 16)
        if address > 0xFFFF:
            print("Address is larger than 16 bits")
        else:
            print(f'You entered address: 0x{address:0>4X}')
            valid_address = address

        if valid_address >= 0:
            data_pins.set_value(address, bits=16)
            input("Press Enter to Pulse the Control Signal")
            control_pins.pulse_signal()


if __name__ == "__main__":
    main("mocked" in sys.argv)
