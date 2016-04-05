/*
 * Copyright (C) 2014, C. Ramakrishnan / Auracle.
 * All rights reserved.
 *
 * This code is licensed under the BSD 3-Clause license.
 * See file LICENSE (or LICENSE.html) for more information.
 */

package com.illposed.osc.utility;

import com.illposed.osc.AddressSelector;
import java.util.regex.Pattern;

/**
 * Checks whether an OSC <i>Address Pattern</i> matches a given
 * Java regular expression.
 */
public class JavaRegexAddressSelector implements AddressSelector {

	private final Pattern selector;

	public JavaRegexAddressSelector(Pattern selector) {
		this.selector = selector;
	}

	public JavaRegexAddressSelector(String selectorRegex) {
		this(Pattern.compile(selectorRegex));
	}

	@Override
	public boolean matches(String messageAddress) {
		return selector.matcher(messageAddress).matches();
	}
}
