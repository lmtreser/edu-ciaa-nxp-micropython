#include <stdint.h>
const char mp_frozen_names[] = {
"ModBus\0"
"\0"};
const uint32_t mp_frozen_sizes[] = {
27164,
};
const char mp_frozen_content[] = {
"import pyb\nimport struct\nimport sys\n\nMODE_RTU   = \'rtu\'\nMODE_ASCII = \'ascii\'\n\n_NUMBER_OF_BYTES_PER_REGISTER = 2\n\n_ASCII_HEADER = \':\'\n_ASCII_FOOTER = \'\\r\\n\'\n\nclass Instrument():\n\n    def __init__(self, uartObj, slaveaddress, mode=MODE_RTU):\n        self.serial = uartObj\n        self.address = slaveaddress\n        self.mode = mode\n        self.debug = False\n        self.precalculate_read_size = True      \n\n    def __repr__(self):\n        return \"{}<id=0x{:x}, address={}, mode={}, serial={}>\".format(\n            self.__module__,\n            id(self),\n            self.address,\n            self.mode,\n            self.serial,\n            )\n\n    def read_bit(self, registeraddress, functioncode=2):\n        _checkFunctioncode(functioncode, [1, 2])\n        return self._genericCommand(functioncode, registeraddress)\n\n    def write_bit(self, registeraddress, value, functioncode=5):\n        _checkFunctioncode(functioncode, [5, 15])\n        _checkInt(value, minvalue=0, maxvalue=1, description=\'input value\')\n        self._genericCommand(functioncode, registeraddress, value)\n\n    def read_register(self, registeraddress, numberOfDecimals=0, functioncode=3, signed=False):\n        _checkFunctioncode(functioncode, [3, 4])\n        _checkInt(numberOfDecimals, minvalue=0, maxvalue=10, description=\'number of decimals\')\n        return self._genericCommand(functioncode, registeraddress, numberOfDecimals=numberOfDecimals, signed=signed)\n\n    def write_register(self, registeraddress, value, numberOfDecimals=0, functioncode=16, signed=False):\n        _checkFunctioncode(functioncode, [6, 16])\n        _checkInt(numberOfDecimals, minvalue=0, maxvalue=10, description=\'number of decimals\')\n        self._genericCommand(functioncode, registeraddress, value, numberOfDecimals, signed=signed)\n\n    def read_registers(self, registeraddress, numberOfRegisters, functioncode=3):\n        _checkFunctioncode(functioncode, [3, 4])\n        _checkInt(numberOfRegisters, minvalue=1, description=\'number of registers\')\n        return self._genericCommand(functioncode, registeraddress, \\\n            numberOfRegisters=numberOfRegisters, payloadformat=\'registers\')\n\n    def write_registers(self, registeraddress, values):\n        if not isinstance(values, list):\n            raise TypeError(\'The \"values parameter\" must be a list. Given: {0!r}\'.format(values))\n        _checkInt(len(values), minvalue=1, description=\'length of input list\')\n        self._genericCommand(16, registeraddress, values, numberOfRegisters=len(values), payloadformat=\'registers\')\n\n\n    def _genericCommand(self, functioncode, registeraddress, value=None, numberOfDecimals=0, numberOfRegisters=1, signed=False, payloadformat=None):\n        NUMBER_OF_BITS = 1\n        NUMBER_OF_BYTES_FOR_ONE_BIT = 1\n        NUMBER_OF_BYTES_BEFORE_REGISTERDATA = 1\n        MAX_NUMBER_OF_REGISTERS = 255\n\n        # Payload format constants, so datatypes can be told apart.\n        PAYLOADFORMAT_LONG      = \'long\'\n        PAYLOADFORMAT_FLOAT     = \'float\'\n        PAYLOADFORMAT_STRING    = \'string\'\n        PAYLOADFORMAT_REGISTER  = \'register\'\n        PAYLOADFORMAT_REGISTERS = \'registers\'\n\n        ## Check input values ##\n        _checkRegisteraddress(registeraddress)\n        _checkInt(numberOfDecimals, minvalue=0, description=\'number of decimals\')\n        _checkInt(numberOfRegisters, minvalue=1, maxvalue=MAX_NUMBER_OF_REGISTERS, description=\'number of registers\')\n\n        ## Check combinations of input parameters ##\n        numberOfRegisterBytes = numberOfRegisters * _NUMBER_OF_BYTES_PER_REGISTER\n\n        # Payload format\n        if functioncode in [3, 4, 6, 16] and payloadformat is None:\n            payloadformat = PAYLOADFORMAT_REGISTER\n        else:\n            if payloadformat is not None:\n                raise ValueError(\'The payload format given is not allowed for this function code. \' + \\\n                    \'Given format: {0!r}, functioncode: {1!r}.\'.format(payloadformat, functioncode))\n\n        # Signed and numberOfDecimals\n        if signed:\n            if payloadformat not in [PAYLOADFORMAT_REGISTER, PAYLOADFORMAT_LONG]:\n                raise ValueError(\'The \"signed\" parameter can not be used for this data format. \' + \\\n                    \'Given format: {0!r}.\'.format(payloadformat))\n\n        if numberOfDecimals > 0 and payloadformat != PAYLOADFORMAT_REGISTER:\n            raise ValueError(\'The \"numberOfDecimals\" parameter can not be used for this data format. \' + \\\n                \'Given format: {0!r}.\'.format(payloadformat))\n\n        # Number of registers\n        if functioncode not in [3, 4, 16] and numberOfRegisters != 1:\n            raise ValueError(\'The numberOfRegisters is not valid for this function code. \' + \\\n                \'NumberOfRegisters: {0!r}, functioncode {1}.\'.format(numberOfRegisters, functioncode))\n\n        if functioncode == 16 and payloadformat == PAYLOADFORMAT_REGISTER and numberOfRegisters != 1:\n            raise ValueError(\'Wrong numberOfRegisters when writing to a \' + \\\n                \'single register. Given {0!r}.\'.format(numberOfRegisters))\n            # Note: For function code 16 there is checking also in the content conversion functions.\n\n        # Value\n        if functioncode in [5, 6, 15, 16] and value is None:\n            raise ValueError(\'The input value is not valid for this function code. \' + \\\n                \'Given {0!r} and {1}.\'.format(value, functioncode))\n\n        # Value for registers\n        if functioncode == 16 and payloadformat == PAYLOADFORMAT_REGISTERS:\n            if not isinstance(value, list):\n                raise TypeError(\'The value parameter must be a list. Given {0!r}.\'.format(value))\n\n            if len(value) != numberOfRegisters:\n                raise ValueError(\'The list length does not match number of registers. \' + \\\n                    \'List: {0!r},  Number of registers: {1!r}.\'.format(value, numberOfRegisters))\n\n        ## Build payload to slave ##\n        payloadToSlave = bytearray()\n        __append2BytesFromInt(payloadToSlave,registeraddress)\n        \n        if functioncode in [1, 2]:\n            __append2BytesFromInt(payloadToSlave,NUMBER_OF_BITS)\n\n        elif functioncode in [3, 4]:\n            __append2BytesFromInt(payloadToSlave,numberOfRegisters)\n           \n\n        elif functioncode == 5:\n            if value == 0:\n                __append2BytesFromInt(payloadToSlave,0x0000)\n            else:\n                __append2BytesFromInt(payloadToSlave,0xFF00)\n\n        elif functioncode == 6:\n            __append2BytesFromInt(payloadToSlave,value,numberOfDecimals)\n\n\n        elif functioncode == 15:\n            __append2BytesFromInt(payloadToSlave,NUMBER_OF_BITS)\n            payloadToSlave.append(NUMBER_OF_BYTES_FOR_ONE_BIT)\n            if value == 0:\n                __append2BytesFromInt(payloadToSlave,0x0000)\n            else:\n                __append2BytesFromInt(payloadToSlave,0xFF00)\n\n        elif functioncode == 16:\n            __append2BytesFromInt(payloadToSlave,numberOfRegisters)\n            payloadToSlave.append(numberOfRegisterBytes)\n\n            if payloadformat == PAYLOADFORMAT_REGISTER:\n                registerData = value\n                __append2BytesFromInt(payloadToSlave,registerData,numberOfDecimals)\n            elif payloadformat == PAYLOADFORMAT_REGISTERS:\n                for reg in value:\n                    __append2BytesFromInt(payloadToSlave,reg,numberOfDecimals)\n\n\n        #Comunicate\t\t\n        payloadFromSlave,retFnc = self._performCommand(functioncode, payloadToSlave)\n\n        ## Check the contents in the response payload ##\n        if functioncode in [1, 2, 3, 4]:\n            _checkResponseByteCount(payloadFromSlave)\n         \n        if functioncode in [5, 6, 15, 16]:\n            _checkResponseRegisterAddress(payloadFromSlave, registeraddress)\n\n        if functioncode == 5:\n            if value == 0:\n                _checkResponseWriteData(payloadFromSlave, 0x0000)\n            else:\n                _checkResponseWriteData(payloadFromSlave, 0xFF00)\n         \n        if functioncode == 6:\n            aux = bytearray()\n            __append2BytesFromInt(aux,value,numberOfDecimals)\n            _checkResponseWriteData(payloadFromSlave, aux[0]<<8 | aux[1] )\n\n        if functioncode == 15:\n            _checkResponseNumberOfRegisters(payloadFromSlave, NUMBER_OF_BITS)\n\n        if functioncode == 16:\n            _checkResponseNumberOfRegisters(payloadFromSlave, numberOfRegisters)\n\n\n        ## Calculate return value ##\n        if functioncode in [1, 2]:\n            registerdata = payloadFromSlave[NUMBER_OF_BYTES_BEFORE_REGISTERDATA:]\n            if len(registerdata) != NUMBER_OF_BYTES_FOR_ONE_BIT:\n                raise ValueError(\'The registerdata length does not match NUMBER_OF_BYTES_FOR_ONE_BIT. \' + \\\n                    \'Given {0}.\'.format(len(registerdata)))\n            return _bitResponseToValue(registerdata)\n\n\n        if functioncode in [3, 4]:\n            registerdata = payloadFromSlave[NUMBER_OF_BYTES_BEFORE_REGISTERDATA:]\n            if len(registerdata) != numberOfRegisterBytes:\n                raise ValueError(\'The registerdata length does not match number of register bytes. \' + \\\n                    \'Given {0!r} and {1!r}.\'.format(len(registerdata), numberOfRegisterBytes))\n\n            #if payloadformat == PAYLOADFORMAT_STRING:\n            #    return _bytestringToTextstring(registerdata, numberOfRegisters)\n            #elif payloadformat == PAYLOADFORMAT_LONG:\n            #    return _bytestringToLong(registerdata, signed, numberOfRegisters)\n            #elif payloadformat == PAYLOADFORMAT_FLOAT:\n            #    return _bytestringToFloat(registerdata, numberOfRegisters)\n\n            if payloadformat == PAYLOADFORMAT_REGISTERS:\n                return _bytesResponseToValuelist(registerdata, numberOfRegisters)\n\n            elif payloadformat == PAYLOADFORMAT_REGISTER:\n                return _bytesResponseToInt(registerdata, numberOfDecimals, signed)\n\n            raise ValueError(\'Wrong payloadformat for return value generation. \' + \\\n                \'Given {0}\'.format(payloadformat))\n\n        return payloadFromSlave\n\n\n    def _performCommand(self, functioncode, payloadToSlave):\n        DEFAULT_NUMBER_OF_BYTES_TO_READ = 1000\n        _checkFunctioncode(functioncode, None)\n\n        # Build request\n        request = _embedPayload(self.address, self.mode, functioncode, payloadToSlave)\n\n        # Calculate number of bytes to read\n        number_of_bytes_to_read = DEFAULT_NUMBER_OF_BYTES_TO_READ\n        if self.precalculate_read_size:\n            try:\n                number_of_bytes_to_read = _predictResponseSize(self.mode, functioncode, payloadToSlave)\n            except:\n                pass\n\n        # Communicate\n        response = self._communicate(request, number_of_bytes_to_read)\n\n        # Extract payload\n        payloadFromSlave = _extractPayload(response, self.address, self.mode, functioncode)\n        return payloadFromSlave\n\n\n    def _communicate(self, request, number_of_bytes_to_read):\n        _checkInt(number_of_bytes_to_read)\n\n        # Sleep to make sure 3.5 character times have passed\n        minimum_silent_period   = _calculate_minimum_silent_period(self.serial.get_baudrate())\n        pyb.delay(minimum_silent_period)\n\n        # Write request\n        self.serial.write(request)\n\n\n        # Read response\n        answer = bytearray()\n        timeOutRead = 200\n        while True:\n            if self.serial.any():\n                answer = self.serial.read(number_of_bytes_to_read)\n                break\n            else:\n                pyb.delay(10)\n                timeOutRead-=1\n                if timeOutRead<=0:\n                    break\n        #_________                       \n\n        if len(answer) == 0:\n            raise Exception(\'No communication with the instrument (no answer)\')\n\n        return answer\n\n\nclass Slave:\n    def __init__(self,uartObj, slaveaddress, mappedRegisters,mode=MODE_RTU):\n        self.serial = uartObj\n        self.address = slaveaddress\n        self.mode = mode\n        self.mappedRegisters = mappedRegisters\n\n    def receive(self):\n        if self.serial.any():\n            answer = self.serial.readall()\n            try:\n                payloadFromMaster,receivedFunctioncode = _extractPayload(answer, self.address, self.mode, None)\n                self.__analysePacket(payloadFromMaster,receivedFunctioncode)\n                return True\n            except Exception as err:\n                pass\n        return False\n\n    def __analysePacket(self,payloadFromMaster,receivedFunctioncode):\n        flagUnsupFnc = True\n        regAddr = payloadFromMaster[0]<<8 | payloadFromMaster[1]\n        out = bytearray()\n        if receivedFunctioncode == 3 or receivedFunctioncode == 4: # read holding/input reg\n            flagUnsupFnc = False\n            qty = payloadFromMaster[2]<<8 | payloadFromMaster[3]\n            out.append(qty*2)\n            for addr in range(regAddr,regAddr+qty):\n                val = self.__getRegisterValue(addr)\n                out.append(val>>8)\n                out.append(val&0xFF)\n        if receivedFunctioncode == 6: # write single reg\n            flagUnsupFnc = False\n            val = payloadFromMaster[2]<<8 | payloadFromMaster[3]\n            self.__setRegisterValue(regAddr,val)\n            out.append((regAddr>>8)&0xFF)\n            out.append(regAddr&0xFF)\n            out.append((val>>8)&0xFF)\n            out.append(val&0xFF)\n\n        if receivedFunctioncode == 16: # write multiple registers\n            flagUnsupFnc = False\n            qty = payloadFromMaster[2]<<8 | payloadFromMaster[3]\n            i = 5\n            for addr in range(regAddr,regAddr+qty):\n                val = payloadFromMaster[i]<<8 | payloadFromMaster[i+1]\n                self.__setRegisterValue(addr,val)\n                i+=2\n            out.append(payloadFromMaster[0])\n            out.append(payloadFromMaster[1])\n            out.append(payloadFromMaster[2])\n            out.append(payloadFromMaster[3])\n\n        if flagUnsupFnc:\n            receivedFunctioncode+=0x80\n            receivedFunctioncode=receivedFunctioncode&0xFF\n            out.append(0x01) #err code\n\n        data = _embedPayload(self.address, self.mode, receivedFunctioncode, out)\n        self.serial.write(data)\n\n\n    def __getRegisterValue(self,addr):\n        if addr in self.mappedRegisters:\n            return self.mappedRegisters[addr]\n        return 0\n\n    def __setRegisterValue(self,addr,val):\n        if addr in self.mappedRegisters:\n            self.mappedRegisters[addr] = val\n   \n\n\n\n\n\ndef __append2BytesFromInt(payloadToSlave,value,numberOfDecimals=0,flagMSF=True):\n    multiplier = 10 ** numberOfDecimals\n    intVal = int(float(value) * multiplier)\n    if flagMSF:\n        payloadToSlave.append((intVal>>8)&0xFF)\n        payloadToSlave.append(intVal&0xFF)\n    else:\n        payloadToSlave.append(intVal&0xFF)\n        payloadToSlave.append((intVal>>8)&0xFF)\n\n\ndef _embedPayload(slaveaddress, mode, functioncode, payloaddata):\n    firstPart = bytearray()\n    firstPart.append(slaveaddress)\n    firstPart.append(functioncode)\n    for b in payloaddata:\n        firstPart.append(b)\n\n    if mode == MODE_ASCII:\n        request = _ASCII_HEADER + \\\n                _hexencode(firstPart) + \\\n                _hexencode(_calculateLrcString(firstPart)) + \\\n                _ASCII_FOOTER\n    else:\n        crc = _calculateCrcString(firstPart)\n        request = bytearray()\n        for b in firstPart:\n            request.append(b)\n        request.append(crc&0xFF)\n        request.append((crc>>8)&0xFF)\n    return request\n\n\n\ndef _calculateCrcString(inputstring):\n    register = 0xFFFF\n    for char in inputstring:\n        register = (register >> 8) ^ _CRC16TABLE[(register ^ int(char)) & 0xFF]\n \n    return register\n\ndef _calculateLrcString(inputstring):\n    register = 0\n    for character in inputstring:\n        register += character\n\n    lrc = ((register ^ 0xFF) + 1) & 0xFF\n\n    out = bytearray()\n    out.append(lrc)\n    return out\n\n\n\ndef _checkInt(inputvalue, minvalue=None, maxvalue=None, description=\'inputvalue\'):\n    flagError=False\n    if minvalue!=None and inputvalue<minvalue:\n        flagError=True\n    if maxvalue!=None and inputvalue>maxvalue:\n        flagError=True\n    if flagError:\n        raise TypeError(\'{0} out of range. Given: {1!r}\'.format(description, inputvalue))\n\n\n\ndef _checkFunctioncode(functioncode, listOfAllowedValues=[]):\n    if functioncode < 1 or functioncode > 127:\n        raise ValueError(\'Wrong function code: {0}\'.format(functioncode))\n    if listOfAllowedValues is None:\n        return\n    if functioncode not in listOfAllowedValues:\n        raise ValueError(\'Wrong function code: {0}, allowed values are {1!r}\'.format(functioncode, listOfAllowedValues))\n\n\ndef _checkRegisteraddress(registeraddress):\n    REGISTERADDRESS_MAX = 0xFFFF\n    REGISTERADDRESS_MIN = 0\n    _checkInt(registeraddress, REGISTERADDRESS_MIN, REGISTERADDRESS_MAX, description=\'registeraddress\')\n\n\ndef _checkResponseByteCount(payload):\n    givenNumberOfDatabytes = payload[0]\n    countedNumberOfDatabytes = len(payload)-1\n    if givenNumberOfDatabytes != countedNumberOfDatabytes:\n        errortemplate = \'Wrong given number of bytes in the response: {0}, but counted is {1} as data payload length is {2}.\' + \\\n            \' The data payload is: {3!r}\'\n        errortext = errortemplate.format(givenNumberOfDatabytes, countedNumberOfDatabytes, len(payload), payload)\n        raise ValueError(errortext)\n\ndef _checkResponseRegisterAddress(payload, registeraddress):\n    receivedStartAddress = payload[0]<<8 | payload[1]\n    if receivedStartAddress!= registeraddress:\n        raise ValueError(\'Wrong given write start adress: {0}, but commanded is {1}. The data payload is: {2!r}\'.format( \\\n            receivedStartAddress, registeraddress, payload))\n\n\ndef _checkResponseWriteData(payload, writedata):\n    receivedWritedata = payload[2]<<8 | payload[3]\n    if receivedWritedata != writedata:\n        raise ValueError(\'Wrong write data in the response: {0!r}, but commanded is {1!r}. The data payload is: {2!r}\'.format( \\\n            receivedWritedata, writedata, payload))\n\n\ndef _checkResponseNumberOfRegisters(payload, numberOfRegisters):\n    receivedNumberOfWrittenReisters = payload[2]<<8 | payload[3]\n    if receivedNumberOfWrittenReisters != numberOfRegisters:\n        raise ValueError(\'Wrong number of registers to write in the response: {0}, but commanded is {1}. The data payload is: {2!r}\'.format( \\\n            receivedNumberOfWrittenReisters, numberOfRegisters, payload))\n\n\ndef _bitResponseToValue(bytesdata):\n    if bytesdata[0] == 0x01:\n        return 1\n    elif bytesdata[0] == 0x00:\n        return 0\n    else:\n        raise ValueError(\'Could not convert bit response to a value. Input: {0!r}\'.format(bytesdata))\n\n\ndef _bytesResponseToInt(bytesdata, numberOfDecimals,signed=False):\n    reg = bytesdata[0]<<8 | bytesdata[1]\n    if numberOfDecimals>0:\n        reg = reg / (10**numberOfDecimals)\n    return reg\n    \n\ndef _bytesResponseToValuelist(bytesdata,numberOfRegisters):\n    out = []\n    index = 0\n    while numberOfRegisters>0:\n        reg =bytesdata[index]<<8 | bytesdata[index+1]\n        out.append(reg)\n        index+=2\n        numberOfRegisters-=1\n    return out\n\n\n_CRC16TABLE = (\n        0, 49345, 49537,   320, 49921,   960,   640, 49729, 50689,  1728,  1920, \n    51009,  1280, 50625, 50305,  1088, 52225,  3264,  3456, 52545,  3840, 53185, \n    52865,  3648,  2560, 51905, 52097,  2880, 51457,  2496,  2176, 51265, 55297, \n     6336,  6528, 55617,  6912, 56257, 55937,  6720,  7680, 57025, 57217,  8000, \n    56577,  7616,  7296, 56385,  5120, 54465, 54657,  5440, 55041,  6080,  5760, \n    54849, 53761,  4800,  4992, 54081,  4352, 53697, 53377,  4160, 61441, 12480, \n    12672, 61761, 13056, 62401, 62081, 12864, 13824, 63169, 63361, 14144, 62721, \n    13760, 13440, 62529, 15360, 64705, 64897, 15680, 65281, 16320, 16000, 65089, \n    64001, 15040, 15232, 64321, 14592, 63937, 63617, 14400, 10240, 59585, 59777, \n    10560, 60161, 11200, 10880, 59969, 60929, 11968, 12160, 61249, 11520, 60865, \n    60545, 11328, 58369,  9408,  9600, 58689,  9984, 59329, 59009,  9792,  8704, \n    58049, 58241,  9024, 57601,  8640,  8320, 57409, 40961, 24768, 24960, 41281, \n    25344, 41921, 41601, 25152, 26112, 42689, 42881, 26432, 42241, 26048, 25728, \n    42049, 27648, 44225, 44417, 27968, 44801, 28608, 28288, 44609, 43521, 27328, \n    27520, 43841, 26880, 43457, 43137, 26688, 30720, 47297, 47489, 31040, 47873, \n    31680, 31360, 47681, 48641, 32448, 32640, 48961, 32000, 48577, 48257, 31808, \n    46081, 29888, 30080, 46401, 30464, 47041, 46721, 30272, 29184, 45761, 45953, \n    29504, 45313, 29120, 28800, 45121, 20480, 37057, 37249, 20800, 37633, 21440, \n    21120, 37441, 38401, 22208, 22400, 38721, 21760, 38337, 38017, 21568, 39937, \n    23744, 23936, 40257, 24320, 40897, 40577, 24128, 23040, 39617, 39809, 23360, \n    39169, 22976, 22656, 38977, 34817, 18624, 18816, 35137, 19200, 35777, 35457, \n    19008, 19968, 36545, 36737, 20288, 36097, 19904, 19584, 35905, 17408, 33985, \n    34177, 17728, 34561, 18368, 18048, 34369, 33281, 17088, 17280, 33601, 16640, \n    33217, 32897, 16448)\n\ndef _hexencode(bytestring, insert_spaces = False):\n    separator = \'\' if not insert_spaces else \' \'\n    byte_representions = []\n    for c in bytestring:\n        byte_representions.append( \'{0:02X}\'.format(c) )\n    return separator.join(byte_representions).strip()\n\n\ndef _hexDecodeNibble(hexStrByte):\n    if hexStrByte >=0x30 and hexStrByte <=0x39 :\n        return hexStrByte - 0x30\n    return hexStrByte - 0x41 + 0x0A\n\ndef _hexdecode(hexstring):\n\n    if len(hexstring) % 2 != 0:\n        raise ValueError(\'The input hexstring must be of even length. Given: {!r}\'.format(hexstring))\n\n    index = 0\n    out = bytearray()\n    while len(hexstring) > index:\n        out.append( _hexDecodeNibble(hexstring[index])<<4 | _hexDecodeNibble(hexstring[index+1]) )\n        index+=2\n    return out\n\ndef _calculate_minimum_silent_period(baudrate):\n    _checkInt(baudrate, minvalue=1, description=\'baudrate\')  # Avoid division by zero\n    BITTIMES_PER_CHARACTERTIME = 11\n    MINIMUM_SILENT_CHARACTERTIMES = 3.5\n    bittime = 1 / float(baudrate)\n    return int((bittime * BITTIMES_PER_CHARACTERTIME * MINIMUM_SILENT_CHARACTERTIMES)*1000)\n\ndef _extractPayload(response, slaveaddress, mode, functioncode):\n    BYTEPOSITION_FOR_ASCII_HEADER          = 0  # Relative to plain response\n\n    BYTEPOSITION_FOR_SLAVEADDRESS          = 0  # Relative to (stripped) response\n    BYTEPOSITION_FOR_FUNCTIONCODE          = 1\n\n    NUMBER_OF_RESPONSE_STARTBYTES          = 2  # Number of bytes before the response payload (in stripped response)\n    NUMBER_OF_CRC_BYTES                    = 2\n    NUMBER_OF_LRC_BYTES                    = 1\n    BITNUMBER_FUNCTIONCODE_ERRORINDICATION = 7\n\n    MINIMAL_RESPONSE_LENGTH_RTU            = NUMBER_OF_RESPONSE_STARTBYTES + NUMBER_OF_CRC_BYTES\n    MINIMAL_RESPONSE_LENGTH_ASCII          = 9\n\n    # Argument validity testing\n    if functioncode!=None:\n        _checkFunctioncode(functioncode, None)\n\n    plainresponse = response\n\n    # Validate response length\n    if mode == MODE_ASCII:\n        if len(response) < MINIMAL_RESPONSE_LENGTH_ASCII:\n            raise ValueError(\'Too short Modbus ASCII response (minimum length {} bytes). Response: {!r}\'.format( \\\n                MINIMAL_RESPONSE_LENGTH_ASCII,\n                response))\n    elif len(response) < MINIMAL_RESPONSE_LENGTH_RTU:\n            raise ValueError(\'Too short Modbus RTU response (minimum length {} bytes). Response: {!r}\'.format( \\\n                MINIMAL_RESPONSE_LENGTH_RTU,\n                response))\n\n    # Validate the ASCII header and footer.\n    if mode == MODE_ASCII:\n        if response[BYTEPOSITION_FOR_ASCII_HEADER] != ord(_ASCII_HEADER):\n            raise ValueError(\'Did not find header ({!r}) as start of ASCII response. The plain response is: {!r}\'.format( \\\n                _ASCII_HEADER,\n                response))\n        elif response[-len(_ASCII_FOOTER):][0] != ord(_ASCII_FOOTER[0]) and response[-len(_ASCII_FOOTER):][1] != ord(_ASCII_FOOTER[1]):\n            raise ValueError(\'Did not find footer ({!r}) as end of ASCII response. The plain response is: {!r}\'.format( \\\n                _ASCII_FOOTER,\n                response))\n\n        # Strip ASCII header and footer\n        response = response[1:-2]\n\n        if len(response) % 2 != 0:\n            template = \'Stripped ASCII frames should have an even number of bytes, but is {} bytes. \' + \\\n                    \'The stripped response is: {!r} (plain response: {!r})\'\n            raise ValueError(template.format(len(response), response, plainresponse))\n\n        # Convert the ASCII (stripped) response string to RTU-like response string\n        response = _hexdecode(response)\n\n    # Validate response checksum\n    if mode == MODE_ASCII:\n        calculateChecksum = _calculateLrcString\n        numberOfChecksumBytes = NUMBER_OF_LRC_BYTES\n    else:\n        calculateChecksum = _calculateCrcString\n        numberOfChecksumBytes = NUMBER_OF_CRC_BYTES\n\n    receivedChecksum = response[-numberOfChecksumBytes:]\n    responseWithoutChecksum = response[0 : len(response) - numberOfChecksumBytes]\n    calculatedChecksum = calculateChecksum(responseWithoutChecksum)\n\n    flagCrcError = False\n    if mode == MODE_ASCII:\n        if (receivedChecksum[0] != calculatedChecksum[0]&0xFF):\n            flagCrcError = True\n    else:\n        if (receivedChecksum[0] != calculatedChecksum&0xFF) or (receivedChecksum[1] != (calculatedChecksum>>8)&0xFF):\n            flagCrcError = True\n\n    if flagCrcError:\n        template = \'Checksum error in {} mode: {!r} instead of {!r} . The response is: {!r} (plain response: {!r})\'\n        text = template.format(\n                mode,\n                receivedChecksum,\n                calculatedChecksum,\n                response, plainresponse)\n        raise ValueError(text)\n\n    # Check slave address\n    responseaddress = int(response[BYTEPOSITION_FOR_SLAVEADDRESS])\n\n    if responseaddress != slaveaddress:\n        raise ValueError(\'Wrong return slave address: {} instead of {}. The response is: {!r}\'.format( \\\n            responseaddress, slaveaddress, response))\n\n    # Check function code\n    receivedFunctioncode = int(response[BYTEPOSITION_FOR_FUNCTIONCODE])\n    if functioncode!=None:\n        if receivedFunctioncode == (functioncode | (1 << BITNUMBER_FUNCTIONCODE_ERRORINDICATION)): # _setBitOn(functioncode, BITNUMBER_FUNCTIONCODE_ERRORINDICATION):\n            raise ValueError(\'The slave is indicating an error. The response is: {!r}\'.format(response))\n        elif receivedFunctioncode != functioncode:\n            raise ValueError(\'Wrong functioncode: {} instead of {}. The response is: {!r}\'.format( \\\n                receivedFunctioncode, functioncode, response))\n\n    # Read data payload\n    firstDatabyteNumber = NUMBER_OF_RESPONSE_STARTBYTES\n\n    if mode == MODE_ASCII:\n        lastDatabyteNumber = len(response) - NUMBER_OF_LRC_BYTES\n    else:\n        lastDatabyteNumber = len(response) - NUMBER_OF_CRC_BYTES\n\n    payload = response[firstDatabyteNumber:lastDatabyteNumber]\n    return payload,receivedFunctioncode\n\0"
};