/*
 * Copyright (C) 2003-2014, C. Ramakrishnan / Illposed Software.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

import com.illposed.osc.utility.OSCJavaToByteArrayConverter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

/**
 * A bundle represents a collection of OSC packets
 * (either messages or other bundles)
 * and has a time-tag which can be used by a scheduler to execute
 * a bundle in the future,
 * instead of immediately.
 * {@link OSCMessage}s are executed immediately.
 *
 * Bundles should be used if you want to send multiple messages to be executed
 * atomically together, or you want to schedule one or more messages to be
 * executed in the future.
 *
 * @author Chandrasekhar Ramakrishnan
 */
public class OSCBundle extends AbstractOSCPacket {

	/**
	 * 2208988800 seconds -- includes 17 leap years
	 */
	public static final long SECONDS_FROM_1900_TO_1970 = 2208988800L;

	/**
	 * The Java representation of an OSC timestamp with the semantics of
	 * "immediately".
	 */
	public static final Date TIMESTAMP_IMMEDIATE = new Date(0);

	private Date timestamp;
	private List<OSCPacket> packets;

	/**
	 * Create a new empty OSCBundle with a timestamp of immediately.
	 * You can add packets to the bundle with addPacket()
	 */
	public OSCBundle() {
		this(TIMESTAMP_IMMEDIATE);
	}

	/**
	 * Create an OSCBundle with the specified timestamp.
	 * @param timestamp the time to execute the bundle
	 */
	public OSCBundle(Date timestamp) {
		this(null, timestamp);
	}

	/**
	 * Creates an OSCBundle made up of the given packets
	 * with a timestamp of now.
	 * @param packets array of OSCPackets to initialize this object with
	 */
	public OSCBundle(Collection<OSCPacket> packets) {
		this(packets, TIMESTAMP_IMMEDIATE);
	}

	/**
	 * Create an OSCBundle, specifying the packets and timestamp.
	 * @param packets the packets that make up the bundle
	 * @param timestamp the time to execute the bundle
	 */
	public OSCBundle(Collection<OSCPacket> packets, Date timestamp) {

		if (null == packets) {
			this.packets = new LinkedList<OSCPacket>();
		} else {
			this.packets = new ArrayList<OSCPacket>(packets);
		}
		this.timestamp = clone(timestamp);
	}

	private static Date clone(final Date toBeCloned) {
		return (toBeCloned == null) ? toBeCloned : (Date) toBeCloned.clone();
	}

	/**
	 * Return the time the bundle will execute.
	 * @return a Date
	 */
	public Date getTimestamp() {
		return clone(timestamp);
	}

	/**
	 * Set the time the bundle will execute.
	 * @param timestamp Date
	 */
	public void setTimestamp(Date timestamp) {
		this.timestamp = clone(timestamp);
	}

	/**
	 * Add a packet to the list of packets in this bundle.
	 * @param packet OSCMessage or OSCBundle
	 */
	public void addPacket(OSCPacket packet) {
		packets.add(packet);
		contentChanged();
	}

	/**
	 * Get the packets contained in this bundle.
	 * @return the packets contained in this bundle.
	 */
	public List<OSCPacket> getPackets() {
		return Collections.unmodifiableList(packets);
	}

	/**
	 * Convert the time-tag (a Java Date) into the OSC byte stream.
	 * Used Internally.
	 * @param stream where to write the time-tag to
	 */
	private void computeTimeTagByteArray(OSCJavaToByteArrayConverter stream) {
		if ((null == timestamp) || (timestamp.equals(TIMESTAMP_IMMEDIATE))) {
			stream.write((int) 0);
			stream.write((int) 1);
			return;
		}

		final long millisecs = timestamp.getTime();
		final long secsSince1970 = (long) (millisecs / 1000);
		final long secs = secsSince1970 + SECONDS_FROM_1900_TO_1970;

		// this line was cribbed from jakarta commons-net's NTP TimeStamp code
		final long fraction = ((millisecs % 1000) * 0x100000000L) / 1000;

		stream.write((int) secs);
		stream.write((int) fraction);
	}

	@Override
	protected byte[] computeByteArray(OSCJavaToByteArrayConverter stream) {
		stream.write("#bundle");
		computeTimeTagByteArray(stream);
		byte[] packetBytes;
		for (final OSCPacket pkg : packets) {
			packetBytes = pkg.getByteArray();
			stream.write(packetBytes);
		}
		return stream.toByteArray();
	}
}
