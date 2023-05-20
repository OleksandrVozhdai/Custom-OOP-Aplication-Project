#include "BookListTable.h"
#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>
#include <vector>
#include <string>

const String IdName = "ID";
const String BookList = "Book list";

using namespace juce;

BookListTable::BookListTable()
{
    TableDemoComponent();
    loadData();
}

BookListTable::~BookListTable()
{

}

DataSorter::DataSorter(String attributeToSortBy) : attributeToSort(attributeToSortBy)
{
   
}

int BookListTable::TableDemoComponent()
{   
    addAndMakeVisible(table);
    table.setModel(this);

    // give it a border
    table.setColour(ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness(1);
    table.setBounds(0, 0, 300, 280);

    // Add some columns to the table header, based on the column list in our database..
    
    table.getHeader().addColumn(IdName, 1, 45);
    table.getHeader().addColumn(BookList, 2, 245);
   

    // we could now change some initial settings..
    table.getHeader().setSortColumnId(1, true); // sort forwards by the ID column
    table.getHeader().setColumnVisible(7, false); // hide the "length" column until the user shows it

    // un-comment this line to have a go of stretch-to-fit mode
    // table.getHeader().setStretchToFitActive (true);

    table.setMultipleSelectionEnabled(true);

    return 1;
}
int BookListTable::getNumRows()
{
    return numRows;
}

void BookListTable::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::white);

    if (rowIsSelected)
        g.setColour(juce::Colours::green);
    else
        g.setColour(juce::Colours::lightgrey);
    g.drawRect(0, 0, width, height);
}

void BookListTable::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::white);
    
    if (auto* rowElement = dataList->getChildElement(rowNumber))
    {
        auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

            if (text.startsWith(BookNameGetText))
            {
                g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);
            } 
    }    

    if (rowIsSelected)
    {
        g.setColour(juce::Colours::red);
        auto* rowElement = dataList->getChildElement(rowNumber);
        String IdNumber = rowElement->getStringAttribute("ID");
        String bookName = rowElement->getStringAttribute("Book");
        String authorName = rowElement->getStringAttribute("Autor");

        selectedBook = bookName;
        selectedAuthor = authorName;
        selectedID = IdNumber;
    }
    else
    {
        g.setColour(juce::Colours::grey);
    }
}


int BookListTable::getColumnAutoSizeWidth(int columnId)
{
    return NULL;
}

String BookListTable::getAttributeNameForColumnId(int columnId)
{
    for (auto* columnXml : columnList->getChildIterator())
    {
        if (columnXml->getIntAttribute("columnId") == columnId)
            return columnXml->getStringAttribute("name");
    }
    return {};
}



inline File getExamplesDirectory() noexcept
{
#ifdef PIP_JUCE_EXAMPLES_DIRECTORY
    MemoryOutputStream mo;

    auto success = Base64::convertFromBase64(mo, JUCE_STRINGIFY(PIP_JUCE_EXAMPLES_DIRECTORY));
    ignoreUnused(success);
    jassert(success);

    return mo.toString();
#elif defined PIP_JUCE_EXAMPLES_DIRECTORY_STRING
    return File{ CharPointer_UTF8 { PIP_JUCE_EXAMPLES_DIRECTORY_STRING } };
#else
    auto currentFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
    auto exampleDir = currentFile.getParentDirectory().getChildFile("examples");

    if (exampleDir.exists())
        return exampleDir;

    // keep track of the number of parent directories so we don't go on endlessly
    for (int numTries = 0; numTries < 15; ++numTries)
    {
        if (currentFile.getFileName() == "examples")
            return currentFile;

        const auto sibling = currentFile.getSiblingFile("examples");

        if (sibling.exists())
            return sibling;

        currentFile = currentFile.getParentDirectory();
    }

    return currentFile;
#endif
}

inline std::unique_ptr<InputStream> createAssetInputStream(const char* resourcePath)
{
#if JUCE_ANDROID
    ZipFile apkZip(File::getSpecialLocation(File::invokedExecutableFile));
    return std::unique_ptr<InputStream>(apkZip.createStreamForEntry(apkZip.getIndexOfFileName("assets/" + String(resourcePath))));
#else
#if JUCE_IOS
    auto assetsDir = File::getSpecialLocation(File::currentExecutableFile)
        .getParentDirectory().getChildFile("Assets");
#elif JUCE_MAC
    auto assetsDir = File::getSpecialLocation(File::currentExecutableFile)
        .getParentDirectory().getParentDirectory().getChildFile("Resources").getChildFile("Assets");

    if (!assetsDir.exists())
        assetsDir = getExamplesDirectory().getChildFile("Assets");
#else
    auto assetsDir = getExamplesDirectory().getChildFile("Assets");
#endif

    auto resourceFile = assetsDir.getChildFile(resourcePath);
    jassert(resourceFile.existsAsFile());

    auto ret = resourceFile.createInputStream();

    return ret;
#endif
}

inline String loadEntireAssetIntoString(const char* assetName)
{
    std::unique_ptr<InputStream> input(createAssetInputStream(assetName));

    if (input == nullptr)
        return {};

    return input->readString();
}

void BookListTable::loadData()
{
    auto str = loadEntireAssetIntoString("BookList.xml");
    demoData = parseXML(str);

    dataList = demoData->getChildByName("DATA");
    columnList = demoData->getChildByName("COLUMNS");
  
    numRows += dataList->getNumChildElements();
}

void BookListTable::sort()
{
    DataSorter sorter(BookNameGetText);
    dataList->sortChildElements(sorter);

    table.updateContent();

}

int DataSorter::compareElements(XmlElement* first, XmlElement* second) const
{
    String bookName1 = first->getStringAttribute("Book");
    String bookName2 = second->getStringAttribute("Book");


    if (bookName1.startsWith(attributeToSort) && bookName2.startsWith(attributeToSort))
    {
        return 0;
    }else
    if (bookName1.startsWith(attributeToSort))
    {
        return -1;
    } else
    if (bookName2.startsWith(attributeToSort))
    {
        return 1;
    } 
   
}