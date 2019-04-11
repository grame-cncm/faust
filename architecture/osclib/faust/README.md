# FAUST OSC Library

## Note about the OSC messages and address space

The OSC address space adheres strictly to the hierarchy defined by
the 'addnode' and 'opengroup' calls.
A node expects to receive OSC messages with a single float value
as parameter. This policy is strict for the parameters count, but
relaxed for the parameter type: OSC int values are accepted and
casted to float.

#### 'get' message

The library provides a simple support for querying the system with
a 'get' message that can be sent to any valid OSC address.
The 'get' message is propagated to every terminal node that responds
with its osc address and current values (value, min and max).

#### 'hello' message

The library provides a simple support for modules discovery with a
'hello' message that can be sent to any module root address. The module
responds with its root address, followed by its IP address, followed
by the UDP ports numbers (listening port, output port, error port).
See the note about network management below for ports numbering scheme.

#### 'json' message

The `json` message is handled by any module root address. The JSON module description will be sent on the output port.

#### 'xmit' message

The `xmit` message is handled by any module root address. It must be followed by an integer value (Ø|1|2). It turns the OSC UI transmit mode on or all or alias. When `all`, any change of a UI element generates the corresponding OSC message including aliases messages if any and the module could be used as a remote control for similar modules. In `alias` mode, only the aliases messages are sent.

#### 'bundle' message

The `bundle` message is handled by any module root address. It must be followed by a boolean value (Ø|1). The `bundle` mode affects the transmition mode (see `xmit` message above). When the `bundle` mode is on, all the OSC messages are generated in an OSC bundle that must be sent at regular interval. To do so, the OSCUI class provides an `endBundle()` method, it's the architecture responsability to call this method to trigger the current bundle transmission. A typical implementation could call it just after the compute method.


#### 'alias' message

The `alias` mechanism provided at metadata level to control a Faust application from a preexisting set of OSC messages, is dynamically available using OSC message as well. The general form of the OSC `alias` message is the following:
~~~
alias message :=
  a)                /target/address alias
  b)              | /target/address alias /alias/address
  c)              | /target/address alias /alias/address min max
~~~
- The **a)** form removes all aliases associated to `/target/address`
- The **b)** form removes the aliase `/alias/address` associated to `/target/address`
- The **c)** form creates the alias `/alias/address` to `/target/address` and scales the alias values from `min`, `max` to the target range of values.

##  Note about network management

The default UDP ports are chosen in an unassigned range
see IANA PORT NUMBERS (last updated 2011-01-24)
at http://www.iana.org/assignments/port-numbers
As of today (jan. 27 2011), the range 5507-5552 is unassigned
and the default ports numbers are:
- **5510** the listening UDP port number
- **5511** the OSC output port number
- **5512** the OSC error port number

#### Changing the ports numbers with the command line

An OSCControler object takes the command line arguments as constructor
parameters. It supports the following options to change the UDP ports
numbers: [-port | -outport | -errport] number

#### Dynamic UDP listening port allocation

When the UDP listening port number is busy, the system automatically
looks for the next available port number. Unless otherwise specified
by the command line, the UDP output port numbers are unchanged. An OSC application sends the allocated ports numbers on the OSC output port on startup.

#### Destination address

The default UDP output streams destination is 'localhost'. It can be
changed with a command line option: -dest address
where address is a host name os an IP number.


##  Sharing ports numbers between several applications

Since version 1.1.0 of the Faust OSC library, a new command line option [ -reuse ] allows to share a listening port between several applications on the same host.
It works in conjunction with the multicast address 224.0.0.1.
Thus, messages addressed to applications launched with `-reuse 1` must be send to the IP address 224.0.0.1.

**Note**: any application running on any host on the same local network, launched with `-reuse 1` and using the same listening port, will receive all the messages addressed to 224.0.0.1 on this port.

Different listening port numbers can be used to create a group of applications restricted to a local host or to create an arbitrary group of applications distributed over the local network.

---

##  Summary of the command line options

- `-port    num`: sets the listening port number (default: 5510)
- `-outport num`: sets the listening port number (default: 5511)
- `-errport num`: sets the listening port number (default: 5512)
- `-desthost [IP|hostname]`: sets the output destination address (defaults to the first incoming message address)
- `-xmit [0|1|2]`: controls UI values transmition  (default: 0)
- `-xmitfilter <paths list>`: sets OSC paths to be filtered on output.
- `-reuse [0|1]`: turns listening port sharing on or off  (default: 0)
- `-bundle [0|1]`: turns OSC bundles on or off  (default: 0)
- `-help`: print a summary of the OSC options

---

In case of trouble, contact me at: <fober@grame.fr>
