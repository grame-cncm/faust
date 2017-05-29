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


##  Note about network management

The default UDP ports are chosen in an unassigned range 
see IANA PORT NUMBERS (last updated 2011-01-24)
at http://www.iana.org/assignments/port-numbers
As of today (jan. 27 2011), the range 5507-5552 is unassigned
and the default ports numbers are:
- 5510 for listening UDP port
- 5511 for the osc output port
- 5512 for the osc error port

#### Changing the ports numbers with the command line

An OSCControler object takes the command line arguments as constructor 
parameters. It supports the following options to change the UDP ports 
numbers: [-port | -outport | -errport] number

#### Dynamic UDP listening port allocation

When the UDP listening port number is busy, the system automatically 
looks for the next available port number. Unless otherwise specified 
by the command line, the UDP output port numbers are unchanged and 
the system sends the allocated ports numbers on the osc output port 
on startup.

#### Destination address

The default UDP output streams destination is 'localhost'. It can be 
changed with a command line option: -dest address 
where address is a host name os an IP number.

In case of trouble, contact me at: <fober@grame.fr>
