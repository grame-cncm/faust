"""
Faust-Wwise Integration Python script responsible for code injection 
and replacement for integrating Faust compiled code into Wwise plugin 
projects using a patch-based method.

The patch method is described as follows:
    - Inside architecture/wwise dir, there are created patch-files in respect to the actual code files (dir placement,naming)
    - The patch files store the code that is to be injected
    - The patch files are consisted of instructions that contain the followin commands:
        - TITLE <a descriptive name to the change>
        - BELOW <a line of code in the template file under which the injected code will be deposited>
        - REPLACE <Number of lines to be erased from the template file. Zero value does not replace any lines>
        - CODE <Coding patch>
    - 2 generic types of operations for C++ source modification:
        - inject    : inject code at specific place of the file (when REPLACE: 0 )
        - replace   : replace code at specific place of the file (when REPLACE > 0 )
    - cross-platform support due to python script utilization
    - @TODO:
        - configuration via the faust-exported JSON for extending plugin integration in the near future
        - AST-based C++ parsing for enhansing the notion of context in parsing C++ files
            https://stackoverflow.com/questions/526797/good-tools-for-creating-a-c-c-parser-analyzer
"""

import sys
import argparse
from pathlib import Path
import pdb

class GenericWwiseIntegrator:
    def __init__(self, plugin_name, plugin_dir, patch_dir, json_file):
        self.plugin_name = plugin_name
        self.plugin_dir = Path(plugin_dir)
        self.json_file = json_file
        self.patch_dir = Path(patch_dir)
    
    def _read_file(self,file_path):
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                return lines
        except Exception as e:
            print(f"Error reading file {file_path}: {e}")
            exit()
            
    def modify(self, file_path, anchor_text, code, num_lines=0):
        """Generic modify function - inject (0) or replace (>0)"""

        lines = self._read_file(file_path)

        # Find anchor
        anchor_idx = None
        for i, line in enumerate(lines):
            if anchor_text in line:
                anchor_idx = i
                break
        
        if anchor_idx is None:
            print(f"Error: Anchor '{anchor_text}' not found")
            return False
        
        if num_lines > 0:
            # Replace mode - remove num_lines starting from anchor
            for _ in range(num_lines):
                if anchor_idx < len(lines):
                    lines.pop(anchor_idx)
            lines.insert(anchor_idx, code + '\n')
        else:
            # Inject mode - insert below anchor
            lines.insert(anchor_idx + 1, code + '\n')
        
        # Write back
        try:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.writelines(lines)
            return True
        except Exception as e:
            print(f"Error writing file: {e}")
            return False
                        
    def load_patch_operations(self, patch_file):
        
        try:
            with open(patch_file, 'r') as f:
                content = f.read()
            
            operations = []
            current_op = {}
            collecting_code = False
            
            for line in content.split('\n'):
                line_stripped = line.strip()
                
                if not collecting_code and (not line_stripped or line_stripped.startswith('#')):
                    continue
                    
                if line_stripped.startswith('TITLE:'):
                    if current_op:  # Save previous operation
                        operations.append(current_op)
                    current_op = {
                        'title':line_stripped[5:],
                        'anchor': "",
                        'num_lines': 0
                        }
                elif line_stripped.startswith('BELOW:'):
                    current_op['anchor'] = line_stripped[6:].strip()
                    collecting_code = False
                    
                elif line_stripped.startswith('REPLACE:'):
                    if 'anchor' in current_op:  # Only if we have an anchor
                        current_op['num_lines'] = int(line_stripped[8:].strip())
                    else:
                        print(f"Warning: REPLACE: found without BELOW:")
                    
                elif line_stripped.startswith('CODE:'):
                    if 'anchor' in current_op:  # Only if we have an anchor
                        code_start = line_stripped[5:].strip() if len(line_stripped) > 5 else ""
                        current_op['code'] = code_start
                        collecting_code = True
                    else:
                        print(f"Warning: CODE: found without BELOW:")
                        
                elif collecting_code and 'anchor' in current_op:
                    current_op['code'] += '\n' + line
            
            if current_op and 'anchor' in current_op:  # Save final operation
                operations.append(current_op)
                
            return operations
            
        except Exception as e:
            print(f"Error loading patch: {e}")
            return []

    def integrate(self, files):

        print("> Pythong based integration")
        for file in files:
            
            # integrate a patch file into a source file
            
            if (file["path"]):
                patch_file = self.patch_dir/ Path(file["path"]) / Path("_"+file["nameid"])
                source_file = self.plugin_dir / Path(file["path"]) / f"{self.plugin_name+file["nameid"]}"
            else:        
                patch_file = self.patch_dir/ Path("_"+file["nameid"]) #  C:/msys64/usr/local/share/faust/wwise/default/source/SoundEnginePlugin/_{PLUGIN_SUFFIX}.cpp
                source_file = self.plugin_dir / f"{self.plugin_name+file["nameid"]}" # {projectname}/SoundEnginePlugin/{projectname}{PLUGIN_SUFFIX}.cpp

            print(f"integrating {patch_file} into {source_file}")

            if not source_file.exists():
                print(f"Error: Source file not found: {source_file}")
                return False
            
            if not patch_file.exists():
                print(f"Error: Patch file not found: {patch_file}")
                return False
                    
            # Load operations from patch
            operations = self.load_patch_operations(patch_file)
            if not operations:
                print("No operations found in patch file")
                return False
            
            # Execute operations
            for op in operations:
                if not self.modify(source_file, op['anchor'], op['code'], op['num_lines']):
                    return False
                else:
                    print(f"OK : {op['title']} integrated into {source_file} file.")         
        return True

def main():
    parser = argparse.ArgumentParser(description='Generic Faust DSP integration into Wwise plugin')
    parser.add_argument('--plugin-name', required=True, help='Name of the plugin')
    parser.add_argument('--plugin-suffix', required=True, help='Suffix of the plugin', choices=["Source","FX"]) # TODO: FX can be in-place and out-of-place
    parser.add_argument('--plugin-dir', required=True, help='Plugin project directory')
    parser.add_argument('--patch-dir', required=True, help='Full path to the patch directory')
    parser.add_argument('--json-file', required=True, help='JSON configuration file from Faust. Will be used latter when adding stuff such as the UI or Parameters.')
    
    args = parser.parse_args()
    
    integrator = GenericWwiseIntegrator(args.plugin_name, args.plugin_dir, args.patch_dir, args.json_file)

    fileList=\
        [
            {
                "path":"SoundEnginePlugin",
                "nameid":f"{args.plugin_suffix}.cpp"
            },
            {
                "path":"SoundEnginePlugin",
                "nameid":f"{args.plugin_suffix}.h"
            }
        ]
    success = integrator.integrate(fileList)
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()