"""
In order to use long delay lines and tables on Daisy devices, it's necessary
to put some buffers in SDRAM. Right now, the Faust backend system doesn't do
this automatically for us, so we do it via Python. A better approach would
be to use a custom memory manager:
https://faustdoc.grame.fr/manual/architectures/#custom-memory-manager

Before the script, our C++ code might look like this

```c++
class mydsp : public dsp {
  private:
    // omitting some code
    float fVec2[131072]; // this needs to be put into SDRAM.
    // omitting some code
  public:
	mydsp() {}
```

Our Python script transforms the C++ code into this:
```c++
static float DSY_SDRAM_BSS fVec2_buffer[131072];
class mydsp: public dsp {
  private:
    // omitting some code
    float* fVec2;
    // omitting some code
  public:
	mydsp() : fVec2(fVec2_buffer) {}
```

Note that the script relies on the class being named `mydsp`, so don't use
this script in combination with `faust -cn MyClassName code.dsp`.
"""


import re
import sys
import os

def debug_print_arrays(arrays_info, threshold=1000):
    """Print debug information about detected arrays"""
    print("\nDebug: Detected Arrays:")
    for info in arrays_info:
        print(f"Type: {info['type']}, Name: {info['name']}, Size: {info['size']}")
        print(f"Will be modified: {info['size'] > threshold}")
        print(f"Original declaration: {info['original']}")
        print("-" * 50)

def find_arrays_in_class(class_content):
    """Find all array declarations in the class content"""
    # More comprehensive array pattern that handles various formats
    array_pattern = r'(float|FAUSTFLOAT)\s+(\w+)\s*\[(\d+)\]\s*;'
    
    arrays = []
    for match in re.finditer(array_pattern, class_content):
        type_name, var_name, size_str = match.groups()
        arrays.append({
            'type': type_name,
            'name': var_name,
            'size': int(size_str),
            'original': match.group(0)
        })
    return arrays

def find_static_arrays(content):
    """Find static array declarations outside the class"""
    static_pattern = r'static\s+(float|FAUSTFLOAT)\s+(\w+)\s*\[(\d+)\]\s*;'
    arrays = []
    for match in re.finditer(static_pattern, content):
        type_name, var_name, size_str = match.groups()
        if 'DSY_SDRAM_BSS' not in match.group(0):  # Skip if already modified
            arrays.append({
                'type': type_name,
                'name': var_name,
                'size': int(size_str),
                'original': match.group(0)
            })
    return arrays

def process_faust_cpp(input_text, debug=True, threshold=1000):
    # First handle static arrays outside the class
    static_arrays = find_static_arrays(input_text)

    if debug and static_arrays:
        print("\nDebug: Found static arrays outside class:")
        debug_print_arrays(static_arrays)

    # Modify static array declarations
    for arr in static_arrays:
        if arr['size'] > threshold:
            old_decl = arr['original']
            new_decl = f'static {arr["type"]} DSY_SDRAM_BSS {arr["name"]}[{arr["size"]}];'
            input_text = input_text.replace(old_decl, new_decl)
            if debug:
                print(f"Modified static array: {arr['name']}")

    # Find the complete mydsp class
    class_match = re.search(
        r'class\s+mydsp\s*:\s*public\s+dsp\s*{(.*?)};', 
        input_text, 
        re.DOTALL
    )
    if not class_match:
        print("Error: Couldn't find `mydsp` class")
        return input_text

    class_content = class_match.group(1)
    
    # Find arrays in the class
    arrays = find_arrays_in_class(class_content)
    
    if debug:
        debug_print_arrays(arrays)

    # Filter arrays that need modification (size > threshold)
    large_arrays = [arr for arr in arrays if arr['size'] > threshold]
    
    if not large_arrays:
        if debug:
            print("No large arrays found to modify in class")
        return input_text

    # Prepare modifications
    static_declarations = []
    pointer_declarations = []
    constructor_inits = []
    
    modified_content = class_content
    
    for arr in large_arrays:
        # Create static SDRAM buffer declaration
        static_declarations.append(
            f'static {arr["type"]} DSY_SDRAM_BSS {arr["name"]}_buffer[{arr["size"]}];'
        )
        
        # Create pointer declaration
        pointer_declarations.append(f'{arr["type"]}* {arr["name"]};')
        
        # Create constructor initialization
        constructor_inits.append(f'{arr["name"]}({arr["name"]}_buffer)')
        
        # Replace array declaration with pointer in class content
        modified_content = modified_content.replace(
            arr['original'],
            f'{arr["type"]}* {arr["name"]};'
        )

    # Add static declarations before class
    if static_declarations:
        static_decl_text = '\n'.join(static_declarations) + '\n\n'
        input_text = input_text.replace('class mydsp :', static_decl_text + 'class mydsp :')

    # Update or add constructor if we have initializations to add
    if constructor_inits:
        constructor_match = re.search(r'mydsp\(\)\s*{', modified_content)
        if constructor_match:
            # Update existing constructor
            modified_content = modified_content.replace(
                'mydsp() {',
                f'mydsp() : {", ".join(constructor_inits)} {{'
            )
        else:
            # Add new constructor after class opening
            constructor_text = f'\n    public:\n    mydsp() : {", ".join(constructor_inits)} {{\n    }}\n'
            modified_content = re.sub(
                r'{(\s*private:)?',
                f'{{\n{constructor_text}\n    private:',
                modified_content,
                count=1
            )

        # Replace the entire class content
        input_text = re.sub(
            r'class\s+mydsp\s*:\s*public\s+dsp\s*{.*?};',
            f'class mydsp : public dsp {{{modified_content}}};',
            input_text,
            flags=re.DOTALL
        )

    return input_text

def main():
    if len(sys.argv) != 2:
        print("Usage: python faust_sdram_converter.py <input_file>")
        sys.exit(1)
        
    input_file = sys.argv[1]
    if not os.path.exists(input_file):
        print(f"Error: File {input_file} not found")
        sys.exit(1)
        
    # Read input file
    with open(input_file, 'r', encoding='utf-8') as f:
        input_text = f.read()
  
    debug = False
    threshold = 1000
    
    # Process the file
    output_text = process_faust_cpp(input_text, debug=debug, threshold=threshold)
    
    # Write to output file
    # output_file = input_file.rsplit('.', 1)[0] + '_sdram.cpp'
    output_file = input_file
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(output_text)
    
    if debug:
        print(f"\nProcessed file saved as: {output_file}")

if __name__ == "__main__":
    main()
