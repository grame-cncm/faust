/*
 * Copyright (C) 2003-2014, C. Ramakrishnan / Illposed Software.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

import java.util.Date;

/**
 * Allows to listen to incoming messages that match some selector pattern.
 * In OSC speak, this is a <i>Method</i>, and it listens to <i>Messages</i>.
 *
 * @author Chandrasekhar Ramakrishnan
 */
public interface OSCListener {

	/**
	 * Process a matching, incoming OSC Message.
	 * @param time     The time this message is to be executed.
	 *   <code>null</code> means: process immediately
	 * @param message  The message to process.
	 */
	void acceptMessage(Date time, OSCMessage message);
}
