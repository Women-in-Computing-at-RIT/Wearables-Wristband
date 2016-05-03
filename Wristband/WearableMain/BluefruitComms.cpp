// 
// 
// 

#include "BluefruitComms.h"

// A small helper
void error(const char*err) {
	Serial.println(err);
	while (1);
}

BluefruitComms::BluefruitComms()
{
	this->communicator = new Bluefruit(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);
}

BluefruitComms::~BluefruitComms()
{
	delete this->communicator;
}

boolean BluefruitComms::initialize()
{
	if (!communicator->begin(VERBOSE_MODE)) {
		error("Couldn't find Bluefruit. Ensure it is in CMD mode nad wiring is correct!");
		return this->connected = false;
	}
	else
	{
		this->factoryReset();

		communicator->echo(false);
		communicator->info();
		
		communicator->verbose(false);
		while (!communicator->isConnected())
			delay(20);

		Serial.println("Bluefruit is Connected!");

		return this->connected = true;
	}
}

Bluefruit *BluefruitComms::getBluefruit()
{
	return this->communicator;
}

void BluefruitComms::factoryReset(void)
{
	if (FACTORYRESET_ENABLE)
	{
		Serial.println("Resetting bluefruit...");
		if (!communicator->factoryReset())
			error("Couldn't factory reset");
	}
}