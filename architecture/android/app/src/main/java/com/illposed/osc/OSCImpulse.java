/*
 * Copyright (C) 2014, C. Ramakrishnan / Illposed Software.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

/**
 * An OSC 1.0 optional, and OSC 1.1 required argument type.
 * Impulse aka "bang", is used for event triggers.
 * No bytes are allocated in the argument data.
 * This type was named "Infinitum" in OSC 1.0.
 * Use like this:
 * <blockquote><pre>{@code
 * OSCMessage msg = new OSCMessage("/my/address");
 * msg.addArgument(OSCImpulse.INSTANCE);
 * }</pre></blockquote>
 */
public final class OSCImpulse {

	public static final OSCImpulse INSTANCE = new OSCImpulse();

	private OSCImpulse() {}
}
