from string import Template
from parameters import Parameter

class TemplateProcessor:

    PLACEHOLDER_PREFIX = "<<FOREACHPARAM:"
    PLACEHOLDER_SUFFIX = ">>"

    def __init__(self, parameters):
        self.parameters = parameters

    def parse_placeholder(self, placeholder_str):

        # Remove prefix and suffix
        inner = placeholder_str[len(self.PLACEHOLDER_PREFIX):-len(self.PLACEHOLDER_SUFFIX)]

        # Spliting the optional condition
        # @TODO If an : mark and a == mark is found before the == mark, then the condition is triggered. We could add an IF capitalized 
        if ":" in inner:
            condition_part, template = inner.split(":", 1)
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

    def render_template(self, template_str, context):
        return Template(template_str).safe_substitute(context)

    def process_file(self, filepath):
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
