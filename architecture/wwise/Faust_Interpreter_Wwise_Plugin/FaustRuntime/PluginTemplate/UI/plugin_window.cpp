#include "plugin_window.h"
#include "PluginUtils/plugin_utils.h"
#include <cmath>

#define PREVIEW_ID_BASE 1000

PluginWindow::PluginWindow(HWND parent, PluginConfiguration& config, ParameterList& params)
    : cfg(config)
    , parameters(params)
    , parentWnd(parent)
    , windowCreated(false)
    , y_span {DEFAULT_Y_SPAN}
    , x_margin{DEFAULT_X_MARGIN}
    , curr_height(10)
    , windowTitle(PluginUtils::string2wstring(cfg.plugin_name).c_str())

{
    windowCreated = createWindow();
}

PluginWindow::~PluginWindow()
{
    Close();
}

void PluginWindow::Close()
{
    if (hwnd)
    {
        DestroyWindow(hwnd);
        hwnd = nullptr;
    }
    sliderValues.clear();
    monitorValues.clear();
}

bool PluginWindow::isWindowCreated()
{
    return windowCreated;
}

void PluginWindow::Show()
{
    ShowWindow(hwnd, SW_SHOW);
}

bool PluginWindow::isActive()
{
    return hwnd && IsWindow(hwnd);
}

void PluginWindow::Update()
{
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        DispatchMessage(&msg);
    }
}

bool PluginWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            return true;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return true;

        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                /*
                // it may be a button or a checkbox. @TODO buttons are used as checkboxes for now. They are triggered by pressing the Play button in the Wwise editor.
                if(LOWORD(wParam) == IDC_BUTTON_NEW)
                {
                    // AKPLATFORM::OutputDebugMsg("Button clicked!\n");
                }
                else if (LOWORD(wParam) == IDC_CHECKBOX_NEW)
                {
                    LRESULT state = SendDlgItemMessage(hwnd, IDC_CHECKBOX_NEW, BM_GETCHECK, 0, 0);
                    bool isChecked = (state == BST_CHECKED);
                    // if (isChecked)
                    //     AKPLATFORM::OutputDebugMsg("Checkbox checked!\n");
                    // else AKPLATFORM::OutputDebugMsg("Checkbox unchecked!\n");
                } 
                */
               int previewID = LOWORD(wParam);
               LRESULT state = SendDlgItemMessage(hwnd, previewID, BM_GETCHECK, 0, 0);
               float value = (state == BST_CHECKED) ? 1.0f : .0f;
               checkBoxValues[previewID]->store(value);
            }
            return true;
        case WM_HSCROLL:
        {
            HWND slider = reinterpret_cast<HWND>(lParam);
            int ctrID = GetDlgCtrlID(slider);
            SliderVal& val = sliderValues[ctrID];

            int pos = static_cast<int>(SendMessage(slider, TBM_GETPOS, 0, 0));

            // update slider value
            // float actualValue = val.minVal + pos * val.step;
            float actualValue = val.minVal + (pos - static_cast<int>(std::round(val.minVal / val.step))) * val.step;
            wchar_t valueTxt[16];
            swprintf(valueTxt, 16, L"%.3f", actualValue);
            SetWindowText(val.hWnd, valueTxt);

            val.value->store(actualValue);

            return true;
        }
        case WM_TIMER:
            UpdateMonitoringValues();
            return true;

        case WM_QUIT:
        {
            Close();
            return false;
        }
        case WM_VSCROLL:
        {
            // TODO: This case needs much much work.
            SCROLLINFO si = { sizeof(si) };
            si.fMask = SIF_ALL;
            GetScrollInfo(hwnd, SB_VERT, &si);  // SB_VERT for WS_VSCROLL, SB_CTL for scrollbar control
            int oldPos = si.nPos;

            // Determine new scroll position
            switch (LOWORD(wParam))
            {
                case SB_LINEUP:    si.nPos -= 10; break;   // scroll up 10 pixels
                case SB_LINEDOWN:  si.nPos += 10; break;   // scroll down 10 pixels
                case SB_PAGEUP:    si.nPos -= si.nPage; break;
                case SB_PAGEDOWN:  si.nPos += si.nPage; break;
                case SB_THUMBTRACK: si.nPos = si.nTrackPos; break;
                case SB_THUMBPOSITION: si.nPos = si.nTrackPos; break;
            }

            // Clamp to valid range
            if (si.nPos < si.nMin) si.nPos = si.nMin;
            if (si.nPos > si.nMax - (int)si.nPage) si.nPos = si.nMax - si.nPage;

            // Set updated scroll position
            si.fMask = SIF_POS;
            SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

            int delta = si.nPos - oldPos; // how far to scroll

            if (delta != 0)
            {
                HWND child = GetWindow(hwnd, GW_CHILD);
                while (child)
                {
                    RECT rc;
                    GetWindowRect(child, &rc);
                    MapWindowPoints(nullptr, hwnd, (POINT*)&rc, 2);
                    SetWindowPos(child, nullptr, rc.left, rc.top - delta, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                    child = GetNextWindow(child, GW_HWNDNEXT);
                }                
            }

            return 0;
        }
    }
    // UpdateMonitoringValues();
    return false;
}

