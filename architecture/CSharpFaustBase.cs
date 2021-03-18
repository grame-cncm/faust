/************************************************************************
    FAUST Architecture File
    Copyright (C) 2021 Mike Oliphant
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

 ************************************************************************
 ************************************************************************/

using System;
using System.Collections.Generic;

public class FaustMetaData
{
    Dictionary<string, string> metaData = new Dictionary<string, string>();

    public void Declare(String name, String value)
    {
        metaData[name] = value;
    }

    public string GetValue(string name)
    {
        if (!metaData.ContainsKey(name))
            return null;

        return metaData[name];
    }
}

public class FaustVariableAccessor
{
    public string ID { get; set; }
    public Action<double> SetValue { get; set; }
    public Func<double> GetValue { get; set; }
}

public enum EFaustUIBoxType
{
}

public enum EFaustUIElementType
{
    TabBox,
    HorizontalBox,
    VerticalBox,
    Button,
    CheckBox,
    VerticalSlider,
    HorizontalSlider,
    NumEntry,
    HorizontalBargraph,
    VerticalBargraph
}

public class FaustUIElement
{
    public EFaustUIElementType ElementType { get; set; }
    public string Label { get; set; }
}

public class FaustBoxElement : FaustUIElement
{
    public List<FaustUIElement> Children { get; set; }

    public FaustBoxElement(EFaustUIElementType elementType, string label)
    {
        this.ElementType = elementType;
        this.Label = label;
        this.Children = new List<FaustUIElement>();
    }
}

public class FaustUIVariableElement : FaustUIElement
{
    public FaustVariableAccessor VariableAccessor { get; set; }

    public FaustUIVariableElement(EFaustUIElementType elementType, string label, FaustVariableAccessor variableAccessor)
    {
        this.ElementType = elementType;
        this.Label = label;
        this.VariableAccessor = variableAccessor;
    }
}

public class FaustUIFloatElement : FaustUIVariableElement
{
    public double MinValue { get; set; }
    public double MaxValue { get; set; }

    public FaustUIFloatElement(EFaustUIElementType elementType, string label, FaustVariableAccessor variableAccessor, double minValue, double maxValue)
        : base(elementType, label, variableAccessor)
    {
        this.MinValue = minValue;
        this.MaxValue = maxValue;
    }
}

public class FaustUIWriteableFloatElement : FaustUIFloatElement
{
    public double Step { get; set; }
    public double DefaultValue { get; set; }

    public FaustUIWriteableFloatElement(EFaustUIElementType elementType, string label, FaustVariableAccessor variableAccessor, double defaultValue, double minValue, double maxValue, double step)
        : base(elementType, label, variableAccessor, minValue, maxValue)
    {
        this.DefaultValue = defaultValue;
        this.Step = step;
    }
}

public class FaustUIDefinition
{
    public FaustUIElement RootElement { get; set; }

    Stack<FaustBoxElement> boxStack = new Stack<FaustBoxElement>();

    public void DeclareElementMetaData(string elemendID, string key, string value)
    {
    }

    public void StartBox(FaustBoxElement box)
    {
        if (boxStack.Count == 0)
        {
            RootElement = box;
        }
        else
        {
            boxStack.Peek().Children.Add(box);
        }

        boxStack.Push(box);
    }

    public void EndBox()
    {
        boxStack.Pop();
    }

    public void AddElement(FaustUIElement element)
    {
        boxStack.Peek().Children.Add(element);
    }
}

public interface IFaustDSP
{
    FaustUIDefinition UIDefinition { get; }
    FaustMetaData MetaData { get; }

    int GetNumInputs();
    int GetNumOutputs();
    int GetInputRate(int channel);
    int GetOutputRate(int channel);
    void ClassInit(int sample_rate);
    void InstanceConstants(int sample_rate);
    void InstanceResetUserInterface();
    void InstanceClear();
    void Init(int sample_rate);
    void InstanceInit(int sample_rate);
    void Compute(int count, double[][] inputs, double[][] outputs);
}

public class dsp
{
    public FaustUIDefinition UIDefinition { get; private set; }
    public FaustMetaData MetaData { get; private set; }

    public dsp()
    {
        UIDefinition = new FaustUIDefinition();
        MetaData = new FaustMetaData();
    }

    public static double FMod(double val1, double val2)
    {
        return val1 % val2;
    }

    public static float FModF(float val1, float val2)
    {
        return val1 % val2;
    }
}


