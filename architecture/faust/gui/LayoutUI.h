/************************** BEGIN LayoutUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_LAYOUTUI_H
#define FAUST_LAYOUTUI_H

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <iostream>
#include <ostream>

#include "faust/gui/DecoratorUI.h"
#include "faust/gui/PathBuilder.h"
#include "faust/gui/MetaDataUI.h"

/*******************************************************************************
 * LayoutUI
 * This section defines the LayoutUI structure and associated classes.
 ******************************************************************************/

// Struct defining standard sizes for UI elements like knobs, sliders, buttons, etc.

struct LayoutItemSize {
    
    float kKnobWidth = 10.f;
    float kKnobHeight = 10.f;

    float kVSliderWidth = 10.f;
    float kVSliderHeight = 25.f;

    float kHSliderWidth = 25.f;
    float kHSliderHeight = 10.f;

    float kButtonWidth = 10.f;
    float kButtonHeight = 10.f;

    float kCheckButtonWidth = 10.f;
    float kCheckButtonHeight = 10.f;

    float kNumEntryWidth = 20.f;
    float kNumEntryHeight = 10.f;

    float kVBargraphWidth = 10.f;
    float kVBargraphHeight = 20.f;

    float kHBargraphWidth = 20.f;
    float kHBargraphHeight = 10.f;
    
    float kBorderX = 5.f;
    float kBorderY = 5.f;
    
};

// Global variable for item sizes
static LayoutItemSize gItemSize;

/**
 Main LayoutUI class inheriting from GenericUI, PathBuilder, and MetaDataUI.
 All UI leave items have a (x,y) position and a (width,height) size, and are kept in a hierarchy of Groups.
 The size of items (leaves and groups) can be read with getWidth/getHeight, and their position with getPosX/getPosY.
 The size of items (leaves and groups) can be set with setSize, and their position with setPos.
 
 The idea is to:
 - build the hierarchy of Groups using buildUserInterface, a top group (fCurrentGroup field) is created
 - the top group size can be read using getWidth/getHeight,
 - the top group size is set using setSize, so that all leave item size are set
 - the position is set using setPos, so that all leave item position are set
*/
struct LayoutUI : public GenericUI, public PathBuilder, public MetaDataUI
{

    // Base UI item class
    struct BaseUIItem {
        
        typedef std::shared_ptr<BaseUIItem> shared_item;
      
        std::string fLabel;
        
        BaseUIItem(const std::string& label):fLabel(label) {}
        virtual ~BaseUIItem() {}
        
        virtual float getPosX() { return 0.f; };
        virtual float getPosY() { return 0.f; };
        
        virtual float getBorderX() { return 0.f; };
        virtual float getBorderY() { return 0.f; };
        
        virtual float getWidth() { return 0.f; };
        virtual float getHeight() { return 0.f; };
        
        virtual void setSize(float width, float height) {}
        virtual void setPos(float top_x, float top_y) {}
        
        virtual std::ostream& print(std::ostream& file) { return file; }
    };
    
    // Derived class for leaf UI elements
    struct UIItem : BaseUIItem  {
        
        float fBorderX = 0.f;
        float fBorderY = 0.f;
        
        float fWidth = 0.f;
        float fHeight = 0.f;
        
        float fPosX = 0.f;
        float fPosY = 0.f;
        
        UIItem(const std::string& label,
                    float width = 0.0f,
                    float height = 0.0f)
            :BaseUIItem(label), fWidth(width), fHeight(height) {}
       
        float getPosX() override { return fPosX; };
        float getPosY() override { return fPosY; };
        
        float getBorderX() override { return fBorderX; };
        float getBorderY() override { return fBorderY; };
        
        float getWidth() override { return fWidth; }
        float getHeight() override { return fHeight; }
        
        // Adapt all leave sizes
        void setSize(float width, float height) override
        {
            fWidth = width;
            fHeight = height;
        }
        
        // Adapt all leave positions
        void setPos(float top_x, float top_y) override
        {
            fPosX = top_x;
            fPosY = top_y;
        }
        
