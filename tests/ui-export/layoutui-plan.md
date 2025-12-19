# Plan: LayoutUI → SVG UI Generator

## Goal
Create an automatic SVG (with JS/CSS) representation of a Faust DSP UI by converting the `LayoutUI` hierarchy (HGroup/VGroup/TGroup + widgets) produced by `buildUserInterface` into positioned SVG elements with interactive controls wired to the DSP parameter API.

## Inputs and references
- Layout model: `architecture/faust/gui/LayoutUI.h` (BaseUIItem/UIItem/Group/HGroup/VGroup; add TGroup).
- Path/metadata: `PathBuilder` for stable IDs; `MetaDataUI` for tooltip/unit/style/radio/log/exp/etc.
- DSP API: `buildUserInterface(UI*)`, `setParamValue/getParamValue` (or equivalent control interface provided by the hosting architecture).
- Design notes: “Architecture Files - Faust Documentation.pdf” (widgets layout and metadata section).

## Deliverable
An API (e.g., `std::string toSVG(dsp*, int width, int height)`) that returns a complete SVG string containing:
- Positioned widgets (buttons, sliders, num entries, bargraphs, check buttons) laid out per H/V/Tab groups.
- Visual styling via CSS.
- Interactivity via JS (pointer/touch/keyboard) hooked to DSP control getters/setters; bargraphs update from DSP values.

## Work plan
0) **Stabilize LayoutUI**
   - Add a deterministic root group in the constructor so `addItem/addGroup` never dereference null.
   - Harden layout math: guard divide-by-zero in `setSize`, clarify/implement border handling, and optionally assert on malformed `closeBox` use.
   - Add `TGroup` support and wire `openTabBox` to it (instead of being a no-op); keep path building intact.
   - Verify path uniqueness where labels may repeat (tabs).

1) **Extend layout model**
   - Add `TGroup` subclass of `Group` (tab container), store child tabs (label + content group).
   - Wire `openTabBox` to create/use `TGroup`; ensure label stack/push/pop is preserved.
   - Ensure `LayoutUI` builds a deterministic root group (e.g., implicit vertical root) before `buildUserInterface`.
   - Preserve and expose metadata and path → item map for later SVG ID assignment.

2) **Layout resolution pass**
   - After `dsp->buildUserInterface(layout)`, compute intrinsic size (`getWidth/Height`).
   - Apply target size (`setSize(target_w, target_h)`) and position (`setPos(0, 0)`) so every node has absolute x/y/width/height.
   - Optionally respect per-item borders/padding if present; keep room for future spacing tweaks.

3) **Scene graph for rendering**
   - Walk the `LayoutUI` tree to build a render model: node type (H/V/T group or widget), label, path ID, abs position/size, metadata, children, tab info.
   - Flatten tabs as separate child lists per tab and keep header data (order + labels).

4) **SVG generation**
   - Emit root `<svg>` with viewBox/size.
   - For each group, emit a `<g>` with `transform="translate(x,y)"`; include optional outlines for debugging.
   - For tabs, render tab headers and per-tab content groups with visibility toggles.
   - For widgets, pick shapes per type (e.g., rect + handle for sliders, circle for knob style, checkbox, bar fills).
   - Generate stable element IDs from paths; add `data-*` attributes for metadata (unit, style, scale, radio, tooltip).

5) **Interactivity layer**
   - JS module embedded in the SVG: helpers for event binding, value normalization, and redraw.
   - Hook to DSP control API: `setParamValue(path, v)`, `getParamValue(path)`; propagate DSP-to-UI updates (e.g., via a polling loop or callbacks the host can call).
   - Implement pointer/touch/keyboard handling per widget type; update visuals (handles, rotation, fills) and tooltips.
   - Tab switching logic to toggle visibility and ARIA-friendly focus handling.

