

#ifndef PYTHONITOM_H
#define PYTHONITOM_H

/* includes */
#ifndef Q_MOC_RUN
    #define PY_ARRAY_UNIQUE_SYMBOL itom_ARRAY_API //see numpy help ::array api :: Miscellaneous :: Importing the api (this line must before include global.h)
    #define NO_IMPORT_ARRAY

    #include "python/pythonWrapper.h"
#endif

#include "../global.h"

#include <qhash.h>
#include <qstring.h>

namespace ito
{

class FuncWeakRef; //forward declaration

class PythonItom
{

public:
    static PyMethodDef PythonMethodItom[];
    static PyModuleDef PythonModuleItom;
    static PyObject* PyInitItom(void);

    //!< methods of module itom
    static PyObject* PyOpenEmptyScriptEditor(PyObject *pSelf, PyObject *pArgs);
    static PyObject* PyNewScript(PyObject *pSelf, PyObject *pArgs);
    static PyObject* PyLog(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PyOpenScript(PyObject *pSelf, PyObject *pArgs);
    static PyObject* PyClearCommandLine(PyObject *pSelf);
    static PyObject* PyShowHelpViewer(PyObject* pSelf, PyObject* pArgs, PyObject* pKwds);

    static PyObject* PyPlotImage(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);
    static PyObject* PyLiveImage(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);

    static PyObject* PyPlot1d(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);
    static PyObject* PyPlot2d(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);
    static PyObject* PyPlot25d(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);

    static PyObject* PyFilter(PyObject *pSelf, PyObject *pArgs, PyObject *pKwds);
    static PyObject* PyFilterHelp(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyWidgetHelp(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyPluginHelp(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyAboutInfo(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyPlotHelp(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyItomVersion(PyObject* pSelf, PyObject* pArgs, PyObject* pKwds);

    static PyObject* PyLoadIDC(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PySaveIDC(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);

    static PyObject* PyPluginLoaded(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PyFilterLoaded(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PyPlotLoaded(PyObject* pSelf, PyObject* pArgs);

    static PyObject* PySaveDataObject(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyLoadDataObject(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);

    static PyObject* PyRegisterResource(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyUnregisterResource(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);

    static PyObject* PyAddButton(PyObject* pSelf, PyObject* pArgs, PyObject *kwds);
    static PyObject* PyRemoveButton(PyObject* pSelf, PyObject* pArgs);

    static PyObject* PyAddMenu(PyObject* pSelf, PyObject* args, PyObject *kwds);
    static PyObject* PyRemoveMenu(PyObject* pSelf, PyObject* args, PyObject *kwds);

	static PyObject* PySetCentralWidgetsSizes(PyObject* pSelf, PyObject* pArgs, PyObject* pKwds);

	static PyObject* PyDumpMenusAndButtons(PyObject* pSelf);

    static PyObject* PyCheckSignals(PyObject* pSelf);
    static PyObject* PyProcessEvents(PyObject* pSelf);

    static PyObject* PySaveMatlabMat(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PyLoadMatlabMat(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PyMatlabMatDataObjectConverter(PyObject *element);  /*!< returns new reference to element.checks whether element is a npDataObject or dataObject and if so,  */

    static PyObject* PyGetDebugger(PyObject* pSelf);
    static PyObject* PyGCStartTracking(PyObject *pSelf);
    static PyObject* PyGCEndTracking(PyObject *pSelf);

    static PyObject* PyAutoReloader(PyObject* pSelf, PyObject *args, PyObject *kwds);

    static PyObject* PyGetScreenInfo(PyObject* pSelf);

    static PyObject* getDefaultScaleableUnits(PyObject* pSelf);
    static PyObject* scaleValueAndUnit(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);

    static PyObject* getAppPath(PyObject* pSelf);
    static PyObject* getQtToolPath(PyObject* pSelf, PyObject* pArgs);
    static PyObject* getCurrentPath(PyObject* pSelf);
    static PyObject* setCurrentPath(PyObject* pSelf, PyObject* pArgs);

    static PyObject* PyGetPalette(PyObject* pSelf, PyObject* pArgs);
    static PyObject* PySetPalette(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);
    static PyObject* PyGetPaletteList(PyObject* pSelf, PyObject* pArgs);

    static PyObject* compressData(PyObject* pSelf, PyObject* pArgs);
    static PyObject* uncompressData(PyObject* pSelf, PyObject* pArgs);

    static PyObject* setApplicationCursor(PyObject* pSelf, PyObject* pArgs);

    static PyObject* userCheckIsAdmin(PyObject* pSelf);
    static PyObject* userCheckIsDeveloper(PyObject* pSelf);
    static PyObject* userCheckIsUser(PyObject* pSelf);
    static PyObject* userGetUserInfo(PyObject* pSelf);

    static PyObject* PyClearAll(PyObject* pSelf);

    static PyObject* PyCopyStringToClipboard(PyObject* pSelf, PyObject* pArgs, PyObject *pKwds);

protected:
    static QHash<size_t, QString> m_gcTrackerList; //!< list with objects currently tracked by python garbage collector.

    static ito::FuncWeakRef* hashButtonOrMenuCode(PyObject *code, PyObject *argtuple, ito::RetVal &retval, QString &codeString);
    static ito::RetVal unhashButtonOrMenuCode(const size_t &funcID);
    static ito::RetVal unhashButtonOrMenuCode(const ito::FuncWeakRef *funcWeakRef);
};

} //end namespace ito
#endif
