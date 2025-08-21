/*
  This file is part of the ArduinoModbus library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _MODBUS_RTU_CLIENT_H_INCLUDED
#define _MODBUS_RTU_CLIENT_H_INCLUDED

#include "ModbusClient.h"
#ifdef ARDUINO_ARCH_SAM 
#include <DUERS485DMA.h>
#define RS485_USED_Class DUERS485DMAClass
#else
#include <ArduinoRS485.h>
#define RS485_USED_Class RS485Class
#endif

class ModbusRTUClientClass : public ModbusClient {
public:
#ifndef DUERS485DMA
  ModbusRTUClientClass(); //remove default constructor with DUEDMA
#endif
  ModbusRTUClientClass(RS485_USED_Class& rs485);
  virtual ~ModbusRTUClientClass();

  /**
   * Start the Modbus RTU client with the specified parameters
   *
   * @param baudrate Baud rate to use
   * @param config serial config. to use defaults to SERIAL_8N1
   *
   * Return 1 on success, 0 on failure
   */
  int begin(unsigned long baudrate, uint16_t config = SERIAL_8N1);
  int begin(RS485_USED_Class& rs485, unsigned long baudrate, uint16_t config = SERIAL_8N1);

private:
#ifdef ARDUINO_ARCH_SAM 
  RS485_USED_Class* _rs485;
#else
  RS485_USED_Class* _rs485 = &RS485;
#endif
};

#ifdef ARDUINO_ARCH_SAM
extern ModbusRTUClientClass ModbusRTUClient; //remove preinitialize object
#endif

#endif
