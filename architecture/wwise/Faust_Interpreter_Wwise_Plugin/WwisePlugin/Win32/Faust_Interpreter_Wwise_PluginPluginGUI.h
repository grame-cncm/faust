/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided 
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the 
"Apache License"); you may not use this file except in compliance with the 
Apache License. You may obtain a copy of the Apache License at 
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2025 Audiokinetic Inc.
*******************************************************************************/
#pragma once

#include "../Faust_Interpreter_Wwise_PluginPlugin.h"
#include "plugin_loader.h"
#include "PluginTemplate/UI/plugin_window.h"
#include "ProjectFiles/Manager.h"

typedef std::pair<int,std::wstring> ProjectFileSelection;

enum WM_STATE{
    INIT_STATE=1,
    RUN_STATE=2,
    EXIT_STATE=3,
    NONINIT_STATE=0
};

class Faust_Interpreter_Wwise_PluginPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	Faust_Interpreter_Wwise_PluginPluginGUI();
    ~Faust_Interpreter_Wwise_PluginPluginGUI();

	HINSTANCE GetResourceHandle() const override;

    bool GetDialog(
        AK::Wwise::Plugin::eDialog in_eDialog,
        UINT& out_uiDialogID,
        AK::Wwise::Plugin::PopulateTableItem*& out_pTable
    ) const override;

    bool WindowProc(
        AK::Wwise::Plugin::eDialog in_eDialog,
        HWND in_hWnd,
        uint32_t in_message,
        WPARAM in_wParam,
        LPARAM in_lParam,
        LRESULT& out_lResult) override;

private:

    HWND faustWnd,
        editorWnd,
        audioInputCombo,
        projectFilesCombo,
        newFileButton, 
        renameFileButton,
        deleteFileButton ,
        renameEdit,
        hToolTip;
    
    // HINT: PluginLoader is a singleton.
    PluginLoader& faustPluginLoader = PluginLoader::getInstance(); 
    PluginWindow* pluginWindow;
    ProjectFilesManager fileManager;

    std::wstring dspCode;
    
    // used to store the state of specific buttons
    WM_STATE state; // used to set the code editor after the plugin initializations is completed.
    int currAudioInputComboSelection;
    std::wstring currentFileWorkingOn;
    
    // used for async building of plugin 
    UINT UnqBuildCompleteWndMsg;
    std::string buildOutputText;        

    // UI setup
    void initializeEditor(HWND);
    void AddTooltip(HWND, const wchar_t*);

    // Re-usable code
    ProjectFileSelection getCurrentProjectFileSelection();
    bool SetCodeEditorText(); 
    bool SaveCodeEditorText();
    void ShowSimpleWindow(LPCWSTR, LPCWSTR);
    
    // Event handlers
    void OnBuildCompleted(WPARAM, LPARAM);
    void OnDeleteProjectFile();
    void OnRenameButtonClicked();
    bool OnRenameAccepted(wchar_t*);
    static LRESULT CALLBACK onRenameWinProc(HWND, UINT, WPARAM, LPARAM);
    void OnNewProjectFile();
    void OnProjectFileSelectionChange();
    void OnExportClicked();
    int AskUserForDirectory(std::wstring&);
    void onDocsClicked();

    // Async Build and Preview
    void OnPreviewButtonClicked();
    void OnBuildButtonClicked();    // @TODO: requires admin priviledges. Check if can be given on runtime for this specific operation.

};