/************************** BEGIN LayoutUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
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
 ******************************************************************************/

struct LayoutUI : public GenericUI, public PathBuilder, public MetaDataUI
{
    // Definition of the elements standard size
    
    #define kKnobWidth 10.f
    #define kKnobHeight 10.f
    
    #define kVSliderWidth 10.f
    #define kVSliderHeight 25.f
    
    #define kHSliderWidth 25.f
    #define kHSliderHeight 10.f
    
    #define kButtonWidth 10.f
    #define kButtonHeight 10.f

    #define kCheckButtonWidth 10.f
    #define kCheckButtonHeight 10.f
    
    #define kNumEntryWidth 10.f
    #define kNumEntryHeight 10.f
    
    #define kVBargraphWidth 10
    #define kVBargraphHeight 20
    
    #define kHBargraphWidth 20
    #define kHBargraphHeight 10

    // Base class
    struct UIItem {
        
        UIItem(float width = 0.0f, float height = 0.0f):fWidth(width), fHeight(height) {}
        virtual ~UIItem() {}
        
        typedef std::shared_ptr<UIItem> shared_item;
        
        float fBorderX = 0.f;
        float fBorderY = 0.f;
        
        float fWidth = 0.f;
        float fHeight = 0.f;
        
        float fTopX = 0.f;
        float fTopY = 0.f;
        
        float fHRatio = 1.f;
        float fVRatio = 1.f;
        
        float getTopX() { return fTopX; };
        float getTopY() { return fTopY; };
        
        float getBorderX() { return fBorderX; };
        float getBorderY() { return fBorderY; };
        
        float getHRatio() { return fHRatio; };
        float getVRatio() { return fVRatio; };
        
        virtual float getWidth() { return fWidth; }
        virtual float getHeight() { return fHeight; }
        
        virtual void setRatio(float rx, float ry) {};
        
        // adapt all leave size and position
        virtual void resize(float width, float height) {}
        
        virtual std::ostream& print(std::ostream& file) = 0;
    
    };
    
    // Grouping classes
    struct Group : UIItem {
        
        typedef std::shared_ptr<Group> shared_group;
        
        std::vector <UIItem::shared_item> fItems;
        
        virtual ~Group()
        {}
        
        void add(UIItem::shared_item item) { fItems.push_back(item); }
        
        void resize(float width, float height) override
        {
            float real_width = width - fBorderX;
            float real_height = height - fBorderY;
            for (auto& it : fItems) {
                it->resize(real_width * it->getHRatio(), real_height * it->getVRatio());
            }
        };
        
        virtual std::ostream& print(std::ostream& file) override { return file; }
        
    };
    
    struct HGroup : Group {
        
        void setRatio(float rx, float ry) override
        {
            for (auto& it : fItems) {
                it->setRatio(rx/fItems.size(), ry);
            }
        };
        
        float getHRatio() { return 1.f; };
        float getVRatio() { return 1.f; };
        
        float getWidth() override
        {
            float res = 0.f;
            for (auto& it : fItems) {
                res += it->getWidth();
            }
            return res;
        }
        
        float getHeight() override
        {
            float res = 0.f;
            for (auto& it : fItems) {
                res = std::max(res, it->getHeight());
            }
            return res;
        }
        
    };
    
    struct VGroup : Group {
        
        void setRatio(float rx, float ry) override
        {
            for (auto& it : fItems) {
                it->setRatio(rx, ry/fItems.size());
            }
        };
        
        float getHRatio() { return 1.f; };
        float getVRatio() { return 1.f; };
        
        float getWidth() override
        {
            float res = 0.f;
            for (auto& it : fItems) {
                res = std::max(res, it->getWidth());
            }
            return res;
        }
        
        float getHeight() override
        {
            float res = 0.f;
            for (auto& it : fItems) {
                res += it->getHeight();
            }
            return res;
        }
        
    };
    
    // Terminal items
    struct Button : UIItem {
        
        Button():UIItem(kButtonWidth, kButtonHeight) {}
        
        virtual std::ostream& print(std::ostream& file) override
        {
            file << "----------Button----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct CheckButton : UIItem {
        
        CheckButton():UIItem(kCheckButtonWidth, kCheckButtonHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------CheckButton----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct HSlider : UIItem {
        
        HSlider():UIItem(kVSliderWidth, kVSliderHeight) {}
        
        virtual std::ostream& print(std::ostream& file) override
        {
            file << "----------HSlider----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct VSlider : UIItem {
        
        VSlider():UIItem(kHSliderWidth, kHSliderHeight) {}
        
        virtual std::ostream& print(std::ostream& file) override
        {
            file << "----------VSlider----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct NumEntry : UIItem {
        
        NumEntry():UIItem(kNumEntryWidth, kNumEntryHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------NumEntry----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct HBargraph : UIItem {
        
        HBargraph():UIItem(kHBargraphWidth, kHBargraphHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------HBargraph----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    struct VBargraph : UIItem {
        
        VBargraph():UIItem(kVBargraphWidth, kVBargraphHeight) {}
        
        std::ostream& print(std::ostream& file) override
        {
            file << "----------VBargraph----------" << std::endl;
            file <<"fWidth = " << fWidth << " fHeight = " << fHeight << std::endl;
            file << "fTopX = " << fTopX << " fTopY = " << fTopY << std::endl;
            file << "fHRatio = " << fHRatio << " fVRatio = " << fVRatio << std::endl;
            file << "--------------------------" << std::endl;
            return file;
        }
    };
    
    Group::shared_group fCurrentGroup = nullptr;
    std::stack<Group::shared_group> fGroupStack;
    std::map<std::string, UIItem::shared_item> fPathItemMap;

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

    // -- widget's layouts

    virtual void openTabBox(const char* label) override
    {
        pushLabel(label);
    }

    virtual void openHorizontalBox(const char* label) override
    {
        addGroup(label, std::make_shared<HGroup>());
    }

    virtual void openVerticalBox(const char* label) override
    {
        addGroup(label, std::make_shared<VGroup>());
    }

    virtual void closeBox() override
    {
        popLabel();
        if (fGroupStack.empty()) {
            // Adjust ratio in all leaves
            fCurrentGroup->setRatio(1, 1);
        } else {
            fCurrentGroup = fGroupStack.top();
            fGroupStack.pop();
        }
    }

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) override
    {
        addItem(label, std::make_shared<Button>());
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override
    {
        addItem(label, std::make_shared<CheckButton>());
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<VSlider>());
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<HSlider>());
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
    {
        addItem(label, std::make_shared<NumEntry>());
    }

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    {
        addItem(label, std::make_shared<HBargraph>());
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
    {
        addItem(label, std::make_shared<VBargraph>());
    }

    // -- metadata declarations

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) override
    {
        MetaDataUI::declare(zone, key, val);
    }
    
};


#endif // FAUST_LAYOUTUI_H
/**************************  END  LayoutUI.h **************************/
