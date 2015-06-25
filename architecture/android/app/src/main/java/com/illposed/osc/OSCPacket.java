/*
 * Copyright (C) 2003-2014, C. Ramakrishnan / Illposed Software.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

import java.nio.charset.Charset;

/**
 * OSCPacket is the abstract superclass for the various
 * kinds of OSC Messages.
 *
 * The actual packets are:
 * <ul>
 * <li>{@link OSCMessage}: simple OSC messages
 * <li>{@link OSCBundle}: OSC messages with timestamps
 *   and/or made up of multiple messages
 * </ul>
 */
public interface OSCPacket {

	/**
	 * Returns the character set used by this packet.
	 * @return the character set used to encode message addresses and string
	 *   arguments.
	 */
	Charset getCharset();

	/**
	 * Sets the character set used by this packet.
	 * @param charset used to encode message addresses and string arguments.
	 */
	void setCharset(Charset charset);

	/**
	 * Return the OSC byte stream for this packet.
	 * @return byte[]
	 */
	byte[] getByteArray();
}
