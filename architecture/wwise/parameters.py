import json

def static_param_id():
    try:
        static_param_id.counter += 1
    except AttributeError:
        static_param_id.counter = 1
    return int(static_param_id.counter)

class Parameter:
    def __init__(self, data):
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

        self.initValue = self._derive_init_value(self.init)
        self.paramVarname = self.varname
        self.paramCastedType = self._derive_casted_type()
        self.setterFunctionName = self._derive_setter_name()
        self.isRTPC = self._derive_is_rtpc()
        self.RTPCname = self._derive_rtpc_name()
        self.WwiseTypeCast = self._cast_type_2wwise()
        self.WwiseXMLTypeCast = self._cast_type_2XMLwwise()
        self.PARAM_ID_NAME = self._derive_id_name()
        self.PARAM_ID = static_param_id()

        self.Wwise_Type_Specific_WriteFunction = self._derive_Wwise_WriteFunction()
        self.Wwise_Type_Specific_GetFunction = self._derive_Wwise_GetFunction()
    
    def _derive_init_value(self, init_value):
        if init_value is not None:
            if isinstance(init_value, bool):
                return "true" if init_value else "false"
            return str(init_value)
        type_defaults = {
            "checkbox": "false",
            "hslider": "0.0",
            "nentry": "0.0",
            "vslider": "0.0",
            "button": "false"
        }
        return type_defaults.get(self.type, "0")

    def _derive_casted_type(self):
        return {
            "hslider": "float",
            "nentry": "float",
            "checkbox": "bool"
        }.get(self.type, "auto")

    def _derive_setter_name(self):
        base = self.shortname or self.Shortname
        return f"set{base.capitalize()}"

    def _derive_is_rtpc(self):
        try:
            meta = self.raw.get("meta", [])
            for item in meta:
                if isinstance(item, dict) and "RTPC" in item:
                    return "RTPC"
            return "NonRTPC"
        except:
            return "NonRTPC"
        
    def _derive_rtpc_name(self):
        return self.paramCastedType[0] + self.Shortname

    def _cast_type_2wwise(self):
        if self.paramCastedType == "float":
            return "AkReal32"
        elif self.paramCastedType == "double":
            return "AkReal64"
        elif self.paramCastedType == "bool":
            return "bool"

    def _cast_type_2XMLwwise(self):
        if self.paramCastedType == "float":
            return "Real32"
        elif self.paramCastedType == "double":
            return "Real64"
        elif self.paramCastedType == "bool":
            return "bool"
        elif self.paramCastedType == "int":
            return "int32"
        # @TODO proper type casting
        """
        bool: Boolean
        int16: 16-bit integer
        Uint16: 16-bit unsigned integer
        int32: 32-bit integer
        Uint32: 32-bit unsigned integer
        int64: 64-bit integer
        Uint64: 64-bit unsigned integer
        Real32: Single-precision float (32-bit)
        Real64: Double-precision float (64-bit)
        string:
        https://www.audiokinetic.com/en/public-library/2024.1.5_8803/?source=SDK&id=plugin_xml_properties.html
        """

    def _derive_id_name(self):
        name = self.shortname or self.Shortname
        return f"PARAM_{name.upper()}_ID"
    
    def _derive_Wwise_WriteFunction(self):
        return {
            "float": "WriteReal32",
            "double": "WriteReal64",
            "bool": "WriteBool"
        }.get(self.paramCastedType, "WriteUnknown")

    def _derive_Wwise_GetFunction(self):
        return {
            "float": "GetReal32",
            "double": "GetReal64",
            "bool": "GetBool"
        }.get(self.paramCastedType, "GetUnknown")

    def to_dict(self):
        return {
            **vars(self),
            **self.raw  # include original fields
        }

    ################################################ other helper functions, could be made properties

    def is_slider(self):
        return self.type in ("hslider", "vslider")

    def has_restrictions(self):
        return self.min is not None and self.max is not None

    def is_rtpc(self):
        return self.isRTPC == "RTPC"

    def default_value(self):
        return self.initValue or "0"