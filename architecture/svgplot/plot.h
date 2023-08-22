/** Signalsmith's Basic C++ Plots - https://signalsmith-audio.co.uk/code/plot/
@copyright Licensed as 0BSD.  If you need anything else, get in touch. */

#ifndef SIGNALSMITH_PLOT_H
#define SIGNALSMITH_PLOT_H

#include <fstream>
#include <memory>
#include <functional>
#include <vector>
#include <cmath>
#include <sstream>

namespace signalsmith { namespace plot {

/**	@defgroup Plots Plots
	@brief Basic C++ plotting
	
	To use, set up a `Figure` or `Plot2D`, add elements to it, and then write with `.write("output.svg")`.
	\image html default-2d.svg An example plot
	
	Elements are drawn hierarchically, but generally in reverse order, so you should add your most important elements first.

	Elements can have a "style index" which simultaneously loops through colour/dash/hatch sequences, for increased greyscale/colourblind support.
 		\image html style-sequence.svg

	@{
	@file
**/

static double estimateUtf8Width(const char *utf8Str);

/** Plotting style, used for both layout and SVG rendering.
	Colour/dash/hatch styles are defined as CSS classes, assigned to elements based on their integer style index.  CSS is written inline in the SVG, and can be extended/overridden with `.cssPrefix`/`.cssSuffix`.
 		\image html custom-2d.svg
	It generates CSS classes from `.colours` (`svg-plot-sN`/`svg-plot-fN`/`svg-plot-tN` for stroke/fill/text), `.dashes` (`svg-plot-dN`) and `.hatches` (`svg-plot-hN`), where `N` is the index - e.g. there are six colours by default, generating `svg-plot-s0` to `svg-plot-s5`.
*/
class PlotStyle {
public:
	double padding = 10;
	double lineWidth = 0.5, precision = 100; //1.25 100
	double markerSize = 3.25;
	double tickH = 4, tickV = 4;
	// Text
	double labelSize = 6, valueSize = 5; //12 10
	double fontAspectRatio = 1; ///< scales size estimates, if using a particularly wide font
	double textPadding = 5, lineHeight = 1.2;
	// Fills
	double fillOpacity = 0.3;
	double hatchWidth = 1, hatchSpacing = 3;
	double animation = 2; ///< Animation duration

	std::string scriptHref = "", scriptSrc = "";
	std::string cssPrefix = "", cssSuffix = "";
    std::vector<std::string> colours = {"#3f48c2", "#db4b3d", "#2bdb72", "#ffeb33", "#448de7", "#dc435b","#a7f547","#f58931","#6275ba","#a63d57","#ffab7b","#ff6c7a","#36354d","#a3c0e6","#222533"};
	//std::vector<std::string> colours = {"#0073E6", "#CC0000", "#00B300", "#806600", "#E69900", "#CC00CC"};
	std::vector<std::vector<double>> dashes = {{}, {1.2, 1.2}, {2.8, 1.6}, {5, 4}, {4, 1, 1, 1, 1, 1}, {10, 3}, {4, 2, 1, 2}};
	/// SVG literals for the markers.  These should be centered on `(0, 0)` and look correct next to a filled circle of radius 1.  They will be given both a stroke and fill-class, so they should specify `fill="none"`/`stroke="none"` if fill/stroke is not wanted.
	std::vector<std::string> markers = {
		"<circle cx=\"0\" cy=\"0\" r=\"1\" stroke=\"none\"/>",
		"<path d=\"M0 0.9 -0.9 0 0 -0.9 0.9 0Z\" fill=\"#FFFA\" stroke-linejoin=\"miter\" stroke-width=\"0.6\"/>",
		"<path fill=\"none\" d=\"M0 -1.2 0 1.2 M -1.2 0 1.2 0\" stroke-width=\"0.7\"/>",
		"<circle cx=\"0\" cy=\"0\" fill=\"#FFFA\" r=\"0.8\" stroke-width=\"0.65\"/>",
		"<path stroke=\"none\" d=\"M0 -1.25 1.25 0.9 -1.25 0.9Z\"/>",
		// spares:
		//"<path fill=\"none\" d=\"M-0.9 -0.9 0.9 0.9 M -0.9 0.9 0.9 -0.9\" stroke-width=\"0.65\"/>",
		//"<rect x=\"-0.9\" y=\"-0.9\" width=\"1.8\" height=\"1.8\" stroke=\"none\"/>",
	};

	struct Hatch {
		std::vector<double> angles;
		double lineScale = 1, spaceScale=1;
		Hatch() {}
		Hatch(double angle) : angles({angle}) {}
		Hatch(std::vector<double> angles, double scale=1) : angles(angles), lineScale(scale), spaceScale(scale) {}
		Hatch(std::vector<double> angles, double lineScale, double spaceScale) : angles(angles), lineScale(lineScale), spaceScale(spaceScale) {}
	};
	std::vector<Hatch> hatches = {{}, {-50}, {{30}, 0.9, 0.8}, {{8, 93}, 0.7, 1}};

	struct Counter {
		int colour, dash, hatch, marker;
		Counter(int colour, int dash, int hatch, int marker) : colour(colour), dash(dash), hatch(hatch), marker(marker) {}
		Counter(int index=0) : colour(index), dash(index), hatch(index), marker(index) {}

		/// Increment the counter, and return the previous value
		Counter bump() {
			Counter result = *this;
			++colour;
			++dash;
			++hatch;
			++marker;
			return result;
		}
		Counter withColour(int index) {
			return Counter(index, dash, hatch, marker);
		}
		Counter withDash(int index) {
			return Counter(colour, index, hatch, marker);
		}
		Counter withHatch(int index) {
			return Counter(colour, dash, index, marker);
		}
		Counter withMarker(int index) {
			return Counter(colour, dash, hatch, index);
		}
	};
	std::string strokeClass(const Counter &counter) const {
		if (counter.colour < 0 || colours.size() == 0) return "svg-plot-s";
		return "svg-plot-s" + std::to_string(counter.colour%(int)colours.size());
	}
	std::string fillClass(const Counter &counter) const {
		if (counter.colour < 0 || colours.size() == 0) return "svg-plot-f";
		return "svg-plot-f" + std::to_string(counter.colour%(int)colours.size());
	}
	std::string textClass(const Counter &counter) const {
		if (counter.colour < 0 || colours.size() == 0) return "svg-plot-t";
		return "svg-plot-t" + std::to_string(counter.colour%(int)colours.size());
	}
	std::string dashClass(const Counter &counter) const {
		if (counter.dash < 0 || dashes.size() == 0) return "svg-plot-d";
		return "svg-plot-d" + std::to_string(counter.dash%(int)dashes.size());
	}
	std::string hatchClass(const Counter &counter) const {
		if (counter.hatch < 0 || hatches.size() == 0) return "svg-plot-h";
		return "svg-plot-h" + std::to_string(counter.hatch%(int)hatches.size());
	}
	std::string markerId(const Counter &counter) const {
		return "svg-plot-marker" + std::to_string(std::abs(counter.marker)%(int)markers.size());
	}
	const std::string & markerRaw(const Counter &counter) const {
		int index = std::abs(counter.marker)%(int)markers.size();
		return markers[index];
	}
	
	void css(std::ostream &o) const {
		o << cssPrefix;
		o << R"CSS(
			.svg-plot {
				stroke-linecap: butt;
				stroke-linejoin: round;
			}
			.svg-plot-bg {
				fill: none;
				stroke: none;
			}
			.svg-plot-axis {
				stroke: none;
				fill: #FFFFFFD9;
			}
			.svg-plot-legend {
				stroke: none;
				fill: #FFFFFFE4;
			}
			.svg-plot-line {
				stroke: blue;
				fill: none;
				stroke-width: )CSS" << lineWidth << R"CSS(px;
				stroke-linejoin: round;
			}
			.svg-plot-fill {
				stroke: none;
				opacity: )CSS" << fillOpacity << R"CSS(;
			}
			.svg-plot-major {
				stroke: #000;
				stroke-width: 1px;
				stroke-linecap: square;
				fill: none;
			}
			.svg-plot-minor {
				stroke: #0000004D;
				stroke-width: 0.5px;
				stroke-dasharray: 0.5 1.5;
				stroke-linecap: round;
				fill: none;
			}
			.svg-plot-tick {
				stroke: #000;
				fill: none;
				stroke-width: 1px;
				stroke-linecap: butt;
			}
			.svg-plot-value, .svg-plot-label {
				font-family: Arial,sans-serif;
				fill: #000;
				stroke: #FFFFFF48;
				stroke-width: 2.5px;
				paint-order: stroke fill;
				text-anchor: middle;
				dominant-baseline: central;
				alignment-baseline: baseline;
			}
			.svg-plot-label {
				font-size: )CSS" << labelSize << R"CSS(px;
			}
			.svg-plot-value {
				font-size: )CSS" << valueSize << R"CSS(px;
			}
			.svg-plot-hatch {
				stroke: #FFF;
				stroke-width: )CSS" << hatchWidth << R"CSS(px;
			}
			.svg-plot-marker {
				transform: scale()CSS" << markerSize << R"CSS();
			}
			.svg-plot-s {
				stroke: #000;
			}
			.svg-plot-f, .svg-plot-t {
				fill: #000;
			}
		)CSS";
		
