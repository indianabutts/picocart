from random import randrange


class MockInputDevice:
    def __init__(self, pin: str):
        self.pin = pin

    @property
    def value(self):
        read_value = randrange(2)
        print(f"Got value of {read_value} from {self.pin}")
        return read_value

    def close(self):
        self.pin=None


class MockOutputDevice:
    def __init__(
        self, pin: str, active_high: bool = False, initial_value: bool = False
    ):
        self.pin = pin
        self.active_high = active_high
        self.initial_value = initial_value
        if initial_value:
            self.on()
        else:
            self.off()

    def on(self):
        if self.active_high:
            self.value = 1
        else:
            self.value = 0
        debug_value = "HIGH" if self.value==1 else "LOW"
        print(f"[ON] Setting {self.pin} to {debug_value}")

    def off(self):
        if self.active_high:
            self.value = 0
        else:
            self.value = 1
        debug_value = "HIGH" if self.value==1 else "LOW"
        print(f"[OFF] Setting {self.pin} to {debug_value}")

    def close(self):
        self.pin = None
