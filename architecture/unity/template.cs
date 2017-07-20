using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using UnityEngine;


#if UNITY_EDITOR
using UnityEditor;

[CustomEditor(typeof(model))]
public class model_Editor : Editor {
    
    public float[] paramtab1;
    public float[] paramtab2;
    private model _dsp;
    private string fJSON;
    private FaustUI_UI fUI;
    
    private void OnEnable() {
        fJSON = "tototata";
        fUI = FaustUI_UI.ReadJSONUi (fJSON);
        fUI.getUI (0).setNumParams ();
        _dsp = (model)target;
        paramtab1 = new float[variables];
        paramtab2 = new float[variables];
    }
    
    public override void OnInspectorGUI() {
        GUI.enabled = true;
        GUILayout.BeginVertical ();
        EditorGUILayout.BeginHorizontal ();
        GUILayout.FlexibleSpace ();
        if(GUILayout.Button(new GUIContent("Initialization", "Set initial values"), GUILayout.Width(100), GUILayout.Height(20))){
            for (int i = 0; i < variables; i++) {
                changeValueParam (0f, fUI.getUI (0).getItem (i).init, i);
            }
        }
        GUILayout.FlexibleSpace ();
        GUILayout.EndHorizontal ();
        EditorGUILayout.HelpBox ("To control a parameter using scripts, use the parameter number and the setFloatParameter() method", MessageType.Info);
        if (fUI.getUI(0).type == "hgroup" || fUI.getUI(0).type == "vgroup" || fUI.getUI(0).type == "tgroup")
        {
            EditorGUILayout.BeginVertical ();
            fUI.getUI(0).groupstate = EditorGUILayout.Foldout (fUI.getUI(0).groupstate, fUI.getUI (0).label);
            EditorGUI.indentLevel++;
            if (fUI.getUI (0).groupstate) {
                for (int i = 0; i < fUI.getUI (0).items.Length; i++) {
                    makeLayoutGrp (fUI.getUI (0).items [i]);
                }
                EditorGUILayout.EndVertical ();
            }
            EditorGUI.indentLevel--;
        }
        EditorGUI.indentLevel--;
        EditorGUILayout.EndVertical ();
    }
    
    void progressBar (float value, Group_UI item) {
        EditorGUILayout.Space();
        EditorGUILayout.BeginHorizontal ();
        if (item.label == "0x00")
        item.label = "";
        Rect rect = GUILayoutUtility.GetRect (18, 18, "TextField");
        EditorGUI.ProgressBar (rect, (value-item.min)/(item.max-item.min), item.label);
        Repaint();
        EditorGUILayout.EndHorizontal ();
        EditorGUILayout.Space();
        
    }
    
    float hSlider (float value, Group_UI item){
        EditorGUILayout.BeginHorizontal ();
        if (item.label == "0x00")
        item.label = "";
        float newvalue = EditorGUILayout.Slider (new GUIContent(item.label, helpBox(item)), value, item.min, item.max);
        EditorGUILayout.EndHorizontal ();
        return newvalue;
    }
    
    float numEntry(float value, Group_UI item){
        EditorGUILayout.BeginHorizontal ();
        if (item.label == "0x00")
        item.label = "";
        float newvalue = EditorGUILayout.FloatField(new GUIContent(item.label, helpBox(item)), value );
        EditorGUILayout.EndHorizontal ();
        return newvalue;
    }
    
    float checkBox (float value, Group_UI item){
        EditorGUILayout.BeginHorizontal ();
        if (item.label == "0x00")
        item.label = "";
        bool temp1 = Convert.ToBoolean (value);
        bool temp2 = EditorGUILayout.Toggle(new GUIContent(item.label,helpBox(item)), temp1) ;
        float newvalue = Convert.ToSingle (temp2);
        EditorGUILayout.EndHorizontal ();
        return newvalue;
    }
    
    float button(Group_UI item){
        EditorGUILayout.BeginHorizontal ();
        if (item.label == "0x00")
        item.label = "";
        if (GUILayout.Button (new GUIContent(item.label, helpBox(item)))) {
            EditorGUILayout.EndHorizontal ();
            return 1;
        } else {
            EditorGUILayout.EndHorizontal ();
            return 0;
        }
    }
    
