#pragma once
#include "TGUI\TGUI.hpp"
#include <string>
using namespace std;

class UIBuilder
{
public:
	UIBuilder(void);
	~UIBuilder(void);
	void createButton(tgui::Button::Ptr& button, string imageLoad, string text, int positionX, int positionY);
	void createSlider(tgui::Slider::Ptr& slider, string imageLoad, int positionX, int positionY, int maxValue, int minValue, int startValue);
	void createLabel(tgui::Label::Ptr& label, string imageLoad, string text, int positionX, int positionY);
	void createComboBox(tgui::ComboBox::Ptr& comboBox, string imageLoad, int positionX, int positionY);

	void resetSliders(tgui::Slider::Ptr& bass, tgui::Slider::Ptr& medium, tgui::Slider::Ptr& trebble, tgui::Slider::Ptr& speed, tgui::Slider::Ptr& pitch);

private:
	int counter;
};

