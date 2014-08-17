desqview-examples
=================

FASM examples for Quarterdeck DESQview. For most recent version of this document go to:

https://github.com/fone32/desqview-examples/edit/master/README.md

About DESQview
==============

DESQview is a text based multitasking environment running on top of MS-DOS compatible systems. It can ran even on 286 machines however DESQview 386 requires (like the name suggests) both 386 or higher CPU and QEMM 386 (Quarterdeck Memory Manager). 

While DESQview is a text based environment it still can run applications that uses graphic modes. It even is capable of running Windows 2.x and 3.x (real mode, enhanced mode will not work).

Quarterdeck also manage to release DESQView/X a complete X environment for DOS system. Contrary to DESQview and DESQview 386 DESQview/X runs in graphic mode. 

This document does not address DESQview/X dedicated features.

DESQview downloads
==================

You can download several DESQview releases including the X version from the following site: http://www.chsoft.com/dv.html

Running DESQview
================

You can ran DESQview on MS DOS compatible system. However it is not possible to run it correctly under Windows provided Dos Box under NTVDM (NT Virtual DOS Machine). Instead you need either need to run it under emulator like Bochs or QEMU or under hypervisor like VMware Player for example. Those option require to install DOS system inside emulated or virtual machine. On such created DOS machine you can install and later run DESQView. The quickest (but with some limitations) option is to run DESQview under DosBox (http://www.dosbox.com/) emulator. This section explains how to configure DosBox to be able to run DESQview. Keep in mind that DosBox is targeting DOS games and not utilities like DESQview. This is why CONFIG.SYS is missing for example. 

  1. Download and install DosBox
  2. Open configuration file (i.e. dosbox-0.74.con)
  3. In the [cpu] section change following lines as shown:
      core=dynamic
      cputype=pentium_slow
      cycles=auto
  4. In the [dos] section enable XMS memory by setting it to true as shown (you can enable UMB too):
      xms=true
  5. In the [dos] section add or edit "files" setting to 200 as shown:
      files=200
  6. Create directory with DESQview unpacked installation files
  7. Start DosBox
  8. Mount DESQview installation directory as a separate drive (i.e. mount d: c:\desqview-install)
  9. Mount your dos directory as a C: driver (i.e mount c: c:\dosfiles)
  10. Run DESQview installer (you will be asked to provide a serial number)
  11. Select C: drive for installation
  12. Run DESQview from C: drive

DO NOT INSTALL QEMM as it will not run correctly under plain DosBox. To install QEMM you need to install DOS under DosBox first. 

Running DESQview under other emulators
--------------------------------------

 * rpix86 - currently DESQview will not run since INT 67 emulation is missing
 * vDosBox - not tested
 * DOSEMU - not tested

Bochs and QEMU should be fine if you install DOS. You can also use VMWare Player or VMWare ESX to run DOS inside VM.
 

Programming DESQview - basic concepts
=====================================

DESQview can ran 3 types of applications (original naming convention from Quarterdeck documentation has been preserved):

 * DESQview-oblivious: those are DOS or DOS Extended applications that are not aware of DESQView presence nor functionality.
 * DESQview-aware: those are DOS programs that checks for DESQView presence so they could ran a bit more efficiently under DESQView environment
 * DESQview-specific: those are applications written specifically for DESQView taking advantage of DESQview api and it's functionality

DESQview even in 386 version does not allow full hardware virtualization since it is based on VCPI and whole concept of VCPI is to enable application to have access to mode switching and memory management functions so that memory managers, task switchers and DOS extenders can coexist. As a side effect DOS Extenders runs in privilege (ring 0) level under VCPI on 386+ CPUs. This means that DOS Extender running under DESQview 386 will run in ring 0 and DESQview can't virtualize its access to underlying hardware. In case of DESQview running on 286 CPU protected mode is not being used at all and VCPI requires 386 or higher CPU. 

Therefore DESQview uses couple of different methods to handle DESQview-oblivious applications. If DESQview can recognize the application being loaded and it contains a special patch for it, the loader will patch the program before execution takes place. This allow DESQview to handle application that misbehave - access IO ports or gfx memory directly for example - even without protected mode on 286. Additionally if a PIF (Windows Program Information File dating back to IBM TopView) or DVQ (DESQvie Program Information File) is available, memory limits and other options will be applied to the execution environment of loaded application.

IRQs and DESQview
-----------------

Due to performance reasons DESQview is reprogramming PIC to redirect IRQ (08h-0Fh for IRQ0-07h and 70h-77h for IRQ8-15) IRQs - probably it was done mainly to speed up performance by separating IRQ5 from interrupt 0Dh: the General Protection Fault (GPF). While it does not sounds like a good idea today it wasn't such a bad move back in its day. 

DESQview relocates IRQ0 to INT 50h and uses next interrupt vectors for the rest of IRQs up to INT 5Fh.

DESQview and DOS Extenders
==========================

DESQview 386 is aware of DOS Extenders and can run DOS Extended application. In fact DOS Extended applications can even run simultaneously using different DOS Extenders thanks to VCPI. The previous statement is obviously true only for VCPI compliant DOS Extenders.  

The Extended application runs in protected mode environment created by the DOS Extender. When INT is being generated by the application it is intercepted by DOS Extender and execution is switched into virtual 86 mode (V86). From V86 mode DOS Extender can either call real mode DOS/BIOS interrupt service routine or pass a call to DESQview/QEMM-386. The DESQview/QEMM-386 serves as VCPI server running again in protected mode environment.

Please note that newer version of QEMM besides providing VCPI support also DPMI through QDPMI program.

VCPI
----
VCPI has been designed before DPMI - one of architects of this standard was Quarterdeck itself. VCPI can run on 386 or higher CPUs as it is implemented around virtual 86 mode (please note that v86 mode is not longer available on x64 in long mode). DOS extender programas running under VCPI enabled dos extender execute in ring 0 unless dos extender is being configured otherwise. In case of Phar Lap TNT DOS Extender the -unpriv switch for DosStyle programs allows to run code at ring 3 instead for example. This is one of main differences between VCPI and DPMI. Under VCPI your code is either priviledge or you can run it in ring 3. Under DPMI it is DPMI host decision which unpriviledge ring will be used for executing your code. In reality most if not every single one DPMI host implementations executes your code at ring 3. 
To check for VCPI presence you can use INT 67h (please note that this interrupt is not emulated under all emulators - rpix86 is one of them) function DE00h. If VCPI is present AH is set to 0 and BX contains VCPI version number. 

For a compelete [VCPI standard](doc/vcpi.txt) please refer to our doc section. 

IRQ redirection under DOS Extenders
-----------------------------------

As noted earlier DESQview during startup is reprogramming PIC in order to redirect IRQs. If you are developing a DOS extended application that installs own IRQ handlers you have to check how your extender deals with this situation. Some DOS extenders - like Phar Lap TNT DOS Extender for example - always present IRQs at their original locations regardless of VCPI/DESQview setup. Other - like PMODE - may not be aware of DESQview at all and/or may ignore the DESQview behavior.

Programming under DESQview using FASM
=====================================

After introduction to some of basic DESQview concepts you can start creating DESQview-aware applications. To create DESQview-specific applications you would need to get understand how panels and tasks works at least. This document does not cover those topic at the moment.

For DESQview-aware applications we provide a set of includes aiding you in development process using FASM. Please note that originally DESQview is not aware of FASM and developer files aren't compatible with FASM syntax.

DVAPI.INC
---------

This is base include file that has been distributed by Quarterback. FASM does not support its syntax. 
Basically the file provides interface based on macros. DESQview API calling is based around INT 15h with one notable exception: INT 15h could not be used to DESQview presence check. Quarterdeck has decided to use INT 21h instead. For DESQview installation/presence check please look at provided examples. 
The OpenWatcom project provided own porn of DESQview API include file – it will also not work with FASM. 

WARNING: DVAPI.INC is work in progress. The porting of original file to FASM syntax is not finished yet therefore you can now find only constants defined originally by Quarterdeck. Macros are missing.

FASM includes
-------------

Besides port of original DVAPI.INC we provide few additional includes that can be used in your DESQview project:

 * DV.INC - this is main include for all examples, it includes all below include files and also contain data definitions
 * DESQVIEW.INC - this include handles DESQview detection and some basic functions documented in original docs; this files is part of f/One32 FAPI interface hence it may not be fully compatible with original Quarterdeck functions.


Copyright ACP 2014
