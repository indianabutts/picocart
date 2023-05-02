from gpiozero import DigitalOutputDevice, DigitalInputDevice


class DataPins:
    def __init__(self, pin_labels_dict, mocked=False):
        self.pin_labels = pin_labels_dict
        self.data_pins = {}
        for i in self.pin_labels.keys():
            self.data_pins[i] = None
        self.mode = None
        self.output_klass = DigitalOutputDevice
        self.input_klass = DigitalInputDevice
        if mocked:
            from .mocks import MockOutputDevice, MockInputDevice

            self.output_klass = MockOutputDevice
            self.input_klass = MockInputDevice

    def set_as_output(self):
        for index, pin in self.pin_labels.items():
            if self.data_pins[index] is not None:
                self.data_pins[index].close()
            self.data_pins[index] = self.output_klass(
                pin, active_high=True, initial_value=False
            )
        self.mode = "Output"

    def set_as_input(self):
        for index, pin in self.pin_labels.items():
            if self.data_pins[index] is not None:
                self.data_pins[index].close()
            self.data_pins[index] = self.input_klass(pin)
        self.mode = "Input"

    def set_value(self, data, low_bit_first=True, bits=8):
        if self.mode == "Input":
            raise TypeError("Cannot Set Value of Input Pins")

        bit_range = range(bits) if low_bit_first else reversed(range(bits))
        for bit in bit_range:
            bit_value = (data >> bit) & 1
            self.data_pins[bit].value = bit_value
        print(f"{data:0>16b}")
    def read_value(self, data, low_bit_first=True) -> int:
        if self.mode == "Output":
            raise TypeError("Cannot Read Value of Output Pins")

        data_value = 0
        for index, pin in enumerate(self.data_pin):
            value = pin.value
            data_value += value << index
        return data_value

    def __del__(self):
        for _, pin in self.data_pins.items():
            if pin is not None:
                pin.close()


class ControlPins:
    def __init__(
        self,
        pulse_label="GPIO17",
        mocked=False,
    ):
        self.output_klass = DigitalOutputDevice
        self.input_klass = DigitalInputDevice
        self.mocked = mocked
        if mocked:
            from .mocks import MockOutputDevice, MockInputDevice

            self.output_klass = MockOutputDevice
            self.input_klass = MockInputDevice

        self.pulse_pin = self.output_klass(
            pulse_label, active_high=False, initial_value=False
        )

    def pulse_signal(self):
        if self.mocked:
            print("Pulsing Control Line")
        print(self.pulse_pin.value)
        self.pulse_pin.on()
        for i in range(100):
            pass
        print(self.pulse_pin.value)
        self.pulse_pin.off()
        print(self.pulse_pin.value)
