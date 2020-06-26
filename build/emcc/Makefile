

all: 
	make -C .. wasmlib
	cp ../lib/libfaust-wasm.* npm/dist
	[ -e tests/libfaust-wasm.data ] || (cd tests && ln -s ../npm/dist/libfaust-wasm.data .)


