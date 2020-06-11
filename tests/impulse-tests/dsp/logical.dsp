// Test logical operators

land = int(_*12345) & int(_*67895);
lor = int(_*12345) | int(_*67895);
lxor = int(_*12345) xor int(_*67895);

process = land, lor, lxor, select2(land, 100, 200), select2(lor, 10, 20), select2(lxor, 1, 2);
		
