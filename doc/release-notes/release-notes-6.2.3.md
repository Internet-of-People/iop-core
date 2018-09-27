**RELEASE NOTE v6.2.3**
-----------------------

The IoP Blockchain client version *6.2.3* is now available

Fixes
=====
Fixed bug that causes nodes to crash if a new block contains duplicate inputs (recently discovered in bitcoin core)
Fixed segregation fault on running iop-qt with startup arguments that cause the program to exit before the Qt backend is initialized.

Improvements
============
Input field in the "Buy IOP" dialog will now change color if input is out of range instead of rejecting input.


Known Issues
============
Toolbar icons still render imperfectly
Scaling on Linux and Windows is still broken. To work around it, start the program with `QT_SCALE_FACTOR=2 iop-qt` or equivalently.
We received feedback about some possible UI improvements. Stay tuned!
