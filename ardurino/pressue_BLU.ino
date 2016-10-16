/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

#include <CurieBLE.h>

/*
   This sketch example partially implements the standard Bluetooth Low-Energy Battery service.
   For more information: https://developer.bluetooth.org/gatt/services/Pages/ServicesHome.aspx
*/

/*  */
BLEPeripheral blePeripheral;       // BLE Peripheral Device (the board you're programming)
BLEService pressureSensorService("f3156083-4b16-4e6e-87bd-bb2643d9eb8d");

BLEUnsignedIntCharacteristic pressureValueA("3c8f4751-149b-4d52-9f6b-d7767931d233", BLERead | BLENotify);
BLEUnsignedIntCharacteristic pressureValueB("0ba91872-7567-4d0a-8571-aae7c3ccfe61", BLERead | BLENotify);

int pressureAread;
int pressureBread;

int fsnPin1 = 1; 
int fsnPin2 = 2; 

void setup() {
  Serial.begin(9600);    // initialize serial communication
  pinMode(13, OUTPUT);   // initialize the LED on pin 13 to indicate when a central is connected
  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet */
  blePeripheral.setLocalName("PressureSensors");
  blePeripheral.setAdvertisedServiceUuid(pressureSensorService.uuid());  // add the service UUID
  blePeripheral.addAttribute(pressureSensorService);   // Add the BLE Battery service
  blePeripheral.addAttribute(pressureValueA);   // Add the BLE Battery service
  blePeripheral.addAttribute(pressureValueB);   // Add the BLE Battery service
  //blePeripheral.addAttribute(batteryLevelChar); // add the battery level characteristic
  pressureValueA.setValue(pressureAread);   // initial value for this characteristic
  pressureValueB.setValue(pressureBread);   // initial value for this characteristic

  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
  blePeripheral.begin();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  int offset = 400;

  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(13, HIGH);

    // check the battery level every 200ms
    // as long as the central is still connected:
    while (central.connected()) {
      pressureAread = analogRead(fsnPin1) - offset;
      pressureBread = analogRead(fsnPin2) - offset;
      Serial.print("A read: ");
      Serial.print(pressureAread);
      Serial.print("\n");
      
      Serial.print("B read: ");
      Serial.print(pressureBread);
      Serial.print("\n");

      pressureValueA.setValue(pressureAread);   // initial value for this characteristic
      pressureValueB.setValue(pressureBread);   // initial value for this characteristic
    }  
   
    // when the central disconnects, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }

  delay(1000);
}


/*
   Copyright (c) 2016 Intel Corporation.  All rights reserved.

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
