Overview
========

This page provides an overview of the Faust Web UI.  The Faust Web UI can be
used to control Faust applications running on a server via GET requests.
An experimental version of WebKit also provides a serverless version of the
Web UI.

Using the Web UI
----------------

In order to use the Faust Web UI, one may access a server running a Faust
application over the appropriate port via a browser that visualizes SVG
according to the W3C specification (http://www.w3.org/2000/svg).  Once the
URL is composed, the graphical UI for the application will be displayed in
the browser.  So, for example, if the website www.ensemble101.fr is running
a faust application on port 8000, the URL http://www.ensemble101.fr:8000 would
be used to access the application.

The goal of Faust Web UI is to provide a robust graphical UI similar to that
of other Faust interfaces (Qt, gtk+, etc.). Should a Faust Web UI fail to
parallel one of these interfaces in the objects drawn or their responsiveness,
an e-mail can be sent to faustwebui@grame.fr.