    string helpBox (Group_UI item)
    {
        string message;
        message = "Parameter Number : " + item.numparam;
        if (item.meta != null) {
            for(int i=0; i< item.meta.Length; i++){
                if (item.meta[i].unit != null) {
                    message += "\nUnit : " + item.meta[i].unit;
                }
                if (item.meta[i].scale != null) {
                    message += "\nScale : " + item.meta[i].scale;
                }
                if (item.meta[i].tooltip != null) {
                    message += "\nDescription : " + item.meta[i].tooltip;
                }
            }
        }
        return message;
    }
    
    void addComponent(Group_UI item){
        int numparam = item.numparam;
        if (item.type == "vslider" || item.type == "hslider") {
            paramtab1 [numparam] = _dsp.getFloatParameter (numparam);
            paramtab2 [numparam] = hSlider (paramtab1 [numparam], item);
            changeValueParam (paramtab1 [numparam], paramtab2 [numparam], numparam);
        } else if (item.type == "nentry"){
            paramtab1 [numparam] = _dsp.getFloatParameter (numparam);
            paramtab2 [numparam] = numEntry (paramtab1[numparam], item);
            changeValueParam (paramtab1 [numparam], paramtab2 [numparam], numparam);
        } else if (item.type == "checkbox") {
            paramtab1 [numparam] = _dsp.getFloatParameter (numparam);
            paramtab2 [numparam] = checkBox(paramtab1[numparam], item);
            changeValueParam (paramtab1 [numparam], paramtab2 [numparam], numparam);
        } else if (item.type == "button") {
            paramtab1 [numparam] = _dsp.getFloatParameter (numparam);
            paramtab2 [numparam] = button(item);
            changeValueParam (paramtab1 [numparam], paramtab2 [numparam], numparam);
        } else if (item.type == "hbargraph" || item.type == "vbargraph"){
            paramtab1 [numparam] = _dsp.getFloatParameter (numparam);
            progressBar(paramtab1[numparam], item);
        }
    }
    
    void makeLayoutGrp (Group_UI item){
        if (item.items != null){
            if (item.type == "hgroup" || item.type == "vgroup" || item.type == "tgroup") {
                EditorGUILayout.BeginVertical ();
                item.groupstate = EditorGUILayout.Foldout (item.groupstate, item.label);
                
                if (item.groupstate) {
                    EditorGUI.indentLevel++;
                    for (int i = 0; i < item.items.Length; i++) {
                        makeLayoutGrp (item.items [i]);
                    }
                    EditorGUI.indentLevel--;
                }
                EditorGUILayout.EndVertical();
            }
        } else {
            addComponent(item);
        }
    }
    
    void changeValueParam (float value, float newvalue, int param){
        if (newvalue != value) {
            _dsp.setFloatParameter (param, newvalue);
        }
    }
    
    string readJSONFile(){
        TextReader reader;
        string fileName = "Assets/Resources/model.json";
        reader = new StreamReader(fileName);
        string fJSON = reader.ReadToEnd();
        reader.Close();
        return fJSON;
    }
}

#endif // UNITY_EDITOR


[RequireComponent (typeof (AudioSource))]
public class model : MonoBehaviour
{
    
    public float[] parameter = new float[variables];
    private Faust_Ctx ctx;
    
    public bool IsInstantiated() { return (ctx != null); }
    
    public float getFloatParameter (int param) {
        
        if (IsInstantiated ()) {
            return ctx.getParameterValue (param);
        } else {
            return parameter[param];
        }
    }
    
    public void setFloatParameter(int param, float x)
    {
        if (IsInstantiated ()) {
            ctx.setParameterValue (param, x);
        } else {
            parameter[param] = x;
        }
    }
    
    private void Awake()
    {
        ctx = new Faust_Ctx (getBufferSize());
        ctx.Ctx_init (AudioSettings.outputSampleRate);
        
        for(int i=0; i<parameter.Length; i++){
            setFloatParameter (i, parameter [i]);
        }
    }
    
    private void OnAudioFilterRead (float[] buffer, int numchannels)
    {
        ctx.process(buffer, buffer.Length/numchannels);
    }
    
    public int getBufferSize()
    {
        int bufferlength;
        int numbuffers;
        AudioSettings.GetDSPBufferSize (out bufferlength, out numbuffers);
        return bufferlength;
    }
    
    public Faust_Ctx getContext () { return ctx; }
}

public class Faust_Ctx{
    
    private IntPtr _context;
    
