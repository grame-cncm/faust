using UnityEngine;
using FaustUtilities_model;


[RequireComponent (typeof (AudioSource))] // Automatically attached the script to an Audiosource
public class FaustPlugin_model : MonoBehaviour
{
	 // Array containing the value of each parameter
    public float[] parameters = new float[variables];

    // Initializes the interface between the plugin and Unity
    private Faust_Context ctx;

    /* @brief Returns true if the plugin is instantiated (the plugin is instantiated when play mode button is pressed)
    */
    public bool IsInstantiated() { return (ctx != null); }

    /* @brief Gets a parameter value from the plugin
    * @param param Use the parameter number available in the parameter inspector (tooltip)
    * @return The parameter value */
    public float getParameter (int param)
    {
    		if (IsInstantiated ())  // if the the plugin is instantiated, the parameter value is changed directly in the plugin
    			return ctx.getParameterValue (param);
    		else  					// if not, the value is stored in parameters[]
          return parameters [param];

    }

    /* @brief Sets a parameter value in the plugin
    * @param param Use the parameter number available in the parameter inspector (tooltip)
    * @param x New parameter value */
    public void setParameter(int param, float x)
    {
        if (IsInstantiated ())
          ctx.setParameterValue (param, x);
        else
          parameters[param] = x;

    }

    /* @brief Instantiates the plugin and the interface between the plugin and Unity
    * @brief And sets the new parameter values changed while in pause mode */
    private void Awake()
    {
        ctx = new Faust_Context (getBufferSize());
        ctx.Context_init (AudioSettings.outputSampleRate);

    	for(int i=0; i<parameters.Length; i++)
          setParameter (i, parameters [i]);

    }

    /* @brief Fills the Unity audio buffer with the audio datas computed by the plugin
    */
    private void OnAudioFilterRead (float[] buffer, int numchannels)
    {
        ctx.process(buffer, buffer.Length/numchannels);
    }

    public int getBufferSize()
    {
        int bufferlength, numbuffers;
        AudioSettings.GetDSPBufferSize (out bufferlength, out numbuffers);
        return bufferlength;
    }

    /* @brief Gets the min value of a parameter
    * @param Use the parameter number available in the parameter inspector (tooltip) */
    public float getParameterMin(int param)
    {
        return ctx.getParamMin (param);
    }

    /* @brief Gets the max value of a parameter
    * @param Use the parameter number available in the parameter inspector (tooltip) */
    public float getParameterMax (int param)
    {
        return ctx.getParamMax (param);
    }

}
