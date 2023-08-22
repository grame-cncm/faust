/** Signalsmith's Basic C++ Plots - https://signalsmith-audio.co.uk/code/plot/
@copyright Licensed as 0BSD.  If you need anything else, get in touch. */

#ifndef SIGNALSMITH_PNG_HEAT_MAP_H
#define SIGNALSMITH_PNG_HEAT_MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <sstream>

#include "./plot.h"

namespace signalsmith { namespace plot {

/**	@defgroup Heat-Map PNG Heat-Maps
	@brief Bitmap heat-maps saved as PNGs
	
	This is an optional module, allowing you to add pixel-based heat-maps to your plots.  You create a heat-map, change its `.scale` (which is an `Axis`) and values:

	\code{.cpp}
		signalsmith::plot::HeatMap heatMap(width, height);
		heatMap.scale.linear(-10, 10); // dark to light

		// Access/modify pixels
		heatMap(x, y) = 5;

		heatMap.write("out.png");
	\endcode
	
	You can add it to an existing `Plot2D`:
	
	\code{.cpp}
		// Takes up the entire plot by default, vertically flipped by default
		heatMap.addTo(plot);

		// You can also give it a specific position and size
		heatMap.addTo(plot, {leftX, rightX, topX, bottomX});
	\endcode
	
	You can pass in a second `Plot2D`, which will be taken over as a "scale" plot, including any ticks/label from `heatMap.scale`:

	\code{.cpp}
		signalsmith::plot::Figure grid;

		auto &plot = grid(0, 0).plot(200, 200);
		auto &scalePlot = grid(1, 0).plot(20, 200);
		heatMap.addTo(plot, scalePlot);
	\endcode

	You can also add it to a `Grid` (e.g. a `Figure`), which will create two sub-plots (data and scale).  All `.addTo()` methods return the data plot, so you can inline things a bit:

	\code{.cpp}
		signalsmith::plot::Figure figure;
		auto &plot = heatMap.addTo(figure, 200, 200);
	\endcode

	@{
	@file
**/

/** Pixel-based heat-map
 
	You create this separately, and then attach to a `Figure` or `Plot` later, or save directly to PNG.
 */
struct HeatMap {
	HeatMap(int width, int height, bool flipped=false) : HeatMap(width, height, width, height, flipped) {}
	HeatMap(int width, int height, int outputWidth, int outputHeight, bool flipped=false) : scale(flipped, !flipped), width(width), height(height), outputWidth(outputWidth), outputHeight(outputHeight) {
		unitValues.assign(width*height, 0);
	}
	
	Axis scale;
	
	void write(std::string pngFile) {
		renderBytes();
		
		std::ofstream output(pngFile);
		output.write((char *)pngBytes.data(), pngBytes.size());
	}
	
	std::string dataUrl() {
		renderBytes();

		const char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		std::stringstream str;
		str << "data:image/png;base64,";
		int toEncode = 0, bitsRemaining = 0;
		for (size_t b = 0; b < pngBytes.size(); ++b) {
			toEncode = toEncode*256 + pngBytes[b];
			bitsRemaining += 8;
			while (bitsRemaining >= 6) {
				bitsRemaining -= 6;
				str << base64[(toEncode>>bitsRemaining)&63];
			}
		}
		if (bitsRemaining > 0) {
			toEncode = toEncode<<(6 - bitsRemaining);
			str << base64[toEncode&63];
		}
		return str.str();
	}
	
	double & operator()(int x, int y) {
		if (x < 0 || x >= width || y < 0 || y >= height) return dummyValue;
		return unitValues[x + y*width];
	}
	const double & operator()(int x, int y) const {
		if (x < 0 || x >= width || y < 0 || y >= height) return dummyValue;
		return unitValues[x + y*width];
	}

	struct EmbeddedHeatMap : public SvgDrawable {
		EmbeddedHeatMap(HeatMap &heatMap, Axis &x, Axis &y, bool flippedY=true) : heatMap(heatMap), x(x), y(y), flippedY(flippedY), fullBounds(true) {}
		EmbeddedHeatMap(HeatMap &heatMap, Axis &x, Axis &y, Bounds dataBounds) : heatMap(heatMap), x(x), y(y), dataBounds(dataBounds) {
			x.autoValue(dataBounds.left);
			x.autoValue(dataBounds.right);
			y.autoValue(dataBounds.top);
			y.autoValue(dataBounds.bottom);
		}

