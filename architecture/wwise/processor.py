"""
processor.py 

The Template processor for Faust2Wwise. 
This module defines the TemplateProcessor class, 
which processes template files containing placeholder tags. 
These placeholders generate parameter-specific code by injecting parameter data into the template content. 
The processor iterates through all parameters and renders the template content for each parameter that matches 
the optional condition. Conditional rendering is applied via the `IF` clause. If there's no condition, the 
generation is applied for all parameters. In genearal, this is a substep of the plugin generation process.

The placeholders follow this syntax:
    <<FOREACHPARAM:template_content>>
    <<FOREACHPARAM:IF condition==value:template_content>>
Example:
    <<FOREACHPARAM:IF paramtype==float:float ${name};>>
"""
from string import Template
from parameters import Parameter
from typing import List, Optional, Tuple, Dict, Any

class TemplateProcessor:
    """
    Processes template files containing parameter placeholders for integrating Faust parameters into Wwise.
    This class renders such placeholders for each Parameter and replaces them
    in the target file during the plugin generation process.
    Each placeholder can optionally include conditions to filter which parameters should be processed.

    Custom placeholders are written using the format:
        <<FOREACHPARAM:IF key==value: template >>
    """
    PLACEHOLDER_PREFIX = "<<FOREACHPARAM:"
    PLACEHOLDER_SUFFIX = ">>"

    def __init__(self, parameters : List[Parameter]) -> None:
        """
        Initialize the TemplateProcessor with a list of parameters.
        Args:
            parameters: List of Parameter objects that will be used for template rendering
        """
        self.parameters = parameters

    def parse_placeholder(self, placeholder_str: str) -> Tuple[Optional[str], Optional[str], str]:
        """
        Function that parses a placeholder, extracting the optional condition and the template code.
        Args:
            placeholder_str (str): The raw placeholder string from the template.
        Returns:
            Tuple[Optional[str], Optional[str], str]: A tuple containing:
                - cond_key (str or None if no condition): The condition key,
                - cond_val (str or None if no condition): The condition value,
                - template (str): The raw template to render per parameter
        """
        # Remove prefix and suffix
        inner = placeholder_str[len(self.PLACEHOLDER_PREFIX):-len(self.PLACEHOLDER_SUFFIX)]

        # Spliting the optional condition
        if "IF" in inner and ":" in inner:
            condition_with_if, template = inner.split(":", 1)
            condition_part = condition_with_if.strip().removeprefix("IF").strip()
            if "==" in condition_part:
                cond_key, cond_val = map(str.strip, condition_part.split("==", 1))
            else:
                cond_key = None
                cond_val = None
                template = inner
        else:
            cond_key = None
            cond_val = None
            template = inner

        return cond_key, cond_val, template.strip()

    def render_template(self, template_str : str, context : Dict[str, Any]) -> str:
        """
        Renders a template string using the provided context.
        For that, Python's string library is used. 'Template' is used to replace 
        placeholders in the template_str with values from the context dictionary.
        The 'substitute' is used to replace the placeholders from the template code 
        using context data.
        Args:
            template_str: Template string containing ${variable} placeholders
            context: Dictionary of variable names to values for substitution
        Returns:
            Rendered template string with variables substituted
        """
        return Template(template_str).substitute(context)

    def process_file(self, filepath:str) -> None:
        """
        Process in-place a template file by replacing all placeholders with rendered content.
        The pipeline is as follows:
            - the file is read, 
            - all placeholders matching the FOREACHPARAM format are found,
            - parameter data are used to render the placeholders, and
            - the result is written back to the file.
        The processing does not support nested placeholders.
        Args:
            filepath: Path to the template file 
        Raises:
            FileNotFoundError: If the specified file dan't be found
        """
        with open(filepath, 'r') as f:
            content = f.read()

        def replace_match(placeholder_str):
            cond_key, cond_val, template = self.parse_placeholder(placeholder_str)

            rendered_blocks = []
            for param in self.parameters:
                context = param.to_dict()
                if cond_key and context.get(cond_key) != cond_val:
                    continue  # skip if condition not matched

                rendered_blocks.append(self.render_template(template, context))

            return "\n".join(rendered_blocks) if rendered_blocks else ""

        # Care - no nested placeholders

        result = ""
        pos = 0
        while True:
            start_idx = content.find(self.PLACEHOLDER_PREFIX, pos)
            if start_idx == -1:
                # No more placeholders
                result += content[pos:]
                break
            end_idx = content.find(self.PLACEHOLDER_SUFFIX, start_idx)
            if end_idx == -1:
                # malformed placeholder; no closing >>
                result += content[pos:]
                break

            end_idx += len(self.PLACEHOLDER_SUFFIX)

            # Append text before placeholder
            result += content[pos:start_idx]

            # Extract placeholder string
            placeholder_str = content[start_idx:end_idx]

            # Replace placeholder with rendered content
            replacement = replace_match(placeholder_str)
            result += replacement

            pos = end_idx

        with open(filepath, 'w') as f:
            f.write(result)
