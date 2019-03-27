RAM_SIZE = 1024


class RAM:
    def __init__(self, size=RAM_SIZE):
        self._minAddr = 0
        self._maxAddr = RAM_SIZE - 1
        self._memory = []   # a list of values.  Could be #s or instructions.
        for i in range(size):
            self._memory.append(0)

    def __getitem__(self, addr):
        return self._memory[addr]

    def __setitem__(self, addr, val):
        self._memory[addr] = val

    def is_legal_addr(self, addr):
        return self._minAddr <= addr <= self._maxAddr


class MMU:
	def __init__(self, ram):
		self._ram = ram

		self._reloc = 0
		self._limit = 0

	def __getitem__(self, addr):
		phys_addr = addr + self._reloc
		if self.is_valid_address(phys_addr):
			return self._ram.__getitem__(phys_addr)

	def __setitem__(self, addr, value):
		phys_addr = addr + self._reloc
		if self.is_valid_address(phys_addr):
			self._ram.__setitem__(phys_addr, value)

	def set_reloc_register(self, val):
		self._reloc = val

	def set_limit_register(self, val):
		self._limit = val

	def is_valid_address(self, addr):
		if self._ram.is_legal_addr(addr):
			if (self._reloc <= addr <= self._limit):
				return True
			else:
				return False
		else:
			print("BAD ADDRESS %d", addr)
			return False


