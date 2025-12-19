/************************** BEGIN HTMLExport.h **************************
 FAUST Architecture File
 Copyright (C) 2025 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_HTMLEXPORT_H
#define FAUST_HTMLEXPORT_H

#include <sstream>
#include <string>

#include "faust/gui/LayoutUI.h"

struct HTMLOptions {
    float       fWidth = 0.f;
    float       fHeight = 0.f;
    bool        fDebugOutlines = false;
    std::string fThemeCSS;
    std::string fScript;      // Inline JS payload (optional)
};

inline void htmlEscape(const std::string& in, std::ostream& out)
{
    for (char c : in) {
        switch (c) {
            case '&': out << "&amp;"; break;
            case '<': out << "&lt;"; break;
            case '>': out << "&gt;"; break;
            case '"': out << "&quot;"; break;
            case '\'': out << "&#39;"; break;
            default: out << c; break;
        }
    }
}

inline void htmlWidget(std::ostream& ss, const RenderNode& n, const std::string& cls)
{
    if (n.fHidden) {
        return;
    }
    ss << "<div class=\"widget " << cls;
    if (!n.fStyle.empty()) {
        ss << " style-" << n.fStyle;
    }
    ss << "\" data-path=\"";
    htmlEscape(n.fPath, ss);
    ss << "\" data-scale=\"";
    ss << (n.fScale == MetaDataUI::kLog ? "log" : (n.fScale == MetaDataUI::kExp ? "exp" : "lin"));
    if (!n.fStyle.empty()) {
        ss << "\" data-style=\"";
        htmlEscape(n.fStyle, ss);
    }
    if (!n.fUnit.empty()) {
        ss << "\" data-unit=\"";
        htmlEscape(n.fUnit, ss);
    }
    if (!n.fTooltip.empty()) {
        ss << "\" data-tooltip=\"";
        htmlEscape(n.fTooltip, ss);
    }
    ss << "\" data-value=\"0\" style=\"left:" << n.fX << "px;top:" << n.fY << "px;width:" << n.fWidth
       << "px;height:" << n.fHeight << "px;\">";
    if (!n.fTooltip.empty()) {
        ss << "<span class=\"tooltip\">";
        htmlEscape(n.fTooltip, ss);
        ss << "</span>";
    }
    ss << "</div>\n";
}

inline void htmlSlider(std::ostream& ss, const RenderNode& n, bool vertical)
{
    if (n.fHidden) {
        return;
    }
    std::string cls = vertical ? "vslider" : "hslider";
    ss << "<div class=\"widget slider " << cls;
    if (!n.fStyle.empty()) {
        ss << " style-" << n.fStyle;
    }
    ss << "\" data-path=\"";
    htmlEscape(n.fPath, ss);
    ss << "\" data-scale=\"";
    ss << (n.fScale == MetaDataUI::kLog ? "log" : (n.fScale == MetaDataUI::kExp ? "exp" : "lin"));
    if (!n.fStyle.empty()) {
        ss << "\" data-style=\"";
        htmlEscape(n.fStyle, ss);
    }
    ss << "\" data-value=\"0\" style=\"left:" << n.fX << "px;top:" << n.fY << "px;width:" << n.fWidth
       << "px;height:" << n.fHeight << "px;\">";
    ss << "<div class=\"track\"></div><div class=\"handle\"></div>";
    ss << "</div>\n";
}

inline void htmlBargraph(std::ostream& ss, const RenderNode& n, bool vertical)
{
    if (n.fHidden) {
        return;
    }
    std::string cls = vertical ? "vbargraph" : "hbargraph";
    ss << "<div class=\"widget bargraph " << cls << "\" data-path=\"";
    htmlEscape(n.fPath, ss);
    ss << "\" data-scale=\"";
    ss << (n.fScale == MetaDataUI::kLog ? "log" : (n.fScale == MetaDataUI::kExp ? "exp" : "lin"));
    ss << "\" data-value=\"0\" style=\"left:" << n.fX << "px;top:" << n.fY << "px;width:" << n.fWidth
       << "px;height:" << n.fHeight << "px;\">";
    ss << "<div class=\"bg\"></div><div class=\"fill\"></div></div>\n";
}

inline void htmlRadioMenu(std::ostream& ss, const RenderNode& n, bool isRadio)
{
    if (n.fHidden) {
        return;
    }
    std::string cls = isRadio ? "radio" : "menu";
    ss << "<div class=\"widget " << cls << "\" data-path=\"";
    htmlEscape(n.fPath, ss);
    ss << "\" data-style=\"" << cls << "\" style=\"left:" << n.fX << "px;top:" << n.fY
       << "px;width:" << n.fWidth << "px;height:" << n.fHeight << "px;\">";
    for (size_t i = 0; i < n.fOptions.size(); ++i) {
        ss << "<div class=\"option\" data-index=\"" << i << "\">";
        htmlEscape(n.fOptions[i].first, ss);
        ss << "</div>\n";
    }
    ss << "</div>\n";
}

inline void htmlGroup(std::ostream& ss, const RenderNode& node, const HTMLOptions& opt);

inline void htmlTabs(std::ostream& ss, const RenderNode& node, const HTMLOptions& opt)
{
    if (node.fHidden || node.fTabs.empty()) {
        return;
    }
    ss << "<div class=\"group tgroup\" style=\"left:" << node.fX << "px;top:" << node.fY
       << "px;width:" << node.fWidth << "px;height:" << node.fHeight << "px;\">\n";
    ss << "<div class=\"tab-headers\">\n";
    for (size_t i = 0; i < node.fTabs.size(); ++i) {
        ss << "<div class=\"tab-header\" data-tab=\"" << i << "\">";
        htmlEscape(node.fTabs[i].fLabel, ss);
        ss << "</div>\n";
    }
    ss << "</div>\n";
    ss << "<div class=\"tab-contents\">\n";
    for (size_t i = 0; i < node.fTabs.size(); ++i) {
        ss << "<div class=\"tab-content\" data-tab=\"" << i << "\">\n";
        htmlGroup(ss, node.fTabs[i], opt);
        ss << "</div>\n";
    }
    ss << "</div>\n";
    ss << "</div>\n";
}

inline void htmlGroup(std::ostream& ss, const RenderNode& node, const HTMLOptions& opt)
{
    if (node.fHidden) {
        return;
    }
    if (node.fType == RenderNodeType::kTGroup) {
        htmlTabs(ss, node, opt);
        return;
    }

    ss << "<div class=\"group";
    switch (node.fType) {
        case RenderNodeType::kHGroup: ss << " hgroup"; break;
        case RenderNodeType::kVGroup: ss << " vgroup"; break;
        default: break;
    }
    ss << "\" style=\"left:" << node.fX << "px;top:" << node.fY
       << "px;width:" << node.fWidth << "px;height:" << node.fHeight << "px;\">\n";

    if (opt.fDebugOutlines) {
        ss << "<div class=\"debug-outline\"></div>\n";
    }

    for (const auto& child : node.fChildren) {
        switch (child.fType) {
            case RenderNodeType::kHGroup:
            case RenderNodeType::kVGroup:
            case RenderNodeType::kTGroup:
                htmlGroup(ss, child, opt);
                break;
            case RenderNodeType::kButton:
                htmlWidget(ss, child, "button");
                break;
            case RenderNodeType::kCheckButton:
                htmlWidget(ss, child, "checkbutton");
                break;
            case RenderNodeType::kHSlider:
                if (child.fStyle == "radio") {
                    htmlRadioMenu(ss, child, true);
                } else if (child.fStyle == "menu") {
                    htmlRadioMenu(ss, child, false);
                } else {
                    htmlSlider(ss, child, false);
                }
                break;
            case RenderNodeType::kVSlider:
                if (child.fStyle == "radio") {
                    htmlRadioMenu(ss, child, true);
                } else if (child.fStyle == "menu") {
                    htmlRadioMenu(ss, child, false);
                } else {
                    htmlSlider(ss, child, true);
                }
                break;
            case RenderNodeType::kNumEntry:
                htmlWidget(ss, child, "numentry");
                break;
            case RenderNodeType::kHBargraph:
                htmlBargraph(ss, child, false);
                break;
            case RenderNodeType::kVBargraph:
                htmlBargraph(ss, child, true);
                break;
            default:
                htmlWidget(ss, child, "unknown");
                break;
        }
    }

    ss << "</div>\n";
}

inline std::string renderHTML(const RenderNode& root, const HTMLOptions& opt)
{
    std::ostringstream ss;
    float w = (opt.fWidth > 0.f) ? opt.fWidth : root.fWidth;
    float h = (opt.fHeight > 0.f) ? opt.fHeight : root.fHeight;

    ss << "<!DOCTYPE html>\n<html><head><meta charset=\"utf-8\"/>\n<style>\n";
    ss << ":root { --bg: #f4f7fb; --panel: #ffffff; --text: #1f2335; --stroke: #1f2a44; --muted: #d7deea; --primary: #4a7cff; --accent: #5ac8fa; --shadow: 0 6px 12px rgba(17,24,39,0.12); --radius: 8px; }\n";
    ss << ".faust-ui { position: relative; width:" << w << "px; height:" << h << "px; background: linear-gradient(180deg, #f7f9ff 0%, #eef2fb 100%); color: var(--text); font-family: 'Inter', 'Helvetica Neue', Arial, sans-serif; }\n";
    ss << ".group { position: absolute; }\n";
    ss << ".widget { position: absolute; box-sizing: border-box; border-radius: var(--radius); }\n";
    ss << ".button, .checkbutton { border:1px solid var(--muted); background: linear-gradient(180deg, #ffffff 0%, #f1f4fb 100%); box-shadow: var(--shadow); transition: transform 80ms ease, box-shadow 120ms ease; }\n";
    ss << ".button:hover, .checkbutton:hover { transform: translateY(-1px); box-shadow: 0 8px 18px rgba(17,24,39,0.16); }\n";
    ss << ".checkbutton.checked { background: linear-gradient(180deg, #e4f5ec 0%, #d2f0e1 100%); border-color: #2a7; }\n";
    ss << ".slider { border:1px solid #c4cee2; background: #e6ecf7; overflow:hidden; box-shadow: inset 0 1px 2px rgba(17,24,39,0.08); }\n";
    ss << ".slider .track { position:absolute; inset:4px; border-radius: 999px; background: linear-gradient(90deg, #e5eaf6 0%, #d7dff0 100%); }\n";
    ss << ".slider .handle { position:absolute; width:10px; height:100%; background: linear-gradient(180deg, #5ac8fa 0%, #4a7cff 100%); border-radius:999px; box-shadow: 0 2px 6px rgba(17,24,39,0.2); }\n";
    ss << ".vslider .handle { width:100%; height:10px; }\n";
    ss << ".numentry { border:1px solid #c4cee2; background:#fffbe6; box-shadow: inset 0 1px 2px rgba(0,0,0,0.08); }\n";
    ss << ".bargraph { border:1px solid #c4cee2; background:#f2f4f8; overflow:hidden; box-shadow: inset 0 1px 2px rgba(0,0,0,0.08); }\n";
    ss << ".bargraph .bg { position:absolute; inset:0; background: linear-gradient(180deg, #f8fafc 0%, #edf2f7 100%); }\n";
    ss << ".bargraph .fill { position:absolute; inset:0; background: linear-gradient(180deg, #5ac8fa, #4a7cff); transform-origin:left center; box-shadow: inset 0 0 0 1px rgba(17,24,39,0.08); }\n";
    ss << ".radio .option, .menu .option { padding: 6px 8px; border:1px solid #c4cee2; border-radius:6px; margin-bottom:4px; cursor:pointer; background:#fff; box-shadow: var(--shadow); }\n";
    ss << ".radio .option.selected, .menu .option.selected { border-color: var(--primary); box-shadow: 0 0 0 2px rgba(74,124,255,0.18); background: #f2f6ff; }\n";
    ss << ".tab-headers { display:flex; gap:6px; margin-bottom:6px; }\n";
    ss << ".tab-header { padding:6px 10px; background:#f1f3f9; border:1px solid #c4cee2; border-radius:6px; cursor:pointer; box-shadow: var(--shadow); }\n";
    ss << ".tab-content { display:none; position:relative; }\n";
    ss << ".tab-content.active { display:block; }\n";
    ss << ".debug-outline { position:absolute; inset:0; border:1px dashed magenta; pointer-events:none; }\n";
    if (!opt.fThemeCSS.empty()) {
        ss << opt.fThemeCSS << "\n";
    }
    ss << "</style>\n";
    if (!opt.fScript.empty()) {
        ss << "<script>" << opt.fScript << "</script>\n";
    }
    ss << "</head><body><div class=\"faust-ui\">\n";

    htmlGroup(ss, root, opt);

    ss << "</div></body></html>\n";
    return ss.str();
}

inline std::string defaultHTMLScript()
{
    return R"JS(
    (function() {
      function selectAll(sel, root) { return Array.prototype.slice.call((root||document).querySelectorAll(sel)); }
      function clamp01(v) { return Math.min(1, Math.max(0, v)); }

      var host = null;

      function setActiveTab(container, index) {
        selectAll('.tab-content', container).forEach(function(el, i) {
          if (i === index) { el.classList.add('active'); }
          else { el.classList.remove('active'); }
        });
      }

      // Default first tab active
      selectAll('.tab-contents').forEach(function(container) {
        setActiveTab(container.parentNode, 0);
      });

      // Tab header click handling
      selectAll('.tab-headers .tab-header').forEach(function(header) {
        header.addEventListener('click', function() {
          var idx = parseInt(header.getAttribute('data-tab'), 10);
          var container = header.closest('.group');
          setActiveTab(container, idx);
        });
      });

      var host = (typeof window !== 'undefined' && window.faustHost) ? window.faustHost : null;

      function applyScale(t, scale) {
        if (scale === 'log') return t * t;
        if (scale === 'exp') return Math.sqrt(t);
        return t;
      }

      function applyScaleInverse(v, scale) {
        if (scale === 'log') return Math.sqrt(v);
        if (scale === 'exp') return v * v;
        return v;
      }

      function updateVisual(path, v) {
        selectAll('[data-path]').forEach(function(el) {
          if (el.getAttribute('data-path') !== path) return;
          var scale = el.getAttribute('data-scale') || 'lin';
          var t = applyScaleInverse(clamp01(v), scale);
          if (el.classList.contains('hslider') || el.classList.contains('vslider')) {
            setHandlePosition(el, t, el.classList.contains('vslider'));
          } else if (el.classList.contains('bargraph')) {
            setBarFill(el, t, el.classList.contains('vbargraph'));
          } else if (el.classList.contains('checkbutton')) {
            if (v > 0) el.classList.add('checked'); else el.classList.remove('checked');
          } else if (el.classList.contains('radio') || el.classList.contains('menu')) {
            selectOption(el, Math.round(v));
          }
        });
      }

      function setHandlePosition(sl, t, vertical) {
        var handle = sl.querySelector('.handle');
        if (!handle) return;
        var rect = sl.getBoundingClientRect();
        if (vertical) {
          var h = handle.getBoundingClientRect().height || 6;
          var y = t * (rect.height - h);
          handle.style.top = (rect.height - h - y) + 'px';
          handle.style.left = '0px';
        } else {
          var w = handle.getBoundingClientRect().width || 6;
          var x = t * (rect.width - w);
          handle.style.left = x + 'px';
          handle.style.top = '0px';
        }
        sl.setAttribute('data-value', t);
      }

      function setBarFill(bg, t, vertical) {
        var fill = bg.querySelector('.fill');
        if (!fill) return;
        if (vertical) {
          fill.style.height = (t * 100) + '%';
          fill.style.top = ((1 - t) * 100) + '%';
        } else {
          fill.style.width = (t * 100) + '%';
        }
        bg.setAttribute('data-value', t);
      }

      function handlePointer(el, cb) {
        function onMove(ev) {
          if (!down) return;
          ev.preventDefault();
          cb(ev);
        }
        var down = false;
        el.addEventListener('pointerdown', function(ev) { down = true; el.setPointerCapture(ev.pointerId); onMove(ev); });
        el.addEventListener('pointermove', onMove);
        el.addEventListener('pointerup', function(ev) { down = false; el.releasePointerCapture(ev.pointerId); });
        el.addEventListener('pointercancel', function(ev) { down = false; el.releasePointerCapture(ev.pointerId); });
      }

      selectAll('.hslider').forEach(function(sl) {
        handlePointer(sl, function(ev) {
          var rect = sl.getBoundingClientRect();
          var t = Math.min(1, Math.max(0, (ev.clientX - rect.left) / rect.width));
          var scale = sl.getAttribute('data-scale') || 'lin';
          var hv = applyScale(t, scale);
          var path = sl.getAttribute('data-path');
          if (host && host.setParamValue) host.setParamValue(path, hv);
          setHandlePosition(sl, t, false);
        });
        setHandlePosition(sl, parseFloat(sl.getAttribute('data-value')) || 0, false);
      });

      selectAll('.vslider').forEach(function(sl) {
        handlePointer(sl, function(ev) {
          var rect = sl.getBoundingClientRect();
          var t = 1 - Math.min(1, Math.max(0, (ev.clientY - rect.top) / rect.height));
          var scale = sl.getAttribute('data-scale') || 'lin';
          var hv = applyScale(t, scale);
          var path = sl.getAttribute('data-path');
          if (host && host.setParamValue) host.setParamValue(path, hv);
          setHandlePosition(sl, t, true);
        });
        setHandlePosition(sl, parseFloat(sl.getAttribute('data-value')) || 0, true);
      });

      selectAll('.button').forEach(function(btn) {
        btn.addEventListener('click', function() {
          var path = btn.getAttribute('data-path');
          if (host && host.setParamValue) host.setParamValue(path, 1);
        });
      });

      selectAll('.checkbutton').forEach(function(chk) {
        chk.addEventListener('click', function() {
          chk.classList.toggle('checked');
          var v = chk.classList.contains('checked') ? 1 : 0;
          var path = chk.getAttribute('data-path');
          if (host && host.setParamValue) host.setParamValue(path, v);
        });
      });

      function selectOption(container, index) {
        selectAll('.option', container).forEach(function(opt, i) {
          if (i === index) opt.classList.add('selected'); else opt.classList.remove('selected');
        });
        container.setAttribute('data-value', index);
      }

      selectAll('.radio, .menu').forEach(function(group) {
        selectAll('.option', group).forEach(function(opt, idx) {
          opt.addEventListener('click', function() {
            selectOption(group, idx);
            var path = group.getAttribute('data-path');
            if (host && host.setParamValue) host.setParamValue(path, idx);
          });
        });
        selectOption(group, parseFloat(group.getAttribute('data-value')) || 0);
      });

      // Host binding and pull-to-refresh hook
      function refresh() {
        if (!host || !host.getParamValue) return;
        var seen = {};
        selectAll('[data-path]').forEach(function(el) {
          var path = el.getAttribute('data-path');
          if (seen[path]) return;
          seen[path] = true;
          var v = host.getParamValue(path);
          if (typeof v === 'number') updateVisual(path, v);
        });
      }

      if (typeof window !== 'undefined') {
        host = window.faustHost || null;
        window.faustUI = window.faustUI || {};
        window.faustUI.bindHost = function(h) { host = h || null; };
        window.faustUI.refresh = refresh;
        window.faustUI.setValue = updateVisual;
      }

      if (host && host.getParamValue) {
        function pump() { refresh(); window.requestAnimationFrame(pump); }
        window.requestAnimationFrame(pump);
      }
    })();
    )JS";
}

/**
 * Generate an HTML string for a given DSP.
 * @param dsp           Pointer to a Faust DSP
 * @param target_width  Target HTML viewport width (if <=0, use intrinsic)
 * @param target_height Target HTML viewport height (if <=0, use intrinsic)
 * @param debugOutlines Draw debug rectangles around groups if true
 */
template <typename DSP>
inline std::string toHTML(DSP* dsp,
                          float target_width = -1.f,
                          float target_height = -1.f,
                          bool debugOutlines = false)
{
    auto resolved = buildResolvedLayout(dsp, target_width, target_height, 0.f, 0.f);
    RenderNode root = buildRenderTree(resolved.fUI);
    
    HTMLOptions opt;
    opt.fWidth = target_width;
    opt.fHeight = target_height;
    opt.fDebugOutlines = debugOutlines;
    opt.fScript = defaultHTMLScript();
    
    return renderHTML(root, opt);
}

#endif // FAUST_HTMLEXPORT_H
/**************************  END  HTMLExport.h **************************/
