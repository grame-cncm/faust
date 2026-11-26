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

#include "Faust_Interpreter_Wwise_PluginPluginGUI.h"
#include "../resource.h"
#include "PluginUtils/syscall.h"
#include "PluginUtils/plugin_utils.h"
#include "AudioInput/audio_inputs.h"
#include <AK/AkWwiseSDKVersion.h>
#include <windows.h>
#include <sstream>
#include <thread>

#define FAUST_DOCS_PAGE L"https://faustdoc.grame.fr/manual/syntax/"

AK_WWISE_PLUGIN_GUI_WINDOWS_BEGIN_POPULATE_TABLE(PropertyTable)
AK_WWISE_PLUGIN_GUI_WINDOWS_END_POPULATE_TABLE()

Faust_Interpreter_Wwise_PluginPluginGUI::Faust_Interpreter_Wwise_PluginPluginGUI()
    : dspCode(L"")
    , faustWnd(nullptr)
    , editorWnd(nullptr)
    , audioInputCombo(nullptr)
    , currAudioInputComboSelection(DEFAUT_AUDIO_INPUT_FOR_EFFECTS)
    , pluginWindow(nullptr)
    , state(WM_STATE::NONINIT_STATE)
    , UnqBuildCompleteWndMsg(RegisterWindowMessage(L"FaustBuildCompleteMessage"))
    , fileManager(faustPluginLoader.getExportPath())
{
    AKPLATFORM::OutputDebugMsg("Faust :: Constructor got called!\n");
}

// @TODO create a window warning/info for everything

Faust_Interpreter_Wwise_PluginPluginGUI::~Faust_Interpreter_Wwise_PluginPluginGUI()
{   
    if (pluginWindow)
    {   
        delete pluginWindow;
        pluginWindow = nullptr;
    }
}

HINSTANCE Faust_Interpreter_Wwise_PluginPluginGUI::GetResourceHandle() const
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return AfxGetStaticModuleState()->m_hCurrentResourceHandle;
}

bool Faust_Interpreter_Wwise_PluginPluginGUI::GetDialog(
    AK::Wwise::Plugin::eDialog in_eDialog,
    UINT& out_uiDialogID,
    AK::Wwise::Plugin::PopulateTableItem*& out_pTable) const
{
    if (in_eDialog == AK::Wwise::Plugin::SettingsDialog)
    {
        out_uiDialogID = IDD_FAUST_PLUGIN;
        out_pTable = PropertyTable;
        return true;
    }
    AKPLATFORM::OutputDebugMsg("Faust :: GetDialog got called!\n");
    return false;
}

bool Faust_Interpreter_Wwise_PluginPluginGUI::WindowProc(
    AK::Wwise::Plugin::eDialog in_eDialog,
    HWND in_hWnd,
    uint32_t in_message,
    WPARAM in_wParam,
    LPARAM in_lParam,
    LRESULT& out_lResult)
{

    switch (state)
    {
        case INIT_STATE:
        {
            // Sets the code editor when plugin is loaded properly
            AKPLATFORM::OutputDebugMsg("Faust :: INIT_STATE got called!\n");
            SetCodeEditorText();
            state = WM_STATE::RUN_STATE;
        }
    }

    if (in_message == UnqBuildCompleteWndMsg)   // UnqBuildCompleteWndMsg is runtime evaluated. Have to be within an if condition instead of being within a case statement.
    {
        OnBuildCompleted(in_wParam, in_lParam);
        return TRUE;
    }

    BOOL bRet = FALSE;
    switch (in_message)
    {
        case WM_INITDIALOG:
        {
            initializeEditor(in_hWnd);
            bRet=TRUE;
            break;  
        }
        case WM_COMMAND:
        {

            int id = LOWORD(in_wParam);
            int notify = HIWORD(in_wParam);
            
            if (notify == BN_CLICKED)
            {
                if (id == IDC_BUTTON_PREVIEW)
                {
                    OnPreviewButtonClicked();
                }
                else if (id == IDC_BUTTON_BUILD)
                {
                    OnBuildButtonClicked();
                }
                
                else if (id == IDC_NEW_PROJECT_FILE)
                {
                    OnNewProjectFile();
                }

                else if (id == IDC_RENAME_PROJECT_FILE)
                {
                    OnRenameButtonClicked();
                }

                else if (id == IDC_DELETE_PROJECT_FILE)
                {
                    OnDeleteProjectFile();
                }
                else if (id == IDC_BUTTON_EXPORT)
                {
                    OnExportClicked();
                }
                else if (id == IDC_BUTTON_DOCS)
                {
                    onDocsClicked();
                }
            }
            else if (notify == CBN_SELCHANGE)
            {
                if (id == IDC_AUDIO_INPUT_COMBO)
                {
                    int selection = (int)SendMessageW(audioInputCombo, CB_GETCURSEL, 0, 0);
                    currAudioInputComboSelection = selection;
                }
                else if (id == IDC_PROJECT_FILES_COMBO)
                {
                    OnProjectFileSelectionChange();
                }
            }
            bRet = TRUE;
            break;
        }
        case WM_DESTROY:
        {
            AKPLATFORM::OutputDebugMsg("Faust :: WM_DESTROY got called!\n");
            faustPluginLoader.unloadPlugin();    
            SaveCodeEditorText();
            state = WM_STATE::EXIT_STATE;
            bRet = TRUE;
            break;
        }
        
    }
    return bRet;
}

