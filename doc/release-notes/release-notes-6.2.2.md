The IoP Blockchain client version *6.2.2* is now available

News
====
Official Ubuntu 18.04 package

Fixes
=====
Fixed a bug in the update check routine
Fixed some faulty icon rendering

Known Issues
============
Toolbar icons still render imperfectly
Scaling on Linux is broken. To work around it, start the program with `QT_SCALE_FACTOR=2 iop-qt` or equivalently.
We received feedback about some possible UI improvements. Stay tuned!



General Information on 6.x.x
============================

This is a new major version release, including new features, various bugfixes
and performance improvements, as well as updated translations. See below for more information.
We have decided to drop the *IoP HD* name in favor of completely replacing the old client.
This software will from now on be referred to as **IoP Core**. 

While the consensus of the blockchain stays the same, the structure of the data directory **does not**. Therefore, **a full reindex of the blockchain is necessary** (see below for instructions). Additionally, the naming scheme of both executables and data files has been streamlined a bit, as detailed in the next section.

Removing all previous *IoP HD* or `iop-blockchain` packages is recommended to prevent possible confusion, but is not strictly necessary. Please be aware that you cannot use both v5.0.1 and v6.0.0 interchangeably with the same data directory.


Naming Scheme
=============

The binaries are `iopd`, `iop-cli`, `iop-tx` and `iop-qt`, while the Windows and macOS executables are `iop-qt.exe` and `IoP-Qt.app`, respectively. The configuration file is called `iop.conf`.

The default data directory for both the command line and the Qt Wallet is

- `~/.iop` on Linux,
- `%APPDATA%\IoP` on Windows, and
- `~/Library/Application Support/IoP` on macOS.

The Qt Wallet (**NOT** the command line utilities) will pick up your previously used data directory. 


How to update
=============

For most users, the relevant packages are the .dmg file (macOS), the .exe file for your CPU architecture (Windows 32-bit and 64-bit), and the .deb packages (Ubuntu 64-bit). Other Linux users should download i686-pc-linux (32-bit) or x86_64-linux (64-bit). The rest of the tar.gz files contain the command line utilities separately or are intended for uncommon architectures (these are untested, feedback is appreciated).


Upgrading from *v5.0.1* or below
================================

A full reindex of the blockchain is necessary if you upgrade from *v5.0.1* or below. The recommended procedure is as follows: 
- make a full backup of your data directory and then move it somewhere else. 
- create a new directory at the default location for your platform, containing only a copy of the files `wallet.dat` and (if applicable) `iop.conf`. 
- start the software.

