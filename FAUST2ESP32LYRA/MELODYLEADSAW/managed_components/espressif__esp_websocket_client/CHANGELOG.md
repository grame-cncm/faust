# Changelog

## [1.5.0](https://github.com/espressif/esp-protocols/commits/websocket-v1.5.0)

### Features

- add separate tx lock for send and receive ([250eebf](https://github.com/espressif/esp-protocols/commit/250eebf))
- add unregister event to websocket client ([ce16050](https://github.com/espressif/esp-protocols/commit/ce16050))
- add ability to reconnect after close ([19891d8](https://github.com/espressif/esp-protocols/commit/19891d8))

### Bug Fixes

- release client-lock during WEBSOCKET_EVENT_DATA ([030cb75](https://github.com/espressif/esp-protocols/commit/030cb75))

## [1.4.0](https://github.com/espressif/esp-protocols/commits/websocket-v1.4.0)

### Features

- Support DS peripheral for mutual TLS ([55385ec3](https://github.com/espressif/esp-protocols/commit/55385ec3))

### Bug Fixes

- wait for task on destroy ([42674b49](https://github.com/espressif/esp-protocols/commit/42674b49))
- Fix pytest to verify client correctly ([9046af8f](https://github.com/espressif/esp-protocols/commit/9046af8f))
- propagate error type ([eeeb9006](https://github.com/espressif/esp-protocols/commit/eeeb9006))
- fix example buffer leak ([5219c39d](https://github.com/espressif/esp-protocols/commit/5219c39d))

### Updated

- chore(websocket): align structure members ([beb6e57e](https://github.com/espressif/esp-protocols/commit/beb6e57e))
- chore(websocket): remove unused client variable ([15d3a01e](https://github.com/espressif/esp-protocols/commit/15d3a01e))

## [1.3.0](https://github.com/espressif/esp-protocols/commits/websocket-v1.3.0)

### Features

- add events for begin/end thread ([d7fa24bc](https://github.com/espressif/esp-protocols/commit/d7fa24bc))
- Make example to use certificate bundle ([aecf6f80](https://github.com/espressif/esp-protocols/commit/aecf6f80))
- propagate esp_tls stack error and cert verify flags ([234f579b](https://github.com/espressif/esp-protocols/commit/234f579b))
- Add option to set and use cert_common_name in Websocket client ([3a6720de](https://github.com/espressif/esp-protocols/commit/3a6720de))
- adding support for `if_name` when using WSS transport ([333a6893](https://github.com/espressif/esp-protocols/commit/333a6893))
- allow updating reconnect timeout for retry backoffs ([bd9f0627](https://github.com/espressif/esp-protocols/commit/bd9f0627))
- allow using external tcp transport handle ([83ea2876](https://github.com/espressif/esp-protocols/commit/83ea2876))
- adding support for `keep_alive_enable` when using WSS transport ([c728eae5](https://github.com/espressif/esp-protocols/commit/c728eae5))

### Bug Fixes

- Prevent crash on network disconnect during send ([a453ca1f](https://github.com/espressif/esp-protocols/commit/a453ca1f))
- use proper interface to delete semaphore ([991ac40d](https://github.com/espressif/esp-protocols/commit/991ac40d))
- Move client to different state when disconnecting ([0d8f2a6d](https://github.com/espressif/esp-protocols/commit/0d8f2a6d))
- fix of websocket host example ([5ccc018a](https://github.com/espressif/esp-protocols/commit/5ccc018a))
- don't get transport from the list if external transport is used ([9d4d5d2d](https://github.com/espressif/esp-protocols/commit/9d4d5d2d))
- Fix locking issues of `esp_websocket_client_send_with_exact_opcode` API ([6393fcd7](https://github.com/espressif/esp-protocols/commit/6393fcd7))

## [1.2.3](https://github.com/espressif/esp-protocols/commits/websocket-v1.2.3)

### Features

- Expanded example to demonstrate the transfer over TLS ([0d0630ed76](https://github.com/espressif/esp-protocols/commit/0d0630ed76))

### Bug Fixes

- fix esp_event dependency management ([1fb02a9a60](https://github.com/espressif/esp-protocols/commit/1fb02a9a60))
- Skip warn on zero timeout and auto reconnect is disabled ([5b467cbf5c](https://github.com/espressif/esp-protocols/commit/5b467cbf5c))
- Fixed to use int return value in Tx functions ([9c54b72e1f](https://github.com/espressif/esp-protocols/commit/9c54b72e1f))
- Fixed Tx functions with DYNAMIC_BUFFER ([16174470ee](https://github.com/espressif/esp-protocols/commit/16174470ee))
- added dependency checks, sdkconfig.defaults and refined README.md ([312982e4aa](https://github.com/espressif/esp-protocols/commit/312982e4aa))
- Close websocket and dispatch event if server does not close within a reasonable amount of time. ([d85311880d](https://github.com/espressif/esp-protocols/commit/d85311880d))
- Continue waiting for TCP connection to be closed ([2b092e0db4](https://github.com/espressif/esp-protocols/commit/2b092e0db4))

### Updated

- docs(websocket): Added README for websocket host example ([2f7c58259d](https://github.com/espressif/esp-protocols/commit/2f7c58259d))

## [1.2.2](https://github.com/espressif/esp-protocols/commits/websocket-v1.2.2)

### Bug Fixes

- continuation after FIN in websocket client (#460) ([774d1c75e6](https://github.com/espressif/esp-protocols/commit/774d1c75e6))
- Re-applie refs to common comps idf_component.yml ([9fe44a4504](https://github.com/espressif/esp-protocols/commit/9fe44a4504))

## [1.2.1](https://github.com/espressif/esp-protocols/commits/websocket-v1.2.1)

### Bug Fixes

- consider failure if return value of `esp_websocket_client_send_with_exact_opcode` less than 0 ([f523b4d](https://github.com/espressif/esp-protocols/commit/f523b4d))
- fix of return value for `esp_websocket_client_send_with_opcode` API ([ba33588](https://github.com/espressif/esp-protocols/commit/ba33588))

## [1.2.0](https://github.com/espressif/esp-protocols/commits/websocket-v1.2.0)

### Features

- Added new API `esp_websocket_client_append_header` ([39e9725](https://github.com/espressif/esp-protocols/commit/39e9725))
- Added new APIs to support fragmented messages transmission ([fae80e2](https://github.com/espressif/esp-protocols/commit/fae80e2))

### Bug Fixes

- Reference common component from IDF ([74fc228](https://github.com/espressif/esp-protocols/commit/74fc228))
- Revert referencing protocol_examples_common from IDF ([b176d3a](https://github.com/espressif/esp-protocols/commit/b176d3a))
- reference protocol_examples_common from IDF ([025ede1](https://github.com/espressif/esp-protocols/commit/025ede1))
- specify override_path in example manifests ([d5e7898](https://github.com/espressif/esp-protocols/commit/d5e7898))
- Return status code correctly on esp_websocket_client_send_with_opcode ([ac8f1de](https://github.com/espressif/esp-protocols/commit/ac8f1de))
- Fix pytest exclusion, gitignore, and changelog checks ([2696221](https://github.com/espressif/esp-protocols/commit/2696221))

## [1.1.0](https://github.com/espressif/esp-protocols/commits/websocket-v1.1.0)

### Features

- Added linux port for websocket ([a22391a](https://github.com/espressif/esp-protocols/commit/a22391a))

### Bug Fixes

- added idf_component.yml for examples ([d273e10](https://github.com/espressif/esp-protocols/commit/d273e10))

## [1.0.1](https://github.com/espressif/esp-protocols/commits/websocket-v1.0.1)

### Bug Fixes

- esp_websocket_client client allow sending 0 byte packets ([b5177cb](https://github.com/espressif/esp-protocols/commit/b5177cb))
- Cleaned up printf/format warnings (-Wno-format) ([e085826](https://github.com/espressif/esp-protocols/commit/e085826))
- Added unit tests to CI + minor fix to pass it ([c974c14](https://github.com/espressif/esp-protocols/commit/c974c14))
- Reintroduce missing CHANGELOGs ([200cbb3](https://github.com/espressif/esp-protocols/commit/200cbb3), [#235](https://github.com/espressif/esp-protocols/issues/235))

### Updated

- docs(common): updated component and example links ([f48d9b2](https://github.com/espressif/esp-protocols/commit/f48d9b2))
- docs(common): improving documentation ([ca3fce0](https://github.com/espressif/esp-protocols/commit/ca3fce0))
- Fix weird error message spacings ([8bb207e](https://github.com/espressif/esp-protocols/commit/8bb207e))

## [1.0.0](https://github.com/espressif/esp-protocols/commits/996fef7)

### Updated

- esp_websocket_client: Updated version to 1.0.0 Updated tests to run agains release-v5.0 ([996fef7](https://github.com/espressif/esp-protocols/commit/996fef7))
- esp_websocket_client: * Error handling improved to show status code from server * Added new API `esp_websocket_client_set_headers` * Dispatches 'WEBSOCKET_EVENT_BEFORE_CONNECT' event before tcp connection ([d047ff5](https://github.com/espressif/esp-protocols/commit/d047ff5))
- unite all tags under common structure py test: update tags under common structure ([c6db3ea](https://github.com/espressif/esp-protocols/commit/c6db3ea))
- websocket: Support HTTP basic authorization ([1b13448](https://github.com/espressif/esp-protocols/commit/1b13448))
- Add task_name config option ([1d68884](https://github.com/espressif/esp-protocols/commit/1d68884))
- Add websocket error messages ([d68624e](https://github.com/espressif/esp-protocols/commit/d68624e))
- websocket: Added new API `esp_websocket_client_destroy_on_exit` ([f9b4790](https://github.com/espressif/esp-protocols/commit/f9b4790))
- Added badges with version of components to the respective README files ([e4c8a59](https://github.com/espressif/esp-protocols/commit/e4c8a59))


## [0.0.4](https://github.com/espressif/esp-protocols/commits/3330b96)

### Updated

- websocket: make `esp_websocket_client_send_with_opcode` a public API ([3330b96](https://github.com/espressif/esp-protocols/commit/3330b96))
- websocket: updated example to use local websocket echo server ([55dc564](https://github.com/espressif/esp-protocols/commit/55dc564))
- CI: Created a common requirements.txt ([23a537b](https://github.com/espressif/esp-protocols/commit/23a537b))
- Examples: using pytest.ini from top level directory ([aee016d](https://github.com/espressif/esp-protocols/commit/aee016d))
- CI: fixing the files to be complient with pre-commit hooks ([945bd17](https://github.com/espressif/esp-protocols/commit/945bd17))
- websocket: updated example to show json data transfer ([3456781](https://github.com/espressif/esp-protocols/commit/3456781))


## [0.0.3](https://github.com/espressif/esp-protocols/commits/5c245db)

### Updated

- esp_websocket_client: Upgraded version to 0.0.3 ([5c245db](https://github.com/espressif/esp-protocols/commit/5c245db))
- CI: Fix build issues ([6e4e4fa](https://github.com/espressif/esp-protocols/commit/6e4e4fa))


## [0.0.2](https://github.com/espressif/esp-protocols/commits/57afa38)

### Features

- Optimize memory size for websocket client init ([4cefcd3](https://github.com/espressif/esp-protocols/commit/4cefcd3))
- allow users to attach CA bundle ([d56b5d9](https://github.com/espressif/esp-protocols/commit/d56b5d9))

### Bug Fixes

- Docs to refer esp-protocols ([91a177e](https://github.com/espressif/esp-protocols/commit/91a177e))

### Updated

- Bump asio/mdns/esp_websocket_client versions ([57afa38](https://github.com/espressif/esp-protocols/commit/57afa38))
- ignore format warnings ([d66f9dc](https://github.com/espressif/esp-protocols/commit/d66f9dc))
- Minor fixes here and there ([8fe2a3a](https://github.com/espressif/esp-protocols/commit/8fe2a3a))
- CI: Added CI example run job ([76298ff](https://github.com/espressif/esp-protocols/commit/76298ff))
- Implement websocket client connect error ([9e37f53](https://github.com/espressif/esp-protocols/commit/9e37f53))
- Add methods to allow get/set of websocket client ping interval ([e55f54b](https://github.com/espressif/esp-protocols/commit/e55f54b))
- esp_websocket_client: Expose frame fin flag in websocket event ([b72a9ae](https://github.com/espressif/esp-protocols/commit/b72a9ae))


## [0.0.1](https://github.com/espressif/esp-protocols/commits/80c3cf0)

### Updated

- websocket: Initial version based on IDF 5.0 ([80c3cf0](https://github.com/espressif/esp-protocols/commit/80c3cf0))
- freertos: Remove legacy data types ([b3c777a](https://github.com/espressif/esp-protocols/commit/b3c777a), [IDF@57fd78f](https://github.com/espressif/esp-idf/commit/57fd78f5baf93a368a82cf4b2e00ca17ffc09115))
- websocket: Added configs `reconnect_timeout_ms` and `network_timeout_ms` ([8ce791e](https://github.com/espressif/esp-protocols/commit/8ce791e), [IDF#8263](https://github.com/espressif/esp-idf/issues/8263), [IDF@6c26d65](https://github.com/espressif/esp-idf/commit/6c26d6520311f83c2ebe852a487c36185a429a69))
- Add http_parser (new component) dependency ([bece6e7](https://github.com/espressif/esp-protocols/commit/bece6e7), [IDF@8e94cf2](https://github.com/espressif/esp-idf/commit/8e94cf2bb1498e94045e73e649f1046111fc6f9f))
- websocket: removed deprecated API "esp_websocket_client_send" ([46bd32d](https://github.com/espressif/esp-protocols/commit/46bd32d), [IDF@7f6ab93](https://github.com/espressif/esp-idf/commit/7f6ab93f7e52bddaf4c030d7337ea5574f33381d))
- refactor (test_utils)!: separate file for memory check functions ([525c70c](https://github.com/espressif/esp-protocols/commit/525c70c), [IDF@16514f9](https://github.com/espressif/esp-idf/commit/16514f93f06cd833306459d615458536a9f2e5cd))
- Build & config: Remove leftover files from the unsupported "make" build system ([19c0455](https://github.com/espressif/esp-protocols/commit/19c0455), [IDF@766aa57](https://github.com/espressif/esp-idf/commit/766aa5708443099f3f033b739cda0e1de101cca6))
- transport: Add CONFI_WS_TRANSPORT for optimize the code size ([9118e0f](https://github.com/espressif/esp-protocols/commit/9118e0f), [IDF@8b02c90](https://github.com/espressif/esp-idf/commit/8b02c9026af32352c8c4ed23025fb42182db6cae))
- ws_client: Fix const correctness in the API config structure ([fbdbd55](https://github.com/espressif/esp-protocols/commit/fbdbd55), [IDF@70b1247](https://github.com/espressif/esp-idf/commit/70b1247a47f4583fccd8a91bf6cc532e5741e632))
- components: Remove repeated keep alive function by ssl layer function ([de7cd72](https://github.com/espressif/esp-protocols/commit/de7cd72), [IDF@c79a907](https://github.com/espressif/esp-idf/commit/c79a907e4fef0c54175ad5659bc0df45a40745c9))
- components: Support bind socket to specified interface in esp_http_client and esp_websocket_client component ([4a608ec](https://github.com/espressif/esp-protocols/commit/4a608ec), [IDF@bead359](https://github.com/espressif/esp-idf/commit/bead3599abd875d746e64cd6749574ff2c155adb))
- esp_websocket_client: Don't log the filename when logging "Websocket already stop" ([f0351ff](https://github.com/espressif/esp-protocols/commit/f0351ff), [IDF@10bde42](https://github.com/espressif/esp-idf/commit/10bde42551b479bd4bfccc9d3c6d983f8abe0b87))
- websocket: Add websocket unit tests ([9219ff7](https://github.com/espressif/esp-protocols/commit/9219ff7), [IDF@cd01a0c](https://github.com/espressif/esp-idf/commit/cd01a0ca81ef2ba5648fd7712c9bf45bbf252339))
- websockets: Set keepalive options after adding transport to the list ([86aa0b8](https://github.com/espressif/esp-protocols/commit/86aa0b8), [IDF@99805d8](https://github.com/espressif/esp-idf/commit/99805d880f41857702b3bbb35bc0dfaf7dec3aec))
- websocket: Add configurable ping interval ([1933367](https://github.com/espressif/esp-protocols/commit/1933367), [IDF@9ff9137](https://github.com/espressif/esp-idf/commit/9ff9137e7a8b64e956c1c63e95a48f4049ad571e))
- ws_transport: Add option to propagate control packets to the app ([95cf983](https://github.com/espressif/esp-protocols/commit/95cf983), [IDF#6307](https://github.com/espressif/esp-idf/issues/6307), [IDF@acc7bd2](https://github.com/espressif/esp-idf/commit/acc7bd2ca45c21033cbd02220a27c3c1ecdd5ad0))
- Add options for esp_http_client and esp_websocket_client to support keepalive ([8a6c320](https://github.com/espressif/esp-protocols/commit/8a6c320), [IDF@b53e46a](https://github.com/espressif/esp-idf/commit/b53e46a68e8671c73e8aafe2602de5ff5a77e3db))
- websocket: support mutual tls for websocket Closes https://github.com/espressif/esp-idf/issues/6059 ([d1dd6ec](https://github.com/espressif/esp-protocols/commit/d1dd6ec), [IDF#6059](https://github.com/espressif/esp-idf/issues/6059), [IDF@5ab774f](https://github.com/espressif/esp-idf/commit/5ab774f9d8e119fff56b566fa2f9bdad853bf701))
- Whitespace: Automated whitespace fixes (large commit) ([d376480](https://github.com/espressif/esp-protocols/commit/d376480), [IDF@66fb5a2](https://github.com/espressif/esp-idf/commit/66fb5a29bbdc2482d67c52e6f66b303378c9b789))
- Websocket client: avoid deadlock if stop called from event handler ([e90272c](https://github.com/espressif/esp-protocols/commit/e90272c), [IDF@c2bb076](https://github.com/espressif/esp-idf/commit/c2bb0762bb5c24cb170bc9c96fdadb86ae2f06e7))
- tcp_transport: Added internal API for underlying socket, used for custom select on connection end for WS ([6d12d06](https://github.com/espressif/esp-protocols/commit/6d12d06), [IDF@5e9f8b5](https://github.com/espressif/esp-idf/commit/5e9f8b52e7a87371370205a387b2d94e5ac6cbf9))
- ws_client: Added support for close frame, closing connection gracefully ([1455bc0](https://github.com/espressif/esp-protocols/commit/1455bc0), [IDF@b213f2c](https://github.com/espressif/esp-idf/commit/b213f2c6d3d78ba3a95005e3206d4ce370b8a649))
- driver, http_client, web_socket, tcp_transport: remove __FILE__ from log messages ([01b4f64](https://github.com/espressif/esp-protocols/commit/01b4f64), [IDF#5637](https://github.com/espressif/esp-idf/issues/5637), [IDF@caaf62b](https://github.com/espressif/esp-idf/commit/caaf62bdad965e6b58bba74171986414057f6757))
-  websocket_client : fix some issues for websocket client ([6ab0aea](https://github.com/espressif/esp-protocols/commit/6ab0aea), [IDF@341e480](https://github.com/espressif/esp-idf/commit/341e48057349d92c3b8afe5f9c0fcd0aa47500b0))
- websocket: add configurable timeout for PONG not received ([b71c49c](https://github.com/espressif/esp-protocols/commit/b71c49c), [IDF@0049385](https://github.com/espressif/esp-idf/commit/0049385850daebfe2222c8f0526b896ffaeacdd9))
- websocket client: the client now aborts the connection if send fails. ([f8e3ba7](https://github.com/espressif/esp-protocols/commit/f8e3ba7), [IDF@6bebfc8](https://github.com/espressif/esp-idf/commit/6bebfc84f3ed9c96bcb331fd0d5b0bbb26ce07a4))
- ws_client: fix fragmented send setting proper opcodes ([7a5b2d5](https://github.com/espressif/esp-protocols/commit/7a5b2d5), [IDF#4974](https://github.com/espressif/esp-idf/issues/4974), [IDF@14992e6](https://github.com/espressif/esp-idf/commit/14992e62c5573d8b6076281f16b4fe11d6bc8f87))
- esp32: add implementation of esp_timer based on TG0 LAC timer ([17281a5](https://github.com/espressif/esp-protocols/commit/17281a5), [IDF@739eb05](https://github.com/espressif/esp-idf/commit/739eb05bb97736b70507e7ebcfee58e670672d23))
- tcp_transport/ws_client: websockets now correctly handle messages longer than buffer ([aec6a75](https://github.com/espressif/esp-protocols/commit/aec6a75), [IDF@ffeda30](https://github.com/espressif/esp-idf/commit/ffeda3003c92102d2d5b145c9adb3ea3105cbbda))
- websocket: added missing event data ([a6be8e2](https://github.com/espressif/esp-protocols/commit/a6be8e2), [IDF@7c0e376](https://github.com/espressif/esp-idf/commit/7c0e3765ec009acaf2ef439e98895598b5fd9aaf))
- Add User-Agent and additional headers to esp_websocket_client ([a48b0fa](https://github.com/espressif/esp-protocols/commit/a48b0fa), [IDF@9200250](https://github.com/espressif/esp-idf/commit/9200250f512146e348f84ebfc76f9e82e2070da2))
- ws_client: fix handling timeouts by websocket client. ([1fcc001](https://github.com/espressif/esp-protocols/commit/1fcc001), [IDF#4316](https://github.com/espressif/esp-idf/issues/4316), [IDF@e1f9829](https://github.com/espressif/esp-idf/commit/e1f982921a08022ca4307900fc058ccacccd26d0))
- websocket_client: fix locking mechanism in ws-client task and when sending data ([d0121b9](https://github.com/espressif/esp-protocols/commit/d0121b9), [IDF@7c5011f](https://github.com/espressif/esp-idf/commit/7c5011f411b7662feb50fd1e53114bec390d8c2e))
- ws_client: fix for not sending ping responses, updated to pass events also for PING and PONG messages, added interfaces to send both binary and text data ([f55d839](https://github.com/espressif/esp-protocols/commit/f55d839), [IDF@abf9345](https://github.com/espressif/esp-idf/commit/abf9345b85559f4a922e8387f48336fb09994041))
- websocket_client: fix URI parsing to include also query part in websocket connection path ([f5a26c4](https://github.com/espressif/esp-protocols/commit/f5a26c4), [IDF@271e6c4](https://github.com/espressif/esp-idf/commit/271e6c4c9c57ca6715c1435a71fe3974cd2b18b3))
- ws_client: fixed posting to event loop with websocket timeout ([23f6a1d](https://github.com/espressif/esp-protocols/commit/23f6a1d), [IDF@5050506](https://github.com/espressif/esp-idf/commit/50505068c45fbe97611be9b7f2c30b8160cbb9e3))
- ws_client: added subprotocol configuration option to websocket client ([2553d65](https://github.com/espressif/esp-protocols/commit/2553d65), [IDF@de6ea39](https://github.com/espressif/esp-idf/commit/de6ea396f17be820153da6acaf977c1bf11806fb))
- ws_client: fixed path config issue when ws server configured using host and path instead of uri ([67949f9](https://github.com/espressif/esp-protocols/commit/67949f9), [IDF@c0ba9e1](https://github.com/espressif/esp-idf/commit/c0ba9e19fc6cff79f5760b991c259970bd4abeab))
- ws_client: fixed transport config option when server address configured as host, port, transport rather then uri ([bfc88ab](https://github.com/espressif/esp-protocols/commit/bfc88ab), [IDF@adee25d](https://github.com/espressif/esp-idf/commit/adee25d90e100a169e959f94db23621f6ffab0e6))
- esp_wifi: wifi support new event mechanism ([4d64495](https://github.com/espressif/esp-protocols/commit/4d64495), [IDF@003a987](https://github.com/espressif/esp-idf/commit/003a9872b7de69d799e9d37521cfbcaff9b37e85))
- tools: Mass fixing of empty prototypes (for -Wstrict-prototypes) ([da74a4a](https://github.com/espressif/esp-protocols/commit/da74a4a), [IDF@afbaf74](https://github.com/espressif/esp-idf/commit/afbaf74007e89d016dbade4072bf2e7a3874139a))
- ws_client: fix double delete issue in ws client initialization ([f718676](https://github.com/espressif/esp-protocols/commit/f718676), [IDF@9b507c4](https://github.com/espressif/esp-idf/commit/9b507c45c86cf491466d705cd7896c6f6e500d0d))
- ws_client: removed dependency on internal tcp_transport header ([13a40d2](https://github.com/espressif/esp-protocols/commit/13a40d2), [IDF@d143356](https://github.com/espressif/esp-idf/commit/d1433564ecfc885f80a7a261a88ab87d227cf1c2))
- examples: use new component registration api ([35d6f9a](https://github.com/espressif/esp-protocols/commit/35d6f9a), [IDF@6771eea](https://github.com/espressif/esp-idf/commit/6771eead80534c51efb2033c04769ef5893b4838))
- esp_websocket_client: Add websocket client component ([f3a0586](https://github.com/espressif/esp-protocols/commit/f3a0586), [IDF#2829](https://github.com/espressif/esp-idf/issues/2829), [IDF@2a2d932](https://github.com/espressif/esp-idf/commit/2a2d932cfe2404057c71bc91d9d9416200e67a03))