/* 
---------------------------------------------------------------------------------------|
------------------------------------- UI Setup --------------------------------------- |
---------------------------------------------------------------------------------------|
*/

void Faust_Interpreter_Wwise_PluginPluginGUI::initializeEditor(HWND in_hWnd)
{
    AKPLATFORM::OutputDebugMsg("Faust :: INITDIALOG got called!\n");
    faustWnd = in_hWnd;
    editorWnd = GetDlgItem(faustWnd, IDC_CODE_EDITOR);
    audioInputCombo = GetDlgItem(faustWnd, IDC_AUDIO_INPUT_COMBO);
    audioInputList audlist = AudioInputs::getAudioInputList();
    for (auto& [id, name] : audlist)
    {
        SendMessageW(audioInputCombo, CB_ADDSTRING, id, (LPARAM)name);
    }
    SendMessageW(audioInputCombo, CB_SETCURSEL, currAudioInputComboSelection, 0);

    projectFilesCombo = GetDlgItem(faustWnd, IDC_PROJECT_FILES_COMBO);
    newFileButton = GetDlgItem(faustWnd, IDC_NEW_PROJECT_FILE);
    renameFileButton = GetDlgItem(faustWnd, IDC_RENAME_PROJECT_FILE);
    deleteFileButton = GetDlgItem(faustWnd, IDC_DELETE_PROJECT_FILE);

    int pfid = 0;
    std::vector<std::string> projectFiles = fileManager.getProjectFiles();
    if (projectFiles.size() != 0)
    {
        for (std::string& name : projectFiles)
        {
            std::wstring wname = PluginUtils::string2wstring(name);
            SendMessageW(projectFilesCombo, CB_ADDSTRING, pfid++, (LPARAM)wname.c_str());
        }
        //set default project file selection. 
        int defaultProjectFile = 0; 
        SendMessage(projectFilesCombo, CB_SETCURSEL, defaultProjectFile, 0);
        currentFileWorkingOn = PluginUtils::string2wstring(projectFiles[defaultProjectFile]); 
    }

    // for hovering
    hToolTip = CreateWindowEx(
        0, TOOLTIPS_CLASS, NULL, WS_POPUP, 0, 0, 0, 0,
        faustWnd, 
        NULL, 
        GetResourceHandle(), 
        NULL
    );
    AddTooltip(newFileButton,    L"Create new Faust dsp file");
    AddTooltip(renameFileButton, L"Rename selected Faust dsp file");
    AddTooltip(deleteFileButton, L"Delete selected Faust dsp file");

    state = WM_STATE::INIT_STATE;
}

