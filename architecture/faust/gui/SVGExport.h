/************************** BEGIN SVGExport.h **************************
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

#ifndef FAUST_SVGEXPORT_H
#define FAUST_SVGEXPORT_H

#include <sstream>
#include <string>

#include "faust/gui/LayoutUI.h"

struct SVGOptions {
    float       fWidth = 0.f;
    float       fHeight = 0.f;
    bool        fDebugOutlines = false;
    std::string fThemeCSS;
    std::string fScript;      // Inline JS payload
};

inline void svgEscape(const std::string& in, std::ostream& out)
{
    for (char c : in) {
        switch (c) {
            case '&': out << "&amp;"; break;
            case '<': out << "&lt;"; break;
            case '>': out << "&gt;"; break;
            case '"': out << "&quot;"; break;
            case '\'': out << "&apos;"; break;
            default: out << c; break;
        }
    }
}

inline const char* scaleToString(MetaDataUI::Scale s)
{
    switch (s) {
        case MetaDataUI::kLog: return "log";
        case MetaDataUI::kExp: return "exp";
        default: return "lin";
    }
}

inline void svgRect(std::ostream& ss, const RenderNode& n, const std::string& cls)
{
    if (n.fHidden) {
        return;
    }
    std::string merged_cls = cls;
    if (!n.fStyle.empty()) {
        merged_cls += " style-" + n.fStyle;
    }
    ss << "<g class=\"" << merged_cls << "\" data-path=\"";
    svgEscape(n.fPath, ss);
    ss << "\"";
    if (!n.fUnit.empty()) {
        ss << " data-unit=\"";
        svgEscape(n.fUnit, ss);
        ss << "\"";
    }
    if (!n.fTooltip.empty()) {
        ss << " data-tooltip=\"";
        svgEscape(n.fTooltip, ss);
        ss << "\"";
    }
    ss << " data-scale=\"" << scaleToString(n.fScale) << "\"";
    if (!n.fStyle.empty()) {
        ss << " data-style=\"";
        svgEscape(n.fStyle, ss);
        ss << "\"";
    }
    ss << ">";
    ss << "<rect x=\"" << n.fX << "\" y=\"" << n.fY
       << "\" width=\"" << n.fWidth << "\" height=\"" << n.fHeight << "\" />\n";
    if (merged_cls.find("checkbutton") != std::string::npos) {
        float mark_x1 = n.fX + n.fWidth * 0.25f;
        float mark_y1 = n.fY + n.fHeight * 0.55f;
        float mark_x2 = n.fX + n.fWidth * 0.45f;
        float mark_y2 = n.fY + n.fHeight * 0.75f;
        float mark_x3 = n.fX + n.fWidth * 0.75f;
        float mark_y3 = n.fY + n.fHeight * 0.25f;
        ss << "<polyline class=\"mark\" points=\""
           << mark_x1 << "," << mark_y1 << " "
           << mark_x2 << "," << mark_y2 << " "
           << mark_x3 << "," << mark_y3 << "\" />\n";
    }
    if (!n.fTooltip.empty()) {
        ss << "<title>";
        svgEscape(n.fTooltip, ss);
        ss << "</title>";
    }
    ss << "</g>\n";
}

inline void svgSlider(std::ostream& ss, const RenderNode& n, const std::string& cls, bool vertical)
{
    if (n.fHidden) {
        return;
    }
    std::string merged_cls = cls;
    if (!n.fStyle.empty()) {
        merged_cls += " style-" + n.fStyle;
    }
    float track_x = n.fX;
    float track_y = n.fY;
    float track_w = n.fWidth;
    float track_h = n.fHeight;

    ss << "<g class=\"" << merged_cls << "\" data-path=\"";
    svgEscape(n.fPath, ss);
    ss << "\"";
    if (!n.fUnit.empty()) {
        ss << " data-unit=\"";
        svgEscape(n.fUnit, ss);
        ss << "\"";
    }
    if (!n.fTooltip.empty()) {
        ss << " data-tooltip=\"";
        svgEscape(n.fTooltip, ss);
        ss << "\"";
    }
    ss << " data-scale=\"" << scaleToString(n.fScale) << "\"";
    if (!n.fStyle.empty()) {
        ss << " data-style=\"";
        svgEscape(n.fStyle, ss);
        ss << "\"";
    }
    ss << " data-value=\"0\">";

    ss << "<rect class=\"track\" x=\"" << track_x << "\" y=\"" << track_y
       << "\" width=\"" << track_w << "\" height=\"" << track_h << "\"/>\n";

    // Handle: horizontal uses width 6px, vertical uses height 6px
    if (vertical) {
        ss << "<rect class=\"handle\" x=\"" << track_x << "\" y=\"" << track_y
           << "\" width=\"" << track_w << "\" height=\"6\" />\n";
    } else {
        ss << "<rect class=\"handle\" x=\"" << track_x << "\" y=\"" << track_y
           << "\" width=\"6\" height=\"" << track_h << "\" />\n";
    }

    if (!n.fTooltip.empty()) {
        ss << "<title>";
        svgEscape(n.fTooltip, ss);
        ss << "</title>\n";
    }

    ss << "</g>\n";
}

inline void svgBargraph(std::ostream& ss, const RenderNode& n, const std::string& cls, bool vertical)
{
    if (n.fHidden) {
        return;
    }
    std::string merged_cls = cls;
    if (!n.fStyle.empty()) {
        merged_cls += " style-" + n.fStyle;
    }
    float bg_x = n.fX;
    float bg_y = n.fY;
    float bg_w = n.fWidth;
    float bg_h = n.fHeight;

    ss << "<g class=\"" << merged_cls << "\" data-path=\"";
    svgEscape(n.fPath, ss);
    ss << "\"";
    if (!n.fUnit.empty()) {
        ss << " data-unit=\"";
        svgEscape(n.fUnit, ss);
        ss << "\"";
    }
    if (!n.fTooltip.empty()) {
        ss << " data-tooltip=\"";
        svgEscape(n.fTooltip, ss);
        ss << "\"";
    }
    ss << " data-scale=\"" << scaleToString(n.fScale) << "\"";
    if (!n.fStyle.empty()) {
        ss << " data-style=\"";
        svgEscape(n.fStyle, ss);
        ss << "\"";
    }
    ss << " data-value=\"0\">";

    ss << "<rect class=\"bg\" x=\"" << bg_x << "\" y=\"" << bg_y
       << "\" width=\"" << bg_w << "\" height=\"" << bg_h << "\"/>\n";

    if (vertical) {
        ss << "<rect class=\"fill\" x=\"" << bg_x << "\" y=\"" << (bg_y + bg_h)
           << "\" width=\"" << bg_w << "\" height=\"0\" />\n";
    } else {
        ss << "<rect class=\"fill\" x=\"" << bg_x << "\" y=\"" << bg_y
           << "\" width=\"0\" height=\"" << bg_h << "\" />\n";
    }

    if (!n.fTooltip.empty()) {
        ss << "<title>";
        svgEscape(n.fTooltip, ss);
        ss << "</title>\n";
    }

    ss << "</g>\n";
}

inline void svgKnob(std::ostream& ss, const RenderNode& n, const std::string& cls)
{
    if (n.fHidden) {
        return;
    }
    std::string merged_cls = cls;
    if (!n.fStyle.empty()) {
        merged_cls += " style-" + n.fStyle;
    }
    float cx = n.fX + n.fWidth * 0.5f;
    float cy = n.fY + n.fHeight * 0.5f;
    float r = std::min(n.fWidth, n.fHeight) * 0.5f;
    float needle_r = r * 0.65f;

    ss << "<g class=\"" << merged_cls << "\" data-path=\"";
    svgEscape(n.fPath, ss);
    ss << "\"";
    if (!n.fUnit.empty()) {
        ss << " data-unit=\"";
        svgEscape(n.fUnit, ss);
        ss << "\"";
    }
    if (!n.fTooltip.empty()) {
        ss << " data-tooltip=\"";
        svgEscape(n.fTooltip, ss);
        ss << "\"";
    }
    ss << " data-scale=\"" << scaleToString(n.fScale) << "\" data-style=\"knob\" data-value=\"0\">";

    ss << "<circle class=\"dial\" cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\"/>\n";
    // Needle defaults to min angle
    float angle_deg = -135.f;
    float angle_rad = angle_deg * float(M_PI) / 180.f;
    float nx = cx + std::cos(angle_rad) * needle_r;
    float ny = cy + std::sin(angle_rad) * needle_r;
    ss << "<line class=\"needle\" x1=\"" << cx << "\" y1=\"" << cy << "\" x2=\"" << nx << "\" y2=\"" << ny << "\" />\n";

    if (!n.fTooltip.empty()) {
        ss << "<title>";
        svgEscape(n.fTooltip, ss);
        ss << "</title>\n";
    }

    ss << "</g>\n";
}

inline void svgRadioMenu(std::ostream& ss, const RenderNode& n, const std::string& cls, bool isRadio)
{
    if (n.fHidden) {
        return;
    }
    std::string merged_cls = cls;
    float option_h = 18.f;
    float option_w = n.fWidth;
    const auto& opts = n.fOptions;
    int options = opts.empty() ? 0 : int(opts.size());

    ss << "<g class=\"" << merged_cls << "\" data-path=\"";
    svgEscape(n.fPath, ss);
    ss << "\" data-style=\"" << (isRadio ? "radio" : "menu") << "\"";
    if (!n.fUnit.empty()) {
        ss << " data-unit=\"";
        svgEscape(n.fUnit, ss);
        ss << "\"";
    }
    if (!n.fTooltip.empty()) {
        ss << " data-tooltip=\"";
        svgEscape(n.fTooltip, ss);
        ss << "\"";
    }
    ss << " data-scale=\"" << scaleToString(n.fScale) << "\" data-value=\"0\">";

    for (int i = 0; i < options; ++i) {
        float oy = n.fY + i * option_h;
        ss << "<g class=\"option\" data-index=\"" << i << "\">";
        if (isRadio) {
            float r = 6.f;
            float cx = n.fX + r + 4;
            float cy = oy + option_h * 0.5f;
            ss << "<circle class=\"shell\" cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r << "\" />\n";
            ss << "<circle class=\"dot\" cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << (r - 3) << "\" />\n";
            ss << "<text class=\"label\" x=\"" << (cx + r + 6) << "\" y=\"" << cy + 4 << "\">";
            svgEscape(opts[i].first, ss);
            ss << "</text>\n";
        } else {
            float bx = n.fX;
            float by = oy;
            float bw = option_w;
            float bh = option_h - 2;
            ss << "<rect class=\"shell\" x=\"" << bx << "\" y=\"" << by << "\" width=\"" << bw << "\" height=\"" << bh << "\" rx=\"2\" ry=\"2\" />\n";
            ss << "<text class=\"label\" x=\"" << (bx + 6) << "\" y=\"" << (by + bh*0.7f + 2) << "\">";
            svgEscape(opts[i].first, ss);
            ss << "</text>\n";
        }
        ss << "</g>\n";
    }

    if (!n.fTooltip.empty()) {
        ss << "<title>";
        svgEscape(n.fTooltip, ss);
        ss << "</title>\n";
    }

    ss << "</g>\n";
}

inline void svgGroup(std::ostream& ss, const RenderNode& node, const SVGOptions& opt);

inline void svgTabs(std::ostream& ss, const RenderNode& node, const SVGOptions& opt)
{
    if (node.fHidden) {
        return;
    }

    // Tab headers as a simple horizontal list for now
    float tab_x = node.fX;
    float tab_y = node.fY;
    float tab_h = 20.f;
    float tab_w = node.fWidth / std::max<size_t>(1, node.fTabs.size());

    ss << "<g class=\"tab-headers\" transform=\"translate(" << tab_x << "," << tab_y << ")\">\n";
    for (size_t i = 0; i < node.fTabs.size(); ++i) {
        ss << "<g class=\"tab-header\" data-tab=\"" << i << "\">";
        ss << "<rect x=\"" << (i * tab_w) << "\" y=\"0\" width=\"" << tab_w << "\" height=\"" << tab_h << "\"/>\n";
        ss << "<text x=\"" << (i * tab_w + 4) << "\" y=\"" << (tab_h * 0.7f) << "\">";
        svgEscape(node.fTabs[i].fLabel, ss);
        ss << "</text></g>\n";
    }
    ss << "</g>\n";

    // Tab content stacked; visibility to be controlled by JS
    ss << "<g class=\"tab-contents\">\n";
    for (size_t i = 0; i < node.fTabs.size(); ++i) {
        ss << "<g class=\"tab-content\" data-tab=\"" << i << "\">\n";
        svgGroup(ss, node.fTabs[i], opt);
        ss << "</g>\n";
    }
    ss << "</g>\n";
}

inline void svgGroup(std::ostream& ss, const RenderNode& node, const SVGOptions& opt)
{
    if (node.fHidden) {
        return;
    }
    ss << "<g class=\"group\" data-type=\"";
    switch (node.fType) {
        case RenderNodeType::kHGroup: ss << "hgroup"; break;
        case RenderNodeType::kVGroup: ss << "vgroup"; break;
        case RenderNodeType::kTGroup: ss << "tgroup"; break;
        default: ss << "group"; break;
    }
    ss << "\" transform=\"translate(" << node.fX << "," << node.fY << ")\">\n";

    if (opt.fDebugOutlines) {
        ss << "<rect class=\"debug-group\" x=\"0\" y=\"0\" width=\"" << node.fWidth
           << "\" height=\"" << node.fHeight << "\" fill=\"none\" stroke=\"magenta\" stroke-dasharray=\"4 2\"/>\n";
    }

    if (node.fType == RenderNodeType::kTGroup) {
        svgTabs(ss, node, opt);
    } else {
        for (const auto& child : node.fChildren) {
            switch (child.fType) {
                case RenderNodeType::kHGroup:
                case RenderNodeType::kVGroup:
                case RenderNodeType::kTGroup:
                    svgGroup(ss, child, opt);
                    break;
                case RenderNodeType::kButton:
                    svgRect(ss, child, "button");
                    break;
                case RenderNodeType::kCheckButton:
                    svgRect(ss, child, "checkbutton");
                    break;
                case RenderNodeType::kHSlider:
                    if (child.fStyle == "knob") {
                        svgKnob(ss, child, "knob");
                    } else if (child.fStyle == "radio") {
                        svgRadioMenu(ss, child, "radio", true);
                    } else if (child.fStyle == "menu") {
                        svgRadioMenu(ss, child, "menu", false);
                    } else {
                        svgSlider(ss, child, "hslider", false);
                    }
                    break;
                case RenderNodeType::kVSlider:
                    if (child.fStyle == "knob") {
                        svgKnob(ss, child, "knob");
                    } else if (child.fStyle == "radio") {
                        svgRadioMenu(ss, child, "radio", true);
                    } else if (child.fStyle == "menu") {
                        svgRadioMenu(ss, child, "menu", false);
                    } else {
                        svgSlider(ss, child, "vslider", true);
                    }
                    break;
                case RenderNodeType::kNumEntry:
                    svgRect(ss, child, "numentry");
                    break;
                case RenderNodeType::kHBargraph:
                    svgBargraph(ss, child, "hbargraph", false);
                    break;
                case RenderNodeType::kVBargraph:
                    svgBargraph(ss, child, "vbargraph", true);
                    break;
                case RenderNodeType::kUnknown:
                    if (child.fStyle == "radio") {
                        svgRadioMenu(ss, child, "radio", true);
                    } else if (child.fStyle == "menu") {
                        svgRadioMenu(ss, child, "menu", false);
                    } else {
                        svgRect(ss, child, "unknown");
                    }
                    break;
                default:
                    svgRect(ss, child, "unknown");
                    break;
            }
        }
    }

    ss << "</g>\n";
}

inline std::string renderSVG(const RenderNode& root, const SVGOptions& opt)
{
    std::ostringstream ss;
    float w = (opt.fWidth > 0.f) ? opt.fWidth : root.fWidth;
    float h = (opt.fHeight > 0.f) ? opt.fHeight : root.fHeight;

    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << w << "\" height=\"" << h
       << "\" viewBox=\"0 0 " << w << " " << h << "\"";
    ss << ">\n";

    // Shared gradients and filters
    ss << "<defs>\n";
    ss << "  <linearGradient id=\"track-grad\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n";
    ss << "    <stop offset=\"0%\" stop-color=\"#dfe5ff\"/>\n";
    ss << "    <stop offset=\"100%\" stop-color=\"#c8d4ff\"/>\n";
    ss << "  </linearGradient>\n";
    ss << "  <linearGradient id=\"bar-fill-grad\" x1=\"0%\" y1=\"0%\" x2=\"0%\" y2=\"100%\">\n";
    ss << "    <stop offset=\"0%\" stop-color=\"#5ac8fa\"/>\n";
    ss << "    <stop offset=\"100%\" stop-color=\"#2e9ad3\"/>\n";
    ss << "  </linearGradient>\n";
    ss << "  <radialGradient id=\"knob-face\" cx=\"50%\" cy=\"50%\" r=\"70%\">\n";
    ss << "    <stop offset=\"0%\" stop-color=\"#f9fbff\"/>\n";
    ss << "    <stop offset=\"100%\" stop-color=\"#dfe7f7\"/>\n";
    ss << "  </radialGradient>\n";
    ss << "  <filter id=\"soft-shadow\" x=\"-20%\" y=\"-20%\" width=\"140%\" height=\"140%\">\n";
    ss << "    <feGaussianBlur in=\"SourceAlpha\" stdDeviation=\"2\" result=\"blur\"/>\n";
    ss << "    <feOffset in=\"blur\" dx=\"0\" dy=\"1\" result=\"offset\"/>\n";
    ss << "    <feMerge><feMergeNode in=\"offset\"/><feMergeNode in=\"SourceGraphic\"/></feMerge>\n";
    ss << "  </filter>\n";
    ss << "</defs>\n";

    // Style block
    ss << "<style><![CDATA[\n";
    ss << ":root {\n";
    ss << "  --bg: #f4f7fb;\n";
    ss << "  --panel: #ffffff;\n";
    ss << "  --stroke: #1f2a44;\n";
    ss << "  --primary: #4a7cff;\n";
    ss << "  --accent: #5ac8fa;\n";
    ss << "  --muted: #d7deea;\n";
    ss << "  --button-bg: #f1f4fb;\n";
    ss << "  --check-on: #d2f0e1;\n";
    ss << "  --text: #1f2335;\n";
    ss << "}\n";
    ss << "svg { font-family: 'Inter', 'Helvetica Neue', Arial, sans-serif; background: linear-gradient(180deg, #f7f9ff 0%, #eef2fb 100%); color: var(--text); }\n";
    ss << ".group { }\n";
    ss << ".button { fill: var(--button-bg); stroke: var(--muted); rx: 6; ry: 6; filter: url(#soft-shadow); transition: transform 80ms ease, filter 80ms ease; }\n";
    ss << ".button:hover { transform: translateY(-1px); }\n";
    ss << ".button:active { filter: none; transform: translateY(0px); }\n";
    ss << ".checkbutton { fill: var(--button-bg); stroke: var(--muted); rx: 6; ry: 6; filter: url(#soft-shadow); }\n";
    ss << ".checkbutton .mark { stroke: var(--stroke); stroke-width: 2; visibility: hidden; }\n";
    ss << ".checkbutton.checked { fill: var(--check-on); stroke: #2a7; }\n";
    ss << ".checkbutton.checked .mark { visibility: visible; }\n";
    ss << ".hslider .track, .vslider .track { fill: url(#track-grad); stroke: #c4cee2; rx: 6; ry: 6; filter: url(#soft-shadow); }\n";
    ss << ".hslider .handle, .vslider .handle { fill: #4a7cff; stroke: #223; rx: 5; ry: 5; transition: transform 80ms ease; }\n";
    ss << ".hslider .handle:hover, .vslider .handle:hover { transform: scale(1.05); }\n";
    ss << ".numentry { fill: #fffbe6; stroke: #777; rx: 3; ry: 3; }\n";
    ss << ".hbargraph .bg, .vbargraph .bg { fill: #f2f2f2; stroke: #888; rx: 2; ry: 2; stroke-dasharray: 4 4; }\n";
    ss << ".hbargraph .fill, .vbargraph .fill { fill: url(#bar-fill-grad); stroke: none; rx: 2; ry: 2; }\n";
    ss << ".knob .dial { fill: url(#knob-face); stroke: #334; filter: url(#soft-shadow); }\n";
    ss << ".knob .needle { stroke: #223; stroke-width: 2.5; stroke-linecap: round; }\n";
    ss << ".style-knob { fill: #d9ecff; }\n";
    ss << ".style-led { fill: #d7ffd7; }\n";
    ss << ".style-numerical { fill: #fff1d6; }\n";
    ss << ".style-radio { fill: #e7e7ff; }\n";
    ss << ".style-menu { fill: #e7f7ff; }\n";
    ss << ".radio .shell, .menu .shell { fill: #f7f7f7; stroke: #777; }\n";
    ss << ".radio .dot { fill: var(--primary); visibility: hidden; }\n";
    ss << ".radio .option.selected .dot { visibility: visible; }\n";
    ss << ".menu .option { cursor: pointer; }\n";
    ss << ".menu .option.selected .shell { fill: #dce8ff; stroke: var(--primary); }\n";
    ss << ".tab-header rect { fill: #ececec; stroke: #777; }\n";
    ss << ".tab-header text { font-size: 12px; fill: var(--text); }\n";
    ss << ".tab-content { display: none; }\n";
    ss << ".tab-content.active { display: block; }\n";
    if (!opt.fThemeCSS.empty()) {
        ss << opt.fThemeCSS << "\n";
    }
    ss << "]]></style>\n";

    svgGroup(ss, root, opt);

    if (!opt.fScript.empty()) {
        ss << "<script><![CDATA[\n" << opt.fScript << "\n]]></script>\n";
    }

    ss << "</svg>\n";
    return ss.str();
}

inline std::string defaultSVGScript()
{
    return R"JS(
    (function() {
      function selectAll(sel) { return Array.prototype.slice.call(document.querySelectorAll(sel)); }
      function clamp01(v) { return Math.min(1, Math.max(0, v)); }
      var host = null;

      function setActiveTab(tabContainer, index) {
        selectAll('.tab-content', tabContainer).forEach(function(el, i) {
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

      function setHandlePosition(sl, t, vertical) {
        var track = sl.querySelector('.track');
        var handle = sl.querySelector('.handle');
        if (!track || !handle) return;
        var tx = parseFloat(track.getAttribute('x')) || 0;
        var ty = parseFloat(track.getAttribute('y')) || 0;
        var tw = parseFloat(track.getAttribute('width')) || 0;
        var th = parseFloat(track.getAttribute('height')) || 0;
        var hw = parseFloat(handle.getAttribute('width')) || 0;
        var hh = parseFloat(handle.getAttribute('height')) || 0;

        if (vertical) {
          var y = ty + (1 - t) * (th - hh);
          handle.setAttribute('y', y);
          handle.setAttribute('x', tx);
        } else {
          var x = tx + t * (tw - hw);
          handle.setAttribute('x', x);
          handle.setAttribute('y', ty);
        }
        sl.setAttribute('data-value', t);
      }

      function setKnobRotation(knob, t) {
        var needle = knob.querySelector('.needle');
        var dial = knob.querySelector('.dial');
        if (!needle || !dial) return;
        var cx = parseFloat(dial.getAttribute('cx')) || 0;
        var cy = parseFloat(dial.getAttribute('cy')) || 0;
        var r = parseFloat(dial.getAttribute('r')) || 0;
        var ang = (-135 + 270 * t) * Math.PI / 180;
        var nx = cx + Math.cos(ang) * r * 0.65;
        var ny = cy + Math.sin(ang) * r * 0.65;
        needle.setAttribute('x2', nx);
        needle.setAttribute('y2', ny);
        knob.setAttribute('data-value', t);
      }

      function handlePointerKnob(knob) {
        function onMove(ev) {
          if (!down) return;
          ev.preventDefault();
          var dial = knob.querySelector('.dial');
          if (!dial) return;
          var cx = parseFloat(dial.getAttribute('cx')) || 0;
          var cy = parseFloat(dial.getAttribute('cy')) || 0;
          var rect = dial.getBoundingClientRect();
          var px = rect.left + rect.width / 2;
          var py = rect.top + rect.height / 2;
          var ang = Math.atan2(ev.clientY - py, ev.clientX - px); // -pi..pi
          var deg = ang * 180 / Math.PI;
          // Map -135..135 to 0..1
          var t = (deg + 135) / 270;
          t = Math.min(1, Math.max(0, t));
          var path = knob.getAttribute('data-path');
          var scale = knob.getAttribute('data-scale') || 'lin';
          var hv = applyScale(t, scale);
          if (host && host.setParamValue) host.setParamValue(path, hv);
          setKnobRotation(knob, t);
        }
        var down = false;
        knob.addEventListener('pointerdown', function(ev) { down = true; knob.setPointerCapture(ev.pointerId); onMove(ev); });
        knob.addEventListener('pointermove', onMove);
        knob.addEventListener('pointerup', function(ev) { down = false; knob.releasePointerCapture(ev.pointerId); });
        knob.addEventListener('pointercancel', function(ev) { down = false; knob.releasePointerCapture(ev.pointerId); });
      }

      function setBarFill(bg, t, vertical) {
        var fill = bg.querySelector('.fill');
        var bgRect = bg.querySelector('.bg');
        if (!fill || !bgRect) return;
        var bx = parseFloat(bgRect.getAttribute('x')) || 0;
        var by = parseFloat(bgRect.getAttribute('y')) || 0;
        var bw = parseFloat(bgRect.getAttribute('width')) || 0;
        var bh = parseFloat(bgRect.getAttribute('height')) || 0;
        if (vertical) {
          var h = t * bh;
          fill.setAttribute('x', bx);
          fill.setAttribute('width', bw);
          fill.setAttribute('height', h);
          fill.setAttribute('y', by + (bh - h));
        } else {
          var w = t * bw;
          fill.setAttribute('x', bx);
          fill.setAttribute('y', by);
          fill.setAttribute('width', w);
          fill.setAttribute('height', bh);
        }
        bg.setAttribute('data-value', t);
      }

      function updateVisual(path, v) {
        selectAll('[data-path]').forEach(function(el) {
          if (el.getAttribute('data-path') !== path) return;
          var scale = el.getAttribute('data-scale') || 'lin';
          var t = applyScaleInverse(clamp01(v), scale);
          if (el.classList.contains('hslider') || el.classList.contains('vslider')) {
            setHandlePosition(el, t, el.classList.contains('vslider'));
          } else if (el.classList.contains('hbargraph') || el.classList.contains('vbargraph')) {
            setBarFill(el, t, el.classList.contains('vbargraph'));
          } else if (el.classList.contains('checkbutton')) {
            if (v > 0) el.classList.add('checked'); else el.classList.remove('checked');
          } else if (el.classList.contains('knob')) {
            setKnobRotation(el, t);
          } else if (el.classList.contains('radio') || el.classList.contains('menu')) {
            selectOption(el, Math.round(v));
          }
        });
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

      // Wire sliders (simple linear mapping)
      selectAll('.hslider').forEach(function(sl) {
        handlePointer(sl, function(ev) {
          var rect = sl.getBoundingClientRect();
          var t = Math.min(1, Math.max(0, (ev.clientX - rect.left) / rect.width));
          var path = sl.getAttribute('data-path');
          var scale = sl.getAttribute('data-scale') || 'lin';
          var hv = applyScale(t, scale);
          if (host && host.setParamValue) host.setParamValue(path, hv);
          setHandlePosition(sl, t, false);
        });
        setHandlePosition(sl, parseFloat(sl.getAttribute('data-value')) || 0, false);
      });
      selectAll('.vslider').forEach(function(sl) {
        handlePointer(sl, function(ev) {
          var rect = sl.getBoundingClientRect();
          var t = 1 - Math.min(1, Math.max(0, (ev.clientY - rect.top) / rect.height));
          var path = sl.getAttribute('data-path');
          var scale = sl.getAttribute('data-scale') || 'lin';
          var hv = applyScale(t, scale);
          if (host && host.setParamValue) host.setParamValue(path, hv);
          setHandlePosition(sl, t, true);
        });
        setHandlePosition(sl, parseFloat(sl.getAttribute('data-value')) || 0, true);
      });

      // Knobs (style=knob sliders)
      selectAll('.knob').forEach(function(knob) {
        handlePointerKnob(knob);
        setKnobRotation(knob, parseFloat(knob.getAttribute('data-value')) || 0);
      });

      // Buttons / checkbuttons toggle
      selectAll('.button, .checkbutton').forEach(function(btn) {
        btn.addEventListener('click', function() {
          var path = btn.getAttribute('data-path');
          if (host && host.setParamValue) host.setParamValue(path, 1);
          btn.classList.add('active');
          setTimeout(function() { btn.classList.remove('active'); }, 100);
        });
      });

      // Checkbox state
      selectAll('.checkbutton').forEach(function(chk) {
        chk.addEventListener('click', function() {
          chk.classList.toggle('checked');
        });
      });

      // Radio/Menu options
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
 * Generate an SVG string for a given DSP.
 * @param dsp           Pointer to a Faust DSP
 * @param target_width  Target SVG width (if <=0, use intrinsic)
 * @param target_height Target SVG height (if <=0, use intrinsic)
 * @param debugOutlines Draw debug rectangles around groups if true
 */
template <typename DSP>
inline std::string toSVG(DSP* dsp,
                         float target_width = -1.f,
                         float target_height = -1.f,
                         bool debugOutlines = false)
{
    auto resolved = buildResolvedLayout(dsp, target_width, target_height, 0.f, 0.f);
    RenderNode root = buildRenderTree(resolved.fUI);
    
    SVGOptions opt;
    opt.fWidth = target_width;
    opt.fHeight = target_height;
    opt.fDebugOutlines = debugOutlines;
    opt.fThemeCSS = "";  // Allow caller to override later
    opt.fScript = defaultSVGScript();
    
    return renderSVG(root, opt);
}

#endif // FAUST_SVGEXPORT_H
/**************************  END  SVGExport.h **************************/