    #if UNITY_STANDALONE_OSX || UNITY_STANDALONE_WIN || UNITY_EDITOR
    const string _dllName = "plugname";
    #elif UNITY_IOS
    const string _dllName = "__Internal";
    #elif UNITY_ANDROID
    const string _dllName = "androidpluginname";
    #else
    Debug.LogError("Architecture not supported by the plugin");
    #endif
    
    [DllImport (_dllName)]
    private static extern IntPtr Faust_contextNew(int buffersize);
    
    [DllImport (_dllName)]
    private static extern void Faust_contextInit(IntPtr ctx, int samplerate);
    
    [DllImport (_dllName)]
    private static extern void Faust_process(IntPtr ctx,[In] float[] inbuffer, [Out] float[] outbuffer, int numframes);
    
    [DllImport (_dllName)]
    private static extern void Faust_delete(IntPtr ctx);
    
    [DllImport (_dllName)]
    private static extern int Faust_getSampleRate(IntPtr ctx);
    
    [DllImport (_dllName)]
    private static extern int Faust_getNumInputChannels(IntPtr ctx);
    
    [DllImport (_dllName)]
    private static extern int Faust_getNumOutputChannels(IntPtr ctx);
    
    [DllImport (_dllName)]
    private static extern void Faust_setParameterValue(IntPtr ctx, int param, float value);
    
    [DllImport (_dllName)]
    private static extern float Faust_getParameterValue (IntPtr ctx, int param);
    
    [DllImport (_dllName)]
    private static extern float Faust_getParamMin (IntPtr ctx, int param);
    
    [DllImport (_dllName)]
    private static extern float Faust_getParamMax (IntPtr ctx, int param);
    
    public Faust_Ctx(int buffersize) { _context = Faust_contextNew (buffersize); }
    
    ~Faust_Ctx() { Faust_delete (_context) ; }
    
    
    public void Ctx_init(int samplerate) { Faust_contextInit (_context, samplerate); }
    
    public int getSampleRate() { return Faust_getSampleRate (_context); }
    
    public int getNumInputChannels() { return Faust_getNumInputChannels(_context); }
    
    public int getNumOutputChannels() { return Faust_getNumOutputChannels(_context); }
    
    public void process(float[] buffer, int numframes) { Faust_process(_context, buffer, buffer, numframes); }
    
    public void setParameterValue(int param, float value) { Faust_setParameterValue (_context, param, value); }
    
    public float getParameterValue(int param) { return Faust_getParameterValue (_context, param); }
    
    public float getParamMin(int param) { return Faust_getParamMin (_context, param); }
    
    public float getParamMax(int param) { return Faust_getParamMax (_context, param); }
    
}

[Serializable]
public class FaustUI_UI
{
    public string name;
    public int inputs;
    public int outputs;
    public UI_UI[] ui;
    
    
    public static FaustUI_UI ReadJSONUi(string fJSON)
    {
        return JsonUtility.FromJson<FaustUI_UI>(fJSON);
    }
    
    public UI_UI getUI(int i)
    {
        return ui[i];
    }
    
    
}

[Serializable]
public class UI_UI
{
    public string type;
    public string label;
    public Group_UI[] items;
    public bool groupstate = true;
    
    public void setNumParams(){
        int param = 0;
        for (int i=0; i<items.Length; i++){
            param = items [i].setNumParamsGr (param);
        }
    }
    
    public Group_UI getItem(int param){
        Group_UI result = null;
        for(int i=0; i<items.Length; i++){
            Group_UI item = items [i].getItem (param);
            if (item != null)
            result = item;
        }
        return result;
    }
}

[Serializable]
public class Group_UI
{
    public string type;
    public string label;
    public Meta_UI[] meta;
    public Group_UI[] items;
    public string address;
    public float init;
    public float min;
    public float max;
    public float step;
    public int numparam;
    public bool groupstate = true;
    
    public int setNumParamsGr(int param){
        if(items != null){
            for(int i=0; i<items.Length; i++){
                param = items[i].setNumParamsGr (param);
                
            }
            return param;
        } else {
            numparam = param;
            param++;
            return param;
        }
    }
    
    public Group_UI getItem(int param){
        Group_UI result = null;
        if(items != null){
            for(int i=0; i<items.Length; i++){
                Group_UI item = items [i].getItem (param);
                if (item != null)
                result = item;
            }
            return result;
        } else {
            if (this.numparam == param)
            return this;
            else
            return null;
        }
    }
}

[Serializable]
public class Meta_UI
{
    public string unit;
    public string scale;
    public string tooltip;
}


