# Compositional Numeric Library

THIS DEPOT IS CURRENTLY IDENTICAL TO THE PARENT CNL v1.1.7.

The Compositional Numeric Library (CNL) is a C++ library of fixed-precision numeric classes which enhance integers to
deliver safer, simpler, cheaper arithmetic types.

This is a fork of [v1.x](https://github.com/johnmcfarlane/cnl/tree/v1.x).
This fork will have changes to improve usability with Arduino build environments.
Specifically, this fork will remain on v1.x (which requires only C++11).
This fork will also modify CNL to use Arduino-style `String`, rather than `std::string`,
as Arduino environments (and embedded generally) do not often have full support for
the `std` namespace.

Documentation on CNL can be found [here](http://johnmcfarlane.github.io/cnl/).

## Requirements

CNL v1.x requires a C++11-compatible tool chain.

NOTE: The Arduino-focused builds have not been built or tested yet.

## Instructions

### PlatformIO

It is expected that use with PlatformIO will be possible by
linking directly to this depot as a library, specifying the tag
for the version you wish to use.  For example, the project configuration
might include:

```ini
lib_deps =
    https://github.com/SimpleHacks/cnl.git#v1.x
```

In fact, this appears to work today, although only when various
string functions in `std::` are available (or, as a non-recommended
hack, where implementations are provided by the user).

### Arduino

TBD ... unsure if reasonable to support due to CMake requirement?

### Integration

The API is exposed through headers in the [include](./include/) directory.
Add this to your system header list and include, e.g.:

```c++
// to use a specific type:
#include <cnl/scaled_integer.h>

// or to include all CNL types:
#include <cnl/all.h>
```
