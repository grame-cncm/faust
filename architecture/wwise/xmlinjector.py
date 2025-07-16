"""
xmlinjector.py

This module contains of a single function that provides the functionality to inject audio plugin parameter 
metadata into a Wwise-compatible XML format. It modifies an existing XML plugin definition by appending 
<Property> entries derived from parameter objects.
"""
import xml.etree.ElementTree as ET
from xml.dom import minidom
import os

def inject_properties_to_xml(parameters : list, xml_file : str) -> None:
    """
    Injects <Property> entries into the provided XML file, appending them under the <Properties> element.

    Args:
        parameters (list[Parameter]): List of Parameter objects.
        xml_file (str): Path to the Wwise plugin XML file.
    Raises:
        FileNotFoundError: If the specified XML file does not exist.
    """
    
    if not os.path.isfile(xml_file):
        raise FileNotFoundError(f"XML file not found: {xml_file}")

    # Parse existing XML tree
    tree = ET.parse(xml_file)
    root = tree.getroot()

    # Try to find or create a <Properties> element
    properties_elem = root.find(".//Properties")
    if properties_elem is None:
        properties_elem = ET.SubElement(root, "Properties")
    
    # Append each parameter;s property XML
    for param in parameters:
        properties_elem.append(_parameter_to_property_xml(param))

    # format before saving - pretty-prints and removes blank lines for cleaner formatting.
    xml_str = ET.tostring(root, encoding="utf-8")
    pretty = minidom.parseString(xml_str).toprettyxml(indent="    ")
    cleanedXml = "\n".join([line for line in pretty.splitlines() if line.strip() != ""])     # erase empty lines
    
    with open(xml_file, "w", encoding="utf-8") as f:
        f.write(cleanedXml)
    
    print("OK : Properties are injected successfully into xml file")

def _parameter_to_property_xml(param) -> ET.Element:
    """
    Converts a Parameter object into a Wwise-compatible <Property> XML element.
    Args:
        param (Parameter): The parameter object to convert.
    Returns:
        ET.Element: An XML element representing the parameter as a Wwise <Property> node.
    """
    property_attrs = {
        "Name": param.Shortname,
        "Type": param.WwiseXMLTypeCast,
        "DisplayName": param.Shortname
    }

    if param.is_rtpc():
        property_attrs["SupportRTPCType"] = "Additive"

    property_elem = ET.Element("Property", property_attrs)

    if param.is_slider():
        ET.SubElement(property_elem, "UserInterface", {
            "Step": str(param.step),
            "Fine": "0.1",
            "Decimals": "1",
            "UIMax": str(param.max or 1000)
        })

    ET.SubElement(property_elem, "DefaultValue").text = param.default_value()
    ET.SubElement(property_elem, "AudioEnginePropertyID").text = str(param.PARAM_ID)

    if param.has_restrictions():
        restrictions = ET.SubElement(property_elem, "Restrictions")
        valres = ET.SubElement(restrictions, "ValueRestriction")
        range_elem = ET.SubElement(valres, "Range", {
            "Type": param.WwiseXMLTypeCast
        })
        ET.SubElement(range_elem, "Min").text = str(param.min)
        ET.SubElement(range_elem, "Max").text = str(param.max)

    return property_elem
