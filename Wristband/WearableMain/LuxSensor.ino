#if WiC_LUX_SENSOR_CODE
#include <Adafruit_Sensor.h>
#include <pgmspace.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

boolean configureLux()
{
	if (!tsl.begin())
		return false;

	tsl.enableAutoRange(true);
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
	return true;
}

void luxLoop()
{
	sensors_event_t event;
	tsl.getEvent(&event);

	if (event.light)
	{
		Serial.print("Light Level: "); Serial.print(event.light); Serial.println(" lux");
		strip.setBrightness((uint8_t)floor(255 - 0.0255*event.light));
	}
}

#endif