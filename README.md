# pylab

[![Generic badge](https://img.shields.io/badge/powered%20by-ITO-blue)](https://www.ito.uni-stuttgart.de/)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL_v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

[![made-with-python](https://img.shields.io/badge/Made%20with-Python-1f425f.svg)](https://www.python.org/)
[![made-with-opencv](https://img.shields.io/badge/Made%20by-OpenCV-green)](https://opencv.org/)
[![made-with-qt](https://img.shields.io/badge/Made%20by-Qt-brightgreen)](https://www.qt.io/product/framework)

pylab future want to a cross-platform, integrated development environment (IDE) for
application developers to create applications for multiple desktop, embedded,
and mobile device platforms. and now is build on windows.

## What is this project for?

This project contains the core application of:
* pylab core application

Furthermore, you may also need the ``plugins`` and ``designer plugins`` repositories to get all itom functionalities.
* plugins hardware/software plugins
* designer plugins widget plugins




# Licensing
The core components and the main application of itom are covered by the [GNU Library General Public Licence (GNU LGPL)](https://github.com/itom-project/itom/blob/master/COPYING.txt "GNU Library General Public Licence (GNU LGPL)"). All components belonging to the SDK of pylab.

## Exception
The full text license of LGPL and pylab is also included as file [COPYING](https://github.com/itom-project/itom/blob/master/COPYING.txt "COPYING") in the source distributions and setups.

All plugins and designer-plugins that can be integrated into itom can have their own licensing. Therefore the user is referred to the specific licensing documents or statements of each external library (plugin).

# Copy from qt bellow

## Supported Platforms

The standalone binary packages support the following platforms:

* Windows 10 (64-bit) or later
* TODO: (K)Ubuntu Linux 20.04 (64-bit) or later
* TODO: macOS 10.14 or later

## Compiling 

Prerequisites:

* Qt 5.15.2 or later
* Qt WebEngine module for QtWebEngine based help viewer
* On Windows:
    * MinGW with GCC 7 or Visual Studio 2017 or later
    * Python 3.5 or later (optional, needed for the python enabled debug helper)
    * Debugging Tools for Windows (optional, for MSVC debugging support with CDB)
* On Mac OS X: latest Xcode
* On Linux: GCC 7 or later
* LLVM/Clang 10 or later (optional, LLVM/Clang 14 is recommended.
  See [instructions](#getting-llvmclang-for-the-clang-code-model) on how to
  get LLVM.
  The ClangFormat plugin uses the LLVM C++ API.
  Since the LLVM C++ API provides no compatibility guarantee,
  if later versions don't compile we don't support that version.)
* CMake
* Ninja (recommended)

The used toolchain has to be compatible with the one Qt was compiled with.