		void writeData(SvgWriter &svg, const PlotStyle &style) override {
			SvgDrawable::writeData(svg, style);
			double drawLeft = fullBounds ? x.drawMin() : x.map(dataBounds.left);
			double drawRight = fullBounds ? x.drawMax() : x.map(dataBounds.right);
			double drawTop = fullBounds ? y.drawMin() : y.map(dataBounds.top);
			double drawBottom = fullBounds ? y.drawMax() : y.map(dataBounds.bottom);
			if (flippedY) std::swap(drawTop, drawBottom);

			svg.tag("image", true).attr("width", 1).attr("height", 1)
				.attr("transform", "translate(", drawLeft, ",", drawTop, ")scale(", drawRight - drawLeft, ",", drawBottom - drawTop, ")")
				.attr("preserveAspectRatio", "none").attr("href", heatMap.dataUrl());
		}
	private:
		HeatMap &heatMap;
		Axis &x, &y;
		bool flippedY = true, fullBounds = false;
		Bounds dataBounds;
	};

	Plot2D & addTo(Plot2D &plot, Bounds dataBounds) {
		auto *embedded = new EmbeddedHeatMap(*this, plot.x, plot.y, dataBounds);
		plot.addChild(embedded);
		return plot;
	}

	Plot2D & addTo(Plot2D &plot, Bounds dataBounds, Plot2D &scalePlot) {
		auto *embedded = new EmbeddedHeatMap(*this, plot.x, plot.y, dataBounds);
		plot.addChild(embedded);
		addToScalePlot(scalePlot);
		return plot;
	}

	Plot2D & addTo(Plot2D &plot, bool flippedY=true) {
		auto *embedded = new EmbeddedHeatMap(*this, plot.x, plot.y, flippedY);
		plot.addChild(embedded);
		return plot;
	}

	Plot2D & addTo(Plot2D &plot, Plot2D &scalePlot, bool flippedY=true) {
		auto *embedded = new EmbeddedHeatMap(*this, plot.x, plot.y, flippedY);
		plot.addChild(embedded);
		addToScalePlot(scalePlot);
		return plot;
	}

	/// Adds data and scale plots to a grid (e.g. a figure), returning the data plot
	Plot2D & addTo(Grid &grid, double width, double height, double scaleWidth=15) {
		return addTo(grid(0, 0).plot(width, height), grid(1, 0).plot(scaleWidth, height));
	}

private:
	void addToScalePlot(Plot2D &scalePlot) {
		struct RetainedMap : public SvgDrawable {
			RetainedMap(HeatMap *map) : map(map) {}
			std::unique_ptr<HeatMap> map;
		};

		// Create and retain a colour map image
		auto *scaleMap = new HeatMap(1, 256);
		for (int y = 0; y < 256; ++y) (*scaleMap)(0, y) = y/255.0;
		scalePlot.addChild(new RetainedMap(scaleMap));

		auto *embeddedScale = new EmbeddedHeatMap(*scaleMap, scalePlot.x, scalePlot.y);
		scalePlot.addChild(embeddedScale);
		scalePlot.y.linkFrom(scale).flip();
	}

	int width, height, outputWidth, outputHeight;
	std::vector<double> unitValues;
	double dummyValue;
	