void PluginWindow::configureWindowScrolling()
{
    // messes up the scrolling functionallity
    SCROLLINFO si = { sizeof(si) };
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = 0;                 // top of content
    si.nMax = curr_height - 1;     // bottom of content
    si.nPage = cfg.preview.height;        // visible client height
    si.nPos = 0;                  // initial scroll position

    SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}

LRESULT CALLBACK PluginWindow::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PluginWindow* pThis = nullptr;

    if (msg == WM_NCCREATE)
    {
        // store the class pointer ('this') from lpCreateParams within GWLP_USERDATA to retrieve it in the next iteration
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<PluginWindow*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
    }
    else
    {
        pThis = reinterpret_cast<PluginWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis && pThis->WindowProc(hwnd, msg, wParam, lParam))
        return 0;

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool PluginWindow::createWindow()
{
    // setup before creating window..
    WNDCLASS wc = {};
    wc.lpfnWndProc = StaticWndProc;
    wc.hInstance = nullptr;
    wc.lpszClassName = windowTitle;
    if (!GetClassInfo(nullptr, windowTitle, &wc))
    {
        RegisterClass(&wc);
    }

    hwnd = CreateWindowEx(
    0,
    windowTitle,
    windowTitle,
    WS_OVERLAPPEDWINDOW | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT, cfg.preview.width,cfg.preview.height,
    parentWnd, nullptr, nullptr, this);
    
    if (createUIcontrols())
    {
        // configureWindowScrolling();
        return true;
    }

    return false;
}

bool PluginWindow::createUIcontrols()
{
    if (hwnd)
    {
        bool success;
        for (Parameter& p : parameters)
        {
            // set the preview.id
            p.preview.id = p.index + int(PREVIEW_ID_BASE);

            if (p.type == "button")
                // success = CreateButton(p); // @TODO Fix : buttons are replaced with checkboxes. Need to find a way to reset the button after it is pressed to a non-pressed state after it is consumed by the (faust) compute function.
                success = CreateCheckbox(p);
            else if (p.type == "checkbox")
                success = CreateCheckbox(p);
            else if (p.type == "slider")
                success = CreateSlider(p);
            else if (p.type == "bargraph" )
                success = CreateMonitor(p);
            else
                break;
            curr_height+=y_span;
        }

        SetTimer(hwnd, 1, 100, nullptr);

        return success;
    }
    return false;
}

