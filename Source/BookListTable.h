#pragma once

#include <JuceHeader.h>
#include <juce_gui_extra/juce_gui_extra.h>

using namespace juce;
class DataSorter;

class BookListTable : public juce::Component, public juce::TableListBoxModel
{
public:

    BookListTable();
    ~BookListTable() override;

    int TableDemoComponent();
    int getNumRows() override;
    int numRows = 0;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool /*rowIsSelected*/) override;
    int getColumnAutoSizeWidth(int columnId) override;
    void loadData();
    String getAttributeNameForColumnId(int columnId);
    
    int getID(const int RowNumber);
    void setID(const int rowNumber, const int newID);
   
    String selectedBook;
    String selectedAuthor;
    String selectedID;

   String BookNameGetText;
   String BookAuthorGetText;
   String BookIdGetText;



   std::vector<char> arr;
   std::vector<char> originalarray;
   std::vector<char> userarray;

private:
    juce::TableListBox table;
    
    std::unique_ptr<juce::XmlElement> demoData;
    juce::XmlElement* columnList = nullptr;
    juce::XmlElement* RowList = nullptr;
    juce::XmlElement* dataList = nullptr;
    
    juce::XmlElement* IdList = nullptr;


    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BookListTable)
};


class DataSorter : public juce::Component, public juce::TableListBoxModel
{
public:
    DataSorter(const String& attributeToSortBy);
    ~DataSorter() override;

    int compareElements(XmlElement* first, XmlElement* second) const;

    String attributeToSort;
    int direction;

    String bookName1;
    String bookName2;
private:
};