#pragma once

#include <JuceHeader.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "BookListTable.h"

using namespace juce;
class MainComponent : public juce::Component, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

   
   

private:
   
    juce::TextEditor BookName;
    juce::TextEditor BookAuthor;
    juce::TextEditor BookId;
    juce::TextButton FindBook;
    juce::TextButton AddBook;
    
    BookListTable table;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};