void Faust_Interpreter_Wwise_PluginPluginGUI::AddTooltip(HWND hTarget, const wchar_t* text)
{
    TOOLINFO ti = { 0 };
    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
    ti.hwnd = faustWnd;
    ti.uId = (UINT_PTR)hTarget;
    ti.lpszText = (LPWSTR)text;

    SendMessage(hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
}

/* 
---------------------------------------------------------------------------------------|
---------------------------------- Re-usable code ------------------------------------ |
---------------------------------------------------------------------------------------|
*/

ProjectFileSelection Faust_Interpreter_Wwise_PluginPluginGUI::getCurrentProjectFileSelection()
{
    int selection = (int)SendMessage(projectFilesCombo, CB_GETCURSEL, 0, 0);
    if (selection == CB_ERR){
        return std::make_pair(-1,L"");
    }

    wchar_t selectionName[256];
    SendMessage(projectFilesCombo, CB_GETLBTEXT, selection, (LPARAM)selectionName);
    return std::make_pair(selection,std::wstring(selectionName));
}

bool Faust_Interpreter_Wwise_PluginPluginGUI::SetCodeEditorText()
{
    if (!editorWnd) return false;

    int filesCount = (int)SendMessage(projectFilesCombo, CB_GETCOUNT, 0, 0);
    if (!filesCount){
        dspCode.clear();
    } else {

        // get the current project file
        auto [option, filename] = getCurrentProjectFileSelection();

        if (!fileManager.load(PluginUtils::wstring2string(filename), dspCode))
        {
            std::wstring message = L"Can't load file " + filename; 
            ShowSimpleWindow(message.c_str(),L"Error");
        }
    }
    SetWindowTextW(editorWnd, dspCode.c_str());
    return true;

}

bool Faust_Interpreter_Wwise_PluginPluginGUI::SaveCodeEditorText()
{
    int len = GetWindowTextLengthW(editorWnd);
    if (len <= 0)
        return false;

    // set the dspCode with the existing code written on the editor.
    std::wstring buffer(len, L'\0');
    GetWindowTextW(editorWnd, &buffer[0], len + 1);
    // ensure null-termination and trim
    buffer.resize(wcslen(buffer.c_str()));
    dspCode = buffer;

    std::string dspName = PluginUtils::wstring2string(currentFileWorkingOn);

    fileManager.writeFile(dspName, dspCode);

    return true;
}

void Faust_Interpreter_Wwise_PluginPluginGUI::ShowSimpleWindow(LPCWSTR text, LPCWSTR title)
{
    MessageBoxW(faustWnd, text, title , MB_OK);
}

/* 
---------------------------------------------------------------------------------------|
---------------------------------- Event Handlers ------------------------------------ |
---------------------------------------------------------------------------------------|
*/

void Faust_Interpreter_Wwise_PluginPluginGUI::OnBuildCompleted(WPARAM in_wParam, LPARAM in_lParam)
{
    EnableWindow((HWND)in_wParam, TRUE); // re-enable build button after completion

    bool succeeded = (bool)in_lParam;
    std::wstring outputMessage;
    if (succeeded) 
    {
        outputMessage = L"Plugin Build Successfully!\n" + PluginUtils::string2wstring(buildOutputText);
    } else 
    {
        outputMessage = std::wstring(L"Failed to build.\nFor more details check the output log file:\n") 
                        + PluginUtils::string2wstring(buildOutputText);
    }

    MessageBoxW(faustWnd, outputMessage.c_str(), L"Faust2Wwise Build Result", MB_OK);

}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnDeleteProjectFile()
{
    int filesCount = (int)SendMessage(projectFilesCombo, CB_GETCOUNT, 0, 0);
    if (!filesCount)
    {
       ShowSimpleWindow(L"Can 't delete no existent file.",L"Warning");
    }
    else
    {

        auto [sel,deletedName] = getCurrentProjectFileSelection();

        // delete the projectFile from the combo
        SendMessage(projectFilesCombo, CB_DELETESTRING, sel, 0);

        // update projectFile combo
        int count = (int)SendMessage(projectFilesCombo, CB_GETCOUNT, 0, 0);
        if (count > 0)
        {
            int newSel = count-1;
            SendMessage(projectFilesCombo, CB_SETCURSEL, newSel, 0);
            // update currentFileWorkingOn
            wchar_t buffer[256];
            SendMessage(projectFilesCombo, CB_GETLBTEXT, newSel, (LPARAM)buffer);
            currentFileWorkingOn = buffer;
        }

        fileManager.remove(PluginUtils::wstring2string(deletedName));
    }

    // update code editor
    SetCodeEditorText();
}

bool Faust_Interpreter_Wwise_PluginPluginGUI::OnRenameAccepted(wchar_t *newName)
{
    // get the oldName
    auto [sel, oldName] = getCurrentProjectFileSelection();

    std::string oldNameStr = PluginUtils::wstring2string(oldName);
    std::string newNameStr = PluginUtils::wstring2string(std::wstring(newName));                    

    // abort if contains spaces...
    if (newNameStr.find(' ') != std::string::npos) 
    {
        ShowSimpleWindow(L"Spaces not allowed.", L"Aborting renaming");
        return false;
    }

    if (fileManager.rename(oldNameStr, newNameStr))
    {
        // 1) rename the comboBox item by:
        // ..deleting the old item..
        SendMessage(projectFilesCombo, CB_DELETESTRING, sel, 0);
        // ..inserting the new item at the same index ..
        SendMessage(projectFilesCombo, CB_INSERTSTRING, sel, (LPARAM)newName);
        // .. and selecting the newly inserted item.
        SendMessage(projectFilesCombo, CB_SETCURSEL, sel, 0);
        // .. + update the currentFileWorkingOn that keeps track of the current selection
        currentFileWorkingOn = std::wstring(newName);

        return true;
    }
        
    return false;
}

LRESULT CALLBACK Faust_Interpreter_Wwise_PluginPluginGUI::onRenameWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == RENAME_CANCEL) // OK or Cancel
        {
            DestroyWindow(hwnd);
            return 0;
        }
        else if (LOWORD(wParam) == RENAME_OK)
        {
            auto* self = (Faust_Interpreter_Wwise_PluginPluginGUI*)
            GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (self)
            {
                // read the newName
                HWND hEdit = GetDlgItem(hwnd, RENAME_EDIT);
                wchar_t newName[256];
                GetWindowTextW(hEdit, newName, 256);

                if (wcslen(newName) != 0) // if the text is not empty, and renamed successfully
                {
                    std::string newNameStr = PluginUtils::wstring2string(std::wstring(newName));
                    if (!self->fileManager.pfNameUnique(newNameStr))
                    {
                        std::wstring message = newName;
                        message += L" already exists";
                        self->ShowSimpleWindow(message.c_str(), L"Aborting renaming");
                    }
                    else if (!self->OnRenameAccepted(newName))
                    {
                        // unable to rename..
                    }
                    DestroyWindow(hwnd);
                    break;
                }
                // else do nothing. Wait for the user to fill up the text.
            }
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnRenameButtonClicked()
{
    int filesCount = (int)SendMessage(projectFilesCombo, CB_GETCOUNT, 0, 0);
    if (!filesCount)
    {
       ShowSimpleWindow(L"Can 't rename no existent file.",L"Warning");
       return;
    }

    HINSTANCE hInst = GetResourceHandle();

    // Register window class once
    static bool registered = false;
    if (!registered)
    {
        WNDCLASSW wc = {};
        wc.lpfnWndProc = onRenameWinProc;
        wc.hInstance = hInst;
        wc.lpszClassName = L"PopupWinClass";
        RegisterClassW(&wc);
        registered = true;
    }

    auto [sel,pf] = getCurrentProjectFileSelection();
    std::wstring title = L"Rename " + pf;

    HWND hPopup = CreateWindowExW(
        0, L"PopupWinClass", title.c_str(),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        400, 300, 300, 150,
        faustWnd, nullptr, hInst, nullptr);

    CreateWindowExW(
        WS_EX_CLIENTEDGE, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE,
        20, 30, 240, 25,
        hPopup, (HMENU)RENAME_EDIT, hInst, nullptr);

    CreateWindowExW(
        0, L"BUTTON", L"OK",
        WS_CHILD | WS_VISIBLE,
        40, 70, 80, 25,
        hPopup, (HMENU)RENAME_OK, hInst, nullptr);

    CreateWindowExW(
        0, L"BUTTON", L"Cancel",
        WS_CHILD | WS_VISIBLE,
        140, 70, 80, 25,
        hPopup, (HMENU)RENAME_CANCEL, hInst, nullptr);

    // pass the pointer to the class (this) to the hPopup window to allow calling of OnRenameAccepted when user presses ok.
    SetWindowLongPtr(hPopup, GWLP_USERDATA, (LONG_PTR)this);

    ShowWindow(hPopup, SW_SHOW);
}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnNewProjectFile()
{
    // save code
    SaveCodeEditorText();
    
    std::string newName;
    fileManager.create(newName);
    std::wstring newPluginName = PluginUtils::string2wstring(newName);
    int idx = (int)SendMessage(projectFilesCombo, CB_ADDSTRING, 0, (LPARAM)newPluginName.c_str());
    SendMessage(projectFilesCombo, CB_SETCURSEL, idx, 0);   
    currentFileWorkingOn = newPluginName;
    SetCodeEditorText();
}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnProjectFileSelectionChange()
{
    int sel = (int)SendMessage(projectFilesCombo, CB_GETCURSEL, 0, 0);
    if (sel != CB_ERR)
    {
        SaveCodeEditorText();
        wchar_t buffer[256];
        SendMessage(projectFilesCombo, CB_GETLBTEXT, sel, (LPARAM)buffer);
        currentFileWorkingOn = buffer;
        SetCodeEditorText();
    }
}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnExportClicked()
{
    SaveCodeEditorText();
    
    // get the checkbox value
    bool saveDSP = (SendMessage(GetDlgItem(faustWnd, IDC_CHECK_SAVE_DSP),BM_GETCHECK, 0, 0) == BST_CHECKED);

    // prompt the user to choose a dir
    std::wstring userDir;
    int res = AskUserForDirectory(userDir);

    if (res==1) {
        ShowSimpleWindow(L"Can 't obtain the export directory to store the files.", L"Export canceled");
        return;
    }
    else if (res == 0) // store file(s) on SUCCES res
    {
        std::string filename = PluginUtils::wstring2string(currentFileWorkingOn);
        std::string storeDir = PluginUtils::wstring2string(userDir) + '/' + filename;
        std::filesystem::create_directory( std::filesystem::path(storeDir));

        // export cpp
        std::string cppfilePath = storeDir + '/' + filename + ".cpp";
        bool doublePrecision = (SendMessage(GetDlgItem(faustWnd,IDC_CHECK_DOUBLE_PRECISION),BM_GETCHECK, 0, 0) == BST_CHECKED);
        std::string errorMessage;
        bool cppExported = faustPluginLoader.exportCPP(
            filename,
            PluginUtils::wstring2string(dspCode),
            cppfilePath,
            doublePrecision,
            errorMessage
        );

        // export dsp
        bool dspExported=true;
        if (saveDSP) 
        {
            std::string dspfilePath = storeDir + '/' + filename + ".dsp";
            dspExported = PluginUtils::store_utf16_file(dspfilePath, dspCode);
        }

        // show windows
        std::string msg, title;

        if (!cppExported) {
            msg = "Could not export cpp file.\n" + errorMessage;
            title = "Export error";
        } 
        if (saveDSP && !dspExported) {
            msg+="\nCould not export dsp file.";
            title = "Export error";
        } 
        if (cppExported && dspExported) 
        {
            title = "Export success";
            msg = "Successfully exported cpp file";
            if (saveDSP) {
                msg += "\nSuccessfully exported dsp file.";
            }
            std::string dirMsg = "\nOutput dir : " + storeDir; 
            msg+=dirMsg;
        }
        ShowSimpleWindow(PluginUtils::string2wstring(msg).c_str(), PluginUtils::string2wstring(title).c_str());
    }
}

int Faust_Interpreter_Wwise_PluginPluginGUI::AskUserForDirectory(std::wstring& directory)
{
    IFileDialog* pfd = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&pfd));

    if (FAILED(hr))
    {
        return 1;
    }
    
    DWORD options;
    pfd->GetOptions(&options);
    pfd->SetOptions(options | FOS_PICKFOLDERS);

    hr = pfd->Show(faustWnd);   // parent window
    if (FAILED(hr)) {
        pfd->Release();
        return 2; // cancelled
    }

    IShellItem* pItem = nullptr;
    hr = pfd->GetResult(&pItem);
    if (FAILED(hr)) {
        pfd->Release();
        return 1; // failed
    }

    PWSTR path = nullptr;
    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &path);

    if (SUCCEEDED(hr))
    {
        directory = path;
    }
    
    CoTaskMemFree(path);
    pItem->Release();
    pfd->Release();

    return 0;
}

