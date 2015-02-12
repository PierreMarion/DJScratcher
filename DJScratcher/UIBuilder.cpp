#include "UIBuilder.h"
/**
Class constructing the whole application's visual
*/

/**
Constructor of the UIBuilder
*/
UIBuilder::UIBuilder(void)
{
	counter = 1;
}

/**
Destructor of the UIBuilder
*/
UIBuilder::~UIBuilder(void)
{

}

/**
Function creating the needed buttons on the application
param button a button object in TGUI
param imageLoad the button's visual
param text the button's text
param positionX  the button's horizontal position in the application
param positionY  the button's vertical position in the application
*/
void UIBuilder::createButton(tgui::Button::Ptr& button, string imageLoad, string text, int positionX, int positionY)
{
	button->load("TGUI/widgets/" + imageLoad + ".conf");
	button->setSize(100, 40);
	button->setPosition(positionX, positionY);
	button->setText(text);
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(counter++);
}
/**
Function creating the needed sliders on the application
param slider a slider object in TGUI
param imageLoad the slider's visual
param positionX  the slider's horizontal position in the application
param positionY  the slider's vertical position in the application
param maxValue the maximal value the slider can reach
param minValue the minimal value the slider can reach
param startPosition the value at which the slider is loaded by default
*/
void UIBuilder::createSlider(tgui::Slider::Ptr& slider, string imageLoad, int positionX, int positionY, int maxValue, int minValue, int startPosition)
{
	slider->load("TGUI/widgets/" + imageLoad + ".conf");
	slider->setMaximum(maxValue);
	slider->setMinimum(minValue);
	slider->setValue(startPosition);
	slider->setVerticalScroll(false);
	slider->setSize(300, 15);
	slider->setPosition(positionX, positionY);
	slider->bindCallback(tgui::Slider::ValueChanged);
	slider->setCallbackId(counter++);
}
/**
Function creating the needed Labels on the application
param label a label object in TGUI
param imageLoad the label's visual
param text the label's text
param positionX  the label's horizontal position in the application
param positionY  the label's vertical position in the application
*/
void UIBuilder::createLabel(tgui::Label::Ptr& label, string imageLoad, string text, int positionX, int positionY)
{
	label->load("TGUI/widgets/" + imageLoad + ".conf");
	label->setText(text);
	label->setSize(600, 35);
	label->setPosition(positionX, positionY);
}
/**
Function creating the needed comboBox on the application
param songList a comboBox object in TGUI
param imageLoad the comboBox's visual
param positionX  the comboBox's horizontal position in the application
param positionY  the comboBox's vertical position in the application
*/
void UIBuilder::createComboBox(tgui::ComboBox::Ptr& songList, string imageLoad, int positionX, int positionY)
{
	songList->load("TGUI/widgets/" + imageLoad + ".conf");
	songList->setPosition(positionX, positionY);
	songList->setSize(300, 30);
}
/**
Function that resets every sliders to their default values
param bass the bass equalizer's slider
param medium the medium equalizer's slider
param trebble the trebble equalizer's slider
param speed the speed equalizer's slider
param pitch the pitch equalizer's slider
*/
void UIBuilder::resetSliders(tgui::Slider::Ptr& bass, tgui::Slider::Ptr& medium, tgui::Slider::Ptr& trebble, tgui::Slider::Ptr& speed, tgui::Slider::Ptr& pitch)
{
	bass->setValue(100);
	medium->setValue(100);
	trebble->setValue(100);
	speed->setValue(10);
	pitch->setValue(10);
}
