FAUST Audio Playground
======================

This repository contains the source code for the Faust Audio Playground.
The goal of this project is to provide a web plateform in which you can easily test/patch 
and export your Faust DSPs or the ones you find surfing on the web.

The pedagogical version includes a library of modules directly available in the page.

Additional ressources
=====================

The following files needs to be added in the deployed version of 'webaudio' folder :

- libfaust.js located in '/usr/local/lib' folder after installation
- jsscripts.js located in '/usr/local/lib/faust/js' folder after installation

Launch locally
==============

To easily test locally, you can start a python server

cd faustplaygroundrepository
python -m SimpleHTTPServer

Then access the page : 
http://127.0.0.1:8000/faustplayground/
http://127.0.0.1:8000/faustplayground/pedagogie