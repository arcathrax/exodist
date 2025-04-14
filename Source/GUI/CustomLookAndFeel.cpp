#include "CustomLookAndFeel.h"
void KnobLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)

{
    // slider properties
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setVelocityModeParameters(1.0, 1, 0.0, true, juce::ModifierKeys::shiftModifier);
    
    // cache the image
    auto image = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
    
    // calculate angle and centerpositions
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    float centerX = x + width * 0.5f;
    float centerY = y + height * 0.5f;

    // generate AffineTransform, based on the calculated angle and centerpos
    juce::AffineTransform transform = juce::AffineTransform::rotation(angle, centerX, centerY);
    juce::Rectangle<float> rectangle (x, y, width, height);

    // draw the Image
    g.setOpacity(1.0f);
    g.addTransform(transform);
    g.drawImage(image, rectangle, juce::RectanglePlacement::stretchToFit);
}
