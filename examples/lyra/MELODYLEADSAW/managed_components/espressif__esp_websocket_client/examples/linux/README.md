# ESP Websocket Client - Host Example

This example demonstrates the ESP websocket client using the `linux` target. It allows for compilation and execution of the example directly within a Linux environment.

## Compilation and Execution

To compile and execute this example on Linux need to set target `linux`

```
idf.py --preview set-target linux
idf.py build
./websocket.elf
```

## Example Output

```
I (164532) websocket: [APP] Startup..
I (164532) websocket: [APP] Free memory: 4294967295 bytes
I (164532) websocket: [APP] IDF version: v5.3-dev-1353-gb3f7e2c8a4
I (164538) websocket: Connecting to ws://echo.websocket.events...
W (164538) websocket_client: `reconnect_timeout_ms` is not set, or it is less than or equal to zero, using default time out 10000 (milliseconds)
W (164538) websocket_client: `network_timeout_ms` is not set, or it is less than or equal to zero, using default time out 10000 (milliseconds)
I (165103) websocket: WEBSOCKET_EVENT_CONNECTED
I (165539) websocket: Sending hello 0000
I (165627) websocket: WEBSOCKET_EVENT_DATA
I (165627) websocket: Received opcode=1
W (165627) websocket: Received=hello 0000
W (165627) websocket: Total payload length=10, data_len=10, current payload offset=0

I (166539) websocket: Sending fragmented message
```

## Coverage Reporting
For generating a coverage report, it's necessary to enable `CONFIG_GCOV_ENABLED=y` option. Set the following configuration in your project's SDK configuration file (`sdkconfig.ci.coverage`, `sdkconfig.ci.linux` or via `menuconfig`):
