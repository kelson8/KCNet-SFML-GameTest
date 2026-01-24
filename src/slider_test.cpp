#include "slider_test.h"

#ifdef KC_SLIDER_TEST

#include "SliderSFML.h"

// https://github.com/N4G1/Slider-SFML



void SliderTest::DisplaySlider(sf::RenderWindow& window)
{
	SliderSFML slider1(100, 100);

	slider1.create(20, 450);
	slider1.setSliderValue(235);
	slider1.draw(window);
}

#endif // KC_SLIDER_TEST