		for (size_t i = 0; i < colours.size(); ++i) {
			o << ".svg-plot-s" << i << "{stroke:" << colours[i] << "}\n";
			o << ".svg-plot-f" << i << ",.svg-plot-t" << i << "{fill:" << colours[i] << "}\n";
		}
		for (size_t i = 0; i < dashes.size(); ++i) {
			auto &d = dashes[i];
			if (d.size() == 0) {
				o << ".svg-plot-d" << i << "{stroke-width:" << (0.9*lineWidth) << "px}\n";
			} else {
				o << ".svg-plot-d" << i << "{stroke-dasharray:";
				for (auto &v : d) o << " " << (v*lineWidth);
				o << "}\n";
			}
		}
		for (size_t i = 0; i < hatches.size(); ++i) {
			auto &h = hatches[i];
			if (h.angles.size()) {
				o << ".svg-plot-h" << i << "{mask:url(#svg-plot-hatch" << i << ")}\n";
			} else {
				// Compensate for the fact that it's not hatched
				o << ".svg-plot-h" << i << "{opacity:" << (fillOpacity*(hatchWidth/hatchSpacing)) << "}\n";
			}
		}
		for (size_t i = 0; i < hatches.size(); ++i) {
			auto &h = hatches[i];
			if (h.lineScale != 1) {
				o << "#svg-plot-hatch" << i << "-pattern{stroke-width:" << hatchWidth*h.lineScale << "px}\n";
			}
		}
		o << cssSuffix;
	}
};

struct Bounds {
	double left = 0, right = 0, top = 0, bottom = 0;
	bool set = false;
	Bounds() {}
	Bounds(double left, double right, double top, double bottom) : left(left), right(right), top(top), bottom(bottom), set(true) {}
	double width() const {
		return right - left;
	}
	double height() const {
		return bottom - top;
	}
	Bounds & expandTo(const Bounds &other) {
		left = std::min(left, other.left);
		top = std::min(top, other.top);
		right = std::max(right, other.right);
		bottom = std::max(bottom, other.bottom);
		return *this;
	}
	Bounds pad(double hPad, double vPad) {
		return {left - hPad, right + hPad, top - vPad, bottom + vPad};
	}
	Bounds pad(double padding) {
		return pad(padding, padding);
	}
};

struct Point2D {
	double x, y;
};

/// Wrapper for slightly more semantic code when writing SVGs
class SvgWriter {
	std::ostream &output;
	std::vector<Bounds> clipStack;
	long idCounter = 0;
	double precision, invPrecision;
public:
	SvgWriter(std::ostream &output, Bounds bounds, double precision) : output(output), clipStack({bounds}), precision(precision), invPrecision(1.0/precision) {}
	
	SvgWriter & raw() {
		return *this;
	}
	template<class First, class ...Args>
	SvgWriter & raw(First &&first, Args &&...args) {
		output << first;
		return raw(args...);
	}

	SvgWriter & write() {
		return *this;
	}
	template<class First, class ...Args>
	SvgWriter & write(First &&v, Args &&...args) {
		// Only strings get escaped
		return raw(v).write(args...);
	}
	template<class ...Args>
	SvgWriter & write(const char *str, Args &&...args) {
		while (*str) {
			if (*str == '<') {
				output << "&lt;";
			} else if (*str == '&') {
				output << "&amp;";
			} else if (*str == '"') {
				output << "&quot;";
			} else {
				output << (*str);
			}
			++str;
		}
		return write(args...);
	}
	template<class ...Args>
	SvgWriter & write(std::string str, Args &&...args) {
		return write(str.c_str(), args...);
	}
	
	template<class ...Args>
	SvgWriter & attr(const char *name, Args &&...args) {
		return raw(" ", name, "=\"").write(args...).raw("\"");
	}
	
	SvgWriter & pushClip(Bounds b, double dataCheckPadding) {
		clipStack.push_back(b.pad(dataCheckPadding));

		auto clipId = elementId("clip");
		tag("clipPath").attr("id", clipId);
		rect(b.left, b.top, b.width(), b.height());
		raw("</clipPath>");
		tag("g").attr("clip-path", "url(#", clipId, ")");
		return *this;
	}
	SvgWriter & popClip() {
		clipStack.resize(clipStack.size() - 1);
		return raw("</g>");
	}
	
	std::string elementId(std::string prefix) {
		return prefix + std::to_string(idCounter++);
	}
	
	/// XML tag helper, closing the tag when it's destroyed
	struct Tag {
		SvgWriter &writer;
		bool active = true;
		bool selfClose;

		Tag(SvgWriter &writer, bool selfClose=false) : writer(writer), selfClose(selfClose) {}
		// Move-construct only
		Tag(Tag &&other) : writer(other.writer), selfClose(other.selfClose) {
			other.active = false;
		}
		~Tag() {
			if (active) writer.raw(selfClose ? "/>" : ">");
		}

		template<class ...Args>
		Tag & attr(const char *name, Args &&...args) & {
			writer.attr(name, args...);
			return *this;
		}
		template<class ...Args>
		Tag && attr(const char *name, Args &&...args) && {
			writer.attr(name, args...);
			return std::move(*this);
		}
	};
	Tag tag(const char *name, bool selfClose=false) {
		raw("<", name);
		return Tag(*this, selfClose);
	}
	Tag line(double x1, double y1, double x2, double y2) {
		return tag("line", true).attr("x1", x1).attr("x2", x2).attr("y1", y1).attr("y2", y2);
	}
	Tag rect(double x, double y, double w, double h) {
		return tag("rect", true).attr("x", x).attr("y", y).attr("width", w).attr("height", h);
	}

	double round(double v) {
		return std::round(v*precision)*invPrecision;
	};

	bool animated = false;
	enum class PointState {start, outOfBounds, singlePoint, pendingLine};
	PointState pointState = PointState::start;
	char outOfBoundsMask = 0; // tracks which direction(s) we are out of bounds
	Point2D lastDrawn, prevPoint;
	double totalPendingError = 0;
	void startPath() {
		pointState = PointState::start;
		outOfBoundsMask = 0;
		prevPoint.x = prevPoint.y = -1e300;
		raw("M");
	}
	void endPath() {
		if (pointState == PointState::pendingLine) {
			raw(" ", round(prevPoint.x), " ", round(prevPoint.y));
		}
	}
	void addPoint(double x, double y, bool alwaysInclude=false) {
		if (std::isnan(x) || std::isnan(y)) return;
		auto clip = clipStack.back();
		/// Bitmask indicating which direction(s) the point is outside the bounds
		char mask = (clip.left > x)
			| (2*(clip.right < x))
			| (4*(clip.top > y))
			| (8*(clip.bottom < y));
		if (alwaysInclude) mask = 0;
		outOfBoundsMask &= mask;
		if (!outOfBoundsMask) {
			if (pointState == PointState::outOfBounds) {
				// Draw the most recent out-of-bounds point
				raw(" ", round(prevPoint.x), " ", round(prevPoint.y));
				lastDrawn = prevPoint;
				pointState = PointState::singlePoint;
			}
			if (pointState == PointState::singlePoint) {
				pointState = PointState::pendingLine;
				totalPendingError = 0;
			} else if (pointState == PointState::pendingLine) {
				// Approximate the pending point as being on the line from last-drawn point -> current
				double d1 = std::hypot(prevPoint.x - lastDrawn.x, prevPoint.y - lastDrawn.y);
				double d2 = std::hypot(x - lastDrawn.x, y - lastDrawn.y);
				double scale = d2 ? d1/d2 : 0;
				double extX = lastDrawn.x + (x - lastDrawn.x)*scale;
				double extY = lastDrawn.y + (y - lastDrawn.y)*scale;
				// How far off would that be?
				totalPendingError += std::hypot(extX - prevPoint.x, extY - prevPoint.y);
				if (totalPendingError > invPrecision) {
					// Would be too much accumulated error.  Draw the pending segment, and start a new one.
					raw(" ", round(prevPoint.x), " ", round(prevPoint.y));
					lastDrawn = prevPoint;
					totalPendingError = 0;
				}
			} else { // start
				raw(" ", round(x), " ", round(y));
				lastDrawn = {x, y};
				pointState = PointState::singlePoint;
			}
			outOfBoundsMask = mask;
			if (outOfBoundsMask) {
				if (pointState == PointState::pendingLine) {
					raw(" ", round(prevPoint.x), " ", round(prevPoint.y));
				}
				raw(" ", round(x), " ", round(y)); // Draw the first out-of-bounds point
				pointState = PointState::outOfBounds;
			}
		}
		prevPoint = {x, y};
	}
};

/** Any drawable element.
 	
	Each element can draw to three layers: fill, stroke and label.  Child elements are drawn in reverse order, so the earliest ones are drawn on top of each layer.
	
	Copy/assign is disabled, to prevent accidental copying when you should be holding a reference.
*/
class SvgDrawable {
	std::vector<std::unique_ptr<SvgDrawable>> children, layoutChildren;
	bool hasLayout = false;
protected:
	Bounds bounds;
	