void Faust_Interpreter_Wwise_PluginPluginGUI::onDocsClicked()
{
    ShellExecuteW(
        faustWnd,
        L"open",
        std::wstring(FAUST_DOCS_PAGE).c_str(),
        NULL,
        NULL,
        SW_SHOWNORMAL
    );
}

/* 
---------------------------------------------------------------------------------------|
----------------------------- Async Build and Preview -------------------------------- |
---------------------------------------------------------------------------------------|
*/

void Faust_Interpreter_Wwise_PluginPluginGUI::OnPreviewButtonClicked()
{   
    // Important: this function runs asynchronously.
    
    SaveCodeEditorText();

    PluginState pluginState = faustPluginLoader.getPluginState();
    if ( pluginState != PluginState::READY)
    {

        // build plugin asynchronously
        std::thread([this]() {
                
                std::string errorMsg;        
                bool pluginCreated = faustPluginLoader.createPlugin(
                    PluginUtils::wstring2string(this->dspCode),
                    currAudioInputComboSelection,
                    errorMsg
                );
                
                if (!pluginCreated)
                {
                    std::wstring outputMessage = std::wstring(L"Failed to compile dsp file.\nError message:\n") 
                        + PluginUtils::string2wstring(errorMsg);
                    ShowSimpleWindow(outputMessage.c_str(),L"Preview error");
                    return;
                }
                    
                // disable selection of audio input source for the effect plugins when preview.
                EnableWindow(audioInputCombo, FALSE);

                ParameterList &parameters = faustPluginLoader.getParameters();
                PluginConfiguration& cfg = faustPluginLoader.getConfiguration();
                PluginState pluginState = faustPluginLoader.getPluginState();

                // verify that params are obtained...
                if (parameters.empty())
                {                    
                    ShowSimpleWindow( 
                        L"The DSP code does not define any parameters. Simply press \'Play\' to start playback", 
                        PluginUtils::string2wstring( cfg.plugin_name ).c_str()
                    );

                    while(pluginState==PluginState::PLUGIN_SET || pluginState==PluginState::READY)
                    {
                        pluginState = faustPluginLoader.getPluginState();
                    }
                }
                else
                {                
                    pluginWindow = new PluginWindow(faustWnd,cfg,parameters);
                    if (pluginWindow->isWindowCreated())
                    {
                        pluginWindow->Show();
                        pluginState = faustPluginLoader.getPluginState();
                        while
                        ( 
                            (pluginState==PluginState::PLUGIN_SET || pluginState==PluginState::READY)
                            && pluginWindow 
                            && pluginWindow->isActive() 
                        )
                        {
                            pluginWindow->Update();
                            pluginState = faustPluginLoader.getPluginState();
                        }
                        // close PluginWindow and reset plugin
                        if (pluginWindow){
                            delete pluginWindow;
                            pluginWindow = nullptr;
                            faustPluginLoader.resetPlugin();
                        }
                    }
                }
            
                // re-enable the audio Input combo
                EnableWindow(audioInputCombo, TRUE);

        }).detach();

    }

}

