# Compiling and Installing Faust

This chapter describes how to get and compile the Faust compiler as well as
other tools related to Faust (e.g., [`libfaust`](#libfaust), `libosc`, 
`libhttpd`, etc.). 

## Getting the Source Code

An overview of the various places where the Faust source can be downloaded is
given [here](#the-faust-distribution). 

If you downloaded the latest Faust release, just un-compressed the archive 
file and open it in a terminal. For instance, something like (this might vary 
depending on the version of Faust you downloaded):

```
tar xzf faust-2.5.31.tar.gz
cd faust-2.5.31
``` 

If you wish to get the Faust source directly from the git repository, just
run:

```
git clone --recursive https://github.com/grame-cncm/faust.git
cd faust
```

in a terminal. Note that the `--recursive` option is necessary here since some 
elements (e.g., the Faust DSP libraries) are placed in other repositories.

Finally, if you wish to use the development (and potentially unstable) branch, 
just run:

```
git checkout master-dev
```

after the previous 2 commands.

TODO: see with Dominique for whatever comes next here...

Since release 2.5.18, Faust compilation and installation is based on `cmake`.
