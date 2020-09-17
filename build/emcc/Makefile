

jssrc := $(wildcard src/*.ts)

all: 
	make -C .. wasmlib
	cp ../lib/libfaust-wasm.* npm/dist
	[ -e tests/libfaust-wasm.data ] || (cd tests && ln -s ../npm/dist/libfaust-wasm.data .)
	make js

js: faustwebaudio.js

faustwebaudio.js : $(jssrc)
	tsc

clean:
	make -C ../faustdir/emcc clean

cmake:
	make -C .. cmake

test:
	echo $(jssrc)