bool PluginWindow::ProcessMessages()
{
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

bool PluginWindow::CreateButton(Parameter& p)
{
    HWND hButton = CreateWindow(
        L"BUTTON",              // Predefined button class
        PluginUtils::string2wstring(p.shortname).c_str(),            // title
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // stylee
        10, curr_height, 100, 30,        // x, y , width, height
        hwnd,                 // parent window
        (HMENU)p.preview.id,                // IDC alternative
        nullptr,    // hInstance from GetResourceHandle
        nullptr             // nevermind
    );
    
    if(!hButton)
        return false;
    return true;
}

bool PluginWindow::CreateCheckbox(Parameter& p)
{
    HWND hCheck = CreateWindow(
        L"BUTTON",              
        PluginUtils::string2wstring(p.shortname).c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        10, curr_height, p.shortname.length()*12, 30,        // x, y, width, height
        hwnd,
        (HMENU)p.preview.id,    
        nullptr,
        nullptr
    );
    if(!hCheck)
        return false;
    
    UINT val = (p.init>0) ? BST_CHECKED : BST_UNCHECKED; // default is unchecked
    SendDlgItemMessage(hwnd, p.preview.id, BM_SETCHECK, val , 0);

    checkBoxValues[p.preview.id] = &p.value;

    return true;
}

bool PluginWindow::CreateSlider(Parameter& p)
{
    int curr_width = p.shortname.length()*12;
    // create the text first
    HWND hText = CreateWindow(
        L"STATIC",
        PluginUtils::string2wstring(p.shortname).c_str(),
        WS_CHILD | WS_VISIBLE,
        10, curr_height, curr_width, y_span,
        hwnd,
        nullptr,
        nullptr,
        nullptr
    );

    if (!hText)
        return false;
    
    int scaledMin  = static_cast<int>(std::round(p.pmin / p.step));
    int scaledMax  = static_cast<int>(std::round(p.pmax / p.step));
    int scaledInit = static_cast<int>(std::round(p.init / p.step));

    curr_width += x_margin+10;
    // create the slider itself
    HWND hSlider = CreateWindowEx(
        0,
        TRACKBAR_CLASS,
        L"",
        WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
        curr_width, curr_height, 200, y_span,
        hwnd,
        (HMENU)p.preview.id,
        nullptr,
        nullptr
    );

    if (!hSlider)
        return false;

    SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKELONG(scaledMin, scaledMax));
    SendMessage(hSlider, TBM_SETPOS, TRUE, scaledInit);

    curr_width += x_margin+210;
    // label for displaying the value 
    HWND hwndSliderValue = CreateWindow(
        L"STATIC",
        std::to_wstring(p.init).c_str(),
        WS_CHILD | WS_VISIBLE,
        curr_width, curr_height, 60, y_span,
        hwnd,
        nullptr,
        nullptr,
        nullptr
    );

    if (!hwndSliderValue)
        return false;

    SliderVal val;
    val.hWnd = hwndSliderValue;
    val.minVal = p.pmin;
    val.maxVal = p.pmax;
    val.step = p.step;
    val.value = &p.value;

    sliderValues[p.preview.id] = val;
    
    return true;
}


bool PluginWindow::CreateMonitor(Parameter& p)
{
    int curr_width = p.shortname.length()*12;
    // Label for the monitor
    HWND hText = CreateWindow(
        L"STATIC",
        PluginUtils::string2wstring(p.shortname).c_str(), 
        WS_CHILD | WS_VISIBLE,
        10, curr_height, curr_width, y_span,         // x, y, width, height
        hwnd,
        nullptr,
        nullptr,
        nullptr
    );

    if (!hText)
        return false;

    curr_width+= x_margin;
    // Value display
    HWND hwndMonitorValue = CreateWindow(
        L"STATIC",
        std::to_wstring(p.init).c_str(),
        WS_CHILD | WS_VISIBLE | SS_RIGHT, // right-aligned text
        curr_width, curr_height, 60, y_span,
        hwnd,
        nullptr,
        nullptr,
        nullptr
    );

    if (!hwndMonitorValue)
        return false;
    
    monitorValues.push_back({hwndMonitorValue, &p.value});

    return true;
}

void PluginWindow::UpdateMonitoringValues()
{
    for (auto& monitorVar : monitorValues)
    {
        wchar_t buffer[32];
        swprintf(buffer, 32, L"%.2f", monitorVar.second->load());
        SetWindowText(monitorVar.first, buffer);
    }
}
