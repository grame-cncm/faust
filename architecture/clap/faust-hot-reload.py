#!/usr/bin/env python3
#####################################################################
#                                                                   #
#                   faust2clap hot-reload GUI                       #
#               (c) GRAME & Facundo Franchino, 2025                 #
#                                                                   #
#####################################################################   

"""
faust-hot-reload.py

Faust Hot Reload GUI,
A friendly interface for the Faust Dynamic CLAP plugin hot reload system.
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import json
import os
from pathlib import Path

class FaustHotReloadGUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Faust Hot Reload")
        self.root.geometry("600x500")
        
        # config file path for the plugin
        self.config_file = "/tmp/faust-current-dsp.txt"
        
        # history file to remember loaded DSP files
        self.history_file = os.path.expanduser("~/.faust-hot-reload-history.json")
        self.history = self.load_history()
        
        self.setup_ui()
        self.update_current_file()
        
    def load_history(self):
        """Load previously used DSP files"""
        try:
            if os.path.exists(self.history_file):
                with open(self.history_file, 'r') as f:
                    return json.load(f)
        except:
            pass
        return []
    
    def save_history(self):
        """Save history to file"""
        try:
            with open(self.history_file, 'w') as f:
                json.dump(self.history, f, indent=2)
        except Exception as e:
            print(f"Error saving history: {e}")
    
    def add_to_history(self, filepath):
        """Add a DSP file to history (avoiding duplicates)"""
        if filepath in self.history:
            self.history.remove(filepath)
        self.history.insert(0, filepath)
        # keep only last 20 files
        self.history = self.history[:20]
        self.save_history()
        self.refresh_history_list()
    
    def setup_ui(self):
        # main title
        title_label = tk.Label(self.root, text="🎵 Faust Hot Reload Controller", 
                              font=("Arial", 16, "bold"))
        title_label.pack(pady=10)
        
        # current file section
        current_frame = ttk.LabelFrame(self.root, text="Currently Loaded DSP", padding=10)
        current_frame.pack(fill="x", padx=10, pady=5)
        
        self.current_label = tk.Label(current_frame, text="No DSP file loaded", 
                                     font=("Monaco", 10), wraplength=500)
        self.current_label.pack()
        
        # load new file section
        load_frame = ttk.LabelFrame(self.root, text="Load New DSP File", padding=10)
        load_frame.pack(fill="x", padx=10, pady=5)
        
        load_btn = ttk.Button(load_frame, text="📁 Browse for DSP File", 
                             command=self.browse_dsp_file, style="Accent.TButton")
        load_btn.pack(pady=5)
        
        # history section
        history_frame = ttk.LabelFrame(self.root, text="Recently Used DSP Files", padding=10)
        history_frame.pack(fill="both", expand=True, padx=10, pady=5)
        
        # scrollable listbox for history
        list_frame = tk.Frame(history_frame)
        list_frame.pack(fill="both", expand=True)
        
        scrollbar = ttk.Scrollbar(list_frame)
        scrollbar.pack(side="right", fill="y")
        
        self.history_listbox = tk.Listbox(list_frame, yscrollcommand=scrollbar.set,
                                         font=("Monaco", 9))
        self.history_listbox.pack(side="left", fill="both", expand=True)
        scrollbar.config(command=self.history_listbox.yview)
        
        # double-click to load from history
        self.history_listbox.bind("<Double-Button-1>", self.load_from_history)
        
        # button to load selected from history
        history_btn_frame = tk.Frame(history_frame)
        history_btn_frame.pack(fill="x", pady=(10, 0))
        
        load_selected_btn = ttk.Button(history_btn_frame, text="🔄 Load Selected", 
                                      command=self.load_selected_from_history)
        load_selected_btn.pack(side="left")
        
        clear_history_btn = ttk.Button(history_btn_frame, text="🗑️ Clear History", 
                                      command=self.clear_history)
        clear_history_btn.pack(side="right")
        
        # info label about compilation errors
        info_frame = tk.Frame(self.root, bg="#fffacd")
        info_frame.pack(fill="x", padx=10, pady=5)
        info_label = tk.Label(info_frame, 
                             text="💡 Tip: Run Reaper from terminal to see compilation errors: /Applications/REAPER.app/Contents/MacOS/REAPER",
                             bg="#fffacd", fg="#666", font=("Arial", 9))
        info_label.pack(pady=2)
        
        # status bar
        self.status_label = tk.Label(self.root, text="Ready", relief="sunken", anchor="w")
        self.status_label.pack(side="bottom", fill="x")
        
        self.refresh_history_list()
    
    def update_current_file(self):
        """Update the currently loaded file display"""
        try:
            if os.path.exists(self.config_file):
                with open(self.config_file, 'r') as f:
                    current_path = f.read().strip()
                if current_path:
                    filename = os.path.basename(current_path)
                    self.current_label.config(text=f"📄 {filename}\n{current_path}")
                    return
        except:
            pass
        self.current_label.config(text="No DSP file loaded")
    
    def browse_dsp_file(self):
        """Open file browser to select a DSP file"""
        filetypes = [
            ("Faust DSP files", "*.dsp"),
            ("All files", "*.*")
        ]
        
        # start in Faust examples directory if it exists
        # Try multiple possible locations for Faust examples
        possible_example_dirs = [
            os.path.expanduser("~/Documents/GitHub/faust/examples"),
            "/usr/local/share/faust/examples",
            "/usr/share/faust/examples", 
            "/opt/homebrew/share/faust/examples",
            os.path.join(os.environ.get("FAUST_LIB", ""), "examples") if os.environ.get("FAUST_LIB") else None,
        ]
        
        initial_dir = os.path.expanduser("~")
        for example_dir in possible_example_dirs:
            if example_dir and os.path.exists(example_dir):
                initial_dir = example_dir
                break
        
        filepath = filedialog.askopenfilename(
            title="Select Faust DSP File",
            filetypes=filetypes,
            initialdir=initial_dir
        )
        
        if filepath:
            self.load_dsp_file(filepath)
    
    def load_dsp_file(self, filepath):
        """Load a DSP file into the hot reload system"""
        try:
            # write to config file for the plugin
            with open(self.config_file, 'w') as f:
                f.write(filepath)
            
            # add to history
            self.add_to_history(filepath)
            
            # update UI
            self.update_current_file()
            filename = os.path.basename(filepath)
            self.status_label.config(text=f"✅ Loaded: {filename}")
            
            # check if file compiles (basic check - file exists and has .dsp extension)
            if not os.path.exists(filepath):
                messagebox.showwarning("Warning", f"File not found:\n{filepath}\n\nThe plugin may fail to compile.")
            elif not filepath.endswith('.dsp'):
                messagebox.showwarning("Warning", f"Not a .dsp file:\n{filepath}\n\nThe plugin may fail to compile.")
            else:
                # show success with note about compilation
                messagebox.showinfo("File Loaded", 
                    f"DSP file loaded:\n{filename}\n\n" +
                    "Note: If the DSP has compilation errors, check Reaper's console output.\n" +
                    "The plugin will show '❌ Compilation error' in the terminal.")
            
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load DSP file:\n{str(e)}")
            self.status_label.config(text="❌ Error loading file")
    
    def refresh_history_list(self):
        """Refresh the history listbox"""
        self.history_listbox.delete(0, tk.END)
        for filepath in self.history:
            if os.path.exists(filepath):
                filename = os.path.basename(filepath)
                display_text = f"{filename} - {filepath}"
                self.history_listbox.insert(tk.END, display_text)
            else:
                # remove non-existent files from history
                self.history.remove(filepath)
        self.save_history()
    
    def load_from_history(self, event=None):
        """Load DSP file from history (double-click handler)"""
        self.load_selected_from_history()
    
    def load_selected_from_history(self):
        """Load the selected DSP file from history"""
        selection = self.history_listbox.curselection()
        if selection:
            index = selection[0]
            if index < len(self.history):
                filepath = self.history[index]
                if os.path.exists(filepath):
                    self.load_dsp_file(filepath)
                else:
                    messagebox.showerror("Error", f"File not found:\n{filepath}")
                    self.history.remove(filepath)
                    self.refresh_history_list()
    
    def clear_history(self):
        """Clear the history list"""
        if messagebox.askyesno("Clear History", "Are you sure you want to clear the history?"):
            self.history = []
            self.save_history()
            self.refresh_history_list()
            self.status_label.config(text="History cleared")
    
    def run(self):
        """Start the GUI"""
        self.root.mainloop()

if __name__ == "__main__":
    app = FaustHotReloadGUI()
    app.run()