	void invalidateLayout() {
		hasLayout = bounds.set = false;
		for (auto &c : children) c->invalidateLayout();
		layoutChildren.resize(0);
	}
	virtual void layout(const PlotStyle &style) {
		hasLayout = true;
		auto processChild = [&](std::unique_ptr<SvgDrawable> &child) {
			child->layoutIfNeeded(style);
			if (bounds.set) {
				if (child->bounds.set) bounds.expandTo(child->bounds);
			} else {
				bounds = child->bounds;
			}
		};
		for (auto &c : layoutChildren) processChild(c);
		for (auto &c : children) processChild(c);
	};
	/// These children are removed when the layout is invalidated
	void addLayoutChild(SvgDrawable *child) {
		layoutChildren.emplace_back(child);
	}
public:
	SvgDrawable() {}
	virtual ~SvgDrawable() {}
	SvgDrawable(const SvgDrawable &other) = delete;
	SvgDrawable & operator =(const SvgDrawable &other) = delete;

	Bounds layoutIfNeeded(const PlotStyle &style) {
		if (!hasLayout) this->layout(style);
		return bounds;
	}

	/// Takes ownership of the child
	void addChild(SvgDrawable *child, bool front=false) {
		if (front) {
			children.emplace(children.begin(), child);
		} else {
			children.emplace_back(child);
		}
	}

	virtual void writeData(SvgWriter &svg, const PlotStyle &style) {
		for (int i = layoutChildren.size() - 1; i >= 0; --i) {
			layoutChildren[i]->writeData(svg, style);
		}
		for (int i = children.size() - 1; i >= 0; --i) {
			children[i]->writeData(svg, style);
		}
	}
	virtual void writeLabel(SvgWriter &svg, const PlotStyle &style) {
		for (int i = layoutChildren.size() - 1; i >= 0; --i) {
			layoutChildren[i]->writeLabel(svg, style);
		}
		for (int i = children.size() - 1; i >= 0; --i) {
			children[i]->writeLabel(svg, style);
		}
	}

	/** Creates a frame from the current stat, and optionally clears the state ready for the next frame.
		The time is the start-time of the frame being created.
 		\image html animation.svg "Two lines with a different number of frames" */
	virtual void toFrame(double time, bool clear=true) {
		for (auto &c : children) c->toFrame(time, clear);
	}
	/// Sets loop time (or < 0 to disable)
	virtual void loopFrame(double loopTime) {
		for (auto &c : children) c->loopFrame(loopTime);
	}
	/// Removes all animation frames.  Mostly useful if re-using the diagram for multiple animations.
	virtual void clearFrames() {
		for (auto &c : children) c->clearFrames();
	}
};

/// Top-level objects which can generate SVG files
class SvgFileDrawable : public SvgDrawable {
public:
	virtual PlotStyle defaultStyle() const {
		PlotStyle result;
#ifdef SIGNALSMITH_PLOT_DEFAULT_STYLE
		SIGNALSMITH_PLOT_DEFAULT_STYLE((PlotStyle &)result);
#endif
		return result;
	}
	
	void write(std::ostream &o, const PlotStyle &style) {
		this->invalidateLayout();
		this->layout(style);

		// Add padding
		auto bounds = this->bounds.pad(style.padding);
		
		SvgWriter svg(o, bounds, style.precision);
		svg.raw("<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
		svg.tag("svg").attr("version", "1.1").attr("class", "svg-plot")
			.attr("xmlns", "http://www.w3.org/2000/svg")
			.attr("width", bounds.width(), "pt").attr("height", bounds.height(), "pt")
			.attr("viewBox", bounds.left, " ", bounds.top, " ", bounds.width(), " ", bounds.height())
			.attr("preserveAspectRatio", "xMidYMid");

		svg.rect(this->bounds.left, this->bounds.top, this->bounds.width(), this->bounds.height())
			.attr("class", "svg-plot-bg");
		this->writeData(svg, style);
		this->writeLabel(svg, style);

		int maxBounds = std::ceil(std::max(
			std::max(std::abs(this->bounds.left), std::abs(this->bounds.right)),
			std::max(std::abs(this->bounds.top), std::abs(this->bounds.bottom))
		)*std::sqrt(2));
		svg.raw("<defs>");
		for (size_t i = 0; i < style.markers.size(); ++i) {
			svg.tag("g").attr("id", style.markerId(i)).attr("class", "svg-plot-marker");
			svg.raw(style.markerRaw(i)).raw("</g>");
		}
		for (size_t i = 0; i < style.hatches.size(); ++i) {
			auto &hatch = style.hatches[i];
			if (!hatch.angles.size()) continue;
			svg.tag("mask").attr("id", "svg-plot-hatch", i);
			for (double angle : hatch.angles) {
				svg.rect(-maxBounds, -maxBounds, 2*maxBounds, 2*maxBounds)
					.attr("fill", "url(#svg-plot-hatch", i, "-pattern)")
					.attr("style", "transform:rotate(", angle, "deg)");
			}
			svg.raw("</mask>");
			double spacing = style.hatchSpacing*hatch.spaceScale;
			svg.tag("pattern").attr("patternUnits", "userSpaceOnUse")
				.attr("id", "svg-plot-hatch", i, "-pattern").attr("class", "svg-plot-hatch")
				.attr("x", 0).attr("y", 0).attr("width", 10).attr("height", spacing)
				.attr("stroke", "#FFF").attr("fill", "none");
			svg.line(-1, spacing*0.5, 11, spacing*0.5);
			svg.raw("</pattern>");
		}
		svg.raw("</defs>");

		svg.raw("<style>");
		std::stringstream cssStream;
		style.css(cssStream);
		std::string css = cssStream.str();
		const char *cPtr = css.c_str();
		// Strip whitespace that doesn't appear between letters/numbers
		bool letter = false, letterThenWhitespace = false;
		while (*cPtr) {
			char c = *(cPtr++);
			if (c == '\t' || c == '\n' || c == ' ') {
				letterThenWhitespace = letter;
			} else {
				letter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '.';
				if (letterThenWhitespace && letter) o << ' ';
				letterThenWhitespace = false;
				o << c;
			}
		}
		svg.raw("</style>");
		if (style.scriptHref.size()) svg.tag("script", true).attr("href", style.scriptHref);
		if (style.scriptSrc.size() > 0) {
			svg.raw("<script>").write(style.scriptSrc).raw("</script>");
		}
		svg.raw("</svg>");
	}
	void write(const std::string &svgFile, const PlotStyle &style) {
		std::ofstream s(svgFile);
		write(s, style);
	}
	// If we aren't given a style, use the default one
	void write(std::ostream &o) {
		this->write(o, this->defaultStyle());
	}
	void write(const std::string &svgFile) {
		write(svgFile, this->defaultStyle());
	}
	
	/// Draws when this object goes out of scope
	struct ScheduledWrite {
		SvgFileDrawable &drawable;
		PlotStyle style;
		std::string svgFile;
		
		ScheduledWrite(SvgFileDrawable &drawable, const PlotStyle &style, const std::string &svgFile) : drawable(drawable), style(style), svgFile(svgFile) {}
		ScheduledWrite(const ScheduledWrite &other) = delete;
		ScheduledWrite(ScheduledWrite &&other) : drawable(other.drawable), style(other.style), svgFile(other.svgFile) {
			other.svgFile = "";
		};
		~ScheduledWrite() {
			if (svgFile.size() > 0) drawable.write(svgFile, style);
		}
	};
	ScheduledWrite writeLater(const std::string &svgFile) {
		return ScheduledWrite{*this, this->defaultStyle(), svgFile};
	}
};

/// A labelled point on an axis.
struct Tick {
	double value;
	std::string name;

