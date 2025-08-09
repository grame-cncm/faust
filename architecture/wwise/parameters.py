"""
parameters.py

The Parameter class used to represent the Faust UI elements as Wwise plugin parameters.
These are typically extracted from Faust-generated JSON UI data and translated into a Wwise-compatible format.
"""
from typing import Any, Dict, Optional

def static_param_id() -> int:
    """
    Static counter function to generate unique parameter IDs for the Wwise plugin integration needs.
    Returns:
        int: Unique integer ID, incremented with each call.
    """
    try:
        static_param_id.counter += 1
    except AttributeError:
        static_param_id.counter = 1
    return int(static_param_id.counter)

class Parameter:
    """
    Models a parameter extracted from a Faust DSP UI JSON structure, providing utilities to transform 
    Faust UI metadata into Wwise plugin-compatible code and XML structures.
    """
    def __init__(self, data: Dict[str, Any], faustfloat_isDouble : bool):
        self.raw = data
        self.varname = data.get("varname")
        self.Shortname = data.get("shortname").capitalize()
        self.shortname = data.get("shortname")
        self.type = data.get("type")
        self.address = data.get("address")

        self.min = data.get("min")
        self.max = data.get("max")
        self.step = data.get("step", 1)
        self.init = data.get("init")

        faustfloatType = "double" if faustfloat_isDouble else "float"

        self.io_type = self._derive_io_type()
        self.initValue = self._derive_init_value(self.init)
        self.paramVarname = self.varname
        self.paramCastedType = self._derive_casted_type(faustfloatType)
        self.isRTPC = self._derive_is_rtpc()
        self.RTPCname = self._derive_rtpc_name(data.get("unq_shortname"))
        self.WwiseTypeCast = self._cast_type_2wwise()
        self.WwiseXMLTypeCast = self._cast_type_2XMLwwise()
        self.PARAM_ID_NAME = self._derive_id_name(data.get("unq_shortname"))
        self.PARAM_ID = static_param_id()

        self.Wwise_Type_Specific_WriteFunction = self._derive_Wwise_WriteFunction()
        self.Wwise_Type_Specific_GetFunction = self._derive_Wwise_GetFunction()
    
    def _derive_io_type(self):
        if self.is_bargraph():
            return "output"
        return "input"

    def _derive_init_value(self, init_value : Any) -> str:
        """Convert init value to a string"""
        if init_value is not None:
            if isinstance(init_value, bool):
                return "true" if init_value else "false"
            return str(init_value)
        return {
            "vbargraph" : "0.0",
            "hbargraph" : "0.0",
            "checkbox": "false",
            "hslider": "0.0",
            "nentry": "0.0",
            "vslider": "0.0",
            "button": "false"
        }.get(self.type, "0")

    def _derive_casted_type(self, faustfloatType : str) -> str:
        """Map Faust UI type to C++ type."""
        return {
            "vbargraph": faustfloatType,
            "hbargraph": faustfloatType,
            "hslider": faustfloatType,
            "vslider": faustfloatType,
            "nentry": faustfloatType,
            "checkbox": "bool",
            "button" : "bool",
        }.get(self.type, "auto")

    def _derive_is_rtpc(self) -> str:
        """
        Check metadata to see if RTPC is enabled.
        """
        try:
            meta = self.raw.get("meta", [])
            for item in meta:
                if isinstance(item, dict) and "RTPC" in item:
                    if self.is_bargraph():
                        self.rtpcType = None
                        return None
                    self.rtpcType = item["RTPC"]
                    return "RTPC"
            return "NonRTPC"
        except:
            return "NonRTPC"
        
    def _derive_rtpc_name(self, unq_shortname : str) -> str:
        """Build a unique RTPC name based on type and shortname"""
        return self.paramCastedType[0] + unq_shortname

    def _cast_type_2wwise(self) -> str:
        """Map internal type to Wwise casted C++ type."""
        return {
            "float" : "AkReal32",
            "double": "AkReal64",
            "double": "AkReal64",
            "bool"  : "bool"
             
        }.get(self.paramCastedType)

    def _cast_type_2XMLwwise(self) -> str:
        """Map internal type to Wwise XML type."""
        return {
            "float": "Real32",
            "double": "Real64",
            "bool": "bool",
            "int": "int32"
        }.get(self.paramCastedType)
        
    def _derive_id_name(self, unq_shortname) -> str:
        """Generate a preprocessor macro name for parameter ID."""
        return f"PARAM_{unq_shortname.upper()}_ID"
    
    def _derive_Wwise_WriteFunction(self) -> str:
        """Return the correct Wwise function"""
        return {
            "float": "WriteReal32",
            "double": "WriteReal64",
            "bool": "WriteBool"
        }.get(self.paramCastedType, "WriteUnknown")

    def _derive_Wwise_GetFunction(self)-> str:
        """Return the correct Wwise function"""
        return {
            "float": "GetReal32",
            "double": "GetReal64",
            "bool": "GetBool"
        }.get(self.paramCastedType, "GetUnknown")

    def to_dict(self)-> Dict[str, Any]:
        """
        Converts the parameter class into a flat dictionary.
        Returns:
            Dict[str, Any]: Dictionary containing all the member variables and their values.
        """
        return {
            **vars(self),
            **self.raw  # include original fields
        }

    ################################################ other helper functions, could be made properties

    def is_slider(self)-> bool:
        """Return True if this parameter is a slider (horizontal or vertical)."""
        return self.type in ("hslider", "vslider")

    def has_restrictions(self)-> bool:
        """Return True if the parameter has both min and max values set."""
        return self.min is not None and self.max is not None

    def is_rtpc(self) -> bool:
        """Return True if parameter is tagged as RTPC-enabled."""
        return self.isRTPC == "RTPC"

    def default_value(self) -> str:
        """Return the derived initial/default value for the parameter."""
        return self.initValue or "0"
    
    def is_bargraph(self) -> bool:
        return self.type=="vbargraph" or self.type=="hbargraph"
    
    def xml_applicable(self) -> bool:
        return not self.is_bargraph()