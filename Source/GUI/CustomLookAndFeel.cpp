#include "CustomLookAndFeel.h"
void CustomLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)

{
    // slider properties
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setVelocityModeParameters(1.0, 1, 0.0, true, juce::ModifierKeys::shiftModifier);
    
    // calculate variables
    juce::Rectangle<float> bounds;
    bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto radius = bounds.getWidth() / 2.0f;
    auto lineWidth = 3.0f;
    auto arcRadius = radius - lineWidth / 2.0f;
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    float centerX = x + width * 0.5f;
    float centerY = y + height * 0.5f;
    
    // draw arc
    auto strokeType = juce::PathStrokeType(
            lineWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    juce::Path valueArc;
            valueArc.addCentredArc(centerX,
                centerY,
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                angle,
                true);
    g.setColour(juce::Colour(0xFF750002).brighter(0.2f));
    g.strokePath(valueArc, strokeType);
    
    // draw background
    auto backgroundImage = juce::ImageCache::getFromMemory(BinaryData::knob_bg_png, BinaryData::knob_bg_pngSize);
    juce::Rectangle<float> rectangle (x, y, width, height);
    rectangle = rectangle.reduced(10.f);
    g.setOpacity(1.f);
    g.drawImage(backgroundImage, rectangle, juce::RectanglePlacement::stretchToFit);
    
    // draw the foreground
    auto foregroundImage = juce::ImageCache::getFromMemory(BinaryData::knob_fg_png, BinaryData::knob_fg_pngSize);

    juce::AffineTransform transform = juce::AffineTransform::rotation(angle, centerX, centerY);

    g.setOpacity(1.0f);
    g.addTransform(transform);
    g.drawImage(foregroundImage, rectangle, juce::RectanglePlacement::stretchToFit);
}
