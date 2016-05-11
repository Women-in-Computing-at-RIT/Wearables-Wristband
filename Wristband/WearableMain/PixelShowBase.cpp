#include "PixelShowBase.h"
#include "WearablesConstants.h"
#include "WearablesUtility.h"

ColorArray createColorArray(Color arr[], uint8_t size)
{
	ColorArray carr = { arr, size };
	return carr;
}

ColorArray copyColorArray(const ColorArray& original)
{
	ColorArray cpy;
	cpy.arr = new Color[original.size];
	cpy.size = original.size;
	
	WiCUtil::arrayCopy(original.arr, 0, cpy.arr, 0, original.size);

	return cpy;
}

void createColorArray(ColorArray& colorArray, Color arr[], uint8_t size)
{
	colorArray.arr = arr;
	colorArray.size = size;
}

void copyColorArray(const ColorArray& original, ColorArray& cpy)
{
	WiCUtil::arrayCopy(original.arr, original.size, cpy.arr, cpy.size);
}

void applyColorArray(ColorArray& colorArray, NeoPixel& strip)
{
	uint16_t nPixels = strip.numPixels();
	uint8_t nColors = colorArray.size;

	float scale = colorArray.stripOptions.colorScale;
	for (uint8_t i = 0; i < nColors && i < nPixels; i++) {
		Color& c = colorArray.arr[i];
		strip.setPixelColor(i, (uint32_t)(c.pixel * scale));
#if WiC_DEBUG
		uint8_t compos[4];
		dissectColor(c, compos);
		WiCLog::debug("Setting Pixel %u - R: %03u, G: %03u, B: %03u, W: %03u -- Hex: 0x%02X%02X%02X%02X, Val: %14lu", i, compos[0], compos[1], compos[2], compos[3], compos[0], compos[1], compos[2], compos[3], c.pixel);
#endif
	}

#if WiC_DEBUG
	WiCLog::debug("Setting Strip Gamma to %u - Override?: %s - Strip Gamma Was %u", colorArray.stripOptions.gamma, colorArray.stripOptions.gammaOverride ? "YES" : "NO", strip.getBrightness());
	WiCLog::debug("Pixel Scalar: %f", scale);
#endif

	if (colorArray.stripOptions.gammaOverride)
	{
		colorArray.stripOptions.gammaOverride = false;
		strip.setBrightness(colorArray.stripOptions.gamma);
	}
	else {
		colorArray.stripOptions.gamma = strip.getBrightness();
	}
}

FloraBoard::FloraBoard() : onboardPixel{1, ONBOARD_PIXEL_PIN, NEO_GRB + NEO_KHZ800}, ledOn(false), pixColor(0)
{
	this->onboardPixel.begin();
	 
	pinMode(ONBOARD_LED_PIN, OUTPUT);
}

FloraBoard::~FloraBoard()
{
	//delete this->onboardPixel;
}

void FloraBoard::setPixelBrightness(uint8_t brightness)
{
	this->onboardPixel.setBrightness(brightness);
}

void FloraBoard::setOnboardPixel(const Color& color)
{
	this->onboardPixel.setPixelColor(0, this->pixColor = color.pixel);
	this->onboardPixel.show();
}

void FloraBoard::setOnboardLed(boolean on)
{
	digitalWrite(ONBOARD_LED_PIN, (ledOn = on) ? HIGH : LOW);
}

uint8_t FloraBoard::getPixelBrightness(void)
{
	return this->onboardPixel.getBrightness();
}

uint32_t FloraBoard::getOnboardPixel(void)
{
	return this->pixColor;
}

boolean FloraBoard::getOnboardLed(void)
{
	return this->ledOn;
}

void FloraBoard::reset(void)
{
	Color col = createColor();
	this->setOnboardPixel(col);
	this->setOnboardLed(false);
	this->setPixelBrightness(0xFFu);

	this->onboardPixel.show();
}

ColorFunction::ColorFunction(){}

ColorFunction::ColorFunction(ColorFunction *inner) : inner(inner)
{}

ColorArray& ColorFunction::apply(ColorArray& input)
{
	if (this->inner != nullptr)
		this->inner->apply(input);

	this->mutate(input);
	return input;
}

ColorArray& ColorFunction::mutate(ColorArray& input)
{
	return input;
}

void ColorFunction::compose(ColorFunction& inner)
{
	ColorFunction *last = this;
	while (last->inner != nullptr)
		last = last->inner;

	last->inner = &inner;
}

ColorArray& ColorFunction::operator()(ColorArray& input)
{
	return this->apply(input);
}

void pixelColorWipe(NeoPixel& strip, const Color& color)
{
	for (uint16_t i = 0; i < strip.numPixels(); i++)
		strip.setPixelColor(i, color.pixel);
}