	enum class Strength {major, minor, tick};
	Strength strength = Strength::tick;
	
	Tick(double value, std::string name) : value(value), name(name) {}

	template<typename T>
	Tick(T v) : value(double(v)) {
		name = (std::stringstream() << value).str();
	}
};

/** A map from values to screen-space.

	Individual grid/ticks can be added with `.major()`/`.minor()`/`.tick()`.
	\code
		axis.major(4); // default label
		axis.major(5, "five"); // explicit label
	\endcode
	
	Multiple grids/ticks can be added using `.majors()`/`.minors()`/`.ticks()`, which accept a variable number of values:
	\code
		axis.majors(0, 10).minors(2, 4, 6, 8);
	\endcode
*/
class Axis {
	std::function<double(double)> unitMap;
	double autoMin, autoMax;
	bool hasAutoValue = false;
	bool autoScale, autoLabel;
	std::string _label = "";

	std::vector<Axis *> linked;
	Axis *linkedParent = nullptr;
public:
	double drawLow, drawHigh;
	double drawMin() const {
		return std::min(drawLow, drawHigh);
	}
	double drawMax() const {
		return std::max(drawLow, drawHigh);
	}
	double drawSize() const {
		return std::abs(drawHigh - drawLow);
	}
	/// Not associated with a particular line by default, but can be
	PlotStyle::Counter styleIndex = -1;

	Axis(double drawLow, double drawHigh) : drawLow(drawLow), drawHigh(drawHigh) {
		linear(0, 1);
		autoScale = true;
		autoLabel = true;
	}
	explicit Axis(const Axis &other) = default;

	/// Register a value for the auto-scale
	void autoValue(double v) {
		if (linkedParent) return linkedParent->autoValue(v);
		if (!autoScale) return;
		if (!hasAutoValue) {
			autoMin = autoMax = v;
			hasAutoValue = true;
		} else {
			autoMin = std::min(autoMin, v);
			autoMax = std::max(autoMax, v);
		}
		for (auto other : linked) other->autoValue(v);
	}
	void autoSetup() {
		if (hasAutoValue) {
			if (autoScale) linear(autoMin, autoMax);
			if (autoLabel) minors(autoMin, autoMax);
		}
		for (auto other : linked) other->autoSetup();
	}
	/// Prevent auto-labelling
	Axis & blank(bool includeLinked=false) {
		tickList.clear();
		autoLabel = false;
		if (includeLinked) {
			for (auto other : linked) other->blank();
		}
		return *this;
	}
	/// Clear the names from any existing labels
	Axis & blankLabels(bool includeLinked=false) {
		for (auto &t : tickList) t.name = "";
		_label = "";
		if (includeLinked) {
			for (auto other : linked) other->blankLabels();
		}
		return *this;
	}
	/// Copy ticks/label from another axis, optionally removing their text
	Axis & copyFrom(Axis &other, bool clearLabels=false) {
		unitMap = other.unitMap;
		for (Tick tick : other.tickList) {
			if (clearLabels) tick.name = "";
			tickList.push_back(tick);
		}
		autoMin = other.autoMin;
		autoMax = other.autoMax;
		hasAutoValue = other.hasAutoValue;
		autoScale = other.autoScale;
		autoLabel = other.autoLabel;
		for (auto &t : tickList) {
			autoValue(t.value);
		}
		if (other._label.size()) this->_label = other._label;
		for (auto o : linked) o->copyFrom(other, clearLabels);
		return *this;
	}
	/// Link this axis to another, copying any ticks/labels set later as well
	Axis & linkFrom(Axis &other) {
		copyFrom(other);
		other.linked.push_back(this);
		linkedParent = &other;
		return *this;
	}
	
	/// Whether the axis should draw on the non-default side (e.g. right/top)
	bool flipped = false;
	Axis & flip(bool flip=true) {
		flipped = flip;
		for (auto other : linked) other->flip(flip);
		return *this;
	}
	
	/// Sets the label, and optionally style to match a particular line.
	Axis & label(std::string l, PlotStyle::Counter index=-1) {
		_label = l;
		styleIndex = index;
		for (auto other : linked) other->label(l, index);
		return *this;
	}
	const std::string & label() const {
		return _label;
	}

	Axis & range(std::function<double(double)> valueToUnit) {
		autoScale = false;
		unitMap = valueToUnit;
		for (auto other : linked) other->range(valueToUnit);
		return *this;
	}
	Axis & range(double map(double)) {
		return range(std::function<double(double)>(map));
	}
	Axis & range(std::function<double(double)> map, double lowValue, double highValue) {
		double lowMapped = map(lowValue), highMapped = map(highValue);
		return range([=](double v) {
			double mapped = map(v);
			return (mapped - lowMapped)/(highMapped - lowMapped);
		});
	}
	Axis & range(double map(double), double lowValue, double highValue) {
		return range(std::function<double(double)>(map), lowValue, highValue);
	}
	Axis & linear(double low, double high) {
		return range([=](double v) {
			return (v - low)/(high - low);
		});
	}
	
	double map(double v) {
		double unit = unitMap(v);
		return drawLow + unit*(drawHigh - drawLow);
	}

	std::vector<Tick> tickList;

	template<class ...Args>
	Axis & major(Args &&...args) {
		Tick t(args...);
		autoValue(t.value);
		t.strength = Tick::Strength::major;
		tickList.push_back(t);
		autoLabel = false;
		for (auto other : linked) other->major(args...);
		return *this;
	}
	template<class ...Args>
	Axis & minor(Args &&...args) {
		Tick t(args...);
		autoValue(t.value);
		t.strength = Tick::Strength::minor;
		tickList.push_back(t);
		autoLabel = false;
		for (auto other : linked) other->minor(args...);
		return *this;
	}
	template<class ...Args>
	Axis & tick(Args &&...args) {
		Tick t(args...);
		autoValue(t.value);
		t.strength = Tick::Strength::tick;
		tickList.push_back(t);
		autoLabel = false;
		for (auto other : linked) other->tick(args...);
		return *this;
	}
	
	Axis &majors() {
		return *this;
	}
	template<class ...Args>
	Axis &majors(Tick tick, Args ...args) {
		return major(tick).majors(args...);
	}
	Axis &minors() {
		autoLabel = false;
		return *this;
	}
	template<class ...Args>
	Axis &minors(Tick tick, Args ...args) {
		return minor(tick).minors(args...);
	}
	Axis & ticks() {
		autoLabel = false;
		return *this;
	}
	template<class ...Args>
	Axis & ticks(Tick t, Args ...args) {
		return tick(t).ticks(args...);
	}
};

class TextLabel : public SvgDrawable {
	double textWidth = 0;
	void write(SvgWriter &svg, double fontSize) {
		{
			auto text = svg.tag("text").attr("class", cssClass);
			double tx = drawAt.x, ty = drawAt.y;
			if (alignment > 0.5) {
				text.attr("style", "text-anchor:start");
				tx += textWidth*(alignment - 1);
			} else if (alignment < -0.5) {
				text.attr("style", "text-anchor:end");
				tx += textWidth*(alignment + 1);
			} else {
				tx += textWidth*alignment;
			}
			ty -= fontSize*0.1; // Just a vertical alignment tweak
			if (vertical) {
				text.attr("x", 0).attr("y", 0)
					.attr("transform", "rotate(-90) translate(", -ty, " ", tx, ")");
			} else {
				text.attr("x", tx).attr("y", ty);
			}
		}
		svg.write(text);
		svg.raw("</text>");
	}
protected:
	Point2D drawAt;
	double alignment = 0; // 0=centre, 1=left, -1=right
	std::string text, cssClass;
	bool vertical, isValue;