void Faust_Interpreter_Wwise_PluginPluginGUI::OnBuildButtonClicked(){
    
    SaveCodeEditorText();

    HWND buildButton = GetDlgItem(faustWnd, IDC_BUTTON_BUILD);
    EnableWindow(buildButton, FALSE);   // disable build button...

    std::thread([this, buildButton]()
    {        
        // compile using faust2wwise implementation..
        auto [id,pluginName] = getCurrentProjectFileSelection();
        bool doublePrecision = (SendMessage(GetDlgItem(faustWnd,IDC_CHECK_DOUBLE_PRECISION),BM_GETCHECK, 0, 0) == BST_CHECKED);
        bool isOutOfPlace = (SendMessage(GetDlgItem(faustWnd,IDC_CHECK_OUT_OF_PLACE),BM_GETCHECK, 0, 0) == BST_CHECKED);
        bool res = faustPluginLoader.buildPlugin(PluginUtils::wstring2string(pluginName), 
                                                PluginUtils::wstring2string(dspCode), 
                                                doublePrecision,
                                                isOutOfPlace,
                                                buildOutputText);
        
        // temp log message
        char dbg[256];
        snprintf(dbg, 256, "OnBuildButtonClicked: result is %d", res);
        AKPLATFORM::OutputDebugMsg(dbg);

        // notify GUI thread - re-enabling the button will happen after the message is received within winProc function.
        PostMessage(faustWnd, UnqBuildCompleteWndMsg, (WPARAM)buildButton, (LPARAM)res);

        //@TODO Design a way to allow user to inspect the output of the build (errors/warnings/success etc..)

    }).detach();

}

AK_ADD_PLUGIN_CLASS_TO_CONTAINER(
    Faust_Interpreter_Wwise_Plugin,            // Name of the plug-in container for this shared library
    Faust_Interpreter_Wwise_PluginPluginGUI,   // Authoring plug-in class to add to the plug-in container
    Faust_Interpreter_Wwise_PluginSource       // Corresponding Sound Engine plug-in class
);
