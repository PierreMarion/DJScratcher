#include "UIBuilder.h"


UIBuilder::UIBuilder(void)
{
	counter = 1;
}


UIBuilder::~UIBuilder(void)
{

}

void UIBuilder::createButton(tgui::Button::Ptr& button, string imageLoad, string text, int positionX, int positionY)
{
	button->load("TGUI/widgets/" + imageLoad + ".conf");
	button->setSize(100, 40);
	button->setPosition(positionX, positionY);
	button->setText(text);
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setCallbackId(counter++);
}

void UIBuilder::createSlider(tgui::Slider::Ptr& bassSlider, string imageLoad, int positionX, int positionY, int maxValue, int minValue, int startPosition)
{
	bassSlider->load("TGUI/widgets/" + imageLoad + ".conf");
	bassSlider->setMaximum(maxValue);
	bassSlider->setMinimum(minValue);
	bassSlider->setValue(startPosition);
	bassSlider->setVerticalScroll(false);
	bassSlider->setSize(300, 15);
	bassSlider->setPosition(positionX, positionY);
	bassSlider->bindCallback(tgui::Slider::ValueChanged);
	bassSlider->setCallbackId(counter++);
}
void UIBuilder::createLabel(tgui::Label::Ptr& label, string imageLoad, string text, int positionX, int positionY)
{
	label->load("TGUI/widgets/" + imageLoad + ".conf");
	label->setText(text);
	label->setSize(600, 35);
	label->setPosition(positionX, positionY);
}
void UIBuilder::createComboBox(tgui::ComboBox::Ptr& songList, string imageLoad, int positionX, int positionY)
{
	songList->load("TGUI/widgets/" + imageLoad + ".conf");
	songList->setPosition(positionX, positionY);
	songList->setSize(300, 30);
}

void UIBuilder::resetSliders(tgui::Slider::Ptr& bass, tgui::Slider::Ptr& medium, tgui::Slider::Ptr& trebble, tgui::Slider::Ptr& speed, tgui::Slider::Ptr& pitch)
{
	bass->setValue(100);
	medium->setValue(100);
	trebble->setValue(100);
	speed->setValue(10);
	pitch->setValue(10);
}