	void layout(const PlotStyle &style) override {
		double x = drawAt.x, y = drawAt.y;
		double fontSize = isValue ? style.valueSize : style.labelSize;

		// Assume all text/labels are UTF-8
		textWidth = estimateUtf8Width(text.c_str())*fontSize*style.fontAspectRatio;

		if (vertical) {
			this->bounds = {x - fontSize*0.5, x + fontSize*0.5, y - textWidth*(alignment - 1)*0.5, y - textWidth*(alignment + 1)*0.5};
		} else {
			this->bounds = {x + textWidth*(alignment - 1)*0.5, x + textWidth*(alignment + 1)*0.5, y - fontSize*0.5, y + fontSize*0.5};
		}
		SvgDrawable::layout(style);
	}

public:
	TextLabel(Point2D at, double alignment, std::string text, std::string cssClass="svg-plot-label", bool vertical=false, bool isValue=false) : drawAt(at), alignment(alignment), text(text), cssClass(cssClass), vertical(vertical), isValue(isValue) {}
	
	void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
		write(svg, isValue ? style.valueSize : style.labelSize);
	}
};

/** A line on a 2D plot, with fill and/or stroke
	\image html filled-circles.svg
*/
class Line2D : public SvgDrawable {
	bool _drawLine = true;
	bool _drawFill = false;
	bool hasFillToX = false, hasFillToY = false;
	Point2D fillToPoint;
	Line2D *fillToLine = nullptr;
	
	Axis &axisX, &axisY;
	std::vector<Point2D> points;
	struct Marker {
		Point2D point;
		int shape;
	};
	std::vector<Marker> markers;
	struct Frame {
		double time;
		std::vector<Point2D> points;
		std::vector<Marker> markers;
	};
	double framesLoopTime = 0;
	std::vector<Frame> frames;
	Point2D latest{0, 0};
	
	template<class WriteValue>
	void writeAnimationAttrs(SvgWriter &svg, WriteValue &&writeValue) {
		double lastFrame = frames.back().time;
		double framesEnd = std::max(framesLoopTime, lastFrame);
		if (framesLoopTime > 0) {
			svg.attr("dur", framesLoopTime, "s").attr("repeatCount", "indefinite");
		} else {
			svg.attr("dur", framesEnd);
		}
		svg.raw(" values=\"");
		for (size_t i = 0; i < frames.size(); ++i) {
			if (i > 0) svg.raw(";");
			writeValue(i);
		}
		if (framesLoopTime > lastFrame) {
			svg.raw(";");
			writeValue(0);
		}
		svg.raw("\" keyTimes=\"");
		for (size_t i = 0; i < frames.size(); ++i) {
			if (i > 0) svg.raw(";");
			svg.write(frames[i].time/framesEnd);
		}
		if (framesLoopTime > lastFrame) svg.raw(";1");
	}
public:
	PlotStyle::Counter styleIndex;

	Line2D(Axis &axisX, Axis &axisY, PlotStyle::Counter styleIndex) : axisX(axisX), axisY(axisY), styleIndex(styleIndex) {}
	
	Line2D & add(double x, double y) {
		latest = {x, y};
		points.push_back({x, y});
		axisX.autoValue(x);
		axisY.autoValue(y);
		return *this;
	}

	template<class X, class Y>
	Line2D & addArray(X &&x, Y &&y, size_t size) {
		for (size_t i = 0; i < size; ++i) add(x[i], y[i]);
		return *this;
	}
	template<class X, class Y>
	Line2D & addArray(X &&x, Y &&y) {
		return addArray(std::forward<X>(x), std::forward<Y>(y), std::min<size_t>(x.size(), y.size()));
	}
	
	Line2D & marker(double x, double y, int shape=-1) {
		latest = {x, y};
		markers.push_back({{x, y}, shape});
		axisX.autoValue(x);
		axisY.autoValue(y);
		return *this;
	}

	void toFrame(double time, bool clear=true) override {
		SvgDrawable::toFrame(time, clear);
		frames.push_back({time, points, markers});
		if (clear) {
			points.clear();
			markers.clear();
		}
		framesLoopTime = std::max(time, framesLoopTime);
	}
	void loopFrame(double endTime) override {
		SvgDrawable::loopFrame(endTime);
		framesLoopTime = endTime;
	}
	void clearFrames() override {
		SvgDrawable::clearFrames();
		frames.resize(0);
		framesLoopTime = 0;
	}

	/// @{
	///@name Draw config

	Line2D & drawLine(bool draw=true) {
		_drawLine = draw;
		return *this;
	}
	Line2D & drawFill(bool draw=true) {
		_drawFill = draw;
		return *this;
	}
	/// Start/end the fill at a given Y value
	Line2D & fillToY(double y) {
		_drawFill = true;
		hasFillToX = false;
		hasFillToY = true;
		fillToPoint = {0, y};
		return *this;
	}
	/// Start/end the fill at a given X value
	Line2D & fillToX(double x) {
		_drawFill = true;
		hasFillToX = true;
		hasFillToY = false;
		fillToPoint = {x, 0};
		return *this;
	}
	Line2D & fillTo(Line2D &other) {
		_drawFill = true;
		hasFillToX = hasFillToY = false;
		fillToLine = &other;
		return *this;
	}
	/// @}
	
	class LineLabel : public TextLabel {
		Axis &axisX, &axisY;
		Point2D at;
		std::string name;
		// direction: 0=right, 1=up, 2=left, 3=down
		double direction, distance;
		Point2D drawLineFrom{0, 0}, drawLineTo{0, 0};
		PlotStyle::Counter &styleIndex;
	protected:
		void layout(const PlotStyle &style) override {
			double sx = axisX.map(at.x), sy = axisY.map(at.y);
			if (distance < 0) {
				this->alignment = 0;
				this->drawAt = {sx, sy};
			} else {
				double angle = direction*3.14159265358979/180;
				double ax = std::cos(angle), ay = std::sin(angle);

				double px = sx + distance*ax, py = sy + distance*ay;
				double tx = px, ty = py;
				double fontSize = style.labelSize;
				double letterHeight = fontSize*0.8;

				double space = fontSize*0.25;
				double verticalWiggle = fontSize*0.3;
				if (ax < -0.7) {
					this->alignment = -1;
					tx -= space;
					ty += ay*verticalWiggle;
				} else if (ax > 0.7) {
					this->alignment = 1;
					tx += space;
					ty += ay*verticalWiggle;
				} else if (ay > 0) {
					ty += letterHeight;
					tx += ax*fontSize;
					this->alignment = ax;
				} else {
					ty -= letterHeight;
					tx += ax*fontSize;
					this->alignment = ax;
				}
				
				double lineDistance = distance - space;
				drawLineFrom = drawLineTo = {px, py};
				if (lineDistance > space) {
					drawLineTo = {sx + ax*space, sy + ay*space};
				}

				this->drawAt = {tx, ty};
			}
			this->cssClass = "svg-plot-label " + style.textClass(styleIndex);

			TextLabel::layout(style);
		}
	public:
		LineLabel(Axis &axisX, Axis &axisY, Point2D at, std::string name, double direction, double distance, PlotStyle::Counter &styleIndex) : TextLabel({0, 0}, 0, name), axisX(axisX), axisY(axisY), at(at), name(name), direction(direction), distance(distance), styleIndex(styleIndex) {}
		
		void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
			if (drawLineTo.x != drawLineFrom.x || drawLineTo.y != drawLineFrom.y) {
				svg.line(drawLineFrom.x, drawLineFrom.y, drawLineTo.x, drawLineTo.y)
					.attr("class", "svg-plot-tick ", style.strokeClass(styleIndex));
			}
			TextLabel::writeLabel(svg, style);
		}
	};

	Line2D & label(double valueX, double valueY, std::string name) {
		return label(valueX, valueY, name, 0, -1);
	}

	Line2D & label(double valueX, double valueY, std::string name, double degrees, double distance=0) {
		axisX.autoValue(valueX);
		axisY.autoValue(valueY);
		this->addChild(new LineLabel(axisX, axisY, {valueX, valueY}, name, degrees, distance, styleIndex));
		return *this;
	}

	Line2D & label(std::string name, double degrees=0, double distance=0) {
		return label(latest.x, latest.y, name, degrees, distance);
	}

	Line2D & label(double xIsh, std::string name, double degrees=0, double distance=0) {
		size_t closest = 0;
		double closestError = -1;
		for (size_t i = 0; i < points.size(); ++i) {
			if (closestError < 0 || closestError > std::abs(points[i].x - xIsh)) {
				closest = i;
				closestError = std::abs(points[i].x - xIsh);
			}
		}
		Point2D latest = points[closest];
		return label(latest.x, latest.y, name, degrees, distance);
	}
	
