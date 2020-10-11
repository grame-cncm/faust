

jssrc := $(wildcard src/*.ts)

all: 
	make -C .. wasmlib
	cp ../lib/libfaust-wasm.* npm/dist
	[ -e tests/libfaust-wasm.data ] || (cd tests && ln -s ../npm/dist/libfaust-wasm.data .)
	make js

js: faustwebaudio.js faustcompiler.js

faustwebaudio.js : $(jssrc)
	tsc --strict --strictNullChecks --noImplicitAny --strictFunctionTypes --noImplicitThis --alwaysStrict --noImplicitReturns --noFallthroughCasesInSwitch    

faustcompiler.js : src/FaustCompiler.d.ts src/FaustCompiler.ts src/libfaust.d.ts
	tsc -p tsCompiler.json

clean:
	make -C ../faustdir/emcc clean

cmake:
	make -C .. cmake

test:
	echo $(jssrc)