6) **Styling**
   - Define CSS variables for colors/spacing/typography; provide a default theme and allow overrides.
   - Honor metadata: `style=knob/led/numerical`, `hidden`, `unit`, `scale=log/exp`, `radio{...}` (for rendering radio groups), `tooltip`.
   - Make sizing responsive to the assigned target size while respecting the computed layout ratios.

7) **Packaging API**
   - Provide a function (e.g., `std::string toSVG(dsp*, int w, int h)`) that:
     1. Instantiates `LayoutUI`, calls `buildUserInterface`.
     2. Runs layout sizing/positioning.
     3. Builds the render model.
     4. Produces the SVG string (or writes to a file on request).
   - Optionally expose a CLI flag or test harness that outputs the SVG for a given DSP.

8) **Validation**
   - Generate SVGs for representative DSPs with mixed H/V/T nesting; visually inspect stacking and sizing.
   - Check ID determinism (paths must match PathBuilder output).
   - Exercise interactions: buttons/sliders/num entries/checkboxes/bargraphs; verify DSP value updates in both directions.
   - Add lightweight automated checks (e.g., parse SVG for expected elements, simulate a few JS handlers in a headless test if feasible).

9) **Visual polish**
   - Map metadata styles to richer shapes: knob dial/handle, checkbox state, radio/menu options, slider handle, bargraph fill and ticks.
   - Add CSS variables/theme hooks and responsive sizing tweaks.
   - Render tooltips/units where useful (title attributes or overlay).

10) **Interactivity polish**
    - Extend JS to animate handles/knob rotation and bargraph fills based on values.
    - Support radio/menu selection and checkbox state, with host API shims for `setParamValue/getParamValue`.
    - Ensure metadata-driven behavior (log/exp scale) is reflected in value normalization.

11) **Metadata correctness**
    - Propagate real widget zones into the render model so tooltip/unit/style/hidden/scale are accurate (not dummy placeholders).
    - Handle hidden widgets/groups consistently in traversal and SVG output.

12) **Validation harness**
    - Automate build/run of `tests/ui-export/generate_ui.cpp` and `check_svg.py` as a sanity target.
    - Optionally add a golden SVG or DOM probe to catch regressions; expose a CLI flag to emit SVG for any DSP.

## Prompts to execute per step
0) Stabilize LayoutUI  
   - Inspect `LayoutUI.h` for root creation, `openTabBox`, border use, and setSize guards.  
   - Patch `LayoutUI.h` to add root init, divide-by-zero guards, optional close assertions, and `TGroup` wiring in `openTabBox`.

1) Extend layout model  
   - Define `TGroup` structure and tab bookkeeping; ensure label stack behavior matches `PathBuilder`.  
   - Confirm path uniqueness with repeated labels (tabs) and adjust if needed.

2) Layout resolution pass  
   - Draft helper to run `buildUserInterface`, then `setSize`/`setPos`; validate intrinsic size is non-zero and guarded.

3) Scene graph for rendering  
   - Write traversal that produces a render model (type, path ID, abs geometry, metadata, children, tab sets).

4) SVG generation  
   - Sketch SVG emitter functions per node type (groups, tabs, widgets) and ID scheme from paths.  
   - Decide on default shapes per widget and optional debug outlines.

5) Interactivity layer  
   - Plan JS API surface (value normalization, event handling, tab toggles) and DSP binding hooks.

6) Styling  
   - Choose CSS variable set and map metadata (style/unit/log/exp/radio/tooltip/hidden) to classes.

7) Packaging API  
   - Specify `toSVG(dsp*, w, h)` flow and (optional) CLI/test harness invocation.

8) Validation  
   - List sample DSPs to export; script ID checks; outline manual/automated interaction checks.

9) Visual polish  
   - Design richer widget shapes (knob/handle/checkbox/bar fill) and CSS variable palette; wire metadata styles/units/tooltips into SVG output.

10) Interactivity polish  
   - Extend JS to animate handles/knob rotation/bar fills; implement radio/menu/checkbox states and host API shim.