	void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
		double xMin = axisX.drawMin(), xMax = axisX.drawMax();
		double yMin = axisY.drawMin(), yMax = axisY.drawMax();
		size_t maxMarkers = markers.size();
		bool animated = (frames.size() > 0);
		for (auto &frame : frames) {
			maxMarkers = std::max(maxMarkers, frame.markers.size());
		}
		static constexpr double outOfRange = -10000;
		for (size_t m = 0; m < maxMarkers; ++m) {
			double x = outOfRange, y = outOfRange;
			auto shape = styleIndex;

			if (m < markers.size()) {
				auto &marker = markers[m];
				x = axisX.map(marker.point.x);
				y = axisY.map(marker.point.y);
				if (x < xMin || x > xMax || y < yMin || y > yMax) {
					x = y = outOfRange;
				}
				if (marker.shape >= 0) shape = marker.shape;
			}
			if (animated || x != outOfRange || y != outOfRange) {
				if (!animated) {
					svg.tag("use", true)
						.attr("href", "#", style.markerId(shape))
						.attr("class", style.fillClass(styleIndex), " ", style.strokeClass(styleIndex))
						.attr("transform", "translate(", x, " ", y, ")");
				} else {
					svg.tag("g")
						.attr("class", style.fillClass(styleIndex), " ", style.strokeClass(styleIndex), "")
						.attr("transform", "translate(", x, " ", y, ")");
					svg.tag("g").attr("class", "svg-plot-marker");
					svg.raw(style.markerRaw(shape)).raw("</g>");

					svg.raw("<animateTransform").attr("calcMode", "discrete")
						.attr("attributeName", "transform").attr("attributeType", "XML")
						.attr("type", "translate");
					writeAnimationAttrs(svg, [&](int index) {
						double x = outOfRange, y = outOfRange;
						if (m < frames[index].markers.size()) {
							x = axisX.map(frames[index].markers[m].point.x);
							y = axisY.map(frames[index].markers[m].point.y);
							if (x < xMin || x > xMax || y < yMin || y > yMax) {
								x = y = outOfRange;
							}
						}
						svg.raw(x, " ", y);
					});
					svg.raw("\"/></g>");
				}
			}
		}
		SvgDrawable::writeLabel(svg, style);
	}
	
	void writeData(SvgWriter &svg, const PlotStyle &style) override {
		auto writePoints = [&](std::vector<Point2D> &points, bool fill) {
			if (!points.size()) return;
			svg.startPath();
			for (auto &p : points) {
				svg.addPoint(axisX.map(p.x), axisY.map(p.y));
			}
			if (fill) {
				if (fillToLine) {
					auto &otherPoints = fillToLine->points;
					for (int i = otherPoints.size() - 1; i >= 0; --i) {
						auto &p = otherPoints[i];
						svg.addPoint(fillToLine->axisX.map(p.x), fillToLine->axisY.map(p.y), i == 0);
					}
				} else if (hasFillToX) {
					svg.addPoint(axisX.map(fillToPoint.x), axisY.map(points.back().y), true);
					svg.addPoint(axisX.map(fillToPoint.x), axisY.map(points[0].y), true);
				} else if (hasFillToY) {
					svg.addPoint(axisX.map(points.back().x), axisY.map(fillToPoint.y), true);
					svg.addPoint(axisX.map(points[0].x), axisY.map(fillToPoint.y), true);
				}
			}
			svg.endPath();
		};
		auto writeD = [&](bool fill){
			auto &p = (points.size() || !frames.size()) ? points : frames.back().points;
			svg.raw(" d=\"");
			writePoints(p, fill);
			if (frames.size() > 0) {
				svg.raw("\">\n<animate")
					.attr("attributeName", "d").attr("calcMode", "discrete");
				writeAnimationAttrs(svg, [&](size_t i) {
					writePoints(frames[i].points, fill);
				});
				svg.raw("\"/></path>");
			} else {
				svg.raw("\"/>");
			}
		};
		
		if (_drawFill) {
			svg.raw("<path")
				.attr("class", "svg-plot-fill ", style.fillClass(styleIndex), " ", style.hatchClass(styleIndex));
			writeD(true);
		}
		if (_drawLine) {
			svg.raw("<path")
				.attr("class", "svg-plot-line ", style.strokeClass(styleIndex), " ", style.dashClass(styleIndex));
			writeD(false);
		}
		SvgDrawable::writeData(svg, style);
	}
};

class Legend : public SvgFileDrawable {
	SvgFileDrawable &ref;
	Bounds dataBounds;
	double rx, ry;
	Bounds location;
	struct Entry {
		PlotStyle::Counter style;
		std::string name;
		bool stroke, fill, marker;
	};
	std::vector<Entry> entries;
public:
	Legend(SvgFileDrawable &ref, Bounds dataBounds, double rx, double ry) : ref(ref), dataBounds(dataBounds), rx(rx), ry(ry) {}
	
	void layout(const PlotStyle &style) override {
		Bounds refBounds = ref.layoutIfNeeded(style).pad(style.textPadding);
		double exampleLineWidth = style.labelSize*1.5; // 1.5em
		double longestLabel = 0;
		for (auto &e : entries) {
			longestLabel = std::max(longestLabel, estimateUtf8Width(e.name.c_str()));
		}
		double width = exampleLineWidth + style.textPadding*3 + longestLabel*style.labelSize;
		double height = style.textPadding*2 + entries.size()*style.labelSize*style.lineHeight;
		
		Bounds dataInset = dataBounds.pad(-style.tickH, -style.tickV);
		double extraW = dataInset.width() - width;
		double extraH = dataInset.height() - height;
		Point2D topLeft = {
			dataInset.left + extraW*std::max(0.0, std::min(1.0, rx)),
			dataInset.bottom - height - extraH*std::max(0.0, std::min(1.0, ry))
		};
		if (rx < 0) topLeft.x += (refBounds.left - width - topLeft.x)*-rx;
		if (rx > 1) topLeft.x += (refBounds.right - topLeft.x)*(rx - 1);
		if (ry < 0) topLeft.y += (refBounds.bottom - topLeft.y)*-ry;
		if (ry > 1) topLeft.y += (refBounds.top - height - topLeft.y)*(ry - 1);
		this->bounds = location = {topLeft.x, topLeft.x + width, topLeft.y, topLeft.y + height};
		
		for (size_t i = 0; i < entries.size(); ++i) {
			auto &entry = entries[i];
			double labelX = topLeft.x + style.textPadding*2 + exampleLineWidth;
			double labelY = location.top + style.textPadding + (i + 0.5)*style.labelSize*style.lineHeight;
			auto *label = new TextLabel({labelX, labelY}, 1, entry.name, "svg-plot-label", false, false);
			this->addLayoutChild(label);
		}
		SvgFileDrawable::layout(style);
	}
	Legend & add(PlotStyle::Counter style, std::string name, bool stroke=true, bool fill=false, bool marker=false) {
		entries.push_back(Entry{style, name, stroke, fill, marker});
		return *this;
	}
	Legend & add(const Line2D &line2D, std::string name, bool stroke=true, bool fill=false, bool marker=false) {
		return add(line2D.styleIndex, name, stroke, fill, marker);
	}
	Legend & line(PlotStyle::Counter style, std::string name) {
		return add(style, name, true, false, false);
	}
	Legend & line(const Line2D &line2D, std::string name) {
		return add(line2D.styleIndex, name, true, false, false);
	}
	Legend & fill(PlotStyle::Counter style, std::string name) {
		return add(style, name, false, true, false);
	}
	Legend & fill(const Line2D &line2D, std::string name) {
		return add(line2D.styleIndex, name, false, true, false);
	}
	Legend & marker(PlotStyle::Counter style, std::string name) {
		return add(style, name, false, false, true);
	}
	Legend & marker(const Line2D &line2D, std::string name) {
		return add(line2D.styleIndex, name, false, false, true);
	}
	void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
		svg.raw("<g>");
		svg.rect(location.left, location.top, location.width(), location.height())
			.attr("class", "svg-plot-legend");
		double lineX1 = location.left + style.textPadding;
		double lineX2 = lineX1 + style.labelSize*1.5; // 1.5em
		for (size_t i = 0; i < entries.size(); ++i) {
			auto &entry = entries[i];
			double lineY = location.top + style.textPadding + (i + 0.5)*style.labelSize*style.lineHeight;
			if (entry.fill) {
				double height = style.labelSize;
				svg.rect(lineX1, lineY - height*0.5, lineX2 - lineX1, height)
					.attr("class", "svg-plot-fill ", style.fillClass(entry.style), " ", style.hatchClass(entry.style));
			}
			if (entry.stroke) {
				svg.line(lineX1, lineY, lineX2, lineY)
					.attr("class", "svg-plot-line ", style.strokeClass(entry.style), " ", style.dashClass(entry.style));
			}
			if (entry.marker) {
				svg.tag("use", true)
					.attr("href", "#", style.markerId(entry.style))
					.attr("class", style.fillClass(entry.style), " ", style.strokeClass(entry.style))
					.attr("transform", "translate(", (lineX1 + lineX2)/2, " ", lineY, ")");
			}
		}
		svg.raw("</g>");
		SvgFileDrawable::writeLabel(svg, style);
	}
};

