/*
 * Copyright (C) 2014, C. Ramakrishnan / Auracle.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc;

/**
 * Checks whether an OSC <i>Address Pattern</i> fulfills certain criteria.
 */
public interface AddressSelector {

	/**
	 * Checks whether the OSC <i>Address Pattern</i> in question
	 * matches this selector.
	 * @param messageAddress for example "/sc/mixer/volume"
	 * @return true if this matcher selects the message address in question.
	 */
	boolean matches(String messageAddress);
}