11) Metadata correctness  
   - Propagate real widget zones into render model; ensure hidden/style/scale/unit/tooltip are accurate; enforce hiding in traversal/SVG.

12) Validation harness  
   - Build/run `tests/ui-export/generate_ui.cpp` and `check_svg.py`; add optional golden/DOM probe tests and a CLI flag for SVG/HTML export.

## Usage notes
- Build and check harness: `make -C tests/ui-export check` (generates SVG/HTML variants and runs `check_svg.py`/`check_html.py`).
- Library API: call `toSVG(dsp*, width, height, debug)` (in `architecture/faust/gui/SVGGenerator.h`) to get an SVG string with inline CSS/JS.
- SVG content embeds default styles and interactivity; host integration can expose `faustHost.setParamValue/getParamValue` for live control.

## Planned test additions (generate_ui.cpp)
- Add explicit vertical-only layout covering vslider, vbargraph, and menu metadata.
- Add horizontal-only layout covering hslider, hbargraph, radio metadata, and checkbutton/button combos.
- Add nested tabs (tab-in-tab) to stress PathBuilder and render traversal.
- Include metadata variants: scale=log/exp, style=knob/led/numerical/radio/menu, tooltip/unit/hidden on different widgets.
- Verify composite group sizes by emitting differing target sizes per layout (e.g., tall vs wide).
- Extend check script expectations per new generated SVGs (one file per layout type).

## Visual polish ideas
- Establish a cohesive theme: define CSS variables for background gradient, primary/accent colors, subtle shadows, and rounded corners; use consistent typography (e.g., a modern sans with tighter letter spacing).
- Upgrade sliders: draw actual tracks and handles with gradients, inset shadows, and value indicators; add tick marks and numeric ghost labels for range context.
- Upgrade knobs: render a face with ticks/labels, a beveled rim, and a smoother needle; animate rotation easing; show a center cap and hover glow.
- Buttons/checkboxes: add pressed/hover states, subtle drop shadows, and checkmarks with smoother strokes; radios/menus with highlighted selection backgrounds and icons.
- Bargraphs: use background gridlines, gradient fills that respond to value, optional peak hold markers.
- Tabs: styled headers with active underline/indicator and rounded corners; animate tab transitions (opacity/slide).
- Tooltips: styled bubbles with subtle shadow and readable padding; show units alongside values.
- Responsiveness: adjust paddings, handle sizes, and font sizes based on target viewport; ensure touch-friendly hit areas.

## HTML + CSS export plan
- Reuse layout: leverage `LayoutUI`, `LayoutResolver`, and `LayoutRenderModel` to generate a DOM tree instead of SVG; map groups to `<div>` with absolute positioning.
- HTML structure: wrap the UI in a container `<div class="faust-ui">`; each node becomes a `<div>` with `data-path`, type classes (`hgroup`, `vgroup`, `tgroup`, `button`, `slider`, etc.), and children matching hierarchy.
- Tabs: render tab headers and content panels with CSS-driven visibility; attach JS handlers similar to the SVG interactivity.
- Controls: render sliders/knobs/buttons/checkboxes/radios/menus/num-entries/bargraphs as HTML elements with appropriate styling hooks; reuse metadata via `data-*` attributes (unit/style/scale/radio/menu/tooltip/hidden).
- Styling: provide a CSS stylesheet (reuse theme variables from SVG) to style tracks, handles, knobs, bargraphs, tabs, buttons; ensure responsive sizing using computed layout dimensions and relative units.
- Interactivity: reuse/port `SVGInteractivity` logic to DOM handlers; bind pointer/touch/keyboard events; map log/exp scales; support host API via `faustHost.setParamValue/getParamValue`.
- Export API: add `toHTML(dsp*, width, height)` returning an HTML string with inline or linked CSS/JS; mirror `toSVG` structure.
- Tests: extend harness to emit HTML files for simple/medium/complex layouts and add a check script to validate class presence and data attributes.
