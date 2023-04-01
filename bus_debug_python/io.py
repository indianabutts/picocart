from gpiozero import DigitalOutputDevice, DigitalInputDevice


class DataPins:
    def __init__(self, pin_labels_dict, mocked=False):
        self.pin_labels = pin_labels_dict
        self.data_pins = {
            0: None,
            1: None,
            2: None,
            3: None,
            4: None,
            5: None,
            6: None,
            7: None,
        }
        self.mode = None
        self.output_klass = DigitalOutputDevice
        self.input_klass = DigitalInputDevice
        if mocked:
            from ramsx.core.mocks import MockOutputDevice, MockInputDevice

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

    def set_value(self, data, low_bit_first=True):
        if self.mode == "Input":
            raise TypeError("Cannot Set Value of Input Pins")

        bit_range = range(8) if low_bit_first else reversed(range(8))
        for bit in bit_range:
            bit_value = data >> bit & 1
            self.data_pins[bit].value = bit_value

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
        control_data_label="GPIO21",
        control_a_label="GPIO26",
        control_b_label="GPIO16",
        control_c_label="GPIO20",
        nRead_label="GPIO19",
        nWrite_label="GPIO13",
        mocked=False,
    ):
        self.output_klass = DigitalOutputDevice
        self.input_klass = DigitalInputDevice
        self.mocked = mocked
        if mocked:
            from ramsx.core.mocks import MockOutputDevice, MockInputDevice

            self.output_klass = MockOutputDevice
            self.input_klass = MockInputDevice

        self.control_data = self.output_klass(
            control_data_label, active_high=True, initial_value=False
        )
        self.control_a = self.output_klass(
            control_a_label, active_high=True, initial_value=False
        )
        self.control_b = self.output_klass(
            control_b_label, active_high=True, initial_value=False
        )
        self.control_c = self.output_klass(
            control_c_label, active_high=True, initial_value=False
        )
        self.nRead = self.output_klass(
            nRead_label, active_high=False, initial_value=False
        )
        self.nWrite = self.output_klass(
            nWrite_label, active_high=False, initial_value=False
        )

    def latch_data(self):
        if self.mocked:
            print("Latching Data")
        self.control_data.on()
        self.control_a.off()
        self.control_b.off()
        self.control_c.on()
        self.control_data.off()
        self.control_data.on()

    def latch_low_address(self):
        if self.mocked:
            print("Latching Lower Address")
        self.control_data.on()
        self.control_a.off()
        self.control_b.on()
        self.control_c.off()
        self.control_data.off()
        self.control_data.on()

    def latch_high_address(self):
        if self.mocked:
            print("Latching Upper Address")
        self.control_data.on()
        self.control_a.on()
        self.control_b.on()
        self.control_c.off()
        self.control_data.off()
        self.control_data.on()

    def select_ram(self):
        if self.mocked:
            print("Asserting RAM Chip Enable")
        self.control_data.on()
        self.control_a.off()
        self.control_b.off()
        self.control_c.off()
        self.control_data.off()

    def deselect_ram(self):
        if self.mocked:
            print("Deasserting RAM Chip Enable")
        self.control_data.off()
        self.control_a.off()
        self.control_b.off()
        self.control_c.off()
        self.control_data.on()

    def assert_write(self):
        if self.mocked:
            print("Asserting RAM Write Enable")
        self.nRead.off()
        self.nWrite.on()

    def deassert_write(self):
        if self.mocked:
            print("Deasserting RAM Write Enable")
        self.nWrite.off()

    def handover_to_msx(self):
        if self.mocked:
            print("Asserting Complete Flag, waiting for MSX RESET signal")
        self.nRead.off()
        self.nWrite.off()
        self.control_data.on()
        self.control_a.on()
        self.control_b.off()
        self.control_c.on()
        self.control_data.off()
