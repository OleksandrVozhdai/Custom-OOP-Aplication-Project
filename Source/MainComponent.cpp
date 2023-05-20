#include "MainComponent.h"
#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>



using namespace juce;

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 800);

    addAndMakeVisible(&BookName);
    addAndMakeVisible(&BookAuthor);
    addAndMakeVisible(&BookId);
    BookName.setBounds(20, 200, 140, 40);
    BookName.setFont(20.0f);
    BookName.setTextToShowWhenEmpty("Book name", juce::Colours::grey);
    BookAuthor.setBounds(20, 260, 140, 40);
    BookAuthor.setFont(20.0f);
    BookAuthor.setTextToShowWhenEmpty("Book author", juce::Colours::grey);
    BookId.setBounds(20, 320, 140, 40);
    BookId.setFont(20.0f);
    BookId.setTextToShowWhenEmpty("Book ID", juce::Colours::grey);
    addAndMakeVisible(&FindBook);
    addAndMakeVisible(&AddBook);
   
    AddBook.setBounds(20, 440, 140, 40);
    AddBook.setButtonText("Add Book");
  
    FindBook.setBounds(20, 380, 140, 40);
    FindBook.setButtonText("Find Book");
  
    startTimer(100);
    addAndMakeVisible(table);
    table.setBounds(260, 200, 300, 280);

    

}

MainComponent::~MainComponent()
{
}



//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
   
    
   
        juce::Font ShelfSpaceFont(64.0f, juce::Font::bold);
        g.setFont(ShelfSpaceFont);
        g.setColour(juce::Colours::white);
        g.drawText("ShelfSpace", -20, -150, 400, 400, juce::Justification::centred, true);
        
        juce::Font InformationFont(32.0f, juce::Font::bold);
        g.setFont(InformationFont);
        g.setColour(juce::Colours::white);
        g.drawText("Information", 10, 440, 200, 200, juce::Justification::centred, true);
    
        juce::Font Infofont(32.0f);
        g.setFont(Infofont);

        g.drawText("Name: ", 20, 500, 200, 200, juce::Justification::left, true);
        g.drawText("Author: ", 20, 550, 200, 200, juce::Justification::left, true);
        g.drawText("ID: ", 20, 600, 200, 200, juce::Justification::left, true);

        g.drawText(table.selectedBook, 120, 500, 600, 200, juce::Justification::left, true);
        g.drawText(table.selectedAuthor, 130, 550, 600, 200, juce::Justification::left, true);
        g.drawText(table.selectedID, 80, 600, 600, 200, juce::Justification::left, true);
}



void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::timerCallback()
{

    table.BookNameGetText = BookName.getText();
    table.BookAuthorGetText = BookAuthor.getText();
    table.BookIdGetText = BookId.getText();




    repaint();
}


