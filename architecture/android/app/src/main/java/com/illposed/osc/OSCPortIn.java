/*
 * Copyright (C) 2004-2014, C. Ramakrishnan / Illposed Software.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

import com.illposed.osc.utility.OSCByteArrayToJavaConverter;
import com.illposed.osc.utility.OSCPacketDispatcher;
import com.illposed.osc.utility.OSCPatternAddressSelector;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.Charset;

/**
 * OSCPortIn is the class that listens for OSC messages.
 *
 * An example:<br>
 * (loosely based on {com.illposed.osc.OSCPortTest#testReceiving()})
 * <blockquote><pre>{@code
 * receiver = new OSCPortIn(OSCPort.DEFAULT_SC_OSC_PORT());
 * OSCListener listener = new OSCListener() {
 * 	public void acceptMessage(java.util.Date time, OSCMessage message) {
 * 		System.out.println("Message received!");
 * 	}
 * };
 * receiver.addListener("/message/receiving", listener);
 * receiver.startListening();
 * }</pre></blockquote>
 *
 * Then, using a program such as SuperCollider or sendOSC, send a message
 * to this computer, port {@link #DEFAULT_SC_OSC_PORT},
 * with the address "/message/receiving".
 *
 * @author Chandrasekhar Ramakrishnan
 */
public class OSCPortIn extends OSCPort implements Runnable {

	/**
	 * Buffers were 1500 bytes in size, but were
	 * increased to 1536, as this is a common MTU.
	 */
	private static final int BUFFER_SIZE = 1536;

	/** state for listening */
	private boolean listening;
	private final OSCByteArrayToJavaConverter converter;
	private final OSCPacketDispatcher dispatcher;

	/**
	 * Create an OSCPort that listens using a specified socket.
	 * @param socket DatagramSocket to listen on.
	 */
	public OSCPortIn(DatagramSocket socket) {
		super(socket, socket.getLocalPort());

		this.converter = new OSCByteArrayToJavaConverter();
		this.dispatcher = new OSCPacketDispatcher();
	}

	/**
	 * Create an OSCPort that listens on the specified port.
	 * Strings will be decoded using the systems default character set.
	 * @param port UDP port to listen on.
	 * @throws SocketException if the port number is invalid,
	 *   or there is already a socket listening on it
	 */
	public OSCPortIn(int port) throws SocketException {
		this(new DatagramSocket(port));
	}

	/**
	 * Create an OSCPort that listens on the specified port,
	 * and decodes strings with a specific character set.
	 * @param port UDP port to listen on.
	 * @param charset how to decode strings read from incoming packages.
	 *   This includes message addresses and string parameters.
	 * @throws SocketException if the port number is invalid,
	 *   or there is already a socket listening on it
	 */
	public OSCPortIn(int port, Charset charset) throws SocketException {
		this(port);

		this.converter.setCharset(charset);
	}

	/**
	 * Run the loop that listens for OSC on a socket until
	 * {@link #isListening()} becomes false.
	 * @see java.lang.Runnable#run()
	 */
	@Override
	public void run() {
		final byte[] buffer = new byte[BUFFER_SIZE];
		final DatagramPacket packet = new DatagramPacket(buffer, BUFFER_SIZE);
		final DatagramSocket socket = getSocket();
		while (listening) {
			try {
				try {
					socket.receive(packet);
				} catch (SocketException ex) {
					if (listening) {
						throw ex;
					} else {
						// if we closed the socket while receiving data,
						// the exception is expected/normal, so we hide it
						continue;
					}
				}
				final OSCPacket oscPacket = converter.convert(buffer,
						packet.getLength());
				dispatcher.dispatchPacket(oscPacket);
			} catch (IOException ex) {
				ex.printStackTrace(); // XXX This may not be a good idea, as this could easily lead to a never ending series of exceptions thrown (due to the non-exited while loop), and because the user of the lib may want to handle this case himself
			}
		}
	}

	/**
	 * Start listening for incoming OSCPackets
	 */
	public void startListening() {
		listening = true;
		final Thread thread = new Thread(this);
		// The JVM exits when the only threads running are all daemon threads.
		thread.setDaemon(true);
		thread.start();
	}

	/**
	 * Stop listening for incoming OSCPackets
	 */
	public void stopListening() {
		listening = false;
	}

	/**
	 * Am I listening for packets?
	 * @return true if this port is in listening mode
	 */
	public boolean isListening() {
		return listening;
	}

	/**
	 * Registers a listener that will be notified of incoming messages,
	 * if their address matches the given pattern.
	 *
	 * @param addressSelector either a fixed address like "/sc/mixer/volume",
	 *   or a selector pattern (a mix between wildcards and regex)
	 *   like "/??/mixer/*", see {@link OSCPatternAddressSelector} for details
	 * @param listener will be notified of incoming packets, if they match
	 */
	public void addListener(String addressSelector, OSCListener listener) {
		this.addListener(new OSCPatternAddressSelector(addressSelector), listener);
	}

	/**
	 * Registers a listener that will be notified of incoming messages,
	 * if their address matches the given selector.
	 * @param addressSelector a custom address selector
	 * @param listener will be notified of incoming packets, if they match
	 */
	public void addListener(AddressSelector addressSelector, OSCListener listener) {
		dispatcher.addListener(addressSelector, listener);
	}
}