class Image : public SvgDrawable {
	Axis &x, &y;
	Bounds dataBounds;
	std::string url;
public:
	Image(Axis &x, Axis &y, Bounds dataBounds, const std::string &url) : x(x), y(y), dataBounds(dataBounds), url(url) {
		// Add the image to automatic bounds
		x.autoValue(dataBounds.left);
		x.autoValue(dataBounds.right);
		y.autoValue(dataBounds.top);
		y.autoValue(dataBounds.bottom);
	}

	void writeData(SvgWriter &svg, const PlotStyle &style) override {
		SvgDrawable::writeData(svg, style);
		double drawLeft = x.map(dataBounds.left);
		double drawRight = x.map(dataBounds.right);
		double drawTop = y.map(dataBounds.top);
		double drawBottom = y.map(dataBounds.bottom);
		svg.tag("image", true).attr("width", 1).attr("height", 1)
			.attr("transform", "translate(", drawLeft, ",", drawTop, ")scale(", drawRight - drawLeft, ",", drawBottom - drawTop, ")")
			.attr("preserveAspectRatio", "none").attr("href", url);
	}
};

class Plot2D : public SvgFileDrawable {
	std::string plotTitle;
	std::vector<std::unique_ptr<Axis>> xAxes, yAxes;
	Bounds size;
public:
	Axis &x, &y;
	/// Creates an X axis, covering some portion of the left/right side
	Axis & newX(double lowRatio=0, double highRatio=1) {
		Axis *x = new Axis(size.left + lowRatio*size.width(), size.left + highRatio*size.width());
		xAxes.emplace_back(x);
		return *x;
	}
	/// Creates a Y axis, covering some portion of the bottom/top side
	Axis & newY(double lowRatio=0, double highRatio=1) {
		Axis *y = new Axis(size.bottom - lowRatio*size.height(), size.bottom - highRatio*size.height());
		yAxes.emplace_back(y);
		return *y;
	}
	/// Style for the next auto-styled element
	PlotStyle::Counter styleCounter;

	Plot2D() : Plot2D(240, 130) {}
	Plot2D(double width, double height) : Plot2D({0, width}, {height, 0}) {}
	Plot2D(Axis ax, Axis ay) : size(ax.drawMin(), ax.drawMax(), ay.drawMin(), ay.drawMax()), x(*(new Axis(ax))), y(*(new Axis(ay))) {
		xAxes.emplace_back(&x); // created above, but we take ownership here
		yAxes.emplace_back(&y);
	}
	
	void writeData(SvgWriter &svg, const PlotStyle &style) override {
		svg.rect(size.left, size.top, size.width(), size.height())
			.attr("class", "svg-plot-axis");
		for (auto &x : xAxes) {
			for (auto &t : x->tickList) {
				if (t.strength != Tick::Strength::tick) {
					double screenX = x->map(t.value);
					bool isMajor = (t.strength == Tick::Strength::major);
					svg.line(screenX, size.top, screenX, size.bottom)
						.attr("class", "svg-plot-", isMajor ? "major" : "minor");
				}
			}
		}
		for (auto &y : yAxes) {
			for (auto &t : y->tickList) {
				if (t.strength != Tick::Strength::tick) {
					double screenY = y->map(t.value);
					bool isMajor = (t.strength == Tick::Strength::major);
					svg.line(size.left, screenY, size.right, screenY)
						.attr("class", "svg-plot-", isMajor ? "major" : "minor");
				}
			}
		}
		svg.pushClip(size.pad(style.lineWidth*0.5), style.lineWidth);
		SvgDrawable::writeData(svg, style);
		svg.popClip();
	}

	void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
		svg.raw("<g>");
		for (auto &x : xAxes) {
			double fromY = x->flipped ? size.top : size.bottom;
			double toY = fromY + (x->flipped ? -style.tickV : style.tickV);
			for (auto &t : x->tickList) {
				double screenX = x->map(t.value);
				if (t.name.size() && style.tickV != 0) {
					svg.line(screenX, fromY, screenX, toY)
						.attr("class", "svg-plot-tick");
				}
			}
		}
		for (auto &y : yAxes) {
			double fromX = y->flipped ? size.right : size.left;
			double toX = fromX + (y->flipped ? style.tickH : -style.tickH);
			for (auto &t : y->tickList) {
				if (t.name.size() && style.tickH != 0) {
					double screenY = y->map(t.value);
					svg.line(fromX, screenY, toX, screenY)
						.attr("class", "svg-plot-tick");
				}
			}
		}
		SvgDrawable::writeLabel(svg, style);
		svg.raw("</g>");
	}

	void layout(const PlotStyle &style) override {
		// Auto-scale axes if needed
		for (auto &x : xAxes) x->autoSetup();
		for (auto &y : yAxes) y->autoSetup();

		double tv = std::max(style.tickV, 0.0), th = std::max(style.tickH, 0.0);

		// Add labels for axes
		for (auto &x : xAxes) {
			double xMin = x->drawMin() - 0.1, xMax = x->drawMax() + 0.1;
			double alignment = (x->flipped ? -1 : 1), hasValues = x->tickList.size() ? 1 : 0;
			double screenY = (x->flipped ? size.top : size.bottom) + alignment*(tv + hasValues*(style.valueSize*0.5 + style.textPadding));
			for (auto &t : x->tickList) {
				double screenX = x->map(t.value);
				if (t.name.size() && screenX >= xMin && screenX <= xMax) {
					auto *label = new TextLabel({screenX, screenY}, 0, t.name, "svg-plot-value", false, true);
					this->addLayoutChild(label);
				}
			}
			if (x->label().size()) {
				double labelY = screenY + alignment*((style.labelSize + hasValues*style.valueSize)*0.5 + style.textPadding);
				double midX = (x->drawMax() + x->drawMin())*0.5;
				auto *label = new TextLabel({midX, labelY}, 0, x->label(), "svg-plot-label " + style.textClass(x->styleIndex), false, true);
				this->addLayoutChild(label);
		}
		}
		double longestLabelLeft = 0, longestLabelRight = 0;
		for (auto &y : yAxes) {
			double yMin = y->drawMin() - 0.1, yMax = y->drawMax() + 0.1;
			double alignment = (y->flipped ? 1 : -1);
			double screenX = (y->flipped ? size.right : size.left) + alignment*(th + style.textPadding);
			for (auto &t : y->tickList) {
				double screenY = y->map(t.value);
				if (t.name.size() && screenY >= yMin && screenY <= yMax) {
					auto *label = new TextLabel({screenX, screenY}, alignment, t.name, "svg-plot-value", false, true);
					this->addLayoutChild(label);

					double &longestLabel = y->flipped ? longestLabelRight : longestLabelLeft;
					longestLabel = std::max(longestLabel, estimateUtf8Width(t.name.c_str()));
				}
			}
		}
		for (auto &y : yAxes) {
			double alignment = (y->flipped ? 1 : -1);
			double screenX = (y->flipped ? size.right : size.left) + alignment*(th + style.textPadding);
			if (y->label().size()) {
				double longestLabel = y->flipped ? longestLabelRight : longestLabelLeft;
				double labelX = screenX + alignment*(style.textPadding*1.5 + longestLabel*style.valueSize);
				double midY = (y->drawMax() + y->drawMin())*0.5;
				auto *label = new TextLabel({labelX, midY}, 0, y->label(), "svg-plot-label " + style.textClass(y->styleIndex), true, true);
				this->addLayoutChild(label);
			}
		}

		this->bounds = size.pad(th, tv);
		SvgDrawable::layout(style);
	};
	
	Line2D & line(Axis &x, Axis &y, PlotStyle::Counter styleIndex) {
		Line2D *line = new Line2D(x, y, styleIndex);
		this->addChild(line);
		return *line;
	}
	Line2D & line(Axis &x, Axis &y) {
		return line(x, y, styleCounter.bump());
	}
	Line2D & line(PlotStyle::Counter styleIndex) {
		return line(this->x, this->y, styleIndex);
	}
	Line2D & line() {
		return line(styleCounter.bump());
	}

	/// Convenience method, returns a line set to only fill.
	template<class ...Args>
	Line2D & fill(Args &&...args) {
		return line(args...).drawLine(false).drawFill(true);
	}
	
	/** Creates a legend at a given position.
	If `xRatio` and `yRatio` are in the range 0-1, the legend will be inside the plot.  Otherwise, it will move outside the plot (e.g. -1 will be left/below the axes, including any labels).
	*/
	Legend & legend(double xRatio, double yRatio) {
		Legend *legend = new Legend(*this, size, xRatio, yRatio);
		this->addChild(legend, true);
		return *legend;
	}
	
	Image & image(Axis &x, Axis &y, Bounds dataBounds, const std::string &url) {
		Image *image = new Image(x, y, dataBounds, url);
		this->addChild(image);
		return *image;
	}
	Image & image(Bounds dataBounds, const std::string &url) {
		return image(x, y, dataBounds, url);
	}
	Image & image(double left, double right, double top, double bottom, const std::string &url) {
		return image(Bounds{left, right, top, bottom}, url);
	}
};

