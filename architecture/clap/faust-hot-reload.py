#!/usr/bin/env python3
#created by Facundo Franchino
"""
Faust Hot Reload GUI
A friendly interface for the Faust Dynamic CLAP plugin hot reload system.
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import json
import os
import sys
from pathlib import Path

def control_file_path():
    """Where the plugin looks for the DSP path to load.

    Mirrors controlFilePath() in dynamic-faust.cpp. The file used to live at a
    fixed /tmp path, which meant every plugin instance on the machine followed
    the same DSP and any local user could rewrite it. It is now per user and
    private, and FAUST_CLAP_CONTROL overrides it so that two instances can
    follow two different programs.
    """
    override = os.environ.get("FAUST_CLAP_CONTROL")
    if override:
        return override

    if sys.platform == "win32":
        base = os.environ.get("LOCALAPPDATA", "")
        directory = os.path.join(base, "faust-clap")
    elif sys.platform == "darwin":
        directory = os.path.expanduser("~/Library/Application Support/faust-clap")
    else:
        base = os.environ.get("XDG_RUNTIME_DIR") or os.environ.get("XDG_CONFIG_HOME")
        directory = (os.path.join(base, "faust-clap") if base
                     else os.path.expanduser("~/.config/faust-clap"))

    os.makedirs(directory, mode=0o700, exist_ok=True)
    return os.path.join(directory, "current-dsp.txt")


class FaustHotReloadGUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Faust Hot Reload")
        self.root.geometry("600x500")
        
        # Control file the plugin watches. Must resolve exactly as
        # controlFilePath() does in dynamic-faust.cpp.
        self.config_file = control_file_path()
        
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
        except (OSError, ValueError):
            pass  # unreadable or corrupt history is not worth reporting
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
        except OSError:
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
        # This script lives in architecture/clap, so the checkout's own examples
        # are two levels up. That replaces a hardcoded ~/Documents/GitHub path,
        # which could only ever have worked on one machine.
        here = os.path.dirname(os.path.abspath(__file__))
        possible_example_dirs = [
            os.path.normpath(os.path.join(here, "..", "..", "examples")),
            "/usr/local/share/faust/examples",
            "/usr/share/faust/examples",
            "/opt/homebrew/share/faust/examples",
            os.path.join(os.environ["FAUST_LIB"], "examples") if os.environ.get("FAUST_LIB") else None,
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
        """Point the plugin at a DSP file by writing the control file."""
        # Checked before writing, not after: the previous order pointed the
        # plugin at a bad path and only then told the user it was bad.
        if not os.path.isfile(filepath):
            messagebox.showwarning(
                "Warning", f"Not a readable file:\n{filepath}\n\nNothing was loaded.")
            return
        if not filepath.endswith('.dsp'):
            if not messagebox.askyesno(
                    "Not a .dsp file",
                    f"{filepath}\n\nThis does not look like a Faust program. Load it anyway?"):
                return

        try:
            self.write_control_file(filepath)
            self.add_to_history(filepath)
            self.update_current_file()
            filename = os.path.basename(filepath)
            self.status_label.config(text=f"✅ Loaded: {filename}")
            messagebox.showinfo(
                "File Loaded",
                f"DSP file loaded:\n{filename}\n\n"
                "Note: If the DSP has compilation errors, the plugin keeps\n"
                "playing the previous one and prints the Faust error to the\n"
                "terminal. Run your DAW from a terminal to see it.")
        except OSError as e:
            messagebox.showerror("Error", f"Failed to load DSP file:\n{e}")
            self.status_label.config(text="❌ Error loading file")

    def write_control_file(self, filepath):
        """Write the control file in one step.

        Through a temporary file and os.replace, because the plugin polls this
        path several times a second: a plain truncate-then-write leaves a window
        where it reads an empty or half-written path and logs a spurious error.
        """
        directory = os.path.dirname(self.config_file) or "."
        temporary = os.path.join(directory, f".{os.path.basename(self.config_file)}.tmp")
        with open(temporary, 'w') as handle:
            handle.write(filepath + "\n")
        os.replace(temporary, self.config_file)
    
    def refresh_history_list(self):
        """Refresh the listbox, dropping entries whose file is gone.

        The pruning builds a new list rather than removing from the one being
        iterated: removing in place skips the element after each removal, so two
        consecutive missing files left the second one in the list -- and in the
        listbox, whose indices the selection handlers then trusted.
        """
        self.history = [path for path in self.history if os.path.exists(path)]

        self.history_listbox.delete(0, tk.END)
        for filepath in self.history:
            self.history_listbox.insert(
                tk.END, f"{os.path.basename(filepath)} - {filepath}")
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