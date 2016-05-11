
void bluetoothHandler()
{
	static char msgBuffer[40];

	snprintf(msgBuffer, sizeof(msgBuffer), "AT+BLEUARTTX=B%03d Q%03d", BPM, IBI);
	comms.getBluefruit()->println(msgBuffer);
	comms.getBluefruit()->waitForOK();

#if WiC_DEBUG || WiC_BLUETOOTH_DEBUG
	Serial.print("BT SEND: "); Serial.println(msgBuffer);
#endif
}