	void colourMap(double v, uint8_t *rgb) {
		// RGB-packed colour map
		double rgb1[51] = {0,0,0,0.1,0.1,0.08,0.204,0.1561,0.1154,0.3303,0.1489,0.132,0.4903,0.1289,0.1412,0.5584,0.15,0.2393,0.552,0.188,0.5,0.4351,0.2853,0.6354,0.3264,0.3979,0.7697,0.1107,0.5283,0.8896,0,0.604,0.9378,0.0606,0.7257,0.5554,0.2485,0.8033,0.137,0.6381,0.8057,0.0459,1,0.7994,0,1,0.9264,0.4412,1,1,1};
		v *= (5 - v)/4; // warp the scale slightly, since our colour-map skews dark
		
		double index = v*16;
		int lowIndex = std::min(std::floor(index), 15.0);
		double rH = (index - lowIndex), rL = 1 - rH;
		
		double *rgbLow = rgb1 + 3*lowIndex;
		for (int c = 0; c < 3; ++c) {
			rgb[c] = std::round(255*std::sqrt(rgbLow[c]*rgbLow[c]*rL + rgbLow[c + 3]*rgbLow[c + 3]*rH));
		}
		return;
	}

	// PNG file contents
	std::vector<uint8_t> pngBytes;
	void renderBytes() {
		double scaleX = outputWidth > 1 ? (width - 1.0)/(outputWidth - 1.0) : (width - 1.0);
		double scaleY = outputHeight > 1 ? (height - 1.0)/(outputHeight - 1.0) : (height - 1.0);
		auto getScaledPixel = [&](int outX, int outY) {
			double scaledSum = 0, counter = 0;
			double inX = outX*scaleX;
			double inY = outY*scaleY;
			// Bidirectional interpolation, scaling up or down
			double spanX = std::max(1.0, scaleX), spanY = std::max(1.0, scaleY);
			for (int x = std::max<int>(0, std::ceil(inX - spanX)); x < std::min<int>(width, std::floor(inX + spanX)); ++x) {
				double wx = 1 - std::abs(x - inX)/spanX;
				wx *= wx*(3 - 2*wx);
				for (int y = std::max<int>(0, std::ceil(inY - spanY)); y < std::min<int>(height, std::floor(inY + spanY)); ++y) {
					double wy = 1 - std::abs(y - inY)/spanY;
					wy *= wy*(3 - 2*wy);
					double w = wx*wy;
					double v = std::max(0.0, std::min(1.0, scale.map((*this)(x, y))));
					scaledSum += v*w;
					counter += w;
				}
			}
			return scaledSum/counter;
		};
	
		pngBytes.resize(0);
		addBytes("\x89PNG\x0D\x0A\x1A\x0A", 8);
		startChunk("IHDR").addInt32(outputWidth).addInt32(outputHeight);
		// 8-bits, palette, compression=0=DEFLATE, filter=0=per-scanline, interlace=0
		addBytes("\x08\x03\x00\x00\x00", 5).endChunk();

		startChunk("PLTE");
		unsigned char rgb[3];
		for (int i = 0; i < 256; ++i) {
			colourMap(i/255.0, rgb);
			addBytes((char *)rgb, 3);
		}
		endChunk();

		// Image data
		startChunk("IDAT").startDeflate();
		std::vector<unsigned char> rowBytes(outputWidth + 1), prevBytes(outputWidth + 1);
		rowBytes[0] = 3; // "average" filter (left and up)
		for (int y = 0; y < outputHeight; ++y) {
			uint8_t leftByte = 0;
			double remainder = 0;
			for (int x = 0; x < outputWidth; ++x) {
				double v = getScaledPixel(x, y)*255 + remainder;
				int v8 = std::round(v);
				remainder = v - v8; // simple dither
				uint8_t byte = std::max(0, std::min(255, v8));
				uint8_t predicted = (leftByte + prevBytes[x + 1])/2;
				rowBytes[x + 1] = (byte - predicted);
				leftByte = prevBytes[x + 1] = byte;
			}
			deflate(rowBytes.data(), rowBytes.size(), y == outputHeight - 1);
		}
		endDeflate().endChunk();
		startChunk("IEND").endChunk();
	}
	