        std::ostream& print(std::ostream& file) override
        {
            file << "Label = " << fLabel << std::endl;
            file << "fPosX = " << fPosX << " fPosY = " << fPosY << std::endl;
            file << "fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    // Base grouping class for UI items
    struct Group : UIItem {
        
        typedef std::shared_ptr<Group> shared_group;
        
        std::vector <UIItem::shared_item> fItems;
        
        Group(const std::string& label):UIItem(label)
        {}
        virtual ~Group()
        {}
        
        void add(UIItem::shared_item item) { fItems.push_back(item); }
        
        // Base implementation
        virtual void setSize(float width, float height) override
        {
            float real_width = getWidth() - getBorderX();
            float real_height = getHeight() - getBorderY();
            
            float w_ratio = width / real_width;
            float h_ratio = height / real_height;
            
            for (const auto& it : fItems) {
                it->setSize(it->getWidth() * w_ratio, it->getHeight() * h_ratio);
            }
        }
        
    };
    
    /**
     For an horizontal group:
        - width is the sum of all item width
        - height is the max of all item height
        - items x pos is moving by each consecutive item width
        - all items have the same y pos
     */
    struct HGroup : Group {
        
        HGroup(const std::string& label):Group(label)
        {}
        
        float getWidth() override
        {
            float res = 0.f;
            for (const auto& it : fItems) {
                res += it->getWidth();
            }
            return res;
        }
        
        float getHeight() override
        {
            float res = 0.f;
            for (const auto& it : fItems) {
                res = std::max(res, it->getHeight());
            }
            return res;
        }
        
        void setPos(float top_x, float top_y) override
        {
            for (const auto& it : fItems) {
                it->setPos(top_x, top_y);
                top_x += it->getWidth();
            }
        }
        
        void setSize(float width, float height) override
        {
            float real_width = getWidth() - getBorderX();
            float real_height = getHeight() - getBorderY();
            
            float w_ratio = width / real_width;
            float h_ratio = height / real_height;
            
            // Force all items height with real_height
            for (const auto& it : fItems) {
                it->setSize(it->getWidth() * w_ratio, real_height * h_ratio);
            }
        }
        
    };
    
    /**
     For a vertical group:
        - width is the max of all item width
        - height is the sum of all item height
        - items y pos is moving by each consecutive item height
        - all items have the same x pos
     */
    struct VGroup : Group {
        
        VGroup(const std::string& label):Group(label)
        {}
        
        float getWidth() override
        {
            float res = 0.f;
            for (const auto& it : fItems) {
                res = std::max(res, it->getWidth());
            }
            return res;
        }
        
        float getHeight() override
        {
            float res = 0.f;
            for (const auto& it : fItems) {
                res += it->getHeight();
            }
            return res;
        }
        
        void setPos(float top_x, float top_y) override
        {
            for (const auto& it : fItems) {
                it->setPos(top_x, top_y);
                top_y += it->getHeight();
            }
        }
        
        void setSize(float width, float height) override
        {
            float real_width = getWidth() - getBorderX();
            float real_height = getHeight() - getBorderY();
            
            float w_ratio = width / real_width;
            float h_ratio = height / real_height;
            
            // Force all items width with real_width
            for (const auto& it : fItems) {
                it->setSize(real_width * w_ratio, it->getHeight() * h_ratio);
            }
        }
        
    };
    
    // Terminal item classes representing various UI elements
    struct Button : UIItem {
        
        Button(const std::string& label):UIItem(label, gItemSize.kButtonWidth, gItemSize.kButtonHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------Button----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct CheckButton : UIItem {
        
        CheckButton(const std::string& label):UIItem(label, gItemSize.kCheckButtonWidth, gItemSize.kCheckButtonHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------CheckButton----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct HSlider : UIItem {
        
        HSlider(const std::string& label):UIItem(label, gItemSize.kHSliderWidth, gItemSize.kHSliderHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------HSlider----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct VSlider : UIItem {
        
        VSlider(const std::string& label):UIItem(label, gItemSize.kVSliderWidth, gItemSize.kVSliderHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------VSlider----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct NumEntry : UIItem {
        
        NumEntry(const std::string& label):UIItem(label, gItemSize.kNumEntryWidth, gItemSize.kNumEntryHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------NumEntry----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct HBargraph : UIItem {
        
        HBargraph(const std::string& label):UIItem(label, gItemSize.kHBargraphWidth, gItemSize.kHBargraphHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------HBargraph----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    struct VBargraph : UIItem {
        
        VBargraph(const std::string& label):UIItem(label, gItemSize.kVBargraphWidth, gItemSize.kVBargraphHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------VBargraph----------" << std::endl;
            return UIItem::print(file);
        }
    };
    
    // Attributes for managing groups and UI elements
    Group::shared_group fCurrentGroup = nullptr;
    std::stack<Group::shared_group> fGroupStack;
    std::map<std::string, UIItem::shared_item> fPathItemMap;

    // Method definitions for adding and managing UI elements and groups
    void addItem(const char* label, UIItem::shared_item item)
    {
        fPathItemMap[buildPath(label)] = item;
        fCurrentGroup->add(item);
    }

    void addGroup(const char* label, Group::shared_group group)
    {
        pushLabel(label);
        if (fCurrentGroup) {
            fCurrentGroup->add(group);
            fGroupStack.push(fCurrentGroup);
        }
        fCurrentGroup = group;
    }

    LayoutUI() {}
    virtual ~LayoutUI() {}
    
    float getWidth()
    {
        return fCurrentGroup->getWidth();
    }
    
    float getHeight()
    {
        return fCurrentGroup->getHeight();
    }
    
    void setSize(float width, float height)
    {
        fCurrentGroup->setSize(width, height);
    }
    
    void setPos(float x_pos, float y_pos)
    {
        fCurrentGroup->setPos(x_pos, y_pos);
    }
    
    void setPosAndSize(float x_pos, float y_pos, float width, float height)
    {
        fCurrentGroup->setSize(width, height);
        fCurrentGroup->setPos(x_pos, y_pos);
    }

    // -- widget's layouts

    virtual void openTabBox(const char* label) override
    {
        pushLabel(label);
    }

    virtual void openHorizontalBox(const char* label) override
    {
        addGroup(label, std::make_shared<HGroup>(label));
    }

    virtual void openVerticalBox(const char* label) override
    {
        addGroup(label, std::make_shared<VGroup>(label));
    }

    virtual void closeBox() override
    {
        popLabel();
        if (fGroupStack.empty()) {
            // Nothing for now
        } else {
            fCurrentGroup = fGroupStack.top();
            fGroupStack.pop();
        }
    }

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) override
    {
        addItem(label, std::make_shared<Button>(label));
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
        addItem(label, std::make_shared<CheckButton>(label));
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<VSlider>(label));
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<HSlider>(label));
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<NumEntry>(label));
    }

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    {
        addItem(label, std::make_shared<HBargraph>(label));
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    {
        addItem(label, std::make_shared<VBargraph>(label));
    }

    // -- metadata declarations

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) override
    {
        MetaDataUI::declare(zone, key, val);
    }
};

// Generic print function for UI items
template <typename T>
inline std::ostream& operator<<(std::ostream& file, std::shared_ptr<T> item)
{
    return item->print(file);
}

#endif // FAUST_LAYOUTUI_H
/**************************  END  LayoutUI.h **************************/
