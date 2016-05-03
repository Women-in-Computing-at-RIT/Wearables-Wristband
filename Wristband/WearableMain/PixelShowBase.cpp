#include "PixelShowBase.h"

ColorArray::ColorArray(const Color colors[], uint8_t size) : length(size)
{
	size_t nbytes = size*sizeof(Color);

	this->arr = (Color *)malloc(nbytes);
	memcpy(this->arr, colors, nbytes);
}

ColorArray::ColorArray(const ColorArray& orig)
{
	size_t nbytes = orig.length * sizeof(Color);

	this->length = orig.length;
	this->arr = (Color *)malloc(nbytes);
	
	memcpy(this->arr, orig.arr, nbytes);
}

ColorArray::~ColorArray()
{
	free(this->arr);
}

Color& ColorArray::get(uint8_t i) const
{
	return this->arr[i];
}

void ColorArray::set(uint8_t i, Color& color)
{
	this->arr[i] = color;
}

uint8_t ColorArray::size(void) const
{
	return this->length;
}

void ColorArray::apply(NeoPixel& strip)
{
	uint16_t nPixels = strip.numPixels();
	uint8_t nColors = this->length;

	for (uint8_t i = 0; i < nColors && i < nPixels; i++)
		strip.setPixelColor(i, this->get(i).pixel);
}

FloraBoard::FloraBoard() : onboardPixel{ 1, ONBOARD_PIXEL_PIN, NEO_GRB + NEO_KHZ800 }, ledOn(false), pixColor(0)
{
	this->onboardPixel.begin();
	this->onboardPixel.show();

	pinMode(ONBOARD_LED_PIN, OUTPUT);
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

uint32_t FloraBoard::getOnboardPixel(void)
{
	return this->pixColor;
}

boolean FloraBoard::getOnboardLed(void)
{
	return this->ledOn;
}


ColorFunction::ColorFunction() : inner(nullptr)
{}

ColorFunction::ColorFunction(ColorFunction *inner) : inner(inner)
{}

ColorArray ColorFunction::apply(const ColorArray& input)
{
	ColorArray cpy = ColorArray(input);
	this->_apply(cpy);

	return cpy;
}

ColorArray& ColorFunction::_apply(ColorArray& input)
{
	if (this->inner != nullptr)
		this->inner->_apply(input);

	this->mutate(input);
	return input;
}

ColorArray& ColorFunction::mutate(ColorArray& input) const
{
	return input;
}

ColorFunction ColorFunction::operator+(ColorFunction& g)
{
	return CombinedColorFunction(*this, g);
}

ColorFunction ColorFunction::operator()(ColorFunction& g)
{
	return CombinedColorFunction(*this, g);
}

ColorArray ColorFunction::operator()(ColorArray& input)
{
	return this->apply(input);
}

CombinedColorFunction::CombinedColorFunction(ColorFunction& f, ColorFunction& g) : f(f), g(g)
{}

ColorArray& CombinedColorFunction::_apply(ColorArray& input)
{
	ColorArray& res = this->g._apply(input);
	res = this->f._apply(res);
	return res;
}

void pixelColorWipe(NeoPixel& strip, const Color& color)
{
	for (uint16_t i = 0; i < strip.numPixels(); i++)
		strip.setPixelColor(i, color.pixel);
}