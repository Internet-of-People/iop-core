IoP Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/Internet-of-People/iop-core.svg?branch=master)](https://travis-ci.org/Internet-of-People/iop-core)

https://iop.global


**RELEASE NOTE v6.2.3**
-----------------------

The IoP Blockchain client version *6.2.3* is now available

Fixes
=====
Fixed bug that causes nodes to crash if a new block contains duplicate inputs (recently discovered in bitcoin core)
Fixed segregation fault on running iop-qt with startup arguments that cause the program to exit before the Qt backend is initialized.
Fixed strange behavior of the IOP buy dialog. Input field will now change color if input is out of range instead of rejecting input.


Known Issues
============
Toolbar icons still render imperfectly
Scaling on Linux and Windows is still broken. To work around it, start the program with `QT_SCALE_FACTOR=2 iop-qt` or equivalently.
We received feedback about some possible UI improvements. Stay tuned!


**RELEASE NOTE v6.2.0**
-----------------------
We are proud to announce a complete redesign of the IoP Core wallet.
You can now buy IOP directly from inside the wallet software thanks to our collaboration with Indacoin.


**RELEASE NOTE v6.1.0**
-----------------------

This major release is meant to replace the old version of the IoP Blockchain client. While the consensus remains fully compatible, the structure of the data directory does not. Please read the [release notes](doc/release-notes/release-notes-6.1.0.md) very carefully if you update from version 5.0.1 or below.


What is IoP?
------------

IoP is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. IoP uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. IoP Core is the name of open source
software which enables the use of this currency.


License
-------

IoP Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/Internet-of-People/iopg-hd/tags) are created
regularly to indicate new official, stable release versions of IoP Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The [Discord channel](https://discord.gg/gsRKp6T)
should be used to discuss complicated or controversial changes before working
on a patch set.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