	HeatMap & addBytes(const char* cStr, int bytes) {
		for (int i = 0; i < bytes; ++i) pngBytes.push_back(cStr[i]);
		return *this;
	}
	HeatMap & addInt(uint32_t value, int bytes, bool bigEndian=true) {
		size_t index = pngBytes.size();
		pngBytes.resize(index + bytes);
		return writeInt(value, bytes, index, bigEndian);
	}
	HeatMap & writeInt(uint32_t value, int bytes, int startIndex, bool bigEndian=true) {
		for (int i = 0; i < bytes; ++i) {
			uint8_t byte = (value >> (i*8))&0xff;
			int index = bigEndian ? (startIndex + bytes - 1 - i) : (startIndex + i);
			pngBytes[index] = byte;
		}
		return *this;
	}
	HeatMap & addInt32(uint32_t value, bool bigEndian=true) {
		return addInt(value, 4, bigEndian);
	}
	size_t chunkStartIndex = 0;
	HeatMap & startChunk(const char *key) {
		chunkStartIndex = pngBytes.size();
		addInt32(0); // this will be replaced by the size later
		addBytes(key, 4);
		return *this;
	}
	void endChunk() {
		uint32_t size = pngBytes.size() - chunkStartIndex - 8;
		writeInt(size, 4, chunkStartIndex);

		// CRC-32
		size_t crcStart = chunkStartIndex + 4;
		uint32_t crc = 0xFFFFFFFFu;
		for (size_t b = crcStart; b < pngBytes.size(); ++b) {
			uint8_t byte = pngBytes[b];
			uint32_t val = (crc^byte)&0xFF;
			for (int i = 0; i < 8; ++i) {
				val = (val&1) ? (val>>1)^0xEDB88320 : (val>>1);
			}
			crc = val^(crc>>8);
		}
		addInt32(crc^0xFFFFFFFF);
	}
	uint32_t adlerA, adlerB;
	void startDeflate() {
		addBytes("\x78\x01", 2); // zlib header
		adlerA = 1;
		adlerB = 0;
	}
	uint32_t pending = 0, pendingBits = 0;
	void writeCode(uint32_t v, int bits, bool flipped=true) {
		// DEFLATE codes are written MSB first, so we flip all the codes around
		for (int b = 0; b < bits; ++b) {
			int b2 = flipped ? (bits - 1 - b) : b;
			pending |= ((v>>b2)&1)<<pendingBits;
			++pendingBits;
		}
		while (pendingBits >= 8) {
			pngBytes.push_back(pending&0xff);
			pending = pending>>8;
			pendingBits -= 8;
		}
	}
	void deflate(const unsigned char *block, int length, bool isFinal) {
		for (int i = 0; i < length; ++i) {
			uint32_t c = block[i];
			adlerA = (adlerA + c)%65521;
			adlerB = (adlerB + adlerA)%65521;
		}

		writeCode(2 + isFinal, 3, false); // fixed-code Huffman, with final-block flag
		// Very limited search for repeating sections
		int writeIndex = 0;
		while (writeIndex < length) {
			int bestDistance = 0, bestLength = 1;
			for (int d = 1; d <= 4 && d < writeIndex; ++d) {
				int sequenceLength = 0;
				while (writeIndex + sequenceLength < length && sequenceLength < 18) {
					int sourceIndex = writeIndex - d + (sequenceLength%d);
					if (block[writeIndex + sequenceLength] != block[sourceIndex]) break;
					++sequenceLength;
				}
				if (sequenceLength > bestLength) {
					bestLength = sequenceLength;
					bestDistance = d;
				}
			}
			if (bestLength >= 3) {
				if (bestLength <= 10) {
					writeCode(bestLength - 2, 7);
				} else { // we limit the sequences to 18
					int extra = (bestLength - 11);
					writeCode(9 + extra/2, 7);
					writeCode(extra, 1);
				}
				writeCode(bestDistance - 1, 5); // no extra bits, because we only searched 4 back
				writeIndex += bestLength;
			} else { // literals in DEFLATE's fixed Huffman
				uint32_t c = block[writeIndex];
				if (c <= 143) {
					writeCode(c + 48, 8);
				} else {
					writeCode(c + 0x100, 9);
				}
				++writeIndex;
			}
		}
		writeCode(0, 7); // end-of-block code
	}
	HeatMap & endDeflate() {
		if (pendingBits) writeCode(0, 8 - pendingBits);
		return addInt32(adlerA + adlerB*65536);
	}
};

/// @}
}} // namespace
#endif // include guard