class Cell : public SvgFileDrawable {
protected:
	void layout(const PlotStyle &style) override {
		this->bounds = {0, 0, 0, 0};
		SvgFileDrawable::layout(style);
	}
public:
	Plot2D & plot(double widthPt, double heightPt) {
		Plot2D *axes = new Plot2D({0, widthPt}, {heightPt, 0});
		this->addChild(axes);
		return *axes;
	}
	Plot2D & plot() {
		Plot2D *axes = new Plot2D();
		this->addChild(axes);
		return *axes;
	}
};

class Grid : public Cell {
	int _colMax = 0, _colMin = 0, _rowMax = 0, _rowMin = 0;
	struct Item {
		int column, row;
		std::unique_ptr<Grid> cell;
		Point2D transpose = {0, 0};
		Item(int column, int row) : column(column), row(row), cell(new Grid()) {}
	};
	std::vector<Item> items;

	void writeItems(bool label, SvgWriter &svg, const PlotStyle &style) {
		for (auto &it : items) {
			svg.tag("g").attr("transform", "translate(", it.transpose.x, " ", it.transpose.y, ")");
			if (label) {
				it.cell->writeLabel(svg, style);
			} else {
				it.cell->writeData(svg, style);
			}
			svg.raw("</g>");
		}
	}
protected:
	void layout(const PlotStyle &style) override {
		struct Range {
			double min = 0, max = 0;
			double offset = 0;
			Range & include(double v) {
				min = std::min(v, min);
				max = std::max(v, max);
				return *this;
			}
		};
		std::vector<Range> colRange(_colMax - _colMin + 1);
		std::vector<Range> rowRange(_rowMax - _rowMin + 1);
		for (auto &it : items) {
			Bounds bounds = it.cell->layoutIfNeeded(style);
			colRange[it.column - _colMin].include(bounds.left).include(bounds.right);
			rowRange[it.row - _rowMin].include(bounds.top).include(bounds.bottom);
		}
		this->bounds = {0, 0, 0, 0};
		double offset = 0;
		for (auto &r : colRange) {
			r.offset = offset - r.min;
			offset += r.max - r.min + style.padding;
		}
		this->bounds.right = offset - style.padding;
		offset = 0;
		for (auto &r : rowRange) {
			r.offset = offset - r.min;
			offset += r.max - r.min + style.padding;
		}
		this->bounds.bottom = offset - style.padding;
		for (auto &it : items) {
			it.transpose = {colRange[it.column - _colMin].offset, rowRange[it.row - _rowMin].offset};
		}
		SvgDrawable::layout(style);
	}

	void writeData(SvgWriter &svg, const PlotStyle &style) override {
		SvgDrawable::writeData(svg, style);
		writeItems(false, svg, style);
	}
	void writeLabel(SvgWriter &svg, const PlotStyle &style) override {
		SvgDrawable::writeLabel(svg, style);
		writeItems(true, svg, style);
	}
public:
	int rows() const {
		return _rowMax - _rowMin;
	}
	int columns() const {
		return _colMax - _colMin;
	}
	Grid & operator ()(int column, int row) {
		_colMin = std::min(_colMin, column);
		_colMax = std::max(_colMax, column);
		_rowMin = std::min(_rowMin, row);
		_rowMax = std::max(_rowMax, row);
		for (auto &it : items) {
			if (it.row == row && it.column == column) {
				return *it.cell;
			}
		}
		items.emplace_back(column, row);
		return *(items.back().cell);
	}

	void toFrame(double time, bool clear=true) override {
		Cell::toFrame(time, clear);
		for (auto &c : items) c.cell->toFrame(time, clear);
	}
	void loopFrame(double loopTime) override {
		Cell::loopFrame(loopTime);
		for (auto &c : items) c.cell->loopFrame(loopTime);
	}
	void clearFrames() override {
		Cell::clearFrames();
		for (auto &c : items) c.cell->clearFrames();
	}
};

class Figure : public Grid {
public:
	PlotStyle style;
	PlotStyle defaultStyle() const override {
		return style;
	}
	
	Figure() : style(Grid::defaultStyle()) {}
};

static double estimateCharWidth(int c) {
	// measured experimentally, covering basic Latin (no accents) and Greek
	if (c >= 32 && c < 127) {
		static char w[95] = {31, 36, 45, 70, 61, 95, 77, 29, 39, 39, 40, 72, 31, 39, 31, 44, 61, 54, 58, 59, 59, 58, 59, 58, 59, 59, 38, 38, 74, 100, 74, 54, 97, 69, 66, 71, 76, 64, 62, 76, 77, 41, 53, 69, 57, 89, 76, 78, 63, 80, 68, 64, 62, 75, 67, 96, 69, 64, 64, 41, 46, 41, 68, 59, 54, 57, 59, 52, 59, 56, 38, 58, 58, 29, 33, 53, 30, 87, 58, 57, 59, 59, 43, 49, 38, 58, 53, 77, 54, 53, 50, 47, 46, 47, 69};
		return w[c - 32]*0.01;
	} else if (c == 168) {
		return 0.53;
	} else if (c == 183) {
		return 0.33;
	} else if (c == 697) {
		return 0.26;
	} else if (c >= 880 && c < 884) {
		static char w[4] = {42, 31, 64, 52};
		return w[c - 880]*0.01;
	} else if (c >= 885 && c < 888) {
		static char w[3] = {40, 66, 48};
		return w[c - 885]*0.01;
	} else if (c >= 890 && c < 894) {
		static char w[4] = {33, 52, 52, 52};
		return w[c - 890]*0.01;
	} else if (c == 895) {
		return 0.33;
	} else if (c == 900) {
		return 0.52;
	} else if (c >= 913 && c < 930) {
		static char w[17] = {75, 71, 63, 73, 71, 71, 82, 82, 45, 77, 75, 94, 81, 70, 83, 85, 67};
		return w[c - 913]*0.01;
	} else if (c >= 931 && c < 938) {
		static char w[7] = {69, 65, 70, 82, 80, 85, 84};
		return w[c - 931]*0.01;
	} else if (c >= 945 && c < 970) {
		static char w[25] = {61, 58, 57, 57, 49, 50, 58, 60, 29, 57, 55, 59, 53, 51, 57, 63, 59, 50, 59, 48, 58, 72, 56, 76, 76};
		return w[c - 945]*0.01;
	} else if (c >= 975 && c < 979) {
		static char w[4] = {47, 66, 74, 66};
		return w[c - 975]*0.01;
	} else if (c >= 981 && c < 1024) {
		static char w[43] = {80, 86, 56, 79, 63, 68, 67, 57, 53, 60, 53, 75, 85, 86, 85, 69, 56, 70, 53, 69, 69, 61, 61, 75, 56, 43, 37, 59, 63, 46, 29, 79, 55, 55, 62, 63, 71, 87, 75, 75, 75, 75, 75};
		return w[c - 981]*0.01;
	} else if (c == 65291) {
		return 1;
	}
	return 0.85;
}

/// Estimates string width encoded with UTF-8
static double estimateUtf8Width(const char *utf8Str) {
	/// TODO: UTF-8 decoding!
	double total = 0;
	while (*utf8Str) {
		total += estimateCharWidth(*utf8Str);
		++utf8Str;
	}
	return total;
}

/// @}
}}; // namespace

#endif // include guard
